#ifndef Event_h
#define Event_h 1


class Event {

private:

  int CheckCounter;
  int Photodiode1;
  int Photodiode2;


public:
  
  Event(int CheckCounter,
	int Photodiode1,
	int Photodiode2);
  ~Event();

  inline int GetChCounter (void) {return CheckCounter;}
  inline void SetChCounter (int t) {CheckCounter=t;}

  inline int GetPhdiode1(void) {return Photodiode1;}
  inline void SetPhdiode1(int t) {Photodiode1=t;}
  
  inline int GetPhdiode2(void) {return Photodiode2;}
  inline void SetPhdiode2(int t) {Photodiode2=t;}

  void print(void) const;


};

#endif
