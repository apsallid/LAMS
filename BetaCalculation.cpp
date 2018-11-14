#include <iostream>
#include <iomanip>
#include <map>
#include <Event.hh>
#include <Cycle.hh>
#include <Led.hh>
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TMarker.h"
#include "Utilities.hh"
#include "BetaCalculation.hh"
#include "Intensity.hh"
#include "TransmissionLength.hh"
#include "TPostScript.h"
#include "CheckLAMSSystem.hh"
#include "TH2F.h"
#include "TF1.h"
#include "TFile.h"

BetaCalculation::BetaCalculation()
{
  m_util = Utilities();
}

BetaCalculation::~BetaCalculation()
{}


double ffun ( double *x, double *par) {return  exp(-par[0]*x[0] ) * par[1]/pow(x[0],2.) ;}

std::map<double,double>  BetaCalculation::fitbetamethodph1 ( std::map<int, double>& ledint1, std::map<int, double>& ledintrms1)
{
  
  //Fit with 
  std::vector<double> yintvsdis;
  std::vector<double> xintvsdis;
  std::vector<double> dyintvsdis;
  std::vector<double> dxintvsdis;

    
  TCanvas *c2 = new TCanvas("c2");

//   yintvsdis.push_back( log(ledint1[10]) );  
//   yintvsdis.push_back( log(ledint1[15]) );  
//   yintvsdis.push_back( log(ledint1[17]) );  
//   yintvsdis.push_back( log(ledint1[22]) );  
  yintvsdis.push_back( ledint1[10] );  
  yintvsdis.push_back( ledint1[15] );  
  yintvsdis.push_back( ledint1[17] );  
  yintvsdis.push_back( ledint1[22] );  

//   xintvsdis.push_back( 10. * log(1./pow(10.,2.) ) );  
//   xintvsdis.push_back( 15.10 * log(1./pow(15.10,2.) ) );  
//   xintvsdis.push_back( 17.17 * log(1./pow(17.17,2.) )  );  
//   xintvsdis.push_back( 22.27 * log(1./pow(22.27,2.) )   );  
  xintvsdis.push_back( 10. );  
  xintvsdis.push_back( 15.10 );  
  xintvsdis.push_back( 17.17 );  
  xintvsdis.push_back( 22.27 );  

//   dyintvsdis.push_back( log(ledintrms1[10]) );  
//   dyintvsdis.push_back( log(ledintrms1[15]) );  
//   dyintvsdis.push_back( log(ledintrms1[17]) );  
//   dyintvsdis.push_back( log(ledintrms1[22]) );  
  dyintvsdis.push_back( ledintrms1[10] );  
  dyintvsdis.push_back( ledintrms1[15] );  
  dyintvsdis.push_back( ledintrms1[17] );  
  dyintvsdis.push_back( ledintrms1[22] );  
  
//   dxintvsdis.push_back( 0.002 * 10.* log(1./pow(0.002 *10.,2.) ) );  
//   dxintvsdis.push_back( 0.002 * 15.10 * log(1./pow(0.002 *15.10,2.) ) );  
//   dxintvsdis.push_back( 0.002 * 17.17 * log(1./pow(0.002 *17.17,2.) ) );  
//   dxintvsdis.push_back( 0.002 * 22.27 * log(1./pow(0.002 *22.27,2.) ) );  
  dxintvsdis.push_back( 0.002 * 10. );  
  dxintvsdis.push_back( 0.002 * 15.10  );  
  dxintvsdis.push_back( 0.002 * 17.17  );  
  dxintvsdis.push_back( 0.002 * 22.27  );  
  
  TGraphErrors *intensityvsdistance = new TGraphErrors( 4, &xintvsdis[0], &yintvsdis[0],&dxintvsdis[0], &dyintvsdis[0] ); 
  intensityvsdistance->SetMarkerStyle(25); 
  intensityvsdistance->SetMarkerSize(1.4); 
//   intensityvsdistance->SetMarkerColor(7);  
  intensityvsdistance->Draw("AP");
  gStyle->SetOptStat(1);
  c2->Update();

  intensityvsdistance -> SetTitle( " Intensity and distances Depth 4100 m Photodiode 1 ");

  intensityvsdistance ->GetHistogram()->SetXTitle(" R (m) ");
  intensityvsdistance->GetHistogram()->SetYTitle(" Intensity (counts) ");
  gStyle->SetOptStat(1);
  c2->Update();


  TF1 *fitfunction= new TF1("fit_function", ffun , 0.,23.,2);

  fitfunction->SetParameter(0,0.);
  fitfunction->SetParameter(1,4000000.);

  intensityvsdistance->Fit("fit_function","REMQ"); 
   
  double fitfunction_par[2];

  fitfunction->GetParameters(&fitfunction_par[0]);
  
//   double constant= fitfunction_par[1]; 
  double beta= fitfunction_par[0];
  double betaerror = fitfunction->GetParError(0);

//   std::cout << constant << std::endl;
//   std::cout << beta << " pm " << betaerror << std::endl;
//   std::cout << 1./beta <<  " pm " << betaerror * pow(1./ beta,2.) << std::endl;
  
  std::map<double,double> tranlengthpmerr;

  tranlengthpmerr.insert( std::map<double,double>::value_type( 1./beta,betaerror * pow(1./ beta,2.) ) );

  return tranlengthpmerr;

}



std::map<double,double> BetaCalculation::fitbetamethodph2 (std::map<int, double>& ledint2, std::map<int, double>& ledintrms2)
{
  
  //Fit with 
  std::vector<double> yintvsdis;
  std::vector<double> xintvsdis;
  std::vector<double> dyintvsdis;
  std::vector<double> dxintvsdis;

    
  TCanvas *c2 = new TCanvas("c2");

//   yintvsdis.push_back( log(ledint2[10]) );  
//   yintvsdis.push_back( log(ledint2[15]) );  
//   yintvsdis.push_back( log(ledint2[17]) );  
//   yintvsdis.push_back( log(ledint2[22]) );  
  yintvsdis.push_back( ledint2[10] );  
  yintvsdis.push_back( ledint2[15] );  
  yintvsdis.push_back( ledint2[17] );  
  yintvsdis.push_back( ledint2[22] );  

//   xintvsdis.push_back( 10. * log(1./pow(10.,2.) ) );  
//   xintvsdis.push_back( 15.10 * log(1./pow(15.10,2.) ) );  
//   xintvsdis.push_back( 17.17 * log(1./pow(17.17,2.) )  );  
//   xintvsdis.push_back( 22.27 * log(1./pow(22.27,2.) )   );  
  xintvsdis.push_back( 10. );  
  xintvsdis.push_back( 15.10 );  
  xintvsdis.push_back( 17.17 );  
  xintvsdis.push_back( 22.27 );  

//   dyintvsdis.push_back( log(ledintrms2[10]) );  
//   dyintvsdis.push_back( log(ledintrms2[15]) );  
//   dyintvsdis.push_back( log(ledintrms2[17]) );  
//   dyintvsdis.push_back( log(ledintrms2[22]) );  
  dyintvsdis.push_back( ledintrms2[10] );  
  dyintvsdis.push_back( ledintrms2[15] );  
  dyintvsdis.push_back( ledintrms2[17] );  
  dyintvsdis.push_back( ledintrms2[22] );  
  
//   dxintvsdis.push_back( 0.002 * 10.* log(1./pow(0.002 *10.,2.) ) );  
//   dxintvsdis.push_back( 0.002 * 15.10 * log(1./pow(0.002 *15.10,2.) ) );  
//   dxintvsdis.push_back( 0.002 * 17.17 * log(1./pow(0.002 *17.17,2.) ) );  
//   dxintvsdis.push_back( 0.002 * 22.27 * log(1./pow(0.002 *22.27,2.) ) );  
  dxintvsdis.push_back( 0.002 * 10. );  
  dxintvsdis.push_back( 0.002 * 15.10  );  
  dxintvsdis.push_back( 0.002 * 17.17  );  
  dxintvsdis.push_back( 0.002 * 22.27  );  
  
  TGraphErrors *intensityvsdistance = new TGraphErrors( 4, &xintvsdis[0], &yintvsdis[0],&dxintvsdis[0], &dyintvsdis[0] ); 
  intensityvsdistance->SetMarkerStyle(25); 
  intensityvsdistance->SetMarkerSize(1.4); 
//   intensityvsdistance->SetMarkerColor(7);  
  intensityvsdistance->Draw("AP");
  gStyle->SetOptStat(1);
  c2->Update();

  intensityvsdistance -> SetTitle( " Intensity and distances Depth 4100 m Photodiode 2");

  intensityvsdistance ->GetHistogram()->SetXTitle(" R (m) ");
  intensityvsdistance->GetHistogram()->SetYTitle(" Intensity (counts) ");
  gStyle->SetOptStat(1);
  c2->Update();


  TF1 *fitfunction= new TF1("fit_function", ffun , 0.,23.,2);

  fitfunction->SetParameter(0,0.);
  fitfunction->SetParameter(1,4000000.);

  intensityvsdistance->Fit("fit_function","REMQ"); 
   
  double fitfunction_par[2];

  fitfunction->GetParameters(&fitfunction_par[0]);
  
//   double constant= fitfunction_par[1]; 
  double beta= fitfunction_par[0];
  double betaerror = fitfunction->GetParError(0);

//   std::cout << constant << std::endl;
//   std::cout << beta << " pm " << betaerror << std::endl;
//   std::cout << 1./beta <<  " pm " << betaerror * pow(1./ beta,2.) << std::endl;
  
  std::map<double,double> tranlengthpmerr;

  tranlengthpmerr.insert( std::map<double,double>::value_type( 1./beta,betaerror * pow(1./ beta,2.) ) );

  return tranlengthpmerr;

}




TGraphErrors* BetaCalculation::fitbetamethodgrapherrorph1( std::vector<TransmissionLength> tranlength)
{

  std::vector<double> yintvsdis;
  std::vector<double> xintvsdis;
  std::vector<double> dyintvsdis;
  std::vector<double> dxintvsdis;


  for (std::vector<TransmissionLength>::iterator it = tranlength.begin();it!=tranlength.end();++it){
    xintvsdis.push_back(  (*it).GetWLength() );
    yintvsdis.push_back( (*it).GetTrLen() );
//     dxintvsdis.push_back( 10. );
    switch ( (int) (*it).GetWLength() ){
    case 375:dxintvsdis.push_back(10./2.355 );break;
    case 383:dxintvsdis.push_back(18./2.355);break;
    case 400:dxintvsdis.push_back(20./2.355);break;
    case 425:dxintvsdis.push_back(20./2.355);break;
    case 450:dxintvsdis.push_back(20./2.355);break;
    case 470:dxintvsdis.push_back(24./2.355);break;
    case 495:dxintvsdis.push_back(40./2.355);break;
    case 525:dxintvsdis.push_back(40. /2.355);break;
    }
    dyintvsdis.push_back(  (*it).GetErrTrLen() );
//     (*it).print();
  }

  TGraphErrors *translength = new TGraphErrors( 8, &xintvsdis[0], &yintvsdis[0],&dxintvsdis[0], &dyintvsdis[0] ); 

  return translength;
}

TGraphErrors* BetaCalculation::fitbetamethodgrapherrorph2( std::vector<TransmissionLength> tranlength)
{

  std::vector<double> yintvsdis;
  std::vector<double> xintvsdis;
  std::vector<double> dyintvsdis;
  std::vector<double> dxintvsdis;

  for (std::vector<TransmissionLength>::iterator it = tranlength.begin();it!=tranlength.end();++it){
    xintvsdis.push_back(  (*it).GetWLength() );
    yintvsdis.push_back( (*it).GetTrLen() );
//     dxintvsdis.push_back( 10. );
    switch ( (int) (*it).GetWLength() ){
    case 375:dxintvsdis.push_back(10./2.355 );break;
    case 383:dxintvsdis.push_back(18./2.355);break;
    case 400:dxintvsdis.push_back(20./2.355);break;
    case 425:dxintvsdis.push_back(20./2.355);break;
    case 450:dxintvsdis.push_back(20./2.355);break;
    case 470:dxintvsdis.push_back(24./2.355);break;
    case 495:dxintvsdis.push_back(40./2.355);break;
    case 525:dxintvsdis.push_back(40. /2.355);break;
    }
    dyintvsdis.push_back(  (*it).GetErrTrLen() );
//     (*it).print();
  }

  TGraphErrors *translength = new TGraphErrors( 8, &xintvsdis[0], &yintvsdis[0],&dxintvsdis[0], &dyintvsdis[0] ); 

  return translength;
}

