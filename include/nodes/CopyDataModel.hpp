//#pragma once

//#include <QtCore/QObject>
//#include <QtWidgets/QLineEdit>

//#include "nodeEditor/NodeDataModel.hpp"
//#include "nodes/DistanceFieldData.hpp"

//#include <iostream>

////------------------------------------------------------------------------------

///// The model dictates the number of inputs and outputs for the Node.
///// In this example it has no logic.
//class CopyDataModel : public NodeDataModel
//{
//  Q_OBJECT

//public:

//  CopyDataModel();


//  virtual ~CopyDataModel();

//  QString caption() const override
//  {
//    return QString("Copy");
//  }

//  static QString name()
//  {
//    return QString("Copy");
//  }



//  void save(Properties &p) const override;

//  unsigned int nPorts(PortType portType) const override;

//  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

//  std::shared_ptr<NodeData> outData(PortIndex port) override;

//  void setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex) override;

//  std::vector<QWidget *> embeddedWidget() override;

//  DFNodeType getNodeType() const { return DFNodeType::SCALAR; }
//  std::string getShaderCode();
//  std::string getExtraParams() const override { return ", 0.6"; }


//private slots:
//  void valueEdit(QString string);


//private:
//  std::shared_ptr<ScalarData> m_v;

//  QLineEdit *m_cp;

//};
