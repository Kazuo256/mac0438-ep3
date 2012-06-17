
#ifndef EP3_ROLLERCOASTER_H_
#define EP3_ROLLERCOASTER_H_

#include <vector>

namespace ep3 {

class RollerCoasterMonitor;
class Car;
class Passenger;

class RollerCoaster {
  public:
    RollerCoaster (float psg_rate, unsigned car_num, unsigned car_cap);
    ~RollerCoaster ();
    void open ();
    void run ();
    //void test ();
    //static void* testthread (void* args);
  private:
    RollerCoasterMonitor    *monitor_;
    float                   psg_delay_;
    unsigned                car_num_;
    std::vector<Car*>       cars_;
    std::vector<Passenger*> psgs_;
};

} // namespace ep3

#endif

