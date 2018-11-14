#include <iostream>
#include <iomanip>
#include <vector>
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "Utilities.hh"
#include "MonitorPhd.hh"
#include "TPostScript.h"
#include "TH2F.h"
#include "TFile.h"

MonitorPhd::MonitorPhd(int& Dep, int& Sou, int& Dis)
  : m_dep(Dep),
    m_sou(Sou),
    m_dis(Dis)
{}

MonitorPhd::~MonitorPhd()
{}


void MonitorPhd::monitorwindow(std::vector<Event*>& Events, int& FirstEventsToDisregard, int& TotalEvents)
{
  
//   std::vector<double> photodi1;
//   std::vector<double> photodi2;
//   int j=0;  
//   for (std::vector<Event*>::iterator e = Events.begin(); e != Events.end(); ++e) {
//     if (j>FirstEventsToDisregard && j<TotalEvents){
//       photodi1.push_back( (*e)->GetPhdiode1() );
//       photodi2.push_back( (*e)->GetPhdiode2() );
//     }
//     ++j;
//   }
//   Double_t x[TotalEvents-FirstEventsToDisregard]; for (int i=0; i<TotalEvents-FirstEventsToDisregard;++i){x[i]=i;}
  
//   TGraph monph1= TGraph(photodi1.size(),x,&photodi1[0]);   
//   monph1.Draw("AC*");
//   TPostScript  ps("test.eps",-113);
  
     
  Utilities util;
  //Book Histos
//   TCanvas *c1 = new TCanvas("c1",("LAMS Data Distance " + util.IntToString(m_dis) + " m ").c_str(),200,10,700,500);
    
  std::string title = "LAMS Data Depth " + util.IntToString(m_dep) + " m Distance " + util.IntToString(m_dis) + " m Source " + util.IntToString(m_sou) ; 
  double xinitbin   = 0.01* FirstEventsToDisregard;
  double xfinbin    = xinitbin + 0.01*TotalEvents;
  int xtotalbins    = (int) (xfinbin-xinitbin);

  if (xtotalbins>4000){xtotalbins=4000;}  
  TH2F *gr1= new TH2F(("PhotoDiode 1 Depth " + util.IntToString(m_dep) + " m Distance " + util.IntToString(m_dis) + " m Source " + util.IntToString(m_sou) ).c_str(), title.c_str() , xtotalbins ,xinitbin,xfinbin,500,0,60000);
  gr1 ->SetXTitle(" Time (sec) ");
  gr1 ->SetYTitle(" Counts ");
  gr1->SetMarkerColor(2);
  TH2F *gr2= new TH2F(("PhotoDiode 2 Depth " + util.IntToString(m_dep) + " m Distance" + util.IntToString(m_dis) + " m Source " + util.IntToString(m_sou) ).c_str(), title.c_str() ,xtotalbins,xinitbin ,xfinbin ,500,0,60000);
  gr2 ->SetXTitle(" Time (sec) ");
  gr2 ->SetYTitle(" Counts ");
  gr2->SetMarkerColor(8);
  int j=FirstEventsToDisregard;  
  for (std::vector<Event*>::iterator e = Events.begin(); e != Events.end(); ++e) {
//     if (j>FirstEventsToDisregard && j<TotalEvents){
      gr1 ->Fill(0.01* j , (*e)->GetPhdiode1() );
      gr2 ->Fill(0.01* j , (*e)->GetPhdiode2() );
//     }
    ++j;
  }
  gr1->SetTitle(title.c_str()) ; 
  gr2->SetTitle(title.c_str()) ; 

//   gr1->Draw();gr2->Draw("SAME");
  TFile f(("LAMS"+ util.IntToString(m_sou) +"_dis" + util.IntToString(m_dis) +  "_" + util.IntToString(m_dep) + ".root").c_str(),"recreate");
//   TFile f(("LAMS"+ util.IntToString(m_sou) +"_dis" + util.IntToString(m_dis) +  ".root").c_str(),"recreate");
  gr1->Write();gr2->Write();
//   c1->Write();
  f.Close();
  delete gr1;
  delete gr2;
//   delete c1;

}

