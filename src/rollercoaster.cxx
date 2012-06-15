
#include "rollercoaster.h"

#include <cstdlib>
#include <ctime>
#include <vector>

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"
#include "car.h"

namespace ep3 {

using std::vector;

RollerCoaster::RollerCoaster (unsigned car_num, unsigned car_cap) :
  monitor_(new RollerCoasterMonitor),
  car_num_(car_num) {}

RollerCoaster::~RollerCoaster () {
  Log().debug("Cleaning roller coaster resources...");
  delete monitor_;
}

void RollerCoaster::open () {
  srand(time(NULL));
  for (unsigned i = 0; i < car_num_; i++)
    cars_.push_back(Car(monitor_));
}

void RollerCoaster::run () {
  Log().line("== Starting roller coaster ==");
  vector<Car>::iterator it;
  for (it = cars_.begin(); it < cars_.end(); it++)
    it->start();
  while (true) Thread::delay(1000.0f);
}

void RollerCoaster::test () {
  Thread *thread1 = Thread::create(&testthread),
         *thread2 = Thread::create(&testthread);
  Log().line("First thread: "+ptos(thread1));
  thread1->run(static_cast<void*>(this));
  sleep(1);
  Log().line("Second thread: "+ptos(thread2));
  thread2->run(static_cast<void*>(this));
  sleep(2);
  Log().line("Wake up thread");
  monitor_->testB();
  sleep(1);
  monitor_->testB();
} 

void* RollerCoaster::testthread (void* args) {
  static unsigned rank = 1;
  RollerCoaster *rc = static_cast<RollerCoaster*>(args);
  rc->monitor_->testA(rank--);
  Log().line("Thread "+ptos(Thread::self())+" exiting");
  return Thread::exit();
}

} // namespace ep3

