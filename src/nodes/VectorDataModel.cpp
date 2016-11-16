#include <QtGui/QDoubleValidator>
#include <iostream>
#include "VectorDataModel.hpp"

VectorDataModel::VectorDataModel() :
	m_v(nullptr),
	m_x(new QLineEdit()),
	m_y(new QLineEdit()),
	m_z(new QLineEdit())
{
	int margin = 12;
	int y = 0, x = 0;
	int w = m_x->sizeHint().width()/2;
	int h = m_x->sizeHint().height();

  auto d = new QDoubleValidator;
  d->setLocale(QLocale("en_GB"));
  m_x->setValidator(d);
	m_x->setMaximumSize(m_x->sizeHint());
	m_x->setGeometry(x, y, w, h);
	connect(m_x, &QLineEdit::textChanged, this, &VectorDataModel::vectorEdit);

	m_x->setText("0.0");

  d = new QDoubleValidator;
  d->setLocale(QLocale("en_GB"));
  m_y->setValidator(d);
	m_y->setMaximumSize(m_y->sizeHint());
	m_y->setGeometry(x, y + h + margin, w, h);
	connect(m_y, &QLineEdit::textChanged, this, &VectorDataModel::vectorEdit);

	m_y->setText("0.0");

  d = new QDoubleValidator;
  d->setLocale(QLocale("en_GB"));
  m_z->setValidator(d);
	m_z->setMaximumSize(m_z->sizeHint());
	m_z->setGeometry(x, y + (h + margin)*2, w, h);
	connect(m_z, &QLineEdit::textChanged, this, &VectorDataModel::vectorEdit);

	m_z->setText("0.0");
}

void VectorDataModel::vectorEdit(QString const)
{
	bool valid = false;

//	float x = m_x->text().toFloat(&valid);
//	if(!valid) {
//		emit dataInvalidated(0);
//		return;
//	}

//	float y = m_y->text().toFloat(&valid);
//	if(!valid) {
//		emit dataInvalidated(0);
//		return;
//	}

//	float z = m_z->text().toFloat(&valid);
//	if(!valid) {
//		emit dataInvalidated(0);
//		return;
//	}

//	m_v = std::make_shared<VectorData>(boost::lexical_cast<std::string>(x),
//																		 boost::lexical_cast<std::string>(y),
//																		 boost::lexical_cast<std::string>(z));
    m_v = std::make_shared<VectorData>(m_x->text().toStdString(),
                                       m_y->text().toStdString(),
                                       m_z->text().toStdString());
	emit dataUpdated(0);
}

unsigned int VectorDataModel::nPorts(PortType portType) const
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

NodeDataType VectorDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch(portType) {
		case PortType::In:
			switch(portIndex)
			{
				case 0:
					return NodeDataType{"Scalar", "x"};
				break;
				case 1:
					return NodeDataType{"Scalar", "y"};
				break;
				case 2:
					return NodeDataType{"Scalar", "z"};
				break;
			}
		break;
		case PortType::Out:
			return VectorData().type();
		break;
		default:
			break;
	}
	return VectorData().type();
}

std::shared_ptr<NodeData> VectorDataModel::outData(PortIndex)
{
	if(m_v)
		return m_v;
	else
		return nullptr;
}

void VectorDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
{
	auto data = std::dynamic_pointer_cast<ScalarData>(_data);
	if(data) {
		m_inputs[portIndex]->setVisible(false);
		m_inputs[portIndex]->setText(data->value().c_str());
	} else {
		m_inputs[portIndex]->setVisible(true);
		m_inputs[portIndex]->setText("0.0");
	}
}

std::vector<QWidget *> VectorDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_x, m_y, m_z};
}

std::string VectorDataModel::getShaderCode() {
	return "";
}


