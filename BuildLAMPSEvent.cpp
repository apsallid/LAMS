#include <iostream>
#include <iomanip>
#include "TGraph.h"
#include "Utilities.hh"
#include "BuildLAMPSEvent.hh"
#include "TPostScript.h"
#include "TH1F.h"

BuildLAMPSEvent::BuildLAMPSEvent(int& Sou, int& Dis, int& FirstEventsToDisregard, int& TotalEvents, int& Threshold)
  :   m_sou(Sou),
      m_dis(Dis),
      m_firsteventstodisregard(FirstEventsToDisregard),
      m_threshold(Threshold),
      m_dataReader ( new DataReader(Sou, Dis,FirstEventsToDisregard,TotalEvents,Threshold) )
{}

BuildLAMPSEvent::~BuildLAMPSEvent()
{
  delete m_dataReader;
}

std::vector<Event*>
BuildLAMPSEvent::calculateEvents (void)
{
  std::vector<Event*> AllEvents;
  // Start the loop on events
  Event* evt = m_dataReader->next_event();

  while (evt) {

    
   
    // evt->print();
    AllEvents.push_back(evt);
    evt = m_dataReader->next_event();
    
  }  // End of loop over events

  return AllEvents;
  
}



