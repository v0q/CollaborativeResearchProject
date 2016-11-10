#include "VectorDataModel.hpp"

VectorDataModel::VectorDataModel() :
	m_x(new QLineEdit()),
	m_y(new QLineEdit()),
	m_z(new QLineEdit())
{
	m_x->setMaximumSize(m_x->sizeHint());
	m_y->setGeometry(m_x->geometry().x(), m_y->geometry().y(), m_y->sizeHint().width()/3, m_y->sizeHint().height());
	m_x->setText("0.0");
	m_y->setMaximumSize(m_y->sizeHint());
	m_y->setGeometry(m_y->sizeHint().width()/3, m_y->geometry().y(), m_y->sizeHint().width()/3, m_y->sizeHint().height());
	m_y->setText("0.0");
	m_z->setMaximumSize(m_z->sizeHint());
	m_y->setGeometry(2*m_z->sizeHint().width()/3, m_z->geometry().y(), m_z->sizeHint().width()/3, m_y->sizeHint().height());
	m_z->setText("0.0");

//	connect(m_x, &QLineEdit::textChanged,
//					this, &NumberSourceDataModel::onTextEdited);

}

VectorDataModel::~VectorDataModel()
{
	delete m_x;
	delete m_y;
	delete m_z;
}

void VectorDataModel::save(Properties &p) const
{
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

std::shared_ptr<NodeData> VectorDataModel::outData(PortIndex port)
{
	return nullptr;
}

void VectorDataModel::setInData(std::shared_ptr<NodeData>, int)
{

}

std::vector<QWidget *> VectorDataModel::embeddedWidget()
{
	return std::vector<QWidget *>{m_x, m_y, m_z};
}

std::string VectorDataModel::getShaderCode() {
	return "";
}
