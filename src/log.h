
#ifndef EP3_LOG_H_
#define EP3_LOG_H_

#include <cstdio>
#include <string>

#include "mutex.h"

namespace ep3 {

std::string itos (int i);
std::string utos (unsigned i);
std::string ptos (const void* p);

class Log {
  public:
    explicit Log (FILE *output = stdout) : output_(output) {}
    Log& line (const std::string& text = std::string());
    Log& debug (const std::string& text = std::string());
    Log& warn (const std::string& text = std::string());
    static void enable_debug ();
    static void enable_warning ();
    static bool debug_on () { return flags_ & debug_flag(); }
    static bool warning_on () { return flags_ & warning_flag(); }
  private:
    FILE *output_;
    static unsigned flags_;
    static Mutex    mutex_;
    static unsigned debug_flag () { return 0x1; }
    static unsigned warning_flag () { return 0x2; }
};

} // namespace ep3

#endif

