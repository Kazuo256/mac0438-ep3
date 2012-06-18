
#include "car.h"

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::string;
using std::vector;
using std::set;

unsigned            Car::next_id_ = 0;
vector<const Car*>  Car::cars_;

Car::Car (RollerCoasterMonitor* monitor) :
  monitor_(monitor),
  id_(next_id_++),
  riding_(false) {
  cars_.push_back(this);
}

string Car::info () const {
  return "<car "+utos(id_)+">";
}

void Car::add_psg (const Thread* psg) {
  psgs_.insert(psg);
}

void Car::drop_psg (const Thread* psg) {
  psgs_.erase(psg);
}

static const char* riding_text (bool riding) {
  return riding ? "riding" : "stopped";
}

void Car::dump_all () {
  vector<const Car*>::iterator cit;
  for (cit = cars_.begin(); cit < cars_.end(); cit++) {
    Log().line("\tCar "+(*cit)->info()+" is "+riding_text((*cit)->riding_)+". "
              +"Number of passengers: "+utos((*cit)->psgs_.size())+".");
    const set<const Thread*>& psgs = (*cit)->psgs_;
    set<const Thread*>::const_iterator pit;
    for (pit = psgs.begin(); pit != psgs.end(); pit++)
      Log().line("\t\t"+(*pit)->info());
  }
}

unsigned Car::num () {
  return cars_.size();
}

void Car::do_run () {
  while (true) {
    monitor_->carrega(this);
    monitor_->ride(this);
    Thread::delay(100.0f);
    monitor_->descarrega(this);
  }
}

} // namespace ep3

