#include "mainwindow.hpp"


MainWindow::MainWindow(int screen_w,
                       int screen_h,
                       int w_app,
                       int h_app,
                       int x_app,
                       int y_app,
                       QWidget* parent,
                       const char* name)
    : QMainWindow(parent, name),
      TITLE("Another Modeler"),
      _screen_w(screen_w),
      _screen_h(screen_h)
{
  _labelStatus = NULL;

  _controlPanel = new ControlPanel(this);

  setCentralWidget(_controlPanel);
  
    
  _pluginManager = new PluginManager(this);

  _toolBar = new QToolBar("Operations", this);
  _toolBar->setHorizontallyStretchable(true);
  _toolBar->setVerticallyStretchable(true);
  _toolBar->setResizeEnabled(true);
  
  resize(w_app, h_app);
  move(0, 0);
  setCaption(TITLE);

  
  show();

  initViewFrames(800, screen_w, w_app);


  
  //Tell the plugin manager to load and unload the available plugins
  //Plugins will be loaded on demand
  _pluginManager->recordAvailablePlugins();

  addStaticMenuBarContent();
  moveDockWindow(_toolBar, Qt::DockLeft);

  
}

MainWindow::~MainWindow()
{
  delete _wSection;
  delete _wProfil;
  delete _wChemin;
  delete _w3d;
  delete _pluginManager;

  
  if ( _labelStatus != NULL)
  {
    delete _labelStatus;
  }
  
}

void
MainWindow::updateGUIWithPluginData(const QString & pluginID,
                                    PluginType type,
                                    std::vector<MenuAddOn *> & infos)
{

  std::cout << "Dans updateGUIWithPluginData "<< std::endl
            << "taille d infos transmis " << infos.size() << std::endl;

  const int nbArgs = infos.size();

  //TODO : use Iterator instead of direct access
  for(int i=0; i<nbArgs; i++)
  {

    //First we retrieve the MenuAddOn
    MenuAddOn* infoMenu = infos[i];
    
    QString emplacement(infoMenu->emplacement->c_str());
    qDebug("emplacement = %s ", emplacement.latin1());

    // We split the string to learn where the plugin wants
    // to be connected with the GUI components
    QStringList decomposition = QStringList::split(INPUT_COMPONENT_SEPARATOR, emplacement);
    
    QString component = decomposition[0];
    qDebug("Compoment = %s ", component.latin1());


    //Which component ?
    //TODO: To IMPROVE the test
    if (component == "Menu")
    {
      QPopupMenu* aMenu;

      for(int j=1; j<decomposition.size()-1; j++)
      {
        aMenu = _menus.find(decomposition[j]);
        //Do we already have built this menu
        if(!aMenu)
        {

          QPopupMenu * aMenu = new QPopupMenu( this );
          _menus.insert(decomposition[j], aMenu);
          if (j == 1)
          {
            menuBar()->insertItem( decomposition[j], _menus[decomposition[j]]);
          }
          else
          {
            QPopupMenu* previousMenu = _menus.find(decomposition[j-1]);
            previousMenu->insertItem( decomposition[j], aMenu);
          }
        }
      }
      
      QAction* aAction = new QAction(this);
      aAction->setText    ( decomposition[decomposition.size() -1] );
      aAction->setMenuText( decomposition[decomposition.size() -1] );

      if( infoMenu->texte != NULL )
      {
        aAction->setAccel( QKeySequence( QString(infoMenu->texte->c_str()) ) );
      }
 
      if( infoMenu->image != NULL )
      {
        aAction->setIconSet( QIconSet(
                               QPixmap
                               (
                                 QString(IMAGES_DIR).append(infoMenu->image->c_str())
                                 ) ) );

        aAction->addTo( _toolBar);
      }
      
      QSignalMapper* _signalMapper = new QSignalMapper(this);
      _signalMapper->setMapping(aAction, pluginID);
      
      connect( aAction, SIGNAL(activated() ),
               _signalMapper, SLOT(map()) );


      switch(infoMenu->typeAppel)
      {
        case LOAD_CALL:
        {
          connect( _signalMapper, SIGNAL(mapped(const QString &) ),
                   _pluginManager, SLOT(executeLoad(const QString &)) );
          break;
        }
        
        case SAVE_CALL:
        {
          connect( _signalMapper, SIGNAL(mapped(const QString &) ),
                   _pluginManager, SLOT(executeSave(const QString &)) );
          break;
        }

        case ACTION_CALL:
        {
          break;
        }
        
        default:
          break;
      }
      
      
      aAction->addTo(_menus[decomposition[decomposition.size() - 2]]);
      
    }
//     else if (component == "Tool")
//     {
//       //TODO : to implement it !!!
//     }

    
  }//end of for loop
  
  
}

