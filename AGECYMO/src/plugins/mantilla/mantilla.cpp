/**************************************************************
 *
 *  plugin in order to check the validity of the current
 *  model with an Epsilon précision. Epsilon can be manualy set
 *  by user.
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

//#include "point.hpp"
//#include "face.hpp"
//#include "tria.hpp"
//#include "quad.hpp"
//#include "absface.hpp"
//#include "faces.hpp"

#include "precision.hpp"

using namespace std;
using namespace gml;

extern "C"
void** query(void){
  
  void** parameters = new void*[5];

  //Plugin's type
  PluginType* type = new PluginType(LOAD_AND_SAVE);

  //Plugin's name
  std::string *name = new string("mantilla");

  //Total number of entries in the different components 
  unsigned short *nbEntries = new unsigned short(2);

  //get Epsilon action 
  MenuAddOn *menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_CALL;
  menuLoadAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuLoadAdd->emplacement->append("/&Tools/set mantilla Epsilon");
  menuLoadAdd->image = new string("epsilon.png");
  menuLoadAdd->texte = new string("CTRL+E");
  

  //Validity calcul action 
  MenuAddOn *menuSaveAdd = new MenuAddOn();
  menuSaveAdd->typeAppel = SAVE_CALL;
  menuSaveAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuSaveAdd->emplacement->append("/&Tools/mantilla validity");
  menuSaveAdd->image = new string("validity.png");
  menuSaveAdd->texte = new string("CTRL+V");

  qDebug("INSIDE PLUGIN : Query mantilla type  = %d", *type);
  
  parameters[0] = type;
  parameters[1] = name;
  parameters[2] = nbEntries;
  parameters[3] = menuLoadAdd;
  parameters[4] = menuSaveAdd;

  return parameters;
}

/***************************************************************
 *  Fonction load
 *  Use in order to get Epsilon for the validity calcul 
 *
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
int load(MainWindow *mainW){
  
  QString message("Set Epsilon for validity calcul");
  mainW->getEventsWindow().writeComments( message);

  //here we get the epsilon value with a popup
  bool ok;
  double res = QInputDialog::getDouble("Mantilla validity", 
				       "Enter Epsilon [0,1]",
				       Precision::getInstance()
				       ->getEpsilon()
				       , 0,
				       1, 2, &ok, NULL );

  //user has entered a correct value and pressed OK
  if ( ok ) {

    //here we set the epsilon in the precision class
    Precision::getInstance()->setEpsilon(res);

    message = "Epsilon value set";
    mainW->getEventsWindow().writeComments( message);
  }
  
  return EXIT_SUCCESS;
}


/***************************************************************
 *  Fonction save
 * 
 *  Use in order to launch the validity calcul and display results
 *
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
int save(MainWindow *mainWin){

  QString message("Mantilla validity calcul launched on current model...");
  mainWin->getEventsWindow().writeComments( message );

  //here starts the validity calcul
  validateModel(mainWin->model());
  //here ends the validity calcul 

  message = "Validity calcul over";
  mainWin->getEventsWindow().writeComments( message );

  return EXIT_SUCCESS;
}
