
#ifndef EP3_CAR_H_
#define EP3_CAR_H_

#include "thread.h"

namespace ep3 {

class RollerCoasterMonitor;

class Car : public Thread {
  public:
    Car (RollerCoasterMonitor* monitor);
  protected:
    void do_run ();
  private:
    RollerCoasterMonitor  *monitor_;
    unsigned              id_;
    static unsigned       next_id_;
};

} // namespace ep3

#endif

