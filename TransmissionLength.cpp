#include <iostream>
#include <iomanip>
#include <string> 
#include "TransmissionLength.hh"

TransmissionLength::TransmissionLength( double wavelength, double trlength, double errorintrlength)
  : wavelength(wavelength),
    trlength(trlength),
    errorintrlength(errorintrlength)
{}

TransmissionLength::~TransmissionLength()
{}

void TransmissionLength::print(void) const 
{


  std::cout << "Wavelength " << wavelength <<  " TrLen " << trlength << " Error " << errorintrlength   << std::endl;

}
