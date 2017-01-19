#include <QtGui/QDoubleValidator>

#include "TriangularPrismPrimitiveDataModel.hpp"

TriangularPrismPrimitiveDataModel::TriangularPrismPrimitiveDataModel() :
	m_color(Vec4f("0.6", "0.6", "0.6", "1.0")),
	m_l(new QLineEdit()),
	m_height(new QLineEdit())
{
	auto d = new QDoubleValidator();
	d->setLocale(QLocale("en_GB"));

	int margin = 12;
	int x = 0, y = 0;
	int w = m_l->sizeHint().width()/3;
	int h = m_l->sizeHint().height();

	m_l->setValidator(d);
	m_l->setMaximumSize(m_l->sizeHint());
	m_l->setGeometry(x, y, w, h);
	m_l->setText("1.0");
	connect(m_l, &QLineEdit::textChanged, this, &TriangularPrismPrimitiveDataModel::sizeEdit);

	m_height->setValidator(d);
	m_height->setMaximumSize(m_height->sizeHint());
	m_height->setGeometry(x, y + h + margin, w, h);
	m_height->setText("1.0");
	connect(m_height, &QLineEdit::textChanged, this, &TriangularPrismPrimitiveDataModel::sizeEdit);
}

void TriangularPrismPrimitiveDataModel::save(Properties &p) const
{
  p.put("model_name", name());
	p.put("length", m_l->text());
	p.put("height", m_height->text());
}

void TriangularPrismPrimitiveDataModel::restore(const Properties &p)
{
	m_l->setText(p.values().find("length").value().toString());
	m_height->setText(p.values().find("height").value().toString());
}

void TriangularPrismPrimitiveDataModel::sizeEdit(QString const)
{
	emit dataUpdated(0);
}

unsigned int TriangularPrismPrimitiveDataModel::nPorts(PortType portType) const
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

NodeDataType TriangularPrismPrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch (portType)
	{
		case PortType::In:
			switch(portIndex)
			{
				case 0:
					return NodeDataType{"Scalar", "Height", Qt::red};
				break;
				case 1:
					return NodeDataType{"Scalar", "Length", Qt::red};
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

std::shared_ptr<NodeData> TriangularPrismPrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void TriangularPrismPrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
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
			m_l->setVisible(false);
			m_l->setText(scalar->value().c_str());
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
	m_l->setVisible(true);
	m_l->text().toFloat(&valid);
	if(!valid)
		m_l->setText("1.0");

	m_height->setVisible(true);
	m_height->text().toFloat(&valid);
	if(!valid)
		m_height->setText("1.0");
}

void TriangularPrismPrimitiveDataModel::setTransform(const Mat4f &_t)
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

std::vector<QWidget *> TriangularPrismPrimitiveDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_l, m_height};
}

std::string TriangularPrismPrimitiveDataModel::getShaderCode()
{
	if(m_transform == "")
		return "sdTriPrism(_position, vec2(" + m_l->text().toStdString() + ", " + m_height->text().toStdString() + "), vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
	else
		return "sdTriPrism(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec2(1.0, 2.0), vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
}
