#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

class SphereData : public NodeData
{
public:

  NodeDataType
  type() const override
	{ return NodeDataType {"DistanceFieldData", "Sphere Data"}; }

};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class SpherePrimitiveDataModel : public NodeDataModel
{
  Q_OBJECT

public:

	virtual ~SpherePrimitiveDataModel();

  QString caption() const override
  {
		return QString("Sphere");
  }

  static QString name()
  {
		return QString("Sphere");
  }


  void save(Properties &p) const override;

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override;

	std::vector<QWidget *> embeddedWidget() override;

	DFNodeType getNodeType() const { return DFNodeType::PRIMITIVE; }
	std::string getShaderCode();
	void setTransform(const std::string &_t) {
		m_transform = _t;
  }

private:
	Vec4f m_color;
	std::string m_transform;
};
