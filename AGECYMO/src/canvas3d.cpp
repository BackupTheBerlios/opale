#include <typeinfo>
#include "canvas3d.hpp"


Canvas3D::Canvas3D(QWidget* parent, const char* name)
    : AbsCanvas(parent, name) //QGLWidget(parent, name),
{
  setCameraPosition(25, 25, 50);
//  buildAxesDPL();
  
}

void
Canvas3D::buildAxesDPL()
{
  _axesIndexDPL = glGenLists(1);

  qDebug("index DPL axes 3D = %d\n", _axesIndexDPL);
  
  if (_axesIndexDPL != 0)
  {
    glNewList(_axesIndexDPL, GL_COMPILE);

    
    GLUquadricObj* qobj = gluNewQuadric();
    gluQuadricNormals(  qobj, GLU_SMOOTH ) ;
    gluQuadricDrawStyle( qobj, GLU_FILL ) ;
    gluQuadricOrientation( qobj, GLU_OUTSIDE ) ;
    
    static const GLdouble axis_radius = 0.0075 ;
    static const GLdouble axis_length = 0.125 ;
    static const GLdouble arrow_radius = 0.01 ;
    static const GLdouble arrow_length = 0.04 ;
    
    glPolygonMode( GL_FRONT_AND_BACK , GL_FILL ) ;
    glEnable( GL_COLOR_MATERIAL ) ;
    glColorMaterial( GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE ) ;
    
    //Y
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glColor4f(1.0f,0.0f,0.0f, 0.5f);
    gluCylinder(qobj, axis_radius, axis_radius,axis_length, 12, 1);
    glTranslated(0.0, 0.0, axis_length);
    gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
    gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
    glPopMatrix();
  
  //X
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glColor4f(0.0f,1.0f,0.0f, 0.5f);
    gluCylinder(qobj, axis_radius, axis_radius, axis_length, 12, 1);
    glTranslated(0.0, 0.0, axis_length);
    gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
    gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
    glPopMatrix();
    
    //Z
    glPushMatrix();
    glColor4f(0.0f,0.0f, 1.0f, 0.5f);
    gluCylinder(qobj, axis_radius, axis_radius, axis_length, 12, 1);
    glTranslated(0.0, 0.0, axis_length);
    gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
    gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
    glPopMatrix();
  
    glEndList();
    
  }
  else
  {
    qDebug("Erreur a la creation de la Display liste pour les axes du repere3D\n");
    
  }
  


}


void
Canvas3D::drawAxes()
{
//   GLUquadricObj* qobj = gluNewQuadric();
//   gluQuadricNormals(  qobj, GLU_SMOOTH ) ;
//   gluQuadricDrawStyle( qobj, GLU_FILL ) ;
//   gluQuadricOrientation( qobj, GLU_OUTSIDE ) ;
  
//   static const GLdouble axis_radius = 0.0075 ;
//   static const GLdouble axis_length = 0.125 ;
//   static const GLdouble arrow_radius = 0.01 ;
//   static const GLdouble arrow_length = 0.04 ;
  
//   glPolygonMode( GL_FRONT_AND_BACK , GL_FILL ) ;
//   glEnable( GL_COLOR_MATERIAL ) ;
//   glColorMaterial( GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE ) ;

//   //Y
//   glPushMatrix();
//   glRotated(-90, 1, 0, 0);
//   glColor4f(1.0f,0.0f,0.0f, 0.5f);
//   gluCylinder(qobj, axis_radius, axis_radius,axis_length, 12, 1);
//   glTranslated(0.0, 0.0, axis_length);
//   gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
//   gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
//   glPopMatrix();

//   //X
//   glPushMatrix();
//   glRotated(90, 0, 1, 0);
//   glColor4f(0.0f,1.0f,0.0f, 0.5f);
//   gluCylinder(qobj, axis_radius, axis_radius, axis_length, 12, 1);
//   glTranslated(0.0, 0.0, axis_length);
//   gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
//   gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
//   glPopMatrix();

//   //Z
//   glPushMatrix();
//   glColor4f(0.0f,0.0f, 1.0f, 0.5f);
//   gluCylinder(qobj, axis_radius, axis_radius, axis_length, 12, 1);
//   glTranslated(0.0, 0.0, axis_length);
//   gluDisk(qobj, axis_radius, arrow_radius, 12, 1);
//   gluCylinder(qobj, arrow_radius, 0, arrow_length, 12, 1);
//   glPopMatrix();

  
  glPolygonMode( GL_FRONT_AND_BACK , GL_FILL ) ;
  glEnable( GL_COLOR_MATERIAL ) ;
  glColorMaterial( GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE ) ;
    
  glCallList(_axesIndexDPL);
  
  
  //gluSphere(quadric, 0.1, 10, 10 );
}

void
Canvas3D::initializeGL()
{
  glEnable     (GL_DITHER);
  glEnable     (GL_DEPTH_TEST);
  glClearColor (0, 0, 0, 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  buildAxesDPL();
  
  _chronometer.start();
}

void
Canvas3D::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  setView();
  drawAxes();
 
  _renderer.render();

  _nFps++;
  drawFps();
}

void
Canvas3D::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(0.75, (double)width/(double)height, 0.1, 500.0);
}

Renderer&
Canvas3D::renderer()
{
  return _renderer;
}

void
Canvas3D::mousePressEvent(QMouseEvent* event)
{
  _clickPos[0] = event->x();
  _clickPos[1] = event->y();

  qDebug("click en position [ %d, %d] \n", _clickPos[0], _clickPos[1]);
    
  updateGL();
}

void
Canvas3D::mouseMoveEvent(QMouseEvent* event)
{
  
  std::cout << " MOVE position x = " << event->x() 
            << " position y = " << event->y() << std::endl;
  
}

void
Canvas3D::mouseReleaseEvent(QMouseEvent* event)
{
  std::cout << " RELEASE "
            << "position x = " << event->x() 
            << " position y = " << event->y() << std::endl;
  
}
