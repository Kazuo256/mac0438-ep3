
#ifndef EP3_PASSENGER_H_
#define EP3_PASSENGER_H_

#include <string>
#include "thread.h"

namespace ep3 {

class RollerCoasterMonitor;

class Passenger : public Thread {
  public:
    Passenger (RollerCoasterMonitor* monitor);
    std::string info () const;
    bool golden () const { return golden_ticket_; }
  protected:
    void do_run ();
  private:
    RollerCoasterMonitor  *monitor_;
    unsigned              id_;
    bool                  golden_ticket_;
    unsigned              ride_num_;
    static unsigned       next_id_;
};

} // namespace ep3

#endif

