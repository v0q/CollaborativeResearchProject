#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

/// \file TimeDataModel.hpp
/// \brief Node for using time as a variable, more comments on the functions can be found in CapsulePrimitiveDataModel.hpp as all of the nodes inherit from the NodeDataModel.
///        Built around the NodeDataModel by Dimitry Pinaev [https://github.com/paceholder/nodeeditor]
/// \authors Teemu Lindborg & Phil Gifford
/// \version 1.0
/// \date 22/01/17 Updated to NCCA Coding standard

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

  DFNodeType getNodeType() const override { return DFNodeType::SCALAR; }
  std::string getShaderCode() override;

private:
  std::shared_ptr<ScalarData> m_v;
};
