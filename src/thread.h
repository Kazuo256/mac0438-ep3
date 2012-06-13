
#ifndef EP3_THREAD_H_
#define EP3_THREAD_H_

#include <pthread.h>
#include <list>
#include <utility>

namespace ep3 {

class Semaph;

class Thread {
  public:
    typedef void* (*Routine) (void*);
    class         Handle;
    bool running () const { return running_; }
    void run (void *arg);
    void join ();
    void wakeup ();
    bool operator == (const Thread& rhs) const;
    static Thread* create (Routine routine);
    static void exit ();
    static void sleep ();
  private:
    typedef std::pair<Thread*, Semaph*> Handle;
    typedef std::list<Handle>           HandleList;
    bool      running_;
    Routine   routine_;
    pthread_t thread_;
    static HandleList handles_;
    Thread (Routine routine) : 
      running_(false), routine_(routine) {}
    Thread (const Thread&);
    Thread& operator = (const Thread&);
    static HandleList::iterator get_handle (const pthread_t& t);
};

} // namespace ep3

#endif

