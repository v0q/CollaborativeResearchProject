#include <QtGui/QDoubleValidator>
#include "SpherePrimitiveDataModel.hpp"

SpherePrimitiveDataModel::SpherePrimitiveDataModel() :
	m_color(Vec4f("0.6", "0.6", "0.6", "1.0")),
  m_size(new QLineEdit)
{
  auto d = new QDoubleValidator();
  d->setLocale(QLocale("en_GB"));

  int x = 0, y = 0;
  int w = m_size->sizeHint().width()/3;
  int h = m_size->sizeHint().height();

  m_size->setValidator(d);
  m_size->setMaximumSize(m_size->sizeHint());
  m_size->setGeometry(x, y, w, h);
  m_size->setText("1.0");
  connect(m_size, &QLineEdit::textChanged, this, &SpherePrimitiveDataModel::sizeEdit);
}

void SpherePrimitiveDataModel::save(Properties &p) const
{
	p.put("model_name", name());
  p.put("size", m_size->text());
}

void SpherePrimitiveDataModel::restore(const Properties &p)
{
  m_size->setText(p.values().find("size").value().toString());
}

void SpherePrimitiveDataModel::sizeEdit(QString const)
{
  emit dataUpdated(0);
}

unsigned int SpherePrimitiveDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch(portType)
  {
    case PortType::In:
      result = 2;
    break;

    case PortType::Out:
      result = 1;
    break;

    default:
      break;
  }

  return result;
}

NodeDataType SpherePrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
{
  switch(portType)
	{
		case PortType::In:
      switch(portIndex)
      {
        case 0:
          return NodeDataType{"Scalar", "Size", Qt::red};
        break;
        case 1:
          return ColorData().type();
        break;
      }
		break;
		case PortType::Out:
			return DistanceFieldOutput().type();
		break;

		default:
			break;
	}
	return DistanceFieldOutput().type();
}

std::shared_ptr<NodeData> SpherePrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void SpherePrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, int)
{
  auto cd = std::dynamic_pointer_cast<ColorData>(_data);
  if(cd) {
    m_color = cd->color();
    return;
	}
  auto szdata = std::dynamic_pointer_cast<ScalarData>(_data);
  if(szdata) {
    m_size->setVisible(false);
    m_size->setText(szdata->value().c_str());
    return;
  }

	m_color = Vec4f("0.6", "0.6", "0.6", "1.0");

	bool valid;
  m_size->setVisible(true);
	m_size->text().toFloat(&valid);
	if(!valid)
		m_size->setText("1.0");
}

std::vector<QWidget *> SpherePrimitiveDataModel::embeddedWidget()
{
  return std::vector<QWidget *>{m_size};
}

void SpherePrimitiveDataModel::setTransform(const Mat4f &_t)
{
  std::ostringstream ss;
  for(int y = 0; y < 4; ++y)
  {
    for(int x = 0; x < 4; ++x)
    {
      if(x || y)
        ss << ", ";
      ss << _t.matrix(x, y);
    }
  }
  m_transform = "mat4x4(" + ss.str() + ")";
}

std::string SpherePrimitiveDataModel::getShaderCode()
{
	if(m_transform == "")
		return "sdSphere(_position, " + m_size->text().toStdString() + ", vec3(clamp(" + m_color.m_x + ", 0.0, 1.0), clamp(" + m_color.m_y + ", 0.0, 1.0), clamp(" + m_color.m_z + ", 0.0, 1.0)))";
	else
		return "sdSphere(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, " + m_size->text().toStdString() + ", vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
}
