#include "CubePrimitiveDataModel.hpp"


CubePrimitiveDataModel::~CubePrimitiveDataModel()
{

}

void CubePrimitiveDataModel::save(Properties &p) const
{
  p.put("Cube", CubePrimitiveDataModel::name());

}

unsigned int CubePrimitiveDataModel::nPorts(PortType portType) const
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

NodeDataType CubePrimitiveDataModel::dataType(PortType portType, PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
      switch (portIndex)
      {
        case 1:
          return CubeDataModel().type();
          break;

        case 0:
          return SimpleCubeData().type();
          break;
      }
      break;

    case PortType::Out:
      return CubeDataModel().type();
      break;

    default:
      break;
  }

}

std::shared_ptr<NodeData> CubePrimitiveDataModel::outData(PortIndex port)
{
  return nullptr;
}

void CubePrimitiveDataModel::setInData(std::shared_ptr<NodeData>, int)
{

}

QWidget* CubePrimitiveDataModel::embeddedWidget()
{
  return nullptr;
}

void CubePrimitiveDataModel::print(float &_cubeSize)
{
  std::cout << _cubeSize << "\n";

}


