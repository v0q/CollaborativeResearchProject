#include <QtGui/QDoubleValidator>
#include <iostream>
#include "ScalarDataModel.hpp"

ScalarDataModel::ScalarDataModel() :
	m_v(nullptr),
	m_value(new QLineEdit())
{
	int y = 0, x = 0;
	int w = m_value->sizeHint().width()/2;
	int h = m_value->sizeHint().height();

	m_value->setValidator(new QDoubleValidator);
	m_value->setMaximumSize(m_value->sizeHint());
	m_value->setGeometry(x, y, w, h);
	m_value->setContentsMargins(0, 0, 0, 0);
	connect(m_value, &QLineEdit::textChanged, this, &ScalarDataModel::vectorEdit);

	m_value->setText("0.0");
}

void ScalarDataModel::vectorEdit(QString const)
{
	bool valid = false;

	float value = m_value->text().toFloat(&valid);
	if(!valid) {
		emit dataInvalidated(0);
		return;
	}

	m_v = std::make_shared<ScalarData>(boost::lexical_cast<std::string>(value));
	emit dataUpdated(0);
}

unsigned int ScalarDataModel::nPorts(PortType portType) const
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

NodeDataType ScalarDataModel::dataType(PortType, PortIndex) const
{
	return ScalarData().type();
}

std::shared_ptr<NodeData> ScalarDataModel::outData(PortIndex)
{
	if(m_v)
		return m_v;
	else
		return nullptr;
}

std::vector<QWidget *> ScalarDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_value};
}

std::string ScalarDataModel::getShaderCode() {
	return "";
}
