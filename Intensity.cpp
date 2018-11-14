#include <iostream>
#include <iomanip>
#include <string> 
#include "Intensity.hh"

Intensity::Intensity( int wavelength, double mean, double rms, int distance)
  : wavelength(wavelength),
    mean(mean),
    rms(rms),
    distance(distance)
{}

Intensity::~Intensity()
{}

void Intensity::print(void) const 
{

//   std::cout << setiosflags(std::ios::fixed);
//   std::cout << "CheckCounter " << CheckCounter << " Photodiode 1 Data "
// 	    << std::setw(16) << std::setprecision(9) << Photodiode1 
// 	    << " Photodiode 2 Data "
// 	    << std::setw(16) << std::setprecision(9) << Photodiode2 
// 	    << std::endl;

  std::cout << "Wavelength " << wavelength <<  " Mean " << mean << " RMS " << rms << " Distance " << distance  << std::endl;

}
