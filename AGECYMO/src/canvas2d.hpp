#ifndef CLASS_CANVAS2D_H
#define CLASS_CANVAS2D_H

#include "abscanvas.hpp"
#include "point.hpp"
#include <qdict.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qiconset.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>


const int squareNumber = 50;
const double glOrthoParameter = 1.0;
const QString sectionS("Section");
const QString cheminS("Chemin");
const QString profilS("Profil");
const QString window3dS("window3D");
const int SQUARE_NUMBER_DEFAULT = 50;

const unsigned short SECTION_CANVAS = 1;
const unsigned short PROFIL_CANVAS = 2;
const unsigned short CHEMIN_CANVAS = 0;
const unsigned short W3D_CANVAS = 3;

const unsigned short POLY_MODE = 1;
const unsigned short CIRCLE_MODE = 2;
const unsigned short REC_MODE = 3;
const unsigned short NURBS_MODE = 4;
const unsigned short NO_TOOL_MODE = 0;

class AbsCurve;

class Canvas2D : public AbsCanvas
{
  Q_OBJECT

  public:
  Canvas2D(QWidget* parent = 0, const char* name = 0);
  AbsCurve *getFigure();
  unsigned short getToolMode();
  unsigned short getCanvasType();
  void setFigure(AbsCurve *figure);

  private:
  
  int _squareNumber;
  AbsCurve *_figure;
  unsigned short _toolMode;
  unsigned short _canvasType;
  QPopupMenu *_fileMenu;
  

  void buildAxesDPL();
  void drawAxes();
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

  void calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point);

  public slots:

  void setPolyMode();
  void setCircleMode();
  void setRecMode();
  void setNurbsMode();
  void deleteAllPoints();
  void deleteSelectedPoints();
  void selectAllPoints();
  void deselectAllPoints();

};



#endif
