#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include "ShaderManager.hpp"
#include "Window.hpp"

namespace hsitho
{
  class SceneWindow : public GLWindow
  {
	public:
    SceneWindow(QWidget *_parent, std::list<Node> m_priorityStatus);
		~SceneWindow();

    void initializeGL();
    void paintGL();

    int getPriorityQueueStatus();
    void setPriorityHigh();
    void setPriorityLow();

    int _priorityStatus;


	private:
		std::string recurseNodeTree(std::shared_ptr<Node> _node);
    //std::vector m_priorityQueue;
    std::list<Node> m_priorityStatus;

    std::shared_ptr<ShaderManager> m_shaderMan;
		Node *m_outputNode;
		QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer m_vbo;


    int m_priorityId;
    int m_queuePlace;


  public slots:
    virtual void nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes);
  };
}
