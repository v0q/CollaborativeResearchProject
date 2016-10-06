#include <fstream>
#include <iostream>

#include "SceneWindow.hpp"

namespace hsitho
{
  SceneWindow::SceneWindow() :
    m_shaderMan(hsitho::ShaderManager::instance())
	{
	}

  void SceneWindow::initializeGL()
  {
    GLWindow::initializeGL();

    m_shaderMan->createShader("ScreenQuad", "screenQuad.vert", "raymarchprimitives.frag");
    m_shaderMan->useShader("ScreenQuad");

    // Generate and bind VAO and VBO buffers
    GLuint vbo;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

  void SceneWindow::paintGL()
	{
    const qreal retinaScale = devicePixelRatio();
    GLfloat resolution[] = {1280, 720};
		glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float vertices[] = {
      // First triangle
      -1.0f,  1.0f,
      -1.0f, -1.0f,
       1.0f,  1.0f,
      // Second triangle
      -1.0f, -1.0f,
       1.0f, -1.0f,
       1.0f,  1.0f
    };

    float uvs[] = {
      0.0f, 1.0f,
      0.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f
    };

    glBindVertexArray(m_vao);
    GLint posAttrib = glGetAttribLocation(m_shaderMan->getProgram(), "a_Position");
    GLint uvAttrib = glGetAttribLocation(m_shaderMan->getProgram(), "a_fragCoord");

    glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(uvAttrib);

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0, uvs);

    m_shaderMan->setUniform1f("u_globalTime", getTimePassed());
    m_shaderMan->setUniform2f("u_resolution", resolution);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glDisableVertexAttribArray(posAttrib);
    glDisableVertexAttribArray(uvAttrib);
  }
}
