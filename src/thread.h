
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
    ~Thread ();
    bool running () const { return running_; }
    void run (void *arg);
    void join ();
    void wakeup ();
    bool operator == (const Thread& rhs) const;
    static Thread* create (Routine routine);
    static void exit ();
    static void sleep ();
  private:
    typedef std::list<Thread*> List;
    bool      running_;
    Routine   routine_;
    pthread_t thread_;
    Semaph    *sem_;
    static List threads_;
    Thread (Routine routine);
    Thread (const Thread&);
    Thread& operator = (const Thread&);
    static List::iterator get_thread (const pthread_t& t);
};

} // namespace ep3

#endif

