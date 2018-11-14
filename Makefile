#
# SIRENE Makefile
#
###############################################################################
include Makefile.arch


PLATFORM=$(shell uname)

SRCS    = $(wildcard *.cpp)
OBJS    = $(SRCS:%.cpp=%.o)

CXXFLAGS += -I/afs/cern.ch/work/a/apsallid/Software/

ifndef CXX
    CXX = g++
endif

#compiler flags

ifeq "$(CXX)" "gcc"
    FLAGS =  -g -O2  -Wall -fPIC
endif

HDRS     = $(wildcard *.hh)



%:%.o
	$(LD) $(LDFLAGS) $(GLIBS) $(OutPutOpt) $(CXX) $(FLAGS) $(ROOTLIBS) $^ -o $@


$(OBJS): %.o: %.cpp $(HDRS)
	@echo "Compiling $< with $(CXX) ..."
	$(CXX)  $(CXXFLAGS) $(FLAGS) -c $< -o $@


lams: lams.o DataReader.o Event.o Utilities.o  BuildLAMPSEvent.o MonitorPhd.o Cycle.o Led.o AnalyzePhd.o CheckLAMSSystem.o Intensity.o BetaCalculation.o TransmissionLength.o
	@echo "Building $@ ..."
	$(LD) $(LDFLAGS) $(GLIBS) $(OutPutOpt) $(CXX) $(FLAGS) lams.o DataReader.o Event.o Utilities.o  BuildLAMPSEvent.o MonitorPhd.o Cycle.o Led.o AnalyzePhd.o CheckLAMSSystem.o Intensity.o BetaCalculation.o TransmissionLength.o -o $@
clean:
	rm -f *.o
