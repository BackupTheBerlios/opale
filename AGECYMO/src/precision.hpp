#ifndef CLASS_PRECISION
#define CLASS_PRECISION

#include <iostream>
#include <math.h>

#ifdef CORE_LEVEL
#include "CORE/CORE.h"
#endif


namespace gml 
{
  
  class Precision
  {
    private:
    
    double EPSILON;

    //For Singleton Management
    static bool        instanceFlag;
    static Precision*  single;
  
    Precision()
    {
      EPSILON = 0.1;
    }

    public:

    static Precision* getInstance();
    
    ~Precision()
    {
        instanceFlag = false;
    }  

    void setEpsilon(double newValue)
    {
      EPSILON = newValue;
    }

    double getEpsilon() const
    {
      return EPSILON;
    }

//Core library not used
#ifndef CORE_LEVEL

    bool isEqual(double a, double b)
    {
      double delta = fabs( a - b);
      return (delta <= EPSILON);
    }

    bool isLesser(double a, double b)
    {
      return (a < b - EPSILON);
    }

    bool isLesserOrEqual(double a, double b)
    {
      return (a < b + EPSILON);
    }
  
    bool isGreater(double a, double b)
    {
      return (a > b + EPSILON);
    }

    bool isGreaterOrEqual(double a, double b)
    {
      return (a > b - EPSILON);
    }

#else

    bool isEqual(double a, double b)
    {
      return (a == b);  
    }

    bool isLesser(double a, double b)
    {
      return (a < b );
    }
  
    bool isLesserOrEqual(double a, double b)
    {
      return (a <= b );
    }
  
    bool isGreater(double a, double b)
    {
      return (a > b );
    }
  
    bool isGreaterOrEqual(double a, double b)
    {
      return (a >= b );
    }

#endif    

  }; //end of class Precision

  static bool isEqual(double a, double b)
  {
    Precision*  pre = Precision::getInstance();
    return pre->isEqual( a, b);
  }
  
  static bool isGreater(double a, double b)
  {
    Precision*  pre = Precision::getInstance();
    return pre->isGreater( a, b);
  }
  
  static bool isGreaterOrEqual(double a, double b)
  {
    Precision*  pre = Precision::getInstance();
    return pre->isGreaterOrEqual( a, b);
  }
  

  static bool isLesser(double a, double b)
  {
    Precision*  pre = Precision::getInstance();
    return pre->isLesser( a, b);
  }
  
  static bool isLesserOrEqual(double a, double b)
  {
    Precision*  pre = Precision::getInstance();
    return pre->isLesserOrEqual( a, b);
  }


  
}//end of namespace

#endif
