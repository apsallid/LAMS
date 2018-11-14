#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <DataReader.hh>
#include <Event.hh>
#include "CheckLAMSSystem.hh"
#include "TFile.h"


CheckLAMSSystem::CheckLAMSSystem(int& Dep,int& Sou,int& Dis)
  : m_dep(Dep),
    m_sou(Sou),
    m_dis(Dis)

{
  m_util = Utilities();
}

CheckLAMSSystem::~CheckLAMSSystem()
{}


TH1F* CheckLAMSSystem::checkled383(std::vector<Led> led)
{  

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 15.;

  TH1F *led383timediff= new TH1F("Led 383 Time Diffs ", ("Led 383 Time Differences "+ m_util.IntToString(m_dis)+" m Depth "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led383timediff->SetXTitle("Led 383 Time Differences (s)");
  led383timediff->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    led383timediff->Fill( (*ld).GetTimeEnd()- (*ld).GetTimeStart());
  }

  return led383timediff;
}

TH1F* CheckLAMSSystem::checkled400(std::vector<Led> led)
{  

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 15.;

  TH1F *led400timediff= new TH1F("Led 400 Time Diffs ", ("Led 400 Time Differences "+ m_util.IntToString(m_dis)+" m Depth "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led400timediff->SetXTitle("Led 400 Time Differences (s)");
  led400timediff->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    led400timediff->Fill( (*ld).GetTimeEnd()- (*ld).GetTimeStart());
  }

  return led400timediff;
}

TH1F* CheckLAMSSystem::checkled470(std::vector<Led> led)
{  

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 15.;

  TH1F *led470timediff= new TH1F("Led 470 Time Diffs ", ("Led 470 Time Differences "+ m_util.IntToString(m_dis)+" m Depth "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led470timediff->SetXTitle("Led 470 Time Differences (s)");
  led470timediff->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    led470timediff->Fill( (*ld).GetTimeEnd()- (*ld).GetTimeStart());
  }

  return led470timediff;
}

TH1F* CheckLAMSSystem::checkled525(std::vector<Led> led)
{  

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 15.;

  TH1F *led525timediff= new TH1F("Led 525 Time Diffs ", ("Led 525 Time Differences "+ m_util.IntToString(m_dis)+" m Depth "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led525timediff->SetXTitle("Led 525 Time Differences (s)");
  led525timediff->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
//     std::cout<< (*ld).GetTimeEnd() <<std::endl;
    led525timediff->Fill( (*ld).GetTimeEnd()- (*ld).GetTimeStart());
  }

  return led525timediff;
}

TH1F* CheckLAMSSystem::checkled375(std::vector<Led> led)
{  

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 15.;

  TH1F *led375timediff= new TH1F("Led 375 Time Diffs ", ("Led 375 Time Differences "+ m_util.IntToString(m_dis)+" m Depth "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led375timediff->SetXTitle("Led 375 Time Differences (s)");
  led375timediff->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    led375timediff->Fill( (*ld).GetTimeEnd()- (*ld).GetTimeStart());
  }

  return led375timediff;
}

TH1F* CheckLAMSSystem::checkled425(std::vector<Led> led)
{  

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 15.;

  TH1F *led425timediff= new TH1F("Led 425 Time Diffs ", ("Led 425 Time Differences "+ m_util.IntToString(m_dis)+" m Depth "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led425timediff->SetXTitle("Led 425 Time Differences (s)");
  led425timediff->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    led425timediff->Fill( (*ld).GetTimeEnd()- (*ld).GetTimeStart());
  }

  return led425timediff;
}

TH1F* CheckLAMSSystem::checkled450(std::vector<Led> led)
{  

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 15.;

  TH1F *led450timediff= new TH1F("Led 450 Time Diffs ", ("Led 450 Time Differences "+ m_util.IntToString(m_dis)+" m Depth "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led450timediff->SetXTitle("Led 450 Time Differences (s)");
  led450timediff->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    led450timediff->Fill( (*ld).GetTimeEnd()- (*ld).GetTimeStart());
  }

  return led450timediff;
}

TH1F* CheckLAMSSystem::checkled495(std::vector<Led> led)
{  

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 15.;

  TH1F *led495timediff= new TH1F("Led 495 Time Diffs ", ("Led 495 Time Differences "+ m_util.IntToString(m_dis)+" m Depth "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led495timediff->SetXTitle("Led 495 Time Differences (s)");
  led495timediff->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
//     std::cout<< (*ld).GetTimeEnd() <<std::endl;
    led495timediff->Fill( (*ld).GetTimeEnd()- (*ld).GetTimeStart());
  }

  return led495timediff;
}


TH1F* CheckLAMSSystem::checkcycle(std::vector<Cycle> ledcycle)
{  

  //Book Histos
  int NBins    = 100;
  double xMin  = 50.;
  double xMax  = 70.;
  
  TH1F *cyclestimediffs= new TH1F("Cycle Time Diffs", ("Cycle Time Diffs Depth "+ m_util.IntToString(m_dep) + "m Distance "+ m_util.IntToString(m_dis)+" m Source "+ m_util.IntToString(m_sou) ).c_str(), NBins, xMin, xMax);
  cyclestimediffs->SetXTitle("Cycle Time Differences (s)");
  cyclestimediffs->SetYTitle(" Cycles "); 
  
  for ( std::vector<Cycle>::iterator ldc= ledcycle.begin();ldc!=ledcycle.end();++ldc){
    cyclestimediffs->Fill( (*ldc).GetTimeEnd()- (*ldc).GetTimeStart());
  }
  
  return cyclestimediffs;
}

TH1F* CheckLAMSSystem::checkL383to400(std::vector<Cycle> ledcycle)
{

  //Book Histos
  int NBins    = 10;
  double xMin  = 0.;
  double xMax  = 10.;

  TH1F *L383toL400time= new TH1F("Time L383nm to L400nm", (" Time Between 383nm and 400nm LEDs "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  L383toL400time->SetXTitle(" Time Between 383nm and 400nm (s)");
  L383toL400time->SetYTitle(" Cycles "); 

  for ( std::vector<Cycle>::iterator ldc= ledcycle.begin();ldc!=ledcycle.end();++ldc){
    L383toL400time->Fill( (*ldc).GetTimeL1toL2() );
 }

  return L383toL400time;

}


TH1F* CheckLAMSSystem::checkL400to470(std::vector<Cycle> ledcycle)
{

  //Book Histos
  int NBins    = 10;
  double xMin  = 0.;
  double xMax  = 10.;

  TH1F *L400toL470time= new TH1F("Time L400nm to L470nm", (" Time Between 400nm and 470nm LEDs "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  L400toL470time->SetXTitle(" Time  Between 400nm and 470nm (s)");
  L400toL470time->SetYTitle(" Cycles "); 

  for ( std::vector<Cycle>::iterator ldc= ledcycle.begin();ldc!=ledcycle.end();++ldc){
    L400toL470time->Fill( (*ldc).GetTimeL2toL3() );
 }

  return L400toL470time;

}

TH1F* CheckLAMSSystem::checkL470to525(std::vector<Cycle> ledcycle)
{

  //Book Histos
  int NBins    = 10;
  double xMin  = 0.;
  double xMax  = 10.;

  TH1F *L470toL525time= new TH1F("Time L470nm to L525nm", (" Time Between 470nm and 525nm LEDs "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  L470toL525time->SetXTitle(" Time  Between 470nm and 525nm (s)");
  L470toL525time->SetYTitle(" Cycles "); 

  for ( std::vector<Cycle>::iterator ldc= ledcycle.begin();ldc!=ledcycle.end();++ldc){
    L470toL525time->Fill( (*ldc).GetTimeL3toL4() );
 }

  return L470toL525time;

}

TH1F* CheckLAMSSystem::checkL375to425(std::vector<Cycle> ledcycle)
{

  //Book Histos
  int NBins    = 10;
  double xMin  = 0.;
  double xMax  = 10.;

  TH1F *L375toL425time= new TH1F("Time L375nm to L425nm", (" Time Between 375nm and 425nm LEDs "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  L375toL425time->SetXTitle(" Time Between 375nm and 425nm (s)");
  L375toL425time->SetYTitle(" Cycles "); 

  for ( std::vector<Cycle>::iterator ldc= ledcycle.begin();ldc!=ledcycle.end();++ldc){
    L375toL425time->Fill( (*ldc).GetTimeL1toL2() );
 }

  return L375toL425time;

}


TH1F* CheckLAMSSystem::checkL425to450(std::vector<Cycle> ledcycle)
{

  //Book Histos
  int NBins    = 10;
  double xMin  = 0.;
  double xMax  = 10.;

  TH1F *L425toL450time= new TH1F("Time L425nm to L450nm", (" Time Between 425nm and 450nm LEDs "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  L425toL450time->SetXTitle(" Time  Between 425nm and 450nm (s)");
  L425toL450time->SetYTitle(" Cycles "); 

  for ( std::vector<Cycle>::iterator ldc= ledcycle.begin();ldc!=ledcycle.end();++ldc){
    L425toL450time->Fill( (*ldc).GetTimeL2toL3() );
 }

  return L425toL450time;

}

TH1F* CheckLAMSSystem::checkL450to495(std::vector<Cycle> ledcycle)
{

  //Book Histos
  int NBins    = 10;
  double xMin  = 0.;
  double xMax  = 10.;

  TH1F *L450toL495time= new TH1F("Time L450nm to L495nm", (" Time Between 450nm and 495nm LEDs "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  L450toL495time->SetXTitle(" Time  Between 450nm and 495nm (s)");
  L450toL495time->SetYTitle(" Cycles "); 

  for ( std::vector<Cycle>::iterator ldc= ledcycle.begin();ldc!=ledcycle.end();++ldc){
    L450toL495time->Fill( (*ldc).GetTimeL3toL4() );
 }

  return L450toL495time;

}


TH1F* CheckLAMSSystem::checkled383cycle(std::vector<Led> led)
{  

  std::vector<double> ldd;
  //Book Histos
  int NBins    = 100;
  double xMin  = 50.;
  double xMax  = 70.;

  TH1F *led383timecycle= new TH1F("Led 383 Cycle ", ("Led 383 Cycle "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led383timecycle->SetXTitle("Led 383 Time Cycle (s)");
  led383timecycle->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldd.push_back( (*ld).GetTimeStart() );
  }

  for (unsigned int i=1; i<ldd.size();++i){
    led383timecycle->Fill( ldd[i]-ldd[i-1]);
  }


  return led383timecycle;
}

TH1F* CheckLAMSSystem::checkled400cycle(std::vector<Led> led)
{  

  std::vector<double> ldd;
  //Book Histos
  int NBins    = 100;
  double xMin  = 50.;
  double xMax  = 70.;

  TH1F *led400timecycle= new TH1F("Led 400 Cycle ", ("Led 400 Cycle "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led400timecycle->SetXTitle("Led 400 Time Cycle (s)");
  led400timecycle->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldd.push_back( (*ld).GetTimeStart() );
  }

  for (unsigned int i=1; i<ldd.size();++i){
    led400timecycle->Fill( ldd[i]-ldd[i-1]);
  }


  return led400timecycle;
}

TH1F* CheckLAMSSystem::checkled470cycle(std::vector<Led> led)
{  

  std::vector<double> ldd;
  //Book Histos
  int NBins    = 100;
  double xMin  = 50.;
  double xMax  = 70.;

  TH1F *led470timecycle= new TH1F("Led 470 Cycle ", ("Led 470 Cycle "+ m_util.IntToString(m_dis)+" m in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led470timecycle->SetXTitle("Led 470 Time Cycle (s)");
  led470timecycle->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldd.push_back( (*ld).GetTimeStart() );
  }

  for (unsigned int i=1; i<ldd.size();++i){
    led470timecycle->Fill( ldd[i]-ldd[i-1]);
  }


  return led470timecycle;
}

TH1F* CheckLAMSSystem::checkled525cycle(std::vector<Led> led)
{  

  std::vector<double> ldd;
  //Book Histos
  int NBins    = 100;
  double xMin  = 50.;
  double xMax  = 70.;

  TH1F *led525timecycle= new TH1F("Led 525 Cycle ", ("Led 525 Cycle "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led525timecycle->SetXTitle("Led 525 Time Cycle (s)");
  led525timecycle->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldd.push_back( (*ld).GetTimeStart() );
  }

  for (unsigned int i=1; i<ldd.size();++i){
    led525timecycle->Fill( ldd[i]-ldd[i-1]);
  }


  return led525timecycle;
}

TH1F* CheckLAMSSystem::checkled375cycle(std::vector<Led> led)
{  

  std::vector<double> ldd;
  //Book Histos
  int NBins    = 100;
  double xMin  = 55.;
  double xMax  = 65.;

  TH1F *led375timecycle= new TH1F("Led 375 Cycle ", ("Led 375 Cycle "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led375timecycle->SetXTitle("Led 375 Time Cycle (s)");
  led375timecycle->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldd.push_back( (*ld).GetTimeStart() );
  }

  for (unsigned int i=1; i<ldd.size();++i){
    led375timecycle->Fill( ldd[i]-ldd[i-1]);
  }


  return led375timecycle;
}

TH1F* CheckLAMSSystem::checkled425cycle(std::vector<Led> led)
{  

  std::vector<double> ldd;
  //Book Histos
  int NBins    = 100;
  double xMin  = 55.;
  double xMax  = 65.;

  TH1F *led425timecycle= new TH1F("Led 425 Cycle ", ("Led 425 Cycle "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led425timecycle->SetXTitle("Led 425 Time Cycle (s)");
  led425timecycle->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldd.push_back( (*ld).GetTimeStart() );
  }

  for (unsigned int i=1; i<ldd.size();++i){
    led425timecycle->Fill( ldd[i]-ldd[i-1]);
  }


  return led425timecycle;
}

TH1F* CheckLAMSSystem::checkled450cycle(std::vector<Led> led)
{  

  std::vector<double> ldd;
  //Book Histos
  int NBins    = 100;
  double xMin  = 55.;
  double xMax  = 65.;

  TH1F *led450timecycle= new TH1F("Led 450 Cycle ", ("Led 450 Cycle "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led450timecycle->SetXTitle("Led 450 Time Cycle (s)");
  led450timecycle->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldd.push_back( (*ld).GetTimeStart() );
  }

  for (unsigned int i=1; i<ldd.size();++i){
    led450timecycle->Fill( ldd[i]-ldd[i-1]);
  }


  return led450timecycle;
}

TH1F* CheckLAMSSystem::checkled495cycle(std::vector<Led> led)
{  

  std::vector<double> ldd;
  //Book Histos
  int NBins    = 100;
  double xMin  = 55.;
  double xMax  = 65.;

  TH1F *led495timecycle= new TH1F("Led 495 Cycle ", ("Led 495 Cycle "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  led495timecycle->SetXTitle("Led 495 Time Cycle (s)");
  led495timecycle->SetYTitle(" Flashes "); 

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldd.push_back( (*ld).GetTimeStart() );
  }

  for (unsigned int i=1; i<ldd.size();++i){
    led495timecycle->Fill( ldd[i]-ldd[i-1]);
  }


  return led495timecycle;
}



TH1F* CheckLAMSSystem::checkLastLedtoNewCycleStart(std::vector<Cycle> ledcycle,std::vector<Led> led)
{
  std::vector<double> newcyclestart;
  std::vector<double> lastled;

  //Book Histos
  int NBins    = 10;
  double xMin  = 5.;
  double xMax  = 20.;

  TH1F *LastLedtoNewCycletime= new TH1F("525nm LED to New Cycle ", (" Time Between Last LED to New Cycle "+ m_util.IntToString(m_dis)+" meters Source "+ m_util.IntToString(m_sou) + " in " + m_util.IntToString(m_dep)+ " m").c_str(), NBins, xMin, xMax);
  LastLedtoNewCycletime->SetXTitle(" Time Between Last LED to New Cycle (s)");
  LastLedtoNewCycletime->SetYTitle(" Cycles "); 

  for ( std::vector<Cycle>::iterator ldc= ledcycle.begin();ldc!=ledcycle.end();++ldc){
//      std::cout<< (*ldc).GetTimeStart() <<std::endl;
     newcyclestart.push_back( (*ldc).GetTimeStart() );
 }

  for ( std::vector<Led>::iterator ldc= led.begin();ldc!=led.end();++ldc){
//     std::cout<< (*ldc).GetTimeEnd() <<std::endl;
    lastled.push_back( (*ldc).GetTimeEnd() );
 }
  //std::min(newcyclestart.size(),lastled.size())
  for (unsigned int i=0; i< lastled.size();++i){
//     std::cout<< newcyclestart[i+1] <<std::endl;
//     std::cout<< lastled[i] <<std::endl;
    LastLedtoNewCycletime->Fill(newcyclestart[i+1]-lastled[i]);
  }

  return LastLedtoNewCycletime;

}

TH1F* CheckLAMSSystem::ledflashplato383(std::vector<Led> led)
{
  int NBins=0; double xMin=0; double xMax=0;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );

  NBins    = 200;
  xMin  = (double) max - 10000.;
  xMax  = (double) max + 10000.;

  
  TH1F *ldplato= new TH1F("Led 383  ", ("Led 383 "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity 383 nm(counts)");
  ldplato->SetYTitle(" Entries "); 
  
  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}


TH1F* CheckLAMSSystem::ledflashplato400(std::vector<Led> led)
{
  int NBins=0; double xMin=0; double xMax=0;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );

  NBins    = 200;
  xMin  = (double) max - 10000.;
  xMax  = (double) max + 10000.;
  

  TH1F *ldplato= new TH1F("Led 400  ", ("Led 400 "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity  400 nm(counts)");
  ldplato->SetYTitle(" Entries "); 
  
  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}


TH1F* CheckLAMSSystem::ledflashplato470(std::vector<Led> led)
{
  int NBins=0; double xMin=0; double xMax=0;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );

  NBins    = 200;
  xMin  = (double) max - 10000.;
  xMax  = (double) max + 10000.;
  

  TH1F *ldplato= new TH1F("Led 470  ", ("Led 470 "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity 470 nm(counts)");
  ldplato->SetYTitle(" Entries "); 
  
  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}


TH1F* CheckLAMSSystem::ledflashplato525(std::vector<Led> led)
{
  int NBins=0; double xMin=0; double xMax=0;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );

  NBins    = 200;
  xMin  = (double) max - 10000.;
  xMax  = (double) max + 10000.;
  

  TH1F *ldplato= new TH1F("Led 525  ", ("Led 525 "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity 525 nm(counts)");
  ldplato->SetYTitle(" Entries "); 
  
  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}

TH1F* CheckLAMSSystem::ledflashplato375(std::vector<Led> led)
{
  int NBins=0; double xMin=0; double xMax=0;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );

  NBins    = 200;
  xMin  = (double) max - 10000.;
  xMax  = (double) max + 10000.;

  
  TH1F *ldplato= new TH1F("Led 375  ", ("Led 375 "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity 375 nm(counts)");
  ldplato->SetYTitle(" Entries "); 
  
  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}


TH1F* CheckLAMSSystem::ledflashplato425(std::vector<Led> led)
{
  int NBins=0; double xMin=0; double xMax=0;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );

  NBins    = 200;
  xMin  = (double) max - 10000.;
  xMax  = (double) max + 10000.;
  

  TH1F *ldplato= new TH1F("Led 425  ", ("Led 425 "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity 425 nm(counts)");
  ldplato->SetYTitle(" Entries "); 
  
  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}


TH1F* CheckLAMSSystem::ledflashplato450(std::vector<Led> led)
{
  int NBins=0; double xMin=0; double xMax=0;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );

  NBins    = 200;
  xMin  = (double) max - 10000.;
  xMax  = (double) max + 10000.;
  

  TH1F *ldplato= new TH1F("Led 450  ", ("Led 450 "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity 450 nm(counts)");
  ldplato->SetYTitle(" Entries "); 
  
  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}


TH1F* CheckLAMSSystem::ledflashplato495(std::vector<Led> led)
{
  int NBins=0; double xMin=0; double xMax=0;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );

  NBins    = 200;
  xMin  = (double) max - 10000.;
  xMax  = (double) max + 10000.;
  

  TH1F *ldplato= new TH1F("Led 495  ", ("Led 495 "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity 495 nm(counts)");
  ldplato->SetYTitle(" Entries "); 
  
  for ( std::vector<Led>::iterator ld= led.begin();ld!=led.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}


TH1F* CheckLAMSSystem::lednoflash(std::vector<Led> dark)
{
  int NBins=0; double xMin=0.; double xMax=0.;
  std::vector<int> ldevents;

  for ( std::vector<Led>::iterator ld= dark.begin();ld!=dark.end();++ld){
    ldevents = (*ld).GetLedflash(); break;
  }
  int max = *max_element( ldevents.begin(), ldevents.end() );
  int min = *min_element( ldevents.begin(), ldevents.end() );

  NBins = 200;
  xMin  =(double) min -50.;
  xMax  = (double) max + 50.;

  
  TH1F *ldplato= new TH1F("Dark Current Photodiode 1", ("Dark Current "+ m_util.IntToString(m_dis)+" m Source "+ m_util.IntToString(m_sou)+ " in "+ m_util.IntToString(m_dep)+" m" ).c_str(), NBins, xMin, xMax);
  ldplato->SetXTitle("Intensity (Counts)");
  ldplato->SetYTitle("Entries"); 
  
  for ( std::vector<Led>::iterator ld= dark.begin();ld!=dark.end();++ld){
    for ( std::vector<int>::iterator ldd= (*ld).GetLedflash().begin();ldd!=(*ld).GetLedflash().end();++ldd){
     ldplato->Fill( (*ldd) );
   }
  }

  return ldplato;
}


void CheckLAMSSystem::checkeventcounter(std::vector<Event*>& Events)
{
  
  int k=0; int j=0;int l=0;int m=0;
  
  for (std::vector<Event*>::iterator e = Events.begin(); e != Events.end(); ++e) {
    if( (*e)->GetChCounter()!=j ){
      
      if ( (*e)->GetChCounter()-j == 1){ 
	++j; l= (256-k) ;m=m+l;
	if (l!=0){std::cout<< "Events lost: " << l <<  " in " << j-1 << " 256ada in " << m_dis << "depth " <<std::endl;}
	k=0;l=0;
      }
      if ( (*e)->GetChCounter()-j > 1){ 
	 l= (256-k)+256*(j-(*e)->GetChCounter());  m=m+l; 
	 if (l!=0){std::cout<< "Events lost: " << l <<  " from " << j-(*e)->GetChCounter() << " to  " << j<<  " 256ada in " << m_dis << "depth "<< std::endl;}
	 j=(*e)->GetChCounter();k=0;l=0;}
       
    }
      
    ++k;
  
  }
  
      std::cout<< "Events lost: " << m << std::endl;

}

TH1F* CheckLAMSSystem::chkphdiffs(std::vector<int> diffsph)
{
  int NBins=0; double xMin=0; double xMax=0;

  int max = *max_element( diffsph.begin(), diffsph.end() );

  NBins    = 200;
  xMin  = (double) max - 500.;
  xMax  = (double) max + 500.;
  

  TH1F *diffbetph= new TH1F("Photodiodes Diffs  ", ("Photodiodes Diffs "+ m_util.IntToString(m_dis)+" m  in "+ m_util.IntToString(m_dep)+" m").c_str(), NBins, xMin, xMax);
  diffbetph->SetXTitle("Photodiode Difference(counts)");
  diffbetph->SetYTitle(" Entries "); 
  
  for ( std::vector<int>::iterator phd= diffsph.begin();phd!=diffsph.end();++phd){
    diffbetph ->Fill( (*phd) );
  }

  return diffbetph;
}



