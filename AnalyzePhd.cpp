#include <iostream>
#include <iomanip>
#include <Event.hh>
#include <Cycle.hh>
#include <Led.hh>
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "Utilities.hh"
#include "AnalyzePhd.hh"
#include "Intensity.hh"
#include "TPostScript.h"
#include "CheckLAMSSystem.hh"
#include "TH2F.h"
#include "TFile.h"
#include <algorithm>

AnalyzePhd::AnalyzePhd(int& Dep, int& Sou, int& Dis, std::vector<Event*>& Events)
  : m_dep(Dep),
    m_sou(Sou),
    m_dis(Dis),
    m_Events(Events)
{}

AnalyzePhd::~AnalyzePhd()
{}


std::vector<int> AnalyzePhd::darkcurrentfinder(std::vector<int>& allevents, int& tmstart, int& tmend)
{
  std::vector<int> ldevents;
  std::vector<int> ledflashevents;

  for (int i=tmstart; i<tmend+1; ++i){
    ldevents.push_back( allevents[i] );
  }
 
  int oft = 400;

  for (unsigned int i= oft; i<(ldevents.size()-oft);++i){
    ledflashevents.push_back( ldevents[i]  );
  }

  return ledflashevents;

}



std::vector<int> AnalyzePhd::ledflashfinder(std::vector<int>& allevents, int& tmstart, int& tmend, double& maxpercent)
{
  std::vector<int> ldevents;
  std::vector<int> ledflashevents;

  for (int i=tmstart; i<tmend+1; ++i){
    ldevents.push_back( allevents[i] );
  }
 
 int max = *max_element( ldevents.begin(), ldevents.end());
 //   std::cout<<max <<std::endl;

  for (std::vector<int>::iterator l= ldevents.begin(); l!=ldevents.end(); ++l){
    if (   (*l) >  maxpercent * max ) { ledflashevents.push_back( (*l) ); }
//     std::cout<< (*l)  <<std::endl;
  }

  return ledflashevents;

}

double AnalyzePhd::ledflashstarttimefinder(std::vector<int>& allevents, int& tmstart, int& tmend, double& maxpercent)
{

  int ledflashtimestart=0;
   
  std::vector<int> ledflashevents = ledflashfinder(allevents,tmstart,tmend, maxpercent);
 
  for (int i= tmstart; i<tmend+1;++i ) { 
    if( allevents[i]== ledflashevents.front() ){
      ledflashtimestart=i;break;
    }
  }
  return ledflashtimestart * 0.01 ;
  
}

double AnalyzePhd::ledflashendtimefinder(std::vector<int>& allevents, int& tmstart, int& tmend, double& maxpercent)
{

  int ledflashendtime=0;
   
  std::vector<int> ledflashevents = ledflashfinder(allevents,tmstart,tmend, maxpercent);
//   std::cout<<  *ledflashevents.end() <<std::endl;
//   std::cout<<  ledflashevents[ledflashevents.size()-1] <<std::endl;
//   for (  std::vector<int>::iterator ldf= ledflashevents.begin();ldf!=ledflashevents.end();++ldf){
//     if ((*ldf)<2000){std::cout<<  (*ldf) << std::endl;}
//   }


  for (int i=tmend ; i>tmstart-1;--i ) { 
//     std::cout<<  ledflashevents[] << std::endl;
//     if ( (*ledflashevents.end() <)
//    if( allevents[i]==  ledflashevents[ledflashevents.size()-1] ){
   if( allevents[i]==  ledflashevents.back() ){
//     std::cout<< i << std::endl;
      ledflashendtime=i;break;
    }
  }
  return ledflashendtime * 0.01 ;
  
}


