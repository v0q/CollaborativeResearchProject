#include <iostream>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "nodeEditor/NodeData.hpp"
#include "nodeEditor/DataModelRegistry.hpp"

#include "ExpressionEvaluator.hpp"
#include "nodes/DistanceFieldOutputDataModel.hpp"
#include "nodes/CollapsedNodeDataModel.hpp"
#include "nodes/OperationDataModels.hpp"
#include "nodes/CopyNumDataModel.hpp"
#include "nodes/TimeDataModel.hpp"
#include "nodes/TranslateDataModel.hpp"
#include "nodes/RotateDataModel.hpp"
#include "nodes/ScaleDataModel.hpp"
#include "nodes/DistanceFieldOutputDataModel.hpp"
#include "nodes/ColorPickerDataModel.hpp"
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

  // Register the nodes
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
	DataModelRegistry::registerModel<InputDataModel>("Generic");
	DataModelRegistry::registerModel<CopyDataModel>("Generic");
	DataModelRegistry::registerModel<CopyNumDataModel>("Generic");
	DataModelRegistry::registerModel<CollapsedNodeDataModel>("Generic");

  connect(this, SIGNAL(nodeEditorModified(std::unordered_map<QUuid, std::shared_ptr<Node>>)), m_gl, SLOT(nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>>)));
	connect(m_ui->actionCompile, &QAction::triggered, this, &MainWindow::triggered);

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
}

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window receives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch(_event->key())
  {
    // escape key to quite
    case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
		case Qt::Key_B : {
			if(_event->modifiers() == Qt::ShiftModifier) {
				emit(nodeEditorModified(getNodes()));
			}
		} break;
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
