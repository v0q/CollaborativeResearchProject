#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QKeyEvent>

namespace hsitho
{
  class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions
  {
	public:
    explicit GLWindow();
		~GLWindow() {}

    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(const int _w, const int _h) override;

    void glInfo();

  private:
    void keyPressEvent(QKeyEvent *_event) override;
	};
}
