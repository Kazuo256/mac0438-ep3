
#include "rollercoastermonitor.h"

#include "car.h"
#include "mutex.h"
#include "log.h"

namespace ep3 {

void RollerCoasterMonitor::pegaCarona (bool golden) {
  Mutex::Lock lock(mutex_);
  // Warn cars that there are more passengers waiting.
  if (empty(waiting_psgs_))
    waiting_psgs_count_++;
  else
    signal(waiting_psgs_);
  // Wait for an available car.
  wait(available_car_, golden ? 0 : 1);
  // Wait for the ride to end.
  wait(ride_end_);
}

void RollerCoasterMonitor::carrega (unsigned car_id) {
  Mutex::Lock lock(mutex_);
  // Make sure to be the next car to load.
  if (loading_car_)
    wait(loading_cars_);
  else
    loading_car_ = true;
  Log().debug("Car #"+utos(car_id)+" is waiting for passengers.");
  // Wait for enough passengers to arrive.
  for (unsigned i = 0; i < car_cap_; i++)
    if (waiting_psgs_count_ == 0)
      wait(waiting_psgs_);
    else
      waiting_psgs_count_--;
  // Let enough passengers in.
  for (unsigned i = 0; i < car_cap_; i++)
    signal(available_car_);
  Log().debug("Car #"+utos(car_id)+" is full.");
  // Let the next car load.
  if (empty(loading_cars_))
    loading_car_ = false;
  else
    signal(loading_cars_);
}

void RollerCoasterMonitor::descarrega (unsigned car_id) {
  Mutex::Lock lock(mutex_);
  // Make sure the car wasn't outrunned.
  while (cars_riding_.front() != car_id)
    wait(riding_order_);
  cars_riding_.pop();
  Log().debug("Car #"+utos(car_id)+" has finished its lap.");
  report();
  // Warn the others.
  signal_all(riding_order_);
  // Let the passengers leave.
  for (unsigned i = 0; i < car_cap_; i++)
    signal(ride_end_);
}

void RollerCoasterMonitor::ride (unsigned car_id) {
  // RIDE!
  Mutex::Lock lock(mutex_);
  cars_riding_.push(car_id);
  Log().debug("Car #"+utos(car_id)+" is now riding.");
  report();
}

void RollerCoasterMonitor::report () const {
  Log()
    .line("## There are "+utos(count(available_car_))+" passengers waiting.");
  dump(available_car_);
}

} // namespace ep3

