#ifndef CLASS_CANVAS3D
#define CLASS_CANVAS3D


#include "point.hpp"
#include "camera.hpp"
#include "abscanvas.hpp"
#include "renderer.hpp"

class Canvas3D : public AbsCanvas   //public QGLWidget
{
  Q_OBJECT
  
  private:

  Renderer _renderer;

  gml::Point2D _clickPos; //position saved when the user clicks

  //int _axesIndexDPL; //indexe of the display list containing the axes.
  
  
  public:
  Canvas3D(QWidget* parent = 0, const char* name = 0);

  Renderer& renderer();
  
  
  protected:
  virtual void initializeGL     ();
  virtual void paintGL          ();
  virtual void resizeGL         (int, int);  
  virtual void mousePressEvent  (QMouseEvent*);
  virtual void mouseMoveEvent   (QMouseEvent*);
  virtual void mouseReleaseEvent(QMouseEvent*);
  
  private:

  void buildAxesDPL();
  void drawAxes();
  
};


#endif
