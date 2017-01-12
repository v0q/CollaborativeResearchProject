#include <QtGui/QDoubleValidator>
#include <iostream>
#include "TimeDataModel.hpp"

TimeDataModel::TimeDataModel() :
  m_v(nullptr)
{
	m_v = std::make_shared<ScalarData>("u_GlobalTime");
}

unsigned int TimeDataModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 0;
		break;

		case PortType::Out:
			result = 1;
		break;

		default:
			break;
	}

	return result;
}

NodeDataType TimeDataModel::dataType(PortType, PortIndex) const
{
	return ScalarData().type();
}

std::shared_ptr<NodeData> TimeDataModel::outData(PortIndex)
{
  return m_v;
}

std::vector<QWidget *> TimeDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string TimeDataModel::getShaderCode() {
	return "";
}
