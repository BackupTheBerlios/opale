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
#include "point.hpp"
#include "face.hpp"
#include "tria.hpp"
#include "quad.hpp"
#include "absface.hpp"
#include "faces.hpp"

using namespace std;
using namespace gml;


const char* MESH_NAME = "mesh2";
const char* TAB       = "  ";
const char* L_BRACE   = "{";
const char* R_BRACE   = "}";
const char* LESS      = "<";
const char* MORE      = ">";
const char* VERTEX    = "vertex_vectors ";
const char* FACES     = "face_indices ";
const char* COMMA     = ",";
const char* PIGMENT   = "pigment";
const char* COLOR     = "Color";


extern "C"
void** query(void)
{
  void** parameters = new void*[5];

  //Plugin's type
  PluginType* type = new PluginType(LOAD_AND_SAVE);

  //Plugin's name
  std::string *name = new string("ioPOV");

  //Total number of entries in the different components 
  unsigned short *nbEntries = new unsigned short(2);

  
  //Load action 
  MenuAddOn *menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_CALL;
  menuLoadAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuLoadAdd->emplacement->append("/&File/Import/A POVRay Model");
  menuLoadAdd->image = NULL;
  menuLoadAdd->texte = NULL;

  //Save Export Action 
  MenuAddOn *menuSaveAdd = new MenuAddOn();
  menuSaveAdd->typeAppel = SAVE_CALL;
  menuSaveAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuSaveAdd->emplacement->append("/&File/Export To/POVRay Model");
  menuSaveAdd->image = NULL;
  menuSaveAdd->texte = NULL;

  qDebug("INSIDE PLUGIN : Query OBJ type  = %d", *type);
  
  
  parameters[0] = type;
  parameters[1] = name;
  parameters[2] = nbEntries;
  parameters[3] = menuLoadAdd;
  parameters[4] = menuSaveAdd;

  return parameters;
}


void
writeVertices( ostream & file,
               const std::vector<gml::Point3D> & points)
{
  std::cout << "Debuging" << std::endl;


  
  file << VERTEX << L_BRACE << std::endl
       << TAB << TAB
       << points.size() << COMMA << std::endl;


  
  for (unsigned int i=0; i<(points.size()-1); i++)
  {
    std::cout << points[i] << std::endl;
    
    file << LESS
         << points[i][0] << COMMA
         << points[i][1] << COMMA
         << points[i][2]
         << MORE << COMMA << std::endl;
  }

  file << LESS
       << points[points.size()-1][0] << COMMA
       << points[points.size()-1][1] << COMMA
       << points[points.size()-1][2]
       << MORE << std::endl;

  file << R_BRACE << std::endl;
}

void writeIndices( ostream & file, std::vector<int> & indices)
{

  file << LESS ;
  
  for (unsigned int j=0; j<(indices.size()-1) ;j++)
  {
    file << indices[j] << COMMA;
    
  }

  file << indices[indices.size()-1]
       << MORE;
  
}


void writeFaces( ostream & file,
                 const std::vector<AbsFace*> & faces)
{

  file << FACES << L_BRACE << std::endl
       << faces.size() << COMMA << std::endl;

  for (unsigned int i=0; i<(faces.size()-1); i++)
  {
    std::vector<int> indices = *(faces[i]->getIndexes());

    writeIndices(file, indices);
    
    file << COMMA << std::endl;
  }

  std::vector<int> indices = *(faces[faces.size()-1]->getIndexes());
  writeIndices(file, indices);

  file << std::endl
       << R_BRACE
       << std::endl;
}



extern "C"
int save(MainWindow *mainWin)
{
  qDebug("Dans Save du PLUGIN ioOBJ ");

  //we load faces to write in the file
  Faces *faces_to_write;
  faces_to_write = new Faces(mainWin->model());

  //list of indexes for faces load
  vector<int> *index_list;

  //user chooses a name for wrl file
  QString fileName = QFileDialog::getSaveFileName(
    ".",
    "*.pov",
    mainWin,
    "POV save dialog box",
    "choose a name" );

  //if no name defined we exit
  if(fileName.isEmpty())
  {
    return EXIT_FAILURE;
  }

  //opening file for writing
  ofstream file(fileName.latin1());
  
  std::vector<gml::Point3D> points;
  std::vector<AbsFace*> faces;
  AbsFace *workFace;

  //file control
  if(!file.is_open())
  {
    QMessageBox::information( mainWin, "Generalized cylinder",
                              "Unable to open file for save.\n");
    return EXIT_FAILURE;
  }


  file << MESH_NAME << L_BRACE
       << std::endl 
       << TAB;
  
  writeVertices( file, faces_to_write->points() );
  writeFaces( file, faces_to_write->faces() );

  file << TAB << PIGMENT << L_BRACE << "rgb 1" << R_BRACE << std::endl;
  
  file << R_BRACE << std::endl;
  
  
  
  //file closing
  file.close();

}

extern "C"
int load(MainWindow *mainWin)
{
  qDebug("Dans load du PLUGIN ioOBJ ");
  QMessageBox::information( mainWin, "NOT IMPLEMETED YET",
                            "Sorry this functionnality is not yet implemented .\n");
  
}
