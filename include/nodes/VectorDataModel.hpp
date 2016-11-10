#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class VectorDataModel : public NodeDataModel
{
	Q_OBJECT

public:

	VectorDataModel();
	~VectorDataModel();

	QString caption() const override {
		return QString("Vector");
	}

	static QString name() {
		return QString("Vector");
	}

	void save(Properties &p) const override;

	unsigned int nPorts(PortType portType) const override;

	NodeDataType dataType(PortType, PortIndex) const override;

	std::shared_ptr<NodeData> outData(PortIndex port) override;

	void setInData(std::shared_ptr<NodeData>, int) override;

	std::vector<QWidget *> embeddedWidget() override;

	DFNodeType getNodeType() const { return DFNodeType::TRANSFORM; }

	std::string getShaderCode();

private:
	QLineEdit *m_x;
	QLineEdit *m_y;
	QLineEdit *m_z;
};
