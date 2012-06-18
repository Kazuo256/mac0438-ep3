
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

using std::string;
using std::list;
using std::max;

Thread::List  Thread::threads_;
Mutex         Thread::list_mutex_;

Thread::Thread () : 
  running_(false) {
  Mutex::Lock lock(list_mutex_);
  threads_.push_back(this);
}

Thread::~Thread () {
  list<Monitor*>::iterator it;
  for (it = monitors_.begin(); it != monitors_.end(); it++)
    (*it)->drop(this);
}

string Thread::info () const {
  // Default information given.
  return "<"+ptos(static_cast<const void*>(this))+">";
}

void Thread::run () {
  if (!running_) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    running_ = true;
    if (pthread_create(&thread_, &attr, routine, static_cast<void*>(this))) {
      running_ = false;
    }
  } else Log().warn("Attempt to run a currently active thread.");
}

Thread* Thread::self () {
  Mutex::Lock lock(list_mutex_);
  List::iterator it = get_thread(pthread_self());
  if (it != threads_.end())
    return *it;
  else return NULL;
}

void Thread::delay (float timedelay) {
  struct timespec t;
  t.tv_sec = static_cast<time_t>(timedelay/10.0f);
  t.tv_nsec = static_cast<long>(1e8f*fmod(timedelay, 10.0f));
  nanosleep(&t, NULL);
}

void* Thread::exit () {
  Thread *thread = NULL;
  std::string thread_info;
  {
    Mutex::Lock lock(list_mutex_);
    List::iterator hit = get_thread(pthread_self());
    if (hit != threads_.end()) {
      thread = *hit;
      thread_info = (*hit)->info();
      delete *hit;
      threads_.erase(hit);
    }
  }
  if (!thread_info.size())
    thread_info = ptos(thread);
  Log().debug("Exiting thread "+thread_info+".");
  pthread_exit(NULL);
  return NULL; // never reaches here
}

void Thread::halt_threads () {
  Mutex::Lock lock(list_mutex_);
  List::iterator it;
  for (it = threads_.begin(); it != threads_.end(); it++) {
    Log().debug("Canceling thread "+(*it)->info()+".");
    pthread_cancel((*it)->thread_);
  }
  for (it = threads_.begin(); it != threads_.end(); it++) {
    Log().debug("Deleting thread "+(*it)->info()+".");
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

void* Thread::routine (void* args) {
  Thread *self = static_cast<Thread*>(args);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  self->do_run();
  return Thread::exit();
}

} // namespace ep3

