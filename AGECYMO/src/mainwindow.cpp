#include "mainwindow.hpp"

/**************************************************************
 *
 *  MainWindow constructor
 *  @param screen_w the width of the screen
 *  @param screen_h the height of the screnn
 *  @param w_app the width of the window
 *  @param h_app the height of the window
 *  @param x_app the x position of the window
 *  @param y_app the y position of the window
 *
 *************************************************************/
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
  
  //HelpWindow
  QDir absoluteManualDir(MANUAL_DIR);
  absoluteManualDir.convertToAbs();
  _helpFrame = new HelpWindow( absoluteManualDir.absFilePath(MANUAL_INDEX) );
  
  //Plugin Manager
  _pluginManager = new PluginManager(this);

  _comments = new EventsWindow();

  //Toolbar
  _toolBar = new QToolBar("Operations", this);
  _toolBar->setHorizontallyStretchable(true);
  _toolBar->setVerticallyStretchable(true);
  _toolBar->setResizeEnabled(true);

  //Geometry stuff
  resize(w_app, h_app);
  move(0, 0);
  setCaption(TITLE);
  
  show();

  //Other View 
  initViewFrames(800, screen_w, w_app);

  
  //Tell the plugin manager to load and unload the available plugins
  //Plugins will be loaded on demand
  _pluginManager->recordAvailablePlugins();

  //Other GUI Stuff
  addStaticMenuBarContent();
  moveDockWindow(_toolBar, Qt::DockLeft);
  
}

/**************************************************************
 *
 *  MainWindow destructor
 *
 *************************************************************/
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

/**************************************************************
 *  This is the main method which update the GUI
 *  according to the plugin's data
 *  @param pluginID the id of the plugin 
 *  @param type the type of the plugin
 *  @param infos plugin informations
 *
 *************************************************************/
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

/**************************************************************
 *
 *  add the static menu bars
 *
 *************************************************************/
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


  // Validation menu
//   QAction* validAction = new QAction("validation",
//                                     QIconSet( QPixmap(IMAGES_DIR + QUIT_IMAGE) ),
//                                     "&Validation",
//                                     CTRL+Key_V,
//                                     this);
//   connect(validAction,
//           SIGNAL( activated() ),
//           this,
//           SLOT( validation() ) );

//   validAction->addTo(_menus[FILE_KEY]);

//   _toolBar->addSeparator();
//   validAction->addTo(_toolBar);

  //Tools Menu
  QPopupMenu* toolsMenu =  _menus.find(TOOLS_KEY);
  if (!toolsMenu)
  {
    QPopupMenu * tools = new QPopupMenu( this );
    _menus.insert(TOOLS_KEY, tools);
    menuBar()->insertItem( TOOLS_KEY, _menus[TOOLS_KEY]);
  }
  
  _menus[TOOLS_KEY]->insertItem("Validate Solid", this, SLOT( validation() ) );
  
    
  //Help Menu with about
  QPopupMenu* helpMenu =  _menus.find(HELP_KEY);

  if (!helpMenu)
  {
    QPopupMenu * help = new QPopupMenu( this );
    _menus.insert(HELP_KEY, help);
    menuBar()->insertItem( HELP_KEY, _menus[HELP_KEY]);
  }

  _menus[HELP_KEY]->insertItem( "Getting &Started", this, SLOT(manual()));
  _menus[HELP_KEY]->insertItem( "&About", this, SLOT(about()));
  
}

/**************************************************************
 *
 *  init the frames
 *  @param screen_height the height of the screen
 *  @param screen_width the width of the screen
 *  @param application_width the width of the application
 *
 *************************************************************/
