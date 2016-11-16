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
	virtual ~VectorDataModel() {}

	QString caption() const override {
		return QString("Vector");
	}

  static QString name() {
		return QString("Vector");
	}

	void save(Properties &p) const override {}
	void setInData(std::shared_ptr<NodeData>, PortIndex portIndex) override;

	unsigned int nPorts(PortType portType) const override;
	NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
	std::shared_ptr<NodeData> outData(PortIndex) override;

	std::vector<QWidget *> embeddedWidget() override;

	DFNodeType getNodeType() const { return DFNodeType::VECTOR; }
	std::string getShaderCode();

private slots:
	void vectorEdit(QString const);

private:
	std::shared_ptr<VectorData> m_v;
	union {
		QLineEdit *m_inputs[3];
		struct {
			QLineEdit *m_x;
			QLineEdit *m_y;
			QLineEdit *m_z;
		};
	};
};
