#ifndef Intensity_h
#define Intensity_h 1


class Intensity {

private:

  int wavelength;
  double mean;
  double rms;
  int distance;


public:
  
  Intensity( int wavelength,
	     double mean,
	     double rms,
	     int distance);
  ~Intensity();

  inline int GetWLength(void) {return wavelength;}
  inline void SetWLength(int t) {wavelength=t;}
 
  inline double GetMean(void) {return mean;}
  inline void SetMean(double t) {mean=t;}

  inline double GetRMS(void) {return rms;}
  inline void SetRMS(double t) {rms=t;}

  inline int GetDistance(void) {return distance;}
  inline void SetDistance(int t) {distance=t;}

  void print(void) const;


};

#endif
