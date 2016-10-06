#include <fstream>
#include <iostream>
#include <cstdlib>

#include "ShaderManager.hpp"

namespace hsitho
{
  std::shared_ptr<ShaderManager> ShaderManager::m_instance = 0;

  void ShaderManager::createShader(const std::string &_name, const std::string &_vs, const std::string &_fs)
  {
    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::ifstream file;

    file.open("shaders/" + _vs, std::ios_base::in);
    if(file.is_open())
    {
      std::string src = std::string((std::istreambuf_iterator<char>(file)),
                                    (std::istreambuf_iterator<char>()));
      const GLchar *csrc = src.c_str();

      glShaderSource(vertexShader, 1, &csrc, nullptr);
      glCompileShader(vertexShader);
      verifyShader(vertexShader, "Vertex shader");
    }
    file.close();
    file.open("shaders/" + _fs, std::ios_base::in);
    if(file.is_open())
    {
      std::string src = std::string((std::istreambuf_iterator<char>(file)),
                                    (std::istreambuf_iterator<char>()));
      const GLchar *csrc = src.c_str();

      glShaderSource(fragmentShader, 1, &csrc, nullptr);
      glCompileShader(fragmentShader);
      verifyShader(fragmentShader, "Fragment shader");
    }

    file.close();

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    m_shaders[_name] = program;
  }

  void ShaderManager::useShader(const std::string &_name)
  {
    if(m_shaders.find(_name) == m_shaders.end())
    {
      std::cout << "No shader named " << _name << " found\n";
      return;
    }
    else if(m_programId != m_shaders[_name])
    {
      m_programId = m_shaders[_name];
      glUseProgram(m_shaders[_name]);
    }
  }

  void ShaderManager::setUniform1f(const std::string &_name, const GLfloat _val)
  {
    GLint loc = glGetUniformLocation(m_programId, _name.c_str());
    glUniform1f(loc, _val);
  }

  void ShaderManager::setUniform2f(const std::string &_name, const GLfloat *_val)
  {
    GLint loc = glGetUniformLocation(m_programId, _name.c_str());
    glUniform2f(loc, _val[0], _val[1]);
  }

  void ShaderManager::setUniform3fv(const std::string &_name, const GLfloat *_val)
  {
    GLint loc = glGetUniformLocation(m_programId, _name.c_str());
    glUniform3fv(loc, 1, _val);
  }

  void ShaderManager::setUniform4fv(const std::string &_name, const GLfloat *_val)
  {
    GLint loc = glGetUniformLocation(m_programId, _name.c_str());
    glUniform4fv(loc, 1, _val);
  }

  void ShaderManager::setUniform4f(const std::string &_name, const GLfloat *_val)
  {
    GLint loc = glGetUniformLocation(m_programId, _name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, _val);
  }

  void ShaderManager::verifyShader(const GLuint &_shader, const std::string &_name)
  {
    GLint status;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
    if(status == GL_TRUE)
    {
      std::cout << "Compiled " << _name << " successfully!\n";
    }
    else
    {
      char buffer[512];
      std::cout << _name << " compile failed\n";

      glGetShaderInfoLog(_shader, 512, nullptr, buffer);
      std::cout << "Compile log:\n" << buffer << "\n";

      exit(EXIT_FAILURE);
    }
  }
}
