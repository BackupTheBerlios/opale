#include "precision.hpp"


namespace gml
{
  //Static variable initialization
  bool Precision::instanceFlag = false;

  Precision* Precision::single = NULL;

  
//Static Methods
  
//Method to retrieve an instance of Precision
  Precision* Precision::getInstance()
  {
    if(! instanceFlag)
    {
      single = new Precision();

      instanceFlag = true;
      return single;
    }
    else
    {
      return single;
    }
  }


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
  
  
 
}
