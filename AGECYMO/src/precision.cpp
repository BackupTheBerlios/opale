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
  
  
 
}
