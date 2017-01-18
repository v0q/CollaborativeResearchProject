#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

#include <iostream>

//------------------------------------------------------------------------------
// Union
//------------------------------------------------------------------------------
class UnionDataModel : public NodeDataModel
{
  Q_OBJECT

public:

  virtual ~UnionDataModel() { }

  QString caption() const override
  {
    return QString("Union");
  }

  static QString name()
  {
    return QString("Union");
  }

  void save(Properties &p) const override { p.put("model_name", name()); }

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex) override { return nullptr; }
  void setInData(std::shared_ptr<NodeData>, int) override { }
  std::vector<QWidget *> embeddedWidget() override { return std::vector<QWidget *>(); }

  DFNodeType getNodeType() const override { return DFNodeType::MIX; }
  std::string getShaderCode() override { return "opUnion("; }
};

//------------------------------------------------------------------------------
// Subtraction
//------------------------------------------------------------------------------
class SubtractionOpDataModel : public NodeDataModel
{
  Q_OBJECT

public:

	virtual ~SubtractionOpDataModel() { }

  QString caption() const override
  {
    return QString("Subtraction");
  }

  static QString name()
  {
    return QString("Subtraction");
  }

  void save(Properties &p) const override { p.put("model_name", name()); }

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex) override { return nullptr; }
  void setInData(std::shared_ptr<NodeData>, int) override { }
  std::vector<QWidget *> embeddedWidget() override { return std::vector<QWidget *>(); }

  DFNodeType getNodeType() const override { return DFNodeType::MIX; }
  std::string getShaderCode() override { return "opSubtraction("; }
};

//------------------------------------------------------------------------------
// Intersection
//------------------------------------------------------------------------------
class IntersectionDataModel : public NodeDataModel
{
  Q_OBJECT

public:

  virtual ~IntersectionDataModel() { }

  QString caption() const override
  {
    return QString("Intersection");
  }

  static QString name()
  {
    return QString("Intersection");
  }

  void save(Properties &p) const override { p.put("model_name", name()); }

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex) override { return nullptr; }
  void setInData(std::shared_ptr<NodeData>, int) override { }
  std::vector<QWidget *> embeddedWidget() override { return std::vector<QWidget *>(); }

  DFNodeType getNodeType() const override { return DFNodeType::MIX; }
  std::string getShaderCode() override { return "opIntersection("; }
};

//------------------------------------------------------------------------------
// Blend
//------------------------------------------------------------------------------
class BlendDataModel : public NodeDataModel
{
  Q_OBJECT

public:
	BlendDataModel();
  virtual ~BlendDataModel() {}

  QString caption() const override
  {
    return QString("Blend");
  }

  static QString name()
  {
    return QString("Blend");
  }

	void save(Properties &p) const override {
		p.put("model_name", name());
		p.put("blend", m_blend->text());
	}
	void restore(const Properties &p) override {
		m_blend->setText(p.values().find("blend").value().toString());
	}

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData> outData(PortIndex port) override { return nullptr; }
  void setInData(std::shared_ptr<NodeData>, int) override {}
	std::vector<QWidget *> embeddedWidget() override { return std::vector<QWidget *>{m_blend}; }

  DFNodeType getNodeType() const override { return DFNodeType::MIX; }
  std::string getShaderCode() override { return "opBlend("; }
	std::string getExtraParams() const override {
		if(m_blend->text().isEmpty())
			return ", 0.0";
		else
			return ", " + m_blend->text().toStdString();
	}
private:
	QLineEdit *m_blend;
};
