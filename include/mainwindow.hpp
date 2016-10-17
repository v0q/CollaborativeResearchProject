#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_H
