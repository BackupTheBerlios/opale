#ifndef CLASS_CANVAS2D_H
#define CLASS_CANVAS2D_H

#include "abscanvas.hpp"
#include "point.hpp"
#include "mainwindow.hpp"
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
const unsigned short POLYG_MODE = 5;
const unsigned short CIRCLE_MODE = 2;
const unsigned short REC_MODE = 3;
const unsigned short NURBS_MODE = 4;
const unsigned short NO_TOOL_MODE = 0;

class Curves;
class MainWindow;

class Canvas2D : public AbsCanvas
{
  Q_OBJECT

  public:
  Canvas2D(MainWindow* mw, QWidget* parent = 0, const char* name = 0);
  Curves *getFigure();
  unsigned short getToolMode();
  unsigned short getCanvasType();
  void setFigure(Curves *figure);
  QPopupMenu *getPopupMenu();

  private:
  
  int _squareNumber;
  Curves *_figure;
  unsigned short _toolMode;
  unsigned short _canvasType;
  QPopupMenu *_fileMenu;
  

  MainWindow* _mw;

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

  MainWindow& getMW();

  void setPolyMode();
  void setPolygMode();
  void setCircleMode();
  void setRecMode();
  void setNurbsMode();
  void deleteAllPoints();
  void selectAllPoints();
  void deselectAllPoints();

};



#endif
