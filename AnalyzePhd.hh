#ifndef AnalyzePhd_h
#define AnalyzePhd_h 1

#include <vector>
#include <map>
#include <Event.hh>
#include <Utilities.hh>
#include <Intensity.hh>


class AnalyzePhd {

private:

  int m_dep;
  int m_sou;
  int m_dis;
  std::vector<Event*> m_Events;

  //Private functions
  std::vector<int> darkcurrentfinder(std::vector<int>& allevents, int& tmstart, int& tmend);
  std::vector<int> ledflashfinder(std::vector<int>& allevents, int& tmstart, int& tmend, double& maxpercent);
  double ledflashstarttimefinder(std::vector<int>& allevents, int& tmstart, int& tmend, double& maxpercent);
  double ledflashendtimefinder(std::vector<int>& allevents, int& tmstart, int& tmend, double& maxpercent);
  
  
public:
  
  AnalyzePhd(int& Dep, int& Sou, int& Dis, std::vector<Event*>& Events);
  ~AnalyzePhd();

  std::map<int,std::map<int, std::vector<Intensity> > >analysisph1(int& Threshold, int& FirstEventsToDisregard, int& TotalEvents);
  std::map<int,std::map<int, std::vector<Intensity> > >analysisph2(int& Threshold, int& FirstEventsToDisregard, int& TotalEvents);
  void phdiffs(int& Threshold, int& FirstEventsToDisregard, int& TotalEvents);

};

#endif
