#include <QDebug>
#include "OutputDataModel.hpp"

OutputDataModel::OutputDataModel() :
	m_dataType(GenericData().type())
{ }

void OutputDataModel::save(Properties &p) const
{
	p.put("model_name", name());
	p.put("data_type_id", m_dataType.id);
	p.put("data_type_name", m_dataType.name);
	p.put("data_type_color", m_dataType.color);
}

void OutputDataModel::restore(const Properties &p)
{
	m_dataType = NodeDataType{p.values().find("data_type_id").value().toString(), p.values().find("data_type_name").value().toString(), p.values().find("data_type_color").value().value<QColor>()};
}

unsigned int OutputDataModel::nPorts(PortType portType) const
{
	unsigned int result = 0;

	switch (portType)
	{
		case PortType::In:
			result = 1;
			break;

		default:
			break;
	}

	return result;
}

NodeDataType OutputDataModel::dataType(PortType, PortIndex) const
{
	return m_dataType;
}
