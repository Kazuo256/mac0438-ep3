
#include "monitor.h"

#include <algorithm>

#include "log.h"
#include "semaph.h"

namespace ep3 {

using std::map;
using std::min;

Monitor::SemMap Monitor::monitoring_map_;

Monitor::~Monitor () {
  SemMap::iterator it;
  for (it = monitoring_map_.begin(); it != monitoring_map_.end(); it++) {
    Log().debug("Droping thread "+ptos(static_cast<void*>(it->first))+".");
    delete it->second;
  }
}

void Monitor::drop (Thread* thread) {
  Mutex::Lock lock(mutex_);
  Log().debug("Droping thread "+ptos(static_cast<void*>(thread))+".");
  SemMap::iterator it = monitoring_map_.find(thread);
  if (it != monitoring_map_.end()) {
    delete it->second;
    monitoring_map_.erase(it);
  }
}

//===//

bool Monitor::empty (const CondVar& cv) const {
  return cv.empty();
}

void Monitor::wait (CondVar& cv, Rank rank) {
  Thread *self = Thread::self();
  cv.push(self, rank);
  mutex_.unlock();
  get_semaph(self)->wait();
  mutex_.lock();
}

void Monitor::signal (CondVar& cv) {
  if (!empty(cv)) {
    Thread *thread = cv.front();
    cv.pop();
    get_semaph(thread)->post();
  }
}

void Monitor::signal_all (CondVar& cv) {
  while (!empty(cv))
    signal(cv);
}

Semaph* Monitor::get_semaph (Thread* thread) {
  SemMap::iterator it = monitoring_map_.find(thread);
  if (it != monitoring_map_.end())
    return it->second;
  else {
    return (monitoring_map_[thread] = new Semaph(0));
  }
}

Monitor::Rank Monitor::minrank (const CondVar& cv) const {
  return cv.minrank();
}

bool Monitor::CondVar::empty () const {
  return minrank_ >= ranks_.size();
}

Thread* Monitor::CondVar::front () const {
  return ranks_[minrank_].front();
}

void Monitor::CondVar::push (Thread *thread, Rank rank) {
  rank = min(rank, static_cast<Rank>(ranks_.size()-1));
  ranks_[rank].push(thread);
  minrank_ = min(minrank_, rank);
}

void Monitor::CondVar::pop () {
  ranks_[minrank_].pop();
  while (minrank_ < ranks_.size() && ranks_[minrank_].empty())
    minrank_++;
    //Log().debug("Up rank "+utos(++minrank_));
}

} // namespace ep3

