#include <iostream>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "nodeEditor/NodeData.hpp"
#include "nodeEditor/DataModelRegistry.hpp"

#include "ExpressionEvaluator.hpp"
#include "nodes/DistanceFieldOutputDataModel.hpp"
#include "nodes/OperationDataModels.hpp"
#include "nodes/CopyNumDataModel.hpp"
#include "nodes/TimeDataModel.hpp"
#include "nodes/TranslateDataModel.hpp"
#include "nodes/RotateDataModel.hpp"
#include "nodes/ScaleDataModel.hpp"
#include "nodes/DistanceFieldOutputDataModel.hpp"
#include "nodes/ColorPickerDataModel.hpp"
#include "nodes/OutputDataModel.hpp"
#include "nodes/CubePrimitiveDataModel.hpp"
#include "nodes/SpherePrimitiveDataModel.hpp"
#include "nodes/TorusPrimitiveDataModel.hpp"
#include "nodes/CylinderPrimitiveDataModel.hpp"
#include "nodes/CapsulePrimitiveDataModel.hpp"
#include "nodes/PlanePrimitiveDataModel.hpp"
#include "nodes/TriangularPrismPrimitiveDataModel.hpp"
#include "nodes/HexagonalPrismPrimitiveDataModel.hpp"
#include "nodes/ConePrimitiveDataModel.hpp"
#include "nodes/CopyDataModel.hpp"

#include "nodes/MathsDataModels.hpp"

MainWindow::MainWindow(QWidget *_parent) :
  QMainWindow(_parent),
  m_ui(new Ui::MainWindow)
{
  std::locale::global(std::locale("en_GB"));
  m_ui->setupUi(this);
  m_gl = new hsitho::SceneWindow(this);

	DataModelRegistry::registerModel<CubePrimitiveDataModel>("Primitives");
  DataModelRegistry::registerModel<TorusPrimitiveDataModel>("Primitives");
  DataModelRegistry::registerModel<SpherePrimitiveDataModel>("Primitives");
  DataModelRegistry::registerModel<CylinderPrimitiveDataModel>("Primitives");
  DataModelRegistry::registerModel<CapsulePrimitiveDataModel>("Primitives");
  DataModelRegistry::registerModel<PlanePrimitiveDataModel>("Primitives");
  DataModelRegistry::registerModel<ConePrimitiveDataModel>("Primitives");
  DataModelRegistry::registerModel<TriangularPrismPrimitiveDataModel>("Primitives");
  DataModelRegistry::registerModel<HexagonalPrismPrimitiveDataModel>("Primitives");

	DataModelRegistry::registerModel<UnionDataModel>("Operations");
	DataModelRegistry::registerModel<SubtractionOpDataModel>("Operations");
  DataModelRegistry::registerModel<IntersectionDataModel>("Operations");
  DataModelRegistry::registerModel<BlendDataModel>("Operations");

	DataModelRegistry::registerModel<TranslateDataModel>("Transforms");
	DataModelRegistry::registerModel<ScaleDataModel>("Transforms");
  DataModelRegistry::registerModel<RotateDataModel>("Transforms");

	DataModelRegistry::registerModel<VectorDataModel>("Maths");
  DataModelRegistry::registerModel<ScalarDataModel>("Maths");
  DataModelRegistry::registerModel<SineDataModel>("Maths");
  DataModelRegistry::registerModel<CosineDataModel>("Maths");
  DataModelRegistry::registerModel<MultiplyDataModel>("Maths");
  DataModelRegistry::registerModel<DivideDataModel>("Maths");
	DataModelRegistry::registerModel<AdditionDataModel>("Maths");
	DataModelRegistry::registerModel<SubtractionDataModel>("Maths");

	DataModelRegistry::registerModel<TimeDataModel>("Misc");
	DataModelRegistry::registerModel<ColorPickerDataModel>("Color");
  DataModelRegistry::registerModel<OutputDataModel>("Generic");
	DataModelRegistry::registerModel<CopyDataModel>("Generic");
	DataModelRegistry::registerModel<CopyNumDataModel>("Generic");

  connect(this, SIGNAL(nodeEditorModified(std::unordered_map<QUuid, std::shared_ptr<Node>>)), m_gl, SLOT(nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>>)));

  m_nodes = new FlowScene(this);
  m_flowView = new FlowView(m_nodes);

  m_ui->m_sceneLayout->addWidget(m_gl, 0, 0, 1, 1);
  m_ui->m_nodeEditorLayout->addWidget(m_flowView, 0, 0, 1, 1);

	// Create the static distance field output node
	auto node = m_nodes->createNode(std::make_unique<DistanceFieldOutputDataModel>(), false, QUuid("ffffffff-ffff-ffff-ffff-ffffffffffff"));
	QRectF geom = m_flowView->sceneRect();

  QPoint pos;
  QRectF box = node->nodeGraphicsObject()->boundingRect();
  qreal x, y, w, h;
  geom.getRect(&x, &y, &w, &h);
  std::cout << w << " " << h << "\n";
  pos.setX(w/2 + box.width());
  pos.setY(h/2 + box.height());
  QPointF posView = m_flowView->mapToScene(pos);

  QFont f;
  f.setPixelSize(36);
  node->nodeGeometry().setSpacing(5);
  node->nodeGeometry().recalculateSize(QFontMetrics(f));
  node->nodeGraphicsObject()->setPos(posView);

  m_flowView->centerOn(node->nodeGraphicsObject().get());

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

