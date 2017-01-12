#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <iostream>

#include "ShaderManager.hpp"
#include "Window.hpp"

namespace hsitho
{
  class SceneWindow : public GLWindow
  {
  public:
    SceneWindow(QWidget *_parent);
    ~SceneWindow();

    void initializeGL();
    void paintGL();

    void createCamera();


  private:
    std::shared_ptr<ShaderManager> m_shaderMan;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer m_vbo;




    const char *m_shaderUserInput;

  public slots:
    virtual void nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes);
  };
}
