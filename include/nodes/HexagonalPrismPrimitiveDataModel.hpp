#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

class HexagonalPrismPrimitiveDataModel : public NodeDataModel
{
  Q_OBJECT

public:
	HexagonalPrismPrimitiveDataModel();
	virtual ~HexagonalPrismPrimitiveDataModel() {}

  QString caption() const override
  {
    return QString("HexPrism");
  }

  static QString name()
  {
    return QString("HexPrism");
  }

  void save(Properties &p) const override;
	void restore(const Properties &p) override;

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;
  void setInData(std::shared_ptr<NodeData>, int) override;
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


