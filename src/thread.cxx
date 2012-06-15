
#include "thread.h"

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "semaph.h"
#include "monitor.h"
#include "log.h"

namespace ep3 {

using std::max;
using std::list;

Thread::List  Thread::threads_;
Mutex         Thread::list_mutex_;

Thread::Thread (Routine routine) : 
  running_(false), routine_(routine) {}

Thread::~Thread () {
  list<Monitor*>::iterator it;
  for (it = monitors_.begin(); it != monitors_.end(); it++)
    (*it)->drop(this);
}

void Thread::run (void *arg) {
  if (!running_) {
    Mutex::Lock lock(mutex_);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    running_ = true;
    if (pthread_create(&thread_, &attr, routine_, arg)) {
      running_ = false;
    }
  } else Log().warn("Attempt to run a currently active thread.");
}

//void Thread::join () {
//  if (!running_) {
//    Log().warn("Attempt to join inactive thread.");
//    return;
//  }
//  if (pthread_join(thread_, NULL))
//    Log().warn("Something bad happend.");
//}

bool Thread::operator == (const Thread& rhs) const {
  return pthread_equal(thread_, rhs.thread_);
}

Thread* Thread::create (Routine routine) {
  Thread *thread = new Thread(routine);
  {
    Mutex::Lock lock(list_mutex_);
    threads_.push_back(thread);
  }
  return thread;
}

Thread* Thread::self () {
  Mutex::Lock lock(list_mutex_);
  List::iterator it = get_thread(pthread_self());
  if (it != threads_.end())
    return *it;
  else return NULL;
}

void Thread::delay (float milis) {
  struct timespec t;
  t.tv_sec = static_cast<time_t>(milis/1000.0f);
  t.tv_nsec = static_cast<long>(1e6f*fmod(milis, 1000.0f));
  nanosleep(&t, NULL);
}

void* Thread::exit () {
  Thread *thread = NULL;
  {
    Mutex::Lock lock(list_mutex_);
    List::iterator hit = get_thread(pthread_self());
    if (hit != threads_.end()) {
      thread = *hit;
      delete *hit;
      threads_.erase(hit);
    }
  }
  Log().debug("Exiting thread "+ptos(thread)+".");
  pthread_exit(NULL);
  return NULL; // never reaches here
}

void Thread::halt_threads () {
  Mutex::Lock lock(list_mutex_);
  List::iterator it;
  for (it = threads_.begin(); it != threads_.end(); it++) {
    Log().debug("Canceling thread "+ptos(static_cast<void*>(&*it))+".");
    pthread_cancel((*it)->thread_);
    delete *it;
  }
  threads_.clear();
}

Thread::List::iterator Thread::get_thread (const pthread_t& t) {
  List::iterator it;
  for (it = threads_.begin(); it != threads_.end(); it++)
    if (pthread_equal((*it)->thread_, t)) break;
  return it;
}

} // namespace ep3

