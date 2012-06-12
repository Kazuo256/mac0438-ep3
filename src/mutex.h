
#ifndef EP3_MUTEX_H_
#define EP3_MUTEX_H_

namespace ep3 {

class Semaph;

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
    //void try_lock ();
    void unlock ();
  private:
    friend class Lock;
    Semaph *mutex_;
    Mutex (const Mutex&);
    Mutex& operator = (const Mutex&);
};

} // namespace ep3

#endif

