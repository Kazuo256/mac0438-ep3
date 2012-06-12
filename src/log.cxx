
#include "log.h"

namespace ep2 {

using std::string;

unsigned  Log::flags_;
//Mutex     Log::mutex_;

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

Log& Log::out (const string& text) {
  //Mutex::Lock lock(mutex_);
  fputs(text.c_str(), output_);
  fputc(10, output_);
  fflush(output_);
  return *this;
}

Log& Log::debug (const string& text) {
  return (flags_ & debug_flag())
    ? out("[DEBUG] " + text)
    : *this;
}

Log& Log::warn (const string& text) {
  return (flags_ & warning_flag())
    ? out("[WARNING] " + text)
    : *this;
}

void Log::enable_debug () {
  flags_ |= debug_flag();
}

void Log::enable_warning () {
  flags_ |= warning_flag();
}

} // namespace ep2

