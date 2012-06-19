
#ifndef EP3_PASSENGER_H_
#define EP3_PASSENGER_H_

#include <string>
#include "thread.h"

namespace ep3 {

class RollerCoasterMonitor;
class Car;

// Reresents the passengers' thread. Its info() method displays the passenger's
// ID. Passengers have a 25% chance of being created bearing a golden ticket.
class Passenger : public Thread {
  public:
    Passenger (RollerCoasterMonitor* monitor);
    // Overrides Thread::info().
    std::string info () const;
    // Returns whether the passenger has a golden ticket or not.
    bool golden () const { return golden_ticket_; }
    //
    const Car* current_car () const { return current_car_; }
    void set_current_car (const Car* car) { current_car_ = car; }
  protected:
    // Implements Thread::do_run();
    void do_run ();
  private:
    RollerCoasterMonitor  *monitor_;
    unsigned              id_;
    bool                  golden_ticket_;
    unsigned              ride_num_;
    const Car             *current_car_;
    static unsigned       next_id_;
};

} // namespace ep3

#endif

