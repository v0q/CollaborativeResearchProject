#pragma once

#include <QMainWindow>
#include <QColorDialog>

#include "nodeEditor/Node.hpp"
#include "nodeEditor/NodeGraphicsObject.hpp"
#include "nodeEditor/FlowView.hpp"
#include "nodeEditor/FlowScene.hpp"
#include "SceneWindow.hpp"
#include "CubePrimitiveDataModel.hpp"

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
  explicit MainWindow(QWidget *_parent = 0);
  ~MainWindow();
	void keyPressEvent(QKeyEvent *_event);

  std::unordered_map<QUuid, std::shared_ptr<Node>> getNodes() { return m_nodes->getNodes(); }

private:
  Ui::MainWindow *m_ui;

  hsitho::SceneWindow *m_gl;
  FlowScene *m_nodes;
	FlowView *m_flowView;
  //QColorDialogTester m_colorTester;

public slots:
  void nodeChanged() { emit(nodeEditorModified(getNodes())); }
signals:
  void nodeEditorModified(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes);
};
