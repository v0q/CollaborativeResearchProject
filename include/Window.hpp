#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QTime>

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
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief number of frames for the fps counter
		//----------------------------------------------------------------------------------------------------------------------
		int m_frames;

  private:
    void keyPressEvent(QKeyEvent *_event) override;
		void timerEvent(QTimerEvent *_event) override;

    float m_timePassed;

		//----------------------------------------------------------------------------------------------------------------------
		/// @brief flag for the fps timer
		//----------------------------------------------------------------------------------------------------------------------
		int m_fpsTimer;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief the fps to draw
		//----------------------------------------------------------------------------------------------------------------------
		int m_fps;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief timer for re-draw
		//----------------------------------------------------------------------------------------------------------------------
		QTime m_timer;

  public slots:
    virtual void nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes) = 0;
	};
}
