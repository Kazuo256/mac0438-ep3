
#include "rollercoastermonitor.h"

#include "car.h"
#include "mutex.h"
#include "log.h"

namespace ep3 {

void RollerCoasterMonitor::pegaCarona (unsigned psg_id, bool golden) {
  Mutex::Lock lock(mutex_);
  // Wait for an available car.
  wait(available_car_, golden ? 0 : 1);
  // Enter the car and wait for the lap to end.
  signal(psg_aboard_);
  wait(lap_end_);
}

void RollerCoasterMonitor::carrega (unsigned car_id) {
  Mutex::Lock lock(mutex_);
  // Make sure to be the next car to load.
  // TODO
  // Wait for enough passengers to arrive.
  // TODO
  // Wait for passengers to fully board the car.
  for (unsigned i = 0; i < cap; i++) {
    signal(available_car_);
    wait(psg_aboard_);
  }
  cars_riding_.push(car_id);
  Log().debug("Car #"+utos(car_id)+" has started a new lap.");
}

void RollerCoasterMonitor::descarrega (unsigned car_id) {
  Mutex::Lock lock(mutex_);
  // Make sure the car wasn't outrunned.
  while (cars_riding_.front() != car_id)
    wait(riding_order_);
  cars_riding_.pop();
  Log().debug("Car #"+utos(car_id)+" has finished its lap.");
  signal_all(riding_order_);
  // Let the passengers leave.
  for (unsigned i = 0; i < cap; i++)
    signal(lap_end_);
}

void RollerCoasterMonitor::start_lap (unsigned car_id) {
  Mutex::Lock lock(mutex_);
  cars_riding_.push(car_id);
  Log().debug("Car #"+utos(car_id)+" has started a new lap.");
}

void RollerCoasterMonitor::finish_lap (unsigned car_id) {
  Mutex::Lock lock(mutex_);
  while (cars_riding_.front() != car_id)
    wait(riding_order_);
  cars_riding_.pop();
  Log().debug("Car #"+utos(car_id)+" has finished its lap.");
  signal_all(riding_order_);
}

//void RollerCoasterMonitor::testA (Rank rank) {
//  Mutex::Lock lock(mutex_);
//  wait(testcv_, rank);
//}
//
//void RollerCoasterMonitor::testB () {
//  Mutex::Lock lock(mutex_);
//  signal(testcv_);
//}

} // namespace ep3

