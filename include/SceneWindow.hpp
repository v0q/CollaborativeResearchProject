#pragma once

#include "Window.hpp"

namespace hsitho
{
	class SceneWindow : public GLWindow
	{
	public:
		SceneWindow();
		~SceneWindow() {}

		void initialize() Q_DECL_OVERRIDE;
		void render() Q_DECL_OVERRIDE;

	private:
		GLuint m_posAttr;
		GLuint m_colAttr;
		GLuint m_matrixUniform;

		QOpenGLShaderProgram *m_program;
		int m_frame;
	};
}
