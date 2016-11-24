#include <QtGui/QDoubleValidator>
#include <iostream>
#include "MathsDataModels.hpp"

// **********************************************
//	SCALAR
// **********************************************
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
	connect(m_value, &QLineEdit::textChanged, this, &ScalarDataModel::valueEdit);

	m_value->setText("0.0");
}

void ScalarDataModel::valueEdit(QString const)
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

// **********************************************
//	VECTOR
// **********************************************
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
	connect(m_x, &QLineEdit::textChanged, this, &VectorDataModel::valueEdit);

	m_x->setText("0.0");

	d = new QDoubleValidator;
	d->setLocale(QLocale("en_GB"));
	m_y->setValidator(d);
	m_y->setMaximumSize(m_y->sizeHint());
	m_y->setGeometry(x, y + h + margin, w, h);
	connect(m_y, &QLineEdit::textChanged, this, &VectorDataModel::valueEdit);

	m_y->setText("0.0");

	d = new QDoubleValidator;
	d->setLocale(QLocale("en_GB"));
	m_z->setValidator(d);
	m_z->setMaximumSize(m_z->sizeHint());
	m_z->setGeometry(x, y + (h + margin)*2, w, h);
	connect(m_z, &QLineEdit::textChanged, this, &VectorDataModel::valueEdit);

	m_z->setText("0.0");
}

void VectorDataModel::valueEdit(QString const)
{
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


// **********************************************
//	SINE
// **********************************************
SineDataModel::SineDataModel() :
	m_v(nullptr),
	m_value(new QLineEdit())
{
	int y = 0, x = 0;
	int w = m_value->sizeHint().width()/2;
	int h = m_value->sizeHint().height();

	auto d = new QDoubleValidator;
	d->setLocale(QLocale("en_GB"));
	m_value->setValidator(d);
	m_value->setMaximumSize(m_value->sizeHint());
	m_value->setGeometry(x, y, w, h);
	m_value->setContentsMargins(0, 0, 0, 0);
	connect(m_value, &QLineEdit::textChanged, this, &SineDataModel::valueEdit);

	m_value->setText("0.0");
}

void SineDataModel::valueEdit(QString const)
{
	m_v = std::make_shared<ScalarData>(boost::lexical_cast<std::string>("sin(" + m_value->text().toStdString() + ")"));
	emit dataUpdated(0);
}

unsigned int SineDataModel::nPorts(PortType portType) const
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

NodeDataType SineDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch(portType) {
		case PortType::In:
			return NodeDataType{"Scalar", " "};
		break;
		case PortType::Out:
			return ScalarData().type();
		break;
		default:
			break;
	}
	return ScalarData().type();
}

std::shared_ptr<NodeData> SineDataModel::outData(PortIndex)
{
	if(m_v)
		return m_v;
	else
		return nullptr;
}

void SineDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
{
	auto data = std::dynamic_pointer_cast<ScalarData>(_data);
	if(data) {
		m_value->setVisible(false);
		m_value->setText(data->value().c_str());
	} else {
		m_value->setVisible(true);
		m_value->setText("0.0");
	}
}

std::vector<QWidget *> SineDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_value};
}


// **********************************************
//	COSINE
// **********************************************
CosineDataModel::CosineDataModel() :
	m_v(nullptr),
	m_value(new QLineEdit())
{
	int y = 0, x = 0;
	int w = m_value->sizeHint().width()/2;
	int h = m_value->sizeHint().height();

	auto d = new QDoubleValidator;
	d->setLocale(QLocale("en_GB"));
	m_value->setValidator(d);
	m_value->setMaximumSize(m_value->sizeHint());
	m_value->setGeometry(x, y, w, h);
	m_value->setContentsMargins(0, 0, 0, 0);
	connect(m_value, &QLineEdit::textChanged, this, &CosineDataModel::valueEdit);

	m_value->setText("0.0");
}

void CosineDataModel::valueEdit(QString const)
{
	m_v = std::make_shared<ScalarData>(boost::lexical_cast<std::string>("cos(" + m_value->text().toStdString() + ")"));
	emit dataUpdated(0);
}

unsigned int CosineDataModel::nPorts(PortType portType) const
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

NodeDataType CosineDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch(portType) {
		case PortType::In:
			return NodeDataType{"Scalar", " "};
		break;
		case PortType::Out:
			return ScalarData().type();
		break;
		default:
			break;
	}
	return ScalarData().type();
}

std::shared_ptr<NodeData> CosineDataModel::outData(PortIndex)
{
	if(m_v)
		return m_v;
	else
		return nullptr;
}

void CosineDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
{
	auto data = std::dynamic_pointer_cast<ScalarData>(_data);
	if(data) {
		m_value->setVisible(false);
		m_value->setText(data->value().c_str());
	} else {
		m_value->setVisible(true);
		m_value->setText("0.0");
	}
}

std::vector<QWidget *> CosineDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_value};
}

// **********************************************
//	MULTIPLY
// **********************************************
MultiplyDataModel::MultiplyDataModel() :
	m_v(nullptr),
	m_x(new QLineEdit()),
	m_y(new QLineEdit())
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
	connect(m_x, &QLineEdit::textChanged, this, &MultiplyDataModel::valueEdit);

	m_x->setText("0.0");

	d = new QDoubleValidator;
	d->setLocale(QLocale("en_GB"));
	m_y->setValidator(d);
	m_y->setMaximumSize(m_y->sizeHint());
	m_y->setGeometry(x, y + h + margin, w, h);
	connect(m_y, &QLineEdit::textChanged, this, &MultiplyDataModel::valueEdit);

	m_y->setText("0.0");
}

void MultiplyDataModel::valueEdit(QString const)
{
	m_v = std::make_shared<ScalarData>(std::string(m_x->text().toStdString() + "*" + m_y->text().toStdString()));
	emit dataUpdated(0);
}

unsigned int MultiplyDataModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 2;
			break;

		case PortType::Out:
			result = 1;

		default:
			break;
	}

	return result;
}

NodeDataType MultiplyDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch(portType) {
		case PortType::In:
			switch(portIndex)
			{
				case 0:
					return NodeDataType{"Scalar", " "};
				break;
				case 1:
					return NodeDataType{"Scalar", " "};
				break;
			}
		break;
		case PortType::Out:
			return ScalarData().type();
		break;
		default:
			break;
	}
	return ScalarData().type();
}

std::shared_ptr<NodeData> MultiplyDataModel::outData(PortIndex)
{
	if(m_v)
		return m_v;
	else
		return nullptr;
}

void MultiplyDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
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

std::vector<QWidget *> MultiplyDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_x, m_y};
}
