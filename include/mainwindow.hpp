#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "nodeEditor/FlowScene.hpp"
#include "SceneWindow.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *_parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *m_ui;

  hsitho::SceneWindow *m_gl;
  FlowScene *m_nodes;
};

#endif // MAINWINDOW_H
