#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "nodeEditor/NodeData.hpp"
#include "nodeEditor/DataModelRegistry.hpp"

//#include "calculator/NumberSourceDataModel.hpp"
//#include "calculator/NumberDisplayDataModel.hpp"
//#include "calculator/MultiplicationModel.hpp"
#include "CubePrimitiveDataModel.hpp"

#include "UnionDataModel.hpp"
#include "DistanceFieldOutputDataModel.hpp"

#include <iostream>


MainWindow::MainWindow(QWidget *_parent) :
  QMainWindow(_parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
	m_gl = new hsitho::SceneWindow(this);


	DataModelRegistry::registerModel<CubePrimitiveDataModel>();
	DataModelRegistry::registerModel<UnionDataModel>();
//	DataModelRegistry::registerModel<NumberSourceDataModel>();
//	DataModelRegistry::registerModel<NumberDisplayDataModel>();
//	DataModelRegistry::registerModel<MultiplicationModel>();

	connect(this, SIGNAL(nodeEditorModified(std::unordered_map<QUuid, std::shared_ptr<Node>>)), m_gl, SLOT(nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>>)));

	m_nodes = new FlowScene(this);
	m_flowView = new FlowView(m_nodes);

	m_ui->m_sceneLayout->addWidget(m_gl, 0, 0, 1, 1);
	m_ui->m_nodeEditorLayout->addWidget(m_flowView, 0, 0, 1, 1);

	// Create the static distance field output node
	auto node = m_nodes->createNode(std::make_unique<DistanceFieldOutputDataModel>(), false);
	QRect geom = m_flowView->geometry();

	QPoint pos;
	QRectF box = node->nodeGraphicsObject()->boundingRect();
	int w, h;
	geom.getRect(&w, &h, &w, &h);
	pos.setX(w + box.width());
	pos.setY(h + box.height());
	QPointF posView = m_flowView->mapToScene(pos);

	QFont f;
	f.setPixelSize(36);
	node->nodeGeometry().setSpacing(5);
	node->nodeGeometry().recalculateSize(QFontMetrics(f));
	node->nodeGraphicsObject()->setPos(posView);

	m_flowView->scaleDown();
}

MainWindow::~MainWindow()
{
	delete m_nodes;
	delete m_flowView;
  delete m_ui;
}
