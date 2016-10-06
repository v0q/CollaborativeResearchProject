#include <fstream>
#include <iostream>

#include "SceneWindow.hpp"

namespace hsitho
{
	SceneWindow::SceneWindow() :
		m_program(0),
		m_frame(0)
	{
	}

	void SceneWindow::initialize()
	{
		m_program = new QOpenGLShaderProgram(this);

		std::ifstream file;

		file.open("shaders/vert.glsl", std::ios_base::in);
		if(file.is_open())
		{
			std::string src = std::string((std::istreambuf_iterator<char>(file)),
																		(std::istreambuf_iterator<char>()));;
			const char *csrc = src.c_str();
			m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, csrc);
		}
		file.close();
		file.open("shaders/frag.glsl", std::ios_base::in);
		if(file.is_open())
		{
			std::string src = std::string((std::istreambuf_iterator<char>(file)),
																		(std::istreambuf_iterator<char>()));;
			const char *csrc = src.c_str();
			m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, csrc);
		}

		file.close();

		m_program->link();
		m_posAttr = m_program->attributeLocation("vertex");
	}

	void SceneWindow::render()
	{
		const qreal retinaScale = devicePixelRatio();
		glViewport(0, 0, width() * retinaScale, height() * retinaScale);

		glClear(GL_COLOR_BUFFER_BIT);

		m_program->bind();

		QMatrix4x4 matrix;
		matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
		matrix.translate(0, 0, -2);
		matrix.rotate(100.0f * m_frame, 0, 1, 0);

		m_program->setUniformValue(m_matrixUniform, matrix);

		GLfloat vertices[] = {
				0.0f, 0.707f,
				-0.5f, -0.5f,
				0.5f, -0.5f
		};

		GLfloat colors[] = {
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
		};

		glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		m_program->release();

		++m_frame;
	}
}
