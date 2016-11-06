#include "UnionDataModel.hpp"


UnionDataModel::~UnionDataModel()
{

}

void UnionDataModel::save(Properties &p) const
{
}

unsigned int UnionDataModel::nPorts(PortType portType) const
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

NodeDataType UnionDataModel::dataType(PortType portType, PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
			return UnionInput().type();
    break;
		case PortType::Out:
			return UnionOutput().type();
		break;

    default:
      break;
	}
}

std::shared_ptr<NodeData> UnionDataModel::outData(PortIndex port)
{
  return nullptr;
}

void UnionDataModel::setInData(std::shared_ptr<NodeData>, int)
{

}

QWidget* UnionDataModel::embeddedWidget()
{
  return nullptr;
}
