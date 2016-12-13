#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>
#include <QColorDialog>

#include "nodeEditor/Node.hpp"
#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class CollapsedNodeDataModel : public NodeDataModel
{
	Q_OBJECT

public:

	CollapsedNodeDataModel(const NodeDataType &_type, std::vector<std::shared_ptr<Node>> &_nodes);
	virtual ~CollapsedNodeDataModel() {}

	QString caption() const override
	{
		return QString("Collapsed Node");
	}

	static QString name()
	{
		return QString("Collapsed Node");
	}


	void save(Properties &p) const override;

	unsigned int nPorts(PortType portType) const override;

	NodeDataType dataType(PortType, PortIndex) const override;

	std::shared_ptr<NodeData> outData(PortIndex port) override;
	void setInData(std::shared_ptr<NodeData>, int) override {}
	std::vector<QWidget *> embeddedWidget() override { return std::vector<QWidget *>(); }
	std::vector<std::shared_ptr<Node>> getNodes() const { return m_nodes; }

	DFNodeType getNodeType() const { return DFNodeType::OUTPUT; }

private:
	NodeDataType m_nodeDataType;
	std::vector<std::shared_ptr<Node>> m_nodes;
};
