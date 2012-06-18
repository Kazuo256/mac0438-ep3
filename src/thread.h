
#ifndef EP3_THREAD_H_
#define EP3_THREAD_H_

#include <pthread.h>
#include <string>
#include <list>
#include <utility>

#include "mutex.h"

namespace ep3 {

class Monitor;

// Represents a thread. It is an abstract class though, you have to inherit it
// and implement the do_run() virtual method. The info() virtual method may
// also be overriden for convenience purposes.
class Thread {
  public:
    virtual ~Thread ();
    // Obvious getter.
    bool running () const { return running_; }
    // Returns a string containing information about the thread. Inherited
    // thread classes may override the information given here.
    virtual std::string info () const;
    // Runs the thread, and returns to the calling thread. These threads are
    // all detached, which means there is no need to join with them later.
    void run ();
    // Returns the current thread. Not very efficient.
    static Thread* self ();
    // Delays the current thread by 'timedelay' time units. A time unit is
    // equivalent to 100 miliseconds.
    static void delay (float timedelay);
    // Exits the current thread. Even the main thread should use this.
    static void* exit ();
    // Stops all current threads except for the main one. The halt is
    // asynchrounous, which means this returns only after all thread have
    // stopped.
    static void halt_threads ();
  protected:
    Thread ();
    // Pure virtual method to be implemented when inheriting from this class.
    // It will be called once when the thread runs. Upon its returning, the
    // thread exits.
    virtual void do_run () = 0;
  private:
    typedef std::list<Thread*>  List;
    bool                running_;
    pthread_t           thread_;
    std::list<Monitor*> monitors_;
    static List         threads_;
    static Mutex        list_mutex_;
    Thread (const Thread&);
    Thread& operator = (const Thread&);
    static List::iterator get_thread (const pthread_t& t);
    static void* routine (void* args);
};

} // namespace ep3

#endif

