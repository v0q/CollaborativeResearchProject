#include <iostream>
#include <string>
#include <memory>

#include "nodeEditor/Node.hpp"
#include "nodeEditor/NodeDataModel.hpp"
#include "SceneWindow.hpp"

namespace hsitho
{
  SceneWindow::SceneWindow(QWidget *_parent, std::list<Node> m_priorityStatus) :
    GLWindow(_parent),
		m_shaderMan(ShaderManager::instance()),
    m_outputNode(nullptr),
    m_priorityStatus(_priorityStatus)
  {
	}

	SceneWindow::~SceneWindow()
	{
		delete m_vao;
	}

  void SceneWindow::initializeGL()
  {
    GLWindow::initializeGL();

    m_shaderMan->createShader("ScreenQuad", "screenQuad.vert", "distancefieldprimitives.frag");
    m_shaderMan->useShader("ScreenQuad");

		// Generate and bind VAO and VBO buffers
    m_vao = new QOpenGLVertexArrayObject(dynamic_cast<QObject*>(this));
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

  void SceneWindow::nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes)
	{
		if(m_outputNode == nullptr)
		{
			for(auto node : _nodes)
			{
				if(node.second.get()->nodeDataModel()->getShaderCode() == "final")
				{
					m_outputNode = node.second.get();
					break;
				}
			}
		}
		if(m_outputNode != nullptr)
		{
			std::cout << "NumOut: " << m_outputNode->nodeState().connection(PortType::In, 0).size() << "\n";
			for(auto connection : m_outputNode->nodeState().connection(PortType::In, 0))
			{
				if(connection.get() && connection->getNode(PortType::Out).lock())
				{
					std::cout << recurseNodeTree(connection->getNode(PortType::Out).lock());
//				std::cout << "\n";
//				std::cout << qPrintable(connections.get()->getNode(PortType::Out).lock()->nodeDataModel()->getShaderCode()) << "\n";
				}
			}


//		m_shaderMan->updateShader(fragmentShader.c_str());
		}
  }

  int SceneWindow::getPriorityQueueStatus()
  {
    return m_priorityStatus;
  }

  void SceneWindow::setPriorityHigh()
  {
    m_priorityStatus.push_front(m_queuePlace);
  }

  void SceneWindow::setPriorityLow()
  {
    m_priorityStatus.push_back(m_queuePlace);
  }

	std::string SceneWindow::recurseNodeTree(std::shared_ptr<Node> _node)
	{
		std::string shadercode;
		shadercode += qPrintable(QString(_node->nodeDataModel()->getShaderCode() + " "));
		for(auto connection : _node->nodeState().connection(PortType::In))
		{
			if(connection.get() && connection->getNode(PortType::Out).lock())
				shadercode += recurseNodeTree(connection->getNode(PortType::Out).lock());
		}
		return shadercode;
	}
}
