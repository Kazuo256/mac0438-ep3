
#include "monitor.h"

#include "semaph.h"

namespace ep3 {

Monitor::Monitor () :
  sem_(new Semaph(1)) {}

Monitor::~Monitor () {
  delete sem_;
}

} // namespace ep3

