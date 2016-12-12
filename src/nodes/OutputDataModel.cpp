#include "OutputDataModel.hpp"

OutputDataModel::OutputDataModel() :
	m_dataType(GenericData().type())
{ }

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
