#include "cylinderGenerator.hpp"


CylinderGenerator::CylinderGenerator(Canvas3D & acanvas)
    : _canvas(acanvas),
      _points(NULL),
      _faces(NULL),
      _isWayClosed(false),
      _chronometer()

{
}

CylinderGenerator::~CylinderGenerator()
{
  if ( _faces != NULL)
  {
    delete _faces;
  }
  
  if ( _points != NULL)
  {
    delete _points;
  }
  
}
void
CylinderGenerator::setWayClosed(bool wayStatus)
{
  _isWayClosed = wayStatus;
}

int
CylinderGenerator::generate(const std::vector<Point3D> & wayPts,
                            const std::vector<Point3D> & sectionPts,
                            const std::vector<Point3D> & profilePts)
{

  qDebug("CylinderGenerator: Starting the generation !!!!");

  _chronometer.start();

  generatePoints( wayPts, sectionPts, profilePts);
  generateFaces(wayPts.size(), sectionPts.size() );

  
  //todo put this in the generate Method
  Faces* model = new Faces(_points, _faces);

  qDebug(" Model = %p", model);
  qDebug("about to set the model");

  _canvas.setModel(*model);


  return _chronometer.elapsed();
}

void
CylinderGenerator::generatePoints(const std::vector<Point3D> & wayPts,
                                  const std::vector<Point3D> & sectionPts,
                                  const std::vector<Point3D> & profilePts)
{
  //delete the old points 
//   if (_points != NULL)
//   {
//     delete _points;
//   }
  
  _points = new std::vector<Point3D>();

  Matrix3D profileMatrix;
  Matrix3D tmpFrame;
  Matrix3D currentFrame;
  Matrix3D previousFrame;
  
  currentFrame.loadIdentity();
  previousFrame.loadIdentity();
  

  
  initFrenetFrame( wayPts[0], wayPts[1], currentFrame);

//   computeProfileMatrix(profilePts, 0, profileMatrix);
//   tmpFrame = currentFrame;
//   currentFrame = tmpFrame * profileMatrix;

//   std::cout << "FIRST currentFrame = " << std::endl
//             << currentFrame << std::endl;
  
  
  computePointsAccordingToFrame(sectionPts, currentFrame);
  
  const unsigned int size = wayPts.size();

  qDebug("We have %d points for the path", size);
  
  for (unsigned int i=1; i<size-1; i++)
  {
    previousFrame = currentFrame;

    
    
    computeFrenetFrame(previousFrame,
                       wayPts[i-1], wayPts[i], wayPts[i+1],
                       currentFrame);
    //Profile part
//     computeProfileMatrix(profilePts, i, profileMatrix);
//     tmpFrame = currentFrame;
//     currentFrame = tmpFrame * profileMatrix;
    
    computePointsAccordingToFrame(sectionPts, currentFrame);
    
  }

  //previousFrame = currentFrame;
  lastFrenetFrame(wayPts[size-2], wayPts[size-1], currentFrame);

  //Profile part
//   computeProfileMatrix(profilePts, (size-1), profileMatrix);
//   tmpFrame = currentFrame;
//   currentFrame = tmpFrame * profileMatrix;
    
  computePointsAccordingToFrame(sectionPts, currentFrame);
  
}

void
CylinderGenerator::computeFrenetFrame( const Matrix3D & previousFrame,
                                       const Point3D & previous,
                                       const Point3D & current,
                                       const Point3D & next,
                                       Matrix3D & newCurrentFrame)
{
  Vector3D tangente, binormale, normale, quasiNormale;
  
  Vector3D tplus;
  Vector3D tmoins;
  Vector3D test;
  
  tplus  = next - current;
  tmoins = current - previous;

  test = cross(tplus, tmoins);

  //Check this particular case
  if (test.norm() < EPSILON)
  {
//    qDebug("PROOOOOOOOOOOOOOOOOOOOOOBLEM");
    
    initFrenetFrame( current, next, newCurrentFrame);
    return;
  }

  quasiNormale = tplus - tmoins;
  quasiNormale.normalize();

  tplus.normalize();
  tangente = tplus;
  
  binormale  = cross(tangente, quasiNormale);
  binormale.normalize();
  
  normale = cross(binormale, tangente);
  normale.normalize();
  
  newCurrentFrame = Matrix3D( binormale[0], tangente[0], normale[0], current[0],
                              binormale[1], tangente[1], normale[1], current[1],
                              binormale[2], tangente[2], normale[2], current[2],
                              0, 0, 0, 1);

//   newCurrentFrame = Matrix3D( normale[0], tangente[0], binormale[0], current[0],
//                               normale[1], tangente[1], binormale[1], current[1],
//                               normale[2], tangente[2], binormale[2], current[2],
//                               0, 0, 0, 1);

//   newCurrentFrame = Matrix3D( tangente[0],  normale[0], binormale[0], current[0],
//                               tangente[1],  normale[1], binormale[1], current[1],
//                               tangente[2],  normale[2], binormale[2], current[2],
//                               0, 0, 0, 1);

  Vector3D previousBiNormal;
  previousBiNormal[0] = previousFrame.m[0];
  previousBiNormal[1] = previousFrame.m[4];
  previousBiNormal[2] = previousFrame.m[8];

  
  if (binormale[2] != previousBiNormal[2])
  {
    std::cout << "Binormale Changed" << std::endl;
    std::cout <<  "Previous Binormal = " << previousBiNormal << std::endl;
    std::cout <<  "New Binormal = " << binormale << std::endl;

    
    std::cout << "previous frame is :" << std::endl
              << previousFrame << std::endl;

    
    newCurrentFrame = Matrix3D( -binormale[0], tangente[0], -normale[0], current[0],
                                -binormale[1], tangente[1], -normale[1], current[1],
                                -binormale[2], tangente[2], -normale[2], current[2],
                                0, 0, 0, 1);

    
    return;
  }
  
  
  std::cout << "CURRENT frame is :" << std::endl
            << newCurrentFrame << std::endl;
  
}

