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
#include <qmainwindow.h>

//class HelpWindow : public QVBox
class HelpWindow : public QMainWindow
{
  Q_OBJECT
  
  private:
  QTextBrowser* _browser;
  
  
  public:
  HelpWindow(const QString& home);

  public slots:

  void sourceChanged( const QString& url );
  
  void redirection( const QString& url );

  void forward();

  void backward();
  
  
};

#endif
