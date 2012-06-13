
#include "monitor.h"

#include "semaph.h"

namespace ep3 {

Monitor::Monitor () {}

bool Monitor::empty (const CondVar& cv) const {
  return cv.empty();
}

bool Monitor::empty (const RankedCondVar& cv) const {
  return cv.minrank > Thread::MAX_RANK;
}

void Monitor::wait (CondVar& cv) {
  //Thread::ID tid = Thread::self();
  //cv.push(t);
  //mutex_.unlock();
}

} // namespace ep3

