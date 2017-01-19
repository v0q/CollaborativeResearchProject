#include <QtGui/QDoubleValidator>

#include "HexagonalPrismPrimitiveDataModel.hpp"

HexagonalPrismPrimitiveDataModel::HexagonalPrismPrimitiveDataModel() :
	m_color(Vec4f("0.6", "0.6", "0.6", "1.0")),
	m_r(new QLineEdit()),
	m_height(new QLineEdit())
{
	auto d = new QDoubleValidator();
	d->setLocale(QLocale("en_GB"));

	int margin = 12;
	int x = 0, y = 0;
	int w = m_r->sizeHint().width()/3;
	int h = m_r->sizeHint().height();

	m_r->setValidator(d);
	m_r->setMaximumSize(m_r->sizeHint());
	m_r->setGeometry(x, y, w, h);
	m_r->setText("1.0");
	connect(m_r, &QLineEdit::textChanged, this, &HexagonalPrismPrimitiveDataModel::sizeEdit);

	m_height->setValidator(d);
	m_height->setMaximumSize(m_height->sizeHint());
	m_height->setGeometry(x, y + h + margin, w, h);
	m_height->setText("1.0");
	connect(m_height, &QLineEdit::textChanged, this, &HexagonalPrismPrimitiveDataModel::sizeEdit);
}

void HexagonalPrismPrimitiveDataModel::save(Properties &p) const
{
	p.put("model_name", name());
	p.put("radius", m_r->text());
	p.put("height", m_height->text());
}

void HexagonalPrismPrimitiveDataModel::restore(const Properties &p)
{
	m_r->setText(p.values().find("radius").value().toString());
	m_height->setText(p.values().find("height").value().toString());
}

void HexagonalPrismPrimitiveDataModel::sizeEdit(QString const)
{
	emit dataUpdated(0);
}

unsigned int HexagonalPrismPrimitiveDataModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 3;
		break;

		case PortType::Out:
			result = 1;
		break;

		default:
			break;
	}

	return result;
}

NodeDataType HexagonalPrismPrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
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
					return NodeDataType{"Scalar", "Height", Qt::red};
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

std::shared_ptr<NodeData> HexagonalPrismPrimitiveDataModel::outData(PortIndex port)
{
	return nullptr;
}

void HexagonalPrismPrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
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
			m_r->setVisible(false);
			m_r->setText(scalar->value().c_str());
			return;
		}
		else if(portIndex == 1)
		{
			m_height->setVisible(false);
			m_height->setText(scalar->value().c_str());
			return;
		}
	}
	m_color = Vec4f("0.6", "0.6", "0.6", "1.0");

	bool valid;
	m_r->setVisible(true);
	m_r->text().toFloat(&valid);
	if(!valid)
		m_r->setText("1.0");

	m_height->setVisible(true);
	m_height->text().toFloat(&valid);
	if(!valid)
		m_height->setText("1.0");
}

void HexagonalPrismPrimitiveDataModel::setTransform(const Mat4f &_t)
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

std::vector<QWidget *> HexagonalPrismPrimitiveDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string HexagonalPrismPrimitiveDataModel::getShaderCode()
{
  if(m_transform == "")
		return "sdHexPrism(_position, vec2(" + m_r->text().toStdString() + ", " + m_height->text().toStdString() + "), vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
	else
		return "sdHexPrism(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec2(" + m_r->text().toStdString() + ", " + m_height->text().toStdString() + "), vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
}
