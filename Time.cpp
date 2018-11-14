#include <iostream>
#include <iomanip>
#include <string> 
#include "Time.hh"

Time::Time(int source, int distance, int depth, int timevalue)
  : source(source),
    distance(distance),
    depth(depth),
    timevalue(timevalue)
{}

Time::~Time()
{}

void Time::print(void) const 
{


  std::cout << "Source " << wavelength <<  " Distance " << mean << " Depth " << rms << " TimeValue " << distance  << std::endl;

}
