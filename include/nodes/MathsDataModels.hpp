#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

// **********************************************
//	SCALAR
// **********************************************
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
	void scalarEdit(QString const);

private:
	std::shared_ptr<ScalarData> m_v;
	QLineEdit *m_value;
};


// **********************************************
//	VECTOR
// **********************************************
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
