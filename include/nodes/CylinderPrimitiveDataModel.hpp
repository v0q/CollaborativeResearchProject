#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

/// \file CylinderPrimitiveDataModel.hpp
/// \brief Node for a cylinder primitive, more comments on the functions can be found in CapsulePrimitiveDataModel.hpp as all of the nodes inherit from the NodeDataModel.
///        Built around the NodeDataModel by Dimitry Pinaev [https://github.com/paceholder/nodeeditor]
/// \authors Teemu Lindborg & Phil Gifford
/// \version 1.0
/// \date 22/01/17 Updated to NCCA Coding standard

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
