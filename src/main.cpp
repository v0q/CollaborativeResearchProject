#include <QApplication>
#include <QGLFormat>
#include <locale>

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
  window.show();

	return app.exec();
}
