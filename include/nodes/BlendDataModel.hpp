#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

#include <iostream>

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class BlendDataModel : public NodeDataModel
{
	Q_OBJECT

public:

	virtual ~BlendDataModel();

	QString caption() const override
	{
		return QString("Blend");
	}

	static QString name()
	{
		return QString("Blend");
	}

	void save(Properties &p) const override;

	unsigned int nPorts(PortType portType) const override;

	NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

	std::shared_ptr<NodeData> outData(PortIndex port) override;

	void setInData(std::shared_ptr<NodeData>, int) override;

	std::vector<QWidget *> embeddedWidget() override;

  DFNodeType getNodeType() const override { return DFNodeType::MIX; }
  std::string getShaderCode() override;
	std::string getExtraParams() const override { return ", 0.6"; }
};
