
#ifndef EP3_ROLLERCOASTER_H_
#define EP3_ROLLERCOASTER_H_

namespace ep3 {

class RollerCoasterMonitor;

class RollerCoaster {
  public:
    RollerCoaster (unsigned car_num, unsigned car_cap);
    ~RollerCoaster ();
    void test ();
    void open ();
    static void* testthread (void *args);
  private:
    RollerCoasterMonitor *monitor_;
};

} // namespace ep3

#endif

