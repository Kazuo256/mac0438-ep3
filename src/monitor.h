
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
    // Locks itself, so DO NOT lock the monitor before calling.
    void drop (Thread* thread);
  protected:
    typedef unsigned char       Rank;
    typedef std::queue<Thread*> CondVar;
    class                       RankedCondVar;
    Mutex mutex_;
    Monitor () {}
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
    static SemMap monitoring_map_;
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
    Semaph* get_semaph (Thread* thread);
};

class Monitor::RankedCondVar {
  public:
    RankedCondVar (Rank range) :
      ranks(range, CondVar()),
      minrank(range) {}
    //CondVar& firstrank () { return rank[mninrank]; }
    bool empty () const;
    Thread* front () const;
    void push (Thread *thread, Rank rank);
    void pop ();
  private:
    std::vector<CondVar>  ranks;
    Rank                  minrank;
};

} // namespace ep3

#endif

