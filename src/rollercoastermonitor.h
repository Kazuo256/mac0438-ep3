
#ifndef EP3_ROLLERCOASTERMONITOR_H_
#define EP3_ROLLERCOASTERMONITOR_H_

#include "monitor.h"

namespace ep3 {

class RollerCoasterMonitor : public Monitor {
  public:
    RollerCoasterMonitor () : Monitor(), testcv_(2) {}
    void pegaCarona ();
    void carrega ();
    void descarrega ();
    void testA (Rank rank);
    void testB ();
  private:
    RankedCondVar testcv_;
};

} // namespace ep3

#endif

