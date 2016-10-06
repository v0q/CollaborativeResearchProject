#include <QCoreApplication>
#include <QKeyEvent>
#include <QTimer>
#include <iostream>

#include "glwidget.hpp"

GLWidget::GLWidget(const QGLFormat& format, QWidget* parent, int timerInterval) :
	QGLWidget(format, parent),
	m_vertexBuffer(QGLBuffer::VertexBuffer)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(timerInterval);
}

void GLWidget::initializeGL()
{
	QGLFormat glFormat = QGLWidget::format();
	if(!glFormat.sampleBuffers())
	qWarning() << "Could not enable sample buffers";

	// Set the clear color to black
	glClearColor(0.95f, 0.95f, 0.95f, 1.0f);

	// Prepare a complete shader program…
	if(!prepareShaderProgram("shaders/vert.glsl", "shaders/frag.glsl"))
		return;

	// We need us some vertex data. Start simple with a triangle ;-)
	float points[] = {-0.5f, -0.5f, 0.0f,
										1.0f,	0.5f, -0.5f,
										0.0f, 1.0f, 0.0f,
										0.5f, 0.0f, 1.0f};
	m_vertexBuffer.create();
	m_vertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
	if(!m_vertexBuffer.bind())
	{
		qWarning() << "Could not bind vertex buffer to the context";
		return;
	}
	m_vertexBuffer.allocate(points, 3 * 4 * sizeof(float));

	// Bind the shader program so that we can associate variables from
	// our application to the shaders
	if (!m_shader.bind())
	{
		qWarning() << "Could not bind shader program to context";
		return;
	}

	// Enable the "vertex" attribute to bind it to our currently bound
	// vertex buffer.
	m_shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);
	m_shader.enableAttributeArray("vertex");
}

bool GLWidget::prepareShaderProgram(const QString& vertexShaderPath, const QString& fragmentShaderPath)
{
	// First we load and compile the vertex shader…
	bool result = m_shader.addShaderFromSourceFile(QGLShader::Vertex, vertexShaderPath);
	if(!result)
		qWarning() << m_shader.log();

	// …now the fragment shader…
	result = m_shader.addShaderFromSourceFile(QGLShader::Fragment, fragmentShaderPath);
	if(!result)
		qWarning() << m_shader.log();

	// …and finally we link them to resolve any references.
	result = m_shader.link();
	if(!result)
		qWarning() << "Could not link shader program:" << m_shader.log();

	return result;
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
