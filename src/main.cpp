#include <QApplication>
#include <QGLFormat>

#include "SceneWindow.hpp"

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	QSurfaceFormat format;
	format.setSamples(16);

	hsitho::SceneWindow window;
	window.setFormat(format);
	window.resize(1280, 720);
	window.show();

	window.setAnimating(true);

	return app.exec();
}
