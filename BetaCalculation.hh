#ifndef BetaCalculation_h
#define BetaCalculation_h 1

#include <vector>
#include <map>
#include "TGraphErrors.h"
#include <Intensity.hh>
#include <Utilities.hh>
#include <TransmissionLength.hh>
#include <math.h>


class BetaCalculation {

private:
 
 //private method
//   double ffun ( double *x, double *par);
  
  Utilities m_util;

public:
  
  BetaCalculation();
  ~BetaCalculation();

  double errorbeta (double rl, double rs, double il, double is, double ilrms, double isrms);

  std::map<double,double> fitbetamethodph1 (std::map<int, double>& ledint1, std::map<int, double>& ledintrms1);
  std::map<double,double> fitbetamethodph2 (std::map<int, double>& ledint2, std::map<int, double>& ledintrms2);

  TGraphErrors* fitbetamethodgrapherrorph1( std::vector<TransmissionLength> tranlength);
  TGraphErrors* fitbetamethodgrapherrorph2( std::vector<TransmissionLength> tranlength);

  TGraphErrors* betavsdepth( int wavelength, std::map<int,std::vector<TransmissionLength> > tranlength);
  TGraphErrors* depthmean( int wavelength1, std::map<int,std::vector<TransmissionLength> > tranlength1);

  void calculateph1 (std::map<int, std::map<int, double> >& led383int1, std::map<int, std::map<int, double> >& led400int1, std::map<int, std::map<int, double> >& led470int1, std::map<int, std::map<int, double> >& led525int1, std::map<int, std::map<int, double> >& led383intrms1, std::map<int, std::map<int, double> >& led400intrms1, std::map<int, std::map<int, double> >& led470intrms1, std::map<int, std::map<int, double> >& led525intrms1,std::map<int, std::map<int, double> >& led375int1, std::map<int, std::map<int, double> >& led425int1, std::map<int, std::map<int, double> >& led450int1, std::map<int, std::map<int, double> >& led495int1, std::map<int, std::map<int, double> >& led375intrms1, std::map<int, std::map<int, double> >& led425intrms1, std::map<int, std::map<int, double> >& led450intrms1, std::map<int, std::map<int, double> >& led495intrms1 );

  void calculateph2 (std::map<int, std::map<int, double> >& led383int2, std::map<int, std::map<int, double> >& led400int2, std::map<int, std::map<int, double> >& led470int2, std::map<int, std::map<int, double> >& led525int2, std::map<int, std::map<int, double> >& led383intrms2, std::map<int, std::map<int, double> >& led400intrms2, std::map<int, std::map<int, double> >& led470intrms2, std::map<int, std::map<int, double> >& led525intrms2,std::map<int, std::map<int, double> >& led375int2, std::map<int, std::map<int, double> >& led425int2, std::map<int, std::map<int, double> >& led450int2, std::map<int, std::map<int, double> >& led495int2, std::map<int, std::map<int, double> >& led375intrms2, std::map<int, std::map<int, double> >& led425intrms2, std::map<int, std::map<int, double> >& led450intrms2, std::map<int, std::map<int, double> >& led495intrms2 );

  void calculateallph (std::map<int, std::map<int, double> >& led383int1, std::map<int, std::map<int, double> >& led400int1, std::map<int, std::map<int, double> >& led470int1, std::map<int, std::map<int, double> >& led525int1, std::map<int, std::map<int, double> >& led383intrms1, std::map<int, std::map<int, double> >& led400intrms1, std::map<int, std::map<int, double> >& led470intrms1, std::map<int, std::map<int, double> >& led525intrms1,std::map<int, std::map<int, double> >& led375int1, std::map<int, std::map<int, double> >& led425int1, std::map<int, std::map<int, double> >& led450int1, std::map<int, std::map<int, double> >& led495int1, std::map<int, std::map<int, double> >& led375intrms1, std::map<int, std::map<int, double> >& led425intrms1, std::map<int, std::map<int, double> >& led450intrms1, std::map<int, std::map<int, double> >& led495intrms1,std::map<int, std::map<int, double> >& led383int2, std::map<int, std::map<int, double> >& led400int2, std::map<int, std::map<int, double> >& led470int2, std::map<int, std::map<int, double> >& led525int2 , std::map<int, std::map<int, double> >& led383intrms2, std::map<int, std::map<int, double> >& led400intrms2, std::map<int, std::map<int, double> >& led470intrms2, std::map<int, std::map<int, double> >& led525intrms2,std::map<int, std::map<int, double> >& led375int2, std::map<int, std::map<int, double> >& led425int2, std::map<int, std::map<int, double> >& led450int2, std::map<int, std::map<int, double> >& led495int2, std::map<int, std::map<int, double> >& led375intrms2, std::map<int, std::map<int, double> >& led425intrms2, std::map<int, std::map<int, double> >& led450intrms2, std::map<int, std::map<int, double> >& led495intrms2);

  void calculateallphanddepth (std::map<int, std::map<int, double> >& led383int1, std::map<int, std::map<int, double> >& led400int1, std::map<int, std::map<int, double> >& led470int1, std::map<int, std::map<int, double> >& led525int1, std::map<int, std::map<int, double> >& led383intrms1, std::map<int, std::map<int, double> >& led400intrms1, std::map<int, std::map<int, double> >& led470intrms1, std::map<int, std::map<int, double> >& led525intrms1,std::map<int, std::map<int, double> >& led375int1, std::map<int, std::map<int, double> >& led425int1, std::map<int, std::map<int, double> >& led450int1, std::map<int, std::map<int, double> >& led495int1, std::map<int, std::map<int, double> >& led375intrms1, std::map<int, std::map<int, double> >& led425intrms1, std::map<int, std::map<int, double> >& led450intrms1, std::map<int, std::map<int, double> >& led495intrms1,std::map<int, std::map<int, double> >& led383int2, std::map<int, std::map<int, double> >& led400int2, std::map<int, std::map<int, double> >& led470int2, std::map<int, std::map<int, double> >& led525int2 , std::map<int, std::map<int, double> >& led383intrms2, std::map<int, std::map<int, double> >& led400intrms2, std::map<int, std::map<int, double> >& led470intrms2, std::map<int, std::map<int, double> >& led525intrms2,std::map<int, std::map<int, double> >& led375int2, std::map<int, std::map<int, double> >& led425int2, std::map<int, std::map<int, double> >& led450int2, std::map<int, std::map<int, double> >& led495int2, std::map<int, std::map<int, double> >& led375intrms2, std::map<int, std::map<int, double> >& led425intrms2, std::map<int, std::map<int, double> >& led450intrms2, std::map<int, std::map<int, double> >& led495intrms2);


};

#endif
