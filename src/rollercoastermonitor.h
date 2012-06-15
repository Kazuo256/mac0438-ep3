
#ifndef EP3_ROLLERCOASTERMONITOR_H_
#define EP3_ROLLERCOASTERMONITOR_H_

#include <vector>
#include <queue>

#include "monitor.h"

namespace ep3 {

class RollerCoasterMonitor : public Monitor {
  public:
    RollerCoasterMonitor () :
      Monitor(),
      testcv_(2) {}
    void pegaCarona ();
    void carrega ();
    void descarrega ();
    void testA (Rank rank);
    void testB ();
  private:
    RankedCondVar         testcv_;
    // Used to know when a car wants to use the rails to start a new lap. May
    // also be used to notify the "rail timer" to die when the roller coaster
    // closes.
    CondVar               request_rails_;
    // Used to know the order in which the cars enter the rails. Refers to
    // positions in ride_rails_.
    std::queue<unsigned>  cars_riding_;
    // Used by the cars
    std::vector<CondVar>  ride_rails_;
};

} // namespace ep3

#endif

