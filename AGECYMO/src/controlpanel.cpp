#include "controlpanel.hpp"


const QString DISCRETIZE_BOX_NAME = QString("Discretization Parameters ");
const QString CYLINDER_BOX_NAME   = QString("Cylinder Parameters ");

const QString WAY_LABEL     = QString("Way");
const QString SECTION_LABEL = QString("Section");
const QString TORSION_LABEL = QString("Torsion");
const QString SCALE_LABEL   = QString("Scale");


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


ControlPanel::ControlPanel(QWidget* parent)
    : QWidget(parent, "Control Panel"),
      _nWay(10),
      _nSection(10),
      _scaleFactor(1.0),
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

  //Signal connection
//   connect ( _wayTF, SIGNAL( textChanged(const QString&) ),
//             this, SLOT( validateWay(const QString&) ) );
  
  connect ( _wayTF, SIGNAL( lostFocus() ),
            this, SLOT( validateWay() ) );
  
  
  QLabel* section = new QLabel( SECTION_LABEL, _discretizeBox);
  _sectionTF = new QLineEdit( _discretizeBox );
  _sectionTF->setFixedSize(80, 20);
  _sectionValidator = new QIntValidator(SECTION_MIN_VALUE, SECTION_MAX_VALUE, this);
  _sectionTF->setValidator( _sectionValidator ) ;
  _sectionTF->validateAndSet( SECTION_INIT, 0, 0, 0);
  
  connect ( _sectionTF, SIGNAL( lostFocus() ),
            this, SLOT( validateSection() ) );

  QLabel* torsion = new QLabel( TORSION_LABEL, _cylinderBox);
  _torsionBox = new QCheckBox( _cylinderBox);

  
  QLabel* scale = new QLabel( SCALE_LABEL, _cylinderBox);

  _scaleTF   = new QLineEdit( _cylinderBox );
  _scaleTF->setFixedSize(80, 20);

  _scaleValidator = new QDoubleValidator(SCALE_MIN_VALUE,
                                         SCALE_MAX_VALUE,
                                         SCALE_PRECISION, _cylinderBox);

  _scaleTF->setValidator( _scaleValidator);
  _scaleTF->validateAndSet( SCALE_INIT, 0, 0, 0);
  
  connect ( _scaleTF, SIGNAL( lostFocus() ),
            this, SLOT( validateScale() ) );
  
  _layout->addWidget( _discretizeBox);
  _layout->addWidget( _cylinderBox);
  
}

ControlPanel::~ControlPanel()
{
}



//accessors
int
ControlPanel::wayDiscretizeValue() 
{
  return _nWay;
}

int
ControlPanel::sectionDiscretizeValue() 
{
  return _nSection;
}


double
ControlPanel::scaleFactor() 
{
  return _scaleFactor;
}


bool
ControlPanel::isTorsionEnabled() const
{
  return _torsionEnabled;
}
// end of accessors

//private slots
//ControlPanel::validateWay(const QString& text)
void
ControlPanel::validateWay()
{
  qDebug("dans validateWay");
  
  QString s = _wayTF->text();
  int zero = 0;
  QValidator::State isValid = _wayValidator->validate( s, zero);
    
  if (isValid != QValidator::Acceptable)
  {
    QMessageBox::warning( this, "Wrong value for the Way",
                          "Wrong value for the way discretization paremeter\n Parameter must be between 2 and 1 million.");

    _wayTF->setText(QString(""));
    _wayTF->setFocus();
  }
  else
  {
    //TODO : mettre a jour _nWay
    _nWay = s.toInt();
    qDebug(" nWay  = %d ", _nWay);
  }
  
}

void
ControlPanel::validateSection()
{
  
  qDebug("dans validate Section");
  
  QString s = _sectionTF->text();
  int zero = 0;
  QValidator::State isValid = _sectionValidator->validate( s, zero);
    
  if (isValid != QValidator::Acceptable)
  {
    QMessageBox::warning( this, "Wrong value for the section",
                          "Wrong value for the section discretization paremeter\n Parameter must be between 3 and 1 million.");

    _sectionTF->setText(QString(""));
    _sectionTF->setFocus();
  }
  else
  {
    //TODO : mettre a jour _nWay
    _nSection = s.toInt();
    qDebug(" nSection  = %d ", _nSection);
  }

}


void
ControlPanel::validateScale()
{
  qDebug("dans validate scale");
  
  QString s = _scaleTF->text();
  int zero = 0;
  QValidator::State isValid = _scaleValidator->validate( s, zero);
    
  if (isValid != QValidator::Acceptable)
  {
    QMessageBox::warning( this,
                          "Wrong value for the scale factor",
                          "Wrong value !!!");

    _scaleTF->setText(QString(""));
    _scaleTF->setFocus();
  }
  else
  {
    //TODO : mettre a jour _nWay
    _scaleFactor = s.toDouble();
    qDebug(" scale  = %f ", _scaleFactor);
  }
  
}

void
ControlPanel::validateAll()
{
  validateWay();
  validateSection();
  validateScale();
}


