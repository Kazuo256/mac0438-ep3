
#include "passenger.h"

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

unsigned Passenger::next_id_ = 0;

Passenger::Passenger (RollerCoasterMonitor* monitor) :
  monitor_(monitor),
  id_(next_id_++),
  golden_ticket_(false) {}

void Passenger::do_run () {
  Log().line("Passenger (#"+utos(id_)+") appears!");
  //Thread self = Thread::self();
  //self->set_info(
  //  "<passenger "+(golden_?"D":"")+utos(id_)+":0>"
  //);
  Log().line("Passenger (#"+utos(id_)+") first time.");
  monitor_->pegaCarona(golden_ticket_);
  Log().line("Passenger (#"+utos(id_)+") second time.");
  monitor_->pegaCarona(golden_ticket_);
}

} // namespace ep3

