#pragma once

#include <QMainWindow>
#include <QColorDialog>

#include "nodeEditor/Node.hpp"
#include "nodeEditor/NodeGraphicsObject.hpp"
#include "nodeEditor/FlowView.hpp"
#include "nodeEditor/FlowScene.hpp"
#include "SceneWindow.hpp"
#include "CubePrimitiveDataModel.hpp"

/// \file mainwindow.hpp
/// \brief Basic UI and the main window combining the node editor and the scene view
/// \authors Teemu Lindborg & Phil Gifford
/// \version 1.0
/// \date 22/01/17 Updated to NCCA Coding standard
/// Revision History :
/// Initial Version 05/10/16

namespace Ui
{
  class MainWindow;
}
namespace hsitho
{
  class SceneWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  ///
  /// \brief MainWindow Default ctor
  /// \param _parent
  ///
  explicit MainWindow(QWidget *_parent = 0);
  ///
  /// \brief ~MainWindow Default dtor
  ///
  ~MainWindow();
  ///
  /// \brief keyPressEvent Triggered when a button is pressed inside the application
  /// \param _event Details about the button press
  ///
  void keyPressEvent(QKeyEvent *_event);

  ///
  /// \brief getNodes Function that calls the node scene for the nodes
  /// \return The nodes in the scene
  ///
  std::unordered_map<QUuid, std::shared_ptr<Node>> getNodes() { return m_nodes->getNodes(); }

private:
  ///
  /// \brief m_ui This window
  ///
  Ui::MainWindow *m_ui;
  ///
  /// \brief m_gl The scene view
  ///
  hsitho::SceneWindow *m_gl;
  ///
  /// \brief m_nodes Flow scene, contains the functionality of the node scene
  ///
  FlowScene *m_nodes;
  ///
  /// \brief m_flowView Visual representation of the flow scene
  ///
	FlowView *m_flowView;

public slots:
  ///
  /// \brief nodeChanged Called when something in the node editor changes
  /// DEPRECATED, replaced by triggered which is called when the user wants to compile the scnee
  ///
	void nodeChanged() { /*emit(nodeEditorModified(getNodes()));*/ }
  ///
  /// \brief triggered Called when the user presses Compile or it's hotkey
  ///
	void triggered(bool) { emit(nodeEditorModified(getNodes())); }
signals:
  ///
  /// \brief nodeEditorModified Signal to tell the scene window to traverse the node tree and regenerate the shader code
  /// \param _nodes Nodes passed from the editor to the render view
  ///
  void nodeEditorModified(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes);
};
