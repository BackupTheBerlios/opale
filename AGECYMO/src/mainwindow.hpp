#ifndef CLASS_MAINWINDOW
#define CLASS_MAINWINDOW

//qt stuff
#include <qdict.h>
#include <qstringlist.h>
#include <qkeysequence.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qmainwindow.h>
#include <qapplication.h>
#include <qsignalmapper.h>
#include <qiconset.h>
#include <qpixmap.h>
#include <qtoolbar.h>
#include <qstatusbar.h>
#include <qlabel.h>
#include <qtoolbutton.h>
#include <qmultilineedit.h>

//Our stuff
#include "matrix.hpp"
#include "abscurve.hpp"
#include "curves.hpp"
#include "eventswindow.hpp"
#include "pluginmanager.hpp"

#include "canvas2d.hpp"
#include "canvas3d.hpp"
#include "window3d.hpp"
#include "controlpanel.hpp"
#include "helpwindow.hpp"

class PluginManager;
class CylinderGenerator;
class Canvas2D;
class Canvas3D;
class Window3D;

const QString INPUT_COMPONENT_SEPARATOR = "/";
const QString FILE_KEY = "&File";
const QString HELP_KEY = "&Help";
const QString CYLINDER_KEY = "&Cylinder";
const QString MANUAL_DIR = "./manual/";
const QString MANUAL_INDEX= "index.html";
const QString IMAGES_DIR = "../images/";
const QString QUIT_IMAGE = "exit.png";
const QString CYLINDER_IMAGE = "cylinder.png";

/******************************************************
 *  derived from QMainWindow. principle window of the modeler
 *
 ******************************************************/
class MainWindow : public QMainWindow
{
  Q_OBJECT
  
private:
  
  const char* TITLE; /**the title*/
  
  int _screen_w; /**screen's width*/
  int _screen_h; /**screen's height*/
  
  Window3D* _w3d; /**the 3d window*/
  Window3D* _wChemin; /**the way window*/
  Window3D* _wSection; /**the section window*/
  Window3D* _wProfil; /**the profil window*/
  
  ControlPanel* _controlPanel; /**the control panel*/
  
  QDict<QPopupMenu> _menus; /**the popupMenuBar*/
  
  QTime   _chronometer; /**chrono for generation*/
  QLabel* _labelStatus; /**this is the label used for the status bar*/
  
  PluginManager*  _pluginManager; /**the plugin manager*/
  
  QToolBar*       _toolBar; /**the tool bar*/
  
  CylinderGenerator*  _cylGenerator; /**in order to generate the cylinder*/
  
  HelpWindow*          _helpFrame; /**the helpWindow*/
  
  EventsWindow* _comments; /**event window for log*/
  
public:

  /**************************************************************
   *
   *  MainWindow constructor
   *  @param screen_w the width of the screen
   *  @param screen_h the height of the screnn
   *  @param w_app the width of the window
   *  @param h_app the height of the window
   *  @param x_app the x position of the window
   *  @param y_app the y position of the window
   *
   *************************************************************/
  MainWindow( int screen_w,
              int screen_h,
              int w_app = 50,
              int h_app = 70,
              int x_app = 10,
              int y_app = 0,
              QWidget* parent = 0,
              const char* name = 0);
  
  /**************************************************************
   *
   *  MainWindow destructor
   *
   *************************************************************/
  ~MainWindow();
  
  /**************************************************************
   *  This is the main method which update the GUI
   *  according to the plugin's data
   *  @param pluginID the id of the plugin 
   *  @param type the type of the plugin
   *  @param infos plugin informations
   *
   *************************************************************/
  void updateGUIWithPluginData(const QString & pluginID,
                               PluginType type,
                               std::vector<MenuAddOn *> & infos);
  
  /**************************************************************
   *
   *  get the canvas3D
   *  @return the 3d canvas
   *
   *************************************************************/
  Canvas3D& getCanvas3D(); 

  /**************************************************************
   *
   *  get the wayCanvas
   *  @return the wayCanvas
   *
   *************************************************************/
  Canvas2D& getCheminCanvas();

  /**************************************************************
   *
   *  get the profilCanvas
   *  @return the profilCanvas
   *
   *************************************************************/
  Canvas2D& getProfilCanvas();

  /**************************************************************
   *
   *  get the sectionCanvas
   *  @return the sectionCanvas
   *
   *************************************************************/
  Canvas2D& getSectionCanvas();
  
  /**************************************************************
   *
   *  get the eventWindow
   *  @return the eventWindow
   *
   *************************************************************/
  EventsWindow& getEventsWindow();
  
  /**************************************************************
   *
   *  get the model
   *  @return the model (all faces)
   *
   *************************************************************/
  Faces& model();
  
  /**************************************************************
   *
   *  set the model
   *  @param faces the model
   *
   *************************************************************/
  void setModel(Faces & faces);
  
  /**************************************************************
   *
   *  display time indications
   *  @param operation the name of the operation
   *  @param timeInMilliSeconds the operation time
   *
   *************************************************************/
  void displayTimeStatus( const char* operation, int timeInMilliSeconds);
  
  
private:
  
  /**************************************************************
   *
   *  init the frames
   *  @param screen_height the height of the screen
   *  @param screen_width the width of the screen
   *  @param application_width the width of the application
   *
   *************************************************************/
  void initViewFrames(int screen_height, int frame_width, int application_width = 50);
  
  /**************************************************************
   *
   *  update the view frame
   *
   *************************************************************/
  void updateViewFramesPosition();
  
  /**************************************************************
   *
   *  add the static menu bars
   *
   *************************************************************/
  void addStaticMenuBarContent();
  
  /**************************************************************
   *
   *  adjust the section via a scale
   *  @param ptsSection the section's points
   *  @param scaleFactor the scale
   *
   *************************************************************/
  void adjustSection(std::vector<Point3D> & ptsSection, double scaleFactor);
  
  /**************************************************************
   *
   *  adjust the way via a scale
   *  @param ptsChemin the way's points
   *  @param scaleFactor the scale
   *
   *************************************************************/
  void adjustWay(std::vector<Point3D> & ptsChemin, double scaleFactor);
  
  
protected:

  /**************************************************************
   *
   *  manage moce events
   *  @param event the event
   *
   *************************************************************/
  virtual void moveEvent(QMoveEvent* event);
  
public slots:

/**************************************************************
 *
 *  display about window
 *
 *************************************************************/
void about();
  
  /**************************************************************
   *
   *  display manual window
   *
   *************************************************************/
  void manual();
  
  /**************************************************************
   *
   *  generate the cylinder
   *
   *************************************************************/
  void generateCylinder();
  

};

#endif
