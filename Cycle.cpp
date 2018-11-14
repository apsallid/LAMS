#include <iostream>
#include <iomanip>
#include <string> 
#include "Cycle.hh"

Cycle::Cycle( double TimeStart, double TimeEnd, double TimeL1toL2, double TimeL2toL3, double TimeL3toL4)
  : TimeStart(TimeStart),
    TimeEnd(TimeEnd),
    TimeL1toL2(TimeL1toL2),
    TimeL2toL3(TimeL2toL3),
    TimeL3toL4(TimeL3toL4)
{}

Cycle::~Cycle()
{}

void Cycle::print(void) const 
{

  std::cout << setiosflags(std::ios::fixed);
  std::cout << "TimeStart " << TimeStart 
	    << "TimeEnd " << TimeEnd 
	    << "TimeL1toL2 " << TimeL1toL2 
	    << "TimeL2toL3 " << TimeL2toL3 
	    << "TimeL3toL4 " << TimeL3toL4 
	    << std::endl;

}
