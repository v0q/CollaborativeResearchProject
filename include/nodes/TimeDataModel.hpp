#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TimeDataModel : public NodeDataModel
{
	Q_OBJECT

public:

  TimeDataModel();
  virtual ~TimeDataModel() {}

	QString caption() const override {
    return QString("Time");
	}

	static QString name() {
    return QString("Time");
	}

	void save(Properties &p) const override {	p.put("model_name", name()); }
	void setInData(std::shared_ptr<NodeData>, int) override {}

	unsigned int nPorts(PortType portType) const override;
	NodeDataType dataType(PortType, PortIndex) const override;
	std::shared_ptr<NodeData> outData(PortIndex) override;

	std::vector<QWidget *> embeddedWidget() override;

	DFNodeType getNodeType() const { return DFNodeType::SCALAR; }
	std::string getShaderCode();

private:
  std::shared_ptr<ScalarData> m_v;
};
