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
  _pluginManager = new PluginManager(this);

  _toolBar = new QToolBar("Operations", this);
  
  resize(w_app, h_app);
  move(x_app, y_app);
  setCaption(TITLE);
  show();

  initViewFrames();

  //Tell the plugin manager to load and unload the available plugins
  //Plugins will be loaded on demand
  _pluginManager->recordAvailablePlugins();

  addStaticMenuBarContent();
  
}

MainWindow::~MainWindow()
{
  delete _wSection;
  delete _wProfil;
  delete _wChemin;
  delete _w3d;
  delete _pluginManager;
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
MainWindow::initViewFrames()
{
  _w3d = new Window3D();
  Canvas3D* _canvas3d = new Canvas3D(_w3d);
  _w3d->attachCanvas(_canvas3d);

  _wChemin = new Window3D();
  Canvas2D* _canvasChemin = new Canvas2D(_wChemin);
  _wChemin->attachCanvas(_canvasChemin);

  _wProfil = new Window3D();
  Canvas2D* _canvasProfil = new Canvas2D(_wProfil);
  _wProfil->attachCanvas(_canvasProfil);

  _wSection = new Window3D();
  Canvas2D* _canvasSection = new Canvas2D(_wSection);
  _wSection->attachCanvas(_canvasSection);
     
  int mw_w = width();
  int mw_h = height();
  int mw_w2 = mw_w / 2;
  
  int h2 = frameGeometry().height();
  int h3 = geometry().height();

  qDebug("Inside initViewFrames");
  qDebug("mw_h =  %d\n", mw_h);
  qDebug("h2 =  %d\n", h2);
  qDebug("h3 =  %d\n", h3);
  
  int f_h = (_screen_h - mw_h) / 2;
  int w_h = (f_h < mw_w2)? (f_h) : (mw_w2);

  _w3d->resize(w_h, w_h);
  _wChemin->resize(w_h, w_h);
  _wSection->resize(w_h, w_h);
  _wProfil->resize(w_h, w_h);

  
  if (w_h != mw_w2)
  {
    resize(2*w_h, mw_h);
    move(((_screen_w - 2*w_h)/2), 0);
  }

  //Set title for each frame !!
  _wChemin->setCaption("Chemin");
  _wSection->setCaption("Section");
  _wProfil->setCaption("Profil");
  
  //Move the frames !
  _wChemin->move(x(), h2);
  _wSection->move(x() + w_h, h2);
  _wProfil->move(x(), h2 + w_h);
  _w3d->move(x() + w_h, h2 + w_h);
  
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
  dynamic_cast<Canvas3D &>( _w3d->canvas() ).renderer().setModel(faces);
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
                      "Another Generalize Cylinder Modeler\n"
                      "\t developed by \n"
                      "\tAlexis Derrien \n"
                      "\tRomain Pacanowski \n"
                      "\tAlexandre Viollet \n" );

}

