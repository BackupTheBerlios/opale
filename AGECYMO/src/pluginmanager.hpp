#ifndef CLASS_PLUGINMANAGER
#define CLASS_PLUGINMANAGER

#include <dlfcn.h>
#include <string>
#include <qobject.h>
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

/******************************************************
 *  allow to manage plugins properties
 *
 ******************************************************/
class PluginHandler
{
  public:
  PluginType    type;   /**plugin's type*/
  HandleType    handler;/**handle type*/
  runFunction*  run; /**launch the action plugin */
  loadFunction* load;/**run the load function*/
  saveFunction* save;/**run the save function*/
};

/******************************************************
 *  allow to manage plugins
 *
 ******************************************************/
class PluginManager : public QObject
{
  Q_OBJECT
  
  //Public Attributes/Constants 
  public:
    
  // Type of components which may be pluged.
  static const char* MENUBAR_CMP; /**may be plugged*/
  static const char* TOOLBAR_CMP; /**may be plugged*/
    
  //Private Attributes
  private:
    
  static const char* QUERY_SYMBOL; /**query symbol*/
  static const char* RUN_SYMBOL; /**run symbol*/
    
  static const char* LOAD_SYMBOL; /**load symbol*/
  static const char* SAVE_SYMBOL; /**save symbol*/
    
  static const QString PLUGIN_EXT; /**plugin extension*/
  static const QString PLUGIN_DIR; /**plugins directory*/
    
  QDict< PluginHandler> _plugins; /**dictionnary for plugins*/
    
  MainWindow*  _mw; /**reference ti the MainWindow*/
    
  
  //Public Methods
  public:
    
  /**************************************************************
   *
   *  PluginManager constructor
   *  @param parent the parent canvas
   *
   *************************************************************/
  PluginManager(MainWindow* appli);
    
  /**************************************************************
   *
   *  PluginManager destructor
   *
   *************************************************************/
  ~PluginManager();

  /**************************************************************
   *
   *  record the plugins
   *
   *************************************************************/
  void recordAvailablePlugins();

  //void executePlugin(const QString & pluginFullName);
  
  
  //Private Methods
  private:
    
  /**************************************************************
   *
   *  load a plugin
   *  @param pluginFullName the full name of the plugin
   *
   *************************************************************/
  void loadPlugin(const QString &pluginFullName);
    
  /**************************************************************
   *
   *  unload a plugin
   *  @param pluginID the id of the plugin
   *
   *************************************************************/
  void unloadPlugin(QString const & pluginID);
    
  /**************************************************************
   *
   *  load an unload the plugin (at start=
   *  @param pluginFullName the full name of the plugin
   *
   *************************************************************/
  void loadAndUnloadPlugin(const QString & pluginFullName);
    
  /**************************************************************
   *
   *  reload a plugin
   *  @param pluginFullName the full name of the plugin
   *  @return the pluginHandler (plugin's properties)
   *
   *************************************************************/
  PluginHandler* reloadPlugin(const QString & pluginFullName);

  
  public slots:

  /**************************************************************
   *
   *  launch the plugin's run function
   *  @param pluginFullName the full name of the plugin
   *
   *************************************************************/
  void executeRun(const QString & pluginFullName);
    
  /**************************************************************
   *
   *  launch the plugin's load function
   *  @param pluginFullName the full name of the plugin
   *
   *************************************************************/
  void executeLoad(const QString & pluginFullName);
    
  /**************************************************************
   *
   *  launch the plugin's save function
   *  @param pluginFullName the full name of the plugin
   *
   *************************************************************/
  void executeSave(const QString & pluginFullName);

};


  
#endif
