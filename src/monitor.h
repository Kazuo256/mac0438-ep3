
#ifndef EP3_MONITOR_H_
#define EP3_MONITOR_H_

#include <vector>
#include <list>
#include <map>

#include "thread.h"
#include "mutex.h"

namespace ep3 {

class Semaph;

// Base class for monitors. Provides the basic operations such as wait(cv) and
// signal(cv). It is important to note that when inheriting this class to
// implement a monitor, the defined public operations must all grant mutual
// exclusion from all threads. In order to achieve this, the line
//
//    Mutex::Lock lock(mutex_);
//
// must be added to the first line of EVERY public method from the child
// classes. The basic protected operations all assume they are called whithin
// critical regions.
// On the other hand, public operations in the class Monitor lock themselves, so
// no need to lock before calling them. Actually, DO NOT lock before calling
// them.
class Monitor {
  public:
    // These two methods lock themselvels, so DO NOT lock the monitor before
    // calling.
    void drop (Thread* thread);
    // This one is needed to avoid some race conditions when threads exit.
    // Threads SHOULD ONLY GIVE THEMSELVES AS ARGUMENTS TO THIS FUNCTION.
    void safe_exit (Thread* thread);
  protected:
    typedef unsigned char       Rank;
    class                       CondVar; // forward declaration, see below
    Mutex mutex_;
    Monitor () {}
    virtual ~Monitor ();
    // These are all basic monitor operations. MUST be called with the monitor
    // locked.
    bool empty (const CondVar& cv) const;
    void wait (CondVar& cv, Rank rank = MAXRANK);
    void signal (CondVar& cv);
    void signal_all (CondVar& cv);
    Rank minrank (const CondVar& cv) const;
    Thread* signal_and_fetch (CondVar& cv);
    unsigned count (const CondVar& cv) const;
    void dump (const CondVar& cv) const;
    // Maximum possible rank.
    static const Rank MAXRANK = static_cast<Rank>(-1);
  private:
    typedef std::map<Thread*, Semaph*> SemMap;
    // This map indicates the semaphores reserved to each thread that uses the
    // monitor.
    static SemMap monitoring_map_;
    // Monitor objects are uncopiable. Use pointers.
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
    // Returns the semaphore reserved to the given thread.
    Semaph* get_semaph (Thread* thread);
};

// This class represent a condition variable. Since they support priorities,
// they ended up being more than just a simple queue. They are vectors of
// queues, one for each priority. Upon creation, the condition variable is given
// (through its constructor) the desired range of priorities needed.
// The idea of using a queue for each priority was also used once by the Linux
// kernel when scheduling processes.
class Monitor::CondVar {
  public:
    CondVar (Rank range = 1u) :
      ranks_(range, std::list<Thread*>()),
      minrank_(range) {}
    bool empty () const;
    Thread* front () const;
    Rank minrank () const { return minrank_; }
    void push (Thread *thread, Rank rank = 0);
    void pop ();
    size_t size () const;
    void dump () const;
  private:
    std::vector< std::list<Thread*> > ranks_;
    Rank                              minrank_;
};

} // namespace ep3

#endif

