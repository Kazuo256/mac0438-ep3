
#include "rollercoaster.h"

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

RollerCoaster::RollerCoaster (unsigned car_num, unsigned car_cap) :
  monitor_(new RollerCoasterMonitor) {

}

RollerCoaster::~RollerCoaster () {
  delete monitor_;
}

void* RollerCoaster::testthread (void* args) {
  static unsigned rank = 1;
  RollerCoaster *rc = static_cast<RollerCoaster*>(args);
  rc->monitor_->testA(rank--);
  Log().line("Thread "+ptos(Thread::self())+" exiting");
  return Thread::exit();
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

} // namespace ep3

