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


extern "C"
void** query(void)
{
  void** parameters = new void*[5];

  //Plugin's type
  PluginType* type = new PluginType(LOAD_AND_SAVE);

  //Plugin's name
  std::string *name = new string("ioOBJ");

  //Total number of entries in the different components 
  unsigned short *nbEntries = new unsigned short(2);

  //Load action 
  MenuAddOn *menuLoadAdd = new MenuAddOn();
  menuLoadAdd->typeAppel = LOAD_CALL;
  menuLoadAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuLoadAdd->emplacement->append("/&File/Import/An OBJ Model");
  menuLoadAdd->image = NULL;
  menuLoadAdd->texte = NULL;
  

  //Save Action 
  MenuAddOn *menuSaveAdd = new MenuAddOn();
  menuSaveAdd->typeAppel = SAVE_CALL;
  menuSaveAdd->emplacement = new string(PluginManager::MENUBAR_CMP);
  menuSaveAdd->emplacement->append("/&File/Export To/An OBJ Model");
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


extern "C"
int load(MainWindow *mainWin)
{
  qDebug("Dans load du PLUGIN ioOBJ ");
  QMessageBox::information( mainWin, "NOT IMPLEMETED YET",
                            "Sorry this functionnality is not yet implemented .\n");
  return EXIT_FAILURE;
}


void
writeVertices( ostream & file,
               const std::vector<gml::Point3D> & points)
{

  for (unsigned int i=0; i<(points.size()-1); i++)
  {
    file << "v "
         << points[i][0] << " "
         << points[i][1] << " "
         << points[i][2] << " " << std::endl;
  }
  

}

void
writeNormals( ostream &file,
              const std::vector<gml::Vector3D> & normals)
{

  for (unsigned int i=0; i<(normals.size()-1); i++)
  {
    file << "vn "
         << normals[i][0] << " "
         << normals[i][1] << " "
         << normals[i][2] << " " << std::endl;
  }
}

void
writeFaces( ostream & file,
            const std::vector<AbsFace*> & faces)
{

  for (unsigned int i=0; i<(faces.size()-1); i++)
  {
    std::vector<int> indices = *(faces[i]->getIndexes());

    file << "f " ;
    
    for (unsigned int j=0; j<(indices.size()-1) ;j++)
    {
      file << (indices[j]+1) << " ";
    }

    file << std::endl;
  }


}

extern "C"
int save(MainWindow *mainWin)
{
  qDebug("Dans save du PLUGIN ioOBJ ");

  //QMessageBox::information( mainWin, "NOT IMPLEMETED YET",
  //                          "Sorry this functionnality is not yet implemented .\n");

  //user chooses a name for wrl file
  QString fileName = QFileDialog::getSaveFileName(
    ".",
    "*.obj",
    mainWin,
    "OBJ save dialog box",
    "choose a name" );

  //if no name defined we exit
  if(fileName.isEmpty())
  {
    return EXIT_FAILURE;
  }
  //opening file for writing
  ofstream file(fileName.latin1());

  //file control
  if(!file.is_open())
  {
    QMessageBox::information( mainWin, "Generalized cylinder",
                              "Unable to open file for save.\n");
    return EXIT_FAILURE;
  }

  //we retrieve the faces to be written in the file
  Faces *faces_to_write;
  faces_to_write = new Faces(mainWin->model());


  file << "# AGECYMO OBJ Exporter " << std::endl;
  
  std::vector<gml::Point3D> points;
  std::vector<AbsFace*> faces;
    
  writeVertices( file, faces_to_write->points() );

  writeFaces( file, faces_to_write->faces() );


  
  return EXIT_SUCCESS;
}
