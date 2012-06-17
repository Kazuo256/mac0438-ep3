
#ifndef EP3_THREAD_H_
#define EP3_THREAD_H_

#include <pthread.h>
#include <string>
#include <list>
#include <utility>

#include "mutex.h"

namespace ep3 {

class Monitor;

class Thread {
  public:
    virtual ~Thread ();
    bool running () const { return running_; }
    virtual std::string info () const;
    void run ();
    static Thread* self ();
    static void delay (float milis);
    static void* exit ();
    static void halt_threads ();
  protected:
    Thread ();
    virtual void do_run () = 0;
  private:
    typedef std::list<Thread*>  List;
    bool                running_;
    pthread_t           thread_;
    std::list<Monitor*> monitors_;
    Mutex               mutex_;
    static List         threads_;
    static Mutex        list_mutex_;
    Thread (const Thread&);
    Thread& operator = (const Thread&);
    static List::iterator get_thread (const pthread_t& t);
    static void* routine (void* args);
    static void cleanup (void* args);
};

} // namespace ep3

#endif

