
#include "rollercoastermonitor.h"

#include "mutex.h"
#include "log.h"

namespace ep3 {

void RollerCoasterMonitor::pegaCarona (unsigned psg_id, bool golden) {
}

void RollerCoasterMonitor::carrega () {

}

void RollerCoasterMonitor::descarrega () {

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

void RollerCoasterMonitor::testA (Rank rank) {
  Mutex::Lock lock(mutex_);
  wait(testcv_, rank);
}

void RollerCoasterMonitor::testB () {
  Mutex::Lock lock(mutex_);
  signal(testcv_);
}

} // namespace ep3

