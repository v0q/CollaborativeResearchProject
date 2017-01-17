#include <QtGui/QDoubleValidator>
#include "CapsulePrimitiveDataModel.hpp"

CapsulePrimitiveDataModel::CapsulePrimitiveDataModel() :
	m_color(Vec4f("0.6", "0.6", "0.6", "1.0")),
	m_r(new QLineEdit())
{
	auto d = new QDoubleValidator();
	d->setLocale(QLocale("en_GB"));

	int x = 0, y = 0;
	int w = m_r->sizeHint().width()/3;
	int h = m_r->sizeHint().height();

	m_r->setValidator(d);
	m_r->setMaximumSize(m_r->sizeHint());
	m_r->setGeometry(x, y, w, h);
	m_r->setText("1.0");
	connect(m_r, &QLineEdit::textChanged, this, &CapsulePrimitiveDataModel::sizeEdit);
}

void CapsulePrimitiveDataModel::save(Properties &p) const
{
  p.put("model_name", name());
	p.put("radius", m_r->text());
}

void CapsulePrimitiveDataModel::restore(const Properties &p)
{
	m_r->setText(p.values().find("radius").value().toString());
}

void CapsulePrimitiveDataModel::sizeEdit(QString const)
{
	emit dataUpdated(0);
}

unsigned int CapsulePrimitiveDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
			result = 4;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}

NodeDataType CapsulePrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
			switch(portIndex)
			{
				case 0:
					return NodeDataType{"Scalar", "Radius", Qt::red};
				break;
				case 1:
					return VectorData("Start").type();
				break;
				case 2:
					return VectorData("End").type();
				break;
				case 3:
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

std::shared_ptr<NodeData> CapsulePrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void CapsulePrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex _portIndex)
{
  auto data = std::dynamic_pointer_cast<ColorData>(_data);
  if(data) {
    m_color = data->color();
		return;
  }
	auto vecdata = std::dynamic_pointer_cast<VectorData>(_data);
	if(vecdata) {
		if(_portIndex == 1)
		{
			m_startPos = vecdata->vector();
			return;
		}
		else if(_portIndex == 2)
		{
			m_endPos = vecdata->vector();
			return;
		}
	}
	auto szdata = std::dynamic_pointer_cast<ScalarData>(_data);
	if(szdata) {
		m_r->setVisible(false);
		m_r->setText(szdata->value().c_str());
		return;
	}

	m_color = Vec4f("0.6", "0.6", "0.6", "1.0");
	m_startPos = Vec4f();
	m_endPos = Vec4f();

	bool valid;
	m_r->setVisible(true);
	m_r->text().toFloat(&valid);
	if(!valid)
		m_r->setText("1.0");
}

void CapsulePrimitiveDataModel::setTransform(const Mat4f &_t)
{
	std::ostringstream ss;
	if(Mat4f() == _t) {
		m_transform = "";
		return;
	}
	for(int y = 0; y < 4; ++y)
	{
		for(int x = 0; x < 4; ++x)
		{
			if(x || y)
				ss << ", ";
			ss << hsitho::Expressions::evaluate(_t.matrix(x, y), "", m_copyNum);
		}
	}
	m_transform = "mat4x4(" + ss.str() + ")";
}

std::vector<QWidget *> CapsulePrimitiveDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_r};
}

std::string CapsulePrimitiveDataModel::getShaderCode()
{
  if(m_transform == "")
		return "sdCapsule(_position, vec3(" + m_startPos.m_x + ", " + m_startPos.m_y + ", " + m_startPos.m_z + "), vec3(" + m_endPos.m_x + ", " + m_endPos.m_y + ", " + m_endPos.m_z + "), " + m_r->text().toStdString() + ",  vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
	else
		return "sdCapsule(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec3(" + m_startPos.m_x + ", " + m_startPos.m_y + ", " + m_startPos.m_z + "), vec3(" + m_endPos.m_x + ", " + m_endPos.m_y + ", " + m_endPos.m_z + "), " + m_r->text().toStdString() + ",  vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
}
