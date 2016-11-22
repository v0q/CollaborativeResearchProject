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

std::vector<QWidget *> CubePrimitiveDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string CubePrimitiveDataModel::getShaderCode()
{
  if(m_transform == "")
  {
    m_transform = "mat4x4(cos(u_GlobalTime)*1.0+0, sin(u_GlobalTime)*1.0+0, 0, 2.5,	-sin(u_GlobalTime)*1.0+0, cos(u_GlobalTime)*1.0+0, 0, 0.600000024, 0, 0, 1, 0, 0, 0, 0, 1)";
  }
	return "sdFastBox(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, 0.6f, vec3(1.0, 0.41, 0.71))";
}
