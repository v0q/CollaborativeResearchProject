#pragma once

#include <QGLWidget>

#include <QGLBuffer>
#include <QGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

class GLWidget : public QGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	GLWidget(const QGLFormat& format, QWidget* parent = 0, int timerInterval = 16);

protected:
	virtual void initializeGL();
	virtual void resizeGL( int w, int h );
	virtual void paintGL();

	virtual void keyPressEvent(QKeyEvent* e);

private:
	QOpenGLVertexArrayObject m_vao;
	GLuint m_vbo;
};
