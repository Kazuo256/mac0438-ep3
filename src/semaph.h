
#ifndef EP3_SEMAPH_H_
#define EP3_SEMAPH_H_

#include <semaphore.h>

namespace ep3 {

// Represent a semaphore. Has the usual wait() and post() operations.
class Semaph {
  public:
    Semaph (unsigned init_val);
    ~Semaph ();
    void wait ();
    void post ();
  private:
    sem_t sem_;
    // Semaph objects are uncopyable, use pointers.
    Semaph (const Semaph&);
    Semaph& operator = (const Semaph&);
};

} // namespace ep3

#endif

