#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class RotateDataModel : public NodeDataModel
{
	Q_OBJECT

public:

	virtual ~RotateDataModel() {}

	QString caption() const override
	{
		return QString("Rotate");
	}

	static QString name()
	{
		return QString("Rotate");
	}

	void save(Properties &p) const override;

	unsigned int nPorts(PortType portType) const override;

	NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

	std::shared_ptr<NodeData> outData(PortIndex port) override;

	void setInData(std::shared_ptr<NodeData>, PortIndex) override;

	std::vector<QWidget *> embeddedWidget() override;

	DFNodeType getNodeType() const { return DFNodeType::TRANSFORM; }
	std::string getShaderCode();
	Mat4f getTransform() { return m_t; }

private:
	Mat4f m_t;
};
