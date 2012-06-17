
#ifndef EP3_CAR_H_
#define EP3_CAR_H_

#include <string>
#include <vector>
#include <list>

#include "thread.h"
#include "mutex.h"

namespace ep3 {

class RollerCoasterMonitor;

class Car : public Thread {
  public:
    Car (RollerCoasterMonitor* monitor);
    std::string info () const;
    unsigned id () const { return id_; }
    void add_psg (const Thread* psg);
    void drop_psg ();
    static void dump_all ();
    static unsigned num ();
  protected:
    void do_run ();
  private:
    RollerCoasterMonitor            *monitor_;
    unsigned                        id_;
    std::list<const Thread*>        psgs_;
    static unsigned                 next_id_;
    static std::vector<const Car*>  cars_;
};

} // namespace ep3

#endif