std::map<int,std::map<int, std::vector<Intensity> > > AnalyzePhd::analysisph1(int& Threshold, int& FirstEventsToDisregard, int& TotalEvents)
{
  //Input Parameters 
  double maxpc383nm = 0.99;
  double maxpc400nm = 0.99;
  double maxpc470nm = 0.99;
  double maxpc525nm = 0.99;
  double maxpc375nm = 0.99;
  double maxpc425nm = 0.99;
  double maxpc450nm = 0.99;
  double maxpc495nm = 0.99;

  int ledoncriticalvalueph1sou1 = 0;
  int ledoncriticalvalueph1sou2 = 0;

  switch ( m_dis ) {	   
  case 10: ledoncriticalvalueph1sou1 = 8000;ledoncriticalvalueph1sou2 = 8000; break;
  case 15: ledoncriticalvalueph1sou1 = 4000;ledoncriticalvalueph1sou2 = 4000; break;
  case 17: ledoncriticalvalueph1sou1 = 4000;ledoncriticalvalueph1sou2 = 4000; break;
  case 22: ledoncriticalvalueph1sou1 = 2000;ledoncriticalvalueph1sou2 = 2000; break;
  }

       
  
int clockcriticalvalueph1sou1 = 1200;
int clockcriticalvalueph1sou2 = 1200;

  std::vector<Led>  led383nm;
  std::vector<Led>  led400nm;
  std::vector<Led>  led470nm;
  std::vector<Led>  led525nm;
  std::vector<Led>  led375nm;
  std::vector<Led>  led425nm;
  std::vector<Led>  led450nm;
  std::vector<Led>  led495nm;
  std::vector<Led>  darkcurrent;
  std::vector<Cycle> ledcycle;
  std::vector<int> alltimevents;
  std::map<int, std::map<int, std::vector<Intensity> > > ledintensity;
  
  int j=0;  
  for (std::vector<Event*>::iterator e = m_Events.begin(); e != m_Events.end(); ++e) {
//     if (j>FirstEventsToDisregard && j< TotalEvents && (*e)->GetPhdiode1()> Threshold ){
       alltimevents.push_back((*e)->GetPhdiode1());
//        std::cout<<(*e)->GetPhdiode1()<<std::endl;
//       }
    ++j;
  }

//   for (unsigned int i = 0; i<timestartregions.size();++i){
//     std::cout<<  timestartregions[i]  <<std::endl;
//     std::cout<<  timeendregions[i+1]  <<std::endl;
//   }
//  std::cout<<  timestartregions.size()  <<std::endl;
//   std::cout<<  timeendregions  <<std::endl;
  //Find the patterns
 
  std::vector<int> ledisonregion;
  Utilities util;
  TFile c(("Source"+ util.IntToString(m_sou) +"Phd1_Check_" + util.IntToString(m_dis) +  "_mDep" + util.IntToString(m_dep) + "m.root").c_str(),"recreate");
    
  CheckLAMSSystem checksystem(m_dep,m_sou,m_dis);

  std::vector<int> timestartregions;
  std::vector<int> timeendregions;


  switch (m_sou){
  case 1: 
    {
      for (unsigned int i = 0; i< alltimevents.size();++i){
	if( alltimevents[i]> ledoncriticalvalueph1sou1) {ledisonregion.push_back(i);}
      }
  
      for (unsigned int i = 0; i< ledisonregion.size();++i){
	if( ledisonregion[i+1]- ledisonregion[i]>1 ){
	  timestartregions.push_back( ledisonregion[i+1] );
	  timeendregions.push_back( ledisonregion[i] );
	}
      }
      for (unsigned int i = 0; i<timeendregions.size();++i){

	//     std::cout<<  timestartregions[i]  -  timeendregions[i]  <<std::endl;
    
	if ( timestartregions[i]-timeendregions[i]> clockcriticalvalueph1sou1 && 
	     timeendregions[i+5]>timestartregions[i+4] && 
	     timeendregions[i+4]>timestartregions[i+3] && 
	     timeendregions[i+3]>timestartregions[i+2] && 
	     timeendregions[i+2]>timestartregions[i+1] && 
	     timeendregions[i+1]>timestartregions[i]){
	
	
	  led383nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm), 
				   ledflashfinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm) ) ); 
      
	  led400nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm), 
				   ledflashfinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm) ) ); 
	
	  led470nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm), 
				   ledflashfinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm) ) ); 
	
	  led525nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm), 
				   ledflashfinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm) ) ); 
	
	  darkcurrent.push_back( Led( ledflashendtimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm), 
				      ledflashstarttimefinder(alltimevents, timestartregions[i+4], timeendregions[i+5], maxpc383nm), 
				      darkcurrentfinder(alltimevents, timeendregions[i+4], timestartregions[i+4]) ) ); 
      
	  ledcycle.push_back( Cycle( ledflashstarttimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+4], timeendregions[i+5], maxpc383nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm) ) );
	
	}
      
      
      }  
      //Checking the LAMS
    
      checksystem.checkeventcounter(m_Events); //Auti i sinartisi einai mono sti mia fotodiodo afou ston counter mas endiaferoun mono ta data apo ta diaforetika bathoi
      TH1F* chkcycle = checksystem.checkcycle(ledcycle);
      TH1F* chkled383 = checksystem.checkled383(led383nm);
      TH1F* chkled400 = checksystem.checkled400(led400nm);
      TH1F* chkled470 = checksystem.checkled470(led470nm);
      TH1F* chkled525 = checksystem.checkled525(led525nm);
      TH1F* chkL383to400 = checksystem.checkL383to400(ledcycle);
      TH1F* chkL400to470 = checksystem.checkL400to470(ledcycle);
      TH1F* chkL470to525 = checksystem.checkL470to525(ledcycle);
      TH1F* chkledcycle383 = checksystem.checkled383cycle(led383nm);
      TH1F* chkledcycle400 = checksystem.checkled400cycle(led400nm);
      TH1F* chkledcycle470 = checksystem.checkled470cycle(led470nm);
      TH1F* chkledcycle525 = checksystem.checkled525cycle(led525nm);
      TH1F* chkLastLedtoNewCycleStart=checksystem.checkLastLedtoNewCycleStart(ledcycle,led525nm);
      TH1F* ldflplat383=checksystem.ledflashplato383(led383nm);
      TH1F* ldflplat400=checksystem.ledflashplato400(led400nm);
      TH1F* ldflplat470=checksystem.ledflashplato470(led470nm);
      TH1F* ldflplat525=checksystem.ledflashplato525(led525nm);
      TH1F* darkintensity= checksystem.lednoflash(darkcurrent);
      ledintensity[m_dep][m_sou].push_back( Intensity(383, ldflplat383->GetMean()-darkintensity->GetMean(),ldflplat383->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(400, ldflplat400->GetMean()-darkintensity->GetMean(),ldflplat400->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(470, ldflplat470->GetMean()-darkintensity->GetMean(),ldflplat470->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(525, ldflplat525->GetMean()-darkintensity->GetMean(),ldflplat525->GetRMS(), m_dis) );
    
      chkcycle->Write();
      chkled383->Write();
      chkled400->Write();
      chkled470->Write();
      chkled525->Write();
      chkL383to400->Write();
      chkL400to470->Write();
      chkL470to525->Write();
      chkledcycle383->Write();
      chkledcycle400->Write();
      chkledcycle470->Write();
      chkledcycle525->Write();
      chkLastLedtoNewCycleStart->Write();
      ldflplat383->Write();
      ldflplat400->Write();
      ldflplat470->Write();
      ldflplat525->Write();
      darkintensity->Write();
    
      delete chkcycle;
      delete chkled383;
      delete chkled400;
      delete chkled470;
      delete chkled525;
      delete chkL383to400;
      delete chkL400to470;
      delete chkL470to525;
      delete chkledcycle383;
      delete chkledcycle400;
      delete chkledcycle470;
      delete chkledcycle525;
      delete chkLastLedtoNewCycleStart;
      delete ldflplat383;
      delete ldflplat400;
      delete ldflplat470;
      delete ldflplat525;
      delete darkintensity;
    
    }
    break;
    
  case 2:   
    {
      for (unsigned int i = 0; i< alltimevents.size();++i){
	if( alltimevents[i]> ledoncriticalvalueph1sou2) {ledisonregion.push_back(i);}
      }
    
      for (unsigned int i = 0; i< ledisonregion.size();++i){
	if( ledisonregion[i+1]- ledisonregion[i]>1 ){
	  timestartregions.push_back( ledisonregion[i+1] );
	  timeendregions.push_back( ledisonregion[i] );
	}
      } 
      for (unsigned int i = 0; i<timeendregions.size();++i){
      
	//     std::cout<<  timestartregions[i]  -  timeendregions[i]  <<std::endl;
      
	if ( timestartregions[i]-timeendregions[i]> clockcriticalvalueph1sou2 && 
	     timeendregions[i+5]>timestartregions[i+4] && 
	     timeendregions[i+4]>timestartregions[i+3] && 
	     timeendregions[i+3]>timestartregions[i+2] && 
	     timeendregions[i+2]>timestartregions[i+1] && 
	     timeendregions[i+1]>timestartregions[i]){
	
	
	  led375nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm), 
				   ledflashfinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm) ) ); 
	
	  led425nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm), 
				   ledflashfinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm) ) ); 
	
	  led450nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm), 
				   ledflashfinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm) ) ); 
	
	  led495nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm), 
				   ledflashfinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm) ) ); 
	
	  darkcurrent.push_back( Led( ledflashendtimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm), 
				      ledflashstarttimefinder(alltimevents, timestartregions[i+4], timeendregions[i+5], maxpc375nm), 
				      darkcurrentfinder(alltimevents, timeendregions[i+4], timestartregions[i+4]) ) ); 

	  ledcycle.push_back( Cycle( ledflashstarttimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+4], timeendregions[i+5], maxpc375nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm) ) );
	
	}
      
      
      }  

      //Checking the LAMS

      checksystem.checkeventcounter(m_Events); //Auti i sinartisi einai mono sti mia fotodiodo afou ston counter mas endiaferoun mono ta data apo ta diaforetika bathoi
      TH1F* chkcycle = checksystem.checkcycle(ledcycle);
      TH1F* chkled375 = checksystem.checkled375(led375nm);
      TH1F* chkled425 = checksystem.checkled425(led425nm);
      TH1F* chkled450 = checksystem.checkled450(led450nm);
      TH1F* chkled495 = checksystem.checkled495(led495nm);
      TH1F* chkL375to425 = checksystem.checkL375to425(ledcycle);
      TH1F* chkL425to450 = checksystem.checkL425to450(ledcycle);
      TH1F* chkL450to495 = checksystem.checkL450to495(ledcycle);
      TH1F* chkledcycle375 = checksystem.checkled375cycle(led375nm);
      TH1F* chkledcycle425 = checksystem.checkled425cycle(led425nm);
      TH1F* chkledcycle450 = checksystem.checkled450cycle(led450nm);
      TH1F* chkledcycle495 = checksystem.checkled495cycle(led495nm);
      TH1F* chkLastLedtoNewCycleStart=checksystem.checkLastLedtoNewCycleStart(ledcycle,led495nm);
      TH1F* ldflplat375=checksystem.ledflashplato375(led375nm);
      TH1F* ldflplat425=checksystem.ledflashplato425(led425nm);
      TH1F* ldflplat450=checksystem.ledflashplato450(led450nm);
      TH1F* ldflplat495=checksystem.ledflashplato495(led495nm);
      TH1F* darkintensity= checksystem.lednoflash(darkcurrent);
      ledintensity[m_dep][m_sou].push_back( Intensity(375, ldflplat375->GetMean()-darkintensity->GetMean(),ldflplat375->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(425, ldflplat425->GetMean()-darkintensity->GetMean(),ldflplat425->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(450, ldflplat450->GetMean()-darkintensity->GetMean(),ldflplat450->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(495, ldflplat495->GetMean()-darkintensity->GetMean(),ldflplat495->GetRMS(), m_dis) );

      chkcycle->Write();
      chkled375->Write();
      chkled425->Write();
      chkled450->Write();
      chkled495->Write();
      chkL375to425->Write();
      chkL425to450->Write();
      chkL450to495->Write();
      chkledcycle375->Write();
      chkledcycle425->Write();
      chkledcycle450->Write();
      chkledcycle495->Write();
      chkLastLedtoNewCycleStart->Write();
      ldflplat375->Write();
      ldflplat425->Write();
      ldflplat450->Write();
      ldflplat495->Write();
      darkintensity->Write();
  
      delete chkcycle;
      delete chkled375;
      delete chkled425;
      delete chkled450;
      delete chkled495;
      delete chkL375to425;
      delete chkL425to450;
      delete chkL450to495;
      delete chkledcycle375;
      delete chkledcycle425;
      delete chkledcycle450;
      delete chkledcycle495;
      delete chkLastLedtoNewCycleStart;
      delete ldflplat375;
      delete ldflplat425;
      delete ldflplat450;
      delete ldflplat495;
      delete darkintensity;

    }
    break;
    
  }

  c.Close();

  return ledintensity;
  
  
  
}



