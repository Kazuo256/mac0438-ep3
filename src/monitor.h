
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
    typedef std::queue<Thread>  CondVar;
    typedef CondVar             RankedCondVar[Thread::RANK_RANGE];
    Monitor ();
    void start_procedure ();
    void end_procedure ();
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
    Mutex mutex_;
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
};

} // namespace ep3

#endif

