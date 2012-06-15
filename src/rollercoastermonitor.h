
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
    //
    void start_lap (unsigned car_id);
    void finish_lap (unsigned car_id);
    //
    void testA (Rank rank);
    void testB ();
  private:
    CondVar               testcv_;
    // Used to know when the car riding order has been updated.
    CondVar               riding_order_;
    // Used to know the order in which the cars enter the rails.
    std::queue<unsigned>  cars_riding_;
    // Used by the cars
    std::vector<CondVar>  ride_rails_;
};

} // namespace ep3

#endif

