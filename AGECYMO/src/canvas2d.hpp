#ifndef CLASS_CANVAS2D_H
#define CLASS_CANVAS2D_H

#include "abscanvas.hpp"
#include "polyline.hpp"
#include "point.hpp"

const int squareNumber = 50;
const double glOrthoParameter = 4.0;
const QString sectionS("Section");
const QString cheminS("Chemin");
const QString profilS("Profil");
const QString window3dS("window3D");
const int SQUARE_NUMBER_DEFAULT = 50;

class Canvas2D : public AbsCanvas
{
  public:
  Canvas2D(QWidget* parent = 0, const char* name = 0);


  private:
  
  int _squareNumber;
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
  void calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point);
  int getSquareNumber();
  void setSquareNumber(int newValue);

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
