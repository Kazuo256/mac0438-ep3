
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
  golden_ticket_(!(rand()&0x3)), // 25% chance. Sry for ugly code.
  ride_num_(0) {}

string Passenger::info () const {
  return
    string("<psg ")+(golden_ticket_?"D":"")+utos(id_)+":"+utos(ride_num_)+">";
}

void Passenger::do_run () {
  Log().debug(info()+" appears!");
  // Ride the roller coaster twice.
  monitor_->pegaCarona(this);
  ride_num_++;
  monitor_->pegaCarona(this);
  ride_num_++;
  // Safely exits the simulation.
  Log().debug(info()+" leaves the roller coaster for good.");
  monitor_->safe_exit(this);
}

} // namespace ep3