//	cos(u_GlobalTime), 0, sin(u_GlobalTime), 0,
//	0, 1, 0, 0,
//	-sin(u_GlobalTime), 0, cos(u_GlobalTime), 0,
//	0, 0, 0, 1,

//	cos(1.04666674*copyNum), 0, sin(1.04666674*copyNum), 0,
//	0, 1, 0, 0,
//	-sin(1.04666674*copyNum), 0, cos(1.04666674*copyNum), 0,
//	0, 0, 0, 1,

	Mat4f tt ("cos(u_GlobalTime)", "0", "sin(u_GlobalTime)", "0",
						"0", "1", "0", "0",
						"-sin(u_GlobalTime)", "0", "cos(u_GlobalTime)", "0",
						"0", "0", "0", "1");

	Mat4f ttt("cos(1.04666674*copyNum)", "0", "sin(1.04666674*copyNum)", "0",
						"0", "1", "0", "0",
						"-sin(1.04666674*copyNum)", "0", "cos(1.04666674*copyNum)", "0",
						"0", "0", "0", "1");

//	std::cout << hsitho::Expressions::evaluate("( -sin(u_GlobalTime) ) * ( cos(1.04666674*copyNum) ) + ( 0 ) * ( 0 ) + ( cos(u_GlobalTime) ) * ( -sin(1.04666674*copyNum) ) + ( 0 ) * ( 0 )") << "\n";
//	exit(0);

//	(tt*ttt).print();
//	exit(0);

  Mat4f t("1.0", "0.0", "0.0", "0.0",
          "0.0", "1.0", "0.0", "0.0",
          "0.0", "0.0", "1.0", "0.0",
          "0.0", "0.0", "0.0", "1.0");
	Mat4f rx("1.0", "0.0", "0.0",		"0.0",
           "0.0", "a",	 "-b",	"0.0",
           "0.0", "b",	 "a",			"0.0",
           "0.0", "0.0", "0.0",		"1.0");
  Mat4f ry("a",			 "0.0", "b",		 "0.0",
           "0.0",		 "1.0", "0.0", "0.0",
           "-b",		 "0.0", "a",		 "0.0",
           "0.0",		 "0.0", "0.0", "1.0");
  Mat4f rz("a",		"-b", "0.0", "0.0",
           "b",		"a",			"0.0", "0.0",
           "0.0", "0.0",	"1.0", "0.0",
           "0.0", "0.0",	"0.0", "1.0");

//	t = t*rx;
//	t.print();
//	t = t*ry;
//	t.print();
//	t = t*rz;
//	t.print();

//  std::string expr("cos(u_GlobalTime) * 1.0 + sin(u_GlobalTime) * 0.0 + 0.0 * 0.0 + 0.0 * 0.0");
  std::string expr("( 6 + a ) * ( a - 2 + b )");
//	std::string nextExpr("( " + hsitho::Expressions::evaluate(expr) + " ) * ( 3 + 10 + 6 * a )");
//	std::string expr("cos(u_GlobalTime)+3 * 6");
//	std::string expr("2 * ( cos(u_GlobalTime) + 6 * 4 )");

//	std::cout << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( c ) + ( 1.0 ) * ( -s ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate(expr) << "\n";
//	std::cout << hsitho::Expressions::evaluate("( 6*a+a*a-6*2-a*2+6*b+a*b ) * ( 2 - c ) + 5") << "\n";
//	std::cout << "\n" << hsitho::Expressions::evaluate("( 0.0 ) * ( 0.0 ) + ( 0.0 ) * ( -b ) + ( 1.0 ) * ( a ) + ( 0.0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( -b*-b ) * ( a ) + ( a ) * ( b ) + ( -b*a ) * ( 0.0 ) + ( 0 ) * ( 0.0 )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("( -b*-b ) * ( a )") << "\n";
//	std::cout << hsitho::Expressions::evaluate("sin(6) * cos(u_GlobalTime)") << "\n";
//	exit(0);
//	exit(EXIT_SUCCESS);
}

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window receives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch(_event->key())
  {
    // escape key to quite
    case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
    case Qt::Key_S : m_nodes->save(); break;
    case Qt::Key_L : m_nodes->load(); break;
    default: break;
  }
}

MainWindow::~MainWindow()
{
  delete m_nodes;
  delete m_flowView;
  delete m_ui;
}
