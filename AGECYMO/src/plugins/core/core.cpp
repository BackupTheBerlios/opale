/**************************************************************
 *
 *  plugin in order to check the validity of the current
 *  model with the Core library.
 *
 *************************************************************/
#include <cstdlib>
#include <stdlib.h>
#include <vector>

//Qt stuff
#include <qapplication.h>
#include <qinputdialog.h>
#include <qstring.h>

//Our stuff
#include "mainwindow.hpp"
// #include "point.hpp"
// #include "face.hpp"
// #include "tria.hpp"
// #include "quad.hpp"
// #include "absface.hpp"
// #include "faces.hpp"

#include "precision.hpp"

using namespace std;
using namespace gml;

extern "C"
void** query(void){
  
  void** parameters = new void*[5];

  //Plugin's type
  PluginType* type = new PluginType(LOAD_AND_SAVE);

  //Plugin's name
  std::string *name = new string("core");

  //Total number of entries in the different components 
  unsigned short *nbEntries = new unsigned short(1);

  //Validity calcul action 
  MenuAddOn *menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_CALL;
  menuLoadAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuLoadAdd->emplacement->append("/&Tools/core validity");
  menuLoadAdd->image = new string("coreValidity.png");
  menuLoadAdd->texte = new string("CTRL+I");

  qDebug("INSIDE PLUGIN : Query core type  = %d", *type);
  
  parameters[0] = type;
  parameters[1] = name;
  parameters[2] = nbEntries;
  parameters[3] = menuLoadAdd;

  return parameters;
}

/***************************************************************
 *  Fonction save
 *  no use...
 *
 *
 ***************************************************************/
extern "C"
int save(MainWindow *mainW){
  return EXIT_SUCCESS;
}

/***************************************************************
 *  Fonction load
 * 
 *  Use in order to launch the validity calcul and display results
 *
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
int load(MainWindow *mainWin){

  QString message("Core validity calcul launched on current model...");
  mainWin->getEventsWindow().writeComments( message );

  //here starts the validity calcul
  validateModel(mainWin->model());
  //here ends the validity calcul 

  message = "Core validity calcul over";
  mainWin->getEventsWindow().writeComments( message );

  return EXIT_SUCCESS;
}
