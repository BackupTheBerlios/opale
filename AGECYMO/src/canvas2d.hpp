#ifndef CLASS_CANVAS2D_H
#define CLASS_CANVAS2D_H

#include "abscanvas.hpp"

class Canvas2D : public AbsCanvas
{
  public:
  Canvas2D(QWidget* parent = 0, const char* name = 0);


  private:
  
  void buildAxesDPL();
  void drawAxes();

    
  protected:
  virtual void initializeGL     ();
  virtual void paintGL          ();
  virtual void resizeGL         (int, int);  
  virtual void mousePressEvent  (QMouseEvent*);
  virtual void mouseMoveEvent   (QMouseEvent*);
  virtual void mouseReleaseEvent(QMouseEvent*);

  

};



#endif