void
CylinderGenerator::initFrenetFrame(const Point3D & p1,
                                   const Point3D & p2,
                                   Matrix3D & frame)
{

  qDebug("Dans initFrenetFrame");
  
  Vector3D v1;
  v1 = p2 - p1;
  v1.normalize();

  Vector3D v2;
  Vector3D a, b, c;
  
  //TODO : check more accuratly
  v2[0] = - v1[1]; v2[1] =  v1[0]; v2[2] = 0;

  a =  v2;

  b = cross(v1, a);
  b.normalize();
  
//  a = cross(v1, v2);
//  a.normalize();

//  b = cross(v1, a);
//  b.normalize();
  
//   std::cout << "v1 = " << v1 << std::endl;
//   std::cout << "v2 = " << v2 << std::endl;
//   std::cout << "a = " << a << std::endl;
//   std::cout << "b = " << b << std::endl;
  
  frame = Matrix3D ( b[0], v1[0], a[0], p1[0],
                     b[1], v1[1], a[1], p1[1],
                     b[2], v1[2], a[2], p1[2],
                     0 , 0, 0, 1);
  
  std::cout << "frame = " << std::endl
            << frame << std::endl;
  
  
}

void
CylinderGenerator::lastFrenetFrame(const Point3D & p1,
                                   const Point3D & p2,
                                   Matrix3D & frame)
{

  qDebug("Dans LAST FrenetFrame");
  
  Vector3D v1;
  v1 = p2 - p1;
  v1.normalize();

  Vector3D v2;
  Vector3D a, b, c;
  
  //TODO : check more accuratly
  v2[0] = - v1[1]; v2[1] =  v1[0]; v2[2] = 0;

  a = v2;
  
  //a = cross(v1, v2);
  //a.normalize();

  b = cross(v1, a);
  b.normalize();
  
//   std::cout << "v1 = " << v1 << std::endl;
//   std::cout << "v2 = " << v2 << std::endl;
//   std::cout << "a = " << a << std::endl;
//   std::cout << "b = " << b << std::endl;
  
  frame = Matrix3D ( b[0], v1[0], a[0], p2[0],
                     b[1], v1[1], a[1], p2[1],
                     b[2], v1[2], a[2], p2[2],
                     0 , 0, 0, 1);
  
  std::cout << "LAST frame = " << std::endl
            << frame << std::endl;
    
}


void
CylinderGenerator::computeProfileMatrix( const std::vector<Point3D> & profilePts,
                                         int indexCurrentPoint,
                                         Matrix3D & profileMatrix)
{
  //Compute a profile matrix according to the profile curve
  //TODO: just do it !
  profileMatrix.loadIdentity();

  double scaleFactor = profilePts[indexCurrentPoint][0];

  std::cout << "Point current profile point = " << profilePts[indexCurrentPoint] << std::endl;
  qDebug("scaleFactor = %f", scaleFactor);
  
  profileMatrix = Matrix3D::scale( scaleFactor, scaleFactor, scaleFactor);
}

void
CylinderGenerator::computePointsAccordingToFrame( const std::vector<Point3D> & sectionPts,
                                                  Matrix3D & currentFrame)
{
  Point3D newPt;
  
  for (unsigned int i=0; i< sectionPts.size(); i++)
  {
    newPt = currentFrame * sectionPts[i];

//     std::cout << " sectionPt = " << sectionPts[i] << std::endl;
//     std::cout << " newPt = " << newPt << std::endl;
    
    _points->push_back( newPt );
  }
  
}
 

void
CylinderGenerator::generateFaces(int nbPtWay, int nbPtSection)
{
  int t1, t2, t3, t4, t5, t6;

  // Older faces should be deleted
//   if (_faces !=NULL)
//   {
//     delete _faces;
//   }
  
  _faces = new std::vector<AbsFace*>();
  
  for (int i=0; i< (nbPtWay-1); i++)
  {
    for (int j=0; j<nbPtSection; j++)
    {
      t1 = i * nbPtSection + j;
      t2 = (t1+1)%nbPtSection + i*nbPtSection;
      t3 = (i+1) * nbPtSection + j;
      t4 = t2;
      t5 = t2+ nbPtSection;
      t6 = t3;

      Tria* triangle1 = new Tria(_points, t1, t2, t3);
      Tria* triangle2 = new Tria(_points, t4, t5, t6);

      _faces->push_back(triangle1);
      _faces->push_back(triangle2);
    }
  }

  //TODO: Add a connexion between last section and the first
  // if the way curve is closed

  // TODO : Check this or the normal for face...
//   std::vector<int> * indexes = new std::vector<int>();

//   for (int i = (nbPtSection - 1); i>=0; i--)
//   {
//     indexes->push_back(i);
//   }
  
//   Face* bottom = new Face( indexes, _points, nbPtSection);
//   _faces->push_back(bottom);


//   indexes->clear();
  
//   int i1 = _points->size() - nbPtSection;
//   int i2 = _points->size();
  
//   for (int i=i1; i<=i2; i++)
//   {
//     indexes->push_back(i);
//   }
  
//   Face* top = new Face( indexes, _points, nbPtSection);
//   _faces->push_back(top);
//   delete indexes;

}

  
