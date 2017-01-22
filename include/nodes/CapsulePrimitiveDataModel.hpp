#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <iostream>

#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/DistanceFieldData.hpp"

/// \file CapsulePrimitiveDataModel.hpp
/// \brief Node for creating a Capsule
///        Built around the NodeDataModel by Dimitry Pinaev [https://github.com/paceholder/nodeeditor]
/// \authors Teemu Lindborg & Phil Gifford
/// \version 1.0
/// \date 22/01/17 Updated to NCCA Coding standard
/// Revision History :
/// Initial Version 05/10/16

class CapsulePrimitiveDataModel : public NodeDataModel
{
  Q_OBJECT

public:

  ///
  /// \brief CapsulePrimitiveDataModel Default ctor, initialises relevant variables
  ///
	CapsulePrimitiveDataModel();
	virtual ~CapsulePrimitiveDataModel() {}

  ///
  /// \brief caption Used to render the name of the node
  /// \return Name of the node
  ///
  QString caption() const override
  {
    return QString("Capsule");
  }

  ///
  /// \brief name Used to show the name of the node in the right-click menu
  /// \return The name of the node
  ///
  static QString name()
  {
    return QString("Capsule");
  }

  ///
  /// \brief save Saves anything that is needed when this node is loaded from a file
  /// \param p Properties used to store the data in
  ///
  void save(Properties &p) const override;
  ///
  /// \brief restore Restores the saved properties when a file is loaded
  /// \param p Properties to read the stored data from
  ///
	void restore(const Properties &p) override;

  ///
  /// \brief nPorts Returns the number of ports the node has for a given port type
  /// \param portType Type of the port to query (In, Out)
  /// \return The number of ports
  ///
  unsigned int nPorts(PortType portType) const override;
  ///
  /// \brief dataType Returns the queried data type of the input/output in the given port
  /// \param portType Type of the port to query
  /// \param portIndex Index of the port to query
  /// \return The data type associated with the port
  ///
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  ///
  /// \brief outData Returns what ever the output from the given port is supposed to give when data is requested
  /// \param port Output to query the data from
  /// \return The data that's being queried
  ///
  std::shared_ptr<NodeData> outData(PortIndex port) override;

  ///
  /// \brief setInData Sets the data inside the node when something's connected to an input node
  /// \param _data Data propagated through the port
  /// \param _portIndex Port that the input is coming from
  ///
  void setInData(std::shared_ptr<NodeData> _data, PortIndex _portIndex) override;

	void sizeEdit(QString const);

  ///
  /// \brief embeddedWidget Returns the editable QWidgets inside the node
  /// \return Editable QWidgets
  ///
  std::vector<QWidget *> embeddedWidget() override;

  ///
  /// \brief getNodeType Returns the type of the node, used when traversing the tree
  /// \return The shader type
  ///
  DFNodeType getNodeType() const override { return DFNodeType::PRIMITIVE; }
  ///
  /// \brief getShaderCode Returns the shader code specific to this node with the relevant variables
  /// \return The shader code
  ///
  std::string getShaderCode() override;
  ///
  /// \brief setTransform Sets the transformation matrix for this node
  /// \param _t New transforamtion matrix
  ///
	void setTransform(const Mat4f &_t) override;

private:
  Vec4f m_color;
	Vec4f m_startPos;
	Vec4f m_endPos;
	QLineEdit *m_r;
  std::string m_transform;
};
