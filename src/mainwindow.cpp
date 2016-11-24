#include <iostream>
#include <boost/lexical_cast.hpp>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "nodeEditor/NodeData.hpp"
#include "nodeEditor/DataModelRegistry.hpp"

#include "CubePrimitiveDataModel.hpp"

#include "UnionDataModel.hpp"
#include "DistanceFieldOutputDataModel.hpp"

#include "ExpressionEvaluator.hpp"
#include "nodes/SpherePrimitiveDataModel.hpp"
#include "nodes/CubePrimitiveDataModel.hpp"
#include "nodes/UnionDataModel.hpp"
#include "nodes/BlendDataModel.hpp"
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

  DataModelRegistry::registerModel<TimeDataModel>("Misc");
  DataModelRegistry::registerModel<CubePrimitiveDataModel>("Primitives");
	DataModelRegistry::registerModel<SpherePrimitiveDataModel>("Primitives");
	DataModelRegistry::registerModel<UnionDataModel>("Operations");
	DataModelRegistry::registerModel<BlendDataModel>("Operations");
  DataModelRegistry::registerModel<TranslateDataModel>("Transforms");
  DataModelRegistry::registerModel<RotateDataModel>("Transforms");
  DataModelRegistry::registerModel<VectorDataModel>("Maths");
  DataModelRegistry::registerModel<ScalarDataModel>("Maths");

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

//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 1.0 ) * ( c ) + ( 0.0 ) * ( -s ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 1.0 ) * ( 1.0 ) + ( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 1.0 ) * ( 0.0 ) + ( 0.0 ) * ( c ) + ( 0.0 ) * ( -s ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 1.0 ) * ( 0.0 ) + ( 0.0 ) * ( s ) + ( 0.0 ) * ( c ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 1.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( 1.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 1.0 ) + ( 1.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 1.0 ) * ( c ) + ( 0.0 ) * ( -s ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 1.0 ) * ( s ) + ( 0.0 ) * ( c ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 1.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( 1.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 1.0 ) + ( 0.0 ) * ( 0.0 ) + ( 1.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( s ) + ( 1.0 ) * ( c ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 ) + ( 1.0 ) * ( 0.0 ) + ( 0.0 ) * ( 1.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 1.0 ) + ( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( 0.0 ) + ( 1.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( c ) + ( 0.0 ) * ( -s ) + ( 1.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( s ) + ( 0.0 ) * ( c ) + ( 1.0 ) * ( 0.0 )") << "\n";

//	Mat4f t("1.0", "0.0", "0.0", "0.0",
//					"0.0", "1.0", "0.0", "0.0",
//					"0.0", "0.0", "1.0", "0.0",
//					"0.0", "0.0", "0.0", "1.0");
	Mat4f rx("1.0", "0.0", "0.0",		"0.0",
					 "0.0", "a",	 "-b",	"0.0",
					 "0.0", "b",	 "a",			"0.0",
					 "0.0", "0.0", "0.0",		"1.0");

//	t = t*t;
//	t.print();

//  std::string expr("cos(u_GlobalTime) * 1.0 + sin(u_GlobalTime) * 0.0 + 0.0 * 0.0 + 0.0 * 0.0");
	std::string expr("( a - 2 ) * ( a + 6 )");
//	std::string nextExpr("( " + hsitho::Expressions::evaluate(expr) + " ) * ( 3 + 10 + 6 * a )");
//	std::string expr("cos(u_GlobalTime)+3 * 6");
//	std::string expr("2 * ( cos(u_GlobalTime) + 6 * 4 )");

//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( c ) + ( 1.0 ) * ( -s ) + ( 0.0 ) * ( 0.0 )") << "\n";
	std::cout << hsitho::Expressions::evaluate(expr) << "\n";
	std::cout << hsitho::Expressions::evaluate("( -b*-b ) * ( a )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( -b*-b ) * ( a ) + ( a ) * ( b ) + ( -b*a ) * ( 0.0 ) + ( 0 ) * ( 0.0 )") << "\n";
	exit(0);
//	exit(EXIT_SUCCESS);
}

MainWindow::~MainWindow()
{
	delete m_nodes;
	delete m_flowView;
  delete m_ui;
}
