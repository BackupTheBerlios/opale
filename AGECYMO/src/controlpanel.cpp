#include "controlpanel.hpp"


const QString DISCRETIZE_BOX_NAME = QString("Discretization Parameters ");
const QString CYLINDER_BOX_NAME   = QString("Cylinder Parameters ");

const QString WAY_LABEL     = QString("Way");
const QString SECTION_LABEL = QString("Section");
const QString TORSION_LABEL = QString("Torsion");
const QString SCALE_LABEL   = QString("Section Scale");
const QString SCALE_WAY_LABEL   = QString("Way Scale");


//The maximum step to discretize the way curve
const int WAY_MIN_VALUE = 2;
const int WAY_MAX_VALUE = 1000000;

//The maximum step to discretize the sectio curve
const int SECTION_MIN_VALUE = 3;
const int SECTION_MAX_VALUE = 1000000;

//Scale factor constraints
const double SCALE_MIN_VALUE = 0.0000001;
const double SCALE_MAX_VALUE = 1000000.0;
const int    SCALE_PRECISION = 8;

//Default initial values

const QString WAY_INIT     = QString("10");
const QString SECTION_INIT = QString("10");
const QString SCALE_INIT  = QString("1.0");

/**************************************************************
 *
 *  ControlPanel constructor
 *  @param parent the parent widget
 *
 *************************************************************/
ControlPanel::ControlPanel(QWidget* parent)
    : QWidget(parent, "Control Panel"),
      _nWay(10),
      _nSection(10),
      _scaleFactorSection(1.0),
      _scaleFactorWay(1.0),
      _torsionEnabled(false)
{
  setMaximumWidth(170);
  
  _layout = new QVBoxLayout(this);

  _discretizeBox = new QGroupBox( 2, Qt::Horizontal, DISCRETIZE_BOX_NAME, this );
  _cylinderBox   = new QGroupBox( 2, Qt::Horizontal, CYLINDER_BOX_NAME, this );

  QLabel* way = new QLabel( WAY_LABEL, _discretizeBox);
  _wayTF     = new QLineEdit( _discretizeBox );
  _wayTF->setFixedSize( 80, 20 );

  _wayValidator = new QIntValidator(WAY_MIN_VALUE, WAY_MAX_VALUE, _discretizeBox);

  _wayTF->setValidator( _wayValidator);
  _wayTF->validateAndSet( WAY_INIT, 0, 0, 0);

  
  QLabel* section = new QLabel( SECTION_LABEL, _discretizeBox);
  _sectionTF = new QLineEdit( _discretizeBox );
  _sectionTF->setFixedSize(80, 20);
  _sectionValidator = new QIntValidator(SECTION_MIN_VALUE, SECTION_MAX_VALUE, this);
  _sectionTF->setValidator( _sectionValidator ) ;
  _sectionTF->validateAndSet( SECTION_INIT, 0, 0, 0);

  QLabel* torsion = new QLabel( TORSION_LABEL, _cylinderBox);
  _torsionBox = new QCheckBox( _cylinderBox);

  
  QLabel* scale = new QLabel( SCALE_LABEL, _cylinderBox);

  _scaleSectionTF   = new QLineEdit( _cylinderBox );
  _scaleSectionTF->setFixedSize(80, 20);

  _scaleValidator = new QDoubleValidator(SCALE_MIN_VALUE,
                                         SCALE_MAX_VALUE,
                                         SCALE_PRECISION, _cylinderBox);

  _scaleSectionTF->setValidator( _scaleValidator);
  _scaleSectionTF->validateAndSet( SCALE_INIT, 0, 0, 0);
  
  QLabel* scaleWay = new QLabel( SCALE_WAY_LABEL, _cylinderBox);

  _scaleWayTF   = new QLineEdit( _cylinderBox );
  _scaleWayTF->setFixedSize(80, 20);

  _scaleValidator = new QDoubleValidator(SCALE_MIN_VALUE,
                                         SCALE_MAX_VALUE,
                                         SCALE_PRECISION, _cylinderBox);

  _scaleWayTF->setValidator( _scaleValidator);
  _scaleWayTF->validateAndSet( SCALE_INIT, 0, 0, 0);
  
  _layout->addWidget( _discretizeBox);
  _layout->addWidget( _cylinderBox);
  
}

