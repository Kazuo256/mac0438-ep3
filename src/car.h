
#ifndef EP3_CAR_H_
#define EP3_CAR_H_

#include <string>
#include <vector>
#include <set>

#include "thread.h"
#include "mutex.h"

namespace ep3 {

class RollerCoasterMonitor;

// Represents the cars' thread. Its info() method displays only the car ID, but
// the dump_all() static method displays information about all cars, including
// number of passengers aboard, which passengers they are, and whether the car
// is riding the roller coaster right now or not.
class Car : public Thread {
  public:
    Car (RollerCoasterMonitor* monitor);
    // Obvious getter.
    unsigned id () const { return id_; }
    // Overrides Thread::info().
    std::string info () const;
    // For managing which and how many passengers are aboard.
    void add_psg (const Thread* psg);
    void drop_psg (const Thread* psg);
    // Change the state of the car to riding or stopped.
    void ride () { riding_ = true; }
    void stop () { riding_ = false; }
    // Displays information about all cars created.
    static void dump_all ();
    // Returns number of cars created.
    static unsigned num ();
  protected:
    // Implements Thread::do_run().
    void do_run ();
  private:
    RollerCoasterMonitor            *monitor_;
    unsigned                        id_;
    std::set<const Thread*>         psgs_;
    bool                            riding_;
    static unsigned                 next_id_;
    static std::vector<const Car*>  cars_;
};

} // namespace ep3

#endif