void
MainWindow::addStaticMenuBarContent()
{
  qDebug("Beginning addStaticMenuBarContent");
  
  //File
  QPopupMenu* fileMenu = _menus.find(FILE_KEY);

  if(!fileMenu)
  {
    std::cout <<  "PROUT" << std::endl;
    
    QPopupMenu * file = new QPopupMenu( this );
    _menus.insert(FILE_KEY, file);
    menuBar()->insertItem( FILE_KEY, _menus[FILE_KEY]);
  }

  _menus[FILE_KEY]->insertSeparator();

  //Cylinder Menu
  QPopupMenu* cylinderMenu =  _menus.find(CYLINDER_KEY);
  if (!cylinderMenu)
  {
    QPopupMenu * help = new QPopupMenu( this );
    _menus.insert(CYLINDER_KEY, help);
    menuBar()->insertItem( CYLINDER_KEY, _menus[CYLINDER_KEY]);
  }
  
  
  QAction* generateCylinderAction = new QAction("generate",
                                                QIconSet( QPixmap(IMAGES_DIR + CYLINDER_IMAGE) ),
                                                "&Generate",
                                                CTRL+Key_G,
                                                this);
  
  connect(generateCylinderAction,
          SIGNAL( activated() ),
          this,
          SLOT( generateCylinder() ) );

  generateCylinderAction->addTo(_menus[CYLINDER_KEY]);
  _toolBar->addSeparator();
  generateCylinderAction->addTo(_toolBar);


  QAction* quitAction = new QAction("quit",
                                    QIconSet( QPixmap(IMAGES_DIR + QUIT_IMAGE) ),
                                    "&Quit",
                                    CTRL+Key_Q,
                                    this);
  connect(quitAction,
          SIGNAL( activated() ),
          qApp,
          SLOT( quit() ) );

  quitAction->addTo(_menus[FILE_KEY]);

  _toolBar->addSeparator();
  quitAction->addTo(_toolBar);

  //Help Menu with about
  QPopupMenu* helpMenu =  _menus.find(HELP_KEY);

  if (!helpMenu)
  {
    QPopupMenu * help = new QPopupMenu( this );
    _menus.insert(HELP_KEY, help);
    menuBar()->insertItem( HELP_KEY, _menus[HELP_KEY]);
  }
  
  _menus[HELP_KEY]->insertItem( "&About", this, SLOT(about()));
  
}

void
MainWindow::initViewFrames(int screen_height, int frame_width, int application_width)
{
  _w3d = new Window3D();
  Canvas3D* _canvas3d = new Canvas3D(_w3d);
  _canvas3d->setCaption("Perspective");
  _w3d->attachCanvas(_canvas3d);
  
  _cylGenerator = new CylinderGenerator(*_canvas3d);
  
  
  _wChemin = new Window3D();
  Canvas2D* _canvasChemin = new Canvas2D(_wChemin,"Chemin");
  _canvasChemin->setCaption("Chemin");
  _wChemin->attachCanvas(_canvasChemin);

  _wProfil = new Window3D();
  Canvas2D* _canvasProfil = new Canvas2D(_wProfil,"Profil");
  _canvasProfil->setCaption("Profil");
  _wProfil->attachCanvas(_canvasProfil);

  _wSection = new Window3D();
  Canvas2D* _canvasSection = new Canvas2D(_wSection,"Section");
  _canvasSection->setCaption("Section");
  _wSection->attachCanvas(_canvasSection);
     
  qDebug("Inside initViewFrames");

  _w3d->resize(frame_width, frame_width);
  _wChemin->resize(frame_width, frame_width);
  _wSection->resize(frame_width, frame_width);
  _wProfil->resize(frame_width, frame_width);
  
  //Set title for each frame !!
  _wChemin->setCaption("Chemin");
  _wSection->setCaption("Section");
  _wProfil->setCaption("Profil");
  
   _wChemin->move(x() + application_width, 0);
   _wSection->move(x() + frame_width + application_width, 0);
   _wProfil->move(x() + application_width, frame_width + 20 );
   _w3d->move(x() + frame_width + application_width, frame_width + 20 );
  
  //ok show the frames !
  _wChemin->show();
  _wSection->show();
  _wProfil->show();
  _w3d->show();
}
void
MainWindow::updateViewFramesPosition()
{
  int h2 = frameGeometry().height();

//  _w3d.move(x() + _w3d.width(), y() + _w3d.width() + height());
}

