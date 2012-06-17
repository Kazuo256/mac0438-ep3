
#include "car.h"

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::string;

unsigned Car::next_id_ = 0;

Car::Car (RollerCoasterMonitor* monitor) :
  monitor_(monitor),
  id_(next_id_++) {}

string Car::info () const {
  return "<car "+utos(id_)+">";
}

void Car::do_run () {
  while (true) {
    monitor_->carrega(this);
    monitor_->ride(this);
    Thread::delay(100.0f);
    monitor_->descarrega(this);
  }
}

} // namespace ep3