TGraphErrors* BetaCalculation::betavsdepth( int wavelength, std::map<int,std::vector<TransmissionLength> > tranlength)
{

  std::vector<double> yvsd;
  std::vector<double> xvsd;
  std::vector<double> dyvsd;
  std::vector<double> dxvsd;

  xvsd.push_back(750.);
  xvsd.push_back(1250.);
  xvsd.push_back(1750.);
  xvsd.push_back(2250.);
  xvsd.push_back(2500.);
  xvsd.push_back(2950.);
  xvsd.push_back(3400.);
  xvsd.push_back(3750.);
  xvsd.push_back(4100.);
  xvsd.push_back(3750.);
  xvsd.push_back(2950.);
  xvsd.push_back(2250.);
  xvsd.push_back(1750.);
  xvsd.push_back(1250.);
  xvsd.push_back(750.);

  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  dxvsd.push_back(0.);
  

  for (std::vector<TransmissionLength>::iterator it = tranlength[5001000].begin();it!=tranlength[5001000].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[10001500].begin();it!=tranlength[10001500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[15002000].begin();it!=tranlength[15002000].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[20002500].begin();it!=tranlength[20002500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[2500].begin();it!=tranlength[2500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[25003400].begin();it!=tranlength[25003400].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[3400].begin();it!=tranlength[3400].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[34004100].begin();it!=tranlength[34004100].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[4100].begin();it!=tranlength[4100].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[41003400].begin();it!=tranlength[41003400].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[34002500].begin();it!=tranlength[34002500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[25002000].begin();it!=tranlength[25002000].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[20001500].begin();it!=tranlength[20001500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[15001000].begin();it!=tranlength[15001000].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[1000500].begin();it!=tranlength[1000500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }



  TGraphErrors *translength = new TGraphErrors( 15, &xvsd[0], &yvsd[0],&dxvsd[0], &dyvsd[0] ); 

  return translength;
}


TGraphErrors* BetaCalculation::depthmean( int wavelength, std::map<int,std::vector<TransmissionLength> > tranlength)
{

  std::vector<double> yvsd;
  std::vector<double> xvsd;
  std::vector<double> dyvsd;
  std::vector<double> dxvsd;

  xvsd.push_back(750.);
  xvsd.push_back(1250.);
  xvsd.push_back(1750.);
  xvsd.push_back(2250.);
  xvsd.push_back(2500.);
  xvsd.push_back(2950.);
  xvsd.push_back(3400.);
  xvsd.push_back(3750.);
  xvsd.push_back(4100.);
  xvsd.push_back(3750.);
  xvsd.push_back(2950.);
  xvsd.push_back(2250.);
  xvsd.push_back(1750.);
  xvsd.push_back(1250.);
  xvsd.push_back(750.);

  dxvsd.push_back(250.);
  dxvsd.push_back(250.);
  dxvsd.push_back(250.);
  dxvsd.push_back(250.);
  dxvsd.push_back(0.);
  dxvsd.push_back(250.);
  dxvsd.push_back(0.);
  dxvsd.push_back(250.);
  dxvsd.push_back(0.);
  dxvsd.push_back(250.);
  dxvsd.push_back(250.);
  dxvsd.push_back(250.);
  dxvsd.push_back(250.);
  dxvsd.push_back(250.);
  dxvsd.push_back(250.);
 

  for (std::vector<TransmissionLength>::iterator it = tranlength[5001000].begin();it!=tranlength[5001000].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[10001500].begin();it!=tranlength[10001500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[15002000].begin();it!=tranlength[15002000].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[20002500].begin();it!=tranlength[20002500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[2500].begin();it!=tranlength[2500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[25003400].begin();it!=tranlength[25003400].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[3400].begin();it!=tranlength[3400].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[34004100].begin();it!=tranlength[34004100].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[4100].begin();it!=tranlength[4100].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  0. );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[41003400].begin();it!=tranlength[41003400].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[34002500].begin();it!=tranlength[34002500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[25002000].begin();it!=tranlength[25002000].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[20001500].begin();it!=tranlength[20001500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[15001000].begin();it!=tranlength[15001000].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }
  for (std::vector<TransmissionLength>::iterator it = tranlength[1000500].begin();it!=tranlength[1000500].end();++it){
    if ( (*it).GetWLength()==wavelength){
      yvsd.push_back( (*it).GetTrLen() );
      dyvsd.push_back(  (*it).GetErrTrLen() );
    }
  }



  TGraphErrors *translength = new TGraphErrors( 15, &xvsd[0], &yvsd[0],&dxvsd[0], &dyvsd[0] ); 

  return translength;
}





double BetaCalculation::errorbeta (double rl, double rs, double il, double is, double ilrms, double isrms)
{
  double a1; double a2;double a3;double a4; double a5; 

  a2 = -1./( il * (rl-rs)); a3 = 1./( is * (rl-rs));
  a4 = -log(is)/pow((rl-rs),2.) + log(il)/pow((rl-rs),2.) + log(pow(rs,2.))/pow((rl-rs),2.) - log(pow(rl,2.))/pow((rl-rs),2.) + 2./(rl*(rl-rs)); 
  a5 = log(is)/pow((rl-rs),2.) - log(il)/pow((rl-rs),2.) + log(pow(rl,2.))/pow((rl-rs),2.)- log(pow(rs,2.))/pow((rl-rs),2.) - 2./(rs*(rl-rs)); 
  a1 = sqrt( pow(a2 * ilrms, 2.) + pow(a3 * isrms ,2.) + pow(a4 * 0.002 * rl,2.) + pow(a5 * 0.002 * rs,2.) );

  return a1;

}



void BetaCalculation::calculateph1 (std::map<int, std::map<int, double> >& led383int1, std::map<int, std::map<int, double> >& led400int1, std::map<int, std::map<int, double> >& led470int1, std::map<int, std::map<int, double> >& led525int1, std::map<int, std::map<int, double> >& led383intrms1, std::map<int, std::map<int, double> >& led400intrms1, std::map<int, std::map<int, double> >& led470intrms1, std::map<int, std::map<int, double> >& led525intrms1,std::map<int, std::map<int, double> >& led375int1, std::map<int, std::map<int, double> >& led425int1, std::map<int, std::map<int, double> >& led450int1, std::map<int, std::map<int, double> >& led495int1, std::map<int, std::map<int, double> >& led375intrms1, std::map<int, std::map<int, double> >& led425intrms1, std::map<int, std::map<int, double> >& led450intrms1, std::map<int, std::map<int, double> >& led495intrms1){

  std::map<int,std::vector<double> > beta1; std::map<int, std::vector<double> > betaerror1; 
  double a1;  

  //Depths that will be processed
  std::vector<int> DepthsToBeProccessed;

  DepthsToBeProccessed.push_back(4100);
  DepthsToBeProccessed.push_back(3400);
  DepthsToBeProccessed.push_back(2500);
  DepthsToBeProccessed.push_back(5001000);
  DepthsToBeProccessed.push_back(10001500);
  DepthsToBeProccessed.push_back(15002000);
  DepthsToBeProccessed.push_back(20002500);
  DepthsToBeProccessed.push_back(25003400);
  DepthsToBeProccessed.push_back(34004100);
  DepthsToBeProccessed.push_back(25002000);
  DepthsToBeProccessed.push_back(34002500);
  DepthsToBeProccessed.push_back(41003400);
  DepthsToBeProccessed.push_back(20001500);
  DepthsToBeProccessed.push_back(15001000);
  DepthsToBeProccessed.push_back(1000500);

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

  //Error in Beta Calculation
  a1 = errorbeta(15.10, 10., led383int1[(*dep)][15], led383int1[(*dep)][10], led383intrms1[(*dep)][15], led383intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led383int1[(*dep)][17], led383int1[(*dep)][10], led383intrms1[(*dep)][17], led383intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led383int1[(*dep)][22], led383int1[(*dep)][10], led383intrms1[(*dep)][22], led383intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led383int1[(*dep)][17], led383int1[(*dep)][15], led383intrms1[(*dep)][17], led383intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led383int1[(*dep)][22], led383int1[(*dep)][15], led383intrms1[(*dep)][22], led383intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led383int1[(*dep)][22], led383int1[(*dep)][17], led383intrms1[(*dep)][22], led383intrms1[(*dep)][17] );
  betaerror1[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led400int1[(*dep)][15], led400int1[(*dep)][10], led400intrms1[(*dep)][15], led400intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led400int1[(*dep)][17], led400int1[(*dep)][10], led400intrms1[(*dep)][17], led400intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led400int1[(*dep)][22], led400int1[(*dep)][10], led400intrms1[(*dep)][22], led400intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led400int1[(*dep)][17], led400int1[(*dep)][15], led400intrms1[(*dep)][17], led400intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led400int1[(*dep)][22], led400int1[(*dep)][15], led400intrms1[(*dep)][22], led400intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led400int1[(*dep)][22], led400int1[(*dep)][17], led400intrms1[(*dep)][22], led400intrms1[(*dep)][17] );
  betaerror1[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led470int1[(*dep)][15], led470int1[(*dep)][10], led470intrms1[(*dep)][15], led470intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led470int1[(*dep)][17], led470int1[(*dep)][10], led470intrms1[(*dep)][17], led470intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led470int1[(*dep)][22], led470int1[(*dep)][10], led470intrms1[(*dep)][22], led470intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led470int1[(*dep)][17], led470int1[(*dep)][15], led470intrms1[(*dep)][17], led470intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led470int1[(*dep)][22], led470int1[(*dep)][15], led470intrms1[(*dep)][22], led470intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led470int1[(*dep)][22], led470int1[(*dep)][17], led470intrms1[(*dep)][22], led470intrms1[(*dep)][17] );
  betaerror1[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led525int1[(*dep)][15], led525int1[(*dep)][10], led525intrms1[(*dep)][15], led525intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led525int1[(*dep)][17], led525int1[(*dep)][10], led525intrms1[(*dep)][17], led525intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led525int1[(*dep)][22], led525int1[(*dep)][10], led525intrms1[(*dep)][22], led525intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led525int1[(*dep)][17], led525int1[(*dep)][15], led525intrms1[(*dep)][17], led525intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led525int1[(*dep)][22], led525int1[(*dep)][15], led525intrms1[(*dep)][22], led525intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led525int1[(*dep)][22], led525int1[(*dep)][17], led525intrms1[(*dep)][22], led525intrms1[(*dep)][17] );
  betaerror1[(*dep)].push_back( a1 );

  //Here the errors in beta from the second source

  a1 = errorbeta(15.10, 10., led375int1[(*dep)][15], led375int1[(*dep)][10], led375intrms1[(*dep)][15], led375intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led375int1[(*dep)][17], led375int1[(*dep)][10], led375intrms1[(*dep)][17], led375intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led375int1[(*dep)][22], led375int1[(*dep)][10], led375intrms1[(*dep)][22], led375intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led375int1[(*dep)][17], led375int1[(*dep)][15], led375intrms1[(*dep)][17], led375intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led375int1[(*dep)][22], led375int1[(*dep)][15], led375intrms1[(*dep)][22], led375intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led375int1[(*dep)][22], led375int1[(*dep)][17], led375intrms1[(*dep)][22], led375intrms1[(*dep)][17] );
  betaerror1[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led425int1[(*dep)][15], led425int1[(*dep)][10], led425intrms1[(*dep)][15], led425intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led425int1[(*dep)][17], led425int1[(*dep)][10], led425intrms1[(*dep)][17], led425intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led425int1[(*dep)][22], led425int1[(*dep)][10], led425intrms1[(*dep)][22], led425intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led425int1[(*dep)][17], led425int1[(*dep)][15], led425intrms1[(*dep)][17], led425intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led425int1[(*dep)][22], led425int1[(*dep)][15], led425intrms1[(*dep)][22], led425intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led425int1[(*dep)][22], led425int1[(*dep)][17], led425intrms1[(*dep)][22], led425intrms1[(*dep)][17] );
  betaerror1[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led450int1[(*dep)][15], led450int1[(*dep)][10], led450intrms1[(*dep)][15], led450intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led450int1[(*dep)][17], led450int1[(*dep)][10], led450intrms1[(*dep)][17], led450intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led450int1[(*dep)][22], led450int1[(*dep)][10], led450intrms1[(*dep)][22], led450intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led450int1[(*dep)][17], led450int1[(*dep)][15], led450intrms1[(*dep)][17], led450intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led450int1[(*dep)][22], led450int1[(*dep)][15], led450intrms1[(*dep)][22], led450intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led450int1[(*dep)][22], led450int1[(*dep)][17], led450intrms1[(*dep)][22], led450intrms1[(*dep)][17] );
  betaerror1[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led495int1[(*dep)][15], led495int1[(*dep)][10], led495intrms1[(*dep)][15], led495intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led495int1[(*dep)][17], led495int1[(*dep)][10], led495intrms1[(*dep)][17], led495intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led495int1[(*dep)][22], led495int1[(*dep)][10], led495intrms1[(*dep)][22], led495intrms1[(*dep)][10] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led495int1[(*dep)][17], led495int1[(*dep)][15], led495intrms1[(*dep)][17], led495intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led495int1[(*dep)][22], led495int1[(*dep)][15], led495intrms1[(*dep)][22], led495intrms1[(*dep)][15] );
  betaerror1[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led495int1[(*dep)][22], led495int1[(*dep)][17], led495intrms1[(*dep)][22], led495intrms1[(*dep)][17] );
  betaerror1[(*dep)].push_back( a1 );


  //Beta Calculation
  beta1[(*dep)].push_back( (1/(15.10-10.))* ( log(led383int1[(*dep)][10])-log(led383int1[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-10.))* ( log(led383int1[(*dep)][10])-log(led383int1[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(22.27-10.))* ( log(led383int1[(*dep)][10])-log(led383int1[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-15.10))* ( log(led383int1[(*dep)][15])-log(led383int1[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-15.10))* ( log(led383int1[(*dep)][15])-log(led383int1[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-17.17))* ( log(led383int1[(*dep)][17])-log(led383int1[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta1[(*dep)].push_back( (1/(15.10-10.))* ( log(led400int1[(*dep)][10])-log(led400int1[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-10.))* ( log(led400int1[(*dep)][10])-log(led400int1[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(22.27-10.))* ( log(led400int1[(*dep)][10])-log(led400int1[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-15.10))* ( log(led400int1[(*dep)][15])-log(led400int1[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-15.10))* ( log(led400int1[(*dep)][15])-log(led400int1[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-17.17))* ( log(led400int1[(*dep)][17])-log(led400int1[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta1[(*dep)].push_back( (1/(15.10-10.))* ( log(led470int1[(*dep)][10])-log(led470int1[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-10.))* ( log(led470int1[(*dep)][10])-log(led470int1[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(22.27-10.))* ( log(led470int1[(*dep)][10])-log(led470int1[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-15.10))* ( log(led470int1[(*dep)][15])-log(led470int1[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-15.10))* ( log(led470int1[(*dep)][15])-log(led470int1[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-17.17))* ( log(led470int1[(*dep)][17])-log(led470int1[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta1[(*dep)].push_back( (1/(15.10-10.))* ( log(led525int1[(*dep)][10])-log(led525int1[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-10.))* ( log(led525int1[(*dep)][10])-log(led525int1[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(22.27-10.))* ( log(led525int1[(*dep)][10])-log(led525int1[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-15.10))* ( log(led525int1[(*dep)][15])-log(led525int1[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-15.10))* ( log(led525int1[(*dep)][15])-log(led525int1[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-17.17))* ( log(led525int1[(*dep)][17])-log(led525int1[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  //Here the beta calculation for the second source

  beta1[(*dep)].push_back( (1/(15.10-10.))* ( log(led375int1[(*dep)][10])-log(led375int1[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-10.))* ( log(led375int1[(*dep)][10])-log(led375int1[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(22.27-10.))* ( log(led375int1[(*dep)][10])-log(led375int1[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-15.10))* ( log(led375int1[(*dep)][15])-log(led375int1[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-15.10))* ( log(led375int1[(*dep)][15])-log(led375int1[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-17.17))* ( log(led375int1[(*dep)][17])-log(led375int1[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta1[(*dep)].push_back( (1/(15.10-10.))* ( log(led425int1[(*dep)][10])-log(led425int1[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-10.))* ( log(led425int1[(*dep)][10])-log(led425int1[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(22.27-10.))* ( log(led425int1[(*dep)][10])-log(led425int1[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-15.10))* ( log(led425int1[(*dep)][15])-log(led425int1[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-15.10))* ( log(led425int1[(*dep)][15])-log(led425int1[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-17.17))* ( log(led425int1[(*dep)][17])-log(led425int1[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta1[(*dep)].push_back( (1/(15.10-10.))* ( log(led450int1[(*dep)][10])-log(led450int1[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-10.))* ( log(led450int1[(*dep)][10])-log(led450int1[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(22.27-10.))* ( log(led450int1[(*dep)][10])-log(led450int1[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-15.10))* ( log(led450int1[(*dep)][15])-log(led450int1[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-15.10))* ( log(led450int1[(*dep)][15])-log(led450int1[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-17.17))* ( log(led450int1[(*dep)][17])-log(led450int1[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta1[(*dep)].push_back( (1/(15.10-10.))* ( log(led495int1[(*dep)][10])-log(led495int1[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-10.))* ( log(led495int1[(*dep)][10])-log(led495int1[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(22.27-10.))* ( log(led495int1[(*dep)][10])-log(led495int1[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta1[(*dep)].push_back( (1/(17.17-15.10))* ( log(led495int1[(*dep)][15])-log(led495int1[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-15.10))* ( log(led495int1[(*dep)][15])-log(led495int1[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta1[(*dep)].push_back( (1/(22.27-17.17))* ( log(led495int1[(*dep)][17])-log(led495int1[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );
  
//  Results Printing
  std::cout<< " Photodiode 1 Beta in " << (*dep) << " m" <<std::endl;
  std::cout<< "WL " << "P(10-15) " << "P(10-17) " << "P(10-22) " << "P(15-17) " << "P(15-22) "  <<  "P(17-22) " << std::endl;
  std::cout<< "---------------------------------------------" << std::endl;
  std::cout<< 383 << " " << beta1[(*dep)][0] << " " << beta1[(*dep)][1]<<" " << beta1[(*dep)][2] << " " << beta1[(*dep)][3] << " " << beta1[(*dep)][4] << " " <<beta1[(*dep)][5] << std::endl;
  std::cout<< 400 <<" " << beta1[(*dep)][6] << " " <<beta1[(*dep)][7]<<" " << beta1[(*dep)][8] << " " << beta1[(*dep)][9] <<  " " <<beta1[(*dep)][10] << " " <<beta1[(*dep)][11] << std::endl;
  std::cout<< 470 << " " <<beta1[(*dep)][12] << " " <<beta1[(*dep)][13]<< " " <<beta1[(*dep)][14] <<  " " <<beta1[(*dep)][15] <<  " " <<beta1[(*dep)][16] << " " <<beta1[(*dep)][17] << std::endl;
  std::cout<< 525 << " " <<beta1[(*dep)][18] << " " <<beta1[(*dep)][19]<< " " <<beta1[(*dep)][20] <<  " " <<beta1[(*dep)][21] <<  " " <<beta1[(*dep)][22] << " " <<beta1[(*dep)][23] << std::endl;
  std::cout<< 375 << " " << beta1[(*dep)][24] << " " << beta1[(*dep)][25]<<" " << beta1[(*dep)][26] << " " << beta1[(*dep)][27] << " " << beta1[(*dep)][28] << " " <<beta1[(*dep)][29] << std::endl;
  std::cout<< 425 <<" " << beta1[(*dep)][30] << " " <<beta1[(*dep)][31]<<" " << beta1[(*dep)][32] << " " << beta1[(*dep)][33] <<  " " <<beta1[(*dep)][34] << " " <<beta1[(*dep)][35] << std::endl;
  std::cout<< 450 << " " <<beta1[(*dep)][36] << " " <<beta1[(*dep)][37]<< " " <<beta1[(*dep)][38] <<  " " <<beta1[(*dep)][39] <<  " " <<beta1[(*dep)][40] << " " <<beta1[(*dep)][41] << std::endl;
  std::cout<< 495 << " " <<beta1[(*dep)][42] << " " <<beta1[(*dep)][43]<< " " <<beta1[(*dep)][44] <<  " " <<beta1[(*dep)][45] <<  " " <<beta1[(*dep)][46] << " " <<beta1[(*dep)][47] << std::endl;

  std::cout<< "---------------------------------------------" << std::endl;
  std::cout<< " Photodiode 1 Errors in Beta in " << (*dep) << " m" << std::endl;
  std::cout<< "WL " << "P(10-15) " << "P(10-17) " << "P(10-22) " << "P(15-17) " << "P(15-22) "  <<  "P(17-22) " << std::endl;
  std::cout<< "---------------------------------------------" << std::endl;
  std::cout<< 383 << " " << betaerror1[(*dep)][0] << " " << betaerror1[(*dep)][1]<<" " << betaerror1[(*dep)][2] << " " << betaerror1[(*dep)][3] << " " << betaerror1[(*dep)][4] << " " <<betaerror1[(*dep)][5] << std::endl;
  std::cout<< 400 <<" " << betaerror1[(*dep)][6] << " " <<betaerror1[(*dep)][7]<<" " << betaerror1[(*dep)][8] << " " << betaerror1[(*dep)][9] <<  " " <<betaerror1[(*dep)][10] << " " <<betaerror1[(*dep)][11] << std::endl;
  std::cout<< 470 << " " <<betaerror1[(*dep)][12] << " " <<betaerror1[(*dep)][13]<< " " <<betaerror1[(*dep)][14] <<  " " <<betaerror1[(*dep)][15] <<  " " <<betaerror1[(*dep)][16] << " " <<betaerror1[(*dep)][17] << std::endl;
  std::cout<< 525 << " " <<betaerror1[(*dep)][18] << " " <<betaerror1[(*dep)][19]<< " " <<betaerror1[(*dep)][20] <<  " " <<betaerror1[(*dep)][21] <<  " " <<betaerror1[(*dep)][22] << " " <<betaerror1[(*dep)][23] << std::endl;
  std::cout<< 375 << " " << betaerror1[(*dep)][24] << " " << betaerror1[(*dep)][25]<<" " << betaerror1[(*dep)][26] << " " << betaerror1[(*dep)][27] << " " << betaerror1[(*dep)][28] << " " <<betaerror1[(*dep)][29] << std::endl;
  std::cout<< 425 <<" " << betaerror1[(*dep)][30] << " " <<betaerror1[(*dep)][31]<<" " << betaerror1[(*dep)][32] << " " << betaerror1[(*dep)][33] <<  " " <<betaerror1[(*dep)][34] << " " <<betaerror1[(*dep)][35] << std::endl;
  std::cout<< 450 << " " <<betaerror1[(*dep)][36] << " " <<betaerror1[(*dep)][37]<< " " <<betaerror1[(*dep)][38] <<  " " <<betaerror1[(*dep)][39] <<  " " <<betaerror1[(*dep)][40] << " " <<betaerror1[(*dep)][41] << std::endl;
  std::cout<< 495 << " " <<betaerror1[(*dep)][42] << " " <<betaerror1[(*dep)][43]<< " " <<betaerror1[(*dep)][44] <<  " " <<betaerror1[(*dep)][45] <<  " " <<betaerror1[(*dep)][46] << " " <<betaerror1[(*dep)][47] << std::endl;

  std::cout<< "---------------------------------------------" << std::endl;


  } // End on loop over Depths


//   //Transmission Length Useful Parameters Filling
//   std::vector<double> y10_15; std::vector<double> x10_15; std::vector<double> dy10_15; std::vector<double> dx10_15;
//   std::vector<double> y10_17; std::vector<double> x10_17; std::vector<double> dy10_17; std::vector<double> dx10_17;
//   std::vector<double> y10_22; std::vector<double> x10_22; std::vector<double> dy10_22; std::vector<double> dx10_22;
//   std::vector<double> y15_17; std::vector<double> x15_17; std::vector<double> dy15_17; std::vector<double> dx15_17;
//   std::vector<double> y15_22; std::vector<double> x15_22; std::vector<double> dy15_22; std::vector<double> dx15_22;
//   std::vector<double> y17_22; std::vector<double> x17_22; std::vector<double> dy17_22; std::vector<double> dx17_22;
  
//   for(int i=0; i<8;++i){dx10_15.push_back( 10. );}
//   for(int i=0; i<8;++i){dx10_17.push_back( 10. );}
//   for(int i=0; i<8;++i){dx10_22.push_back( 10. );}
//   for(int i=0; i<8;++i){dx15_17.push_back( 10. );}
//   for(int i=0; i<8;++i){dx15_22.push_back( 10. );}
//   for(int i=0; i<8;++i){dx17_22.push_back( 10. );}

//   y10_15.push_back( 1./beta1[0] );  x10_15.push_back( 383. ); dy10_15.push_back( betaerror1[0] * pow(1./ beta1[0],2.) );
//   y10_15.push_back( 1./beta1[6] );  x10_15.push_back( 400. ); dy10_15.push_back( betaerror1[6] * pow(1./ beta1[6],2.) );
//   y10_15.push_back( 1./beta1[12] );  x10_15.push_back( 470. ); dy10_15.push_back( betaerror1[12] * pow(1./ beta1[12],2.) );
//   y10_15.push_back( 1./beta1[18] );  x10_15.push_back( 525. ); dy10_15.push_back( betaerror1[18] * pow(1./ beta1[18],2.) );

//   y10_17.push_back( 1./beta1[1] );  x10_17.push_back( 383. ); dy10_17.push_back( betaerror1[1] *  pow(1./beta1[1],2.) );
//   y10_17.push_back( 1./beta1[7] );  x10_17.push_back( 400. ); dy10_17.push_back( betaerror1[7] *  pow(1./beta1[7],2.) );
//   y10_17.push_back( 1./beta1[13] );  x10_17.push_back( 470. ); dy10_17.push_back( betaerror1[13] *  pow(1./beta1[13],2.) );
//   y10_17.push_back( 1./beta1[19] );  x10_17.push_back( 525. ); dy10_17.push_back( betaerror1[19] *  pow(1./beta1[19],2.) );

//   y10_22.push_back( 1./beta1[2] );  x10_22.push_back( 383. );  dy10_22.push_back( betaerror1[2] * pow(1./beta1[2],2.) );
//   y10_22.push_back( 1./beta1[8] );  x10_22.push_back( 400. );  dy10_22.push_back( betaerror1[8] * pow(1./beta1[8],2.) );
//   y10_22.push_back( 1./beta1[14] );  x10_22.push_back( 470. ); dy10_22.push_back( betaerror1[14] * pow(1./beta1[14],2.) );
//   y10_22.push_back( 1./beta1[20] );  x10_22.push_back( 525. ); dy10_22.push_back( betaerror1[20] * pow(1./beta1[20],2.) );

//   y15_17.push_back( 1./beta1[3] );  x15_17.push_back( 383. ); dy15_17.push_back( betaerror1[3] *  pow(1./beta1[3],2.) );
//   y15_17.push_back( 1./beta1[9] );  x15_17.push_back( 400. ); dy15_17.push_back( betaerror1[9] *  pow(1./beta1[9],2.) );
//   y15_17.push_back( 1./beta1[15] );  x15_17.push_back( 470. ); dy15_17.push_back( betaerror1[15] *  pow(1./beta1[15],2.) );
//   y15_17.push_back( 1./beta1[21] );  x15_17.push_back( 525. ); dy15_17.push_back( betaerror1[21] *  pow(1./beta1[21],2.) );

//   y15_22.push_back( 1./beta1[4] );  x15_22.push_back( 383. );  dy15_22.push_back( betaerror1[4] * pow(1./beta1[4],2.) );
//   y15_22.push_back( 1./beta1[10] );  x15_22.push_back( 400. ); dy15_22.push_back( betaerror1[10] * pow(1./beta1[10],2.) );
//   y15_22.push_back( 1./beta1[16] );  x15_22.push_back( 470. ); dy15_22.push_back( betaerror1[16] * pow(1./beta1[16],2.) );
//   y15_22.push_back( 1./beta1[22] );  x15_22.push_back( 525. ); dy15_22.push_back( betaerror1[22] * pow(1./beta1[22],2.) );

//   y17_22.push_back( 1./beta1[5] );  x17_22.push_back( 383. ); dy17_22.push_back( betaerror1[5] * pow(1./beta1[5],2.) );
//   y17_22.push_back( 1./beta1[11] );  x17_22.push_back( 400. ); dy17_22.push_back( betaerror1[11] * pow(1./beta1[11],2.) );
//   y17_22.push_back( 1./beta1[17] );  x17_22.push_back( 470. ); dy17_22.push_back( betaerror1[17] * pow(1./beta1[17],2.) );
//   y17_22.push_back( 1./beta1[23] );  x17_22.push_back( 525. ); dy17_22.push_back( betaerror1[23] * pow(1./beta1[23],2.) );
  
//   //Source 2 now
//   y10_15.push_back( 1./beta1[24] );  x10_15.push_back( 375. ); dy10_15.push_back( betaerror1[24] * pow(1./ beta1[24],2.) );
//   y10_15.push_back( 1./beta1[30] );  x10_15.push_back( 425. ); dy10_15.push_back( betaerror1[30] * pow(1./ beta1[30],2.) );
//   y10_15.push_back( 1./beta1[36] );  x10_15.push_back( 450. ); dy10_15.push_back( betaerror1[36] * pow(1./ beta1[36],2.) );
//   y10_15.push_back( 1./beta1[42] );  x10_15.push_back( 495. ); dy10_15.push_back( betaerror1[42] * pow(1./ beta1[42],2.) );

//   y10_17.push_back( 1./beta1[25] );  x10_17.push_back( 375. ); dy10_17.push_back( betaerror1[25] *  pow(1./beta1[25],2.) );
//   y10_17.push_back( 1./beta1[31] );  x10_17.push_back( 425. ); dy10_17.push_back( betaerror1[31] *  pow(1./beta1[31],2.) );
//   y10_17.push_back( 1./beta1[37] );  x10_17.push_back( 450. ); dy10_17.push_back( betaerror1[37] *  pow(1./beta1[37],2.) );
//   y10_17.push_back( 1./beta1[43] );  x10_17.push_back( 495. ); dy10_17.push_back( betaerror1[43] *  pow(1./beta1[43],2.) );

//   y10_22.push_back( 1./beta1[26] );  x10_22.push_back( 375. );  dy10_22.push_back( betaerror1[26] * pow(1./beta1[26],2.) );
//   y10_22.push_back( 1./beta1[32] );  x10_22.push_back( 425. );  dy10_22.push_back( betaerror1[32] * pow(1./beta1[32],2.) );
//   y10_22.push_back( 1./beta1[38] );  x10_22.push_back( 450. ); dy10_22.push_back( betaerror1[38] * pow(1./beta1[38],2.) );
//   y10_22.push_back( 1./beta1[44] );  x10_22.push_back( 495. ); dy10_22.push_back( betaerror1[44] * pow(1./beta1[44],2.) );

//   y15_17.push_back( 1./beta1[27] );  x15_17.push_back( 375. ); dy15_17.push_back( betaerror1[27] *  pow(1./beta1[27],2.) );
//   y15_17.push_back( 1./beta1[33] );  x15_17.push_back( 425. ); dy15_17.push_back( betaerror1[33] *  pow(1./beta1[33],2.) );
//   y15_17.push_back( 1./beta1[39] );  x15_17.push_back( 450. ); dy15_17.push_back( betaerror1[39] *  pow(1./beta1[39],2.) );
//   y15_17.push_back( 1./beta1[45] );  x15_17.push_back( 495. ); dy15_17.push_back( betaerror1[45] *  pow(1./beta1[45],2.) );

//   y15_22.push_back( 1./beta1[28] );  x15_22.push_back( 375. );  dy15_22.push_back( betaerror1[28] * pow(1./beta1[28],2.) );
//   y15_22.push_back( 1./beta1[34] );  x15_22.push_back( 425. ); dy15_22.push_back( betaerror1[34] * pow(1./beta1[34],2.) );
//   y15_22.push_back( 1./beta1[40] );  x15_22.push_back( 450. ); dy15_22.push_back( betaerror1[40] * pow(1./beta1[40],2.) );
//   y15_22.push_back( 1./beta1[46] );  x15_22.push_back( 495. ); dy15_22.push_back( betaerror1[46] * pow(1./beta1[46],2.) );

//   y17_22.push_back( 1./beta1[29] );  x17_22.push_back( 375. ); dy17_22.push_back( betaerror1[29] * pow(1./beta1[29],2.) );
//   y17_22.push_back( 1./beta1[35] );  x17_22.push_back( 425. ); dy17_22.push_back( betaerror1[35] * pow(1./beta1[35],2.) );
//   y17_22.push_back( 1./beta1[41] );  x17_22.push_back( 450. ); dy17_22.push_back( betaerror1[41] * pow(1./beta1[41],2.) );
//   y17_22.push_back( 1./beta1[47] );  x17_22.push_back( 495. ); dy17_22.push_back( betaerror1[47] * pow(1./beta1[47],2.) );


//   TCanvas *c1 = new TCanvas("c1");

//   TGraphErrors *gr17_22 = new TGraphErrors( 8, &x17_22[0], &y17_22[0],&dx17_22[0], &dy17_22[0] ); 
//   gr17_22->SetMarkerStyle(25); 
//   gr17_22->SetMarkerSize(1.4); 
// //   gr17_22->SetMarkerColor(7);  
//   gr17_22->Draw("AP");
//   gStyle->SetOptStat(1);
//   c1->Update();

//   TGraphErrors *gr10_15 = new TGraphErrors( 8,  &x10_15[0], &y10_15[0], &dx10_15[0], &dy10_15[0] ); 
//   gr10_15->SetMarkerStyle(29); 
//   gr10_15->SetMarkerSize(1.4); 
// //   gr10_15->SetMarkerColor(2);  
//   gr10_15->Draw("SP");
//   c1->Update();

//   TGraphErrors *gr10_17 = new TGraphErrors( 8, &x10_17[0], &y10_17[0],&dx10_17[0], &dy10_17[0] ); 
//   gr10_17->SetMarkerStyle(20); 
//   gr10_17->SetMarkerSize(1.4); 
// //   gr10_17->SetMarkerColor(3);  
//   gr10_17->Draw("SP");
//   c1->Update();


//   TGraphErrors *gr10_22 =  new TGraphErrors( 8, &x10_22[0], &y10_22[0],&dx10_22[0], &dy10_22[0] ); 
//   gr10_22->SetMarkerStyle(21); 
//   gr10_22->SetMarkerSize(1.4); 
// //   gr10_22->SetMarkerColor(4);  
//   gr10_22->Draw("PS");
//   c1->Update();
  
//   TGraphErrors *gr15_17 =  new TGraphErrors( 8, &x15_17[0], &y15_17[0],&dx15_17[0], &dy15_17[0] ); 
//   gr15_17->SetMarkerStyle(22); 
//   gr15_17->SetMarkerSize(1.4); 
// //   gr15_17->SetMarkerColor(5);  
//   gr15_17->Draw("PS");
//   c1->Update();
  
//   TGraphErrors *gr15_22 =  new TGraphErrors( 8, &x15_22[0], &y15_22[0],&dx15_22[0], &dy15_22[0] ); 
//   gr15_22->SetMarkerStyle(27); 
//   gr15_22->SetMarkerSize(1.4); 
// //   gr15_22->SetMarkerColor(6);  
//   gr15_22->Draw("PS");
//   c1->Update();

//   TLegend *leg = new TLegend(0.8,0.7,0.89,0.89);  //coordinates are fractions
//                                          //of pad dimensions
//   leg->AddEntry(gr10_15,"(15-10) m","P");  
//   leg->AddEntry(gr10_17,"(17-10) m","P");  
//   leg->AddEntry(gr10_22,"(22-10) m","P");  
//   leg->AddEntry(gr15_17,"(17-15) m","P");  
//   leg->AddEntry(gr15_22,"(22-15) m","P");  
//   leg->AddEntry(gr17_22,"(22-17) m","P");  // "l" means line
// //   leg->SetHeader("The Legend Title");
//                                             // use "f" for a box
//   leg->Draw("PS");
//   c1->Update();


//   gr17_22 -> SetTitle( " L = f (#lambda) Depth 4100 m Photodiode 1");

//   gr17_22->GetHistogram()->SetXTitle("Wavelength (nm)");
//   gr17_22->GetHistogram()->SetYTitle("Transmission Length L (m)");
//   gStyle->SetOptStat(1);
//   c1->Update();

//   double xinitbin   = 0.;
//   double xfinbin    = 15.;
//   int xtotalbins    = 100;
//   //Histos for Beta Photodiode 1 
//   TH2F *beta1led383= new TH2F(" Beta Ph1 LED 383 " , " Beta Values For 383nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta1led383 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta1led383 ->SetYTitle(" #beta (1/m) ");
//   beta1led383->SetMarkerStyle(kFullCircle);

//   beta1led383 -> Fill(5.,beta1[0]);
//   beta1led383 -> Fill(7.,beta1[1]);
//   beta1led383 -> Fill(12.,beta1[2]);
//   beta1led383 -> Fill(2.,beta1[3]);
//   beta1led383 -> Fill(7.,beta1[4]);
//   beta1led383 -> Fill(12.,beta1[5]);

//   TH2F *beta1led400= new TH2F(" Beta Ph1 LED 400 " , " Beta Values For 400nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta1led400 ->SetXTitle(" R_{L}-R_{S} (m) ");
//   beta1led400 ->SetYTitle(" #beta (1/m) ");
//   beta1led400->SetMarkerStyle(kFullCircle);

//   beta1led400 -> Fill(5.,beta1[6]);
//   beta1led400 -> Fill(7.,beta1[7]);
//   beta1led400 -> Fill(12.,beta1[8]);
//   beta1led400 -> Fill(2.,beta1[9]);
//   beta1led400 -> Fill(7.,beta1[10]);
//   beta1led400 -> Fill(12.,beta1[11]);

//   TH2F *beta1led470= new TH2F(" Beta Ph1 LED 470 " , " Beta Values For 470nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta1led470 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta1led470 ->SetYTitle(" #beta (1/m) ");
//   beta1led470->SetMarkerStyle(kFullCircle);

//   beta1led470 -> Fill(5.,beta1[12]);
//   beta1led470 -> Fill(7.,beta1[13]);
//   beta1led470 -> Fill(12.,beta1[14]);
//   beta1led470 -> Fill(2.,beta1[15]);
//   beta1led470 -> Fill(7.,beta1[16]);
//   beta1led470 -> Fill(12.,beta1[17]);

//   TH2F *beta1led525= new TH2F(" Beta Ph1 LED 525 " , " Beta Values For 525nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta1led525 ->SetXTitle(" R_{L}-R_{S} (m) ");
//   beta1led525 ->SetYTitle(" #beta (1/m) ");
//   beta1led525->SetMarkerStyle(kFullCircle);

//   beta1led525 -> Fill(5.,beta1[18]);
//   beta1led525 -> Fill(7.,beta1[19]);
//   beta1led525 -> Fill(12.,beta1[20]);
//   beta1led525 -> Fill(2.,beta1[21]);
//   beta1led525 -> Fill(7.,beta1[22]);
//   beta1led525 -> Fill(12.,beta1[23]);

//   //Now the second source
//   TH2F *beta1led375= new TH2F(" Beta Ph1 LED 375 " , " Beta Values For 375nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta1led375 ->SetXTitle(" R_{L}-R_{S} (m) ");
//   beta1led375 ->SetYTitle(" #beta (1/m) ");
//   beta1led375->SetMarkerStyle(kFullCircle);

//   beta1led375 -> Fill(5.,beta1[24]);
//   beta1led375 -> Fill(7.,beta1[25]);
//   beta1led375 -> Fill(12.,beta1[26]);
//   beta1led375 -> Fill(2.,beta1[27]);
//   beta1led375 -> Fill(7.,beta1[28]);
//   beta1led375 -> Fill(12.,beta1[29]);

//   TH2F *beta1led425= new TH2F(" Beta Ph1 LED 425 " , " Beta Values For 425nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta1led425 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta1led425 ->SetYTitle(" #beta (1/m)  ");
//   beta1led425->SetMarkerStyle(kFullCircle);

//   beta1led425 -> Fill(5.,beta1[30]);
//   beta1led425 -> Fill(7.,beta1[31]);
//   beta1led425 -> Fill(12.,beta1[32]);
//   beta1led425 -> Fill(2.,beta1[33]);
//   beta1led425 -> Fill(7.,beta1[34]);
//   beta1led425 -> Fill(12.,beta1[35]);

//   TH2F *beta1led450= new TH2F(" Beta Ph1 LED 450 " , " Beta Values For 450nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta1led450 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta1led450 ->SetYTitle(" #beta (1/m)  ");
//   beta1led450->SetMarkerStyle(kFullCircle);

//   beta1led450 -> Fill(5.,beta1[36]);
//   beta1led450 -> Fill(7.,beta1[37]);
//   beta1led450 -> Fill(12.,beta1[38]);
//   beta1led450 -> Fill(2.,beta1[39]);
//   beta1led450 -> Fill(7.,beta1[40]);
//   beta1led450 -> Fill(12.,beta1[41]);

//   TH2F *beta1led495= new TH2F(" Beta Ph1 LED 495 " , " Beta Values For 495nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta1led495 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta1led495 ->SetYTitle(" #beta (1/m)  ");
//   beta1led495->SetMarkerStyle(kFullCircle);

//   beta1led495 -> Fill(5.,beta1[42]);
//   beta1led495 -> Fill(7.,beta1[43]);
//   beta1led495 -> Fill(12.,beta1[44]);
//   beta1led495 -> Fill(2.,beta1[45]);
//   beta1led495 -> Fill(7.,beta1[46]);
//   beta1led495 -> Fill(12.,beta1[47]);

//   //Beta as a function of the wavelength for the first photodiode
//   TH2F *beta1allled= new TH2F("PhotoDiode 1", " L = f (#lambda)" , 100 , 350.,550.,100, 0.,100.);
//   beta1allled ->SetXTitle(" Wavelength (nm) ");
//   beta1allled ->SetYTitle(" Transmission Length L (m)");

//   for (int i=0;i<6;++i){ beta1allled -> Fill( 383. ,1./beta1[i]); }
//   for (int i=6;i<12;++i){ beta1allled -> Fill( 400. ,1./beta1[i]); }
//   for (int i=12;i<18;++i){ beta1allled -> Fill( 470. ,1./beta1[i]); }
//   for (int i=18;i<24;++i){ beta1allled -> Fill( 525. ,1./beta1[i]); }
//   for (int i=24;i<30;++i){ beta1allled -> Fill( 375. ,1./beta1[i]); }
//   for (int i=30;i<36;++i){ beta1allled -> Fill( 425. ,1./beta1[i]); }
//   for (int i=36;i<42;++i){ beta1allled -> Fill( 450. ,1./beta1[i]); }
//   for (int i=42;i<48;++i){ beta1allled -> Fill( 495. ,1./beta1[i]); }

  // Create a file

  std::map<int,std::map<double,double> > fitlength383; 
  std::map<int,std::map<double,double> > fitlength400; 
  std::map<int,std::map<double,double> > fitlength470; 
  std::map<int,std::map<double,double> > fitlength525; 
  std::map<int,std::map<double,double> > fitlength375; 
  std::map<int,std::map<double,double> > fitlength425;
  std::map<int,std::map<double,double> > fitlength450; 
  std::map<int,std::map<double,double> > fitlength495;

  std::map<int,std::vector<TransmissionLength> > trleng;

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

    fitlength383[(*dep)] = fitbetamethodph1(led383int1[(*dep)],led383intrms1[(*dep)]);
    fitlength400[(*dep)] = fitbetamethodph1(led400int1[(*dep)],led400intrms1[(*dep)]);
    fitlength470[(*dep)] = fitbetamethodph1(led470int1[(*dep)],led470intrms1[(*dep)]);
    fitlength525[(*dep)] = fitbetamethodph1(led525int1[(*dep)],led525intrms1[(*dep)]);
    fitlength375[(*dep)] = fitbetamethodph1(led375int1[(*dep)],led375intrms1[(*dep)]);
    fitlength425[(*dep)] = fitbetamethodph1(led425int1[(*dep)],led425intrms1[(*dep)]);
    fitlength450[(*dep)] = fitbetamethodph1(led450int1[(*dep)],led450intrms1[(*dep)]);
    fitlength495[(*dep)] = fitbetamethodph1(led495int1[(*dep)],led495intrms1[(*dep)]);

//     std::cout<< " Photodiode 1 Intensity in " << (*dep) << " m for 10,15,17,22 m" <<std::endl;
//     std::cout<< 375 << " " << led375int1[(*dep)][10]  << " "<< led375int1[(*dep)][15]  << " "<< led375int1[(*dep)][17] << " " << led375int1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 383 << led383int1[(*dep)][10] << " " << led383int1[(*dep)][15] << " " << led383int1[(*dep)][17] << " " << led383int1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 400  << " "<< led400int1[(*dep)][10] << " " << led400int1[(*dep)][15] << " " << led400int1[(*dep)][17] << " " << led400int1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 425 << " " << led425int1[(*dep)][10] << " " << led425int1[(*dep)][15] << " " << led425int1[(*dep)][17] << " " << led425int1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 450 << " " << led450int1[(*dep)][10] << " " << led450int1[(*dep)][15] << " " << led450int1[(*dep)][17] << " " << led450int1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 470 << " " << led470int1[(*dep)][10] << " " << led470int1[(*dep)][15] << " " << led470int1[(*dep)][17] << " " << led470int1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 495 << " " << led495int1[(*dep)][10] << " " << led495int1[(*dep)][15] << " " << led495int1[(*dep)][17] << " " << led495int1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 525 << " " << led525int1[(*dep)][10] << " " << led525int1[(*dep)][15] << " " << led525int1[(*dep)][17] << " " << led525int1[(*dep)][22] << " " <<std::endl;
//     std::cout<< " Photodiode 1 Intensity RMS in " << (*dep) << " m for 10,15,17,22 m" <<std::endl;
//     std::cout<< 375 << " " << led375intrms1[(*dep)][10]  << " "<< led375intrms1[(*dep)][15]  << " "<< led375intrms1[(*dep)][17] << " " << led375intrms1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 383 << led383intrms1[(*dep)][10] << " " << led383intrms1[(*dep)][15] << " " << led383intrms1[(*dep)][17] << " " << led383intrms1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 400  << " "<< led400intrms1[(*dep)][10] << " " << led400intrms1[(*dep)][15] << " " << led400intrms1[(*dep)][17] << " " << led400intrms1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 425 << " " << led425intrms1[(*dep)][10] << " " << led425intrms1[(*dep)][15] << " " << led425intrms1[(*dep)][17] << " " << led425intrms1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 450 << " " << led450intrms1[(*dep)][10] << " " << led450intrms1[(*dep)][15] << " " << led450intrms1[(*dep)][17] << " " << led450intrms1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 470 << " " << led470intrms1[(*dep)][10] << " " << led470intrms1[(*dep)][15] << " " << led470intrms1[(*dep)][17] << " " << led470intrms1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 495 << " " << led495intrms1[(*dep)][10] << " " << led495intrms1[(*dep)][15] << " " << led495intrms1[(*dep)][17] << " " << led495intrms1[(*dep)][22] << " " <<std::endl;
//     std::cout<< 525 << " " << led525intrms1[(*dep)][10] << " " << led525intrms1[(*dep)][15] << " " << led525intrms1[(*dep)][17] << " " << led525intrms1[(*dep)][22] << " " <<std::endl;
//     std::cout<< "-------------------------------------------------------------------------------------------"<<std::endl;

  for (std::map<double,double>::iterator it =fitlength383[(*dep)].begin();it!=fitlength383[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 383. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength400[(*dep)].begin();it!=fitlength400[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 400. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength470[(*dep)].begin();it!=fitlength470[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 470. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength525[(*dep)].begin();it!=fitlength525[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 525. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength375[(*dep)].begin();it!=fitlength375[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 375. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength425[(*dep)].begin();it!=fitlength425[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 425. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength450[(*dep)].begin();it!=fitlength450[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 450. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength495[(*dep)].begin();it!=fitlength495[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 495. , (*it).first,(*it).second ) );
  }

  } // End on loop over Depths

//   ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 470 nm////////////////////////////////////////////// 
//   TCanvas *c5 = new TCanvas("c5");
  
//   TGraphErrors *bvsd470 = betavsdepth( 470, trleng );
//   bvsd470->SetMarkerStyle(20);//circle full 
//   bvsd470->SetMarkerSize(0.9); 
//   bvsd470->Draw("AP");
//   c5->Update();

//   bvsd470-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 470 nm Photodiode 1 ");

//   bvsd470->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd470->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd470->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd470->GetXaxis()->SetRangeUser(400.,4400.);
//   c5->Update();

//   ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 450 nm////////////////////////////////////////////// 

//   TCanvas *c4 = new TCanvas("c4");
  
//   TGraphErrors *bvsd450 = betavsdepth( 450, trleng );
//   bvsd450->SetMarkerStyle(20);//circle full 
//   bvsd450->SetMarkerSize(0.9); 
//   bvsd450->Draw("AP");
//   c4->Update();

//   bvsd450-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 450 nm Photodiode 1 ");

//   bvsd450->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd450->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd450->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd450->GetXaxis()->SetRangeUser(400.,4400.);
//   c4->Update();

//    ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 375 nm////////////////////////////////////////////// 

//   TCanvas *c6 = new TCanvas("c6");
  
//   TGraphErrors *bvsd375 = betavsdepth( 375, trleng );
//   bvsd375->SetMarkerStyle(20);//circle full 
//   bvsd375->SetMarkerSize(0.9); 
//   bvsd375->Draw("AP");
//   c6->Update();

//   bvsd375-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 375 nm Photodiode 1 ");

//   bvsd375->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd375->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd375->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd375->GetXaxis()->SetRangeUser(400.,4400.);
//   c6->Update();

//    ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 383 nm////////////////////////////////////////////// 

//   TCanvas *c7 = new TCanvas("c7");
  
//   TGraphErrors *bvsd383 = betavsdepth( 383, trleng );
//   bvsd383->SetMarkerStyle(20);//circle full 
//   bvsd383->SetMarkerSize(0.9); 
//   bvsd383->Draw("AP");
//   c7->Update();

//   bvsd383-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 383 nm Photodiode 1 ");

//   bvsd383->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd383->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd383->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd383->GetXaxis()->SetRangeUser(400.,4400.);
//   c7->Update();

//    ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 400 nm////////////////////////////////////////////// 

//   TCanvas *c8 = new TCanvas("c8");
  
//   TGraphErrors *bvsd400 = betavsdepth( 400, trleng );
//   bvsd400->SetMarkerStyle(20);//circle full 
//   bvsd400->SetMarkerSize(0.9); 
//   bvsd400->Draw("AP");
//   c8->Update();

//   bvsd400-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 400 nm Photodiode 1 ");

//   bvsd400->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd400->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd400->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd400->GetXaxis()->SetRangeUser(400.,4400.);
//   c8->Update();

//    ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 425 nm////////////////////////////////////////////// 

//   TCanvas *c9 = new TCanvas("c9");
  
//   TGraphErrors *bvsd425 = betavsdepth( 425, trleng );
//   bvsd425->SetMarkerStyle(20);//circle full 
//   bvsd425->SetMarkerSize(0.9); 
//   bvsd425->Draw("AP");
//   c9->Update();

//   bvsd425-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 425 nm Photodiode 1 ");

//   bvsd425->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd425->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd425->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd425->GetXaxis()->SetRangeUser(400.,4400.);
//   c9->Update();
//    ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 495 nm////////////////////////////////////////////// 

//   TCanvas *c10 = new TCanvas("c10");
  
//   TGraphErrors *bvsd495 = betavsdepth( 495, trleng );
//   bvsd495->SetMarkerStyle(20);//circle full 
//   bvsd495->SetMarkerSize(0.9); 
//   bvsd495->Draw("AP");
//   c10->Update();

//   bvsd495-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 495 nm Photodiode 1 ");

//   bvsd495->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd495->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd495->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd495->GetXaxis()->SetRangeUser(400.,4400.);
//   c10->Update();
//    ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 525 nm////////////////////////////////////////////// 

//   TCanvas *c11 = new TCanvas("c11");
  
//   TGraphErrors *bvsd525 = betavsdepth( 525, trleng );
//   bvsd525->SetMarkerStyle(20);//circle full 
//   bvsd525->SetMarkerSize(0.9); 
//   bvsd525->Draw("AP");
//   c11->Update();

//   bvsd525-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 525 nm Photodiode 1 ");

//   bvsd525->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd525->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd525->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd525->GetXaxis()->SetRangeUser(400.,4400.);
//   c11->Update();


  ///////////////////////////////Transmission Length Sinartisi WaveLength 2500,3400,4100m////////////////////////////////////////////// 
  TCanvas *c3_2500_3400_4100 = new TCanvas("c3_2500_3400_4100");
   
  TGraphErrors *translength4100 = fitbetamethodgrapherrorph1( trleng[4100] );
  translength4100->SetMarkerStyle(20);//circle full 
  translength4100->SetMarkerSize(0.9); 
  translength4100->SetMarkerColor(2);//red  
  translength4100->SetLineColor(2);
  translength4100->Draw("AP");
  c3_2500_3400_4100->Update();

  TGraphErrors *translength3400 = fitbetamethodgrapherrorph1( trleng[3400] );
  translength3400->SetMarkerStyle(29);//star full 
  translength3400->SetMarkerSize(0.9); 
  translength3400->SetMarkerColor(4);//blue  
  translength3400->SetLineColor(4);
  translength3400->Draw("PS");
  c3_2500_3400_4100->Update();

  TGraphErrors *translength2500 = fitbetamethodgrapherrorph1( trleng[2500] );
  translength2500->SetMarkerStyle(22);// triangle full 
  translength2500->SetMarkerSize(0.9); 
  translength2500->SetMarkerColor(8);//green  
  translength2500->SetLineColor(8);
  translength2500->Draw("PS");
  c3_2500_3400_4100->Update();

  TLegend *leg_2500_3400_4100 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_2500_3400_4100->AddEntry(translength4100,"4100 m","LP");  
  leg_2500_3400_4100->AddEntry(translength3400,"3400 m","LP");  
  leg_2500_3400_4100->AddEntry(translength2500,"2500 m","LP");  
  leg_2500_3400_4100->SetFillColor(18);
  leg_2500_3400_4100->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_2500_3400_4100->Draw("PS");
  c3_2500_3400_4100->Update();

  translength4100 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 1");

  translength4100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength4100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength4100 ->GetYaxis()->SetRangeUser(15.,50.);
  translength4100 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_2500_3400_4100->Update();

  /////////////Transmission Length Sinartisi WaveLength 500-1000,1000-1500,1500-2000m////////////////////////////////////////////// 
  TCanvas *c3_500_2000 = new TCanvas("c3_500_2000");
   
  TGraphErrors *translength15002000 = fitbetamethodgrapherrorph1( trleng[15002000] );
  translength15002000->SetMarkerStyle(20);//circle full 
  translength15002000->SetMarkerSize(0.9); 
  translength15002000->SetMarkerColor(2);//red  
  translength15002000->SetLineColor(2);
  translength15002000->Draw("AP");
  c3_500_2000->Update();

  TGraphErrors *translength10001500 = fitbetamethodgrapherrorph1( trleng[10001500] );
  translength10001500->SetMarkerStyle(29);//star full 
  translength10001500->SetMarkerSize(0.9); 
  translength10001500->SetMarkerColor(4);//blue  
  translength10001500->SetLineColor(4);
  translength10001500->Draw("PS");
  c3_500_2000->Update();

  TGraphErrors *translength5001000 = fitbetamethodgrapherrorph1( trleng[5001000] );
  translength5001000->SetMarkerStyle(22);// triangle full 
  translength5001000->SetMarkerSize(0.9); 
  translength5001000->SetMarkerColor(8);//green  
  translength5001000->SetLineColor(8);
  translength5001000->Draw("PS");
  c3_500_2000->Update();

  TLegend *leg_500_2000 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_500_2000->AddEntry(translength15002000,"1500-2000 m","LP");  
  leg_500_2000->AddEntry(translength10001500,"1000-1500 m","LP");  
  leg_500_2000->AddEntry(translength5001000,"500-1000 m","LP");  
  leg_500_2000->SetFillColor(18);
  leg_500_2000->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_500_2000->Draw("PS");
  c3_500_2000->Update();

  translength15002000 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 1");

  translength15002000 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength15002000 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength15002000 ->GetYaxis()->SetRangeUser(15.,50.);
  translength15002000 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_500_2000->Update();

  /////////////Transmission Length Sinartisi WaveLength 2000-2500,2500-3400,3400-4100m////////////////////////////////////////////// 
  TCanvas *c3_2000_4100 = new TCanvas("c3_2000_4100");
   
  TGraphErrors *translength34004100 = fitbetamethodgrapherrorph1( trleng[34004100] );
  translength34004100->SetMarkerStyle(20);//circle full 
  translength34004100->SetMarkerSize(0.9); 
  translength34004100->SetMarkerColor(2);//red  
  translength34004100->SetLineColor(2);
  translength34004100->Draw("AP");
  c3_2000_4100->Update();

  TGraphErrors *translength25003400 = fitbetamethodgrapherrorph1( trleng[25003400] );
  translength25003400->SetMarkerStyle(29);//star full 
  translength25003400->SetMarkerSize(0.9); 
  translength25003400->SetMarkerColor(4);//blue  
  translength25003400->SetLineColor(4);
  translength25003400->Draw("PS");
  c3_2000_4100->Update();

  TGraphErrors *translength20002500 = fitbetamethodgrapherrorph1( trleng[20002500] );
  translength20002500->SetMarkerStyle(22);// triangle full 
  translength20002500->SetMarkerSize(0.9); 
  translength20002500->SetMarkerColor(8);//green  
  translength20002500->SetLineColor(8);
  translength20002500->Draw("PS");
  c3_2000_4100->Update();

  TLegend *leg_2000_4100 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_2000_4100->AddEntry(translength34004100,"3400-4100 m","LP");  
  leg_2000_4100->AddEntry(translength25003400,"2500-3400 m","LP");  
  leg_2000_4100->AddEntry(translength20002500,"2000-2500 m","LP");  
  leg_2000_4100->SetFillColor(18);
  leg_2000_4100->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_2000_4100->Draw("PS");
  c3_2000_4100->Update();

  translength34004100 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 1");

  translength34004100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength34004100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength34004100 ->GetYaxis()->SetRangeUser(15.,50.);
  translength34004100 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_2000_4100->Update();

  /////////////Transmission Length Sinartisi WaveLength 4100-3400,3400-2500,2500-2000m////////////////////////////////////////////// 

  TCanvas *c3_4100_2000 = new TCanvas("c3_4100_2000");
   
   TGraphErrors *translength41003400 = fitbetamethodgrapherrorph1( trleng[41003400] );
  translength41003400->SetMarkerStyle(20);//circle full 
  translength41003400->SetMarkerSize(0.9); 
  translength41003400->SetMarkerColor(2);//red  
  translength41003400->SetLineColor(2);
  translength41003400->Draw("AP");
  c3_4100_2000->Update();

  TGraphErrors *translength34002500 = fitbetamethodgrapherrorph1( trleng[34002500] );
  translength34002500->SetMarkerStyle(29);//star full 
  translength34002500->SetMarkerSize(0.9); 
  translength34002500->SetMarkerColor(4);//blue  
  translength34002500->SetLineColor(4);
  translength34002500->Draw("PS");
  c3_4100_2000->Update();

  TGraphErrors *translength25002000 = fitbetamethodgrapherrorph1( trleng[25002000] );
  translength25002000->SetMarkerStyle(22);// triangle full 
  translength25002000->SetMarkerSize(0.9); 
  translength25002000->SetMarkerColor(8);//green  
  translength25002000->SetLineColor(8);
  translength25002000->Draw("PS");
  c3_4100_2000->Update();

  TLegend *leg_4100_2000 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_4100_2000->AddEntry(translength41003400,"4100-3400 m","LP");  
  leg_4100_2000->AddEntry(translength34002500,"3400-2500 m","LP");  
  leg_4100_2000->AddEntry(translength25002000,"2500-2000 m","LP");  
  leg_4100_2000->SetFillColor(18);
  leg_4100_2000->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_4100_2000->Draw("PS");
  c3_4100_2000->Update();

  translength41003400 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 1");

  translength41003400 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength41003400 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength41003400 ->GetYaxis()->SetRangeUser(15.,50.);
  translength41003400 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_4100_2000->Update();

  /////////////Transmission Length Sinartisi WaveLength 2000-500m////////////////////////////////////////////// 

  TCanvas *c3_2000_500 = new TCanvas("c3_2000_500");
   
  TGraphErrors *translength20001500 = fitbetamethodgrapherrorph1( trleng[20001500] );
  translength20001500->SetMarkerStyle(20);//circle full 
  translength20001500->SetMarkerSize(0.9); 
  translength20001500->SetMarkerColor(2);//red  
  translength20001500->SetLineColor(2);
  translength20001500->Draw("AP");
  c3_2000_500->Update();

  TGraphErrors *translength15001000 = fitbetamethodgrapherrorph1( trleng[15001000] );
  translength15001000->SetMarkerStyle(29);//star full 
  translength15001000->SetMarkerSize(0.9); 
  translength15001000->SetMarkerColor(4);//blue  
  translength15001000->SetLineColor(4);
  translength15001000->Draw("PS");
  c3_2000_500->Update();

  TGraphErrors *translength1000500 = fitbetamethodgrapherrorph1( trleng[1000500] );
  translength1000500->SetMarkerStyle(22);// triangle full 
  translength1000500->SetMarkerSize(0.9); 
  translength1000500->SetMarkerColor(8);//green  
  translength1000500->SetLineColor(8);
  translength1000500->Draw("PS");
  c3_2000_500->Update();

  TLegend *leg_2000_500 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_2000_500->AddEntry(translength20001500,"2000-1500 m","LP");  
  leg_2000_500->AddEntry(translength15001000,"1500-1000 m","LP");  
  leg_2000_500->AddEntry(translength1000500,"1000-500 m","LP");  
  leg_2000_500->SetFillColor(18);
  leg_2000_500->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_2000_500->Draw("PS");
  c3_2000_500->Update();

  translength20001500 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 1");

  translength20001500 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength20001500 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength20001500 ->GetYaxis()->SetRangeUser(15.,50.);
  translength20001500 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_2000_500->Update();



  TFile f("BetaHistosPH_1.root","recreate");
 //  beta1led375->Write();beta1led425->Write();beta1led450->Write();beta1led495->Write();
//   beta1led383->Write();beta1led400->Write();beta1led470->Write();beta1led525->Write();
//   beta1allled->Write();
  c3_2500_3400_4100->Write();c3_500_2000->Write();c3_2000_4100->Write();c3_4100_2000->Write();c3_2000_500->Write();
//   c4->Write();c5->Write();
  f.Close();
//   delete beta1led383;
//   delete beta1led400;
//   delete beta1led470;
//   delete beta1led525;
//   delete beta1led375;
//   delete beta1led425;
//   delete beta1led450;
//   delete beta1led495;
//   delete beta1allled;
  delete c3_2500_3400_4100;
  delete c3_500_2000;
  delete c3_2000_4100;
  delete c3_4100_2000;
  delete c3_2000_500;
//   delete c4;
//   delete c5;
//   delete c6;
//   delete c7;
//   delete c8;
//   delete c9;
//   delete c10;
//   delete c11;
//   delete gr10_15;
//   delete gr10_17;
//   delete gr10_22;
//   delete gr15_17;
//   delete gr15_22;
//   delete gr17_22;
  delete translength4100;
  delete translength3400;
  delete translength2500;
  delete translength41003400;
  delete translength34002500;
  delete translength25002000;
  delete translength20001500;
  delete translength15001000;
  delete translength1000500;
//   delete bvsd450;
//   delete bvsd470;
  delete leg_2500_3400_4100;
  delete leg_500_2000;
  delete leg_2000_4100;
  delete leg_4100_2000;
  delete leg_2000_500;
}



void BetaCalculation::calculateph2 ( std::map<int, std::map<int, double> >& led383int2, std::map<int, std::map<int, double> >& led400int2, std::map<int, std::map<int, double> >& led470int2, std::map<int, std::map<int, double> >& led525int2 , std::map<int, std::map<int, double> >& led383intrms2, std::map<int, std::map<int, double> >& led400intrms2, std::map<int, std::map<int, double> >& led470intrms2, std::map<int, std::map<int, double> >& led525intrms2,std::map<int, std::map<int, double> >& led375int2, std::map<int, std::map<int, double> >& led425int2, std::map<int, std::map<int, double> >& led450int2, std::map<int, std::map<int, double> >& led495int2, std::map<int, std::map<int, double> >& led375intrms2, std::map<int, std::map<int, double> >& led425intrms2, std::map<int, std::map<int, double> >& led450intrms2, std::map<int, std::map<int, double> >& led495intrms2)
{

 std::map<int,std::vector<double> > beta2; std::map<int, std::vector<double> > betaerror2; 
  double a1;  

  //Depths that will be processed
  std::vector<int> DepthsToBeProccessed;

  DepthsToBeProccessed.push_back(4100);
  DepthsToBeProccessed.push_back(3400);
  DepthsToBeProccessed.push_back(2500);
  DepthsToBeProccessed.push_back(5001000);
  DepthsToBeProccessed.push_back(10001500);
  DepthsToBeProccessed.push_back(15002000);
  DepthsToBeProccessed.push_back(20002500);
  DepthsToBeProccessed.push_back(25003400);
  DepthsToBeProccessed.push_back(34004100);
  DepthsToBeProccessed.push_back(25002000);
  DepthsToBeProccessed.push_back(34002500);
  DepthsToBeProccessed.push_back(41003400);
  DepthsToBeProccessed.push_back(20001500);
  DepthsToBeProccessed.push_back(15001000);
  DepthsToBeProccessed.push_back(1000500);

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

  //Error in Beta Calculation
  a1 = errorbeta(15.10, 10., led383int2[(*dep)][15], led383int2[(*dep)][10], led383intrms2[(*dep)][15], led383intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led383int2[(*dep)][17], led383int2[(*dep)][10], led383intrms2[(*dep)][17], led383intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led383int2[(*dep)][22], led383int2[(*dep)][10], led383intrms2[(*dep)][22], led383intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led383int2[(*dep)][17], led383int2[(*dep)][15], led383intrms2[(*dep)][17], led383intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led383int2[(*dep)][22], led383int2[(*dep)][15], led383intrms2[(*dep)][22], led383intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led383int2[(*dep)][22], led383int2[(*dep)][17], led383intrms2[(*dep)][22], led383intrms2[(*dep)][17] );
  betaerror2[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led400int2[(*dep)][15], led400int2[(*dep)][10], led400intrms2[(*dep)][15], led400intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led400int2[(*dep)][17], led400int2[(*dep)][10], led400intrms2[(*dep)][17], led400intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led400int2[(*dep)][22], led400int2[(*dep)][10], led400intrms2[(*dep)][22], led400intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led400int2[(*dep)][17], led400int2[(*dep)][15], led400intrms2[(*dep)][17], led400intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led400int2[(*dep)][22], led400int2[(*dep)][15], led400intrms2[(*dep)][22], led400intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led400int2[(*dep)][22], led400int2[(*dep)][17], led400intrms2[(*dep)][22], led400intrms2[(*dep)][17] );
  betaerror2[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led470int2[(*dep)][15], led470int2[(*dep)][10], led470intrms2[(*dep)][15], led470intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led470int2[(*dep)][17], led470int2[(*dep)][10], led470intrms2[(*dep)][17], led470intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led470int2[(*dep)][22], led470int2[(*dep)][10], led470intrms2[(*dep)][22], led470intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led470int2[(*dep)][17], led470int2[(*dep)][15], led470intrms2[(*dep)][17], led470intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led470int2[(*dep)][22], led470int2[(*dep)][15], led470intrms2[(*dep)][22], led470intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led470int2[(*dep)][22], led470int2[(*dep)][17], led470intrms2[(*dep)][22], led470intrms2[(*dep)][17] );
  betaerror2[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led525int2[(*dep)][15], led525int2[(*dep)][10], led525intrms2[(*dep)][15], led525intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led525int2[(*dep)][17], led525int2[(*dep)][10], led525intrms2[(*dep)][17], led525intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led525int2[(*dep)][22], led525int2[(*dep)][10], led525intrms2[(*dep)][22], led525intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led525int2[(*dep)][17], led525int2[(*dep)][15], led525intrms2[(*dep)][17], led525intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led525int2[(*dep)][22], led525int2[(*dep)][15], led525intrms2[(*dep)][22], led525intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led525int2[(*dep)][22], led525int2[(*dep)][17], led525intrms2[(*dep)][22], led525intrms2[(*dep)][17] );
  betaerror2[(*dep)].push_back( a1 );

  //Here the errors in beta from the second source

  a1 = errorbeta(15.10, 10., led375int2[(*dep)][15], led375int2[(*dep)][10], led375intrms2[(*dep)][15], led375intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led375int2[(*dep)][17], led375int2[(*dep)][10], led375intrms2[(*dep)][17], led375intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led375int2[(*dep)][22], led375int2[(*dep)][10], led375intrms2[(*dep)][22], led375intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led375int2[(*dep)][17], led375int2[(*dep)][15], led375intrms2[(*dep)][17], led375intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led375int2[(*dep)][22], led375int2[(*dep)][15], led375intrms2[(*dep)][22], led375intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led375int2[(*dep)][22], led375int2[(*dep)][17], led375intrms2[(*dep)][22], led375intrms2[(*dep)][17] );
  betaerror2[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led425int2[(*dep)][15], led425int2[(*dep)][10], led425intrms2[(*dep)][15], led425intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led425int2[(*dep)][17], led425int2[(*dep)][10], led425intrms2[(*dep)][17], led425intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led425int2[(*dep)][22], led425int2[(*dep)][10], led425intrms2[(*dep)][22], led425intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led425int2[(*dep)][17], led425int2[(*dep)][15], led425intrms2[(*dep)][17], led425intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led425int2[(*dep)][22], led425int2[(*dep)][15], led425intrms2[(*dep)][22], led425intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led425int2[(*dep)][22], led425int2[(*dep)][17], led425intrms2[(*dep)][22], led425intrms2[(*dep)][17] );
  betaerror2[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led450int2[(*dep)][15], led450int2[(*dep)][10], led450intrms2[(*dep)][15], led450intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led450int2[(*dep)][17], led450int2[(*dep)][10], led450intrms2[(*dep)][17], led450intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led450int2[(*dep)][22], led450int2[(*dep)][10], led450intrms2[(*dep)][22], led450intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led450int2[(*dep)][17], led450int2[(*dep)][15], led450intrms2[(*dep)][17], led450intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led450int2[(*dep)][22], led450int2[(*dep)][15], led450intrms2[(*dep)][22], led450intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led450int2[(*dep)][22], led450int2[(*dep)][17], led450intrms2[(*dep)][22], led450intrms2[(*dep)][17] );
  betaerror2[(*dep)].push_back( a1 );
  
  a1 = errorbeta(15.10, 10., led495int2[(*dep)][15], led495int2[(*dep)][10], led495intrms2[(*dep)][15], led495intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 10., led495int2[(*dep)][17], led495int2[(*dep)][10], led495intrms2[(*dep)][17], led495intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 10., led495int2[(*dep)][22], led495int2[(*dep)][10], led495intrms2[(*dep)][22], led495intrms2[(*dep)][10] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(17.17, 15.10, led495int2[(*dep)][17], led495int2[(*dep)][15], led495intrms2[(*dep)][17], led495intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 15.10, led495int2[(*dep)][22], led495int2[(*dep)][15], led495intrms2[(*dep)][22], led495intrms2[(*dep)][15] );
  betaerror2[(*dep)].push_back( a1 );
  a1 = errorbeta(22.27, 17.17, led495int2[(*dep)][22], led495int2[(*dep)][17], led495intrms2[(*dep)][22], led495intrms2[(*dep)][17] );
  betaerror2[(*dep)].push_back( a1 );


  //Beta Calculation
  beta2[(*dep)].push_back( (1/(15.10-10.))* ( log(led383int2[(*dep)][10])-log(led383int2[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-10.))* ( log(led383int2[(*dep)][10])-log(led383int2[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(22.27-10.))* ( log(led383int2[(*dep)][10])-log(led383int2[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-15.10))* ( log(led383int2[(*dep)][15])-log(led383int2[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-15.10))* ( log(led383int2[(*dep)][15])-log(led383int2[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-17.17))* ( log(led383int2[(*dep)][17])-log(led383int2[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta2[(*dep)].push_back( (1/(15.10-10.))* ( log(led400int2[(*dep)][10])-log(led400int2[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-10.))* ( log(led400int2[(*dep)][10])-log(led400int2[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(22.27-10.))* ( log(led400int2[(*dep)][10])-log(led400int2[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-15.10))* ( log(led400int2[(*dep)][15])-log(led400int2[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-15.10))* ( log(led400int2[(*dep)][15])-log(led400int2[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-17.17))* ( log(led400int2[(*dep)][17])-log(led400int2[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta2[(*dep)].push_back( (1/(15.10-10.))* ( log(led470int2[(*dep)][10])-log(led470int2[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-10.))* ( log(led470int2[(*dep)][10])-log(led470int2[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(22.27-10.))* ( log(led470int2[(*dep)][10])-log(led470int2[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-15.10))* ( log(led470int2[(*dep)][15])-log(led470int2[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-15.10))* ( log(led470int2[(*dep)][15])-log(led470int2[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-17.17))* ( log(led470int2[(*dep)][17])-log(led470int2[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta2[(*dep)].push_back( (1/(15.10-10.))* ( log(led525int2[(*dep)][10])-log(led525int2[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-10.))* ( log(led525int2[(*dep)][10])-log(led525int2[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(22.27-10.))* ( log(led525int2[(*dep)][10])-log(led525int2[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-15.10))* ( log(led525int2[(*dep)][15])-log(led525int2[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-15.10))* ( log(led525int2[(*dep)][15])-log(led525int2[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-17.17))* ( log(led525int2[(*dep)][17])-log(led525int2[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  //Here the beta calculation for the second source

  beta2[(*dep)].push_back( (1/(15.10-10.))* ( log(led375int2[(*dep)][10])-log(led375int2[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-10.))* ( log(led375int2[(*dep)][10])-log(led375int2[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(22.27-10.))* ( log(led375int2[(*dep)][10])-log(led375int2[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-15.10))* ( log(led375int2[(*dep)][15])-log(led375int2[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-15.10))* ( log(led375int2[(*dep)][15])-log(led375int2[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-17.17))* ( log(led375int2[(*dep)][17])-log(led375int2[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta2[(*dep)].push_back( (1/(15.10-10.))* ( log(led425int2[(*dep)][10])-log(led425int2[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-10.))* ( log(led425int2[(*dep)][10])-log(led425int2[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(22.27-10.))* ( log(led425int2[(*dep)][10])-log(led425int2[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-15.10))* ( log(led425int2[(*dep)][15])-log(led425int2[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-15.10))* ( log(led425int2[(*dep)][15])-log(led425int2[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-17.17))* ( log(led425int2[(*dep)][17])-log(led425int2[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta2[(*dep)].push_back( (1/(15.10-10.))* ( log(led450int2[(*dep)][10])-log(led450int2[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-10.))* ( log(led450int2[(*dep)][10])-log(led450int2[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(22.27-10.))* ( log(led450int2[(*dep)][10])-log(led450int2[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-15.10))* ( log(led450int2[(*dep)][15])-log(led450int2[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-15.10))* ( log(led450int2[(*dep)][15])-log(led450int2[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-17.17))* ( log(led450int2[(*dep)][17])-log(led450int2[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );

  beta2[(*dep)].push_back( (1/(15.10-10.))* ( log(led495int2[(*dep)][10])-log(led495int2[(*dep)][15])-2*(log(15.10)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-10.))* ( log(led495int2[(*dep)][10])-log(led495int2[(*dep)][17])-2*(log(17.17)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(22.27-10.))* ( log(led495int2[(*dep)][10])-log(led495int2[(*dep)][22])-2*(log(22.27)- log(10.)) ) );
  beta2[(*dep)].push_back( (1/(17.17-15.10))* ( log(led495int2[(*dep)][15])-log(led495int2[(*dep)][17])-2*(log(17.17)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-15.10))* ( log(led495int2[(*dep)][15])-log(led495int2[(*dep)][22])-2*(log(22.27)- log(15.10)) ) );
  beta2[(*dep)].push_back( (1/(22.27-17.17))* ( log(led495int2[(*dep)][17])-log(led495int2[(*dep)][22])-2*(log(22.27)- log(17.17)) ) );
  
//  Results Printing
  std::cout<< " Photodiode 2 Beta in " << (*dep) << " m" <<std::endl;
  std::cout<< "WL " << "P(10-15) " << "P(10-17) " << "P(10-22) " << "P(15-17) " << "P(15-22) "  <<  "P(17-22) " << std::endl;
  std::cout<< "---------------------------------------------" << std::endl;
  std::cout<< 383 << " " << beta2[(*dep)][0] << " " << beta2[(*dep)][1]<<" " << beta2[(*dep)][2] << " " << beta2[(*dep)][3] << " " << beta2[(*dep)][4] << " " <<beta2[(*dep)][5] << std::endl;
  std::cout<< 400 <<" " << beta2[(*dep)][6] << " " <<beta2[(*dep)][7]<<" " << beta2[(*dep)][8] << " " << beta2[(*dep)][9] <<  " " <<beta2[(*dep)][10] << " " <<beta2[(*dep)][11] << std::endl;
  std::cout<< 470 << " " <<beta2[(*dep)][12] << " " <<beta2[(*dep)][13]<< " " <<beta2[(*dep)][14] <<  " " <<beta2[(*dep)][15] <<  " " <<beta2[(*dep)][16] << " " <<beta2[(*dep)][17] << std::endl;
  std::cout<< 525 << " " <<beta2[(*dep)][18] << " " <<beta2[(*dep)][19]<< " " <<beta2[(*dep)][20] <<  " " <<beta2[(*dep)][21] <<  " " <<beta2[(*dep)][22] << " " <<beta2[(*dep)][23] << std::endl;
  std::cout<< 375 << " " << beta2[(*dep)][24] << " " << beta2[(*dep)][25]<<" " << beta2[(*dep)][26] << " " << beta2[(*dep)][27] << " " << beta2[(*dep)][28] << " " <<beta2[(*dep)][29] << std::endl;
  std::cout<< 425 <<" " << beta2[(*dep)][30] << " " <<beta2[(*dep)][31]<<" " << beta2[(*dep)][32] << " " << beta2[(*dep)][33] <<  " " <<beta2[(*dep)][34] << " " <<beta2[(*dep)][35] << std::endl;
  std::cout<< 450 << " " <<beta2[(*dep)][36] << " " <<beta2[(*dep)][37]<< " " <<beta2[(*dep)][38] <<  " " <<beta2[(*dep)][39] <<  " " <<beta2[(*dep)][40] << " " <<beta2[(*dep)][41] << std::endl;
  std::cout<< 495 << " " <<beta2[(*dep)][42] << " " <<beta2[(*dep)][43]<< " " <<beta2[(*dep)][44] <<  " " <<beta2[(*dep)][45] <<  " " <<beta2[(*dep)][46] << " " <<beta2[(*dep)][47] << std::endl;

  std::cout<< "---------------------------------------------" << std::endl;
  std::cout<< " Photodiode 2 Errors in Beta in " << (*dep) << " m" << std::endl;
  std::cout<< "WL " << "P(10-15) " << "P(10-17) " << "P(10-22) " << "P(15-17) " << "P(15-22) "  <<  "P(17-22) " << std::endl;
  std::cout<< "---------------------------------------------" << std::endl;
  std::cout<< 383 << " " << betaerror2[(*dep)][0] << " " << betaerror2[(*dep)][1]<<" " << betaerror2[(*dep)][2] << " " << betaerror2[(*dep)][3] << " " << betaerror2[(*dep)][4] << " " <<betaerror2[(*dep)][5] << std::endl;
  std::cout<< 400 <<" " << betaerror2[(*dep)][6] << " " <<betaerror2[(*dep)][7]<<" " << betaerror2[(*dep)][8] << " " << betaerror2[(*dep)][9] <<  " " <<betaerror2[(*dep)][10] << " " <<betaerror2[(*dep)][11] << std::endl;
  std::cout<< 470 << " " <<betaerror2[(*dep)][12] << " " <<betaerror2[(*dep)][13]<< " " <<betaerror2[(*dep)][14] <<  " " <<betaerror2[(*dep)][15] <<  " " <<betaerror2[(*dep)][16] << " " <<betaerror2[(*dep)][17] << std::endl;
  std::cout<< 525 << " " <<betaerror2[(*dep)][18] << " " <<betaerror2[(*dep)][19]<< " " <<betaerror2[(*dep)][20] <<  " " <<betaerror2[(*dep)][21] <<  " " <<betaerror2[(*dep)][22] << " " <<betaerror2[(*dep)][23] << std::endl;
  std::cout<< 375 << " " << betaerror2[(*dep)][24] << " " << betaerror2[(*dep)][25]<<" " << betaerror2[(*dep)][26] << " " << betaerror2[(*dep)][27] << " " << betaerror2[(*dep)][28] << " " <<betaerror2[(*dep)][29] << std::endl;
  std::cout<< 425 <<" " << betaerror2[(*dep)][30] << " " <<betaerror2[(*dep)][31]<<" " << betaerror2[(*dep)][32] << " " << betaerror2[(*dep)][33] <<  " " <<betaerror2[(*dep)][34] << " " <<betaerror2[(*dep)][35] << std::endl;
  std::cout<< 450 << " " <<betaerror2[(*dep)][36] << " " <<betaerror2[(*dep)][37]<< " " <<betaerror2[(*dep)][38] <<  " " <<betaerror2[(*dep)][39] <<  " " <<betaerror2[(*dep)][40] << " " <<betaerror2[(*dep)][41] << std::endl;
  std::cout<< 495 << " " <<betaerror2[(*dep)][42] << " " <<betaerror2[(*dep)][43]<< " " <<betaerror2[(*dep)][44] <<  " " <<betaerror2[(*dep)][45] <<  " " <<betaerror2[(*dep)][46] << " " <<betaerror2[(*dep)][47] << std::endl;

  std::cout<< "---------------------------------------------" << std::endl;


  } // End on loop over Depths


//   //Transmission Length Useful Parameters Filling
//   std::vector<double> y10_15; std::vector<double> x10_15; std::vector<double> dy10_15; std::vector<double> dx10_15;
//   std::vector<double> y10_17; std::vector<double> x10_17; std::vector<double> dy10_17; std::vector<double> dx10_17;
//   std::vector<double> y10_22; std::vector<double> x10_22; std::vector<double> dy10_22; std::vector<double> dx10_22;
//   std::vector<double> y15_17; std::vector<double> x15_17; std::vector<double> dy15_17; std::vector<double> dx15_17;
//   std::vector<double> y15_22; std::vector<double> x15_22; std::vector<double> dy15_22; std::vector<double> dx15_22;
//   std::vector<double> y17_22; std::vector<double> x17_22; std::vector<double> dy17_22; std::vector<double> dx17_22;
  
//   for(int i=0; i<8;++i){dx10_15.push_back( 10. );}
//   for(int i=0; i<8;++i){dx10_17.push_back( 10. );}
//   for(int i=0; i<8;++i){dx10_22.push_back( 10. );}
//   for(int i=0; i<8;++i){dx15_17.push_back( 10. );}
//   for(int i=0; i<8;++i){dx15_22.push_back( 10. );}
//   for(int i=0; i<8;++i){dx17_22.push_back( 10. );}

//   y10_15.push_back( 1./beta2[0] );  x10_15.push_back( 383. ); dy10_15.push_back( betaerror2[0] * pow(1./ beta2[0],2.) );
//   y10_15.push_back( 1./beta2[6] );  x10_15.push_back( 400. ); dy10_15.push_back( betaerror2[6] * pow(1./ beta2[6],2.) );
//   y10_15.push_back( 1./beta2[12] );  x10_15.push_back( 470. ); dy10_15.push_back( betaerror2[12] * pow(1./ beta2[12],2.) );
//   y10_15.push_back( 1./beta2[18] );  x10_15.push_back( 525. ); dy10_15.push_back( betaerror2[18] * pow(1./ beta2[18],2.) );

//   y10_17.push_back( 1./beta2[1] );  x10_17.push_back( 383. ); dy10_17.push_back( betaerror2[1] *  pow(1./beta2[1],2.) );
//   y10_17.push_back( 1./beta2[7] );  x10_17.push_back( 400. ); dy10_17.push_back( betaerror2[7] *  pow(1./beta2[7],2.) );
//   y10_17.push_back( 1./beta2[13] );  x10_17.push_back( 470. ); dy10_17.push_back( betaerror2[13] *  pow(1./beta2[13],2.) );
//   y10_17.push_back( 1./beta2[19] );  x10_17.push_back( 525. ); dy10_17.push_back( betaerror2[19] *  pow(1./beta2[19],2.) );

//   y10_22.push_back( 1./beta2[2] );  x10_22.push_back( 383. );  dy10_22.push_back( betaerror2[2] * pow(1./beta2[2],2.) );
//   y10_22.push_back( 1./beta2[8] );  x10_22.push_back( 400. );  dy10_22.push_back( betaerror2[8] * pow(1./beta2[8],2.) );
//   y10_22.push_back( 1./beta2[14] );  x10_22.push_back( 470. ); dy10_22.push_back( betaerror2[14] * pow(1./beta2[14],2.) );
//   y10_22.push_back( 1./beta2[20] );  x10_22.push_back( 525. ); dy10_22.push_back( betaerror2[20] * pow(1./beta2[20],2.) );

//   y15_17.push_back( 1./beta2[3] );  x15_17.push_back( 383. ); dy15_17.push_back( betaerror2[3] *  pow(1./beta2[3],2.) );
//   y15_17.push_back( 1./beta2[9] );  x15_17.push_back( 400. ); dy15_17.push_back( betaerror2[9] *  pow(1./beta2[9],2.) );
//   y15_17.push_back( 1./beta2[15] );  x15_17.push_back( 470. ); dy15_17.push_back( betaerror2[15] *  pow(1./beta2[15],2.) );
//   y15_17.push_back( 1./beta2[21] );  x15_17.push_back( 525. ); dy15_17.push_back( betaerror2[21] *  pow(1./beta2[21],2.) );

//   y15_22.push_back( 1./beta2[4] );  x15_22.push_back( 383. );  dy15_22.push_back( betaerror2[4] * pow(1./beta2[4],2.) );
//   y15_22.push_back( 1./beta2[10] );  x15_22.push_back( 400. ); dy15_22.push_back( betaerror2[10] * pow(1./beta2[10],2.) );
//   y15_22.push_back( 1./beta2[16] );  x15_22.push_back( 470. ); dy15_22.push_back( betaerror2[16] * pow(1./beta2[16],2.) );
//   y15_22.push_back( 1./beta2[22] );  x15_22.push_back( 525. ); dy15_22.push_back( betaerror2[22] * pow(1./beta2[22],2.) );

//   y17_22.push_back( 1./beta2[5] );  x17_22.push_back( 383. ); dy17_22.push_back( betaerror2[5] * pow(1./beta2[5],2.) );
//   y17_22.push_back( 1./beta2[11] );  x17_22.push_back( 400. ); dy17_22.push_back( betaerror2[11] * pow(1./beta2[11],2.) );
//   y17_22.push_back( 1./beta2[17] );  x17_22.push_back( 470. ); dy17_22.push_back( betaerror2[17] * pow(1./beta2[17],2.) );
//   y17_22.push_back( 1./beta2[23] );  x17_22.push_back( 525. ); dy17_22.push_back( betaerror2[23] * pow(1./beta2[23],2.) );
  
//   //Source 2 now
//   y10_15.push_back( 1./beta2[24] );  x10_15.push_back( 375. ); dy10_15.push_back( betaerror2[24] * pow(1./ beta2[24],2.) );
//   y10_15.push_back( 1./beta2[30] );  x10_15.push_back( 425. ); dy10_15.push_back( betaerror2[30] * pow(1./ beta2[30],2.) );
//   y10_15.push_back( 1./beta2[36] );  x10_15.push_back( 450. ); dy10_15.push_back( betaerror2[36] * pow(1./ beta2[36],2.) );
//   y10_15.push_back( 1./beta2[42] );  x10_15.push_back( 495. ); dy10_15.push_back( betaerror2[42] * pow(1./ beta2[42],2.) );

//   y10_17.push_back( 1./beta2[25] );  x10_17.push_back( 375. ); dy10_17.push_back( betaerror2[25] *  pow(1./beta2[25],2.) );
//   y10_17.push_back( 1./beta2[31] );  x10_17.push_back( 425. ); dy10_17.push_back( betaerror2[31] *  pow(1./beta2[31],2.) );
//   y10_17.push_back( 1./beta2[37] );  x10_17.push_back( 450. ); dy10_17.push_back( betaerror2[37] *  pow(1./beta2[37],2.) );
//   y10_17.push_back( 1./beta2[43] );  x10_17.push_back( 495. ); dy10_17.push_back( betaerror2[43] *  pow(1./beta2[43],2.) );

//   y10_22.push_back( 1./beta2[26] );  x10_22.push_back( 375. );  dy10_22.push_back( betaerror2[26] * pow(1./beta2[26],2.) );
//   y10_22.push_back( 1./beta2[32] );  x10_22.push_back( 425. );  dy10_22.push_back( betaerror2[32] * pow(1./beta2[32],2.) );
//   y10_22.push_back( 1./beta2[38] );  x10_22.push_back( 450. ); dy10_22.push_back( betaerror2[38] * pow(1./beta2[38],2.) );
//   y10_22.push_back( 1./beta2[44] );  x10_22.push_back( 495. ); dy10_22.push_back( betaerror2[44] * pow(1./beta2[44],2.) );

//   y15_17.push_back( 1./beta2[27] );  x15_17.push_back( 375. ); dy15_17.push_back( betaerror2[27] *  pow(1./beta2[27],2.) );
//   y15_17.push_back( 1./beta2[33] );  x15_17.push_back( 425. ); dy15_17.push_back( betaerror2[33] *  pow(1./beta2[33],2.) );
//   y15_17.push_back( 1./beta2[39] );  x15_17.push_back( 450. ); dy15_17.push_back( betaerror2[39] *  pow(1./beta2[39],2.) );
//   y15_17.push_back( 1./beta2[45] );  x15_17.push_back( 495. ); dy15_17.push_back( betaerror2[45] *  pow(1./beta2[45],2.) );

//   y15_22.push_back( 1./beta2[28] );  x15_22.push_back( 375. );  dy15_22.push_back( betaerror2[28] * pow(1./beta2[28],2.) );
//   y15_22.push_back( 1./beta2[34] );  x15_22.push_back( 425. ); dy15_22.push_back( betaerror2[34] * pow(1./beta2[34],2.) );
//   y15_22.push_back( 1./beta2[40] );  x15_22.push_back( 450. ); dy15_22.push_back( betaerror2[40] * pow(1./beta2[40],2.) );
//   y15_22.push_back( 1./beta2[46] );  x15_22.push_back( 495. ); dy15_22.push_back( betaerror2[46] * pow(1./beta2[46],2.) );

//   y17_22.push_back( 1./beta2[29] );  x17_22.push_back( 375. ); dy17_22.push_back( betaerror2[29] * pow(1./beta2[29],2.) );
//   y17_22.push_back( 1./beta2[35] );  x17_22.push_back( 425. ); dy17_22.push_back( betaerror2[35] * pow(1./beta2[35],2.) );
//   y17_22.push_back( 1./beta2[41] );  x17_22.push_back( 450. ); dy17_22.push_back( betaerror2[41] * pow(1./beta2[41],2.) );
//   y17_22.push_back( 1./beta2[47] );  x17_22.push_back( 495. ); dy17_22.push_back( betaerror2[47] * pow(1./beta2[47],2.) );


//   TCanvas *c1 = new TCanvas("c1");

//   TGraphErrors *gr17_22 = new TGraphErrors( 8, &x17_22[0], &y17_22[0],&dx17_22[0], &dy17_22[0] ); 
//   gr17_22->SetMarkerStyle(25); 
//   gr17_22->SetMarkerSize(1.4); 
// //   gr17_22->SetMarkerColor(7);  
//   gr17_22->Draw("AP");
//   gStyle->SetOptStat(1);
//   c1->Update();

//   TGraphErrors *gr10_15 = new TGraphErrors( 8,  &x10_15[0], &y10_15[0], &dx10_15[0], &dy10_15[0] ); 
//   gr10_15->SetMarkerStyle(29); 
//   gr10_15->SetMarkerSize(1.4); 
// //   gr10_15->SetMarkerColor(2);  
//   gr10_15->Draw("SP");
//   c1->Update();

//   TGraphErrors *gr10_17 = new TGraphErrors( 8, &x10_17[0], &y10_17[0],&dx10_17[0], &dy10_17[0] ); 
//   gr10_17->SetMarkerStyle(20); 
//   gr10_17->SetMarkerSize(1.4); 
// //   gr10_17->SetMarkerColor(3);  
//   gr10_17->Draw("SP");
//   c1->Update();


//   TGraphErrors *gr10_22 =  new TGraphErrors( 8, &x10_22[0], &y10_22[0],&dx10_22[0], &dy10_22[0] ); 
//   gr10_22->SetMarkerStyle(21); 
//   gr10_22->SetMarkerSize(1.4); 
// //   gr10_22->SetMarkerColor(4);  
//   gr10_22->Draw("PS");
//   c1->Update();
  
//   TGraphErrors *gr15_17 =  new TGraphErrors( 8, &x15_17[0], &y15_17[0],&dx15_17[0], &dy15_17[0] ); 
//   gr15_17->SetMarkerStyle(22); 
//   gr15_17->SetMarkerSize(1.4); 
// //   gr15_17->SetMarkerColor(5);  
//   gr15_17->Draw("PS");
//   c1->Update();
  
//   TGraphErrors *gr15_22 =  new TGraphErrors( 8, &x15_22[0], &y15_22[0],&dx15_22[0], &dy15_22[0] ); 
//   gr15_22->SetMarkerStyle(27); 
//   gr15_22->SetMarkerSize(1.4); 
// //   gr15_22->SetMarkerColor(6);  
//   gr15_22->Draw("PS");
//   c1->Update();

//   TLegend *leg = new TLegend(0.8,0.7,0.89,0.89);  //coordinates are fractions
//                                          //of pad dimensions
//   leg->AddEntry(gr10_15,"(15-10) m","P");  
//   leg->AddEntry(gr10_17,"(17-10) m","P");  
//   leg->AddEntry(gr10_22,"(22-10) m","P");  
//   leg->AddEntry(gr15_17,"(17-15) m","P");  
//   leg->AddEntry(gr15_22,"(22-15) m","P");  
//   leg->AddEntry(gr17_22,"(22-17) m","P");  // "l" means line
// //   leg->SetHeader("The Legend Title");
//                                             // use "f" for a box
//   leg->Draw("PS");
//   c1->Update();


//   gr17_22 -> SetTitle( " L = f (#lambda) Depth 4100 m Photodiode 1");

//   gr17_22->GetHistogram()->SetXTitle("Wavelength (nm)");
//   gr17_22->GetHistogram()->SetYTitle("Transmission Length L (m)");
//   gStyle->SetOptStat(1);
//   c1->Update();

//   double xinitbin   = 0.;
//   double xfinbin    = 15.;
//   int xtotalbins    = 100;
//   //Histos for Beta Photodiode 1 
//   TH2F *beta2led383= new TH2F(" Beta Ph1 LED 383 " , " Beta Values For 383nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta2led383 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta2led383 ->SetYTitle(" #beta (1/m) ");
//   beta2led383->SetMarkerStyle(kFullCircle);

//   beta2led383 -> Fill(5.,beta2[0]);
//   beta2led383 -> Fill(7.,beta2[1]);
//   beta2led383 -> Fill(12.,beta2[2]);
//   beta2led383 -> Fill(2.,beta2[3]);
//   beta2led383 -> Fill(7.,beta2[4]);
//   beta2led383 -> Fill(12.,beta2[5]);

//   TH2F *beta2led400= new TH2F(" Beta Ph1 LED 400 " , " Beta Values For 400nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta2led400 ->SetXTitle(" R_{L}-R_{S} (m) ");
//   beta2led400 ->SetYTitle(" #beta (1/m) ");
//   beta2led400->SetMarkerStyle(kFullCircle);

//   beta2led400 -> Fill(5.,beta2[6]);
//   beta2led400 -> Fill(7.,beta2[7]);
//   beta2led400 -> Fill(12.,beta2[8]);
//   beta2led400 -> Fill(2.,beta2[9]);
//   beta2led400 -> Fill(7.,beta2[10]);
//   beta2led400 -> Fill(12.,beta2[11]);

//   TH2F *beta2led470= new TH2F(" Beta Ph1 LED 470 " , " Beta Values For 470nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta2led470 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta2led470 ->SetYTitle(" #beta (1/m) ");
//   beta2led470->SetMarkerStyle(kFullCircle);

//   beta2led470 -> Fill(5.,beta2[12]);
//   beta2led470 -> Fill(7.,beta2[13]);
//   beta2led470 -> Fill(12.,beta2[14]);
//   beta2led470 -> Fill(2.,beta2[15]);
//   beta2led470 -> Fill(7.,beta2[16]);
//   beta2led470 -> Fill(12.,beta2[17]);

//   TH2F *beta2led525= new TH2F(" Beta Ph1 LED 525 " , " Beta Values For 525nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta2led525 ->SetXTitle(" R_{L}-R_{S} (m) ");
//   beta2led525 ->SetYTitle(" #beta (1/m) ");
//   beta2led525->SetMarkerStyle(kFullCircle);

//   beta2led525 -> Fill(5.,beta2[18]);
//   beta2led525 -> Fill(7.,beta2[19]);
//   beta2led525 -> Fill(12.,beta2[20]);
//   beta2led525 -> Fill(2.,beta2[21]);
//   beta2led525 -> Fill(7.,beta2[22]);
//   beta2led525 -> Fill(12.,beta2[23]);

//   //Now the second source
//   TH2F *beta2led375= new TH2F(" Beta Ph1 LED 375 " , " Beta Values For 375nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta2led375 ->SetXTitle(" R_{L}-R_{S} (m) ");
//   beta2led375 ->SetYTitle(" #beta (1/m) ");
//   beta2led375->SetMarkerStyle(kFullCircle);

//   beta2led375 -> Fill(5.,beta2[24]);
//   beta2led375 -> Fill(7.,beta2[25]);
//   beta2led375 -> Fill(12.,beta2[26]);
//   beta2led375 -> Fill(2.,beta2[27]);
//   beta2led375 -> Fill(7.,beta2[28]);
//   beta2led375 -> Fill(12.,beta2[29]);

//   TH2F *beta2led425= new TH2F(" Beta Ph1 LED 425 " , " Beta Values For 425nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta2led425 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta2led425 ->SetYTitle(" #beta (1/m)  ");
//   beta2led425->SetMarkerStyle(kFullCircle);

//   beta2led425 -> Fill(5.,beta2[30]);
//   beta2led425 -> Fill(7.,beta2[31]);
//   beta2led425 -> Fill(12.,beta2[32]);
//   beta2led425 -> Fill(2.,beta2[33]);
//   beta2led425 -> Fill(7.,beta2[34]);
//   beta2led425 -> Fill(12.,beta2[35]);

//   TH2F *beta2led450= new TH2F(" Beta Ph1 LED 450 " , " Beta Values For 450nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta2led450 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta2led450 ->SetYTitle(" #beta (1/m)  ");
//   beta2led450->SetMarkerStyle(kFullCircle);

//   beta2led450 -> Fill(5.,beta2[36]);
//   beta2led450 -> Fill(7.,beta2[37]);
//   beta2led450 -> Fill(12.,beta2[38]);
//   beta2led450 -> Fill(2.,beta2[39]);
//   beta2led450 -> Fill(7.,beta2[40]);
//   beta2led450 -> Fill(12.,beta2[41]);

//   TH2F *beta2led495= new TH2F(" Beta Ph1 LED 495 " , " Beta Values For 495nm Ph1 " , xtotalbins, xinitbin, xfinbin, 100, -0.01, 0.01);
//   beta2led495 ->SetXTitle(" R_{L}-R_{S} (m)");
//   beta2led495 ->SetYTitle(" #beta (1/m)  ");
//   beta2led495->SetMarkerStyle(kFullCircle);

//   beta2led495 -> Fill(5.,beta2[42]);
//   beta2led495 -> Fill(7.,beta2[43]);
//   beta2led495 -> Fill(12.,beta2[44]);
//   beta2led495 -> Fill(2.,beta2[45]);
//   beta2led495 -> Fill(7.,beta2[46]);
//   beta2led495 -> Fill(12.,beta2[47]);

//   //Beta as a function of the wavelength for the first photodiode
//   TH2F *beta2allled= new TH2F("PhotoDiode 1", " L = f (#lambda)" , 100 , 350.,550.,100, 0.,100.);
//   beta2allled ->SetXTitle(" Wavelength (nm) ");
//   beta2allled ->SetYTitle(" Transmission Length L (m)");

//   for (int i=0;i<6;++i){ beta2allled -> Fill( 383. ,1./beta2[i]); }
//   for (int i=6;i<12;++i){ beta2allled -> Fill( 400. ,1./beta2[i]); }
//   for (int i=12;i<18;++i){ beta2allled -> Fill( 470. ,1./beta2[i]); }
//   for (int i=18;i<24;++i){ beta2allled -> Fill( 525. ,1./beta2[i]); }
//   for (int i=24;i<30;++i){ beta2allled -> Fill( 375. ,1./beta2[i]); }
//   for (int i=30;i<36;++i){ beta2allled -> Fill( 425. ,1./beta2[i]); }
//   for (int i=36;i<42;++i){ beta2allled -> Fill( 450. ,1./beta2[i]); }
//   for (int i=42;i<48;++i){ beta2allled -> Fill( 495. ,1./beta2[i]); }

  // Create a file

  std::map<int,std::map<double,double> > fitlength383; 
  std::map<int,std::map<double,double> > fitlength400; 
  std::map<int,std::map<double,double> > fitlength470; 
  std::map<int,std::map<double,double> > fitlength525; 
  std::map<int,std::map<double,double> > fitlength375; 
  std::map<int,std::map<double,double> > fitlength425;
  std::map<int,std::map<double,double> > fitlength450; 
  std::map<int,std::map<double,double> > fitlength495;

  std::map<int,std::vector<TransmissionLength> > trleng;

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

    fitlength383[(*dep)] = fitbetamethodph2(led383int2[(*dep)],led383intrms2[(*dep)]);
    fitlength400[(*dep)] = fitbetamethodph2(led400int2[(*dep)],led400intrms2[(*dep)]);
    fitlength470[(*dep)] = fitbetamethodph2(led470int2[(*dep)],led470intrms2[(*dep)]);
    fitlength525[(*dep)] = fitbetamethodph2(led525int2[(*dep)],led525intrms2[(*dep)]);
    fitlength375[(*dep)] = fitbetamethodph2(led375int2[(*dep)],led375intrms2[(*dep)]);
    fitlength425[(*dep)] = fitbetamethodph2(led425int2[(*dep)],led425intrms2[(*dep)]);
    fitlength450[(*dep)] = fitbetamethodph2(led450int2[(*dep)],led450intrms2[(*dep)]);
    fitlength495[(*dep)] = fitbetamethodph2(led495int2[(*dep)],led495intrms2[(*dep)]);

//     std::cout<< " Photodiode 2 Intensity in " << (*dep) << " m for 10,15,17,22 m" <<std::endl;
//     std::cout<< 375 << " " << led375int2[(*dep)][10]  << " "<< led375int2[(*dep)][15]  << " "<< led375int2[(*dep)][17] << " " << led375int2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 383 << led383int2[(*dep)][10] << " " << led383int2[(*dep)][15] << " " << led383int2[(*dep)][17] << " " << led383int2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 400  << " "<< led400int2[(*dep)][10] << " " << led400int2[(*dep)][15] << " " << led400int2[(*dep)][17] << " " << led400int2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 425 << " " << led425int2[(*dep)][10] << " " << led425int2[(*dep)][15] << " " << led425int2[(*dep)][17] << " " << led425int2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 450 << " " << led450int2[(*dep)][10] << " " << led450int2[(*dep)][15] << " " << led450int2[(*dep)][17] << " " << led450int2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 470 << " " << led470int2[(*dep)][10] << " " << led470int2[(*dep)][15] << " " << led470int2[(*dep)][17] << " " << led470int2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 495 << " " << led495int2[(*dep)][10] << " " << led495int2[(*dep)][15] << " " << led495int2[(*dep)][17] << " " << led495int2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 525 << " " << led525int2[(*dep)][10] << " " << led525int2[(*dep)][15] << " " << led525int2[(*dep)][17] << " " << led525int2[(*dep)][22] << " " <<std::endl;
//     std::cout<< " Photodiode 2 Intensity RMS in " << (*dep) << " m for 10,15,17,22 m" <<std::endl;
//     std::cout<< 375 << " " << led375intrms2[(*dep)][10]  << " "<< led375intrms2[(*dep)][15]  << " "<< led375intrms2[(*dep)][17] << " " << led375intrms2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 383 << led383intrms2[(*dep)][10] << " " << led383intrms2[(*dep)][15] << " " << led383intrms2[(*dep)][17] << " " << led383intrms2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 400  << " "<< led400intrms2[(*dep)][10] << " " << led400intrms2[(*dep)][15] << " " << led400intrms2[(*dep)][17] << " " << led400intrms2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 425 << " " << led425intrms2[(*dep)][10] << " " << led425intrms2[(*dep)][15] << " " << led425intrms2[(*dep)][17] << " " << led425intrms2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 450 << " " << led450intrms2[(*dep)][10] << " " << led450intrms2[(*dep)][15] << " " << led450intrms2[(*dep)][17] << " " << led450intrms2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 470 << " " << led470intrms2[(*dep)][10] << " " << led470intrms2[(*dep)][15] << " " << led470intrms2[(*dep)][17] << " " << led470intrms2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 495 << " " << led495intrms2[(*dep)][10] << " " << led495intrms2[(*dep)][15] << " " << led495intrms2[(*dep)][17] << " " << led495intrms2[(*dep)][22] << " " <<std::endl;
//     std::cout<< 525 << " " << led525intrms2[(*dep)][10] << " " << led525intrms2[(*dep)][15] << " " << led525intrms2[(*dep)][17] << " " << led525intrms2[(*dep)][22] << " " <<std::endl;
//     std::cout<< "------------------------------------------------------------------------------------------- "<<std::endl;


  for (std::map<double,double>::iterator it =fitlength383[(*dep)].begin();it!=fitlength383[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 383. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength400[(*dep)].begin();it!=fitlength400[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 400. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength470[(*dep)].begin();it!=fitlength470[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 470. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength525[(*dep)].begin();it!=fitlength525[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 525. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength375[(*dep)].begin();it!=fitlength375[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 375. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength425[(*dep)].begin();it!=fitlength425[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 425. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength450[(*dep)].begin();it!=fitlength450[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 450. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength495[(*dep)].begin();it!=fitlength495[(*dep)].end();++it){
   trleng[(*dep)].push_back( TransmissionLength( 495. , (*it).first,(*it).second ) );
  }

  } // End on loop over Depths







//   ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 470 nm////////////////////////////////////////////// 
//   TCanvas *c5 = new TCanvas("c5");
  
//   TGraphErrors *bvsd470 = betavsdepth( 470, trleng );
//   bvsd470->SetMarkerStyle(20);//circle full 
//   bvsd470->SetMarkerSize(0.9); 
//   bvsd470->Draw("AP");
//   c5->Update();

//   bvsd470-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 470 nm Photodiode 2 ");

//   bvsd470->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd470->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd470->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd470->GetXaxis()->SetRangeUser(400.,4400.);
//   c5->Update();

//   ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 450 nm////////////////////////////////////////////// 

//   TCanvas *c4 = new TCanvas("c4");
  
//   TGraphErrors *bvsd450 = betavsdepth( 450, trleng );
//   bvsd450->SetMarkerStyle(20);//circle full 
//   bvsd450->SetMarkerSize(0.9); 
//   bvsd450->Draw("AP");
//   c4->Update();

//   bvsd450-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 450 nm Photodiode 2 ");

//   bvsd450->GetHistogram()->SetXTitle(" Depth (m) ");
//   bvsd450->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   bvsd450->GetYaxis()->SetRangeUser(15.,50.);
//   bvsd450->GetXaxis()->SetRangeUser(400.,4400.);
//   c4->Update();

  ///////////////////////////////Transmission Length Sinartisi WaveLength 2500,3400,4100m////////////////////////////////////////////// 
  TCanvas *c3_2500_3400_4100 = new TCanvas("c3_2500_3400_4100");
   
  TGraphErrors *translength4100 = fitbetamethodgrapherrorph2( trleng[4100] );
  translength4100->SetMarkerStyle(20);//circle full 
  translength4100->SetMarkerSize(0.9); 
  translength4100->SetMarkerColor(2);//red  
  translength4100->SetLineColor(2);
  translength4100->Draw("AP");
  c3_2500_3400_4100->Update();

  TGraphErrors *translength3400 = fitbetamethodgrapherrorph2( trleng[3400] );
  translength3400->SetMarkerStyle(29);//star full 
  translength3400->SetMarkerSize(0.9); 
  translength3400->SetMarkerColor(4);//blue  
  translength3400->SetLineColor(4);
  translength3400->Draw("PS");
  c3_2500_3400_4100->Update();

  TGraphErrors *translength2500 = fitbetamethodgrapherrorph2( trleng[2500] );
  translength2500->SetMarkerStyle(22);// triangle full 
  translength2500->SetMarkerSize(0.9); 
  translength2500->SetMarkerColor(8);//green  
  translength2500->SetLineColor(8);
  translength2500->Draw("PS");
  c3_2500_3400_4100->Update();

  TLegend *leg_2500_3400_4100 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_2500_3400_4100->AddEntry(translength4100,"4100 m","LP");  
  leg_2500_3400_4100->AddEntry(translength3400,"3400 m","LP");  
  leg_2500_3400_4100->AddEntry(translength2500,"2500 m","LP");  
  leg_2500_3400_4100->SetFillColor(18);
  leg_2500_3400_4100->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_2500_3400_4100->Draw("PS");
  c3_2500_3400_4100->Update();

  translength4100 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 2");

  translength4100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength4100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength4100 ->GetYaxis()->SetRangeUser(15.,50.);
  translength4100 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_2500_3400_4100->Update();

  ///
  //////////Transmission Length Sinartisi WaveLength 500-1000,1000-1500,1500-2000m////////////////////////////////////////////// 
  TCanvas *c3_500_2000 = new TCanvas("c3_500_2000");
   
  TGraphErrors *translength15002000 = fitbetamethodgrapherrorph2( trleng[15002000] );
  translength15002000->SetMarkerStyle(20);//circle full 
  translength15002000->SetMarkerSize(0.9); 
  translength15002000->SetMarkerColor(2);//red  
  translength15002000->SetLineColor(2);
  translength15002000->Draw("AP");
  c3_500_2000->Update();

  TGraphErrors *translength10001500 = fitbetamethodgrapherrorph2( trleng[10001500] );
  translength10001500->SetMarkerStyle(29);//star full 
  translength10001500->SetMarkerSize(0.9); 
  translength10001500->SetMarkerColor(4);//blue  
  translength10001500->SetLineColor(4);
  translength10001500->Draw("PS");
  c3_500_2000->Update();

  TGraphErrors *translength5001000 = fitbetamethodgrapherrorph1( trleng[5001000] );
  translength5001000->SetMarkerStyle(22);// triangle full 
  translength5001000->SetMarkerSize(0.9); 
  translength5001000->SetMarkerColor(8);//green  
  translength5001000->SetLineColor(8);
  translength5001000->Draw("PS");
  c3_500_2000->Update();

  TLegend *leg_500_2000 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_500_2000->AddEntry(translength15002000,"1500-2000 m","LP");  
  leg_500_2000->AddEntry(translength10001500,"1000-1500 m","LP");  
  leg_500_2000->AddEntry(translength5001000,"500-1000 m","LP");  
  leg_500_2000->SetFillColor(18);
  leg_500_2000->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_500_2000->Draw("PS");
  c3_500_2000->Update();

  translength15002000 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 2");

  translength15002000 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength15002000 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength15002000 ->GetYaxis()->SetRangeUser(15.,50.);
  translength15002000 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_500_2000->Update();

  /////////////Transmission Length Sinartisi WaveLength 2000-2500,2500-3400,3400-4100m////////////////////////////////////////////// 
  TCanvas *c3_2000_4100 = new TCanvas("c3_2000_4100");
   
  TGraphErrors *translength34004100 = fitbetamethodgrapherrorph2( trleng[34004100] );
  translength34004100->SetMarkerStyle(20);//circle full 
  translength34004100->SetMarkerSize(0.9); 
  translength34004100->SetMarkerColor(2);//red  
  translength34004100->SetLineColor(2);
  translength34004100->Draw("AP");
  c3_2000_4100->Update();

  TGraphErrors *translength25003400 = fitbetamethodgrapherrorph2( trleng[25003400] );
  translength25003400->SetMarkerStyle(29);//star full 
  translength25003400->SetMarkerSize(0.9); 
  translength25003400->SetMarkerColor(4);//blue  
  translength25003400->SetLineColor(4);
  translength25003400->Draw("PS");
  c3_2000_4100->Update();

  TGraphErrors *translength20002500 = fitbetamethodgrapherrorph2( trleng[20002500] );
  translength20002500->SetMarkerStyle(22);// triangle full 
  translength20002500->SetMarkerSize(0.9); 
  translength20002500->SetMarkerColor(8);//green  
  translength20002500->SetLineColor(8);
  translength20002500->Draw("PS");
  c3_2000_4100->Update();

  TLegend *leg_2000_4100 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_2000_4100->AddEntry(translength34004100,"3400-4100 m","LP");  
  leg_2000_4100->AddEntry(translength25003400,"2500-3400 m","LP");  
  leg_2000_4100->AddEntry(translength20002500,"2000-2500 m","LP");  
  leg_2000_4100->SetFillColor(18);
  leg_2000_4100->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_2000_4100->Draw("PS");
  c3_2000_4100->Update();

  translength34004100 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 2");

  translength34004100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength34004100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength34004100 ->GetYaxis()->SetRangeUser(15.,50.);
  translength34004100 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_2000_4100->Update();

  /////////////Transmission Length Sinartisi WaveLength 4100-3400,3400-2500,2500-2000m////////////////////////////////////////////// 

  TCanvas *c3_4100_2000 = new TCanvas("c3_4100_2000");
   
   TGraphErrors *translength41003400 = fitbetamethodgrapherrorph2( trleng[41003400] );
  translength41003400->SetMarkerStyle(20);//circle full 
  translength41003400->SetMarkerSize(0.9); 
  translength41003400->SetMarkerColor(2);//red  
  translength41003400->SetLineColor(2);
  translength41003400->Draw("AP");
  c3_4100_2000->Update();

  TGraphErrors *translength34002500 = fitbetamethodgrapherrorph2( trleng[34002500] );
  translength34002500->SetMarkerStyle(29);//star full 
  translength34002500->SetMarkerSize(0.9); 
  translength34002500->SetMarkerColor(4);//blue  
  translength34002500->SetLineColor(4);
  translength34002500->Draw("PS");
  c3_4100_2000->Update();

  TGraphErrors *translength25002000 = fitbetamethodgrapherrorph2( trleng[25002000] );
  translength25002000->SetMarkerStyle(22);// triangle full 
  translength25002000->SetMarkerSize(0.9); 
  translength25002000->SetMarkerColor(8);//green  
  translength25002000->SetLineColor(8);
  translength25002000->Draw("PS");
  c3_4100_2000->Update();

  TLegend *leg_4100_2000 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_4100_2000->AddEntry(translength41003400,"4100-3400 m","LP");  
  leg_4100_2000->AddEntry(translength34002500,"3400-2500 m","LP");  
  leg_4100_2000->AddEntry(translength25002000,"2500-2000 m","LP");  
  leg_4100_2000->SetFillColor(18);
  leg_4100_2000->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_4100_2000->Draw("PS");
  c3_4100_2000->Update();

  translength41003400 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 2");

  translength41003400 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength41003400 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength41003400 ->GetYaxis()->SetRangeUser(15.,50.);
  translength41003400 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_4100_2000->Update();

  /////////////Transmission Length Sinartisi WaveLength 2000-500m////////////////////////////////////////////// 

  TCanvas *c3_2000_500 = new TCanvas("c3_2000_500");
   
  TGraphErrors *translength20001500 = fitbetamethodgrapherrorph2( trleng[20001500] );
  translength20001500->SetMarkerStyle(20);//circle full 
  translength20001500->SetMarkerSize(0.9); 
  translength20001500->SetMarkerColor(2);//red  
  translength20001500->SetLineColor(2);
  translength20001500->Draw("AP");
  c3_2000_500->Update();

  TGraphErrors *translength15001000 = fitbetamethodgrapherrorph2( trleng[15001000] );
  translength15001000->SetMarkerStyle(29);//star full 
  translength15001000->SetMarkerSize(0.9); 
  translength15001000->SetMarkerColor(4);//blue  
  translength15001000->SetLineColor(4);
  translength15001000->Draw("PS");
  c3_2000_500->Update();

  TGraphErrors *translength1000500 = fitbetamethodgrapherrorph2( trleng[1000500] );
  translength1000500->SetMarkerStyle(22);// triangle full 
  translength1000500->SetMarkerSize(0.9); 
  translength1000500->SetMarkerColor(8);//green  
  translength1000500->SetLineColor(8);
  translength1000500->Draw("PS");
  c3_2000_500->Update();

  TLegend *leg_2000_500 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg_2000_500->AddEntry(translength20001500,"2000-1500 m","LP");  
  leg_2000_500->AddEntry(translength15001000,"1500-1000 m","LP");  
  leg_2000_500->AddEntry(translength1000500,"1000-500 m","LP");  
  leg_2000_500->SetFillColor(18);
  leg_2000_500->SetHeader(" Depth ");
                                            // use "f" for a box
  leg_2000_500->Draw("PS");
  c3_2000_500->Update();

  translength20001500 -> SetTitle( "  PRELIMINARY - NOT FOR DISTRIBUTION. Photodiode 2");

  translength20001500 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength20001500 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength20001500 ->GetYaxis()->SetRangeUser(15.,50.);
  translength20001500 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_2000_500->Update();











 
//   TCanvas *c3 = new TCanvas("c3");
    
//   TGraphErrors *translength4100 = fitbetamethodgrapherrorph2( trleng[4100] );
// //    TGraphErrors *translength4100 = fitbetamethodgrapherrorph2( trleng[15002000] );
// //   TGraphErrors *translength4100 = fitbetamethodgrapherrorph2( trleng[34004100] );
// //   TGraphErrors *translength4100 = fitbetamethodgrapherrorph2( trleng[41003400] );
// //   TGraphErrors *translength4100 = fitbetamethodgrapherrorph2( trleng[20001500] );
//   translength4100->SetMarkerStyle(20); 
//   translength4100->SetMarkerSize(0.9); 
//   translength4100->SetMarkerColor(2);  
//   translength4100->SetLineColor(2);
//   translength4100->Draw("AP");
//   c3->Update();

//   TGraphErrors *translength3400 = fitbetamethodgrapherrorph2( trleng[3400] );
// //   TGraphErrors *translength3400 = fitbetamethodgrapherrorph2( trleng[10001500] );
// //   TGraphErrors *translength3400 = fitbetamethodgrapherrorph2( trleng[25003400] );
// //   TGraphErrors *translength3400 = fitbetamethodgrapherrorph2( trleng[34002500] );
// //   TGraphErrors *translength3400 = fitbetamethodgrapherrorph2( trleng[15001000] );
//   translength3400->SetMarkerStyle(29); 
//   translength3400->SetMarkerSize(0.9); 
//   translength3400->SetMarkerColor(4);  
//   translength3400->SetLineColor(4);
//   translength3400->Draw("PS");
//   c3->Update();

//   TGraphErrors *translength2500 = fitbetamethodgrapherrorph2( trleng[2500] );
// //   TGraphErrors *translength2500 = fitbetamethodgrapherrorph2( trleng[5001000] );
// //   TGraphErrors *translength2500 = fitbetamethodgrapherrorph2( trleng[20002500] );
// //   TGraphErrors *translength2500 = fitbetamethodgrapherrorph2( trleng[25002000] );
// //   TGraphErrors *translength2500 = fitbetamethodgrapherrorph2( trleng[1000500] );
//   translength2500->SetMarkerStyle(22); 
//   translength2500->SetMarkerSize(0.9); 
//   translength2500->SetMarkerColor(8);  
//   translength2500->SetLineColor(8);
//   translength2500->Draw("PS");
//   c3->Update();

//   TLegend *leg = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
//                                          //of pad dimensions
//   leg->AddEntry(translength4100,"4100 m","LP");  
//   leg->AddEntry(translength3400,"3400 m","LP");  
//   leg->AddEntry(translength2500,"2500 m","LP");  
// //   leg->AddEntry(translength4100,"1500-2000 m","LP");  
// //   leg->AddEntry(translength3400,"1000-1500 m","LP");  
// //   leg->AddEntry(translength2500,"500-1000 m","LP");  
// //   leg->AddEntry(translength4100,"3400-4100 m","LP");  
// //   leg->AddEntry(translength3400,"2500-3400 m","LP");  
// //   leg->AddEntry(translength2500,"2000-2500 m","LP");  
// //   leg->AddEntry(translength4100,"4100-3400 m","LP");  
// //   leg->AddEntry(translength3400,"3400-2500 m","LP");  
// //   leg->AddEntry(translength2500,"2500-2000 m","LP");  
// //   leg->AddEntry(translength4100,"2000-1500 m","LP");  
// //   leg->AddEntry(translength3400,"1500-1000 m","LP");  
// //   leg->AddEntry(translength2500,"1000-500 m","LP");  
//   leg->SetFillColor(18);
//   leg->SetHeader(" Depth ");
//                                             // use "f" for a box
//   leg->Draw("PS");
//   c3->Update();

//   translength4100 -> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. ");

//   translength4100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
//   translength4100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   translength4100 ->GetYaxis()->SetRangeUser(15.,50.);
//   translength4100 ->GetXaxis()->SetRangeUser(360.,560.);
//   c3->Update();


  TFile f("BetaHistosPH_2.root","recreate");
//   beta2led375->Write();beta2led425->Write();beta2led450->Write();beta2led495->Write();
//   beta2led383->Write();beta2led400->Write();beta2led470->Write();beta2led525->Write();
//   beta2allled->Write();
  c3_2500_3400_4100->Write();c3_500_2000->Write();c3_2000_4100->Write();c3_4100_2000->Write();c3_2000_500->Write();// c4->Write();c5->Write();
  f.Close();
//   delete beta2led383;
//   delete beta2led400;
//   delete beta2led470;
//   delete beta2led525;
//   delete beta2led375;
//   delete beta2led425;
//   delete beta2led450;
//   delete beta2led495;
//   delete beta2allled;
  delete c3_2500_3400_4100;
  delete c3_500_2000;
  delete c3_2000_4100;
  delete c3_4100_2000;
  delete c3_2000_500;
//   delete c4;
//   delete c5;
//   delete gr10_15;
//   delete gr10_17;
//   delete gr10_22;
//   delete gr15_17;
//   delete gr15_22;
//   delete gr17_22;
  delete translength4100;
  delete translength3400;
  delete translength2500;
  delete translength41003400;
  delete translength34002500;
  delete translength25002000;
  delete translength20001500;
  delete translength15001000;
  delete translength1000500;
//   delete bvsd450;
//   delete bvsd470;
  delete leg_2500_3400_4100;
  delete leg_500_2000;
  delete leg_2000_4100;
  delete leg_4100_2000;
  delete leg_2000_500;



  
}


void BetaCalculation::calculateallph (std::map<int, std::map<int, double> >& led383int1, std::map<int, std::map<int, double> >& led400int1, std::map<int, std::map<int, double> >& led470int1, std::map<int, std::map<int, double> >& led525int1, std::map<int, std::map<int, double> >& led383intrms1, std::map<int, std::map<int, double> >& led400intrms1, std::map<int, std::map<int, double> >& led470intrms1, std::map<int, std::map<int, double> >& led525intrms1,std::map<int, std::map<int, double> >& led375int1, std::map<int, std::map<int, double> >& led425int1, std::map<int, std::map<int, double> >& led450int1, std::map<int, std::map<int, double> >& led495int1, std::map<int, std::map<int, double> >& led375intrms1, std::map<int, std::map<int, double> >& led425intrms1, std::map<int, std::map<int, double> >& led450intrms1, std::map<int, std::map<int, double> >& led495intrms1,std::map<int, std::map<int, double> >& led383int2, std::map<int, std::map<int, double> >& led400int2, std::map<int, std::map<int, double> >& led470int2, std::map<int, std::map<int, double> >& led525int2 , std::map<int, std::map<int, double> >& led383intrms2, std::map<int, std::map<int, double> >& led400intrms2, std::map<int, std::map<int, double> >& led470intrms2, std::map<int, std::map<int, double> >& led525intrms2,std::map<int, std::map<int, double> >& led375int2, std::map<int, std::map<int, double> >& led425int2, std::map<int, std::map<int, double> >& led450int2, std::map<int, std::map<int, double> >& led495int2, std::map<int, std::map<int, double> >& led375intrms2, std::map<int, std::map<int, double> >& led425intrms2, std::map<int, std::map<int, double> >& led450intrms2, std::map<int, std::map<int, double> >& led495intrms2){



  //Depths that will be processed
  std::vector<int> DepthsToBeProccessed;

  DepthsToBeProccessed.push_back(4100);
  DepthsToBeProccessed.push_back(3400);
  DepthsToBeProccessed.push_back(2500);
  DepthsToBeProccessed.push_back(5001000);
  DepthsToBeProccessed.push_back(10001500);
  DepthsToBeProccessed.push_back(15002000);
  DepthsToBeProccessed.push_back(20002500);
  DepthsToBeProccessed.push_back(25003400);
  DepthsToBeProccessed.push_back(34004100);
  DepthsToBeProccessed.push_back(25002000);
  DepthsToBeProccessed.push_back(34002500);
  DepthsToBeProccessed.push_back(41003400);
  DepthsToBeProccessed.push_back(20001500);
  DepthsToBeProccessed.push_back(15001000);
  DepthsToBeProccessed.push_back(1000500);




  // Create a file

  std::map<int,std::map<double,double> > fitlength383ph1; 
  std::map<int,std::map<double,double> > fitlength400ph1; 
  std::map<int,std::map<double,double> > fitlength470ph1; 
  std::map<int,std::map<double,double> > fitlength525ph1; 
  std::map<int,std::map<double,double> > fitlength375ph1; 
  std::map<int,std::map<double,double> > fitlength425ph1;
  std::map<int,std::map<double,double> > fitlength450ph1; 
  std::map<int,std::map<double,double> > fitlength495ph1;

  std::map<int,std::vector<TransmissionLength> > trlengph1;

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

    fitlength383ph1[(*dep)] = fitbetamethodph1(led383int1[(*dep)],led383intrms1[(*dep)]);
    fitlength400ph1[(*dep)] = fitbetamethodph1(led400int1[(*dep)],led400intrms1[(*dep)]);
    fitlength470ph1[(*dep)] = fitbetamethodph1(led470int1[(*dep)],led470intrms1[(*dep)]);
    fitlength525ph1[(*dep)] = fitbetamethodph1(led525int1[(*dep)],led525intrms1[(*dep)]);
    fitlength375ph1[(*dep)] = fitbetamethodph1(led375int1[(*dep)],led375intrms1[(*dep)]);
    fitlength425ph1[(*dep)] = fitbetamethodph1(led425int1[(*dep)],led425intrms1[(*dep)]);
    fitlength450ph1[(*dep)] = fitbetamethodph1(led450int1[(*dep)],led450intrms1[(*dep)]);
    fitlength495ph1[(*dep)] = fitbetamethodph1(led495int1[(*dep)],led495intrms1[(*dep)]);


  for (std::map<double,double>::iterator it =fitlength383ph1[(*dep)].begin();it!=fitlength383ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 383. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength400ph1[(*dep)].begin();it!=fitlength400ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 400. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength470ph1[(*dep)].begin();it!=fitlength470ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 470. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength525ph1[(*dep)].begin();it!=fitlength525ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 525. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength375ph1[(*dep)].begin();it!=fitlength375ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 375. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength425ph1[(*dep)].begin();it!=fitlength425ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 425. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength450ph1[(*dep)].begin();it!=fitlength450ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 450. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength495ph1[(*dep)].begin();it!=fitlength495ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 495. , (*it).first,(*it).second ) );
  }

  } // End on loop over Depths


  // Create a file

  std::map<int,std::map<double,double> > fitlength383ph2; 
  std::map<int,std::map<double,double> > fitlength400ph2; 
  std::map<int,std::map<double,double> > fitlength470ph2; 
  std::map<int,std::map<double,double> > fitlength525ph2; 
  std::map<int,std::map<double,double> > fitlength375ph2; 
  std::map<int,std::map<double,double> > fitlength425ph2;
  std::map<int,std::map<double,double> > fitlength450ph2; 
  std::map<int,std::map<double,double> > fitlength495ph2;

  std::map<int,std::vector<TransmissionLength> > trlengph2;

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

    fitlength383ph2[(*dep)] = fitbetamethodph2(led383int2[(*dep)],led383intrms2[(*dep)]);
    fitlength400ph2[(*dep)] = fitbetamethodph2(led400int2[(*dep)],led400intrms2[(*dep)]);
    fitlength470ph2[(*dep)] = fitbetamethodph2(led470int2[(*dep)],led470intrms2[(*dep)]);
    fitlength525ph2[(*dep)] = fitbetamethodph2(led525int2[(*dep)],led525intrms2[(*dep)]);
    fitlength375ph2[(*dep)] = fitbetamethodph2(led375int2[(*dep)],led375intrms2[(*dep)]);
    fitlength425ph2[(*dep)] = fitbetamethodph2(led425int2[(*dep)],led425intrms2[(*dep)]);
    fitlength450ph2[(*dep)] = fitbetamethodph2(led450int2[(*dep)],led450intrms2[(*dep)]);
    fitlength495ph2[(*dep)] = fitbetamethodph2(led495int2[(*dep)],led495intrms2[(*dep)]);


  for (std::map<double,double>::iterator it =fitlength383ph2[(*dep)].begin();it!=fitlength383ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 383. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength400ph2[(*dep)].begin();it!=fitlength400ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 400. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength470ph2[(*dep)].begin();it!=fitlength470ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 470. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength525ph2[(*dep)].begin();it!=fitlength525ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 525. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength375ph2[(*dep)].begin();it!=fitlength375ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 375. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength425ph2[(*dep)].begin();it!=fitlength425ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 425. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength450ph2[(*dep)].begin();it!=fitlength450ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 450. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength495ph2[(*dep)].begin();it!=fitlength495ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 495. , (*it).first,(*it).second ) );
  }

  } // End on loop over Depths


  
  ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 470 nm////////////////////////////////////////////// 
  TCanvas *c1 = new TCanvas("c1");
  
  TGraphErrors *bvsd470ph1 = betavsdepth( 470, trlengph1 );
  bvsd470ph1->SetMarkerStyle(20);//circle full 
  bvsd470ph1->SetMarkerSize(0.9); 
//   bvsd470ph1->SetLineColor(2);
//   bvsd470ph1->SetMarkerColor(2);//red  
  bvsd470ph1->Draw("AP");
  c1->Update();

  TGraphErrors *bvsd470ph2 = betavsdepth( 470, trlengph2 );
  bvsd470ph2->SetMarkerStyle(29);//star full  
  bvsd470ph2->SetMarkerSize(0.9); 
//   bvsd470ph2->SetLineColor(4);
//   bvsd470ph2->SetMarkerColor(4);//blue  
  bvsd470ph2->Draw("SP");
  c1->Update();

  TGraphErrors *dpmean470ph1= depthmean( 470, trlengph1 );
  dpmean470ph1->SetMarkerStyle(20);//circle full 
  dpmean470ph1->SetMarkerSize(0.9); 
//   dpmeanph1->SetLineColor(2);
  dpmean470ph1->SetLineStyle(2);
//   dpmeanph1->SetMarkerColor(2);//red  
  dpmean470ph1 ->Draw("SP");
  c1->Update();

  TGraphErrors *dpmean470ph2= depthmean( 470, trlengph2 );
  dpmean470ph2->SetMarkerStyle(29);//circle full 
  dpmean470ph2->SetMarkerSize(0.9); 
//   dpmeanph2->SetLineColor(4);
  dpmean470ph2->SetLineStyle(2);
//   dpmeanph2->SetMarkerColor(4);//red  
  dpmean470ph2 ->Draw("SP");
  c1->Update();


  bvsd470ph1-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 470 nm  ");

  bvsd470ph1->GetHistogram()->SetXTitle(" Depth (m) ");
  bvsd470ph1->GetHistogram()->SetYTitle(" Transmission Length (m)");
  bvsd470ph1->GetYaxis()->SetRangeUser(15.,50.);
  bvsd470ph1->GetXaxis()->SetRangeUser(400.,4400.);
  c1->Update();

  TLegend *leg470 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg470->AddEntry(bvsd470ph1,"Photodiode 1","LP");  
  leg470->AddEntry(bvsd470ph2,"Photodiode 2","LP");  
  leg470->SetFillColor(18);
//   leg470->SetHeader("  ");
                                            // use "f" for a box
  leg470->Draw("PS");
  c1->Update();

  ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 450 nm////////////////////////////////////////////// 
  TCanvas *c2 = new TCanvas("c2");
  
  TGraphErrors *bvsd450ph1 = betavsdepth( 450, trlengph1 );
  bvsd450ph1->SetMarkerStyle(20);//circle full 
  bvsd450ph1->SetMarkerSize(0.9); 
//   bvsd450ph1->SetLineColor(2);
//   bvsd450ph1->SetMarkerColor(2);//red  
  bvsd450ph1->Draw("AP");
  c2->Update();

  TGraphErrors *bvsd450ph2 = betavsdepth( 450, trlengph2 );
  bvsd450ph2->SetMarkerStyle(29);//star full  
  bvsd450ph2->SetMarkerSize(0.9); 
//   bvsd450ph2->SetLineColor(4);
//   bvsd450ph2->SetMarkerColor(4);//blue  
  bvsd450ph2->Draw("SP");
  c2->Update();

  TGraphErrors *dpmean450ph1= depthmean( 450, trlengph1 );
  dpmean450ph1->SetMarkerStyle(20);//circle full 
  dpmean450ph1->SetMarkerSize(0.9); 
//   dpmean450ph1->SetLineColor(2);
  dpmean450ph1->SetLineStyle(2);
//   dpmean450ph1->SetMarkerColor(2);//red  
  dpmean450ph1 ->Draw("SP");
  c2->Update();

  TGraphErrors *dpmean450ph2= depthmean( 450, trlengph2 );
  dpmean450ph2->SetMarkerStyle(29);//circle full 
  dpmean450ph2->SetMarkerSize(0.9); 
//   dpmean450ph2->SetLineColor(4);
  dpmean450ph2->SetLineStyle(2);
//   dpmean450ph2->SetMarkerColor(4);//red  
  dpmean450ph2 ->Draw("SP");
  c2->Update();


  bvsd450ph1-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 450 nm   ");

  bvsd450ph1->GetHistogram()->SetXTitle(" Depth (m) ");
  bvsd450ph1->GetHistogram()->SetYTitle(" Transmission Length (m)");
  bvsd450ph1->GetYaxis()->SetRangeUser(15.,50.);
  bvsd450ph1->GetXaxis()->SetRangeUser(400.,4400.);
  c2->Update();

  TLegend *leg450 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg450->AddEntry(bvsd450ph1,"Photodiode 1","LP");  
  leg450->AddEntry(bvsd450ph2,"Photodiode 2","LP");  
  leg450->SetFillColor(18);
//   leg450->SetHeader("  ");
                                            // use "f" for a box
  leg450->Draw("PS");
  c2->Update();


  ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 375 nm////////////////////////////////////////////// 
  TCanvas *c3 = new TCanvas("c3");
  
  TGraphErrors *bvsd375ph1 = betavsdepth( 375, trlengph1 );
  bvsd375ph1->SetMarkerStyle(20);//circle full 
  bvsd375ph1->SetMarkerSize(0.9); 
//   bvsd375ph1->SetLineColor(2);
//   bvsd375ph1->SetMarkerColor(2);//red  
  bvsd375ph1->Draw("AP");
  c3->Update();

  TGraphErrors *bvsd375ph2 = betavsdepth( 375, trlengph2 );
  bvsd375ph2->SetMarkerStyle(29);//star full  
  bvsd375ph2->SetMarkerSize(0.9); 
//   bvsd375ph2->SetLineColor(4);
//   bvsd375ph2->SetMarkerColor(4);//blue  
  bvsd375ph2->Draw("SP");
  c3->Update();

  TGraphErrors *dpmean375ph1= depthmean( 375, trlengph1 );
  dpmean375ph1->SetMarkerStyle(20);//circle full 
  dpmean375ph1->SetMarkerSize(0.9); 
//   dpmean375ph1->SetLineColor(2);
  dpmean375ph1->SetLineStyle(2);
//   dpmean375ph1->SetMarkerColor(2);//red  
  dpmean375ph1 ->Draw("SP");
  c3->Update();

  TGraphErrors *dpmean375ph2= depthmean( 375, trlengph2 );
  dpmean375ph2->SetMarkerStyle(29);//circle full 
  dpmean375ph2->SetMarkerSize(0.9); 
//   dpmean375ph2->SetLineColor(4);
  dpmean375ph2->SetLineStyle(2);
//   dpmean375ph2->SetMarkerColor(4);//red  
  dpmean375ph2 ->Draw("SP");
  c3->Update();


  bvsd375ph1-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 375 nm   ");

  bvsd375ph1->GetHistogram()->SetXTitle(" Depth (m) ");
  bvsd375ph1->GetHistogram()->SetYTitle(" Transmission Length (m)");
  bvsd375ph1->GetYaxis()->SetRangeUser(15.,50.);
  bvsd375ph1->GetXaxis()->SetRangeUser(400.,4400.);
  c3->Update();

  TLegend *leg375 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg375->AddEntry(bvsd375ph1,"Photodiode 1","LP");  
  leg375->AddEntry(bvsd375ph2,"Photodiode 2","LP");  
  leg375->SetFillColor(18);
//   leg375->SetHeader("  ");
                                            // use "f" for a box
  leg375->Draw("PS");
  c3->Update();


  ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 383 nm////////////////////////////////////////////// 
  TCanvas *c4 = new TCanvas("c4");
  
  TGraphErrors *bvsd383ph1 = betavsdepth( 383, trlengph1 );
  bvsd383ph1->SetMarkerStyle(20);//circle full 
  bvsd383ph1->SetMarkerSize(0.9); 
//   bvsd383ph1->SetLineColor(2);
//   bvsd383ph1->SetMarkerColor(2);//red  
  bvsd383ph1->Draw("AP");
  c4->Update();

  TGraphErrors *bvsd383ph2 = betavsdepth( 383, trlengph2 );
  bvsd383ph2->SetMarkerStyle(29);//star full  
  bvsd383ph2->SetMarkerSize(0.9); 
//   bvsd383ph2->SetLineColor(4);
//   bvsd383ph2->SetMarkerColor(4);//blue  
  bvsd383ph2->Draw("SP");
  c4->Update();

  TGraphErrors *dpmean383ph1= depthmean( 383, trlengph1 );
  dpmean383ph1->SetMarkerStyle(20);//circle full 
  dpmean383ph1->SetMarkerSize(0.9); 
//   dpmean383ph1->SetLineColor(2);
  dpmean383ph1->SetLineStyle(2);
//   dpmean383ph1->SetMarkerColor(2);//red  
  dpmean383ph1 ->Draw("SP");
  c4->Update();

  TGraphErrors *dpmean383ph2= depthmean( 383, trlengph2 );
  dpmean383ph2->SetMarkerStyle(29);//circle full 
  dpmean383ph2->SetMarkerSize(0.9); 
//   dpmean383ph2->SetLineColor(4);
  dpmean383ph2->SetLineStyle(2);
//   dpmean383ph2->SetMarkerColor(4);//red  
  dpmean383ph2 ->Draw("SP");
  c4->Update();


  bvsd383ph1-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 383 nm   ");

  bvsd383ph1->GetHistogram()->SetXTitle(" Depth (m) ");
  bvsd383ph1->GetHistogram()->SetYTitle(" Transmission Length (m)");
  bvsd383ph1->GetYaxis()->SetRangeUser(15.,50.);
  bvsd383ph1->GetXaxis()->SetRangeUser(400.,4400.);
  c4->Update();

  TLegend *leg383 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg383->AddEntry(bvsd383ph1,"Photodiode 1","LP");  
  leg383->AddEntry(bvsd383ph2,"Photodiode 2","LP");  
  leg383->SetFillColor(18);
//   leg383->SetHeader("  ");
                                            // use "f" for a box
  leg383->Draw("PS");
  c4->Update();


  ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 400 nm////////////////////////////////////////////// 
  TCanvas *c5 = new TCanvas("c5");
  
  TGraphErrors *bvsd400ph1 = betavsdepth( 400, trlengph1 );
  bvsd400ph1->SetMarkerStyle(20);//circle full 
  bvsd400ph1->SetMarkerSize(0.9); 
//   bvsd400ph1->SetLineColor(2);
//   bvsd400ph1->SetMarkerColor(2);//red  
  bvsd400ph1->Draw("AP");
  c5->Update();

  TGraphErrors *bvsd400ph2 = betavsdepth( 400, trlengph2 );
  bvsd400ph2->SetMarkerStyle(29);//star full  
  bvsd400ph2->SetMarkerSize(0.9); 
//   bvsd400ph2->SetLineColor(4);
//   bvsd400ph2->SetMarkerColor(4);//blue  
  bvsd400ph2->Draw("SP");
  c5->Update();

  TGraphErrors *dpmean400ph1= depthmean( 400, trlengph1 );
  dpmean400ph1->SetMarkerStyle(20);//circle full 
  dpmean400ph1->SetMarkerSize(0.9); 
//   dpmean400ph1->SetLineColor(2);
  dpmean400ph1->SetLineStyle(2);
//   dpmean400ph1->SetMarkerColor(2);//red  
  dpmean400ph1 ->Draw("SP");
  c5->Update();

  TGraphErrors *dpmean400ph2= depthmean( 400, trlengph2 );
  dpmean400ph2->SetMarkerStyle(29);//circle full 
  dpmean400ph2->SetMarkerSize(0.9); 
//   dpmean400ph2->SetLineColor(4);
  dpmean400ph2->SetLineStyle(2);
//   dpmean400ph2->SetMarkerColor(4);//red  
  dpmean400ph2 ->Draw("SP");
  c5->Update();


  bvsd400ph1-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 400 nm   ");

  bvsd400ph1->GetHistogram()->SetXTitle(" Depth (m) ");
  bvsd400ph1->GetHistogram()->SetYTitle(" Transmission Length (m)");
  bvsd400ph1->GetYaxis()->SetRangeUser(15.,50.);
  bvsd400ph1->GetXaxis()->SetRangeUser(400.,4400.);
  c5->Update();

  TLegend *leg400 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg400->AddEntry(bvsd400ph1,"Photodiode 1","LP");  
  leg400->AddEntry(bvsd400ph2,"Photodiode 2","LP");  
  leg400->SetFillColor(18);
//   leg400->SetHeader("  ");
                                            // use "f" for a box
  leg400->Draw("PS");
  c5->Update();

  ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 425 nm////////////////////////////////////////////// 
  TCanvas *c6 = new TCanvas("c6");
  
  TGraphErrors *bvsd425ph1 = betavsdepth( 425, trlengph1 );
  bvsd425ph1->SetMarkerStyle(20);//circle full 
  bvsd425ph1->SetMarkerSize(0.9); 
//   bvsd425ph1->SetLineColor(2);
//   bvsd425ph1->SetMarkerColor(2);//red  
  bvsd425ph1->Draw("AP");
  c6->Update();

  TGraphErrors *bvsd425ph2 = betavsdepth( 425, trlengph2 );
  bvsd425ph2->SetMarkerStyle(29);//star full  
  bvsd425ph2->SetMarkerSize(0.9); 
//   bvsd425ph2->SetLineColor(4);
//   bvsd425ph2->SetMarkerColor(4);//blue  
  bvsd425ph2->Draw("SP");
  c6->Update();

  TGraphErrors *dpmean425ph1= depthmean( 425, trlengph1 );
  dpmean425ph1->SetMarkerStyle(20);//circle full 
  dpmean425ph1->SetMarkerSize(0.9); 
//   dpmean425ph1->SetLineColor(2);
  dpmean425ph1->SetLineStyle(2);
//   dpmean425ph1->SetMarkerColor(2);//red  
  dpmean425ph1 ->Draw("SP");
  c6->Update();

  TGraphErrors *dpmean425ph2= depthmean( 425, trlengph2 );
  dpmean425ph2->SetMarkerStyle(29);//circle full 
  dpmean425ph2->SetMarkerSize(0.9); 
//   dpmean425ph2->SetLineColor(4);
  dpmean425ph2->SetLineStyle(2);
//   dpmean425ph2->SetMarkerColor(4);//red  
  dpmean425ph2 ->Draw("SP");
  c6->Update();


  bvsd425ph1-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 425 nm   ");

  bvsd425ph1->GetHistogram()->SetXTitle(" Depth (m) ");
  bvsd425ph1->GetHistogram()->SetYTitle(" Transmission Length (m)");
  bvsd425ph1->GetYaxis()->SetRangeUser(15.,50.);
  bvsd425ph1->GetXaxis()->SetRangeUser(400.,4400.);
  c6->Update();

  TLegend *leg425 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg425->AddEntry(bvsd425ph1,"Photodiode 1","LP");  
  leg425->AddEntry(bvsd425ph2,"Photodiode 2","LP");  
  leg425->SetFillColor(18);
//   leg425->SetHeader("  ");
                                            // use "f" for a box
  leg425->Draw("PS");
  c6->Update();


  ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 495 nm////////////////////////////////////////////// 
  TCanvas *c7 = new TCanvas("c7");
  
  TGraphErrors *bvsd495ph1 = betavsdepth( 495, trlengph1 );
  bvsd495ph1->SetMarkerStyle(20);//circle full 
  bvsd495ph1->SetMarkerSize(0.9); 
//   bvsd495ph1->SetLineColor(2);
//   bvsd495ph1->SetMarkerColor(2);//red  
  bvsd495ph1->Draw("AP");
  c7->Update();

  TGraphErrors *bvsd495ph2 = betavsdepth( 495, trlengph2 );
  bvsd495ph2->SetMarkerStyle(29);//star full  
  bvsd495ph2->SetMarkerSize(0.9); 
//   bvsd495ph2->SetLineColor(4);
//   bvsd495ph2->SetMarkerColor(4);//blue  
  bvsd495ph2->Draw("SP");
  c7->Update();

  TGraphErrors *dpmean495ph1= depthmean( 495, trlengph1 );
  dpmean495ph1->SetMarkerStyle(20);//circle full 
  dpmean495ph1->SetMarkerSize(0.9); 
//   dpmean495ph1->SetLineColor(2);
  dpmean495ph1->SetLineStyle(2);
//   dpmean495ph1->SetMarkerColor(2);//red  
  dpmean495ph1 ->Draw("SP");
  c7->Update();

  TGraphErrors *dpmean495ph2= depthmean( 495, trlengph2 );
  dpmean495ph2->SetMarkerStyle(29);//circle full 
  dpmean495ph2->SetMarkerSize(0.9); 
//   dpmean495ph2->SetLineColor(4);
  dpmean495ph2->SetLineStyle(2);
//   dpmean495ph2->SetMarkerColor(4);//red  
  dpmean495ph2 ->Draw("SP");
  c7->Update();


  bvsd495ph1-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 495 nm    ");

  bvsd495ph1->GetHistogram()->SetXTitle(" Depth (m) ");
  bvsd495ph1->GetHistogram()->SetYTitle(" Transmission Length (m)");
  bvsd495ph1->GetYaxis()->SetRangeUser(15.,50.);
  bvsd495ph1->GetXaxis()->SetRangeUser(400.,4400.);
  c7->Update();

  TLegend *leg495 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg495->AddEntry(bvsd495ph1,"Photodiode 1","LP");  
  leg495->AddEntry(bvsd495ph2,"Photodiode 2","LP");  
  leg495->SetFillColor(18);
//   leg495->SetHeader("  ");
                                            // use "f" for a box
  leg495->Draw("PS");
  c7->Update();


 ///////////////////////////////Transmission Length Gia OLA Ta Bathoi 525 nm////////////////////////////////////////////// 
  TCanvas *c8 = new TCanvas("c8");
  
  TGraphErrors *bvsd525ph1 = betavsdepth( 525, trlengph1 );
  bvsd525ph1->SetMarkerStyle(20);//circle full 
  bvsd525ph1->SetMarkerSize(0.9); 
//   bvsd525ph1->SetLineColor(2);
//   bvsd525ph1->SetMarkerColor(2);//red  
  bvsd525ph1->Draw("AP");
  c8->Update();

  TGraphErrors *bvsd525ph2 = betavsdepth( 525, trlengph2 );
  bvsd525ph2->SetMarkerStyle(29);//star full  
  bvsd525ph2->SetMarkerSize(0.9); 
//   bvsd525ph2->SetLineColor(4);
//   bvsd525ph2->SetMarkerColor(4);//blue  
  bvsd525ph2->Draw("SP");
  c8->Update();

  TGraphErrors *dpmean525ph1= depthmean( 525, trlengph1 );
  dpmean525ph1->SetMarkerStyle(20);//circle full 
  dpmean525ph1->SetMarkerSize(0.9); 
//   dpmean525ph1->SetLineColor(2);
  dpmean525ph1->SetLineStyle(2);
//   dpmean525ph1->SetMarkerColor(2);//red  
  dpmean525ph1 ->Draw("SP");
  c8->Update();

  TGraphErrors *dpmean525ph2= depthmean( 525, trlengph2 );
  dpmean525ph2->SetMarkerStyle(29);//circle full 
  dpmean525ph2->SetMarkerSize(0.9); 
//   dpmean525ph2->SetLineColor(4);
  dpmean525ph2->SetLineStyle(2);
//   dpmean525ph2->SetMarkerColor(4);//red  
  dpmean525ph2 ->Draw("SP");
  c8->Update();


  bvsd525ph1-> SetTitle( " PRELIMINARY - NOT FOR DISTRIBUTION. 525 nm    ");

  bvsd525ph1->GetHistogram()->SetXTitle(" Depth (m) ");
  bvsd525ph1->GetHistogram()->SetYTitle(" Transmission Length (m)");
  bvsd525ph1->GetYaxis()->SetRangeUser(15.,50.);
  bvsd525ph1->GetXaxis()->SetRangeUser(400.,4400.);
  c8->Update();

  TLegend *leg525 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg525->AddEntry(bvsd525ph1,"Photodiode 1","LP");  
  leg525->AddEntry(bvsd525ph2,"Photodiode 2","LP");  
  leg525->SetFillColor(18);
//   leg525->SetHeader("  ");
                                            // use "f" for a box
  leg525->Draw("PS");
  c8->Update();




  TFile f("HistTrAllPH.root","recreate");
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  c6->Write();
  c7->Write();
  c8->Write();
  f.Close();
  delete c1;
  delete c2;
  delete c3;
  delete c4;
  delete c5;
  delete c6;
  delete c7;
  delete c8;
  delete bvsd375ph1;
  delete bvsd375ph2;
  delete bvsd383ph1;
  delete bvsd383ph2;
  delete bvsd400ph1;
  delete bvsd400ph2;
  delete bvsd425ph1;
  delete bvsd425ph2;
  delete bvsd450ph1;
  delete bvsd450ph2;
  delete bvsd470ph1;
  delete bvsd470ph2;
  delete bvsd495ph1;
  delete bvsd495ph2;
  delete bvsd525ph1;
  delete bvsd525ph2;
  delete leg375;
  delete leg383;
  delete leg400;
  delete leg425;
  delete leg450;
  delete leg470;
  delete leg495;
  delete leg525;
  delete dpmean375ph1;
  delete dpmean375ph2;
  delete dpmean383ph1;
  delete dpmean383ph2;
  delete dpmean400ph1;
  delete dpmean400ph2;
  delete dpmean450ph1;
  delete dpmean450ph2;
  delete dpmean470ph1;
  delete dpmean470ph2;
  delete dpmean495ph1;
  delete dpmean495ph2;
  delete dpmean525ph1;
  delete dpmean525ph2;
}




void BetaCalculation::calculateallphanddepth (std::map<int, std::map<int, double> >& led383int1, std::map<int, std::map<int, double> >& led400int1, std::map<int, std::map<int, double> >& led470int1, std::map<int, std::map<int, double> >& led525int1, std::map<int, std::map<int, double> >& led383intrms1, std::map<int, std::map<int, double> >& led400intrms1, std::map<int, std::map<int, double> >& led470intrms1, std::map<int, std::map<int, double> >& led525intrms1,std::map<int, std::map<int, double> >& led375int1, std::map<int, std::map<int, double> >& led425int1, std::map<int, std::map<int, double> >& led450int1, std::map<int, std::map<int, double> >& led495int1, std::map<int, std::map<int, double> >& led375intrms1, std::map<int, std::map<int, double> >& led425intrms1, std::map<int, std::map<int, double> >& led450intrms1, std::map<int, std::map<int, double> >& led495intrms1,std::map<int, std::map<int, double> >& led383int2, std::map<int, std::map<int, double> >& led400int2, std::map<int, std::map<int, double> >& led470int2, std::map<int, std::map<int, double> >& led525int2 , std::map<int, std::map<int, double> >& led383intrms2, std::map<int, std::map<int, double> >& led400intrms2, std::map<int, std::map<int, double> >& led470intrms2, std::map<int, std::map<int, double> >& led525intrms2,std::map<int, std::map<int, double> >& led375int2, std::map<int, std::map<int, double> >& led425int2, std::map<int, std::map<int, double> >& led450int2, std::map<int, std::map<int, double> >& led495int2, std::map<int, std::map<int, double> >& led375intrms2, std::map<int, std::map<int, double> >& led425intrms2, std::map<int, std::map<int, double> >& led450intrms2, std::map<int, std::map<int, double> >& led495intrms2){



  //Depths that will be processed
  std::vector<int> DepthsToBeProccessed;

  DepthsToBeProccessed.push_back(4100);
  DepthsToBeProccessed.push_back(3400);
  DepthsToBeProccessed.push_back(2500);
  DepthsToBeProccessed.push_back(5001000);
  DepthsToBeProccessed.push_back(10001500);
  DepthsToBeProccessed.push_back(15002000);
  DepthsToBeProccessed.push_back(20002500);
  DepthsToBeProccessed.push_back(25003400);
  DepthsToBeProccessed.push_back(34004100);
  DepthsToBeProccessed.push_back(25002000);
  DepthsToBeProccessed.push_back(34002500);
  DepthsToBeProccessed.push_back(41003400);
  DepthsToBeProccessed.push_back(20001500);
  DepthsToBeProccessed.push_back(15001000);
  DepthsToBeProccessed.push_back(1000500);




  // Create a file

  std::map<int,std::map<double,double> > fitlength383ph1; 
  std::map<int,std::map<double,double> > fitlength400ph1; 
  std::map<int,std::map<double,double> > fitlength470ph1; 
  std::map<int,std::map<double,double> > fitlength525ph1; 
  std::map<int,std::map<double,double> > fitlength375ph1; 
  std::map<int,std::map<double,double> > fitlength425ph1;
  std::map<int,std::map<double,double> > fitlength450ph1; 
  std::map<int,std::map<double,double> > fitlength495ph1;

  std::map<int,std::vector<TransmissionLength> > trlengph1;

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

    fitlength383ph1[(*dep)] = fitbetamethodph1(led383int1[(*dep)],led383intrms1[(*dep)]);
    fitlength400ph1[(*dep)] = fitbetamethodph1(led400int1[(*dep)],led400intrms1[(*dep)]);
    fitlength470ph1[(*dep)] = fitbetamethodph1(led470int1[(*dep)],led470intrms1[(*dep)]);
    fitlength525ph1[(*dep)] = fitbetamethodph1(led525int1[(*dep)],led525intrms1[(*dep)]);
    fitlength375ph1[(*dep)] = fitbetamethodph1(led375int1[(*dep)],led375intrms1[(*dep)]);
    fitlength425ph1[(*dep)] = fitbetamethodph1(led425int1[(*dep)],led425intrms1[(*dep)]);
    fitlength450ph1[(*dep)] = fitbetamethodph1(led450int1[(*dep)],led450intrms1[(*dep)]);
    fitlength495ph1[(*dep)] = fitbetamethodph1(led495int1[(*dep)],led495intrms1[(*dep)]);


  for (std::map<double,double>::iterator it =fitlength383ph1[(*dep)].begin();it!=fitlength383ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 383. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength400ph1[(*dep)].begin();it!=fitlength400ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 400. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength470ph1[(*dep)].begin();it!=fitlength470ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 470. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength525ph1[(*dep)].begin();it!=fitlength525ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 525. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength375ph1[(*dep)].begin();it!=fitlength375ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 375. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength425ph1[(*dep)].begin();it!=fitlength425ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 425. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength450ph1[(*dep)].begin();it!=fitlength450ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 450. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength495ph1[(*dep)].begin();it!=fitlength495ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 495. , (*it).first,(*it).second ) );
  }

  } // End on loop over Depths


  // Create a file

  std::map<int,std::map<double,double> > fitlength383ph2; 
  std::map<int,std::map<double,double> > fitlength400ph2; 
  std::map<int,std::map<double,double> > fitlength470ph2; 
  std::map<int,std::map<double,double> > fitlength525ph2; 
  std::map<int,std::map<double,double> > fitlength375ph2; 
  std::map<int,std::map<double,double> > fitlength425ph2;
  std::map<int,std::map<double,double> > fitlength450ph2; 
  std::map<int,std::map<double,double> > fitlength495ph2;

  std::map<int,std::vector<TransmissionLength> > trlengph2;

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

    fitlength383ph2[(*dep)] = fitbetamethodph2(led383int2[(*dep)],led383intrms2[(*dep)]);
    fitlength400ph2[(*dep)] = fitbetamethodph2(led400int2[(*dep)],led400intrms2[(*dep)]);
    fitlength470ph2[(*dep)] = fitbetamethodph2(led470int2[(*dep)],led470intrms2[(*dep)]);
    fitlength525ph2[(*dep)] = fitbetamethodph2(led525int2[(*dep)],led525intrms2[(*dep)]);
    fitlength375ph2[(*dep)] = fitbetamethodph2(led375int2[(*dep)],led375intrms2[(*dep)]);
    fitlength425ph2[(*dep)] = fitbetamethodph2(led425int2[(*dep)],led425intrms2[(*dep)]);
    fitlength450ph2[(*dep)] = fitbetamethodph2(led450int2[(*dep)],led450intrms2[(*dep)]);
    fitlength495ph2[(*dep)] = fitbetamethodph2(led495int2[(*dep)],led495intrms2[(*dep)]);


  for (std::map<double,double>::iterator it =fitlength383ph2[(*dep)].begin();it!=fitlength383ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 383. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength400ph2[(*dep)].begin();it!=fitlength400ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 400. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength470ph2[(*dep)].begin();it!=fitlength470ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 470. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength525ph2[(*dep)].begin();it!=fitlength525ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 525. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength375ph2[(*dep)].begin();it!=fitlength375ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 375. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength425ph2[(*dep)].begin();it!=fitlength425ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 425. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength450ph2[(*dep)].begin();it!=fitlength450ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 450. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength495ph2[(*dep)].begin();it!=fitlength495ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 495. , (*it).first,(*it).second ) );
  }

  } // End on loop over Depths

 ///////////////////////////////Transmission Length Sinartisi WaveLength 2500,3400,4100m////////////////////////////////////////////// 
  TCanvas *c3 = new TCanvas("c3");
   
  TGraphErrors *translength4100 = fitbetamethodgrapherrorph1( trlengph1[4100] );
  translength4100->SetMarkerStyle(20);
  translength4100->SetMarkerSize(0.9); 
  translength4100->SetMarkerColor(2);  
  translength4100->SetLineColor(2);
  translength4100->Draw("AP");
  c3->Update();

  TGraphErrors *translength3400 = fitbetamethodgrapherrorph1( trlengph1[3400] );
  translength3400->SetMarkerStyle(20);
  translength3400->SetMarkerSize(0.9); 
  translength3400->SetMarkerColor(4); 
  translength3400->SetLineColor(4);
  translength3400->Draw("PS");
  c3->Update();

  TGraphErrors *translength2500 = fitbetamethodgrapherrorph1( trlengph1[2500] );
  translength2500->SetMarkerStyle(20); 
  translength2500->SetMarkerSize(0.9); 
  translength2500->SetMarkerColor(8); 
  translength2500->SetLineColor(8);
  translength2500->Draw("PS");
  c3->Update();

  TLegend *leg = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg->AddEntry(translength4100,"4100 m Photodiode 1","LP");  
  leg->AddEntry(translength3400,"3400 m Photodiode 1","LP");  
  leg->AddEntry(translength2500,"2500 m Photodiode 1","LP");  
  leg->SetFillColor(18);
  leg->SetHeader(" Depth ");
                                            // use "f" for a box
  leg->Draw("PS");
  c3->Update();

  translength4100 -> SetTitle( "  	PRELIMINARY. NOT FOR DISTRIBUTION.  ");

  translength4100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength4100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength4100 ->GetYaxis()->SetRangeUser(15.,50.);
  translength4100 ->GetXaxis()->SetRangeUser(360.,560.);
  c3->Update();

  ///////////////////////////////Transmission Length Sinartisi WaveLength 2500,3400,4100m////////////////////////////////////////////// 
   
  TGraphErrors *translength24100 = fitbetamethodgrapherrorph2( trlengph2[4100] );
  translength24100->SetMarkerStyle(29);
  translength24100->SetMarkerSize(0.9); 
  translength24100->SetMarkerColor(2);  
  translength24100->SetLineColor(2);
  translength24100->Draw("SP");
  c3->Update();

  TGraphErrors *translength23400 = fitbetamethodgrapherrorph2( trlengph2[3400] );
  translength23400->SetMarkerStyle(29);
  translength23400->SetMarkerSize(0.9); 
  translength23400->SetMarkerColor(4); 
  translength23400->SetLineColor(4);
  translength23400->Draw("PS");
  c3->Update();

  TGraphErrors *translength22500 = fitbetamethodgrapherrorph2( trlengph2[2500] );
  translength22500->SetMarkerStyle(29); 
  translength22500->SetMarkerSize(0.9); 
  translength22500->SetMarkerColor(8); 
  translength22500->SetLineColor(8);
  translength22500->Draw("PS");
  c3->Update();

                                         //of pad dimensions
  leg->AddEntry(translength24100,"4100 m Photodiode 2","LP");  
  leg->AddEntry(translength23400,"3400 m Photodiode 2","LP");  
  leg->AddEntry(translength22500,"2500 m Photodiode 2","LP");  
  leg->SetFillColor(18);
  leg->SetHeader(" Depth ");
                                            // use "f" for a box
  leg->Draw("PS");
  c3->Update();

  translength4100 -> SetTitle( "  	PRELIMINARY. NOT FOR DISTRIBUTION.  ");

  translength4100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength4100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength4100 ->GetYaxis()->SetRangeUser(15.,50.);
  translength4100 ->GetXaxis()->SetRangeUser(360.,560.);
  c3->Update();


 //  ////// Transmission Length Sinartisi WaveLength 500-1000,1000-1500,1500-2000m////////////////////////////////////////////// 
   
//   TGraphErrors *translength15002000 = fitbetamethodgrapherrorph1( trlengph1[15002000] );
//   translength15002000->SetMarkerStyle(23);
//   translength15002000->SetMarkerSize(0.9); 
//   translength15002000->SetMarkerColor(5);
//   translength15002000->SetLineColor(5);
//   translength15002000->Draw("SP");
//   c3->Update();

//   TGraphErrors *translength10001500 = fitbetamethodgrapherrorph1( trlengph1[10001500] );
//   translength10001500->SetMarkerStyle(24);
//   translength10001500->SetMarkerSize(0.9); 
//   translength10001500->SetMarkerColor(6);
//   translength10001500->SetLineColor(6);
//   translength10001500->Draw("PS");
//   c3->Update();

//   TGraphErrors *translength5001000 = fitbetamethodgrapherrorph1( trlengph1[5001000] );
//   translength5001000->SetMarkerStyle(25);
//   translength5001000->SetMarkerSize(0.9); 
//   translength5001000->SetMarkerColor(7);
//   translength5001000->SetLineColor(7);
//   translength5001000->Draw("PS");
//   c3->Update();

//   leg->AddEntry(translength15002000,"1500-2000 m","LP");  
//   leg->AddEntry(translength10001500,"1000-1500 m","LP");  
//   leg->AddEntry(translength5001000,"500-1000 m","LP");  
//   leg->SetFillColor(18);
//   leg->SetHeader(" Depth ");
//                                             // use "f" for a box
//   leg->Draw("PS");
//   c3->Update();

//   translength15002000 -> SetTitle( "  	PRELIMINARY. NOT FOR DISTRIBUTION. ");

//   translength15002000 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
//   translength15002000 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   translength15002000 ->GetYaxis()->SetRangeUser(15.,50.);
//   translength15002000 ->GetXaxis()->SetRangeUser(360.,560.);
//   c3->Update();

//   /////////////Transmission Length Sinartisi WaveLength 2000-2500,2500-3400,3400-4100m////////////////////////////////////////////// 
   
//   TGraphErrors *translength34004100 = fitbetamethodgrapherrorph1( trlengph1[34004100] );
//   translength34004100->SetMarkerStyle(26);
//   translength34004100->SetMarkerSize(0.9); 
//   translength34004100->SetMarkerColor(8);
//   translength34004100->SetLineColor(8);
//   translength34004100->Draw("SP");
//   c3->Update();

//   TGraphErrors *translength25003400 = fitbetamethodgrapherrorph1( trlengph1[25003400] );
//   translength25003400->SetMarkerStyle(27);
//   translength25003400->SetMarkerSize(0.9); 
//   translength25003400->SetMarkerColor(9);
//   translength25003400->SetLineColor(9);
//   translength25003400->Draw("PS");
//   c3->Update();

//   TGraphErrors *translength20002500 = fitbetamethodgrapherrorph1( trlengph1[20002500] );
//   translength20002500->SetMarkerStyle(28); 
//   translength20002500->SetMarkerSize(0.9); 
//   translength20002500->SetMarkerColor(40);
//   translength20002500->SetLineColor(40);
//   translength20002500->Draw("PS");
//   c3->Update();

//   leg->AddEntry(translength34004100,"3400-4100 m","LP");  
//   leg->AddEntry(translength25003400,"2500-3400 m","LP");  
//   leg->AddEntry(translength20002500,"2000-2500 m","LP");  
//   leg->SetFillColor(18);
//   leg->SetHeader(" Depth ");
                                           
//   leg->Draw("PS");
//   c3->Update();

//   translength34004100 -> SetTitle( "  	PRELIMINARY. NOT FOR DISTRIBUTION. ");

//   translength34004100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
//   translength34004100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   translength34004100 ->GetYaxis()->SetRangeUser(15.,50.);
//   translength34004100 ->GetXaxis()->SetRangeUser(360.,560.);
//   c3->Update();

//   /////////////Transmission Length Sinartisi WaveLength 4100-3400,3400-2500,2500-2000m////////////////////////////////////////////// 

   
//    TGraphErrors *translength41003400 = fitbetamethodgrapherrorph1( trlengph1[41003400] );
//   translength41003400->SetMarkerStyle(29);
//   translength41003400->SetMarkerSize(0.9); 
//   translength41003400->SetMarkerColor(41);
//   translength41003400->SetLineColor(41);
//   translength41003400->Draw("SP");
//   c3 ->Update();

//   TGraphErrors *translength34002500 = fitbetamethodgrapherrorph1( trlengph1[34002500] );
//   translength34002500->SetMarkerStyle(2);
//   translength34002500->SetMarkerSize(0.9); 
//   translength34002500->SetMarkerColor(42);
//   translength34002500->SetLineColor(42);
//   translength34002500->Draw("PS");
//   c3 ->Update();

//   TGraphErrors *translength25002000 = fitbetamethodgrapherrorph1( trlengph1[25002000] );
//   translength25002000->SetMarkerStyle(3); 
//   translength25002000->SetMarkerSize(0.9); 
//   translength25002000->SetMarkerColor(43); 
//   translength25002000->SetLineColor(43);
//   translength25002000->Draw("PS");
//   c3 ->Update();

//   leg ->AddEntry(translength41003400,"4100-3400 m","LP");  
//   leg ->AddEntry(translength34002500,"3400-2500 m","LP");  
//   leg ->AddEntry(translength25002000,"2500-2000 m","LP");  
//   leg ->SetFillColor(18);
//   leg ->SetHeader(" Depth ");
//                                             // use "f" for a box
//   leg ->Draw("PS");
//   c3 ->Update();

//   translength41003400 -> SetTitle( "  	PRELIMINARY. NOT FOR DISTRIBUTION. ");

//   translength41003400 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
//   translength41003400 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   translength41003400 ->GetYaxis()->SetRangeUser(15.,50.);
//   translength41003400 ->GetXaxis()->SetRangeUser(360.,560.);
//   c3 ->Update();

//   /////////////Transmission Length Sinartisi WaveLength 2000-500m////////////////////////////////////////////// 

   
//   TGraphErrors *translength20001500 = fitbetamethodgrapherrorph1( trlengph1[20001500] );
//   translength20001500->SetMarkerStyle(31);
//   translength20001500->SetMarkerSize(0.9); 
//   translength20001500->SetMarkerColor(44); 
//   translength20001500->SetLineColor(44);
//   translength20001500->Draw("SP");
//   c3 ->Update();

//   TGraphErrors *translength15001000 = fitbetamethodgrapherrorph1( trlengph1[15001000] );
//   translength15001000->SetMarkerStyle(5);
//   translength15001000->SetMarkerSize(0.9); 
//   translength15001000->SetMarkerColor(45);
//   translength15001000->SetLineColor(45);
//   translength15001000->Draw("PS");
//   c3 ->Update();

//   TGraphErrors *translength1000500 = fitbetamethodgrapherrorph1( trlengph1[1000500] );
//   translength1000500->SetMarkerStyle(30);
//   translength1000500->SetMarkerSize(0.9); 
//   translength1000500->SetMarkerColor(46); 
//   translength1000500->SetLineColor(46);
//   translength1000500->Draw("PS");
//   c3 ->Update();

//   leg ->AddEntry(translength20001500,"2000-1500 m","LP");  
//   leg ->AddEntry(translength15001000,"1500-1000 m","LP");  
//   leg ->AddEntry(translength1000500,"1000-500 m","LP");  
//   leg ->SetFillColor(18);
//   leg ->SetHeader(" Depth ");
//                                             // use "f" for a box
//   leg ->Draw("PS");
//   c3 ->Update();

//   translength20001500 -> SetTitle( "  	PRELIMINARY. NOT FOR DISTRIBUTION. ");

//   translength20001500 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
//   translength20001500 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
//   translength20001500 ->GetYaxis()->SetRangeUser(15.,50.);
//   translength20001500 ->GetXaxis()->SetRangeUser(360.,560.);
//   c3 ->Update();



  TFile f("HistTrvsWLforAllDepth.root","recreate");
  c3->Write();
  f.Close();
  delete c3;
  delete translength4100;
  delete translength3400;
  delete translength2500;
  delete translength24100;
  delete translength23400;
  delete translength22500;
//   delete translength41003400;
//   delete translength34002500;
//   delete translength25002000;
//   delete translength20001500;
//   delete translength15001000;
//   delete translength1000500;
  delete leg;
  

}





