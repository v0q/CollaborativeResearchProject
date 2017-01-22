#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>


#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

#include <iostream>
#include <QColorDialog>

/// \file ColorPickerDataModel.hpp
/// \brief Node for selecting a colour, more comments on the functions can be found in CapsulePrimitiveDataModel.hpp as all of the nodes inherit from the NodeDataModel.
///        Built around the NodeDataModel by Dimitry Pinaev [https://github.com/paceholder/nodeeditor]
/// \authors Teemu Lindborg & Phil Gifford
/// \version 1.0
/// \date 22/01/17 Updated to NCCA Coding standard

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
    return QString("Color");
  }

  static QString name()
  {
    return QString("Color Picker");
  }

  void setColor() {current_color = m_color.onColor(current_color); }

  void setPalColor();

  void setCurrentColor(const QColor &color);

  void save(Properties &p) const override;
	void restore(const Properties &p) override;
  void setInData(std::shared_ptr<NodeData>, int) override;
  void updateWidgets() override;

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex) const override;
  std::shared_ptr<NodeData> outData(PortIndex) override;

  std::vector<QWidget *> embeddedWidget() override;

  DFNodeType getNodeType() const override { return DFNodeType::COLOR; }
  std::string getShaderCode() override;

private slots:
  void colorEdit(QString const &string);

protected:
  bool eventFilter(QObject *object, QEvent *event) override;

private:
  QPalette m_palColor;
  QColorPicker m_color;
  QLabel *_label;
  QColor current_color;
  QColor label_color;
  unsigned int m_w, m_h, m_px, m_py, m_margin;
	bool m_vars;

  std::shared_ptr<ColorData> m_cd;

  union {
    QLineEdit *m_inputs[3];
    struct {
      QLineEdit *m_x;
      QLineEdit *m_y;
      QLineEdit *m_z;
    };
  };

};
