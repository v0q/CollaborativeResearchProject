#include "RotateDataModel.hpp"

void RotateDataModel::save(Properties &p) const
{
	p.put("model_name", name());
}

unsigned int RotateDataModel::nPorts(PortType portType) const
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

NodeDataType RotateDataModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch (portType)
	{
		case PortType::In:
			switch(portIndex)
			{
				case 0:
					return DistanceFieldInput().type();
				break;
				case 1:
					return VectorData().type();
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

std::shared_ptr<NodeData> RotateDataModel::outData(PortIndex port)
{
	return nullptr;
}

void RotateDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
{
	if(portIndex == 1)
	{
		auto vec = std::dynamic_pointer_cast<VectorData>(_data);
		if(vec)
    {
			Vec4f v = vec->vector();
			std::string cx = "cos(" + hsitho::Expressions::evaluate(v.m_x) + ")";
			std::string cy = "cos(" + hsitho::Expressions::evaluate(v.m_y) + ")";
			std::string cz = "cos(" + hsitho::Expressions::evaluate(v.m_z) + ")";
			std::string sx = "sin(" + hsitho::Expressions::evaluate(v.m_x) + ")";
			std::string sy = "sin(" + hsitho::Expressions::evaluate(v.m_y) + ")";
			std::string sz = "sin(" + hsitho::Expressions::evaluate(v.m_z) + ")";

			Mat4f rx("1.0", "0.0", "0.0",		"0.0",
							 "0.0", cx,		 "-"+sx,	"0.0",
							 "0.0", sx,		 cx,			"0.0",
							 "0.0", "0.0", "0.0",		"1.0");
			Mat4f ry(cy,			 "0.0", sy,		 "0.0",
							 "0.0",		 "1.0", "0.0", "0.0",
							 "-"+sy,	 "0.0", cy,		 "0.0",
							 "0.0",		 "0.0", "0.0", "1.0");
			Mat4f rz(cz,		"-"+sz, "0.0", "0.0",
							 sz,		cz,			"0.0", "0.0",
							 "0.0", "0.0",	"1.0", "0.0",
							 "0.0", "0.0",	"0.0", "1.0");

			m_t = Mat4f();
			if(v.m_x != "0.0") {
        m_t = m_t * rx;
			}
			if(v.m_y != "0.0") {
        m_t = m_t * ry;
			}
			if(v.m_z != "0.0") {
        m_t = m_t * rz;
			}
    }
	}
}

std::vector<QWidget *> RotateDataModel::embeddedWidget()
{
	return std::vector<QWidget *>();
}

std::string RotateDataModel::getShaderCode() {
	return "";
}
