#include <QColorDialog>
#include <QtGui/QDoubleValidator>
#include <QEvent>

#include "ColorPickerDataModel.hpp"
#include "ExpressionEvaluator.hpp"

ColorPickerDataModel::ColorPickerDataModel()
  : _label(new QLabel("Select Color")),
    m_x(new QLineEdit()),
    m_y(new QLineEdit()),
    m_z(new QLineEdit()),
    m_margin(12),
    m_w(0),
    m_h(0),
    m_px(0),
    m_py(0),
    m_cd(nullptr)
{
  m_w = m_x->sizeHint().width()/2;
  m_h = m_x->sizeHint().height();

  auto d = new QDoubleValidator;
  d->setLocale(QLocale("en_GB"));
  m_x->setValidator(d);
  m_x->setMaximumSize(m_x->sizeHint());
  m_x->setGeometry(0, 0, m_w, m_h);
  connect(m_x, &QLineEdit::textChanged, this, &ColorPickerDataModel::colorEdit);

  m_x->setText("0.0");

  d = new QDoubleValidator;
  d->setLocale(QLocale("en_GB"));
  m_y->setValidator(d);
  m_y->setMaximumSize(m_y->sizeHint());
  m_y->setGeometry(m_w + m_margin, 0, m_w, m_h);
  connect(m_y, &QLineEdit::textChanged, this, &ColorPickerDataModel::colorEdit);

  m_y->setText("0.0");

  d = new QDoubleValidator;
  d->setLocale(QLocale("en_GB"));
  m_z->setValidator(d);
  m_z->setMaximumSize(m_z->sizeHint());
  m_z->setGeometry((m_w + m_margin)*2, 0, m_w, m_h);
  connect(m_z, &QLineEdit::textChanged, this, &ColorPickerDataModel::colorEdit);

  m_z->setText("0.0");

  _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  QFont f = _label->font();
  f.setBold(true);

  _label->setFont(f);
  _label->installEventFilter(this);
  current_color = QColor(0, 0, 0);
  label_color = QColor(255,255,255);

  m_palColor = _label->palette();
  m_palColor.setColor(_label->backgroundRole(), current_color);
  m_palColor.setColor(_label->foregroundRole(), Qt::white);

  _label->setPalette(m_palColor);
  _label->setMaximumSize(QSize(m_w*3 + m_margin*2, m_h));
  _label->setGeometry(0, m_h + m_margin, m_w*3 + m_margin*2, m_h);
}

ColorPickerDataModel::~ColorPickerDataModel()
{

}

QColor QColorPicker::onColor(QColor& current_color)
{
  QColor color = QColorDialog::getColor(current_color, this);
//  current_color = color;

  return color;
}

void ColorPickerDataModel::colorEdit(QString const &string)
{
  m_cd = std::make_shared<ColorData>(m_x->text().toStdString(),
                                     m_y->text().toStdString(),
                                     m_z->text().toStdString());
  emit dataUpdated(0);
}

void ColorPickerDataModel::setPalColor()
{
  m_palColor.setColor(_label->backgroundRole(), current_color);
  _label->setPalette(m_palColor);
  m_x->setText(QString::number(current_color.red() / 255.0));
  m_y->setText(QString::number(current_color.green() / 255.0));
  m_z->setText(QString::number(current_color.blue() / 255.0));
//  if(current_color == QColor(255,255,255))
//  {
//    m_palColor.setColor(_label->foregroundRole(), Qt::black);
//    _label->setPalette(m_palColor);
//  }
//  else
//  {
//    m_palColor.setColor(_label->foregroundRole(), Qt::white);
//    _label->setPalette(m_palColor);
//  }
}

void ColorPickerDataModel::save(Properties &p) const
{
}

unsigned int ColorPickerDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 1;
    default:
      break;
  }
  return result;
}

bool ColorPickerDataModel::eventFilter(QObject *object, QEvent *event)
{
  if(event->type() == QEvent::MouseButtonPress && object == _label && _label->text() != "")
  {
    setColor();
    setPalColor();
    return true;
  }
  return false;
}


NodeDataType ColorPickerDataModel::dataType(PortType portType, PortIndex) const
{
  switch(portType)
  {
    case PortType::In:
      return VectorData().type();
    break;
    case PortType::Out:
      return ColorData().type();
    break;
    default:
      return NodeDataType{"", ""};
    break;
  }
}

void ColorPickerDataModel::setInData(std::shared_ptr<NodeData> _data, int)
{
  auto data = std::dynamic_pointer_cast<VectorData>(_data);
  if(data) {
    m_x->setVisible(false);
    m_x->setText(QString(data->vector().m_x.c_str()));
    m_y->setVisible(false);
    m_y->setText(QString(data->vector().m_y.c_str()));
    m_z->setVisible(false);
    m_z->setText(QString(data->vector().m_z.c_str()));

    m_x->setGeometry(0, 0, 0, 0);
    m_y->setGeometry(0, 0, 0, 0);
    m_z->setGeometry(0, 0, 0, 0);
    _label->setText("");
    _label->setGeometry(m_px, m_py, m_w, m_h);
    try {
      Vec4f vec = data->vector();

      int r = hsitho::Expressions::clamp<int>((int)(boost::lexical_cast<float>(vec.m_x) * 255), 0, 255);
      int g = hsitho::Expressions::clamp<int>((int)(boost::lexical_cast<float>(vec.m_y) * 255), 0, 255);
      int b = hsitho::Expressions::clamp<int>((int)(boost::lexical_cast<float>(vec.m_z) * 255), 0, 255);
      current_color = QColor(r, g, b);
      setPalColor();
    } catch(boost::exception &) {
      current_color = QColor(0, 0, 0);
      setPalColor();
    }
  } else {
    m_x->setGeometry(m_px, m_py, m_w, m_h);
    m_y->setGeometry(m_px + m_w + m_margin, m_py, m_w, m_h);
    m_z->setGeometry(m_px + (m_w + m_margin)*2, m_py, m_w, m_h);
    _label->setGeometry(m_px, m_py + m_h + m_margin, m_w*3 + m_margin*2, m_h);

    m_x->setVisible(true);
    m_y->setVisible(true);
    m_z->setVisible(true);
    _label->setText("Select Color");
  }
}

std::shared_ptr<NodeData> ColorPickerDataModel::outData(PortIndex)
{
  return m_cd;
}

std::vector<QWidget *> ColorPickerDataModel::embeddedWidget()
{
  return std::vector<QWidget *>{m_x, m_y, m_z, _label};
}

void ColorPickerDataModel::updateWidgets()
{
  m_px = m_x->pos().x();
  m_py = m_x->pos().y();
}

std::string ColorPickerDataModel::getShaderCode()
{
   return "";
}