
cmake_minimum_required (VERSION 2.8)

project (ep3 CXX C)
include_directories (src)

set (CMAKE_THREAD_PREFER_PTHREAD True)
find_package (Threads)
if (NOT CMAKE_USE_PTHREADS_INIT)
  message (FATAL_ERROR "Pthread libs not found!")
endif ()

add_executable (ep3
  src/main.cxx
  src/ep3.cxx
  src/log.cxx
  src/monitor.cxx
  src/thread.cxx
  src/semaph.cxx
)

target_link_libraries (ep3 m ${CMAKE_THREAD_LIBS_INIT})
set_target_properties (ep3 PROPERTIES COMPILE_FLAGS "-ansi -Wall -O2")

