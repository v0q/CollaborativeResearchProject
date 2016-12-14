#include "CapsulePrimitiveDataModel.hpp"


CapsulePrimitiveDataModel::~CapsulePrimitiveDataModel()
{

}

void CapsulePrimitiveDataModel::save(Properties &p) const
{
  p.put("model_name", name());
}

unsigned int CapsulePrimitiveDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}

NodeDataType CapsulePrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
      return ColorData().type();
    break;
    case PortType::Out:
      return DistanceFieldOutput().type();
    break;

    default:
      break;
  }
  return DistanceFieldOutput().type();
}

std::shared_ptr<NodeData> CapsulePrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void CapsulePrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, int)
{
  auto data = std::dynamic_pointer_cast<ColorData>(_data);
  if(data) {
    m_color = data->color();
  }
}

std::vector<QWidget *> CapsulePrimitiveDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string CapsulePrimitiveDataModel::getShaderCode()
{
  if(m_transform == "")
  {
    m_transform = "mat4x4(cos(u_GlobalTime)*1.0+0, sin(u_GlobalTime)*1.0+0, 0, 2.5,	-sin(u_GlobalTime)*1.0+0, cos(u_GlobalTime)*1.0+0, 0, 0.600000024, 0, 0, 1, 0, 0, 0, 0, 1)";
  }
  return "sdCapsule(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec3(1.0, 1.0, 3.0), vec3(1.0, 1.0, 1.0), 0.6,  vec3(clamp(" + m_color.m_x + ", 0.0, 1.0), clamp(" + m_color.m_y + ", 0.0, 1.0), clamp(" +m_color.m_z + ", 0.0, 1.0)))";
}
