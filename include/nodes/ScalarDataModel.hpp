#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ScalarDataModel : public NodeDataModel
{
	Q_OBJECT

public:

	ScalarDataModel();
	virtual ~ScalarDataModel() {}

	QString caption() const override {
		return QString("Scalar");
	}

	static QString name() {
		return QString("Scalar");
	}

	void save(Properties &p) const override {}
	void setInData(std::shared_ptr<NodeData>, int) override {}

	unsigned int nPorts(PortType portType) const override;
	NodeDataType dataType(PortType, PortIndex) const override;
	std::shared_ptr<NodeData> outData(PortIndex) override;

	std::vector<QWidget *> embeddedWidget() override;

	DFNodeType getNodeType() const { return DFNodeType::SCALAR; }
	std::string getShaderCode();

private slots:
	void vectorEdit(QString const);

private:
	std::shared_ptr<ScalarData> m_v;
	QLineEdit *m_value;
};
