#include <iostream>
#include <boost/lexical_cast.hpp>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "nodeEditor/NodeData.hpp"
#include "nodeEditor/DataModelRegistry.hpp"

//#include "calculator/NumberSourceDataModel.hpp"
//#include "calculator/NumberDisplayDataModel.hpp"
//#include "calculator/MultiplicationModel.hpp"
#include "ExpressionEvaluator.hpp"
#include "nodes/CubePrimitiveDataModel.hpp"
#include "nodes/UnionDataModel.hpp"
#include "nodes/TimeDataModel.hpp"
#include "nodes/TranslateDataModel.hpp"
#include "nodes/RotateDataModel.hpp"
#include "nodes/VectorDataModel.hpp"
#include "nodes/ScalarDataModel.hpp"
#include "nodes/DistanceFieldOutputDataModel.hpp"



MainWindow::MainWindow(QWidget *_parent) :
  QMainWindow(_parent),
  m_ui(new Ui::MainWindow)
{
  std::locale::global(std::locale("en_GB"));
  m_ui->setupUi(this);
	m_gl = new hsitho::SceneWindow(this);

  DataModelRegistry::registerModel<TimeDataModel>();
	DataModelRegistry::registerModel<CubePrimitiveDataModel>();
	DataModelRegistry::registerModel<UnionDataModel>();
	DataModelRegistry::registerModel<TranslateDataModel>();
	DataModelRegistry::registerModel<RotateDataModel>();
	DataModelRegistry::registerModel<VectorDataModel>();
	DataModelRegistry::registerModel<ScalarDataModel>();
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

  std::string expr("cos(u_GlobalTime) * 1.0 + sin(u_GlobalTime) * 0.0 + 0.0 * 0.0 + 0.0 * 0.0");
  std::cout << hsitho::Expressions::evaluate(expr) << "\n";
//	hsitho::evalExp::evaluate(std::string("5.0 * 2.0 + sin(u_GlobalTime) * 1.0"));
//	std::cout << std::atof("5.0f") << " " << std::atof("u_GlobalTime") << " " << derp << "\n";
}

MainWindow::~MainWindow()
{
	delete m_nodes;
	delete m_flowView;
  delete m_ui;
}
