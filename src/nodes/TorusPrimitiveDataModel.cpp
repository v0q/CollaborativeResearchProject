#include <QtGui/QDoubleValidator>

#include "TorusPrimitiveDataModel.hpp"

TorusPrimitiveDataModel::TorusPrimitiveDataModel() :
	m_color(Vec4f("0.6", "0.6", "0.6", "1.0")),
	m_outerR(new QLineEdit),
	m_ringR(new QLineEdit)
{
	auto d = new QDoubleValidator();
	d->setLocale(QLocale("en_GB"));

	int margin = 12;
	int x = 0, y = 0;
	int w = m_outerR->sizeHint().width()/3;
	int h = m_outerR->sizeHint().height();

	m_outerR->setValidator(d);
	m_outerR->setMaximumSize(m_outerR->sizeHint());
	m_outerR->setGeometry(x, y, w, h);
	m_outerR->setText("1.0");
	connect(m_outerR, &QLineEdit::textChanged, this, &TorusPrimitiveDataModel::sizeEdit);

	m_ringR->setValidator(d);
	m_ringR->setMaximumSize(m_ringR->sizeHint());
	m_ringR->setGeometry(x, y + h + margin, w, h);
	m_ringR->setText("0.25");
	connect(m_ringR, &QLineEdit::textChanged, this, &TorusPrimitiveDataModel::sizeEdit);
}

void TorusPrimitiveDataModel::save(Properties &p) const
{
	p.put("model_name", name());
	p.put("outer_radius", m_outerR->text());
	p.put("inner_radius", m_ringR->text());
}

void TorusPrimitiveDataModel::restore(const Properties &p)
{
	m_outerR->setText(p.values().find("outer_radius").value().toString());
	m_ringR->setText(p.values().find("inner_radius").value().toString());
}

void TorusPrimitiveDataModel::sizeEdit(QString const)
{
	emit dataUpdated(0);
}

unsigned int TorusPrimitiveDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
			result = 3;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}

NodeDataType TorusPrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch (portType)
	{
		case PortType::In:
			switch(portIndex)
			{
				case 0:
					return NodeDataType{"Scalar", "Outer Radius", Qt::red};
				break;
				case 1:
					return NodeDataType{"Scalar", "Ring diam", Qt::red};
				break;
				case 2:
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

std::shared_ptr<NodeData> TorusPrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void TorusPrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
{
	auto cd = std::dynamic_pointer_cast<ColorData>(_data);
	if(cd) {
		m_color = cd->color();
		return;
	}
	auto scalar = std::dynamic_pointer_cast<ScalarData>(_data);
	if(scalar)
	{
		if(portIndex == 0)
		{
			m_outerR->setVisible(false);
			m_outerR->setText(scalar->value().c_str());
			return;
		}
		else if(portIndex == 1)
		{
			m_ringR->setVisible(false);
			m_ringR->setText(scalar->value().c_str());
			return;
		}
	}

	m_color = Vec4f("0.6", "0.6", "0.6", "1.0");

	bool valid;
	m_outerR->setVisible(true);
	m_outerR->text().toFloat(&valid);
	if(!valid)
		m_outerR->setText("1.0");

	m_ringR->setVisible(true);
	m_ringR->text().toFloat(&valid);
	if(!valid)
		m_ringR->setText("0.25");
}

void TorusPrimitiveDataModel::setTransform(const Mat4f &_t)
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

std::vector<QWidget *> TorusPrimitiveDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string TorusPrimitiveDataModel::getShaderCode()
{
  if(m_transform == "")
		return "sdTorus(_position, vec2(" + m_outerR->text().toStdString() + ", " + m_ringR->text().toStdString() + "), vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
	else
		return "sdTorus(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec2(" + m_outerR->text().toStdString() + ", " + m_ringR->text().toStdString() + "), vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
}
