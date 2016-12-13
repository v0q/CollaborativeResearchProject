#include "nodeEditor/Connection.hpp"
#include "CollapsedNodeDataModel.hpp"
#include "MathsDataModels.hpp"

CollapsedNodeDataModel::CollapsedNodeDataModel(const NodeDataType &_type, std::vector<std::shared_ptr<Node> > &_nodes) :
	m_nodeDataType(_type),
	m_nodes(_nodes)
{
	for(auto &n : m_nodes)
	{
		if(n->nodeDataModel()->getNodeType() == DFNodeType::OUTPUT)
		{
			m_outputs.push_back(n);
		}
	}
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
	return m_outputs[0]->nodeState().getEntries(PortType::In)[0][0].lock()->getNode(PortType::Out).lock()->nodeDataModel()->outData(port);
}
