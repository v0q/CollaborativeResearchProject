#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

class CopyNumDataModel : public NodeDataModel
{
	Q_OBJECT

public:
	CopyNumDataModel() : m_val(nullptr)
	{
		m_val = std::make_shared<ScalarData>(boost::lexical_cast<std::string>("copyNum"));
	}
	virtual ~CopyNumDataModel() {}

	QString caption() const override {
		return QString("Copy num");
	}

	static QString name() {
		return QString("Copy num");
	}

	void save(Properties &p) const override {	p.put("model_name", name()); }
	void setInData(std::shared_ptr<NodeData>, int) override {}

	unsigned int nPorts(PortType portType) const override
	{
		unsigned int result = 1;

		switch (portType)
		{
			case PortType::In:
				result = 0;
				break;

			case PortType::Out:
				result = 1;

			default:
				break;
		}

		return result;
	}
	NodeDataType dataType(PortType, PortIndex) const override { return ScalarData().type(); }
	std::shared_ptr<NodeData> outData(PortIndex) override { return m_val; }

	std::vector<QWidget *> embeddedWidget() override { return std::vector<QWidget *>(); }

  DFNodeType getNodeType() const override { return DFNodeType::SCALAR; }
	std::string getShaderCode() override { return ""; }

private:
	std::shared_ptr<ScalarData> m_val;
};
