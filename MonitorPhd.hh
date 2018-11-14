#ifndef MonitorPhd_h
#define MonitorPhd_h 1

#include <vector>
#include <Event.hh>


class MonitorPhd {

private:

  int m_dep;
  int m_sou;
  int m_dis;
//   std::vector<Event*> Events;

public:
  
  MonitorPhd(int& Dep, int& Sou, int& Dis);
  ~MonitorPhd();

  void monitorwindow(std::vector<Event*>& Events, int& FirstEventsToDisregard, int& TotalEvents);

};

#endif
