#include <QGuiApplication>
#include <QKeyEvent>
#include <QDebug>

#include "Window.hpp"

namespace hsitho
{
  GLWindow::GLWindow()
  {
    makeCurrent();
  }

  void GLWindow::initializeGL()
  {
    initializeOpenGLFunctions();
    glInfo();
    glClearColor(0.f, 0.f, 0.f, 1.f);
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
