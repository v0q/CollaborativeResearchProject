#include "PlanePrimitiveDataModel.hpp"


PlanePrimitiveDataModel::PlanePrimitiveDataModel() :
	m_color(Vec4f("0.6", "0.6", "0.6", "1.0")),
	m_normal(Vec4f("0.0", "1.0", "0.0", "1.0"))
{

}

void PlanePrimitiveDataModel::save(Properties &p) const
{
  p.put("model_name", name());
}

void PlanePrimitiveDataModel::restore(const Properties &p)
{

}

unsigned int PlanePrimitiveDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
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

NodeDataType PlanePrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
			switch(portIndex)
			{
				case 0:
					return NodeDataType{"Vector", "Normal", Qt::yellow};
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
  return DistanceFieldOutput().type();
}

std::shared_ptr<NodeData> PlanePrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void PlanePrimitiveDataModel::setInData(std::shared_ptr<NodeData> _data, int)
{
	auto cd = std::dynamic_pointer_cast<ColorData>(_data);
	if(cd) {
		m_color = cd->color();
		return;
	}
	auto normal = std::dynamic_pointer_cast<VectorData>(_data);
	if(normal)
	{
		m_normal = normal->vector();
		return;
	}
	m_color = Vec4f("0.6", "0.6", "0.6", "1.0");
	m_normal = Vec4f("0.0", "1.0", "0.0", "1.0");
}

void PlanePrimitiveDataModel::setTransform(const Mat4f &_t)
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

std::vector<QWidget *> PlanePrimitiveDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string PlanePrimitiveDataModel::getShaderCode()
{
  if(m_transform == "")
		return "sdPlane(_position, vec4(" + m_normal.m_x + ", " + m_normal.m_y + ", " + m_normal.m_z + ", " + m_normal.m_w + ") ,vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
	else
		return "sdPlane(vec3(" + m_transform + " * vec4(_position, 1.0)).xyz, vec4(" + m_normal.m_x + ", " + m_normal.m_y + ", " + m_normal.m_z + ", " + m_normal.m_w + ") ,vec3(" + m_color.m_x + ", " + m_color.m_y + ", " + m_color.m_z + "))";
}
