#include <iostream>
#include <iomanip>
#include <string> 
#include "Event.hh"

Event::Event(int CheckCounter,int  Photodiode1,int  Photodiode2)
  : CheckCounter(CheckCounter),
    Photodiode1(Photodiode1),
    Photodiode2(Photodiode2)
{}

Event::~Event()
{}

void Event::print(void) const 
{

//   std::cout << setiosflags(std::ios::fixed);
//   std::cout << "CheckCounter " << CheckCounter << " Photodiode 1 Data "
// 	    << std::setw(16) << std::setprecision(9) << Photodiode1 
// 	    << " Photodiode 2 Data "
// 	    << std::setw(16) << std::setprecision(9) << Photodiode2 
// 	    << std::endl;

  std::cout << CheckCounter << " " << Photodiode1 << " " << Photodiode2 << std::endl;

}
