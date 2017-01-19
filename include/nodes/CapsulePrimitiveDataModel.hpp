#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

class CapsulePrimitiveDataModel : public NodeDataModel
{
  Q_OBJECT

public:

	CapsulePrimitiveDataModel();
	virtual ~CapsulePrimitiveDataModel() {}

  QString caption() const override
  {
    return QString("Capsule");
  }

  static QString name()
  {
    return QString("Capsule");
  }


  void save(Properties &p) const override;
	void restore(const Properties &p) override;

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;
	void setInData(std::shared_ptr<NodeData>, PortIndex _portIndex) override;

	void sizeEdit(QString const);

  std::vector<QWidget *> embeddedWidget() override;

  DFNodeType getNodeType() const override { return DFNodeType::PRIMITIVE; }
  std::string getShaderCode() override;
	void setTransform(const Mat4f &_t) override;

private:
  Vec4f m_color;
	Vec4f m_startPos;
	Vec4f m_endPos;
	QLineEdit *m_r;
  std::string m_transform;
};
