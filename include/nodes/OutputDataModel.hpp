#pragma once

#include <QtCore/QObject>
#include <iostream>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

class OutputDataModel : public NodeDataModel
{
	Q_OBJECT

public:
	OutputDataModel();
	virtual ~OutputDataModel() {}

	QString caption() const override
	{
		return QString("Output");
	}

	static QString name()
	{
		return QString("Output");
	}

	void save(Properties &p) const override;
	void restore(const Properties &p) override;
	void setInData(std::shared_ptr<NodeData>, int) override {}
	void setDataType(const NodeDataType &_dt) override { m_dataType = _dt; }
	unsigned int nPorts(PortType portType) const override;
	NodeDataType dataType(PortType, PortIndex) const override;
	std::shared_ptr<NodeData> outData(PortIndex port) override { return nullptr; }
	std::vector<QWidget *> embeddedWidget() override { return std::vector<QWidget *>(); }
  DFNodeType getNodeType() const override { return DFNodeType::OUTPUT; }

private:
	NodeDataType m_dataType;
};


