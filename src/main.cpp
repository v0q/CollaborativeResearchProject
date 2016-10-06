#include <QApplication>
#include <QGLFormat>

#include "glwidget.hpp"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QGLFormat glFormat;
	glFormat.setVersion(4, 1);
	glFormat.setProfile(QGLFormat::CoreProfile);
	glFormat.setSampleBuffers(true);

	// Create a GLWidget requesting our format
	GLWidget w(glFormat);
	w.show();

	return a.exec();
}
