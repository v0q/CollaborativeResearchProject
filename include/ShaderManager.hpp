#pragma once

#include <memory>
#include <unordered_map>
#include <QOpenGLShaderProgram>

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

		~ShaderManager();
    void createShader(const std::string &_name, const QString &_vs, const QString &_fs);
		void useShader(const std::string &_name);
		QOpenGLShaderProgram* getProgram() const { return m_program; }
  private:
    static std::shared_ptr<hsitho::ShaderManager> m_instance;
		std::unordered_map<std::string, QOpenGLShaderProgram*> m_shaders;
		QOpenGLShaderProgram *m_program;

    ShaderManager() {}
    ShaderManager(const ShaderManager &_rhs) = delete;
		ShaderManager& operator= (const ShaderManager &_rhs) = delete;
  };
}
