
#include "car.h"

#include <cstdlib>
#include "rollercoastermonitor.h"
#include "thread.h"

namespace ep3 {

unsigned Car::next_id_ = 0;

Car::Car (RollerCoasterMonitor* monitor) :
  monitor_(monitor),
  id_(next_id_++) {}

void Car::do_run () {
  while (true) {
    monitor_->carrega(id_);
    monitor_->ride(id_);
    Thread::delay(100.0f);
    monitor_->descarrega(id_);
  }
}

} // namespace ep3

