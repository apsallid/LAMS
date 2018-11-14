#ifndef CheckLAMSSystem_h
#define CheckLAMSSystem_h 1

#include <vector>
#include <Cycle.hh>
#include <Led.hh>
#include "TH1F.h"

class CheckLAMSSystem{

private:

  int m_dep;
  int m_sou;
  int m_dis;

  Utilities m_util;
  
  
public:
  
  CheckLAMSSystem(int& Dep,int& Sou,int& Dis);
  ~CheckLAMSSystem();


  void checkeventcounter(std::vector<Event*>& Events);
  TH1F* checkcycle(std::vector<Cycle> ledcycle);
  TH1F* checkled383(std::vector<Led> led);
  TH1F* checkled400(std::vector<Led> led);
  TH1F* checkled470(std::vector<Led> led);
  TH1F* checkled525(std::vector<Led> led);
  TH1F* checkled375(std::vector<Led> led);
  TH1F* checkled425(std::vector<Led> led);
  TH1F* checkled450(std::vector<Led> led);
  TH1F* checkled495(std::vector<Led> led);
  TH1F* checkL383to400(std::vector<Cycle> ledcycle);
  TH1F* checkL400to470(std::vector<Cycle> ledcycle);
  TH1F* checkL470to525(std::vector<Cycle> ledcycle);
  TH1F* checkL375to425(std::vector<Cycle> ledcycle);
  TH1F* checkL425to450(std::vector<Cycle> ledcycle);
  TH1F* checkL450to495(std::vector<Cycle> ledcycle);
  TH1F* checkled383cycle(std::vector<Led> led);
  TH1F* checkled400cycle(std::vector<Led> led);
  TH1F* checkled470cycle(std::vector<Led> led);
  TH1F* checkled525cycle(std::vector<Led> led);
  TH1F* checkled375cycle(std::vector<Led> led);
  TH1F* checkled425cycle(std::vector<Led> led);
  TH1F* checkled450cycle(std::vector<Led> led);
  TH1F* checkled495cycle(std::vector<Led> led);
  TH1F* checkLastLedtoNewCycleStart(std::vector<Cycle> ledcycle,std::vector<Led> led);
  TH1F* ledflashplato383(std::vector<Led> led);
  TH1F* ledflashplato400(std::vector<Led> led);
  TH1F* ledflashplato470(std::vector<Led> led);
  TH1F* ledflashplato525(std::vector<Led> led);
  TH1F* ledflashplato375(std::vector<Led> led);
  TH1F* ledflashplato425(std::vector<Led> led);
  TH1F* ledflashplato450(std::vector<Led> led);
  TH1F* ledflashplato495(std::vector<Led> led);
  TH1F* lednoflash(std::vector<Led> dark);
  TH1F* chkphdiffs(std::vector<int> diffsph);



};

#endif
