#ifndef CLASS_PLUGINMANAGER
#define CLASS_PLUGINMANAGER

#include <dlfcn.h>

#include <string>

#include <qmap.h>
#include <qpair.h>

#include <qstring.h>
#include <qstringlist.h>


#include <qdir.h>
#include <qfileinfo.h>

#include "mainwindow.hpp"

class MainWindow;


// Plugin types definition
enum PluginType{ LOAD_AND_SAVE, ACTION }; //What's the type of the plugin ?

enum CallType{ACTION_CALL, LOAD_CALL, SAVE_CALL}; 

class MenuAddOn{
public:
  CallType typeAppel;
  std::string *emplacement;
  std::string *image; //
  std::string *texte;
};


//Plugins manager for AGECYMO
class PluginManager
{

  //Public Attributes/Constants 
  public:

  // Type of components which may be pluged.
  static const char* MENUBAR_CMP;
  static const char* TOOLBAR_CMP;
  
  //Private Attributes
  private:

  typedef void** (*queryFunction) (void);
  typedef int    (*runFunction) (void**);

  typedef void*  HandleType;

  
  static const char*   QUERY_SYMBOL;
  static const char*   RUN_SYMBOL;
  
  static const QString PLUGIN_EXT;
  static const QString PLUGIN_DIR;
  
  QMap< QString,  QPair<bool, HandleType> > _plugins;
  
  MainWindow*  _mw;

  
  //Public Methods
  public:

  PluginManager(MainWindow* appli);

  ~PluginManager();


  
  void readAvailablePlugins();

  // public slots:
  void executePlugin(const QString & pluginFullName);


  void executeRun(const QString & pluginFullName);

  void executeLoad(const QString & pluginFullName);

  void executeSave(const QString & pluginFullName);
  
  
  //Private Methods
  private:

  void loadPlugin(const QString &pluginFullName);
  void unloadPlugin(HandleType handler);
  
  void loadAndUnloadPlugin(const QString & pluginFullName);


  void addMenuBarEntry();

  void addToolBarEntry();
  
  
};



#endif
