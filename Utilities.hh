#ifndef Utilities_h
#define Utilities_h 1

#include <string>
#include <sstream>

class Utilities {

private:

public:

  Utilities();
  ~Utilities();

  inline std::string IntToString (int number1)
  {
    std::ostringstream oss1;
    oss1<< number1;
    return oss1.str();
  }

};

#endif
