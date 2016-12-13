#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>
#include <QColorDialog>


#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TriangularPrismPrimitiveDataModel : public NodeDataModel
{
  Q_OBJECT

public:

  virtual ~TriangularPrismPrimitiveDataModel();

  QString caption() const override
  {
    return QString("TriPrism");
  }

  static QString name()
  {
    return QString("TriPrism");
  }


  void save(Properties &p) const override;

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override;

  void setInData(std::shared_ptr<NodeData>, int) override;

  std::vector<QWidget *> embeddedWidget() override;

  DFNodeType getNodeType() const override { return DFNodeType::PRIMITIVE; }
  std::string getShaderCode() override;
  void setTransform(const Mat4f &_t) override {
    std::ostringstream ss;
    for(int y = 0; y < 4; ++y)
    {
      for(int x = 0; x < 4; ++x)
      {
        if(x || y)
          ss << ", ";
        ss << _t.matrix(x, y);
      }
    }
    m_transform = "mat4x4(" + ss.str() + ")";
  }

private:
  Vec4f m_color;
  std::string m_transform;
};


