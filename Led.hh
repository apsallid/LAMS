#ifndef Led_h
#define Led_h 1

#include <vector>

class Led {

private:

  double TimeStart;
  double TimeEnd;
  std::vector<int> Ledflash;

public:
  
  Led(  double TimeStart,
	double TimeEnd,
	std::vector<int> Ledflash);
  ~Led();

  inline double GetTimeStart (void) {return TimeStart;}
  inline void SetTimeStart (double t) {TimeStart=t;}

  inline double GetTimeEnd(void) {return TimeEnd;}
  inline void SetTimeEnd(double t) {TimeEnd=t;}
  
  inline std::vector<int> GetLedflash(void) {return Ledflash;}

  void print(void) const;


};

#endif
