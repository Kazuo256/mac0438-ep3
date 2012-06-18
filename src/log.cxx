
#include "log.h"

namespace ep3 {

using std::string;

unsigned  Log::flags_;
Mutex     Log::mutex_;

// obs: numbers, be they integrals, floating-point or hexadecimals, can't
//      really make strings greater than 20 caracters or so.

string itos (int i) {
  char buffer[32];
  sprintf(buffer, "%d", i);
  return buffer;
}

string utos (unsigned i) {
  char buffer[32];
  sprintf(buffer, "%u", i);
  return buffer;
}

string ptos (const void* p) {
  char buffer[32];
  sprintf(buffer, "%p", p);
  return buffer;
}

Log& Log::line (const string& text) {
  Mutex::Lock lock(mutex_);
  fputs(text.c_str(), output_);
  fputc(10, output_);
  fflush(output_);
  return *this;
}

Log& Log::debug (const string& text) {
  return (flags_ & debug_flag())
    ? line("[DEBUG] " + text)
    : *this;
}

Log& Log::warn (const string& text) {
  return (flags_ & warning_flag())
    ? line("[WARNING] " + text)
    : *this;
}

void Log::enable_debug () {
  flags_ |= debug_flag();
}

void Log::enable_warning () {
  flags_ |= warning_flag();
}

} // namespace ep3

