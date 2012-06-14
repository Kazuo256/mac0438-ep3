
#include "rollercoastermonitor.h"

#include "mutex.h"

namespace ep3 {

void RollerCoasterMonitor::testA () {
  Mutex::Lock lock(mutex_);
  wait(testcv_,0);
}

void RollerCoasterMonitor::testB () {
  Mutex::Lock lock(mutex_);
  signal(testcv_);
}

} // namespace ep3

