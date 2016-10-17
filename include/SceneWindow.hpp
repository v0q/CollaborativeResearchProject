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
		SceneWindow();
		~SceneWindow();

    void initializeGL();
    void paintGL();

	private:
    std::shared_ptr<ShaderManager> m_shaderMan;
		QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer m_vbo;
	};
}
