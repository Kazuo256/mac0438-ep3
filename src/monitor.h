
#ifndef EP3_MONITOR_H_
#define EP3_MONITOR_H_

#include <queue>

namespace ep3 {

class Semaph;

class Monitor {
  public:
    typedef unsigned char Rank;
    static const Rank     MAXRANK = -1;
    ~Monitor ();
  protected:
    typedef int           CondVar; // TODO
    Monitor ();
    void start_procedure ();
    void end_procedure ();
    bool empty (const CondVar& cv) const;
    void wait (CondVar& cv, Rank rank = MAXRANK);
    void signal (CondVar& cv);
    void signal_all (CondVar& cv);
    Rank minrank (const CondVar& cv) const;
  private:
    Semaph *sem_;
    Monitor (const Monitor&);
    Monitor& operator = (const Monitor&);
};

} // namespace ep3

#endif

