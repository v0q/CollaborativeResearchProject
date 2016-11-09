#include "ViewerDataModel.hpp"


ViewerDataModel::~ViewerDataModel()
{

}

void ViewerDataModel::save(Properties &p) const
{
  p.put("Viewer", ViewerDataModel::name());

}

unsigned int ViewerDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}

NodeDataType ViewerDataModel::dataType(PortType portType, PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
      switch (portIndex)
      {
        case 1:
          return ViewerDataModel().type();
          break;

        case 0:
          return SimpleViewerData().type();
          break;
      }
      break;

    case PortType::Out:
      return ViewerDataModel().type();
      break;

    default:
      break;
  }

}

std::shared_ptr<NodeData> ViewerDataModel::outData(PortIndex port)
{
  return nullptr;
}

void ViewerDataModel::setInData(std::shared_ptr<NodeData>, int)
{

}

QWidget* ViewerDataModel::embeddedWidget()
{
  return nullptr;
}



