
#include "car.h"

#include "rollercoastermonitor.h"
#include "thread.h"
#include "log.h"

namespace ep3 {

using std::string;
using std::vector;
using std::list;

unsigned            Car::next_id_ = 0;
vector<const Car*>  Car::cars_;

Car::Car (RollerCoasterMonitor* monitor) :
  monitor_(monitor),
  id_(next_id_++) {
  cars_.push_back(this);
}

string Car::info () const {
  return "<car "+utos(id_)+">";
}

void Car::add_psg (const Thread* psg) {
  psgs_.push_back(psg);
}

void Car::drop_psg () {
  psgs_.pop_front();
}

void Car::dump_all () {
  vector<const Car*>::iterator cit;
  for (cit = cars_.begin(); cit < cars_.end(); cit++) {
    Log().line("\tNumber of passengers at "+(*cit)->info()+": "+
               utos((*cit)->psgs_.size())+".");
    const list<const Thread*>& psgs = (*cit)->psgs_;
    list<const Thread*>::const_iterator pit;
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

