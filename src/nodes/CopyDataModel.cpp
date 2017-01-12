#include <QtGui/QIntValidator>
#include "CopyDataModel.hpp"

CopyDataModel::CopyDataModel() :
	m_cp(new QLineEdit)
{
	int margin = 12;
	int y = 0, x = 0;
	int w = m_cp->sizeHint().width()/2;
	int h = m_cp->sizeHint().height();

	auto d = new QIntValidator;
	d->setLocale(QLocale("en_GB"));
	m_cp->setValidator(d);
	m_cp->setMaximumSize(m_cp->sizeHint());
	m_cp->setGeometry(x, y + h + margin, w, h);
	connect(m_cp, &QLineEdit::textChanged, this, &CopyDataModel::valueEdit);

	m_cp->setText("1");
}

void CopyDataModel::save(Properties &p) const
{
	p.put("model_name", name());
}

void CopyDataModel::valueEdit(QString const)
{
	emit dataUpdated(0);
}

unsigned int CopyDataModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
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

NodeDataType CopyDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch (portType)
	{
		case PortType::In:
			switch(portIndex)
			{
				case 0:
					return DistanceFieldInput().type();
				break;
				case 1:
					return ScalarData("Num", "0.0").type();
				break;
			}
		break;
		case PortType::Out:
			return DistanceFieldInput().type();
		break;

		default:
			break;
	}
	return DistanceFieldInput().type();
}

void CopyDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex)
{
	auto data = std::dynamic_pointer_cast<ScalarData>(_data);
	if(data)
	{
		m_cp->setVisible(false);
		m_cp->setText(data->value().c_str());
		return;
	}
	m_cp->setVisible(true);
	m_cp->setText("1");
}
