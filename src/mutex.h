
#ifndef EP3_MUTEX_H_
#define EP3_MUTEX_H_

namespace ep3 {

class Semaph;

// This class just makes a wrapper for the Semaph class, in a way that it
// behaves just like a common mutex. It has some fancy features worth noticing
// though. Basically, if you have a Mutex variable, you can lock a whole block
// of code by declaring a Mutex::lock variable at its begining and using the
// mutex variable in the lock object constructor. Like this:
//
//    Mutex mutex;
//    ...
//    {
//      // This whole block of code is locked.
//      Mutex::Lock lock(mutex);
//      ... critical region ...
//    }
//
// The Mutex class also has the common lock() and unlock() methods, so it can
// be used normally too.
class Mutex {
  public:
    class Lock {
      public:
        Lock (Mutex& mutex);
        ~Lock ();
      private:
        Lock (const Lock&);
        Lock& operator = (const Lock&);
        Mutex &mutex_ref_;
    };
    Mutex ();
    ~Mutex ();
    void lock ();
    void unlock ();
  private:
    friend class Lock;
    Semaph *mutex_;
    Mutex (const Mutex&);
    Mutex& operator = (const Mutex&);
};

} // namespace ep3

#endif

