#ifndef CLASS_CANVAS2D_H
#define CLASS_CANVAS2D_H

#include "abscanvas.hpp"
#include "polyline.hpp"

const int squareNumber = 50;
const double glOrthoParameter = 4.0;


class Canvas2D : public AbsCanvas
{
  public:
  Canvas2D(QWidget* parent = 0, const char* name = 0);


  private:
  
  Polyline _polyline;
  void buildAxesDPL();
  void drawAxes();
    
  protected:
  virtual void initializeGL     ();
  virtual void paintGL          ();
  virtual void resizeGL         (int, int);  
  virtual void mousePressEvent  (QMouseEvent*);
  virtual void mouseMoveEvent   (QMouseEvent*);
  virtual void mouseReleaseEvent(QMouseEvent*);
  virtual void mouseDoubleClickEvent(QMouseEvent*);

  

};



#endif
