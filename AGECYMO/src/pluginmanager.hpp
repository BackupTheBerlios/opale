#ifndef CLASS_PLUGINMANAGER
#define CLASS_PLUGINMANAGER

#include <dlfcn.h>

#include <string>

#include <qmap.h>
#include <qpair.h>
#include <qdict.h>

#include <qstring.h>
#include <qstringlist.h>


#include <qdir.h>
#include <qfileinfo.h>

#include "plugin.hpp"

class MainWindow;

typedef void** (*queryFunction) (void);
typedef int    (*runFunction) (void**);
  
typedef void   (*loadFunction) (MainWindow *);
typedef void   (*saveFunction) (MainWindow *);
  
typedef void*  HandleType;

class PluginHandler
{
  public:
  PluginType    type;
  HandleType    handler;
  runFunction*  run;
  loadFunction* load;
  saveFunction* save;
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
    
  static const char* QUERY_SYMBOL;
  static const char* RUN_SYMBOL;
    
  static const char* LOAD_SYMBOL;
  static const char* SAVE_SYMBOL;
    
  static const QString PLUGIN_EXT;
  static const QString PLUGIN_DIR;
    
  QDict< PluginHandler> _plugins;
    
  MainWindow*  _mw;
    
  
  //Public Methods
  public:
    
  PluginManager(MainWindow* appli);
    
  ~PluginManager();

  void recordAvailablePlugins();
  
    
  // public slots:
  void executePlugin(const QString & pluginFullName);
    
  void executeRun(const QString & pluginFullName);
    
  void executeLoad(const QString & pluginFullName);
    
  void executeSave(const QString & pluginFullName);
  
  
  //Private Methods
  private:
    
  void loadPlugin(const QString &pluginFullName);
    
  void unloadPlugin(QString const & pluginID);
    
  void loadAndUnloadPlugin(const QString & pluginFullName);
    
  PluginHandler* reloadPlugin(const QString & pluginFullName);
    
};


  
#endif
