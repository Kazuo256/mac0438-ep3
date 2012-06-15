
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
    class                       CondVar;
    Mutex mutex_;
    Monitor () {}
    virtual ~Monitor ();
    // Basic monitor operations. MUST be called with the monitor locked.
    bool empty (const CondVar& cv) const;
    void wait (CondVar& cv, Rank rank = MAXRANK);
    void signal (CondVar& cv);
    void signal_all (CondVar& cv);
    Rank minrank (const CondVar& cv) const;
    static const Rank MAXRANK = static_cast<Rank>(-1);
  private:
    typedef std::map<Thread*, Semaph*> SemMap;
    static SemMap monitoring_map_;
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
    Semaph* get_semaph (Thread* thread);
};

class Monitor::CondVar {
  public:
    CondVar (Rank range = 1u) :
      ranks_(range, std::queue<Thread*>()),
      minrank_(range) {}
    //CondVar& firstrank () { return rank[mninrank]; }
    bool empty () const;
    Thread* front () const;
    Rank minrank () const { return minrank_; }
    void push (Thread *thread, Rank rank = 0);
    void pop ();
  private:
    std::vector< std::queue<Thread*> >  ranks_;
    Rank                                minrank_;
};

} // namespace ep3

#endif

