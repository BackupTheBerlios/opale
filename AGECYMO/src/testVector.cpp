#include <iostream>

#include "testVector.hpp"

#include "absVector.hpp"
#include "vector.hpp"
#include "point.hpp"

using namespace gml;

void testVector()
{
  std::cout << "***** TEST VECTOR *****" << std::endl;
  
  gml::Vector<> v1;
  gml::Vector<> v2;
  gml::Vector<int> v3;
  gml::Vector<float> v4;
  gml::Vector<> v5;

  gml::AbsVector<> av1;
  gml::Point<> pt1;

  gml::Point3D p1, p2;
  gml::PointH  ph1;
  gml::Vector3D v3d1;
  gml::Vector3F v3f1;
  
  
  std::cout << "p1  = " << p1 << std::endl;
  std::cout << "ph1  = " << ph1 << std::endl;
  std::cout << "v3d1  = " << v3d1 << std::endl;
  std::cout << "v3f1  = " << v3f1 << std::endl;

  p1[0] = 2.0; p1[1] = 1; p1[2] = 0;
  p2[0] = -1.0; p2[1] = 1; p2[2] = -1;

  std::cout << "p1  = " << p1 << std::endl;
  std::cout << "p2  = " << p2 << std::endl;
  
  v3d1 = p2 - p1;
  std::cout << "v3d1  = " << v3d1 << std::endl;
  
  v1[0] = 1.0; v1[1] = 0; v1[2] = 0;
  v2[0] = 5.00; v2[1] = 1; v2[2] = 1;
  v3[0] = 0; v3[1] = 1; v3[2] = 2;
  v4[0] = 0; v4[1] = 0; v4[2] = 0;

  
  std::cout << "v1  = " << v1 << std::endl;
  std::cout << "v2  = " << v2 << std::endl;
  std::cout << "v3  = " << v3 << std::endl;
  std::cout << "v4  = " << v4 << std::endl;

//   std::cout << v1 << std::endl;
//   std::cout << v2 << std::endl;
  
//  double f = gml::Vector<>::dot(v1, v2);
  double f = gml::dot(v1, v2);
  
  v3 = v3 * 3;
  
  v2 = v1 * 5.1220;
  v2 = v3;
  
  v4 = v2 / 5.0;
  std::cout << "v4  = " << v4 << std::endl;
  v4.normalize();

  v5 = v4 + v3;
  
  //v3 = v3 * 4.8; //COMPILE ERROR 
  
  std::cout << "v1  = " << v1 << std::endl;
  std::cout << "v2  = " << v2 << std::endl;
  std::cout << "v3  = " << v3 << std::endl;
  std::cout << "v4  = " << v4 << std::endl;
  std::cout << "v5  = " << v5 << std::endl;

  std::cout << "f = " << f << std::endl;
  std::cout << "v3's square norm = " << v3.squareNorm() << std::endl;
  std::cout << "v2's square norm = " << v2.squareNorm() << std::endl;
  std::cout << "v1's square norm = " << v1.squareNorm() << std::endl;

  std::cout << "v3's  norm = " << v3.norm() << std::endl;
  std::cout << "v2's  norm = " << v2.norm() << std::endl;
  std::cout << "v1's  norm = " << v1.norm() << std::endl;
  std::cout << "v4's  norm = " << v4.norm() << std::endl;
  std::cout << "***** END *****" << std::endl;
  
}
