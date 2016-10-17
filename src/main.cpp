//#include "nodeEditor/NodeData.hpp"
//#include "nodeEditor/FlowScene.hpp"
//#include "nodeEditor/FlowView.hpp"

#include <QApplication>
#include <QGLFormat>

//#include "nodeEditor/DataModelRegistry.hpp"

#include "SceneWindow.hpp"

int main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setDepthBufferSize(16);
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);

  hsitho::SceneWindow window;
	window.setFormat(format);
	window.resize(1280, 720);
	window.show();
  window.setTitle("hsitho");

	return app.exec();
}
