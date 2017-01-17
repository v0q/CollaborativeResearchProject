#include "ConePrimitiveDataModel.hpp"

ConePrimitiveDataModel::ConePrimitiveDataModel() :
	m_color(Vec4f("0.6", "0.6", "0.6", "1.0")),
	m_dimensions(Vec4f("1.0", "1.0", "1.0", "1.0"))
{

}

void ConePrimitiveDataModel::save(Properties &p) const
{
  p.put("model_name", name());
}

void ConePrimitiveDataModel::restore(const Properties &p)
{

}

unsigned int ConePrimitiveDataModel::nPorts(PortType portType) const
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

NodeDataType ConePrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
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

std::shared_ptr<NodeData> ConePrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void ConePrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, int)
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
	m_color = Vec4f("0.6", "0.6", "0.6", "1.0");
	m_dimensions = Vec4f("1.0", "1.0", "1.0", "1.0");
}

void ConePrimitiveDataModel::setTransform(const Mat4f &_t)
{
	std::ostringstream ss;
	if(Mat4f() == _t) {
		m_transform = "";
		return;
	}
	for(int y = 0; y < 4; ++y)
	{
		for(int x = 0; x < 4; ++x)
		{
			if(x || y)
				ss << ", ";
			ss << hsitho::Expressions::evaluate(_t.matrix(x, y), "", m_copyNum);
		}
	}
	m_transform = "mat4x4(" + ss.str() + ")";
}

std::vector<QWidget *> ConePrimitiveDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string ConePrimitiveDataModel::getShaderCode()
{
	if(m_transform == "")
		return "sdCappedCone(_position, vec3(" + m_dimensions.m_x + ", " + m_dimensions.m_y + ", " + m_dimensions.m_z + "), vec3(clamp(" + m_color.m_x + ", 0.0, 1.0), clamp(" + m_color.m_y + ", 0.0, 1.0), clamp(" + m_color.m_z + ", 0.0, 1.0)))";
	else
		return "sdCappedCone(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec3(" + m_dimensions.m_x + ", " + m_dimensions.m_y + ", " + m_dimensions.m_z + "), vec3(clamp(" + m_color.m_x + ", 0.0, 1.0), clamp(" + m_color.m_y + ", 0.0, 1.0), clamp(" + m_color.m_z + ", 0.0, 1.0)))";
}
