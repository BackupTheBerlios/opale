#include "helpwindow.hpp"


HelpWindow::HelpWindow(const QString& home)
    : QVBox()
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
  
  QFile file( home ); // Read the text from a file
  if ( file.open( IO_ReadOnly ) )
  {
    QTextStream stream( &file );
    _browser->setText( stream.read() );
  }

  file.close();
  
  resize(620, 700);
}
void
HelpWindow::sourceChanged( const QString& url )
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
