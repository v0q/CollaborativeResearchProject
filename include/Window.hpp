#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QTime>

#include "nodeEditor/FlowScene.hpp"

/// \file Window.hpp
/// \brief Simple base class for a Qt OpenGL window, used to inherit from
///        FPS counter is based on the FPS counter in NGL by Jon Macey
/// \author Teemu Lindborg
/// \version 1.0
/// \date 25/04/16 Initial version

namespace hsitho
{
  class GLWindow : public QOpenGLWidget, protected QOpenGLFunctions
  {
  Q_OBJECT
  public:
    explicit GLWindow(QWidget *_parent);
    ~GLWindow();

    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(const int _w, const int _h) override;

    void glInfo();
    float getTimePassed() { return m_timePassed; }
		int m_frames;

  private:
    void keyPressEvent(QKeyEvent *_event) override;
		void timerEvent(QTimerEvent *_event) override;

    float m_timePassed;
    int m_fpsTimer;
    int m_fps;
		QTime m_timer;

  public slots:
    virtual void nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes) = 0;
	};
}
