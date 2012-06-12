
#ifndef EP3_MONITOR_H_
#define EP3_MONITOR_H_

#include <semaphore.h>

namespace ep3 {

class Monitor {
  public:
    Monitor ();
  private:
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
};

} // namespace ep3

#endif

