
#include "mutex.h"

#include "semaph.h"
#include "log.h"

namespace ep3 {

Mutex::Mutex () :
  mutex_(new Semaph(1)) {}

Mutex::~Mutex () {
  delete mutex_;
}

void Mutex::lock () {
  mutex_->wait();
}

void Mutex::unlock () {
  mutex_->post();
}

Mutex::Lock::Lock (Mutex& mutex) :
  mutex_ref_(mutex) {
  mutex.lock();
}

Mutex::Lock::~Lock () {
  mutex_ref_.unlock();
}

} // namespace ep3

