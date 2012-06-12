
#include "mutex.h"
#include "log.h"

namespace ep3 {

Mutex::Mutex () {
  if (pthread_mutex_init(&mutex_, NULL))
    Log().warn("Mutex may not have been correctly initialized.");
}

Mutex::~Mutex () {
  if (pthread_mutex_destroy(&mutex_))
    Log().warn("Mutex may not have been correctly destroyed.");
}

void Mutex::lock () {
  if (pthread_mutex_lock(&mutex_))
    Log().warn("Mutex lock failed.");
}

void Mutex::try_lock () {
  if (pthread_mutex_trylock(&mutex_))
    Log().warn("Mutesx Busy.");
}

void Mutex::unlock () {
  if (pthread_mutex_unlock(&mutex_))
    Log().warn("Mutex unlock failed.");
}

Mutex::Lock::Lock (Mutex& mutex) :
  mutex_ref_(mutex) {
  mutex.lock();
}

Mutex::Lock::~Lock () {
  mutex_ref_.unlock();
}

} // namespace ep3

