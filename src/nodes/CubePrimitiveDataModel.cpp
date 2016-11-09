#include "CubePrimitiveDataModel.hpp"


CubePrimitiveDataModel::~CubePrimitiveDataModel()
{

}

void CubePrimitiveDataModel::save(Properties &p) const
{

}

unsigned int CubePrimitiveDataModel::nPorts(PortType portType) const
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

NodeDataType CubePrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
{
//  switch (portType)
//  {
//    case PortType::In:
//      return MyNodeData().type();
//    break;
//		case PortType::Out:
			return DistanceFieldOutput().type();
//		break;

//    default:
//      break;
//  }
}

std::shared_ptr<NodeData> CubePrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void CubePrimitiveDataModel::setInData(std::shared_ptr<NodeData>, int)
{

}

QWidget* CubePrimitiveDataModel::embeddedWidget()
{
  return nullptr;
}

std::string CubePrimitiveDataModel::getShaderCode()
{
	if(m_transform == "")
	{
		m_transform = "vec3(0.0, 0.0, 0.0)";
	}
	return "cube(_position + " + m_transform + ", 0.6f)";
}
