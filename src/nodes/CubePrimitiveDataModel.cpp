#include <QtGui/QDoubleValidator>
#include "CubePrimitiveDataModel.hpp"

CubePrimitiveDataModel::CubePrimitiveDataModel() :
	m_dimensions(Vec4f("1.0", "1.0", "1.0", "1.0"))
{

}

void CubePrimitiveDataModel::save(Properties &p) const
{
	p.put("model_name", name());
}

void CubePrimitiveDataModel::restore(const Properties &p)
{

}

unsigned int CubePrimitiveDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch(portType)
  {
    case PortType::In:
      result = 2;
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
  switch(portType)
  {
    case PortType::In:
      switch(portIndex)
      {
        case 0:
					return VectorData("Dim").type();
        break;
        case 1:
          return ColorData().type();
        break;
      }
    break;
    case PortType::Out:
      return DistanceFieldOutput().type();
    break;
    default:
      break;
  }
  return DistanceFieldInput().type();
}

std::shared_ptr<NodeData> CubePrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void CubePrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, int)
{
  auto cd = std::dynamic_pointer_cast<ColorData>(_data);
  if(cd) {
    m_color = cd->color();
    return;
  }
	auto vecdata = std::dynamic_pointer_cast<VectorData>(_data);
	if(vecdata) {
		m_dimensions = vecdata->vector();
    return;
	}
}

void CubePrimitiveDataModel::setTransform(const Mat4f &_t)
{
  std::ostringstream ss;
  for(int y = 0; y < 4; ++y)
  {
    for(int x = 0; x < 4; ++x)
    {
      if(x || y)
        ss << ", ";
      ss << _t.matrix(x, y);
    }
  }
  m_transform = "mat4x4(" + ss.str() + ")";
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
	return "sdBox(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec3(" + m_dimensions.m_x + ", " + m_dimensions.m_y + ", " + m_dimensions.m_z + "), vec3(clamp(" + m_color.m_x + ", 0.0, 1.0), clamp(" + m_color.m_y + ", 0.0, 1.0), clamp(" + m_color.m_z + ", 0.0, 1.0)))";
}
