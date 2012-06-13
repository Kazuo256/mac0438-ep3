
#include <cstdio>
#include <cstring>
#include <algorithm>

#include "thread.h"
#include "semaph.h"
#include "log.h"

namespace ep3 {

using std::max;

Thread::List Thread::threads_;

Thread::Thread (Routine routine) : 
  running_(false), routine_(routine), sem_(new Semaph(0)) {}

Thread::~Thread () {
  delete sem_;
}

void Thread::run (void *arg) {
  if (!running_) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_, &attr, routine_, arg);
    running_ = true;
  } else Log().warn("Attempt to run a currently active thread.");
}

void Thread::join () {
  if (!running_) {
    Log().warn("Attempt to join inactive thread.");
    return;
  }
  if (pthread_join(thread_, NULL))
    Log().warn("Something bad happend.");
}

void Thread::wakeup () {
  sem_->post();
}

bool Thread::operator == (const Thread& rhs) const {
  return pthread_equal(thread_, rhs.thread_);
}

Thread* Thread::create (Routine routine) {
  Thread *thread = new Thread(routine);
  threads_.push_back(thread);
  return thread;
}

void Thread::exit () {
  List::iterator hit = get_thread(pthread_self());
  if (hit != threads_.end()) {
    delete *hit;
    threads_.erase(hit);
  }
  pthread_exit(NULL);
}

void Thread::sleep () {
  List::iterator hit = get_thread(pthread_self());
  if (hit != threads_.end())
    (*hit)->sem_->wait();
  else
    Log().warn("Tried to sleep main thread or invalid thread.");
}

Thread::List::iterator Thread::get_thread (const pthread_t& t) {
  List::iterator it;
  for (it = threads_.begin(); it != threads_.end(); it++)
    if (pthread_equal((*it)->thread_, t)) break;
  return it;
}

} // namespace ep3

