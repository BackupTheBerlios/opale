#ifndef CLASS_CANVAS3D
#define CLASS_CANVAS3D


#include <qaccel.h>

#include "point.hpp"
#include "camera.hpp"
#include "abscanvas.hpp"
#include "renderer.hpp"

class Canvas3D : public AbsCanvas   //public QGLWidget
{
  Q_OBJECT
  
  //Public Members/Attributes
  public:

  enum AccelKey
  {
    CAMERA_TURN_RIGHT ,
    CAMERA_TURN_LEFT  ,
    CAMERA_TURN_DOWN  ,
    CAMERA_TURN_UPPER ,
    CAMERA_MOVE_AWAY  ,
    CAMERA_MOVE_CLOSER,
    ENABLE_DRAW_AXES,
    ENABLE_DRAW_FPS,
    ENABLE_DRAW_BOUNDING_BOX,
    ENABLE_DRAW_INFO_MODEL, //number of quads, tria etc
    WIREFRAME_RENDERING_MODE,
    FLAT_RENDERING_MODE,
    GOURAUD_RENDERING_MODE,
    WF_HDLR_RENDERING_MODE,
  };

  private:

  Renderer _renderer;

  bool     _axesEnabled;
  
  gml::Point2D _clickPos; //position saved when the user clicks

  gml::Point3D _lightPos; //position of the light which is used for gouraud shading
  
  QAccel*  _accel;
  
  
  public:
  Canvas3D(QWidget* parent = 0, const char* name = 0);
  ~Canvas3D();
  
  
  Renderer& renderer();
  
  
  protected:
  virtual void initializeGL     ();
  virtual void paintGL          ();
  virtual void resizeGL         (int, int);  
  
  virtual void mousePressEvent  (QMouseEvent *);
  virtual void mouseMoveEvent   (QMouseEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);

  
  private:

  void buildAxesDPL();
  void drawAxes();


  private slots:

  void accelEvent(int id);
  
 
};


#endif
