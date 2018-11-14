#ifndef Time_h
#define Time_h 1


class Time {

private:

  int source;
  int distance;
  int depth;
  int timevalue;


public:
  
  Time(  int source,
	 int distance,
	 int depth,
	 int timevalue
	 );
  ~Time();
  
  inline int GetSource(void) {return source;}
  inline void SetSource(int t) {source=t;}
 
  inline int GetDistance(void) {return distance;}
  inline void SetDistance(int t) {distance=t;}

  inline int GetDepth(void) {return depth;}
  inline void SetDepth(int t) {depth=t;}

  inline int GetTimeValue(void) {return distance;}
  inline void SetTimeValue(int t) {distance=t;}

  void print(void) const;


};

#endif
