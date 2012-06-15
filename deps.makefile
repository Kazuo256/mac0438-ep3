# dependencies
.temp/mutex.o: src/mutex.cxx src/mutex.h src/semaph.h src/log.h
.temp/thread.o: src/thread.cxx src/thread.h src/mutex.h src/semaph.h \
 src/monitor.h src/log.h
.temp/ep3.o: src/ep3.cxx src/ep3.h src/rollercoaster.h src/thread.h \
 src/mutex.h src/log.h
.temp/rollercoaster.o: src/rollercoaster.cxx src/rollercoaster.h \
 src/rollercoastermonitor.h src/monitor.h src/thread.h src/mutex.h \
 src/log.h
.temp/main.o: src/main.cxx src/ep3.h src/log.h src/mutex.h src/thread.h
.temp/rollercoastermonitor.o: src/rollercoastermonitor.cxx \
 src/rollercoastermonitor.h src/monitor.h src/thread.h src/mutex.h \
 src/log.h
.temp/log.o: src/log.cxx src/log.h src/mutex.h
.temp/semaph.o: src/semaph.cxx src/semaph.h src/log.h src/mutex.h
.temp/monitor.o: src/monitor.cxx src/monitor.h src/thread.h src/mutex.h \
 src/log.h src/semaph.h
