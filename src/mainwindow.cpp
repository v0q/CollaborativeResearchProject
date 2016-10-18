#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "nodeEditor/NodeData.hpp"
#include "nodeEditor/FlowView.hpp"
#include "nodeEditor/DataModelRegistry.hpp"

#include "CubePrimitiveDataModel.hpp"

MainWindow::MainWindow(QWidget *_parent) :
  QMainWindow(_parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl = new hsitho::SceneWindow(this);

  DataModelRegistry::registerModel<CubePrimitiveDataModel>();

  m_nodes = new FlowScene;

  m_ui->m_sceneLayout->addWidget(m_gl, 0, 0, 1, 1);
  m_ui->m_nodeEditorLayout->addWidget(new FlowView(m_nodes), 0, 0, 1, 1);
}

MainWindow::~MainWindow()
{
  delete m_ui;
}
