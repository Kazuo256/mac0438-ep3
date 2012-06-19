
#ifndef EP3_ROLLERCOASTERMONITOR_H_
#define EP3_ROLLERCOASTERMONITOR_H_

#include <string>
#include <vector>
#include <queue>
#include <map>

#include "monitor.h"

namespace ep3 {

class Car;
class Passenger;

// Roller Coaster's monitor class. Inherits from Monitor and implements the
// operations "pegaCarona", "descarrega", "descarrega", and also "ride".
// There are a lot a condition variables so they are explained with more detail.
class RollerCoasterMonitor : public Monitor {
  public:
    RollerCoasterMonitor (unsigned car_cap) :
      Monitor(),
      car_cap_(car_cap),
      waiting_psgs_count_(0),
      available_car_(2), // only condition variable the 2 priority levels
      loading_car_(false) {}
    // The main synchronization operations for the simulation.
    void pegaCarona (const Passenger* psg);
    void carrega (Car* car);
    void descarrega (Car* car);
    void ride (Car* car);
    void register_car (const Car* car);
  private:
    unsigned                      car_cap_;
    // These two are used as a semaphore between the incoming passengers and
    // the next car being loaded.
    unsigned                      waiting_psgs_count_;
    CondVar                       waiting_psgs_;
    // Passengers wait for an available car, and the car lets them in according
    // to their arrival order, but allowing the ones with golden tickets to go
    // first. This condition variable with two ranks is responsible for all
    // that (see constructor above).
    CondVar                       available_car_;
    // A passenger uses this to know when the ride has ended. 
    std::map<const Car*,CondVar>  ride_end_;
    // These form yet another semaphore, though a binary one this time. It
    // basically certifies that only one car at a time is loading passengers.
    bool                          loading_car_;
    CondVar                       loading_cars_;
    // These ones control the cars' order on the rails once they start riding
    // it. The threads are delayed by time measures, so they could get messed
    // around during their ride. The queue enforces their original order.
    std::queue<unsigned>          cars_riding_;
    CondVar                       riding_order_;
    // Reports roller coaster state.
    void report (const std::string& title) const;
};

} // namespace ep3

#endif

