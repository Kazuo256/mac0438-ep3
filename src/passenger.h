
#ifndef EP3_PASSENGER_H_
#define EP3_PASSENGER_H_

namespace ep3 {

class RollerCoasterMonitor;

class Passenger {
  public:
    Passenger (RollerCoasterMonitor* monitor);
    void start ();
  private:
    RollerCoasterMonitor  *monitor_;
    unsigned              id_;
    bool                  golden_ticket_;
    void run ();
};

} // namespace ep3

#endif

