#ifndef CLASS_PRECISION
#define CLASS_PRECISION

#include <qmessagebox.h>

#include <sstream>
#include <iostream>
#include <vector>

#include <math.h>

#include "faces.hpp"

#ifdef CORE_LEVEL
#include "CORE/CORE.h"
#endif

#include "point.hpp"


//namespace gml 
//{
  
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


  //Floating values comparators
  
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


  //Geometric comparator

  /**
   * Compares two Point3D and return true if they
   * are the same (according to precision mechanism used)
   * and false otherwise
   *
   * @param p1 the first  Point3D
   * @param p2 the second Point3D
   * @return whether given points are equal or not
   */
  static bool isTheSame(gml::Point3D const &p1, gml::Point3D const &p2)
  {
    for (int i=0; i<3; i++)
    {
      if( !isEqual(p1[i], p2[i]) )
      {
        return false;
      }
    }
    return true;
  }

  /**
   * Returns whether or not Point3D p is on edge [a,b]
   *
   */
  static bool isOnEdge(gml::Point3D const & p,
                       gml::Point3D const & a, gml::Point3D const & b,
                       double * t) 
  {
    double null_value = 0;
    double one = 1;
    
    //Is this a real edge ?
    if ( isTheSame(a, b) )
    {
      if ( isTheSame(p, a) )
      {
        *t = 0.0;
        return true;
      }
      else
      {
        return false;
      }
    }

    //Point is the first vertex of the edge?
    if ( isTheSame(p, a) )
    {
      *t = 0.0;
      return true;
    }
    
    //Point is the second vertex of the edge?
    if ( isTheSame(p, b) )
    {
      *t = 1.0;
      return true;
    }
    else     //test if the point is between the two points on the edge
    {

      //OLD FASHION
//       double deltaX, deltaY, deltaZ;

//       double p0 = p[0]; double p1 = p[1]; double p2 = p[2];
//       double a0 = a[0]; double a1 = a[1]; double a2 = a[2];
//       double b0 = b[0]; double b1 = b[1]; double b2 = b[2];
      
      
//       deltaX = (p0 - a0)/(b0 - a0);
//       deltaY = (p1 - a1)/(b1 - a1);
//       deltaZ = (p2 - a2)/(b2 - a2);
      
//       deltaX = (p[0] - a[0])/(b[0] - a[0]);
//       deltaY = (p[1] - a[1])/(b[1] - a[1]);
//       deltaZ = (p[2] - a[2])/(b[2] - a[2]);

      
//       if ( isEqual(deltaX, deltaY) && isEqual(deltaY, deltaZ))
//       {
//         if (isGreaterOrEqual(deltaX, null_value) && isLesserOrEqual(deltaX, one) )
//         {
//           *t = deltaX;
//           return true;
//         }
//       }
      
       //NEW FASHION
      double ux = b[0] - a[0];
      double uy = b[1] - a[1];
      double uz = b[2] - a[2];

      double segmentLength2 = ux*ux + uy*uy + uz*uz;
      double inprod = ux*(p[0] - a[0]) + uy*(p[1] - a[1]) + uz*(p[2] - a[2]);

      if ( isGreaterOrEqual(inprod, null_value) && isLesserOrEqual(inprod, segmentLength2) )
      {
        *t = inprod / segmentLength2;
        return true;
      }
      else
      {
        return false;
      }
    }
    
    return false;    
  } //end of method isOnEdge

  
  /////////////////////////////////////////////////////
  // défine a plane with given points 
  // returns a vector which contains coefficient a,b,c,d of the plane if the plane exists
  // or an empty vector if the plane does not exist
  static std::vector<double> definePlane(std::vector < gml::Point3D > const &points)
  {
    int len=0;
    double a, b, c, norm;
    double xi, yi, zi, xj, yj, zj, xc, yc, zc;
    int i= 0;
    std::vector<double> result;
    int iNxt;

    a = b = c = xc = yc = zc = 0.0;
    do
    {
      iNxt = 0;

      xi = points[i][0];
      yi = points[i][1];
      zi = points[i][2];
      
      iNxt= (i == (int)points.size()-1)?0:i+1;
      xj = points[iNxt][0];
      yj = points[iNxt][1];
      zj = points[iNxt][2];
      
      a += ( yi - yj ) * ( zi + zj );
      b += ( zi - zj ) * ( xi + xj );
      c += ( xi - xj ) * ( yi + yj );
      xc += xi;
      yc += yi;
      zc += zi;
      len++;
      i++;
    }
    while( i < (int)points.size() );
    
    norm = sqrt( a * a + b * b + c * c );
    double w = (-len);

    if(! isEqual(norm, 0) )
    {
      result.push_back(a / norm);
      result.push_back(b / norm);
      result.push_back(c / norm);
      result.push_back((result[0] * xc + result[1] * yc + result[2] * zc) 
		       / w);
      return result;
    }
    
    return result;
  }

  /**
   * Returns whether the given point p lies on the same plane as thoose defined
   * in  the given vector.
   *
   **/
  static bool onPlane(gml::Point3D const & p, std::vector < gml::Point3D > const & planePoints)
  {
    std::vector<double> plane;
    double dist= 0.0;

    std::vector <int> samePoints;

    std::vector < gml::Point3D > allPoints;

    // Erase point if there are same point in points
    for(int i=0; i<(int)planePoints.size(); i++)
    {
      for(int j=i+1; j<(int)planePoints.size();j++)
      {
        //Est ce que la méthode isTheSame ne devrait elle pas etre utilisée plutot 
        // que comparer valeur par valeur ?
        if (isEqual(planePoints[i][0], planePoints[j][0]) &&
            isEqual(planePoints[i][1], planePoints[j][1]) &&
            isEqual(planePoints[i][2], planePoints[j][2]))
        {
          samePoints.push_back(i);  
        }
      }
    }
	
    bool diff=true;
    
    for (int i=0; i<(int)planePoints.size();i++)
    {
      int j=0;
      while (j<(int)samePoints.size() && diff)
      {
        if (i==samePoints[j])
        {
          diff = false;
        }
        else
        {
          j++;
        }
      }
	
      if (diff)
      {  
        allPoints.push_back(planePoints[i]);
      }
      diff = true;
    }

    plane = definePlane(allPoints);
    if(plane.empty())
    {
      return false;
    }

    dist = p[0]*plane[0] + p[1]*plane[1] + p[2]*plane[2] + plane[3];
    
    if( isEqual(dist, 0) )
    {
      return true;
    }
    return false;
  }

  /**
   * Returns whether the given point p lies on the same plane as thoose defined
   * in  the given vector.
   *
   **/
