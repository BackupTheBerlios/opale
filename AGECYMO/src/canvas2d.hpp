#ifndef CLASS_CANVAS2D_H
#define CLASS_CANVAS2D_H

#include "abscanvas.hpp"
#include "polyline.hpp"

const int squareNumber = 50;
const double glOrthoParameter = 4.0;
const QString sectionS("section");
const QString cheminS("chemin");
const QString profilS("profil");
const QString window3dS("window3D");

class Canvas2D : public AbsCanvas
{
  public:
  Canvas2D(QWidget* parent = 0, const char* name = 0);


  private:
  
  Polyline _polyline;
  Polyline _symetrique;

  void buildAxesDPL();
  void drawAxes();
  void sectionClickEvent(QMouseEvent* event);
  void profilClickEvent(QMouseEvent* event);
  void cheminClickEvent(QMouseEvent* event);
  void window3dClickEvent(QMouseEvent* event);
  void sectionMoveEvent(QMouseEvent* event);
  void profilMoveEvent(QMouseEvent* event);
  void cheminMoveEvent(QMouseEvent* event);
  void window3dMoveEvent(QMouseEvent* event);
  void sectionReleaseEvent(QMouseEvent* event);
  void profilReleaseEvent(QMouseEvent* event);
  void cheminReleaseEvent(QMouseEvent* event);
  void window3dReleaseEvent(QMouseEvent* event);
  void sectionDoubleClickEvent(QMouseEvent* event);
  void profilDoubleClickEvent(QMouseEvent* event);
  void cheminDoubleClickEvent(QMouseEvent* event);
  void window3dDoubleClickEvent(QMouseEvent* event);
    
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
