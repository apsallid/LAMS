#ifndef TransmissionLength_h
#define TransmissionLength_h 1


class TransmissionLength {

private:

  double wavelength;
  double trlength;
  double errorintrlength;


public:
  
  TransmissionLength( double wavelength,
		      double trlength,
		      double errorintrlength);
  ~TransmissionLength();

  inline double GetWLength(void) {return wavelength;}
  inline void SetWLength(double t) {wavelength=t;}
 
  inline double GetTrLen(void) {return trlength;}
  inline void SetTrLen(double t) {trlength=t;}

  inline double GetErrTrLen(void) {return errorintrlength;}
  inline void SetErrTrLen(double t) {errorintrlength=t;}


  void print(void) const;


};

#endif
