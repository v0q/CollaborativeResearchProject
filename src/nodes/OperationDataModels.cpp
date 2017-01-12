#include "OperationDataModels.hpp"

//------------------------------------------------------------------------------
// Union
//------------------------------------------------------------------------------
unsigned int UnionDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 2;
    break;

    case PortType::Out:
      result = 1;
    break;

    default:
    break;
  }

  return result;
}

NodeDataType UnionDataModel::dataType(PortType portType, PortIndex portIndex) const
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

//------------------------------------------------------------------------------
// Subtraction
//------------------------------------------------------------------------------
unsigned int SubtractionOpDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 2;
    break;

    case PortType::Out:
      result = 1;
    break;

    default:
    break;
  }

  return result;
}

NodeDataType SubtractionOpDataModel::dataType(PortType portType, PortIndex portIndex) const
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

//------------------------------------------------------------------------------
// Intersection
//------------------------------------------------------------------------------
unsigned int IntersectionDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 2;
    break;

    case PortType::Out:
      result = 1;
    break;

    default:
    break;
  }

  return result;
}

NodeDataType IntersectionDataModel::dataType(PortType portType, PortIndex portIndex) const
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

//------------------------------------------------------------------------------
// Blend
//------------------------------------------------------------------------------
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
