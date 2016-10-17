#include "nodeEditor/NodeData.hpp"
#include "nodeEditor/FlowScene.hpp"
#include "nodeEditor/FlowView.hpp"

#include <QApplication>
#include <QGLFormat>

#include "nodeEditor/DataModelRegistry.hpp"

//#include "SceneWindow.hpp"
#include "mainwindow.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setDepthBufferSize(16);
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);

  QSurfaceFormat::setDefaultFormat(format);

  MainWindow window;
//  hsitho::SceneWindow window;
//	window.setFormat(format);
  window.show();

	return app.exec();
}
