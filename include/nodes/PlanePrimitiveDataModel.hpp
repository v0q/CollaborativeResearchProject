#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

class PlanePrimitiveDataModel : public NodeDataModel
{
  Q_OBJECT

public:

	PlanePrimitiveDataModel();
	virtual ~PlanePrimitiveDataModel() {}

  QString caption() const override
  {
    return QString("Plane");
  }

  static QString name()
  {
    return QString("Plane");
  }

  void save(Properties &p) const override;
	void restore(const Properties &p) override;

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;
  void setInData(std::shared_ptr<NodeData>, int) override;

  std::vector<QWidget *> embeddedWidget() override;

  DFNodeType getNodeType() const override { return DFNodeType::PRIMITIVE; }
  std::string getShaderCode() override;
	void setTransform(const Mat4f &_t) override;

private:
  Vec4f m_color;
	Vec4f m_normal;
  std::string m_transform;
};