Canvas3D&
MainWindow::getCanvas3D()
{
  return dynamic_cast<Canvas3D &>( _w3d->canvas() );
}

Canvas2D&
MainWindow::getCheminCanvas()
{
  return dynamic_cast<Canvas2D &>( _wChemin->canvas() );
}

Canvas2D&
MainWindow::getProfilCanvas()
{
  return dynamic_cast<Canvas2D &>( _wProfil->canvas() );
}

Canvas2D& 
MainWindow::getSectionCanvas()
{
  return dynamic_cast<Canvas2D &>( _wSection->canvas() );
}

Faces&
MainWindow::model()
{
  return dynamic_cast<Canvas3D &>( _w3d->canvas() ).renderer().model();
}

void
MainWindow::setModel(Faces& faces)
{
  qDebug("MainWindow : beginning setModel ");
    
  Canvas3D& c3d = dynamic_cast<Canvas3D &>( _w3d->canvas() );

  c3d.makeCurrent();

  _chronometer.start();
  c3d.renderer().setModel(faces);
  int buildTime = (_chronometer.elapsed());

  QString status = QString("Display Lists rebuilt in %1").arg(buildTime) + QString(" ms");
  statusBar()->message( status, 5000 );
  
  
  c3d.updateGL();

//  qApp->sendPostedEvents();
}


//Qt EVENTS
void
MainWindow::moveEvent(QMoveEvent* event)
{
  qDebug("Move event received\n");
  updateViewFramesPosition();
}


//SLOTS
void
MainWindow::about()
{

  std::cout << "dans ABOUT" << std::endl;
  
  QMessageBox::about( this,
                      "About AGECYMO",
                      "Another Generalized Cylinder Modeler\n"
                      "\t developed by \n"
                      "\tAlexis Derrien \n"
                      "\tRomain Pacanowski \n"
                      "\tAlexandre Viollet \n" );

}



// void
// MainWindow::generateCylinder()
// {

//   qDebug("Mainwindow : Dans generateCylinder ");
  
//   std::vector<Point3D> ptsSection;
//   std::vector<Point3D> ptsProfile;
//   std::vector<Point3D> ptsChemin;


//   Point3D s1, s2, s3, s4;
//   Point3D s5, s6, s7, s8;
  
//   Point3D c1, c2, c3, c4 , c5, c6 ;

//   s1[0] = -1.0; s1[1] = 0;  s1[2] = 1.0;
//   s2[0] = 1.0; s2[1] = 0;  s2[2] = 1.0;
//   s3[0] = 1.0; s3[1] = 0;  s3[2] = -1.0;
//   s4[0] = -1.0; s4[1] = 0;  s4[2] = -1.0;

  
//   s5[0] = 0.0; s5[1] = 0;  s5[2] = 1.4;
//   s6[0] = 1.4; s6[1] = 0;  s6[2] = 0;
//   s7[0] = 0; s7[1] = 0;  s7[2] = -1.4;
//   s8[0] = -1.4; s8[1] = 0;  s8[2] = 0;

//   ptsSection.push_back(s1);
//   ptsSection.push_back(s5);
//   ptsSection.push_back(s2);
//   ptsSection.push_back(s6);
//   ptsSection.push_back(s3);
//   ptsSection.push_back(s7);
//   ptsSection.push_back(s4);
//   ptsSection.push_back(s8);
  
//   c1[0] = 0; c1[1] = 0; c1[2] = 0;
//   c2[0] = 0; c2[1] = 5; c2[2] = 0;
//   c3[0] = 5; c3[1] = 8; c3[2] = 0;

//   c4[0] = 0; c4[1] = 4; c4[2] = 0;
//   c5[0] = 0.1; c5[1] = 8; c5[2] = 0;
//   c6[0] = 1.75; c6[1] = 1.75; c6[2] = 0;
  

//   ptsChemin.push_back(c1);
//   ptsChemin.push_back(c4);
//   ptsChemin.push_back(c2);
//   ptsChemin.push_back(c5);
//   ptsChemin.push_back(c3);
// //  ptsChemin.push_back(c4);
// //  ptsChemin.push_back(c5);
// //  ptsChemin.push_back(c6);
  
//   _cylGenerator->generate( ptsChemin, ptsSection, ptsProfile);

// }

