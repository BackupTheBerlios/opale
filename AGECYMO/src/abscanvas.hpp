#ifndef CLASS_ABSCANVAS_H
#define CLASS_ABSCANVAS_H

//Qt's objectes
#include "qdatetime.h"
#include "qstring.h"
#include "qgl.h"

//Our objects
#include "camera.hpp"

class AbsCanvas : public QGLWidget
{
  Q_OBJECT

  protected:
  
  static const int MIN_TIME_FOR_FPS_MEASURE = 2;
  static const int FPS_X_OFFSET = 10;
  static const int FPS_Y_OFFSET = 10;

  int _nFps; //frame per second
  int _fpsEnabled; //True if we display the FPS on the Canvas false otherwise
  
  QTime _chronometer; // used to count the number of frames rendered. 
  gml::Camera _camera; //The Camera associated
  
  
  int _axesIndexDPL; //indexe of the display list containing the axes.

  
  public:
  AbsCanvas(QWidget* parent = 0, const char* name = 0);
  virtual ~AbsCanvas();

  
  void setCameraPosition(gml::Point3D const& new_position);
  void setCameraPosition(double px, double py, double pz);
  
  void setCameraUp(double upx, double upy, double upz);
  void setCameraLookAt(double cx, double cy, double cz);
  

  protected:

  virtual void buildAxesDPL() = 0;
  virtual void drawAxes() = 0;

  void setView();//set the view according to the camera
  void drawFps();
  
  //OpenGL routines
 //  virtual void initializeGL     ();
//   virtual void paintGL          ();
//   virtual void resizeGL         (int, int);  
//   virtual void mousePressEvent  (QMouseEvent*);
//   virtual void mouseMoveEvent   (QMouseEvent*);
//   virtual void mouseReleaseEvent(QMouseEvent*);

  
};



#endif
