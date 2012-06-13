
#ifndef EP3_MONITOR_H_
#define EP3_MONITOR_H_

#include <vector>

#include "mutex.h"

namespace ep3 {

class Semaph;

class Monitor {
  public:
    typedef unsigned char Rank;
    static const Rank     MAXRANK = -1;
  protected:
    typedef int           CondVar; // TODO
    Monitor ();
    void start_procedure ();
    void end_procedure ();
    bool empty (const CondVar& cv) const;
    void wait (CondVar& cv, Rank rank = MAXRANK);
    void signal (CondVar& cv);
    void signal_all (CondVar& cv);
    Rank minrank (const CondVar& cv) const;
  private:
    Mutex mutex_;
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
};

} // namespace ep3

#endif

