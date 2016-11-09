#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"

#include <iostream>


/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class ViewerNodeDataModel : public NodeData
{
public:

  NodeDataType
  type() const override
  { return NodeDataType {"Viewer", "Viewer Data"}; }

};

class SimpleViewerData : public NodeData
{
public:

  NodeDataType
  type() const override
  { return NodeDataType {"SimpleData", "Simple Data"}; }
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ViewerDataModel : public NodeDataModel
{
  Q_OBJECT

public:

  virtual ~ViewerDataModel();

  QString caption() const override
  {
    return QString("Viewer Data Model");
  }

  static QString name()
  {
    return QString("ViewerDataModel");
  }

  void save(Properties &p) const override;

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override;


  QWidget *embeddedWidget() override;

private:


};
