#ifndef CLASS_HELPWINDOW_H
#define CLASS_HELPWINDOW_H

#include <iostream>

#include <qframe.h>
#include <qtextbrowser.h>
#include <qfile.h>
#include <qvbox.h>
#include <qmime.h>
#include <qstylesheet.h>


class HelpWindow : public QVBox
{
  Q_OBJECT
  
  private:
  QTextBrowser* _browser;
  
  
  public:
  HelpWindow(const QString& home);

  public slots:

  void sourceChanged( const QString& url );
  
  void redirection( const QString& url );
  
  
};

#endif
