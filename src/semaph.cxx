
#include "semaph.h"

#include <cerrno>
#include "log.h"

namespace ep3 {

Semaph::Semaph (unsigned init_val) {
  if (sem_init(&sem_, 0, init_val))
    Log().warn("Problem initializing semaphore!");
}

Semaph::~Semaph () {
  if (sem_destroy(&sem_))
    Log().warn("Problem destroying semaphore!");
}

void Semaph::wait () {
  int err;
  if ((err = sem_wait(&sem_))) {
    if (err == EINTR)
      Log().warn("Semaphore wait interrupted.");
    else
      Log().warn("Semaphore wait operation failed.");
  }
}

void Semaph::post () {
  if (sem_post(&sem_))
    Log().warn("Semaphore post operation failed.");
}

} // namespace ep3

