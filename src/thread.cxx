
#include <cstdio>
#include <cstring>
#include <algorithm>

#include "thread.h"
#include "semaph.h"
#include "log.h"

namespace ep3 {

using std::max;

Thread::HandleList Thread::handles_;

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
  HandleList::iterator hit = get_handle(thread_);
  if (hit != handles_.end())
    hit->second->post();
  else
    Log().warn("Tried to wake up invalid thread.");
}

bool Thread::operator == (const Thread& rhs) const {
  return pthread_equal(thread_, rhs.thread_);
}

Thread* Thread::create (Routine routine) {
  Handle handle = Handle(new Thread(routine), new Semaph(0));
  handles_.push_back(handle);
  return handle.first;
}

void Thread::exit () {
  HandleList::iterator hit = get_handle(pthread_self());
  if (hit != handles_.end()) {
    delete hit->first;
    delete hit->second;
    handles_.erase(hit);
  }
  pthread_exit(NULL);
}

void Thread::sleep () {
  HandleList::iterator hit = get_handle(pthread_self());
  if (hit != handles_.end())
    hit->second->wait();
  else
    Log().warn("Tried to sleep main thread or invalid thread.");
}

Thread::HandleList::iterator Thread::get_handle (const pthread_t& t) {
  HandleList::iterator it;
  for (it = handles_.begin(); it != handles_.end(); it++)
    if (pthread_equal(it->first->thread_, t)) break;
  return it;
}

} // namespace ep3

