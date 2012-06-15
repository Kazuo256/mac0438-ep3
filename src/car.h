
#ifndef EP3_CAR_H_
#define EP3_CAR_H_

namespace ep3 {

class RollerCoasterMonitor;

class Car {
  public:
    Car (RollerCoasterMonitor* monitor);
    void start ();
  private:
    RollerCoasterMonitor  *monitor_;
    unsigned              id_;
    static unsigned       next_id_;
    void run ();
};

} // namespace ep3

#endif

