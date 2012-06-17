
#include "rollercoaster.h"

#include <cstdlib>
#include <ctime>
#include <vector>

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"
#include "car.h"
#include "passenger.h"

namespace ep3 {

using std::vector;

RollerCoaster::RollerCoaster (float psg_rate,
                              unsigned car_num,
                              unsigned car_cap) :
  monitor_(new RollerCoasterMonitor(car_cap)),
  psg_delay_(1.0f/psg_rate),
  car_num_(car_num) {}

RollerCoaster::~RollerCoaster () {
  Log().debug("Cleaning roller coaster resources...");
  delete monitor_;
}

void RollerCoaster::run () {
  srand(time(NULL));
  Log().line("== Starting roller coaster ==");
  // Threads manage their own memory, so no need to keep their pointers.
  for (unsigned i = 0; i < car_num_; i++)
    (new Car(monitor_))->run();
  while (true)  {
    (new Passenger(monitor_))->run();
    Thread::delay(psg_delay_);
  }
}

} // namespace ep3

