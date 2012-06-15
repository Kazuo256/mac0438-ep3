
#include "car.h"

#include <cstdlib>
#include "rollercoastermonitor.h"
#include "thread.h"

namespace ep3 {

unsigned Car::next_id_ = 0;

Car::Car (RollerCoasterMonitor* monitor) :
  monitor_(monitor),
  id_(next_id_++) {}

void Car::start () {
  Thread *t = Thread::create(&thread);
  t->run(static_cast<void*>(this));
}

void Car::run () {
  while (true) {
    Thread::delay(1000.0f*rand()/RAND_MAX);
    monitor_->carrega();
    monitor_->start_lap(id_);
    Thread::delay(100.0f);
    monitor_->finish_lap(id_);
    monitor_->descarrega();
  }
}

void* Car::thread (void* args) {
  static_cast<Car*>(args)->run();
  return Thread::exit();
}

} // namespace ep3

