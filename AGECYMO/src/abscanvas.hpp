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

  //Public Members/Attributes
  public:
  
  //Protected Members/Attributes
  protected:
  
  static const int MIN_TIME_FOR_FPS_MEASURE = 2;
  static const int FPS_X_OFFSET = 10;
  static const int FPS_Y_OFFSET = 10;

  int _nFps; //frame per second
  int _fpsEnabled; //True if we display the FPS on the Canvas false otherwise
  
  QTime _chronometer; // used to count the number of frames rendered. 
  gml::Camera _camera; //The Camera associated
    
  int _axesIndexDPL; //indexe of the display list containing the axes.


  //Public Methods
  public:
  AbsCanvas(QWidget* parent = 0, const char* name = 0);
  virtual ~AbsCanvas();

  //Protected Methods
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
