#include "DistanceFieldOutputDataModel.hpp"


DistanceFieldOutputDataModel::~DistanceFieldOutputDataModel()
{

}

void DistanceFieldOutputDataModel::save(Properties &p) const
{
	p.put("Cube_size", DistanceFieldOutputDataModel::name());
}

unsigned int DistanceFieldOutputDataModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 1;
			break;

		case PortType::Out:
			result = 0;

		default:
			break;
	}

	return result;
}

NodeDataType DistanceFieldOutputDataModel::dataType(PortType, PortIndex) const
{
	return OutputData().type();
}

std::shared_ptr<NodeData> DistanceFieldOutputDataModel::outData(PortIndex port)
{
	return nullptr;
}

void DistanceFieldOutputDataModel::setInData(std::shared_ptr<NodeData>, int)
{

}

QWidget* DistanceFieldOutputDataModel::embeddedWidget()
{
	return nullptr;
}


