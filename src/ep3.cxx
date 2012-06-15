
#include "ep3.h"

#include <cstdlib>
#include <memory>

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::string;
using std::auto_ptr;

// Smart pointer to the roller coaster monitor. Automatically deletes the
// monitor at the end of the program.
static auto_ptr<RollerCoasterMonitor> rc_monitor(NULL);
// Passenger creation rate.
static float                          psg_rate = 0.01f;

static void help (const string& progname) {
  Log()
    .line("Usage:")
    .line("\t"+progname+" [-d] [-w] <t> <m> <C>")
    .line("See LEIAME for more information.");
}

bool init (int argc, char** argv) {
  // Get program name.
  string progname = *argv++;
  argc--;
  // Read optional parameters.
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
  // Check if there are enough required parameters.
  if (argc < 3) {
    Log().line(progname+": Missing parameters.");
    help(progname);
    return false;
  }
  // Read parameter values.
  psg_rate = atof(argv[0]);
  int car_num = atoi(argv[1]),
      car_cap = atoi(argv[2]);
  // Verify parameter values.
  if (psg_rate <= 0.0f) {
    Log().line(progname+": The first parameter (passenger creation rate), must "
               "be a non-zero positive floating-point number.");
    return false;
  }
  if (car_num <= 0) {
    Log().line(progname+": The second parameter (number of roller coaster cars)"
               ", must be a positive integer number greater or equal to 1.");
    return false;
  }
  if (car_cap <= 0) {
    Log().line(progname+": The third parameter (roller coaster car capacity), "
               "must be a positive integer number greater or equal to 1.");
    return false;
  }
  // Parameters checked, prepare simulation.
  rc_monitor.reset(
    new RollerCoasterMonitor(
      static_cast<unsigned>(car_num),
      static_cast<unsigned>(car_cap)
    )
  );
  // Everything ok, print some info and return success.
  if (Log::debug_on())    Log().debug("Debug logging activated.");
  if (Log::warning_on())  Log().warn("Warning logging activated.");
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