std::map<int, std::map<int, std::vector<Intensity> > > AnalyzePhd::analysisph2(int& Threshold, int& FirstEventsToDisregard, int& TotalEvents)
{
  //Input Parameters 
  double maxpc383nm = 0.99;
  double maxpc400nm = 0.99;
  double maxpc470nm = 0.99;
  double maxpc525nm = 0.99;
  double maxpc375nm = 0.99;
  double maxpc425nm = 0.99;
  double maxpc450nm = 0.99;
  double maxpc495nm = 0.99;

  int ledoncriticalvalueph2sou1 = 0;
  int ledoncriticalvalueph2sou2 = 0;
  int clockcriticalvalueph2sou1 = 0;
  int clockcriticalvalueph2sou2 = 0;

  switch ( m_dis ) {	   
  case 10: 
    ledoncriticalvalueph2sou1 = 8000;
    ledoncriticalvalueph2sou2 = 8000;
    clockcriticalvalueph2sou1 = 1000;
    clockcriticalvalueph2sou2 = 1000;
    break;
  case 15: 
    ledoncriticalvalueph2sou1 = 6000;
    ledoncriticalvalueph2sou2 = 4000; 
    clockcriticalvalueph2sou1 = 950;
    clockcriticalvalueph2sou2 = 950;
    break;
  case 17: 
    ledoncriticalvalueph2sou1 = 4000;
    ledoncriticalvalueph2sou2 = 4000; 
    clockcriticalvalueph2sou1 = 750;
    clockcriticalvalueph2sou2 = 750;
    break;
  case 22: 
    ledoncriticalvalueph2sou1 = 2000;
    ledoncriticalvalueph2sou2 = 2000; 
    clockcriticalvalueph2sou1 = 500;
    clockcriticalvalueph2sou2 = 500; 
    break;
  }
  

      
  std::vector<Led>  led383nm;
  std::vector<Led>  led400nm;
  std::vector<Led>  led470nm;
  std::vector<Led>  led525nm;
  std::vector<Led>  led375nm;
  std::vector<Led>  led425nm;
  std::vector<Led>  led450nm;
  std::vector<Led>  led495nm;
  std::vector<Led>  darkcurrent;
  std::vector<Cycle> ledcycle;
  std::vector<int> alltimevents;
  std::map<int, std::map<int, std::vector<Intensity> > >ledintensity;
  
  int j=0;  
  for (std::vector<Event*>::iterator e = m_Events.begin(); e != m_Events.end(); ++e) {
//     if (j>FirstEventsToDisregard && j< TotalEvents && (*e)->GetPhdiode1()> Threshold ){
       alltimevents.push_back((*e)->GetPhdiode2());
//        std::cout<<(*e)->GetPhdiode1()<<std::endl;
//       }
    ++j;
  }


//   for (unsigned int i = 0; i<timestartregions.size();++i){
//     std::cout<<  timestartregions[i]  <<std::endl;
//     std::cout<<  timeendregions[i+1]  <<std::endl;
//   }
//  std::cout<<  timestartregions.size()  <<std::endl;
//   std::cout<<  timeendregions  <<std::endl;
  //Find the patterns


    std::vector<int> ledisonregion;
    Utilities util;
    TFile c(("Source"+ util.IntToString(m_sou) +"Phd2_Check_" + util.IntToString(m_dis) +  "_mDep" + util.IntToString(m_dep) + "m.root").c_str(),"recreate");
    
    CheckLAMSSystem checksystem(m_dep,m_sou,m_dis);

    std::vector<int> timestartregions;
    std::vector<int> timeendregions;


  switch (m_sou){
  case 1:  
    {
      for (unsigned int i = 0; i< alltimevents.size();++i){
	if( alltimevents[i]> ledoncriticalvalueph2sou1) {ledisonregion.push_back(i);}
      }
  
      for (unsigned int i = 0; i< ledisonregion.size();++i){
	if( ledisonregion[i+1]- ledisonregion[i]>1 ){
	  timestartregions.push_back( ledisonregion[i+1] );
	  timeendregions.push_back( ledisonregion[i] );
	}
      }
      for (unsigned int i = 0; i<timeendregions.size();++i){

	//     std::cout<<  timestartregions[i]  -  timeendregions[i]  <<std::endl;
    
	if ( timestartregions[i]-timeendregions[i]> clockcriticalvalueph2sou1 && 
	     timeendregions[i+5]>timestartregions[i+4] && 
	     timeendregions[i+4]>timestartregions[i+3] && 
	     timeendregions[i+3]>timestartregions[i+2] && 
	     timeendregions[i+2]>timestartregions[i+1] && 
	     timeendregions[i+1]>timestartregions[i]){
	
	
	  led383nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm), 
				   ledflashfinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm) ) ); 
      
	  led400nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm), 
				   ledflashfinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm) ) ); 
	
	  led470nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm), 
				   ledflashfinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm) ) ); 
	
	  led525nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm), 
				   ledflashendtimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm), 
				   ledflashfinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm) ) ); 
	
	  darkcurrent.push_back( Led( ledflashendtimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm), 
				      ledflashstarttimefinder(alltimevents, timestartregions[i+4], timeendregions[i+5], maxpc383nm), 
				      darkcurrentfinder(alltimevents, timeendregions[i+4], timestartregions[i+4]) ) ); 
      
	  ledcycle.push_back( Cycle( ledflashstarttimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+4], timeendregions[i+5], maxpc383nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc383nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc400nm), 
				     ledflashstarttimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc525nm)
				     - ledflashendtimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc470nm) ) );
	
	}
      
      
      }  
      //Checking the LAMS
    
      TH1F* chkcycle = checksystem.checkcycle(ledcycle);
      TH1F* chkled383 = checksystem.checkled383(led383nm);
      TH1F* chkled400 = checksystem.checkled400(led400nm);
      TH1F* chkled470 = checksystem.checkled470(led470nm);
      TH1F* chkled525 = checksystem.checkled525(led525nm);
      TH1F* chkL383to400 = checksystem.checkL383to400(ledcycle);
      TH1F* chkL400to470 = checksystem.checkL400to470(ledcycle);
      TH1F* chkL470to525 = checksystem.checkL470to525(ledcycle);
      TH1F* chkledcycle383 = checksystem.checkled383cycle(led383nm);
      TH1F* chkledcycle400 = checksystem.checkled400cycle(led400nm);
      TH1F* chkledcycle470 = checksystem.checkled470cycle(led470nm);
      TH1F* chkledcycle525 = checksystem.checkled525cycle(led525nm);
      TH1F* chkLastLedtoNewCycleStart=checksystem.checkLastLedtoNewCycleStart(ledcycle,led525nm);
      TH1F* ldflplat383=checksystem.ledflashplato383(led383nm);
      TH1F* ldflplat400=checksystem.ledflashplato400(led400nm);
      TH1F* ldflplat470=checksystem.ledflashplato470(led470nm);
      TH1F* ldflplat525=checksystem.ledflashplato525(led525nm);
      TH1F* darkintensity= checksystem.lednoflash(darkcurrent);
      ledintensity[m_dep][m_sou].push_back( Intensity(383, ldflplat383->GetMean()-darkintensity->GetMean(),ldflplat383->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(400, ldflplat400->GetMean()-darkintensity->GetMean(),ldflplat400->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(470, ldflplat470->GetMean()-darkintensity->GetMean(),ldflplat470->GetRMS(), m_dis) );
      ledintensity[m_dep][m_sou].push_back( Intensity(525, ldflplat525->GetMean()-darkintensity->GetMean(),ldflplat525->GetRMS(), m_dis) );
    
      chkcycle->Write();
      chkled383->Write();
      chkled400->Write();
      chkled470->Write();
      chkled525->Write();
      chkL383to400->Write();
      chkL400to470->Write();
      chkL470to525->Write();
      chkledcycle383->Write();
      chkledcycle400->Write();
      chkledcycle470->Write();
      chkledcycle525->Write();
      chkLastLedtoNewCycleStart->Write();
      ldflplat383->Write();
      ldflplat400->Write();
      ldflplat470->Write();
      ldflplat525->Write();
      darkintensity->Write();
    
      delete chkcycle;
      delete chkled383;
      delete chkled400;
      delete chkled470;
      delete chkled525;
      delete chkL383to400;
      delete chkL400to470;
      delete chkL470to525;
      delete chkledcycle383;
      delete chkledcycle400;
      delete chkledcycle470;
      delete chkledcycle525;
      delete chkLastLedtoNewCycleStart;
      delete ldflplat383;
      delete ldflplat400;
      delete ldflplat470;
      delete ldflplat525;
      delete darkintensity;
      
    }
    break;
    
  case 2:   
    {
    std::vector<int> ledisonregion;
    for (unsigned int i = 0; i< alltimevents.size();++i){
      if( alltimevents[i]> ledoncriticalvalueph2sou2) {ledisonregion.push_back(i);}
    }
    
    std::vector<int> timestartregions;
    std::vector<int> timeendregions;
    for (unsigned int i = 0; i< ledisonregion.size();++i){
      if( ledisonregion[i+1]- ledisonregion[i]>1 ){
	timestartregions.push_back( ledisonregion[i+1] );
	timeendregions.push_back( ledisonregion[i] );
      }
    } 
    for (unsigned int i = 0; i<timeendregions.size();++i){
      
      //     std::cout<<  timestartregions[i]  -  timeendregions[i]  <<std::endl;
      
      if ( timestartregions[i]-timeendregions[i]> clockcriticalvalueph2sou2 && 
	   timeendregions[i+5]>timestartregions[i+4] && 
	   timeendregions[i+4]>timestartregions[i+3] && 
	   timeendregions[i+3]>timestartregions[i+2] && 
	   timeendregions[i+2]>timestartregions[i+1] && 
	   timeendregions[i+1]>timestartregions[i]){
	
	
	led375nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm), 
				 ledflashendtimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm), 
				 ledflashfinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm) ) ); 
	
	led425nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm), 
				 ledflashendtimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm), 
				 ledflashfinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm) ) ); 
	
	led450nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm), 
				 ledflashendtimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm), 
				 ledflashfinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm) ) ); 
	
	led495nm.push_back( Led( ledflashstarttimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm), 
				 ledflashendtimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm), 
				 ledflashfinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm) ) ); 
	
	darkcurrent.push_back( Led( ledflashendtimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm), 
				    ledflashstarttimefinder(alltimevents, timestartregions[i+4], timeendregions[i+5], maxpc375nm), 
				    darkcurrentfinder(alltimevents, timeendregions[i+4], timestartregions[i+4]) ) ); 

	ledcycle.push_back( Cycle( ledflashstarttimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm), 
				   ledflashstarttimefinder(alltimevents, timestartregions[i+4], timeendregions[i+5], maxpc375nm), 
				   ledflashstarttimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm)
				   - ledflashendtimefinder(alltimevents, timestartregions[i], timeendregions[i+1], maxpc375nm), 
				   ledflashstarttimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm)
				   - ledflashendtimefinder(alltimevents, timestartregions[i+1], timeendregions[i+2], maxpc425nm), 
				   ledflashstarttimefinder(alltimevents, timestartregions[i+3], timeendregions[i+4], maxpc495nm)
				   - ledflashendtimefinder(alltimevents, timestartregions[i+2], timeendregions[i+3], maxpc450nm) ) );
	
      }
      
      
    }  

    //Checking the LAMS
    
    TH1F* chkcycle = checksystem.checkcycle(ledcycle);
    TH1F* chkled375 = checksystem.checkled375(led375nm);
    TH1F* chkled425 = checksystem.checkled425(led425nm);
    TH1F* chkled450 = checksystem.checkled450(led450nm);
    TH1F* chkled495 = checksystem.checkled495(led495nm);
    TH1F* chkL375to425 = checksystem.checkL375to425(ledcycle);
    TH1F* chkL425to450 = checksystem.checkL425to450(ledcycle);
    TH1F* chkL450to495 = checksystem.checkL450to495(ledcycle);
    TH1F* chkledcycle375 = checksystem.checkled375cycle(led375nm);
    TH1F* chkledcycle425 = checksystem.checkled425cycle(led425nm);
    TH1F* chkledcycle450 = checksystem.checkled450cycle(led450nm);
    TH1F* chkledcycle495 = checksystem.checkled495cycle(led495nm);
    TH1F* chkLastLedtoNewCycleStart=checksystem.checkLastLedtoNewCycleStart(ledcycle,led495nm);
    TH1F* ldflplat375=checksystem.ledflashplato375(led375nm);
    TH1F* ldflplat425=checksystem.ledflashplato425(led425nm);
    TH1F* ldflplat450=checksystem.ledflashplato450(led450nm);
    TH1F* ldflplat495=checksystem.ledflashplato495(led495nm);
    TH1F* darkintensity= checksystem.lednoflash(darkcurrent);
    ledintensity[m_dep][m_sou].push_back( Intensity(375, ldflplat375->GetMean()-darkintensity->GetMean(),ldflplat375->GetRMS(), m_dis) );
    ledintensity[m_dep][m_sou].push_back( Intensity(425, ldflplat425->GetMean()-darkintensity->GetMean(),ldflplat425->GetRMS(), m_dis) );
    ledintensity[m_dep][m_sou].push_back( Intensity(450, ldflplat450->GetMean()-darkintensity->GetMean(),ldflplat450->GetRMS(), m_dis) );
    ledintensity[m_dep][m_sou].push_back( Intensity(495, ldflplat495->GetMean()-darkintensity->GetMean(),ldflplat495->GetRMS(), m_dis) );
    
    chkcycle->Write();
    chkled375->Write();
    chkled425->Write();
    chkled450->Write();
    chkled495->Write();
    chkL375to425->Write();
    chkL425to450->Write();
    chkL450to495->Write();
    chkledcycle375->Write();
    chkledcycle425->Write();
    chkledcycle450->Write();
    chkledcycle495->Write();
    chkLastLedtoNewCycleStart->Write();
    ldflplat375->Write();
    ldflplat425->Write();
    ldflplat450->Write();
    ldflplat495->Write();
    darkintensity->Write();

    delete chkcycle;
    delete chkled375;
    delete chkled425;
    delete chkled450;
    delete chkled495;
    delete chkL375to425;
    delete chkL425to450;
    delete chkL450to495;
    delete chkledcycle375;
    delete chkledcycle425;
    delete chkledcycle450;
    delete chkledcycle495;
    delete chkLastLedtoNewCycleStart;
    delete ldflplat375;
    delete ldflplat425;
    delete ldflplat450;
    delete ldflplat495;
    delete darkintensity;
    
    
    }
    break;
    
  }
  
  c.Close();

    return ledintensity;
  
  
}




void AnalyzePhd::phdiffs(int& Threshold, int& FirstEventsToDisregard, int& TotalEvents)
{
  std::vector<int> alltimevents;

  int j=0;  
  for (std::vector<Event*>::iterator e = m_Events.begin(); e != m_Events.end(); ++e) {
    alltimevents.push_back((*e)->GetPhdiode2()-(*e)->GetPhdiode1());
    ++j;
  }

  Utilities util;
  TFile c(("Source"+ util.IntToString(m_sou) +"Phd2-1_Check_" + util.IntToString(m_dis) +  "_mDep" + util.IntToString(m_dep) + "m.root").c_str(),"recreate");

  CheckLAMSSystem checksystem(m_dep,m_sou,m_dis);

  TH1F* chkphdiffs = checksystem.chkphdiffs(alltimevents);
      
  chkphdiffs->Write();
  delete chkphdiffs;
  c.Close();

}



