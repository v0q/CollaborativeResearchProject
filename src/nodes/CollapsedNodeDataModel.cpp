#include "nodeEditor/Connection.hpp"
#include "CollapsedNodeDataModel.hpp"
#include "MathsDataModels.hpp"

CollapsedNodeDataModel::CollapsedNodeDataModel(std::vector<std::shared_ptr<Node> > &_nodes) :
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
  p.put("model_name", name());
}

void CollapsedNodeDataModel::restore(const Properties &p)
{

}

unsigned int CollapsedNodeDataModel::nPorts(PortType portType) const
{
	unsigned int result = 0;

  switch(portType)
	{
		case PortType::In:
			result = 0;
    break;

		case PortType::Out:
      result = m_outputs.size();
    break;

		default:
    break;
	}

	return result;
}

NodeDataType CollapsedNodeDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch(portType)
	{
		case PortType::Out:
      return m_outputs[portIndex]->nodeDataModel()->dataType(PortType::In, 0);
		break;

		default:
			return NodeDataType{};
		break;
	}
}

std::shared_ptr<NodeData> CollapsedNodeDataModel::outData(PortIndex port)
{
  return m_outputs[(unsigned int)port]->nodeState().getEntries(PortType::In)[0][0].lock()->getNode(PortType::Out).lock()->nodeDataModel()->outData(port);
}
