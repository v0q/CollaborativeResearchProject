#include <QGuiApplication>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>

#include "Window.hpp"

namespace hsitho
{
  GLWindow::GLWindow(QWidget *_parent) :
    QOpenGLWidget(_parent),
    m_timePassed(0.f)
  {
    this->resize(_parent->size());
//    makeCurrent();
  }

  GLWindow::~GLWindow()
  {
  }

  void GLWindow::initializeGL()
  {
    initializeOpenGLFunctions();
    glInfo();
    glClearColor(0.f, 0.f, 0.f, 1.f);
		m_fpsTimer = startTimer(0);
		m_fps = 0;
		m_frames = 0;
		m_timer.start();
	}

  void GLWindow::paintGL()
	{
  }

  void GLWindow::resizeGL(const int _w, const int _h)
  {
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, _w * retinaScale, _h * retinaScale);
  }

  void GLWindow::keyPressEvent(QKeyEvent *_event)
  {
    switch(_event->key())
    {
      case Qt::Key_Escape: {
        QGuiApplication::exit(EXIT_SUCCESS);
      } break;
      default: break;
    }
  }

	void GLWindow::timerEvent(QTimerEvent *_event)
  {
		if(_event->timerId() == m_fpsTimer)
		{
			if(m_timer.elapsed() > 1000.0)
			{
				m_fps = m_frames;
				m_frames = 0;
				m_timer.restart();
			}
		}

		this->window()->setWindowTitle(QString("FPS: ") + QString::number(m_fps));
    m_timePassed += 0.1;
    update();
  }

  void GLWindow::glInfo()
  {
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
    #define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
      switch (format().profile())
      {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
      }
    #undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
  }


}
