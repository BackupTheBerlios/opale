#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <qapplication.h>
#include <fstream>
#include <string>
#include <vector>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "../../testVector.hpp"
#include "../../mainwindow.hpp"
#include "../../point.hpp"
#include "../../face.hpp"
#include "../../tria.hpp"
#include "../../quad.hpp"
#include "../../absface.hpp"
#include "../../faces.hpp"

//a inplémenter dans le module de chargement des plugins
enum PluginType{ LOAD_SAVE, ACTION };
enum EmplacementType{ACTION_ADD, LOAD_ADD, SAVE_ADD};
class MenuAddOn{
public:
  unsigned short typeAppel;
  std::string *emplacement;
  std::string *image;
  std::string *texte;
};

using namespace std;
using namespace gml;

//Tokens for VRML load and save
const char* L_BRACE               = "{";
const char* R_BRACE               = "}";
const char* L_SBRACKET            = "[";
const char* R_SBRACKET            = "]";
const char* HEADER                = "#VRML V2.0 utf8\n";
const char* GROUP_NODE            = "Group";
const char* CHILDREN_PARAMETER    = "children";
const char* SHAPE_NODE            = "Shape";
const char* APPEARANCE_PARAMETER  = "appearance";
const char* APPEARANCE_NODE       = "Appearance";
const char* MATERIAL_PARAMETER    = "material";
const char* MATERIAL_NODE         = "Material";
const char* GEOMETRY_PARAMETER    = "geometry";
const char* INDEXED_FACE_SET_NODE = "IndexedFaceSet";
const char* COORD_PARAMETER       = "coord";
const char* COORDINATE_NODE       = "Coordinate";
const char* POINT_PARAMETER       = "point";
const char* COORD_INDEX_PARAMETER = "coordIndex";
const char* SPACE                 = " ";


extern "C"
void **query(void){
  void ** parameters;
  
  *parameters = calloc(5,sizeof(void*));

  unsigned short *type;
  *type = LOAD_SAVE;
  std::string *name = new string("ioVRML");
  unsigned short *nbEntries;
  *nbEntries = 2;

  MenuAddOn *menuLoadAdd;
  menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_ADD;
  menuLoadAdd->emplacement = new string("Menu/file/loadVRML");
  menuLoadAdd->image = NULL;
  menuLoadAdd->texte = NULL;

  MenuAddOn *menuSaveAdd;
  menuSaveAdd = new MenuAddOn();
  menuSaveAdd->typeAppel = SAVE_ADD;
  menuSaveAdd->emplacement = new string("Menu/file/saveVRML");
  menuSaveAdd->image = NULL;
  menuSaveAdd->texte = NULL;

  parameters[0] = type;
  parameters[1] = name;
  parameters[2] = nbEntries;
  parameters[3] = menuLoadAdd;
  parameters[4] = menuSaveAdd;

  return parameters;
}

extern "C"
int load(MainWindow *mainWin){
  return EXIT_SUCCESS;
}


/***************************************************************
 *  Fonction save
 * 
 *  @param mainWin the principal window of the application
 *  @return 0 if success, -1 else.
 *
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 ***************************************************************/
extern "C"
int save(MainWindow *mainWin){
  //we load faces to write in the file
  Faces *faces_to_write;
  faces_to_write = new Faces(mainWin->model());

  //list of indexes for faces load
  vector<int> *index_list;

  //user chooses a name for wrl file
  QString fileName = QFileDialog::getSaveFileName(
                    ".",
                    "",
                    mainWin,
                    "VRML save dialog box",
                    "choose a name for VRML save" );

  //if no name defined exit
  if(fileName.isEmpty()){
    return EXIT_FAILURE;
  }

  //opening file for writing
  ofstream file(fileName.latin1());

  int cpt, nbFaces, nbPoints;
  std::vector<gml::Point3D> points;
  std::vector<AbsFace*> faces;
  AbsFace *workFace;

  //file control
  if(!file.is_open()){
    QMessageBox::information( mainWin, "Generalized cylinder",
    "Unable to open file for save.\n");
    return EXIT_FAILURE;
  }

  //points and faces load
  points = faces_to_write->points();
  faces = faces_to_write->faces();
  nbPoints = points.size();
  nbFaces = faces.size();

  //header writing
  file<<HEADER<<endl;

  //architecture writing
  file<<endl<<GROUP_NODE<<SPACE<<L_BRACE<<endl
      <<CHILDREN_PARAMETER<<SPACE<<L_SBRACKET<<endl
      <<SHAPE_NODE<<SPACE<<L_BRACE<<endl
      <<APPEARANCE_PARAMETER<<SPACE<<APPEARANCE_NODE<<SPACE<<L_BRACE<<endl
      <<MATERIAL_PARAMETER<<SPACE<<MATERIAL_NODE<<L_BRACE<<endl
      <<R_BRACE<<endl
      <<R_BRACE<<endl
      <<GEOMETRY_PARAMETER<<SPACE<<INDEXED_FACE_SET_NODE<<SPACE<<L_BRACE<<endl
      <<COORD_PARAMETER<<SPACE<<COORDINATE_NODE<<SPACE<<L_BRACE<<endl
      <<POINT_PARAMETER<<L_SBRACKET;

  //we write the points
  for(cpt = 0; cpt<nbPoints; cpt++){
    if(cpt != 0){
      file<<", ";
    }
    file<<points[cpt][0]<<SPACE<<points[cpt][1]<<SPACE<<points[cpt][2];
  }
  file<<R_SBRACKET<<endl<<R_BRACE<<endl;


  //we write the faces (indexes) 
  file<<endl<<COORD_INDEX_PARAMETER<<SPACE<<L_SBRACKET;
  for(cpt = 0; cpt<nbFaces; cpt++){
    if(cpt!=0){
      file<<", ";
    }
    workFace = faces[cpt];
    index_list = workFace->getIndexes();
    for(unsigned int i = 0; i<index_list->size(); i++){
      file<<(*index_list)[i]<<SPACE;
    }
    file<<"-1";
  }

  //braces closing
  file<<R_SBRACKET<<endl
      <<R_BRACE<<endl<<R_BRACE<<endl
      <<R_SBRACKET<<endl
      <<R_BRACE<<endl;

  //file closing
  file.close();
  delete faces_to_write;

  return EXIT_SUCCESS;
}
