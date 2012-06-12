
#include <cstdlib>
#include <cstdio>

#include "ep3.h"
#include "log.h"

using ep3::Log;

int main (int argc, char** argv) {
  if (!ep3::init(argc, argv)) {
    Log().out("Failed to initialize program. Exiting.");
    return EXIT_FAILURE;
  }
  ep3::run();
  return EXIT_SUCCESS;
}

