#include <QtGui/QDoubleValidator>
#include <iostream>
#include "VectorDataModel.hpp"

VectorDataModel::VectorDataModel() :
	m_v(nullptr),
	m_x(new QLineEdit()),
	m_y(new QLineEdit()),
	m_z(new QLineEdit())
{
	int margin = 4;
	int y = 0, x = 0;
	int w = (m_x->sizeHint().width()*1.5)/3;
	int h = m_x->sizeHint().height();

	m_x->setValidator(new QDoubleValidator);
	m_x->setMaximumSize(m_x->sizeHint());
	m_x->setGeometry(x, y, w, h);
	connect(m_x, &QLineEdit::textChanged, this, &VectorDataModel::vectorEdit);

	m_x->setText("0.0");


	m_y->setValidator(new QDoubleValidator);
	m_y->setMaximumSize(m_y->sizeHint());
	m_y->setGeometry(x + w + margin, y, w, h);
	connect(m_y, &QLineEdit::textChanged, this, &VectorDataModel::vectorEdit);

	m_y->setText("0.0");


	m_z->setValidator(new QDoubleValidator);
	m_z->setMaximumSize(m_z->sizeHint());
	m_z->setGeometry(x + (w + margin)*2, y, w, h);
	connect(m_z, &QLineEdit::textChanged, this, &VectorDataModel::vectorEdit);

	m_z->setText("0.0");
}

void VectorDataModel::vectorEdit(QString const)
{
	bool valid = false;

	float x = m_x->text().toFloat(&valid);
	if(!valid) {
		emit dataInvalidated(0);
		return;
	}

	float y = m_y->text().toFloat(&valid);
	if(!valid) {
		emit dataInvalidated(0);
		return;
	}

	float z = m_z->text().toFloat(&valid);
	if(!valid) {
		emit dataInvalidated(0);
		return;
	}

	m_v = std::make_shared<VectorData>(x, y, z);
	emit dataUpdated(0);
}

unsigned int VectorDataModel::nPorts(PortType portType) const
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

NodeDataType VectorDataModel::dataType(PortType, PortIndex) const
{
	return VectorData().type();
}

std::shared_ptr<NodeData> VectorDataModel::outData(PortIndex)
{
	if(m_v)
		return m_v;
	else
		return nullptr;
}

std::vector<QWidget *> VectorDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_x, m_y, m_z};
}

std::string VectorDataModel::getShaderCode() {
	return "";
}
