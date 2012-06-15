
#include "rollercoastermonitor.h"

#include "mutex.h"

namespace ep3 {

void RollerCoasterMonitor::start_lap (unsigned car_id) {
  Mutex::Lock lock(mutex_);
  cars_riding_.push(car_id);
}

void RollerCoasterMonitor::finish_lap (unsigned car_id) {
  Mutex::Lock lock(mutex_);
  while (cars_riding_.front() != car_id)
    wait(riding_order_);
  cars_riding_.pop();
  signal_all(riding_order_);
}

void RollerCoasterMonitor::testA (Rank rank) {
  Mutex::Lock lock(mutex_);
  wait(testcv_, rank);
}

void RollerCoasterMonitor::testB () {
  Mutex::Lock lock(mutex_);
  signal(testcv_);
}

} // namespace ep3

