
#include "ep3.h"

#include <memory>

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::string;
using std::auto_ptr;

static auto_ptr<RollerCoasterMonitor> rc_monitor;

static void help (const string& progname) {
  Log()
    .line("Usage:")
    .line("\t"+progname+" [-d] [-w] <t> <m> <C>")
    .line("See LEIAME for more information.");
}

bool init (int argc, char** argv) {
  string progname = *argv++;
  argc--;
  while (argc > 0 && (*argv)[0] == '-') {
    switch((*argv)[1]) {
      case 'd':
        Log::enable_debug();
        break;
      case 'w':
        Log::enable_warning();
        break;
      default:
        Log().line(progname+": Invalid option -- '"+(*argv+1)+"'.");
        help(progname);
        return false;
    }
    argv++;
    argc--;
  }
  if (argc < 3) {
    Log().line(progname+": Missing parameters.");
    help(progname);
    return false;
  }
  if (Log::debug_on)    Log().debug("Debug logging activated.");
  if (Log::warning_on)  Log().warn("Warning logging activated.");
  rc_monitor.reset(new RollerCoasterMonitor);
  return true;
}

static void* test (void* arg) {
  static unsigned rank = 1;
  rc_monitor->testA(rank--);
  Log().line("Thread "+ptos(Thread::self())+" exiting");
  return Thread::exit();
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