/**************************************************************
 *
 *  ControlPanel destructor
 *
 *************************************************************/
ControlPanel::~ControlPanel()
{
}


/**************************************************************
 *
 *  returns the discretization value for the way
 *  @return the value for discretization
 *
 *************************************************************/
int
ControlPanel::wayDiscretizeValue() 
{
  return _nWay;
}

/**************************************************************
 *
 *  returns the discretization value for the section
 *  @return the value for discretization
 *
 *************************************************************/
int
ControlPanel::sectionDiscretizeValue() 
{
  return _nSection;
}

/**************************************************************
 *
 *  returns the scale factor for the section
 *  @return the scale factor
 *
 *************************************************************/
double
ControlPanel::scaleFactorSection() 
{
  return _scaleFactorSection;
}

/**************************************************************
 *
 *  returns the scale factor for the way
 *  @return the scale factor
 *
 *************************************************************/
double
ControlPanel::scaleFactorWay() 
{
  return _scaleFactorWay;
}

/**************************************************************
 *
 *  define if the torsion is correct
 *  @return the number of curves
 *
 *************************************************************/
bool
ControlPanel::isTorsionEnabled() const
{
//return _torsionEnabled;
  return _torsionBox->isChecked();
}

/**************************************************************
 *
 *  define if the way value is correct
 *  @return true if correct, false else
 *
 *************************************************************/
bool
ControlPanel::controlWayValue()
{
  qDebug("dans controlWay value");
  
  QString s = _wayTF->text();
  int zero = 0;
  QValidator::State isValid = _wayValidator->validate( s, zero);
    
  if (isValid != QValidator::Acceptable)
  {
    QMessageBox::warning( this, "Wrong value for the Way",
                          "Wrong value for the way discretization paremeter\n Parameter must be between 2 and 1 million.");

    return false;
  }
  else
  {
    _nWay = s.toInt();
    return true;
  }

}

/**************************************************************
 *
 *  define if the section is correct
 *  @return true if correct, false else
 *
 *************************************************************/
bool
ControlPanel::controlSectionValue()
{
  QString s = _sectionTF->text();
  int zero = 0;
  QValidator::State isValid = _sectionValidator->validate( s, zero);
    
  if (isValid != QValidator::Acceptable)
  {
    QMessageBox::warning( this, "Wrong value for the section",
                          "Wrong value for the section discretization paremeter\n Parameter must be between 3 and 1 million.");

    return false;
  }
  else
  {
    _nSection = s.toInt();
    return true;
  }
}

/**************************************************************
 *
 *  define if the scale section value is correct
 *  @return true if correct, false else
 *
 *************************************************************/
bool
ControlPanel::controlScaleSectionValue()
{
  int zero = 0;

  QString s = _scaleSectionTF->text();
  QValidator::State isValid = _scaleValidator->validate( s, zero);
    
  if( isValid != QValidator::Acceptable )
  {
    QMessageBox::warning( this,
                          "Wrong value",
                          "Wrong value  for the section scale factor!!!");
    return false;
  }
  else
  {
    _scaleFactorSection = s.toDouble();
    return true;
  }
  
}

/**************************************************************
 *
 *  define if the scale way value is correct
 *  @return true if correct, false else
 *
 *************************************************************/
bool
ControlPanel::controlScaleWayValue()
{
  int zero = 0;
  
  QString s1 = _scaleWayTF->text();
  QValidator::State isValid2 = _scaleValidator->validate( s1, zero);
  if ( isValid2 != QValidator::Acceptable )
  {
    QMessageBox::warning( this,
                          "Wrong value",
                          "Wrong value  for the way scale factor!!!");
    return false;
  }
  else
  {
    _scaleFactorWay = s1.toDouble();
    return true;
  }

}

