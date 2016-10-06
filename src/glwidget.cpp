#include <QCoreApplication>
#include <QKeyEvent>
#include <QTimer>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "glwidget.hpp"

GLWidget::GLWidget(const QGLFormat& format, QWidget* parent, int timerInterval) :
	QGLWidget(format, parent)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(timerInterval);
}

void GLWidget::initializeGL()
{
	// Initialise OpenGL functions (Qt)
	initializeOpenGLFunctions();

	QGLFormat glFormat = QGLWidget::format();
	if(!glFormat.sampleBuffers())
		qWarning() << "Could not enable sample buffers";

	// Set the clear color to black
	glClearColor(0.95f, 0.95f, 0.95f, 1.0f);


	// Screen space quad
	glm::vec3 verts[6];
	verts[0] = glm::vec3(0.f, 0.f, -2.f);
	verts[1] = glm::vec3(0.f, 1.f, -2.f);
	verts[2] = glm::vec3(1.f, 0.f, -2.f);
	verts[3] = glm::vec3(0.f, 1.f, -2.f);
	verts[4] = glm::vec3(1.f, 1.f, -2.f);
	verts[5] = glm::vec3(1.f, 0.f, -2.f);

	if(!(m_vao.create())) {
		qWarning() << "Could not create a vao";
		return;
	}

	m_vao.

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), glm::value_ptr(verts[0]), GL_STATIC_DRAW);
}

void GLWidget::resizeGL(int w, int h)
{
	// Set the viewport to window dimensions
	glViewport(0, 0, w * devicePixelRatio(), qMax(h, 1) * devicePixelRatio());
}

void GLWidget::paintGL()
{
	// Clear the buffer with the current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw stuff
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLWidget::keyPressEvent(QKeyEvent* e)
{
	switch(e->key())
	{
		case Qt::Key_Escape: {
			QCoreApplication::instance()->quit();
		} break;

		default: {
			QGLWidget::keyPressEvent(e);
		}
	}
}
