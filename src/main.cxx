
#include <cstdlib>
#include <cstdio>

#include "ep3.h"
#include "log.h"
#include "thread.h"

using ep3::Log;
using ep3::Thread;

int main (int argc, char** argv) {
  if (!ep3::init(argc, argv)) {
    Log().out("Failed to initialize program. Exiting.");
  } else ep3::run();
  Thread::exit();
  // never reaches here
  return EXIT_FAILURE;
}

