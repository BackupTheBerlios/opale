#ifndef CLASS_PRECISION
#define CLASS_PRECISION

#include <iostream>
#include <math.h>


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
      return (a => b );
    }
#endif    

  }; //end of class Precision
  
}//end of namespace

#endif
