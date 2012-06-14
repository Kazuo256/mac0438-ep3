
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
  rc_monitor.reset(new RollerCoasterMonitor);
  return true;
}

static void* test (void* arg) {
  rc_monitor->testA();
  Log().line("Thread exiting");
  Thread::exit();
  return NULL; // never reaches here
}

void run () {
  Thread *thread = Thread::create(test);
  thread->run(NULL);
  sleep(2);
  rc_monitor->testB();
}

} // namespace ep3

