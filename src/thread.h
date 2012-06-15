
#ifndef EP3_THREAD_H_
#define EP3_THREAD_H_

#include <pthread.h>
#include <list>
#include <utility>

#include "mutex.h"

namespace ep3 {

//class Semaph;
class Monitor;

class Thread {
  public:
    typedef void* (*Routine) (void*);
    ~Thread ();
    bool running () const { return running_; }
    void run (void *arg);
    //void join ();
    bool operator == (const Thread& rhs) const;
    static Thread* create (Routine routine);
    template <class T, void (T::*method) (void)>
    static Thread* create ();
    static Thread* self ();
    static void delay (float milis);
    static void* exit ();
    static void halt_threads ();
  private:
    typedef std::list<Thread*>  List;
    bool                running_;
    Routine             routine_;
    pthread_t           thread_;
    std::list<Monitor*> monitors_;
    Mutex               mutex_;
    static List         threads_;
    static Mutex        list_mutex_;
    Thread (Routine routine);
    Thread (const Thread&);
    Thread& operator = (const Thread&);
    static List::iterator get_thread (const pthread_t& t);
    template <class T, void (T::*method) (void)>
    static void* method_thread (void* args);
};

template <class T, void (T::*method) (void)>
inline Thread* Thread::create () {
  return create(&method_thread<T,method>);
}

template <class T, void (T::*method) (void)>
inline void* Thread::method_thread (void* args) {
  T *obj = static_cast<T*>(args);
  (obj->*method) ();
  return Thread::exit();
}

} // namespace ep3

#endif

