#ifndef InputParameters_h
#define InputParameters_h 1

#include <string>
#include <sstream>

class InputParameters {

private:

public:

  InputParameters();
  ~InputParameters();

  inline std::string IntToString (int number1)
  {
    std::ostringstream oss1;
    oss1<< number1;
    return oss1.str();
  }

};

#endif
