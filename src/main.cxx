
#include <cstdlib>
#include <cstdio>

#include "ep3.h"

int main (int argc, char** argv) {
  if (!ep3::init(argc, argv)) {
    puts("Failed to initialize program. Exiting.");
    return EXIT_FAILURE;
  }
  ep3::run();
  return EXIT_SUCCESS;
}

