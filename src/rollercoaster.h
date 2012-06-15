
#ifndef EP3_ROLLERCOASTER_H_
#define EP3_ROLLERCOASTER_H_

namespace ep3 {

class RollerCoasterMonitor;

class RollerCoaster {
  public:
    RollerCoaster (unsigned car_num, unsigned car_cap);
    ~RollerCoaster ();
    void open ();
    void run ();
    void test ();
    static void* car_thread (void* args);
    static void* psg_thread (void* args);
    static void* testthread (void* args);
  private:
    RollerCoasterMonitor  *monitor_;
    unsigned              car_num_;
};

} // namespace ep3

#endif

