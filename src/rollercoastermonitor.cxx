
#include "rollercoastermonitor.h"

#include "car.h"
#include "passenger.h"
#include "mutex.h"
#include "log.h"

namespace ep3 {

using std::string;

// We seriously hope the code here is as legible as it can be.
// There are quite a few condition variables, so keep track of their purposes
// by referring to their documentation in the header.

void RollerCoasterMonitor::pegaCarona (const Passenger* psg) {
  Mutex::Lock lock(mutex_);
  // Warn cars that there are more passengers waiting.
  if (empty(waiting_psgs_))
    waiting_psgs_count_++;
  else
    signal(waiting_psgs_);
  // Report passenger arrival.
  report("Passenger "+psg->info()+" is arriving at the queue.");
  // Wait for an available car.
  wait(available_car_, psg->golden() ? 0 : 1);
  // Wait for the ride to end.
  wait(ride_end_[psg->current_car()]);
}

void RollerCoasterMonitor::carrega (Car* car) {
  Mutex::Lock lock(mutex_);
  // Make sure to be the next car to load.
  if (loading_car_)
    wait(loading_cars_);
  else
    loading_car_ = true;
  Log().debug(car->info()+" is waiting for passengers.");
  // Wait for enough passengers to arrive.
  for (unsigned i = 0; i < car_cap_; i++)
    if (waiting_psgs_count_ == 0)
      wait(waiting_psgs_);
    else
      waiting_psgs_count_--;
  // Let enough passengers in.
  for (unsigned i = 0; i < car_cap_; i++) {
    Thread *t = signal_and_fetch(available_car_);
    Passenger *psg = dynamic_cast<Passenger*>(t);
    if (psg) {
      psg->set_current_car(car);
      car->add_psg(psg);
    } else Log().warn("Unknown thread "+t->info()+" tried to board a car.");
  }
  Log().debug(car->info()+" is full.");
  // Let the next car load.
  if (empty(loading_cars_))
    loading_car_ = false;
  else
    signal(loading_cars_);
}

void RollerCoasterMonitor::descarrega (Car* car) {
  Mutex::Lock lock(mutex_);
  // Make sure the car wasn't outrunned.
  while (cars_riding_.front() != car->id())
    wait(riding_order_);
  // Now the car isn't riding anymore.
  cars_riding_.pop();
  car->stop();
  // Report car's ride end.
  report("Car "+car->info()+" has finished its ride.");
  // Warn the other riding cars that the order has been updated.
  signal_all(riding_order_);
  // Let the passengers leave.
  CondVar &cv = ride_end_[car];
  for (unsigned i = 0; i < car_cap_; i++) {
    Thread *t = signal_and_fetch(cv);
    Passenger *psg = dynamic_cast<Passenger*>(t);
    if (psg) {
      psg->set_current_car(NULL);
      car->drop_psg(psg);
    } else Log().warn("Unknown thread "+t->info()+" tried to leave a car.");
  }
}

void RollerCoasterMonitor::ride (Car* car) {
  Mutex::Lock lock(mutex_);
  // RIDE!
  cars_riding_.push(car->id());
  car->ride();
  // Report car's departure.
  report("Car "+car->info()+" is now riding.");
}

void RollerCoasterMonitor::register_car (const Car* car) {
  ride_end_[car] = CondVar();
}

void RollerCoasterMonitor::report (const string& title) const {
  Log()
    .line("Reporting: "+title)
    .line("Simulation status:")
    .line(" + Passengers currently waiting: "+utos(count(available_car_))+".");
  dump(available_car_);
  Log()
    .line(" + Cars currently riding: "+utos(cars_riding_.size())+
          " (of "+utos(Car::num())+").");
  Car::dump_all();
  Log().line();
}

} // namespace ep3

