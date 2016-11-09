#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"

#include <iostream>

class DistanceFieldData : public NodeData
{
public:

	NodeDataType type() const override {
		return NodeDataType {"DistanceFieldData", "DISTANCE"};
	}
};

class DistanceFieldOutputDataModel : public NodeDataModel
{
	Q_OBJECT

public:

	virtual ~DistanceFieldOutputDataModel();

	QString caption() const override
	{
		return QString("");
	}

	static QString name()
	{
		return QString("");
	}

	void save(Properties &p) const override;

	unsigned int nPorts(PortType portType) const override;

	NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

	std::shared_ptr<NodeData> outData(PortIndex port) override;

	void setInData(std::shared_ptr<NodeData>, int) override;


	QWidget *embeddedWidget() override;


	QString getOutData()
	{
		return QString("Blah");
	}
};
