#include <QGuiApplication>
#include <QKeyEvent>
#include <QDebug>

#include "Window.hpp"

namespace hsitho
{
  GLWindow::GLWindow() :
    m_timePassed(0.f)
  {
    makeCurrent();
  }

  void GLWindow::initializeGL()
  {
    initializeOpenGLFunctions();
    glInfo();
    glClearColor(0.f, 0.f, 0.f, 1.f);
    startTimer(10);
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

  void GLWindow::timerEvent(QTimerEvent *_timer)
  {
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
