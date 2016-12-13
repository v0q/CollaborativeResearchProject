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
      std::string cx = "cos(" + v.m_x + ")";
      std::string cy = "cos(" + v.m_y + ")";
      std::string cz = "cos(" + v.m_z + ")";
      std::string sx = "sin(" + v.m_x + ")";
      std::string sy = "sin(" + v.m_y + ")";
      std::string sz = "sin(" + v.m_z + ")";
//			float x = boost::lexical_cast<float>(v.m_x);
//			float y = boost::lexical_cast<float>(v.m_y);
//			float z = boost::lexical_cast<float>(v.m_z);
//			std::string cx = boost::lexical_cast<std::string>(cos(x));
//			std::string cy = boost::lexical_cast<std::string>(cos(y));
//			std::string cz = boost::lexical_cast<std::string>(cos(z));
//			std::string sx = boost::lexical_cast<std::string>(sin(x));
//			std::string sxm = boost::lexical_cast<std::string>(-sin(x));
//			std::string sy = boost::lexical_cast<std::string>(sin(y));
//			std::string sym = boost::lexical_cast<std::string>(-sin(y));
//			std::string sz = boost::lexical_cast<std::string>(sin(z));
//			std::string szm = boost::lexical_cast<std::string>(-sin(y));

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
//			Mat4f rx("1.0", "0.0", "0.0",		"0.0",
//							 "0.0", "a",	 "-b",	"0.0",
//							 "0.0", "b",	 "a",			"0.0",
//							 "0.0", "0.0", "0.0",		"1.0");
//			Mat4f ry("a",			 "0.0", "b",		 "0.0",
//							 "0.0",		 "1.0", "0.0", "0.0",
//							 "-b",		 "0.0", "a",		 "0.0",
//							 "0.0",		 "0.0", "0.0", "1.0");
//			Mat4f rz("a",		"-b", "0.0", "0.0",
//							 "b",		"a",			"0.0", "0.0",
//							 "0.0", "0.0",	"1.0", "0.0",
//							 "0.0", "0.0",	"0.0", "1.0");
			m_t = Mat4f();
			if(v.m_x != "0.0") {
				m_t = m_t * rx;
				std::cout << "1 : \n";
				m_t.print();
				std::cout << "\n";
			}
			if(v.m_y != "0.0") {
				m_t = m_t * ry;
				std::cout << "2 : \n";
				m_t.print();
				std::cout << "\n";
			}
			if(v.m_z != "0.0") {
				m_t = m_t * rz;
				std::cout << "3 : \n";
				m_t.print();
				std::cout << "\n\n";
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
