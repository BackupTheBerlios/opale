#ifndef CLASS_HELPWINDOW_H
#define CLASS_HELPWINDOW_H

#include <iostream>

#include <qframe.h>
#include <qtextbrowser.h>
#include <qfile.h>
#include <qvbox.h>
#include <qmime.h>
#include <qstylesheet.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qiconset.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qmainwindow.h>
#include <qstringlist.h>

//class HelpWindow : public QVBox
class HelpWindow : public QMainWindow
{
  Q_OBJECT
  
  private:
  QTextBrowser* _browser;
  
  QStringList history;
  
  int backwardId, forwardId;
  
  public:
  HelpWindow(const QString& home);

  public slots:
 
 
  
  void redirection( const QString& url );

//   void forward();

//   void backward();
  
  private slots:

  void setBackwardAvailable( bool );

  void setForwardAvailable( bool );

  void sourceChanged( const QString& url ); 
};

#endif
