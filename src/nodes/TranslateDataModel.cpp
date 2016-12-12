#include "TranslateDataModel.hpp"

void TranslateDataModel::save(Properties &p) const
{
	p.put("model_name", name());
}

unsigned int TranslateDataModel::nPorts(PortType portType) const
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

NodeDataType TranslateDataModel::dataType(PortType portType, PortIndex portIndex) const
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

std::shared_ptr<NodeData> TranslateDataModel::outData(PortIndex port)
{
	return nullptr;
}

void TranslateDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
{
	if(portIndex == 1)
	{
		auto vec = std::dynamic_pointer_cast<VectorData>(_data);
		if(vec)
		{
			Vec4f v = vec->vector();
			m_t = Mat4f("1.0", "0.0", "0.0", "0.0",
									"0.0", "1.0", "0.0", "0.0",
									"0.0", "0.0", "1.0", "0.0",
									hsitho::Expressions::evaluate(v.m_x), hsitho::Expressions::evaluate(v.m_y), hsitho::Expressions::evaluate(v.m_z), "1.0");
		}
	}
}

std::vector<QWidget *> TranslateDataModel::embeddedWidget()
{
	return std::vector<QWidget *>();
}

std::string TranslateDataModel::getShaderCode() {
	return "";
}
