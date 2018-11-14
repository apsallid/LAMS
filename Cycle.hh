#ifndef Cycle_h
#define Cycle_h 1


class Cycle {

private:

  double TimeStart;
  double TimeEnd;
  double TimeL1toL2;
  double TimeL2toL3;
  double TimeL3toL4;


public:
  
  Cycle(  double TimeStart,
	  double TimeEnd,
	  double TimeL1toL2,
	  double TimeL2toL3,
	  double TimeL3toL4);
  ~Cycle();

  inline double GetTimeStart (void) {return TimeStart;}
  inline void SetTimeStart (double t) {TimeStart=t;}

  inline double GetTimeEnd(void) {return TimeEnd;}
  inline void SetTimeEnd(double t) {TimeEnd=t;}
  
  inline double GetTimeL1toL2(void) {return TimeL1toL2;}
  inline void SetTimeL1toL2(double t) {TimeL1toL2=t;}

  inline double GetTimeL2toL3(void) {return TimeL2toL3;}
  inline void SetTimeL2toL3(double t) {TimeL2toL3=t;}

  inline double GetTimeL3toL4(void) {return TimeL3toL4;}
  inline void SetTimeL3toL4(double t) {TimeL3toL4=t;}

  void print(void) const;


};

#endif
