
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

//===//

bool Monitor::empty (const CondVar& cv) const {
  return cv.empty();
}

bool Monitor::empty (const RankedCondVar& cv) const {
  return cv.empty();
}

void Monitor::wait (CondVar& cv) {
  Thread *self = Thread::self();
  cv.push(self);
  mutex_.unlock();
  get_semaph(self)->wait();
  mutex_.lock();
}

void Monitor::wait (RankedCondVar& cv, Rank rank) {
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

void Monitor::signal (RankedCondVar& cv) {
  if (!empty(cv)) {
    Thread *thread = cv.front();
    cv.pop();
    get_semaph(thread)->post();
  }
}

bool Monitor::RankedCondVar::empty () const {
  return minrank >= ranks.size();
}

Thread* Monitor::RankedCondVar::front () const {
  return ranks[minrank].front();
}

void Monitor::RankedCondVar::push (Thread *thread, Rank rank) {
  rank = min(rank, static_cast<Rank>(ranks.size()-1));
  Log().debug("Pushed rank "+utos(rank));
  ranks[rank].push(thread);
  minrank = min(minrank, rank);
  Log().debug("New minrank "+utos(minrank));
}

void Monitor::RankedCondVar::pop () {
  ranks[minrank].pop();
  while (minrank < ranks.size() && ranks[minrank].size())
    Log().debug("Up rank "+utos(++minrank));
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

