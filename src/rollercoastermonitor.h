
#ifndef EP3_ROLLERCOASTERMONITOR_H_
#define EP3_ROLLERCOASTERMONITOR_H_

#include <vector>
#include <queue>

#include "monitor.h"

namespace ep3 {

class Car;

class RollerCoasterMonitor : public Monitor {
  public:
    RollerCoasterMonitor () :
      Monitor(),
      //testcv_(2),
      available_car_(2),
      waiting_psgs_count_(0),
      next_car_(NULL) {}
    void pegaCarona (unsigned psg_id, bool golden);
    void carrega (std::vector<unsigned>& car_sits);
    void descarrega ();
    //
    void start_lap (unsigned car_id);
    void finish_lap (unsigned car_id);
    //
    //void testA (Rank rank);
    //void testB ();
  private:
    //CondVar               testcv_;
    // Used as a queue for the incoming passengers.
    CondVar               available_car_;
    // Used as a queue for the arriving cars.
    CondVar               full_cap_;
    unsigned              waiting_psgs_count_;
    // Used to know when the car loading order has been updated.
    CondVar               load_order_;
    // Used to know the order in which the cars start to load.
    std::vector<unsigned> psg_buffer_;
    Car                   *next_car_;
    ////////
    // Used to know when the car riding order has been updated.
    CondVar               riding_order_;
    // Used to know the order in which the cars enter the rails.
    std::queue<unsigned>  cars_riding_;
};

} // namespace ep3

#endif

