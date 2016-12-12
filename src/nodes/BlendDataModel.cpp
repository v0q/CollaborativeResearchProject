#include "BlendDataModel.hpp"


BlendDataModel::~BlendDataModel()
{

}

void BlendDataModel::save(Properties &p) const
{
	p.put("model_name", BlendDataModel::name());
}

unsigned int BlendDataModel::nPorts(PortType portType) const
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

NodeDataType BlendDataModel::dataType(PortType portType, PortIndex portIndex) const
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
  return DistanceFieldInput().type();
}

std::shared_ptr<NodeData> BlendDataModel::outData(PortIndex port)
{
  return nullptr;
}

void BlendDataModel::setInData(std::shared_ptr<NodeData>, int)
{

}

std::vector<QWidget *> BlendDataModel::embeddedWidget()
{
  return std::vector<QWidget *>();
}

std::string BlendDataModel::getShaderCode() {
 return "opBlend(";
}
