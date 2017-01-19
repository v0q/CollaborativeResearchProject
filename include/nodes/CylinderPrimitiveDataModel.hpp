#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

class CylinderPrimitiveDataModel : public NodeDataModel
{
  Q_OBJECT

public:
	CylinderPrimitiveDataModel();
	virtual ~CylinderPrimitiveDataModel() {}

  QString caption() const override
  {
    return QString("Cylinder");
  }

  static QString name()
  {
    return QString("Cylinder");
  }

  void save(Properties &p) const override;
	void restore(const Properties &p) override;

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;
	void setInData(std::shared_ptr<NodeData>, PortIndex portIndex) override;
	void sizeEdit(QString const);

  std::vector<QWidget *> embeddedWidget() override;

  DFNodeType getNodeType() const override { return DFNodeType::PRIMITIVE; }
  std::string getShaderCode() override;
	void setTransform(const Mat4f &_t) override;

private:
  Vec4f m_color;
	QLineEdit *m_r;
	QLineEdit *m_height;
  std::string m_transform;
};
