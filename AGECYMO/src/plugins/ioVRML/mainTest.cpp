/*****************testSavePlugin***************************/

int
main(int argc, char **argv)
{
  //creation de deux faces (un triangle et un quad)
  std::vector<gml::Point3D> points;
  std::vector<AbsFace*> *faces_list;
  faces_list = new std::vector<AbsFace*>();
  AbsFace *triangle;
  AbsFace *quad;

  gml::Point3D p0;
  gml::Point3D p1;
  gml::Point3D p2;
  gml::Point3D p3;
  gml::Point3D p4;
  gml::Point3D p5;

  p0[0] = 0.0;
  p0[1] = 5.0;
  p0[2] = 0.0;
  p1[0] = -5.0;
  p1[1] = 0.0;
  p1[2] = 0.0;
  p2[0] = 5.0;
  p2[1] = 0.0;
  p2[2] = 0.0;
  p3[0] = 0.0;
  p3[1] = 5.0;
  p3[2] = 8.0;
  p4[0] = 0.0;
  p4[1] = 0.0;
  p4[2] = 8.0;
  p5[0] = 0.0;
  p5[1] = 0.0;
  p5[2] = 0.0;

  points.push_back(p0);
  points.push_back(p1);
  points.push_back(p2);
  points.push_back(p3);
  points.push_back(p4);
  points.push_back(p5);

  //création de la géométrie
  //triangle  
  triangle = new Tria(&points,0,1,2);
  //quad
  quad = new Quad(&points,0,3,4,5);

  faces_list->push_back(triangle);
  faces_list->push_back(quad);


  //création de l'objet Faces
  Faces *faces_to_write = new Faces(points,faces_list);

  //ajout des faces à la MainWindow
  mainWindow.setModel(*faces_to_write);

  if(save(&mainWindow)==-1){
    exit(-1);
  }

  delete faces_list; 
  delete triangle;
  delete quad;
  delete faces_to_write;

}
