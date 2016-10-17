#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *_parent) :
  QMainWindow(_parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl = new hsitho::SceneWindow(this);

  m_ui->m_nodeEditorLayout->addWidget(m_gl);
}

MainWindow::~MainWindow()
{
  delete m_ui;
}
