
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

void Passenger::start () {
  Thread::create<Passenger,&Passenger::run>()->run(static_cast<void*>(this));
}

void Passenger::run () {
  Log().line("A wild passenger (#"+utos(id_)+") appears!");
  monitor_->pegaCarona(golden_ticket_);
  monitor_->pegaCarona(golden_ticket_);
}

} // namespace ep3