//   static bool onPlane(PointH const & p, std::vector < PointH > const & planePoints)
//   {
//     std::vector<double> plane;
//     double dist= 0.0;

//     std::vector <int> samePoints;

//     std::vector < gml::Point3D > allPoints;

//     // Erase point if there are same point in points
//     for(int i=0; i<(int)planePoints.size(); i++)
//     {
//       for(int j=i+1; j<(int)planePoints.size();j++)
//       {
//         //Est ce que la méthode isTheSame ne devrait elle pas etre utilisée plutot 
//         // que comparer valeur par valeur ?
//         if (isEqual(planePoints[i][0], planePoints[j][0]) &&
//             isEqual(planePoints[i][1], planePoints[j][1]) &&
//             isEqual(planePoints[i][2], planePoints[j][2]))
//         {
//           samePoints.push_back(i);  
//         }
//       }
//     }
	
//     bool diff=true;
    
//     for (int i=0; i<(int)planePoints.size();i++)
//     {
//       int j=0;
//       while (j<(int)samePoints.size() && diff)
//       {
//         if (i==samePoints[j])
//         {
//           diff = false;
//         }
//         else
//         {
//           j++;
//         }
//       }
	
//       if (diff)
//       {  
//         allPoints.push_back(planePoints[i]);
//       }
//       diff = true;
//     }

