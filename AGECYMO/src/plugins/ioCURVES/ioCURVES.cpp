#include <cstdlib>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Qt stuff
#include <qapplication.h>
#include <qfiledialog.h>
#include <qmessagebox.h>

//Our stuff
#include "mainwindow.hpp"
//#include "plugin.hpp"
#include "point.hpp"
#include "face.hpp"
#include "tria.hpp"
#include "quad.hpp"
#include "absface.hpp"
#include "faces.hpp"
#include "canvas2d.hpp"
#include "abscurve.hpp"

using namespace std;
using namespace gml;

//Tokens for VRML load and save
const char* L_SBRACKET            = "[";
const char* R_SBRACKET            = "]";
const char* SPACE                 = " ";
const char* COMA                  = ",";

/***************************************************************
 *  Fonction query for curves
 * 
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
void** query(void){
  
  void** parameters = new void*[5];

  //Plugin's type
  PluginType* type = new PluginType(LOAD_AND_SAVE);

  //Plugin's name
  std::string *name = new string("ioCURVES");

  //Total number of entries in the different components 
  unsigned short *nbEntries = new unsigned short(2);

  //Load action 
  MenuAddOn *menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_CALL;
  menuLoadAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuLoadAdd->emplacement->append("/&File/Load Curves");
  menuLoadAdd->image = new string("up.png");
  menuLoadAdd->texte = new string("CTRL+M");
  

  //Save Action 
  MenuAddOn *menuSaveAdd = new MenuAddOn();
  menuSaveAdd->typeAppel = SAVE_CALL;
  menuSaveAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuSaveAdd->emplacement->append("/&File/Save Curves");
  menuSaveAdd->image = new string("down.png");
  menuSaveAdd->texte = new string("CTRL+P");

  qDebug("INSIDE PLUGIN : Query IOCURVES type  = %d", *type);
  
  
  parameters[0] = type;
  parameters[1] = name;
  parameters[2] = nbEntries;
  parameters[3] = menuLoadAdd;
  parameters[4] = menuSaveAdd;

  return parameters;
}



/***************************************************************
 *  Fonction load for curves
 * 
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
int load(MainWindow *mainW){

  return EXIT_SUCCESS;
}


/***************************************************************
 *  Fonction save for curves
 * 
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *
 ***************************************************************/
extern "C"
int save(MainWindow *mainWin){

  AbsCurve *figure;
  gml::Point3D point;

  //user chooses a name for wrl file
  QString fileName = QFileDialog::getSaveFileName(
    ".",
    "*.wrl",
    mainWin,
    "VRML save dialog box",
    "choose a name for VRML save" );

  //if no name defined exit
  if(fileName.isEmpty()){
    return EXIT_FAILURE;
  }

  //opening file for writing
  ofstream file(fileName.latin1());


  /************ chemin canvas **********************/
  
  figure = (mainWin->getCheminCanvas()).getFigure();
  if(figure != NULL){
    if((mainWin->getCheminCanvas()).getToolMode() == CIRCLE_MODE){
      file<<CIRCLE_MODE<<SPACE;
    }
    else if((mainWin->getCheminCanvas()).getToolMode() == NURBS_MODE){
      file<<NURBS_MODE<<SPACE;
    }
    else if((mainWin->getCheminCanvas()).getToolMode() == REC_MODE){
      file<<REC_MODE<<SPACE;
    }
    else{
      file<<POLY_MODE<<SPACE;
    }
  }
  else{
    file<<NO_TOOL_MODE<<SPACE;
  }
  
  if(figure != NULL){
    for(int i = 0; i<figure->getNbPoints(); i++){
      point = figure->getPoint(i);
      file<<point[0]<<SPACE<<point[1]<<SPACE;
    }
  }
  file<<COMA<<endl;



  /************ section canvas **********************/
  figure = (mainWin->getSectionCanvas()).getFigure();
  if(figure != NULL){
    if((mainWin->getSectionCanvas()).getToolMode() == CIRCLE_MODE){
      file<<CIRCLE_MODE<<SPACE;
    }
    else if((mainWin->getSectionCanvas()).getToolMode() == NURBS_MODE){
      file<<NURBS_MODE<<SPACE;
    }
    else if((mainWin->getSectionCanvas()).getToolMode() == REC_MODE){
      file<<REC_MODE<<SPACE;
    }
    else{
      file<<POLY_MODE<<SPACE;
    }
  }
  else{
    file<<NO_TOOL_MODE<<SPACE;
  }
  
  if(figure != NULL){
    for(int i = 0; i<figure->getNbPoints(); i++){
      point = figure->getPoint(i);
      file<<point[0]<<SPACE<<point[1]<<SPACE;
    }
  }
  file<<COMA<<endl;



  /************ profil canvas **********************/
  figure = (mainWin->getProfilCanvas()).getFigure();
  if(figure != NULL){
    if((mainWin->getProfilCanvas()).getToolMode() == CIRCLE_MODE){
      file<<CIRCLE_MODE<<SPACE;
    }
    else if((mainWin->getProfilCanvas()).getToolMode() == NURBS_MODE){
      file<<NURBS_MODE<<SPACE;
    }
    else if((mainWin->getProfilCanvas()).getToolMode() == REC_MODE){
      file<<REC_MODE<<SPACE;
    }
    else{
      file<<POLY_MODE<<SPACE;
    }
  }
  else{
    file<<NO_TOOL_MODE<<SPACE;
  }
  
  if(figure != NULL){
    for(int i = 0; i<figure->getNbPoints(); i++){
      point = figure->getPoint(i);
      file<<point[0]<<SPACE<<point[1]<<SPACE;
    }
  }
  file<<COMA<<endl;

  
  //file closing
  file.close();

  return EXIT_SUCCESS;
}
