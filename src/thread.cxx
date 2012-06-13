
#include <cstdio>
#include <algorithm>

#include "thread.h"
#include "log.h"

namespace ep3 {

using std::max;

void Thread::run (void *arg) {
  if (!running_) {
    pthread_create(&thread_, NULL, routine_, arg);
    running_ = true;
  } else Log().warn("Attempt to run a currently active thread.");
}

void Thread::join () {
  if (!running_) {
    Log().warn("Attempt to join inactive thread.");
    return;
  }
  if (pthread_join(thread_, NULL))
    Log().warn("Something bad happend.");
}

bool Thread::operator == (const Thread& rhs) const {
  return pthread_equal(thread_, rhs.thread_);
}

void Thread::exit () {
  pthread_exit(NULL);
}

} // namespace ep3

