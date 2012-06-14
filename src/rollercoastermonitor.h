
#ifndef EP3_ROLLERCOASTERMONITOR_H_
#define EP3_ROLLERCOASTERMONITOR_H_

#include "monitor.h"

namespace ep3 {

class RollerCoasterMonitor : public Monitor {
  public:
    RollerCoasterMonitor () : Monitor(1u) {}
    void pegaCarona ();
    void carrega ();
    void descarrega ();
    void testA ();
    void testB ();
  private:
    CondVar testcv_;
};

} // namespace ep3

#endif

