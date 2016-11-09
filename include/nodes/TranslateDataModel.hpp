#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TranslateDataModel : public NodeDataModel
{
	Q_OBJECT

public:

	virtual ~TranslateDataModel();

	QString caption() const override
	{
		return QString("Translate");
	}

	static QString name()
	{
		return QString("Translate");
	}

	void save(Properties &p) const override;

	unsigned int nPorts(PortType portType) const override;

	NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

	std::shared_ptr<NodeData> outData(PortIndex port) override;

	void setInData(std::shared_ptr<NodeData>, int) override;

	QWidget *embeddedWidget() override;

	DFNodeType getNodeType() const { return DFNodeType::TRANSFORM; }
	Vec4f addTranslation() { return Vec4f(0.0f, -1.0f, 0.0f, 1.0f); }

	std::string getShaderCode();
};
