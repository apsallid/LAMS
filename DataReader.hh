#ifndef DataReader_h
#define DataReader_h 1

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <Event.hh>
#include <Utilities.hh>

class DataReader {

private:

  int m_sou;

  int m_dis;

  int m_firsteventstodisregard;

  int m_totalevents;
  
  int m_total_events_in_file;
  
  double m_threshold;

  int m_current_event;

  int m_current_event_to_process;

  Utilities m_util;

  std::ifstream m_data_file;

  // Private methods
  //   Event* ReadData (void);
  void ReadData (int& CheckCounter,int& Photodiode1,int& Photodiode2);
public:
  
  DataReader(int Sou, int Dis, int FirstEventsToDisregard,int TotalEvents,  double Threshold);
  ~DataReader();

  Event* next_event(void);

};

#endif