void
MainWindow::initViewFrames(int screen_height, int frame_width, int application_width)
{
  _w3d = new Window3D();
  Canvas3D* _canvas3d = new Canvas3D(this, _w3d);
  _canvas3d->setCaption("Perspective");
  _w3d->attachCanvas(_canvas3d);
  
  _cylGenerator = new CylinderGenerator(*_canvas3d);
  
  
  _wChemin = new Window3D();
  Canvas2D* _canvasChemin = new Canvas2D(this, _wChemin,"Chemin");
  _canvasChemin->setCaption("Chemin");
  _wChemin->attachCanvas(_canvasChemin);

  _wProfil = new Window3D();
  Canvas2D* _canvasProfil = new Canvas2D(this, _wProfil,"Profil");
  _canvasProfil->setCaption("Profil");
  _wProfil->attachCanvas(_canvasProfil);

  _wSection = new Window3D();
  Canvas2D* _canvasSection = new Canvas2D(this, _wSection,"Section");
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
  
   _wChemin->move(x() + application_width +110, 0);
   _wSection->move(x() + frame_width + application_width+110, 0);
   _wProfil->move(x() + application_width+110, frame_width + 20 );
   _w3d->move(x() + frame_width + application_width+110, frame_width + 20 );
  
  //ok show the frames !
  _wChemin->show();
  _wSection->show();
  _wProfil->show();
  _w3d->show();
  _comments->show();
}


/**************************************************************
 *
 *  update the view frame
 *
 *************************************************************/
void
MainWindow::updateViewFramesPosition()
{
  int h2 = frameGeometry().height();

//  _w3d.move(x() + _w3d.width(), y() + _w3d.width() + height());
}

/**************************************************************
 *
 *  get the canvas3D
 *  @return the 3d canvas
 *
 *************************************************************/
Canvas3D&
MainWindow::getCanvas3D()
{
  return dynamic_cast<Canvas3D &>( _w3d->canvas() );
}

/**************************************************************
 *
 *  get the wayCanvas
 *  @return the wayCanvas
 *
 *************************************************************/
Canvas2D&
MainWindow::getCheminCanvas()
{
  return dynamic_cast<Canvas2D &>( _wChemin->canvas() );
}

/**************************************************************
 *
 *  get the profilCanvas
 *  @return the profilCanvas
 *
 *************************************************************/
Canvas2D&
MainWindow::getProfilCanvas()
{
  return dynamic_cast<Canvas2D &>( _wProfil->canvas() );
}

/**************************************************************
 *
 *  get the sectionCanvas
 *  @return the sectionCanvas
 *
 *************************************************************/
Canvas2D& 
MainWindow::getSectionCanvas()
{
  return dynamic_cast<Canvas2D &>( _wSection->canvas() );
}

/**************************************************************
 *
 *  get the eventWindow
 *  @return the eventWindow
 *
 *************************************************************/
EventsWindow&
MainWindow::getEventsWindow() {
  return *_comments;
}

/**************************************************************
 *
 *  get the model
 *  @return the model (all faces)
 *
 *************************************************************/
Faces&
MainWindow::model()
{
  return dynamic_cast<Canvas3D &>( _w3d->canvas() ).renderer().model();
}

/**************************************************************
 *
 *  set the model
 *  @param faces the model
 *
 *************************************************************/
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


/**************************************************************
 *
 *  manage moce events
 *  @param event the event
 *
 *************************************************************/
void
MainWindow::moveEvent(QMoveEvent* event)
{
  qDebug("Move event received\n");
  updateViewFramesPosition();
}


/**************************************************************
 *
 *  display about window
 *
 *************************************************************/
void
MainWindow::about()
{

  qDebug("dans ABOUT");
  
  
  QMessageBox::about( this,
                      "About AGECYMO",
                      "Another Generalized Cylinder Modeler\n"
                      "\t developed by \n"
                      "\tAlexis Derrien \n"
                      "\tRomain Pacanowski \n"
                      "\tAlexandre Viollet \n" );

}

/**************************************************************
 *
 *  display manual window
 *
 *************************************************************/
