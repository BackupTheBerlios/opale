#ifndef CLASS_CANVAS2D_H
#define CLASS_CANVAS2D_H

#include <qstring.h>
#include <qdict.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qiconset.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>

#include "abscanvas.hpp"
#include "point.hpp"
#include "mainwindow.hpp"

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

/******************************************************
 *  derived class from AbsCanvas. manage a 2D widget
 *
 ******************************************************/
class Canvas2D : public AbsCanvas
{
  Q_OBJECT

  public:
  /**************************************************************
   *
   *  constructor 
   *  @param MainWindow the mainWindow
   *  @param parent the parent widget
   *  @return name the name of the canvas
   *
   *************************************************************/
  Canvas2D(MainWindow* mw, QWidget* parent = 0, const char* name = 0);
  
  /**************************************************************
   *
   *  get the curves
   *  @return the curves
   *
   *************************************************************/
  Curves *getFigure();

  /**************************************************************
   *
   *  get the selected toolMode
   *  @return the toolMode
   *
   *************************************************************/
  unsigned short getToolMode();

  /**************************************************************
   *
   *  get the type of this canvas
   *  @return the canvas type
   *
   *************************************************************/
  unsigned short getCanvasType();

  /**************************************************************
   *
   *  set the curves
   *  @param the curves to set
   *
   *************************************************************/
  void setFigure(Curves *figure);

  /**************************************************************
   *
   *  get the popupMenu for manage tools
   *  @return the tools popupMenu
   *
   *************************************************************/
  QPopupMenu *getPopupMenu();

  private:
  
  int _squareNumber; /**the grid square number*/
  Curves *_figure; /**the contained curves*/
  unsigned short _toolMode; /**the toolMode selected*/
  unsigned short _canvasType; /**the type of this canvas*/
  QPopupMenu *_fileMenu; /**the fileMenu for tools*/
  MainWindow* _mw; /** a reference to the mainWondow*/

  /**************************************************************
   *
   *  build principal axes
   *
   *************************************************************/
  void buildAxesDPL(); 

  /**************************************************************
   *
   *  draw axes in an openGL context
   *
   *************************************************************/
  void drawAxes(); 
  
  /**************************************************************
   *
   *  get the number of square (grid resolution)
   *  @return the square number
   *
   *************************************************************/
  int getSquareNumber();

  /**************************************************************
   *
   *  set the number of square (grid resolution)
   *  @param newValue the new square number
   *
   *************************************************************/
  void setSquareNumber(int newValue);

  protected:

  /**************************************************************
   *
   *  initialise the openGL context
   *
   *************************************************************/
  virtual void initializeGL     ();

  /**************************************************************
   *
   *  paint canvas curves in openGL context
   *
   *************************************************************/
  virtual void paintGL          ();

  /**************************************************************
   *
   *  resize the canvas
   *  @param x the height
   *  @param y the width
   *
   *************************************************************/
  virtual void resizeGL         (int x, int y);  

  /**************************************************************
   *
   *  manage mouse press event
   *  @param event the event
   *
   *************************************************************/
  virtual void mousePressEvent  (QMouseEvent* event);

  /**************************************************************
   *
   *  manage mouse move event
   *  @param event the event
   *
   *************************************************************/
  virtual void mouseMoveEvent   (QMouseEvent* event);

  /**************************************************************
   *
   *  manage mouse release event
   *  @param event the event
   *
   *************************************************************/
  virtual void mouseReleaseEvent(QMouseEvent* event);

  /**************************************************************
   *
   *  manage moude double click event
   *  @param event the event
   *
   *************************************************************/
  virtual void mouseDoubleClickEvent(QMouseEvent*);

  /**************************************************************
   *
   *  translate to OpenGl coordinates from QT coordinates
   *  @param event the event (contains position of click)
   *  @param point the point to initialise
   *
   *************************************************************/
  void calculateQtToOpenGL(QMouseEvent* event, gml::Point3D *point);

  public slots:

  /**************************************************************
   *
   *  get the mainWindow
   *  @return the mainwindow
   *
   *************************************************************/
  MainWindow& getMW();

  /**************************************************************
   *
   *  set toolMode to polylin mode
   *
   *************************************************************/
  void setPolyMode();

  /**************************************************************
   *
   *  set toolMode to polygone mode
   *
   *************************************************************/
  void setPolygMode();

  /**************************************************************
   *
   *  set toolMode ti circle mode
   *
   *************************************************************/
  void setCircleMode();

  /**************************************************************
   *
   *  set toolMode to rectangle mode
   *
   *************************************************************/
  void setRecMode();

  /**************************************************************
   *
   *  set toolMode to nubs mode
   *
   *************************************************************/
  void setNurbsMode();

  /**************************************************************
   *
   *  delete all the points (here mean all the curves too)
   *
   *************************************************************/
  void deleteAllPoints();

  /**************************************************************
   *
   *  select all the points
   *
   *************************************************************/
  void selectAllPoints();

  /**************************************************************
   *
   *  deselect all the points
   *
   *************************************************************/
  void deselectAllPoints();

};



#endif
