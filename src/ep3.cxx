
#include "ep3.h"

#include <cstdlib>
#include <memory>

#include "rollercoaster.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::string;
using std::auto_ptr;

// Smart pointer to the roller coaster. Automatically deletes the monitor at the
// end of the program.
static auto_ptr<RollerCoaster>  rollercoaster(NULL);
// Passenger creation rate.
static float                    psg_rate = 0.01f;

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
  rollercoaster.reset(
    new RollerCoaster(
      static_cast<unsigned>(car_num),
      static_cast<unsigned>(car_cap)
    )
  );
  // Everything ok, print some info and return success.
  if (Log::debug_on())    Log().debug("Debug logging activated.");
  if (Log::warning_on())  Log().warn("Warning logging activated.");
  return true;
}

#include <signal.h>

static void handle (int sig) {
  Log().line("Interruption signal captured!");
  Thread::halt_threads();
  Thread::exit();
}

void run () {
  signal(SIGINT, handle);
  rollercoaster->open();
  //rollercoaster->test();
  rollercoaster->run();
}

} // namespace ep3

