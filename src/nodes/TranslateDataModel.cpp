#include "TranslateDataModel.hpp"

TranslateDataModel::~TranslateDataModel()
{
}

void TranslateDataModel::save(Properties &p) const
{
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
			return DistanceFieldInput().type();
		break;
		case PortType::Out:
			return DistanceFieldOutput().type();
		break;

		default:
			break;
	}
}

std::shared_ptr<NodeData> TranslateDataModel::outData(PortIndex port)
{
	return nullptr;
}

void TranslateDataModel::setInData(std::shared_ptr<NodeData>, int)
{

}

std::vector<QWidget *> TranslateDataModel::embeddedWidget()
{
	return std::vector<QWidget *>();
}

std::string TranslateDataModel::getShaderCode() {
	return "";
}
