#ifndef BuildLAMPSEvent_h
#define BuildLAMPSEvent_h 1

#include <vector>
#include <Event.hh>
#include <DataReader.hh>


class BuildLAMPSEvent {

private:

  int m_sou;

  int m_dis;

  int m_firsteventstodisregard;

  int m_totalevents;

  int m_threshold;

  DataReader*  m_dataReader;

public:
  
  BuildLAMPSEvent(int& Sou, int& Dis, int& FirstEventsToDisregard, int& TotalEvents,int& Threshold);
  ~BuildLAMPSEvent();

  std::vector<Event*> calculateEvents(void);

};

#endif
