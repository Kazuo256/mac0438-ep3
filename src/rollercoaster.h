
#ifndef EP3_ROLLERCOASTER_H_
#define EP3_ROLLERCOASTER_H_

namespace ep3 {

class RollerCoasterMonitor;

class RollerCoaster {
  public:
    RollerCoaster (unsigned car_num, unsigned car_cap);
    ~RollerCoaster ();
    static void* testthread (void *args);
    void test ();
  private:
    RollerCoasterMonitor *monitor_;
};

} // namespace ep3

#endif

