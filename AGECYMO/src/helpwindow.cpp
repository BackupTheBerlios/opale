#include "helpwindow.hpp"


//most of this code has been taken from Qt example

HelpWindow::HelpWindow(const QString& home)
//    : QVBox()
    : QMainWindow()
{
  _browser = new QTextBrowser(this);
  _browser->setFrameStyle( QFrame::Panel | QFrame::Sunken );

  _browser->setSource( home );
  _browser->setTextFormat(Qt::RichText);
  _browser->setStyleSheet( QStyleSheet::defaultSheet() );
  
  connect( _browser, SIGNAL( sourceChanged(const QString& ) ),
           this, SLOT( sourceChanged( const QString&) ) );

  connect( _browser, SIGNAL( linkClicked ( const QString&) ),
           this, SLOT ( redirection(const QString&) ) );
  
  // The same three icons are used twice each.
  QIconSet icon_back( QPixmap("./manual/back.xpm") );
  QIconSet icon_forward( QPixmap("./manual/forward.xpm") );
  QIconSet icon_home( QPixmap("./manual/home.xpm") );

  //Go Menu
  QPopupMenu* go = new QPopupMenu( this );
  backwardId = go->insertItem( icon_back,
                               tr("&Backward"), _browser, SLOT( backward() ),
                               CTRL+Key_Left );
  forwardId = go->insertItem( icon_forward,
                              tr("&Forward"), _browser, SLOT( forward() ),
                              CTRL+Key_Right );
  go->insertItem( icon_home, tr("&Home"), _browser, SLOT( home() ) );

  menuBar()->insertItem( tr("&Go"), go );
  
  //Tool Bar
  QToolBar* toolbar = new QToolBar( this );
  addToolBar( toolbar, "Toolbar");

  QToolButton* button;
  
  button = new QToolButton( icon_back, tr("Backward"), "",
                            _browser, SLOT(backward()), toolbar );

  connect( _browser, SIGNAL( backwardAvailable(bool) ),
           button, SLOT( setEnabled(bool) ) );

  button->setEnabled( FALSE );

  button = new QToolButton( icon_forward, tr("Forward"), "",
                            _browser, SLOT(forward()),
                            toolbar );

  connect( _browser, SIGNAL( forwardAvailable(bool) ),
           button, SLOT( setEnabled(bool) ) );

  button->setEnabled( FALSE );
  
  button = new QToolButton( icon_home, tr("Home"), "", _browser, SLOT(home()), toolbar );

  
//   QFile file( home ); // Read the text from a file
//   if ( file.open( IO_ReadOnly ) )
//   {
//     QTextStream stream( &file );
//     _browser->setText( stream.read() );
//   }

//   file.close();

  setCentralWidget( _browser);
  resize(620, 700);
}

void
HelpWindow::sourceChanged( const QString& url)
{
}

void
HelpWindow::redirection( const QString& url )
{
  
  QFile file( url ); // Read the text from a file
  if ( file.open( IO_ReadOnly ) )
  {
    QTextStream stream( &file );
    _browser->setText( stream.read() );
  }
  file.close();
}


void
HelpWindow::setBackwardAvailable( bool b)
{
    menuBar()->setItemEnabled( backwardId, b);
}

void
HelpWindow::setForwardAvailable( bool b)
{
    menuBar()->setItemEnabled( forwardId, b);
}
