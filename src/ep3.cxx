
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
  rc_monitor->testA(1);
  Log().line("Thread exiting");
  Thread::exit();
  return NULL; // never reaches here
}

void run () {
  Thread *thread1 = Thread::create(test),
         *thread2 = Thread::create(test);
  Log().line("First thread.");
  thread1->run(NULL);
  sleep(1);
  Log().line("Second thread.");
  thread2->run(NULL);
  sleep(5);
  Log().line("Wake up thread");
  rc_monitor->testB();
  rc_monitor->testB();
}

} // namespace ep3

