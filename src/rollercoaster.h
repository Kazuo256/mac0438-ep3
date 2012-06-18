
#ifndef EP3_ROLLERCOASTER_H_
#define EP3_ROLLERCOASTER_H_

#include <vector>

namespace ep3 {

class RollerCoasterMonitor;
class Car;
class Passenger;

// Class responsible for running the roller coaster simulation.
// Basically uses the parameters given to the constructor to manage thread
// creation and initial information they require.
class RollerCoaster {
  public:
    RollerCoaster (float psg_rate, unsigned car_num, unsigned car_cap);
    ~RollerCoaster ();
    void run ();
  private:
    RollerCoasterMonitor    *monitor_;
    float                   psg_delay_;
    unsigned                car_num_;
};

} // namespace ep3

#endif

