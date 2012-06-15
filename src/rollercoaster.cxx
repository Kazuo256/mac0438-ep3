
#include "rollercoaster.h"

#include <time.h>
#include <cmath>
#include <vector>

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::vector;

RollerCoaster::RollerCoaster (unsigned car_num, unsigned car_cap) :
  monitor_(new RollerCoasterMonitor),
  car_num_(car_num) {

}

RollerCoaster::~RollerCoaster () {
  Log().debug("Cleaning roller coaster resources...");
  delete monitor_;
}

struct ThreadArgs {
  unsigned      id;
  RollerCoaster *rc;
};

static vector<ThreadArgs> cars;

void RollerCoaster::open () {
  for (unsigned i = 0; i < car_num_; i++) {
    ThreadArgs car;
    car.id = i;
    car.rc = this;
    cars.push_back(car);
  }
}

static void delay (float milis) {
  struct timespec t;
  t.tv_sec = static_cast<time_t>(milis/1000.0f);
  t.tv_nsec = static_cast<long>(1e6f*fmod(milis, 1000.0f));
  nanosleep(&t, NULL);
}

void RollerCoaster::run () {
  Log().line("== Starting roller coaster ==");
  vector<ThreadArgs>::iterator it;
  for (it = cars.begin(); it < cars.end(); it++) {
    Thread *thread = Thread::create(&car_thread);
    thread->run(static_cast<void*>(&*it));
  }
  while (true) delay(1000.0f);
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

void* RollerCoaster::car_thread (void* args) {
  ThreadArgs *targs = static_cast<ThreadArgs*>(args);
  while (true) {
    targs->rc->monitor_->start_lap(targs->id);
    sleep(1);
    targs->rc->monitor_->finish_lap(targs->id);
  }
  return Thread::exit();
}

void* RollerCoaster::testthread (void* args) {
  static unsigned rank = 1;
  RollerCoaster *rc = static_cast<RollerCoaster*>(args);
  rc->monitor_->testA(rank--);
  Log().line("Thread "+ptos(Thread::self())+" exiting");
  return Thread::exit();
}

} // namespace ep3

