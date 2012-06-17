
#ifndef EP3_PASSENGER_H_
#define EP3_PASSENGER_H_

#include "thread.h"

namespace ep3 {

class RollerCoasterMonitor;

class Passenger : public Thread {
  public:
    Passenger (RollerCoasterMonitor* monitor);
  protected:
    virtual void do_run ();
  private:
    RollerCoasterMonitor  *monitor_;
    unsigned              id_;
    bool                  golden_ticket_;
    static unsigned       next_id_;
};

} // namespace ep3

#endif

