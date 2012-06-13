
#ifndef EP2_THREAD_H_
#define EP2_THREAD_H_

#include <pthread.h>

// Change this to support more priority levels.
#define EP3_NUMBER_OF_PRIORITIES 2

namespace ep3 {

class Thread {
  public:
    typedef void* (*Routine) (void*);
    typedef unsigned char Rank;
    Thread (Routine routine, Rank rank = MAX_RANK) : 
      running_(false), routine_(routine), rank_(rank) {}
    bool running () const { return running_; }
    void run (void *arg);
    void join ();
    bool operator == (const Thread& rhs) const;
    static const Rank RANK_RANGE = EP3_NUMBER_OF_PRIORITIES;
    static const Rank MAX_RANK = RANK_RANGE-1;
    static void exit();
  private:
    bool      running_;
    Routine   routine_;
    pthread_t thread_;
    Rank      rank_;
};

} // namespace ep3

#endif

