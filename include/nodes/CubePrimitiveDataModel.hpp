#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"

#include <iostream>

class NumberData : public NodeData
{
public:

  NumberData()
    : _number(0.0)
  {}

  NumberData(double const number)
    : _number(number)
  {}

  NodeDataType type() const override
  {
    return NodeDataType {"number",
                         "Number"};
  }

  double number() const
  { return _number; }

  QString numberAsText() const
  { return QString::number(_number, 'f'); }

private:

  double _number;
};


/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class CubePrimitiveDataModel
  : public NodeDataModel
{
  Q_OBJECT

public:
  CubePrimitiveDataModel();

  virtual
  ~CubePrimitiveDataModel() {}

public:

  QString
  caption() const override
  { return QString("Number Source"); }

  bool
  captionVisible() const override
  { return false; }

  static QString
  name() { return QString("NumberSource"); }

public:

  void
  save(Properties &p) const override;

  void
  restore(Properties const &p) override;

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData>, int) override
  { }

  QWidget *
  embeddedWidget() override { return _lineEdit; }

private slots:

  void
  onTextEdited(QString const &string);

private:

  std::shared_ptr<NumberData> _number;

  QLineEdit * _lineEdit;
};
