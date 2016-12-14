#include "HexagonalPrismPrimitiveDataModel.hpp"

HexagonalPrismPrimitiveDataModel::~HexagonalPrismPrimitiveDataModel()
{

}

void HexagonalPrismPrimitiveDataModel::save(Properties &p) const
{
  p.put("model_name", name());
}

unsigned int HexagonalPrismPrimitiveDataModel::nPorts(PortType portType) const
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

NodeDataType HexagonalPrismPrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
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
  return DistanceFieldInput().type();
}

std::shared_ptr<NodeData> HexagonalPrismPrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void HexagonalPrismPrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, int)
{
  auto data = std::dynamic_pointer_cast<ColorData>(_data);
  if(data) {
    m_color = data->color();
  }
}

std::vector<QWidget *> HexagonalPrismPrimitiveDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string HexagonalPrismPrimitiveDataModel::getShaderCode()
{
  if(m_transform == "")
  {
    m_transform = "mat4x4(cos(u_GlobalTime)*1.0+0, sin(u_GlobalTime)*1.0+0, 0, 2.5,	-sin(u_GlobalTime)*1.0+0, cos(u_GlobalTime)*1.0+0, 0, 0.600000024, 0, 0, 1, 0, 0, 0, 0, 1)";
  }
  return "sdHexPrism(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec2(1.0, 2.0), vec3(clamp(" + m_color.m_x + ", 0.0, 1.0), clamp(" + m_color.m_y + ", 0.0, 1.0), clamp(" +m_color.m_z + ", 0.0, 1.0)))";
}
