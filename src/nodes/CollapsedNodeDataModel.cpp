#include "CollapsedNodeDataModel.hpp"

CollapsedNodeDataModel::CollapsedNodeDataModel(const NodeDataType &_type, std::vector<std::shared_ptr<Node> > &_nodes) :
	m_nodeDataType(_type),
	m_nodes(_nodes)
{

}

void CollapsedNodeDataModel::save(Properties &p) const
{

}

unsigned int CollapsedNodeDataModel::nPorts(PortType portType) const
{
	unsigned int result = 0;

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

NodeDataType CollapsedNodeDataModel::dataType(PortType, PortIndex) const
{
	return m_nodeDataType;
}

std::shared_ptr<NodeData> CollapsedNodeDataModel::outData(PortIndex port)
{
	return nullptr;
}
