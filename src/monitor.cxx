
#include "monitor.h"

#include "semaph.h"

namespace ep3 {

using std::map;

Monitor::SemMap Monitor::monitoring_map_;

Monitor::Monitor (Rank range) :
 range_(range) {}

Monitor::~Monitor () {
  SemMap::iterator it;
  for (it = monitoring_map_.begin(); it != monitoring_map_.end(); it++)
    delete it->second;
}

void Monitor::drop (Thread* thread) {
  Mutex::Lock lock(mutex_);
  SemMap::iterator it = monitoring_map_.find(thread);
  if (it != monitoring_map_.end()) {
    delete it->second;
    monitoring_map_.erase(it);
  }
}

bool Monitor::empty (const CondVar& cv) const {
  return cv.empty();
}

bool Monitor::empty (const RankedCondVar& cv) const {
  return cv.minrank > range_;
}

void Monitor::wait (CondVar& cv) {
  //Thread::ID tid = Thread::self();
  //cv.push(t);
  //mutex_.unlock();
}

Semaph* Monitor::get_semaph (Thread* thread) {
  SemMap::iterator it = monitoring_map_.find(thread);
  if (it != monitoring_map_.end())
    return it->second;
  else {
    return (monitoring_map_[thread] = new Semaph(0));
  }
}

} // namespace ep3

