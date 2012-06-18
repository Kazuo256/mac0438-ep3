
#ifndef EP3_EP3_H_
#define EP3_EP3_H_

namespace ep3 {

// Tries to initialize the program by reading the command line paramenters
// given by the user. Returns true upon success, false otherwise.
bool init (int argc, char** argv);

// Runs the roller coaster simulation.
void run ();

} // namespace ep3

#endif

