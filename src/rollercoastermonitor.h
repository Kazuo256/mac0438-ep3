
#ifndef EP3_ROLLERCOASTERMONITOR_H_
#define EP3_ROLLERCOASTERMONITOR_H_

#include "monitor.h"

namespace ep3 {

class RollerCoasterMonitor : public Monitor {
  public:
    RollerCoasterMonitor (unsigned car_num, unsigned car_cap) :
      Monitor(),
      testcv_(2),
      car_num_(car_num),
      car_cap_(car_cap) {}
    void pegaCarona ();
    void carrega ();
    void descarrega ();
    void testA (Rank rank);
    void testB ();
  private:
    RankedCondVar testcv_;
    unsigned      car_num_,
                  car_cap_;
};

} // namespace ep3

#endif

