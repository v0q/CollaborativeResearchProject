#include <QOpenGLShader>
#include <iostream>
#include <cstdlib>

#include "ShaderManager.hpp"

namespace hsitho
{
  std::shared_ptr<ShaderManager> ShaderManager::m_instance = 0;

	ShaderManager::~ShaderManager()
	{
	}

  void ShaderManager::createShader(const std::string &_name, const QString &_vs, const QString &_fs)
	{
		QOpenGLShaderProgram *program = new QOpenGLShaderProgram();

		program->addShaderFromSourceFile(QOpenGLShader::Vertex, "./shaders/" + _vs);
		program->addShaderFromSourceFile(QOpenGLShader::Fragment, "./shaders/" + _fs);

    program->link();

		m_shaders[_name] = program;
  }

  void ShaderManager::updateShader(const char *_shaderCode)
  {
		if(m_program != nullptr)
		{
			m_program->release();

			m_program->removeAllShaders();
			m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "./shaders/screenQuad.vert");
			m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, QString(_shaderCode));

			m_program->link();
		}
  }

  void ShaderManager::useShader(const std::string &_name)
  {
    if(m_shaders.find(_name) == m_shaders.end())
    {
      std::cout << "No shader named " << _name << " found\n";
      return;
    }
		else if(m_program != m_shaders[_name])
    {
			m_program = m_shaders[_name];
    }
  }
}
