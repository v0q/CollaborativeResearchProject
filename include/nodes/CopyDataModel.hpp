#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

#include <iostream>

class CopyDataModel : public NodeDataModel
{
	Q_OBJECT

public:

	CopyDataModel();
	virtual ~CopyDataModel() {}

	QString caption() const override
	{
		return QString("Copy");
	}

	static QString name()
	{
		return QString("Copy");
	}

	void save(Properties &p) const override;
	void restore(const Properties &p) override;
	void valueEdit(QString const);

	unsigned int nPorts(PortType portType) const override;
	NodeDataType dataType(PortType portType, PortIndex) const override;

	std::shared_ptr<NodeData> outData(PortIndex port) override { return nullptr; }
	void setInData(std::shared_ptr<NodeData>, PortIndex) override;

	std::vector<QWidget *> embeddedWidget() override { return std::vector<QWidget *>{m_cp}; }

	DFNodeType getNodeType() const { return DFNodeType::COPY; }
	std::string getShaderCode() { return m_cp->text().toStdString(); }


private:
	QLineEdit *m_cp;
};
