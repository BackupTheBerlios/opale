#include "canvas2d.hpp"


Canvas2D::Canvas2D(QWidget* parent, const char* name)
    : AbsCanvas(parent, name)
{
}


void
Canvas2D::buildAxesDPL()
{

  _axesIndexDPL = glGenLists(1);

  qDebug("index DPL axes 2D = %d\n", _axesIndexDPL);

  if (_axesIndexDPL != 0)
  {
    glNewList(_axesIndexDPL, GL_COMPILE);
    
    glColor3f(0.7, 0.0, 0.0);
    
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();
    
    glColor3f(0.0, 0.7, 0.0);
    
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    glEndList();
    
  }
  else
  {
    qDebug("Erreur a la creation de la Display liste pour les AXES 2D \n");
  }
  
}


void
Canvas2D::drawAxes()
{
  std::cout << "ici " << std::endl;
  
//   glColor3f(0.7, 0.0, 0.0);
  
//   glBegin(GL_LINES);
//   glVertex2f(0.0, 0.0);
//   glVertex2f(1.0, 0.0);
//   glEnd();

//   glColor3f(0.0, 0.7, 0.0);
  
//   glBegin(GL_LINES);
//   glVertex2f(0.0, 0.0);
//   glVertex2f(0.0, 1.0);
//   glEnd();

      
  glCallList(_axesIndexDPL);

}

void
Canvas2D::initializeGL()
{
  glClearColor (0.5, 0.5, 0.5, 0);
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPolygonMode(GL_FRONT, GL_LINE);

  buildAxesDPL();
  
}

void
Canvas2D::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawAxes();
  
  glColor3f(0.0, 0.0, 0.85);

}


void
Canvas2D::resizeGL(int width, int height)
{
  double w2 = width / 2.0;
  double h2 = height / 2.0;
  
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-4, 4, -4, 4);
}


void
Canvas2D::mousePressEvent(QMouseEvent* event)
{
}

void
Canvas2D::mouseMoveEvent(QMouseEvent* event)
{
}

void
Canvas2D::mouseReleaseEvent(QMouseEvent* event)
{
  
}
