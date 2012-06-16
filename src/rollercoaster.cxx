
#include "rollercoaster.h"

#include <cstdlib>
#include <ctime>
#include <vector>

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"
#include "car.h"
#include "passenger.h"

namespace ep3 {

using std::vector;

RollerCoaster::RollerCoaster (float psg_rate,
                              unsigned car_num,
                              unsigned car_cap) :
  monitor_(new RollerCoasterMonitor(car_cap)),
  psg_delay_(1.0f/psg_rate),
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
  while (true)  {
    psgs_.push_back(Passenger(monitor_));
    psgs_.back().start();
    Thread::delay(psg_delay_);
  }
}

//void RollerCoaster::test () {
//  Thread *thread1 = Thread::create(&testthread),
//         *thread2 = Thread::create(&testthread);
//  Log().line("First thread: "+ptos(thread1));
//  thread1->run(static_cast<void*>(this));
//  sleep(1);
//  Log().line("Second thread: "+ptos(thread2));
//  thread2->run(static_cast<void*>(this));
//  sleep(2);
//  Log().line("Wake up thread");
//  monitor_->testB();
//  sleep(1);
//  monitor_->testB();
//} 
//
//void* RollerCoaster::testthread (void* args) {
//  static unsigned rank = 1;
//  RollerCoaster *rc = static_cast<RollerCoaster*>(args);
//  rc->monitor_->testA(rank--);
//  Log().line("Thread "+ptos(Thread::self())+" exiting");
//  return Thread::exit();
//}

} // namespace ep3

