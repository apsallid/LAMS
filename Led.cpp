#include <iostream>
#include <iomanip>
#include <string> 
#include "Led.hh"

Led::Led( double TimeStart, double TimeEnd, std::vector<int> Ledflash)
  : TimeStart(TimeStart),
    TimeEnd(TimeEnd),
    Ledflash(Ledflash)
{}

Led::~Led()
{}

void Led::print(void) const 
{

  std::cout << setiosflags(std::ios::fixed);
  std::cout << "TimeStart " << TimeStart 
	    << "TimeEnd " << TimeEnd 
	    << std::endl;

}
