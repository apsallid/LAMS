#include <iostream>
#include <iomanip>
#include <string> 
#include <sstream>
#include <stdlib.h>
#include "DataReader.hh"
#include "Utilities.hh"


DataReader::DataReader(int Sou, int Dis, int FirstEventsToDisregard, int TotalEvents, double Threshold)
  : m_sou(Sou),
    m_dis(Dis),
    m_firsteventstodisregard(FirstEventsToDisregard),
    m_totalevents(TotalEvents),
    m_threshold(Threshold),
    m_current_event(0),
    m_current_event_to_process(0)
{
  
  m_util = Utilities();

  // Find the total number of events in file
  std::string linux_command =  "wc -l LAMS"+ m_util.IntToString(m_sou) +"_dis" +m_util.IntToString(m_dis) + ".txt >> pp.txt";
  system(linux_command.c_str());
  std::ifstream pp_file("pp.txt");
  std::string buffer;
  getline(pp_file, buffer);
  std::istringstream is(buffer);
  is >> m_total_events_in_file;
  pp_file.close();
  system("rm -rf pp.txt");
  
}

DataReader::~DataReader()
{  
  m_data_file.close(); 
}

void
DataReader::ReadData (int& CheckCounter,int& Photodiode1,int& Photodiode2)
{
  if(m_current_event ==0){
    m_data_file.close();
    m_data_file.clear();
    std::string file =  "LAMS"+ m_util.IntToString(m_sou) +"_dis" + m_util.IntToString(m_dis)+ ".txt";
    m_data_file.open(file.c_str(), std::ios::in);
    if (!m_data_file)  {
      std::cerr << " Failed to open Data File. Distance: " << m_dis << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  if (m_current_event < m_firsteventstodisregard) {
    for (int ie = 0; ie < m_firsteventstodisregard; ++ie) {
      std::string buffer;
      getline(m_data_file, buffer);
      std::istringstream is(buffer);
      is >> std::hex >> CheckCounter >> std::hex >>  Photodiode1 >> std::hex >> Photodiode2;

      ++m_current_event;
    }
  } else {

    std::string buffer;
    getline(m_data_file, buffer);
    std::istringstream is(buffer);
    is >> std::hex >> CheckCounter >> std::hex >>  Photodiode1 >> std::hex >> Photodiode2;
  }

//     is >> CheckCounter >>  Photodiode1 >>  Photodiode2;
//     Data->SetChCounter(CheckCounter); Data->SetPhdiode1(Photodiode1);Data->SetPhdiode2(Photodiode2);
//     std::cout<<  Data->GetChCounter() << " " << Data->GetPhdiode1()<< " " <<  Data->GetPhdiode2() <<std::endl;

//     return Data;
}


Event*
DataReader::next_event(void)
{
  if (m_current_event_to_process > m_totalevents || 
      m_current_event > m_total_events_in_file) return 0;

// Read Event Data
  int CheckCounter;
  int Photodiode1;
  int Photodiode2;
  Utilities util;
 
  ReadData(CheckCounter,Photodiode1,Photodiode2);
//   std::cout<< CheckCounter<<" " <<Photodiode1 << " "<<Photodiode2 <<std::endl;
  ++m_current_event;
  ++m_current_event_to_process;
  
  return new Event(CheckCounter ,Photodiode1 , Photodiode2 );
 
}
