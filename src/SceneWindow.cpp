#include <fstream>
#include <iostream>




#include "SceneWindow.hpp"

namespace hsitho
{
  SceneWindow::SceneWindow() :
    m_shaderMan(hsitho::ShaderManager::instance())
	{
	}

	SceneWindow::~SceneWindow()
	{
		delete m_vao;
	}

  void SceneWindow::initializeGL()
  {
		GLWindow::initializeGL();

		m_shaderMan->createShader("ScreenQuad", "screenQuad.vert", "crystalbeacon.frag", this);
		m_shaderMan->useShader("ScreenQuad");

		// Generate and bind VAO and VBO buffers
		m_vao = new QOpenGLVertexArrayObject(this);
		m_vao->create();
		m_vao->bind();

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

		m_vbo.create();
		m_vbo.bind();
		m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_vbo.allocate(nullptr, sizeof(vertices)*sizeof(uvs));
		m_vbo.write(0, vertices, sizeof(vertices));
		m_vbo.write(sizeof(vertices), uvs, sizeof(uvs));
	}

  void SceneWindow::paintGL()
	{
    const qreal retinaScale = devicePixelRatio();
		GLfloat resolution[] = {width() * (float)retinaScale, height() * (float)retinaScale};
		glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_vao->bind();
		m_vbo.bind();
		m_shaderMan->getProgram()->bind();

		m_shaderMan->getProgram()->enableAttributeArray("a_Position");
		m_shaderMan->getProgram()->enableAttributeArray("a_FragCoord");

		GLuint posLocation = m_shaderMan->getProgram()->attributeLocation("a_Position");
		GLuint uvLocation = m_shaderMan->getProgram()->attributeLocation("a_FragCoord");

		m_shaderMan->getProgram()->setAttributeBuffer(posLocation, GL_FLOAT, 0, 2, 0);
		m_shaderMan->getProgram()->setAttributeBuffer(uvLocation, GL_FLOAT, 6*2*sizeof(float), 2, 0);
		m_shaderMan->getProgram()->setUniformValue("u_GlobalTime", getTimePassed());
		m_shaderMan->getProgram()->setUniformValueArray("u_Resolution", resolution, 1, 2);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		m_shaderMan->getProgram()->disableAttributeArray("a_Position");
		m_shaderMan->getProgram()->disableAttributeArray("a_FragCoord");
		m_shaderMan->getProgram()->release();

		m_vbo.release();
		m_vao->release();
  }
}
