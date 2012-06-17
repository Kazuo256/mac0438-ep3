
#include "passenger.h"

#include <cstdlib>

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::string;

unsigned Passenger::next_id_ = 0;

Passenger::Passenger (RollerCoasterMonitor* monitor) :
  monitor_(monitor),
  id_(next_id_++),
  golden_ticket_(!(rand()&0x3)), // 25%
  ride_num_(0) {}

string Passenger::info () const {
  return
    string("<psg ")+(golden_ticket_?"D":"")+utos(id_)+":"+utos(ride_num_)+">";
}

void Passenger::do_run () {
  Log().debug(info()+" appears!");
  monitor_->pegaCarona(this);
  monitor_->pegaCarona(this);
}

} // namespace ep3

