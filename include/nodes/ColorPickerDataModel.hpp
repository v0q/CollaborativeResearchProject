#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

#include <iostream>
#include <QColorDialog>

//------------------------------------------------------------------------------

class QColorPicker : public QWidget
{
public:
  QColor onColor(QColor&);
};


class ColorPickerDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  ColorPickerDataModel();

  virtual ~ColorPickerDataModel();

  QString caption() const override
  {
    return QString("    Color     ");
  }

  static QString name()
  {
    return QString("Color Picker");
  }

  void setColor() {current_color = m_color.onColor(current_color); }

  void setPalColor();

  void setCurrentColor(const QColor &color);

  void save(Properties &p) const override;
  void setInData(std::shared_ptr<NodeData>, int) override {}

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  std::shared_ptr<NodeData> outData(PortIndex) override;

  std::vector<QWidget *> embeddedWidget() override;

  DFNodeType getNodeType() const { return DFNodeType::COLOR; }
  std::string getShaderCode();

protected:
  bool eventFilter(QObject *object, QEvent *event);

private:
 // std::shared_ptr<ColorData> m_cd;
  QPalette m_palColor;
  QColorPicker m_color;
  QLabel *_label;
  QColor current_color;
  QColor label_color;

  int m_r, m_b, m_g;


};
