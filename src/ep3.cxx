
#include "ep3.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

bool init (int argc, char** argv) {
  Log::enable_warning();
  return true;
}

static void* test (void* arg) {
  Log().line("Thread exiting");
  Thread::exit();
  return NULL; // never reaches here
}

void run () {
  Thread *thread = Thread::create(test);
  thread->run(NULL);
}

} // namespace ep3

