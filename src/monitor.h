
#ifndef EP3_MONITOR_H_
#define EP3_MONITOR_H_

#include <vector>
#include <queue>
#include <map>

#include "thread.h"
#include "mutex.h"

namespace ep3 {

class Semaph;

class Monitor {
  public:
    void drop (Thread* thread);
  protected:
    typedef unsigned char       Rank;
    typedef std::queue<Thread*> CondVar;
    struct RankedCondVar;
    Mutex mutex_;
    Monitor (Rank range);
    virtual ~Monitor ();
    // Basic monitor operations. MUST be called with the monitor locked.
    bool empty (const CondVar& cv) const;
    bool empty (const RankedCondVar& cv) const;
    void wait (CondVar& cv);
    void wait (RankedCondVar& cv, Rank rank = MAXRANK);
    void signal (CondVar& cv);
    void signal (RankedCondVar& cv);
    void signal_all (CondVar& cv);
    void signal_all (RankedCondVar& cv);
    Rank minrank (const RankedCondVar& cv) const;
    static const Rank MAXRANK = static_cast<Rank>(-1);
  private:
    typedef std::map<Thread*, Semaph*> SemMap;
    const Rank    range_;
    static SemMap monitoring_map_;
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
    Semaph* get_semaph (Thread* thread);
};

struct Monitor::RankedCondVar {
  std::vector<CondVar>  rank;
  Rank                  minrank;
  RankedCondVar (Rank range) :
    rank(range, CondVar()),
    minrank(range) {}
  //CondVar& firstrank () { return rank[mninrank]; }
};

} // namespace ep3

#endif

