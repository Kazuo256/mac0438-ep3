
#ifndef EP3_MONITOR_H_
#define EP3_MONITOR_H_

#include <vector>
#include <queue>

#include "thread.h"
#include "mutex.h"

namespace ep3 {

class Semaph;

class Monitor {
  public:
  protected:
    typedef std::queue<Thread> CondVar;
    struct RankedCondVar;
    Mutex mutex_;
    Monitor ();
    // Basic monitor operations. MUST be called with the monitor locked.
    bool empty (const CondVar& cv) const;
    bool empty (const RankedCondVar& cv) const;
    void wait (CondVar& cv);
    void wait (RankedCondVar& cv, Thread::Rank rank = Thread::MAX_RANK);
    void signal (CondVar& cv);
    void signal (RankedCondVar& cv);
    void signal_all (CondVar& cv);
    void signal_all (RankedCondVar& cv);
    Thread::Rank minrank (const RankedCondVar& cv) const;
  private:
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
};

struct Monitor::RankedCondVar {
  CondVar       rank[Thread::RANK_RANGE];
  Thread::Rank  minrank;
  RankedCondVar () : minrank(Thread::MAX_RANK+1) {}
  //CondVar& firstrank () { return rank[mninrank]; }
};

} // namespace ep3

#endif