void
MainWindow::generateCylinder()
{
  qDebug("Mainwindow : Dans generateCylinder ");

  
  Canvas3D & canvas =  dynamic_cast<Canvas3D &>(_w3d->canvas());
  canvas.makeCurrent();

  int paramDiscretisationCHEMIN  = 18;
  int paramDiscretisationSECTION = 15;

  Canvas2D & canvasSection =  dynamic_cast<Canvas2D &>(_wSection->canvas());
  Canvas2D & canvasChemin  =  dynamic_cast<Canvas2D &>(_wChemin->canvas());
  Canvas2D & canvasProfil  =  dynamic_cast<Canvas2D &>(_wProfil->canvas());

  AbsCurve* section =  canvasSection.getFigure();
  AbsCurve* chemin =  canvasChemin.getFigure();
  AbsCurve* profil =  canvasProfil.getFigure();

  if( (section == NULL) || (chemin == NULL) || (profil == NULL) )
  {
    QMessageBox::warning( this, "ERROR",
                          "Impossible to generate a cylinder without curves .\n");
    return;
  }
  
  
  std::vector<Point3D> ptsSection = section->discretize(paramDiscretisationSECTION);
  adjustSection(ptsSection);
  
  std::vector<Point3D> ptsChemin  = chemin->discretize(paramDiscretisationCHEMIN);

  std::vector<Point3D> ptsProfile = profil->discretize(paramDiscretisationCHEMIN);

  
  int timeTiGenerateIt = ( _cylGenerator->generate( ptsChemin,
                                                    ptsSection,
                                                    ptsProfile) );
    

  displayTimeStatus("Cylinder generated in %1", timeTiGenerateIt);
}

void
MainWindow::adjustSection(std::vector<Point3D> & ptsSection)
{
  Point3D temp;
  
  
  for (unsigned int i = 0; i< ptsSection.size(); i++)
  {
    temp = ptsSection[i];

    ptsSection[i][0] = temp[0];
    ptsSection[i][1] = 0;
    ptsSection[i][2] = temp[1];
  }

}



// void
// MainWindow::generateCylinder()
// {

//   qDebug("Mainwindow : Dans generateCylinder ");
  
//   std::vector<Point3D> ptsSection;
//   std::vector<Point3D> ptsProfile;
//   std::vector<Point3D> ptsChemin;


//   Point3D s1, s2, s3, s4;
//   Point3D s5, s6, s7, s8;
  
//   Point3D c1, c2, c3, c4;

//   s1[0] = -1.0; s1[1] = 0;  s1[2] = 1.0;
//   s2[0] = 1.0; s2[1] = 0;  s2[2] = 1.0;
//   s3[0] = 1.0; s3[1] = 0;  s3[2] = -1.0;
//   s4[0] = -1.0; s4[1] = 0;  s4[2] = -1.0;

  

//   s5[0] = 0.0; s5[1] = 0;  s5[2] = 1.4;
//   s6[0] = 1.4; s6[1] = 0;  s6[2] = 0;
//   s7[0] = 0; s7[1] = 0;  s7[2] = -1.4;
//   s8[0] = -1.4; s8[1] = 0;  s8[2] = 0;


//   ptsSection.push_back(s1);
//   ptsSection.push_back(s5);
//   ptsSection.push_back(s2);
//   ptsSection.push_back(s6);
//   ptsSection.push_back(s3);
//   ptsSection.push_back(s7);
//   ptsSection.push_back(s4);
//   ptsSection.push_back(s8);
  
//   c1[0] = 0; c1[1] = 1; c1[2] = 0;
//   c2[0] = 0; c2[1] = 2; c2[2] = 0;
//   c3[0] = 0; c3[1] = 3; c3[2] = 0;
//   c4[0] = 0; c4[1] = 4; c4[2] = 0;
  

//   ptsChemin.push_back(c1);
//   ptsChemin.push_back(c2);
//   ptsChemin.push_back(c3);
//   ptsChemin.push_back(c4);

//   _cylGenerator->generate( ptsChemin, ptsSection, ptsProfile);

// }

  

void
MainWindow::displayTimeStatus(const char* operation, int timeInMilliSeconds)
{
  if (_labelStatus == NULL)
  {
    _labelStatus =  new QLabel(this);
  }
  else
  {
    statusBar()->removeWidget(_labelStatus);
  }
  
  QString status = QString(operation).arg(timeInMilliSeconds).append(" ms");
  _labelStatus->setText(status);
  
  statusBar()->addWidget( _labelStatus );

}

