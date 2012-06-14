
#include "ep3.h"

#include <memory>

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::auto_ptr;

static auto_ptr<RollerCoasterMonitor> rc_monitor;

bool init (int argc, char** argv) {
  Log::enable_warning();
  Log::enable_debug();
  rc_monitor.reset(new RollerCoasterMonitor);
  return true;
}

static void* test (void* arg) {
  static unsigned rank = 1;
  rc_monitor->testA(rank--);
  Log().line("Thread "+ptos(Thread::self())+" exiting");
  Thread::exit();
  return NULL; // never reaches here
}

void run () {
  Thread *thread1 = Thread::create(test),
         *thread2 = Thread::create(test);
  Log().line("First thread: "+ptos(thread1));
  thread1->run(NULL);
  sleep(1);
  Log().line("Second thread: "+ptos(thread2));
  thread2->run(NULL);
  sleep(2);
  Log().line("Wake up thread");
  rc_monitor->testB();
  sleep(1);
  rc_monitor->testB();
}

} // namespace ep3

