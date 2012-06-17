
#ifndef EP3_CAR_H_
#define EP3_CAR_H_

#include <string>
#include "thread.h"

namespace ep3 {

class RollerCoasterMonitor;

class Car : public Thread {
  public:
    Car (RollerCoasterMonitor* monitor);
    std::string info () const;
    unsigned id () const { return id_; }
  protected:
    void do_run ();
  private:
    RollerCoasterMonitor  *monitor_;
    unsigned              id_;
    static unsigned       next_id_;
};

} // namespace ep3

#endif