void
MainWindow::manual()
{
  qDebug("Dans manual");

  _helpFrame->show();
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


/**************************************************************
 *
 *  generate the cylinder
 *
 *************************************************************/
void
MainWindow::generateCylinder()
{
  qDebug("Mainwindow : Dans generateCylinder ");

  if ( ! (_controlPanel->controlWayValue()) )
  {
    return;
  }

  if ( ! (_controlPanel->controlSectionValue()) )
  {
    return;
  }
  
  if ( ! (_controlPanel->controlScaleSectionValue()) )
  {
    return;
  }
  
  if ( ! (_controlPanel->controlScaleWayValue()) )
  {
    return;
  }
  
  //Set the OpenGL Context to the 3D Canvas
  Canvas3D & canvas =  dynamic_cast<Canvas3D &>(_w3d->canvas());
  canvas.makeCurrent();

  //Retrieve the curves !!!
  Canvas2D & canvasSection =  dynamic_cast<Canvas2D &>(_wSection->canvas());
  Canvas2D & canvasChemin  =  dynamic_cast<Canvas2D &>(_wChemin->canvas());
  Canvas2D & canvasProfil  =  dynamic_cast<Canvas2D &>(_wProfil->canvas());

  Curves* section =  canvasSection.getFigure();
  Curves* chemin =  canvasChemin.getFigure();
  Curves* profil = canvasProfil.getFigure();
  
  _cylGenerator->setWayClosed( chemin->isClosed() );

  int nbSegmentsChemin  =  chemin->globalNbSegments();
  int nbSegmentsProfil  =  profil->globalNbSegments();
  int nbSegmentsSection =  section->globalNbSegments();


  if (nbSegmentsChemin == 0)
  {
    QMessageBox::warning( this, "ERROR",
                          "Impossible to generate a cylinder without a way curve .\n");
    return;
  }

  if (nbSegmentsSection == 0)
  {
    QMessageBox::warning( this, "ERROR",
                          "Impossible to generate a cylinder without a section curve .\n");
    return;
  }


  
  if (nbSegmentsProfil == 0)
  {
    QMessageBox::warning( this, "ERROR",
                          "Impossible to generate a cylinder without a profile curve .\n");
    return;
  }
  

  
  
  std::cout << "nb de segments " << std::endl
            << "chemin  = " << nbSegmentsChemin << std::endl
            << "profil  = " << nbSegmentsProfil << std::endl
            << "section = " << nbSegmentsSection << std::endl;


  int nWay = _controlPanel->wayDiscretizeValue();

    
  std::vector<Point3D> ptsProfile;
  std::vector<Point3D> ptsChemin;

  if ( nbSegmentsChemin == 1)
  {
    qDebug("Cas chemin = un segment");
    
    int n = (nWay / nbSegmentsProfil);
    qDebug("n = %d", n);
    ptsProfile = profil->discretize( n );
    ptsChemin = chemin->discretize( ptsProfile.size() );
  }
  else if ( nbSegmentsProfil == 1)
  {
    qDebug("Cas profil = un segment");
    
    int n = (nWay / nbSegmentsChemin);
    qDebug("n = %d", n);
    ptsChemin  = chemin->discretize( n );
    ptsProfile = profil->discretize( ptsChemin.size() );
  }
  else if ( nbSegmentsChemin == nbSegmentsProfil) 
  {
    qDebug("Cas MEME Nombre de segments ");
    int n = (nWay / nbSegmentsProfil);
    qDebug("n = %d", n);
    ptsProfile = profil->discretize( n );
    ptsChemin = chemin->discretize( n );
  }
  else 
  {
    qDebug("ICI  !!!!!!!!!!!!");
    
    int nbPtCtrlProfile = nbSegmentsProfil + 1;
    int nbPtCtrlChemin  = nbSegmentsChemin + 1;

    bool found  = false;

    int partieEntiere1 = 0;
    int partieEntiere2 = 0;

    qDebug("nWay = %d", nWay);
    qDebug("n point de controle profile = %d", nbPtCtrlProfile);
    
    int i=0;
    
    while (  !found)
    {
      partieEntiere1 =  (int)  ( (nWay - nbPtCtrlProfile) / nbSegmentsProfil );
      int reste1  =  (nWay - nbPtCtrlProfile) % nbSegmentsProfil;

      qDebug("partieEntiere1  = %d", partieEntiere1);
      qDebug("reste1  = %d", reste1);
      
      if ( reste1 == 0)
      {

      }
      else
      {
        partieEntiere1++;
        nWay = nbSegmentsProfil * partieEntiere1 + nbPtCtrlProfile;
      }
      
      
      partieEntiere2 = (int) ( ( nWay - nbPtCtrlChemin) / nbSegmentsChemin );
      int reste2 = ( nWay - nbPtCtrlChemin) % nbSegmentsChemin;
      
      qDebug("partieEntiere2  = %d", partieEntiere2);
      qDebug("reste2  = %d", reste2);
      
      if (reste2 == 0)
      {
        found = true;
      }
      else
      {
        nWay = ((partieEntiere1 + 1) * nbSegmentsProfil) + nbPtCtrlProfile;
      }
      qDebug("current nway before looping = %d ", nWay);
    }
    
    
    qDebug("nWay found is %d", nWay);
    qDebug("partie entiere1 found is %d", partieEntiere1);
    qDebug("partie entiere2 found is %d", partieEntiere2);


    assert( nWay == (partieEntiere1 * nbSegmentsProfil + nbPtCtrlProfile) );
    assert( nWay == (partieEntiere2 * nbSegmentsChemin + nbPtCtrlChemin) );

    ptsProfile = profil->discretize( partieEntiere1 + 2 );
    ptsChemin = chemin->discretize( partieEntiere2 + 2 );
    
  }
  
  adjustWay(ptsChemin, _controlPanel->scaleFactorWay() );
  
 
  std::cout << "We have " << ptsProfile.size() << "pts on the profile curve" << std::endl;
  std::cout << "We have " << ptsChemin.size() << " pts on the WAY curve" << std::endl;

  
  

  //Hack
  if ( ptsProfile.size() > ptsChemin.size() )
  {

    ptsProfile.pop_back();
  }
  else if ( ptsChemin.size() > ptsProfile.size()  )
  {
    ptsChemin.pop_back();
    
  }
  
  assert (ptsProfile.size() == ptsChemin.size() );
  
  
  int nSection = _controlPanel->sectionDiscretizeValue();
  std::vector<Point3D> ptsSection = section->discretize( nSection / nbSegmentsSection);
  adjustSection(ptsSection, _controlPanel->scaleFactorSection() );
  
  if ( ptsProfile.size() == 0)
  {
    QMessageBox::warning( this, "ERROR",
                          "Impossible to generate a cylinder without a profile curve .\n");
    return;
  }


  if (ptsChemin.size() < 2)
  {
    QMessageBox::warning( this, "ERROR",
                          "Impossible to generate need more point for the way.\n");
    return;
  }

  if (ptsProfile.size() < 2)
  {
    QMessageBox::warning( this, "ERROR",
                          "Impossible to generate need more points for the profile .\n");
    return;
  }

  if (ptsSection.size() < 3)
  {
    QMessageBox::warning( this, "ERROR",
                          "Impossible to generate need more points for the section .\n");
    return;
  }
  

  int timeTiGenerateIt = ( _cylGenerator->generate( ptsChemin,
                                                    ptsSection,
                                                    ptsProfile) );
    
  displayTimeStatus("Cylinder generated in %1", timeTiGenerateIt);  
}


// void
// MainWindow::generateCylinder()
// {
//   qDebug("Mainwindow : Dans generateCylinder ");

//   if ( ! (_controlPanel->controlWayValue()) )
//   {
//     return;
//   }

//   if ( ! (_controlPanel->controlSectionValue()) )
//   {
//     return;
//   }
  
//   if ( ! (_controlPanel->controlScaleSectionValue()) )
//   {
//     return;
//   }
  
//   if ( ! (_controlPanel->controlScaleWayValue()) )
//   {
//     return;
//   }

//   _cylGenerator->setTorsionEnabled( _controlPanel->isTorsionEnabled());
  
//   //Set the OpenGL Context to the 3D Canvas
//   Canvas3D & canvas =  dynamic_cast<Canvas3D &>(_w3d->canvas());
//   canvas.makeCurrent();

//   int paramDiscretisationCHEMIN  = 20;
//   int paramDiscretisationSECTION = 15;
//   int paramDiscretisationPROFIL  = 15;

//   Canvas2D & canvasSection =  dynamic_cast<Canvas2D &>(_wSection->canvas());
//   Canvas2D & canvasChemin  =  dynamic_cast<Canvas2D &>(_wChemin->canvas());
//   Canvas2D & canvasProfil  =  dynamic_cast<Canvas2D &>(_wProfil->canvas());

//   Curves* section =  canvasSection.getFigure();
//   Curves* chemin =  canvasChemin.getFigure();
//   Curves* profil = canvasProfil.getFigure();


// //  QMessageBox::warning( this, "ERROR",
// //                        "Impossible to generate a cylinder without curves .\n");
    

//   std::cout << "Chemin is closed = " << chemin->isClosed() << std::endl;
//   _cylGenerator->setWayClosed( chemin->isClosed() );


//   int nbSegmentsChemin  =  chemin->getNbControlPoints() - 1;
//   int nbSegmentsProfil  =  profil->getNbControlPoints() - 1;
//   int nbSegmentsSection =  section->getNbControlPoints() - 1;
  
//   std::cout << "nb de segments " << std::endl
//             << "chemin  = " << nbSegmentsChemin << std::endl
//             << "profil  = " << nbSegmentsProfil << std::endl
//             << "section = " << nbSegmentsSection << std::endl;

//   int nWay = _controlPanel->wayDiscretizeValue();
//   int nSection = _controlPanel->sectionDiscretizeValue();

//   paramDiscretisationSECTION = nSection / nbSegmentsSection;
//   paramDiscretisationPROFIL  = nWay / nbSegmentsProfil;
//   paramDiscretisationCHEMIN  = nWay / nbSegmentsChemin;

//   qDebug("nWay recupere = %d", nWay);
//   qDebug("paramDiscretisationSECTION = %d", paramDiscretisationSECTION);
//   qDebug("paramDiscretisationPROFIL = %d", paramDiscretisationPROFIL);
//   qDebug("paramDiscretisationCHEMIN = %d", paramDiscretisationCHEMIN);
  
  
//   std::vector<Point3D> ptsSection = section->discretize(paramDiscretisationSECTION);
//   adjustSection(ptsSection, _controlPanel->scaleFactorSection() );

//   int nProfile = nWay / nbSegmentsProfil;
//   nProfile = (nProfile < 2) ? (2) : (nProfile);

//   qDebug("nProfile = %d", nProfile);
  
//   std::vector<Point3D> ptsProfile = profil->discretize( nProfile );
  
//   int discretizeWay;
//   int u = ptsProfile.size()/ nbSegmentsChemin;
//   qDebug(" nombre de points sur le profil = %d", ptsProfile.size() );
//   qDebug("u = %d", u);
//   qDebug("nbSegmentsChemin = %d", nbSegmentsChemin);
  
//   std::vector<Point3D> ptsChemin  = chemin->discretize( u );
// //  std::vector<Point3D> ptsChemin  = chemin->discretize( ptsProfile.size() );

//   qDebug("size de ptsChemin = %d", ptsChemin.size() );
  
//    while (  (discretizeWay = ptsChemin.size()) < ptsProfile.size() )
//    {
//      u++;
//      ptsChemin = chemin->discretize( u );
//    }

//    while( ptsChemin.size() != (ptsProfile.size()) )
//    {
//      ptsChemin.pop_back();
//    }
  
  
//   adjustWay(ptsChemin, _controlPanel->scaleFactorWay() );
  
//   qDebug("Apres Discretisation");
//   qDebug(" nb pt chemin = %d",  ptsChemin.size());
//   qDebug(" nb pt profile = %d", ptsProfile.size());
    

//   if ( ptsChemin.size() == 0 )
//   {
//     QMessageBox::warning( this, "ERROR",
//                           "Impossible to generate a cylinder without a way curve .\n");
//     return;
//   }

//   if ( ptsSection.size() == 0)
//   {
//     QMessageBox::warning( this, "ERROR",
//                           "Impossible to generate a cylinder without a section curve .\n");
//     return;
//   }
  
  
//   if ( ptsProfile.size() == 0)
//   {
//     QMessageBox::warning( this, "ERROR",
//                           "Impossible to generate a cylinder without a profile curve .\n");
//     return;
//   }


//   if (ptsChemin.size() < 2)
//   {
//     QMessageBox::warning( this, "ERROR",
//                           "Impossible to generate need more point for the way.\n");
//     return;
//   }

//   if (ptsProfile.size() < 2)
//   {
//     QMessageBox::warning( this, "ERROR",
//                           "Impossible to generate need more points for the profile .\n");
//     return;
//   }

//   if (ptsSection.size() < 3)
//   {
//     QMessageBox::warning( this, "ERROR",
//                           "Impossible to generate need more points for the section .\n");
//     return;
//   }
  

//   int timeTiGenerateIt = ( _cylGenerator->generate( ptsChemin,
//                                                     ptsSection,
//                                                     ptsProfile) );
    

//   displayTimeStatus("Cylinder generated in %1", timeTiGenerateIt);
// }

/**************************************************************
 *
 *  adjust the way via a scale
 *  @param ptsChemin the way's points
 *  @param scaleFactor the scale
 *
 *************************************************************/
void
MainWindow::adjustWay(std::vector<Point3D> & ptsChemin, double scaleFactor)
{
  Point3D temp;

  qDebug("Dans adjustWay scale factor = : %f", scaleFactor);
  
  Matrix3D scaleMatrix = Matrix3D::scale(scaleFactor, scaleFactor, scaleFactor);
  
  for (unsigned int i = 0; i< ptsChemin.size(); i++)
  {
    temp = ptsChemin[i];
    ptsChemin[i] = scaleMatrix * temp;
  }
  
}
                      
/**************************************************************
 *
 *  adjust the section via a scale
 *  @param ptsSection the section's points
 *  @param scaleFactor the scale
 *
 *************************************************************/
void
MainWindow::adjustSection(std::vector<Point3D> & ptsSection, double scaleFactor)
{
  Point3D temp;
  Point3D temp2;
  
  Matrix3D scaleMatrix = Matrix3D::scale(scaleFactor, scaleFactor, scaleFactor);
  
  
  for (unsigned int i = 0; i< ptsSection.size(); i++)
  {
    temp = ptsSection[i];

    
//     ptsSection[i][0] = temp[0];
//     ptsSection[i][1] = 0;
//     ptsSection[i][2] = temp[1];

    temp2[0] = temp[0];
    temp2[1] = 0;
    temp2[2] = temp[1];

    ptsSection[i] = scaleMatrix * temp2;
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

  
/**************************************************************
 *
 *  display time indications
 *  @param operation the name of the operation
 *  @param timeInMilliSeconds the operation time
 *
 *************************************************************/
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

void 
MainWindow::validation() {


  Faces & allFaces = model();
  

  allFaces.validModel();
  
}
