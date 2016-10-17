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
