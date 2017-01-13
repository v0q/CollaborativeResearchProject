#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <fstream>

#include <glm/glm.hpp>

#include "nodes/DistanceFieldData.hpp"
#include "ShaderManager.hpp"
#include "Window.hpp"

struct Branch
{
  std::string m_sc;
  std::vector<Branch> m_branches;
};

namespace hsitho
{
  class SceneWindow : public GLWindow
  {
  public:
    SceneWindow(QWidget *_parent);
    ~SceneWindow();

    void initializeGL();
    void paintGL();
		void mousePressEvent(QMouseEvent *_event);
		void mouseMoveEvent(QMouseEvent *_event);

  private:
		std::string recurseNodeTree(std::shared_ptr<Node> _node, Mat4f _t, PortIndex portIndex = 0, unsigned int _cp = 0);
    std::shared_ptr<ShaderManager> m_shaderMan;
    Node *m_outputNode;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer m_vbo;
    std::string m_shaderStart;
    std::string m_shaderEnd;

		glm::vec4 m_cam;
		glm::vec3 m_camU;
		glm::vec3 m_camL;

		int m_origX;
		int m_origY;

  public slots:
    virtual void nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes);
  };
}