//     plane = definePlane(allPoints);
//     if(plane.empty())
//     {
//       return false;
//     }

//     dist = p[0]*plane[0] + p[1]*plane[1] + p[2]*plane[2] + p[3]*plane[3];
    
//     if( isEqual(dist, 0) )
//     {
//       return true;
//     }
//     return false;
//   }

   // intersection segment((p - 1erpoint vector)/segment(2e et 3e point du vecteur)
  static int inter(gml::Point3D const & p,
                   std::vector< gml::Point3D > const &points,
                   double* t1, double* t2)
  {
    double one = 1;
    double null_value = 0;
    
    int i;
    double d, a[3], b[3], c[3];
    std::vector< gml::Point3D > allPoints;
     
    allPoints.push_back(p);
    allPoints.push_back(points[0]);
    allPoints.push_back(points[1]);
    allPoints.push_back(points[2]);

    //define if all the points are on the plane
    if( ! onPlane(allPoints[0], allPoints) )
    {
      return 0;
    }

    if( ! onPlane(allPoints[1], allPoints) )
    {
      return 0;
    }

    if( ! onPlane(allPoints[2], allPoints) )
    {
      return 0;
    }

    if( ! onPlane(allPoints[3], allPoints) )
    {
      return 0;
    }


    for(i=0; i<3; i++)
    {
      a[i]= allPoints[1][i] - allPoints[0][i];
      b[i]= -allPoints[3][i] + allPoints[2][i];
      c[i]= allPoints[0][i] - allPoints[2][i];
    }
    
    for(i=0; i<3; i++)
    {
      int j, j_nxt;
      
      j=i;
      j_nxt=(i==2)?0:i+1;

      d= a[j]*b[j_nxt] - b[j]*a[j_nxt];
      
      if( ! isEqual(d, 0.0) )
      {
        *t1= (-c[j]*b[j_nxt] + b[j]*c[j_nxt])/d;
        *t2= (-a[j]*c[j_nxt] + c[j]*a[j_nxt])/d;
	
//        if( *t1 < -tolerance || *t1 > 1.+tolerance )
        if( isLesser(*t1, null_value) || isGreater(*t1, one) ) 
        {
          return 2;
        }
        
//        if( *t2 < -tolerance || *t2 > 1.+tolerance )
        if( isLesser(*t2, null_value) || isGreater(*t2, one) ) 
        {
          return 2;
        }
        return 1;
      }
    }
    
    return 0;
    
  } //end of method inter

  /**
   * Returns whether or not the given point p belongs to the face defined
   * by the vector points.
   */
  static bool onFace(gml::Point3D const & p, std::vector < gml::Point3D > const & points)
  {
    std::vector<double> plane;
//    double dist= 0.0;
    std::vector <int> samePoints;
    std::vector < gml::Point3D > allPoints;

    // Firstly copy of the vector points in the vector 
    // samePoints, if all the points are different
    for(int i=0; i<(int)points.size(); i++)
    {
      for(int j=i+1; j<(int)points.size();j++)
      {

        if (isTheSame(points[i], points[j]))
        {
          samePoints.push_back(i);
        }
      }
    }
    
    // Construction of the vector allPoints, with only the different points
    bool diff=true;
    for (int i=0; i<(int)points.size();i++)
    {
      int j=0;
      while (j<(int)samePoints.size() && diff)
      {
        if (i==samePoints[j])
        {
          diff = false;
        }
        else
        {
          j++;
        }
      }
      
      if (diff)
      {  
        allPoints.push_back(points[i]);
      }
      diff = true;
    }


    // 1) Check if the vector allPoints is a really a plan
    plane = definePlane(allPoints);
    if( plane.empty() )
    {
      return false;
    }
    
    // 2) Check if the current point is on the plan
    if( ! onPlane(p, allPoints) )
    {
      return false;
    }

    // 3) Check if the point belows to one of edge of the face
    for (int i=0 ; i<(int)allPoints.size() ; i++)
    {
      int next = i+1;
      if (next == (int)allPoints.size())
      {
        next = 0;
      }
      double t;

      if (isOnEdge(p, allPoints[i], allPoints[next], &t))
      {
        return true;
      }
    }
   
    // 4) Computation of a line


  //   double diffx = allPoints[0][0] - allPoints[1][0];
//     double diffy = allPoints[0][1] - allPoints[1][1];
//     double diffz = allPoints[0][2] - allPoints[1][2];

    gml::Vector3D diffVector =  allPoints[0] - allPoints[1];
    
    gml::Point3D newPoint = p + diffVector;
 //    newPoint[0] = p[0] + diffx;
//     newPoint[1] = p[1] + diffy;
//     newPoint[2] = p[2] + diffz;
    
    // 5) Check if the line cut or not the plan
    int nbCut = 0;
    for (int i=0 ; i<(int)allPoints.size() ; i++)
    {
      int next = i+1;
      if (next == (int)allPoints.size())
      {
        next = 0;
      }

      std::vector< gml::Point3D > newPlane;
      newPlane.push_back(newPoint);
      newPlane.push_back(allPoints[i]);
      newPlane.push_back(allPoints[next]);

      double t1, t2;
      int valueCut = inter(p, newPlane, &t1, &t2);
      if (valueCut > 0)
      {
        if (isGreaterOrEqual(t1, 0) &&
            isGreaterOrEqual(t2, 0) &&
            isLesserOrEqual(t2, 1))
        { 
          nbCut++;
        }
      }

      if (nbCut == 1)
      {
        return true;
      }
    }
    return false; 
  } //end of method on face


  //Returns wheter or not the segment [ a , b]
  // intersect he plane defined by the points in the vector
  static bool interPlan(gml::Point3D & a, gml::Point3D & b, 
                        std::vector < gml::Point3D > const & points,
                        double *t)
  {
    std::vector<double> plane;
    double null_value = 0.0;
    double one = 1.0;

    // 1) If the normal of the plan and the vector of the 
    //edge are perpendicular, then there is no verification
    double vectorEdgeX = a[0] - b[0];
    double vectorEdgeY = a[1] - b[1];
    double vectorEdgeZ = a[2] - b[2];

    plane = definePlane(points);
    if( plane.empty() )
    {
      return false;
    }

    //  if (plane[0]*vectorEdgeX + plane[1]*vectorEdgeY +	plane[2]*vectorEdgeZ
    //    == null_value)
    // BUG !!! PROBLEME 
    //Test incomplet pour conclure il faut s assure que la droite n est PAS coplanaire au plan
    if( isEqual((plane[0]*vectorEdgeX + plane[1]*vectorEdgeY +	plane[2]*vectorEdgeZ),
                 null_value)
      )
    {
      
      // 1.5) Verification if the egde is not a edge of the plane of the considerate face
      if (!onPlane(a, points) && !onPlane(b, points)) {
	return false;
      }

      

    }
    
    // 2) If the edge is an edge of the face
    bool found1 = false;
    bool found2 = false;
    int i=0;
    while ((!found1 || !found2 ) && i<points.size())
    {
      
      if ( isTheSame(a, points[i]) ) 
      {
        found1 = true;
      }
            
      if ( isTheSame(b, points[i]) )
      {
        found2 = true;
      }
      i++;
    }
    
    if (!found1 && !found2) {
      bool aOnFace = onFace(a, points);
      bool bOnFace = onFace(b, points);
      if (aOnFace) {
	*t=0.0;
	return true;
      }
      if (bOnFace) {
	*t=1.0;
	return true;
      }
      if (aOnFace, bOnFace) {
	return false;
      }
	

    if (found1 && found2)
    {
      return false;
    }

    // 3) Compute of t
    *t = (-plane[0] * a[0] - plane[1] * a[1] - plane[2] * a[2] - plane[3]) /
      (plane[0]*vectorEdgeX + plane[1]*vectorEdgeY + plane[2]*vectorEdgeZ);

    //Intersection avec la droite mais PAS le segment
    if ( isLesser(*t, null_value) || isGreater(*t ,one) )
    {
      return false;
    }
    else
    {
#ifndef CORE_LEVEL
      gml::Point3D interPoint = a.collinear(b, *t);
#else
      //TODO : check more accurately
      gml::Point3D interPoint = a.collinear(b, (*t).doubleValue() );
#endif
      if (! onFace(interPoint, points))
	{
	  return false;
	}
      else
	{
	  return true;
	}
    }
  }



// Verification if there is edges intersections
static void edgesIntersections(std::vector< std::vector<gml::Point3D> > & edges) {
  
  int nbVerif = 0;
  int nbValid = 0;
  int nbNotValid = 0;

  double one = 1;
  double null_value = 0;
  
  std::ostringstream oss;
  
  //Test intersections between egdes
  for (int i=0 ; i<(int)edges.size() ; i++)
    {
      for (int j=i+1 ; j<(int)edges.size() ; j++)
	{
	  std::vector <gml::Point3D> temp;
	  temp.push_back(edges[i][1]);
	  temp.push_back(edges[j][0]);
	  temp.push_back(edges[j][1]);
	  nbVerif++;
	  double t1, t2;
	  int value = inter( edges[i][0], temp, &t1, &t2);
	  
	  if (value == 1)
	    {
	      if ( ( isEqual(t1, null_value) || isEqual(t1, one) ) &&
		   ( isEqual(t2, null_value) || isEqual(t2, one) )    )
		{
		  nbValid ++;
		}
	      else
		{
		  nbNotValid++;
		}
	    }
	  else
	    {
	      nbValid++;
	    }
	}
    } //end of double loop to test edges intersection
  
  
  //Display the results !!
  oss << "Number of edges : " << edges.size() << std::endl
      << "Number of verifications : " << nbVerif << std::endl
      << "Number of valid intersections : " << nbValid << std::endl
      << "Number of not valid intersections : " << nbNotValid << std::endl;
  
  QMessageBox::information(0, "Validation 1 :", oss.str());
}

// Verification if each faces are in the same plane
static void facesOnSamePlan(std::vector<AbsFace*> & faces, std::vector<gml::Point3D> & points) {
  
  int nbVerif = 0;
  int nbValid = 0;
  int nbNotValid = 0;

  double one = 1;
  double null_value = 0;
  
  std::ostringstream oss;  

  for (int i=0 ; i<(int)faces.size(); i++)
    {
      nbVerif++;
      
      std::vector <int> & indexes =  *( faces[i]->getIndexes() );
      
      gml::Point3D firstPoint = points[ indexes[0] ];
      
      // The verification is necessary only if the face owns more of three points
      if ( (int)( indexes.size()) > 3)
	{
	  std::vector <gml::Point3D> temp;
	  
	  for (int j=1; j<(int)(indexes.size()); j++)
	    {
	      temp.push_back( points[ indexes[j] ] );
	    }
        
	  if ( ! onPlane(firstPoint, temp) )
	    {
	      nbNotValid++;
	    }
	  else
	    {
	      nbValid++;
	    }
	}
      else
	{
	  nbValid++;
	}
    } //end of for loop to test planarity of each face
  
  //Print the results !
  oss << "Number of faces : " << faces.size() << std::endl
      << "Number of verifications : " << nbVerif << std::endl
      << "Number of valid faces : " << nbValid << std::endl
      << "Number of not valid faces : " << nbNotValid << std::endl;
  QMessageBox::information(0, "Validation 2 :", oss.str());
}

static void edgesCutFaces(std::vector<AbsFace*> & faces, std::vector< std::vector<gml::Point3D> > & edges, std::vector<gml::Point3D> points) 
{

  int nbVerif = 0;
  int nbValid = 0;
  int nbNotValid = 0;
  
  double one = 1;
  double null_value = 0;

  std::ostringstream oss;
  
  // Verification if each edge doesn't cut a face
  for (int i=0 ; i<(int)edges.size() ; i++)
    {
      for (int j=0 ; j<(int)faces.size() ; j++)
	{
	  std::vector <gml::Point3D> temp;
	  nbVerif++;
	  
	  std::vector <int> & indexes =  *( faces[j]->getIndexes() );
	  
	  for (int k=0 ; k<(int)indexes.size() ; k++)
	    {
	      temp.push_back( points[indexes[k]] );
	    }
	  
	  double t;
	  
	  if (interPlan(edges[i][0], edges[i][1], temp, &t) )
	    {
	      if ( isEqual(t, null_value) || isEqual(t, one) )
		{
		  nbValid ++;
		}
	      else
		{
		  nbNotValid++;
		}
	    }
	  else
	    {
	      nbValid++;
	    }
	}
    }//end of double loop for. Last test edge versus face
  
  //Print the results 
  oss << "Number of faces : " << faces.size() << std::endl
      << "Number of edges : " << edges.size() << std::endl
      << "Number of verifications : " << nbVerif << std::endl
      << "Number of valid faces : " << nbValid << std::endl
      << "Number of not valid faces : " << nbNotValid << std::endl;
  
  QMessageBox::information(0, "Validation 3 :", oss.str());
  
}//end of validate method

static void validateModel(Faces & facesToBeValidated )
{
  
  std::vector<AbsFace*> faces      = facesToBeValidated.faces();
  std::vector<gml::Point3D> points = facesToBeValidated.points();
  
  bool find=false;
  
  std::vector< std::vector<gml::Point3D> > edges; 

  // Edges' construction
  for (int i=0 ; i<(int) faces.size() ; i++)
    { 
      std::vector <int> & indexes =  *( faces[i]->getIndexes() );
      
      for (int j=0 ; j< (int) indexes.size(); j++)
	{
	  std::vector <gml::Point3D> temp;
	  
	  temp.push_back( points[ indexes[j] ] );
	  
	  if (j+1 == (int) (indexes.size()) )
	    {
	      temp.push_back( points[indexes[0]] );
	    }
	  else
	    {
	      temp.push_back( points[indexes[j+1]] );
	    }

	  // Test if the found edge is not already in the vector edges
	  int k=0;
	  while (k<(int)edges.size() && !find) 
	    {
	      // Exact comparaison
	      if ((edges[k][0][0] == temp[0][0] && 
		   edges[k][0][1] == temp[0][1] &&
		   edges[k][0][2] == temp[0][2] &&
		   edges[k][1][0] == temp[1][0] &&
		   edges[k][1][1] == temp[1][1] &&
		   edges[k][1][2] == temp[1][2]) ||
		  (edges[k][0][0] == temp[1][0] && 
		   edges[k][0][1] == temp[1][1] &&
		   edges[k][0][2] == temp[1][2] &&
		   edges[k][1][0] == temp[0][0] &&
		   edges[k][1][1] == temp[0][1] &&
		   edges[k][1][2] == temp[0][2])) {
		   
		find = true;
		
	      }
	      else 
		{
		
		  k++;
		}
	    }
	  k=0;
	  if (!find) {
	    edges.push_back(temp);
	  }
	  else {
	    find = false;
	  }
	}
    }

  edgesIntersections(edges);
  facesOnSamePlan(faces, points);
  edgesCutFaces(faces, edges, points);


}  

#endif
