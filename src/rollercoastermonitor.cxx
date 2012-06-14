
#include "rollercoastermonitor.h"

#include "mutex.h"

namespace ep3 {

void RollerCoasterMonitor::testA (Rank rank) {
  Mutex::Lock lock(mutex_);
  wait(testcv_, rank);
}

void RollerCoasterMonitor::testB () {
  Mutex::Lock lock(mutex_);
  signal(testcv_);
}

} // namespace ep3

