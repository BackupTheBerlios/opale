#ifndef CLASS_CONTROLPANEL_H
#define CLASS_CONTROLPANEL_H

#include <qlayout.h>
#include <qvgroupbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qvalidator.h>
#include <qcheckbox.h>
#include <qmessagebox.h>

/******************************************************
 *  allow the user to specifies his parameters
 *
 ******************************************************/
class ControlPanel : public QWidget
{
  Q_OBJECT
  
  private:

  QBoxLayout* _layout; /**extern widget*/
  
  QGroupBox*  _discretizeBox; /**extern widget*/
  QGroupBox*  _cylinderBox; /**extern widget*/


  QLineEdit*   _wayTF; /**textfield*/
  QLineEdit*   _sectionTF; /**textfield*/

  QLineEdit*   _scaleSectionTF; /**textfield*/
  QLineEdit*   _scaleWayTF; /**textfield*/

  QCheckBox*  _torsionBox; /**checkbox*/
  
  QIntValidator*    _wayValidator; 
  QIntValidator*    _sectionValidator;

  QDoubleValidator* _scaleValidator;


  int _nWay ; /**user's discretization parameter for the Way*/
  int _nSection; /**user's discretization parameter for the Section*/

  double _scaleFactorSection; /**user's scale parameter for the Section*/
  double _scaleFactorWay; /**user's scale parameter for the Way*/
  
  bool   _torsionEnabled; /**user's torsion parameter*/
  
  public:

  /**************************************************************
   *
   *  ControlPanel constructor
   *  @param parent the parent widget
   *
   *************************************************************/
  ControlPanel(QWidget* parent);

  /**************************************************************
   *
   *  ControlPanel destructor
   *
   *************************************************************/
  ~ControlPanel();

  /**************************************************************
   *
   *  returns the discretization value for the way
   *  @return the value for discretization
   *
   *************************************************************/
  int wayDiscretizeValue();

  /**************************************************************
   *
   *  returns the discretization value for the section
   *  @return the value for discretization
   *
   *************************************************************/
  int sectionDiscretizeValue();

  /**************************************************************
   *
   *  returns the scale factor for the section
   *  @return the scale factor
   *
   *************************************************************/
  double scaleFactorSection();

  /**************************************************************
   *
   *  returns the scale factor for the way
   *  @return the scale factor
   *
   *************************************************************/
  double scaleFactorWay();
  
  /**************************************************************
   *
   *  define if the torsion is correct
   *  @return the number of curves
   *
   *************************************************************/
  bool isTorsionEnabled() const;

  /**************************************************************
   *
   *  define if the way value is correct
   *  @return true if correct, false else
   *
   *************************************************************/
  bool controlWayValue();

  /**************************************************************
   *
   *  define if the section is correct
   *  @return true if correct, false else
   *
   *************************************************************/
  bool controlSectionValue();

  /**************************************************************
   *
   *  define if the scale section value is correct
   *  @return true if correct, false else
   *
   *************************************************************/
  bool controlScaleSectionValue();
  
  /**************************************************************
   *
   *  define if the scale way value is correct
   *  @return true if correct, false else
   *
   *************************************************************/
  bool controlScaleWayValue();
  
  
  private:
  
};


#endif

