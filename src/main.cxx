
#include <cstdlib>
#include <cstdio>

#include "ep3.h"
#include "log.h"
#include "thread.h"

using ep3::Log;
using ep3::Thread;

int main (int argc, char** argv) {
  // Read command line parameters.
  if (!ep3::init(argc, argv)) {
    Log().line("Failed to initialize program. Exiting.");
  } else ep3::run(); // Run program upon sucess.
  Thread::exit();
  // Never reaches here
  return EXIT_FAILURE;
}

