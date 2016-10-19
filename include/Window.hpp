#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>

#include "nodeEditor/FlowScene.hpp"

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

  private:
    void keyPressEvent(QKeyEvent *_event) override;
    void timerEvent(QTimerEvent *_timer) override;

    float m_timePassed;

  public slots:
    virtual void nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes) = 0;
	};
}
