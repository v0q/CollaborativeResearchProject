#pragma once

#include <memory>
#include <unordered_map>
#include <OpenGL/gl3.h>

namespace hsitho
{
  class ShaderManager
  {
  public:
    static std::shared_ptr<ShaderManager> instance()
    {
      if(m_instance == nullptr)
        m_instance.reset(new ShaderManager());

      return m_instance;
    }

    ~ShaderManager() {}
    void createShader(const std::string &_name, const std::string &_vs, const std::string &_fs);
    void useShader(const std::string &_name);
    void setUniform1f(const std::string &_name, const GLfloat _val);
    void setUniform2f(const std::string &_name, const GLfloat *_val);
    void setUniform3fv(const std::string &_name, const GLfloat *_val);
    void setUniform4fv(const std::string &_name, const GLfloat *_val);
    void setUniform4f(const std::string &_name, const GLfloat *_val);
    GLint getProgram() const { return m_programId; }
  private:
    static std::shared_ptr<hsitho::ShaderManager> m_instance;
    std::unordered_map<std::string, GLuint> m_shaders;
    GLuint m_programId;

    ShaderManager() {}
    ShaderManager(const ShaderManager &_rhs) = delete;
    ShaderManager& operator= (const ShaderManager &_rhs) = delete;

    void verifyShader(const GLuint &_shader, const std::string &_name);
  };
}
