#include "ColorPickerDataModel.hpp"
#include <QColorDialog>
#include <QEvent>


ColorPickerDataModel::ColorPickerDataModel()
  : _label(new QLabel("Select Color")),
    m_r(0),
    m_g(0),
    m_b(0)
{
  _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);


  QFont f = _label->font();
  f.setBold(true);

  _label->setFont(f);
  _label->setFixedSize(100, 100);
  _label->installEventFilter(this);
  current_color = QColor(m_r, m_g, m_b);
  label_color = QColor(255,255,255);

  m_palColor = _label->palette();
  m_palColor.setColor(_label->backgroundRole(), current_color);
  m_palColor.setColor(_label->foregroundRole(), Qt::white);
  _label->setPalette(m_palColor);

//  QPalette palette = _label->palette();
//  palette.setColor(_label->backgroundRole(), m_color.onColor(current_color));
// palette.setColor(_label->foregroundRole(), current_color);
//  _label->setPalette(palette);

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

void ColorPickerDataModel::setPalColor()
{
    m_palColor = _label->palette();
    m_palColor.setColor(_label->backgroundRole(), current_color);
    _label->setPalette(m_palColor);
    if(current_color == QColor(255,255,255))
    {
      std::cout << "Owwww" << "\n";
      m_palColor.setColor(_label->foregroundRole(), Qt::black);
      _label->setPalette(m_palColor);
    }
    else
    {
      m_palColor.setColor(_label->foregroundRole(), Qt::white);
      _label->setPalette(m_palColor);
    }
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
      result = 0;
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
    if (event->type() == QEvent::MouseButtonPress && object == _label)
    {
     setColor();
     setPalColor();
     return true;
    }
  return false;
}


NodeDataType ColorPickerDataModel::dataType(PortType portType, PortIndex portIndex) const
{
    return DistanceFieldOutput().type();
}

std::shared_ptr<NodeData> ColorPickerDataModel::outData(PortIndex)
{

}


std::vector<QWidget *> ColorPickerDataModel::embeddedWidget()
{
  return std::vector<QWidget *>{_label};
}

std::string ColorPickerDataModel::getShaderCode()
{
   return "";
}
