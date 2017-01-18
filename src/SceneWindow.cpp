#include <iostream>
#include <string>
#include <memory>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "nodeEditor/Node.hpp"
#include "nodeEditor/NodeDataModel.hpp"
#include "nodes/CollapsedNodeDataModel.hpp"
#include "SceneWindow.hpp"

namespace hsitho
{
  SceneWindow::SceneWindow(QWidget *_parent) :
    GLWindow(_parent),
    m_shaderMan(ShaderManager::instance()),
		m_outputNode(nullptr),
		m_cam(glm::vec4(0.f, 0.132164f, 0.991228f, 0.f)),
		m_camU(glm::vec3(0.f, 1.f, 0.f)),
		m_camL(glm::vec3(1.f, 0.f, 0.f)),
//		m_camDist(7.566f)
		m_camDist(15.f)
  {
    std::ifstream s("shaders/shader.begin");
    std::ifstream e("shaders/shader.end");
    m_shaderStart = std::string((std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>());
    m_shaderEnd = std::string((std::istreambuf_iterator<char>(e)), std::istreambuf_iterator<char>());
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
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
    };

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.allocate(nullptr, sizeof(vertices)*sizeof(uvs));
    m_vbo.write(0, vertices, sizeof(vertices));
    m_vbo.write(sizeof(vertices), uvs, sizeof(uvs));
  }

	void SceneWindow::mousePressEvent(QMouseEvent *_event)
	{
		if(_event->button() == Qt::LeftButton)
		{
			m_origX = _event->x();
			m_origY = _event->y();
		}
	}

	void SceneWindow::mouseMoveEvent(QMouseEvent *_event)
	{
		if(_event->buttons() == Qt::LeftButton)
		{
			float dx = 0.5f * (_event->x() - m_origX);
			float dy = 0.5f * (_event->y() - m_origY);
			m_origX = _event->x();
			m_origY = _event->y();

			glm::mat4 rot = glm::rotate(glm::mat4(1.f), glm::radians(dx), m_camU);
			rot = glm::rotate(rot, glm::radians(dy), -m_camL);

			m_cam = glm::normalize(rot * m_cam);
			glm::vec3 d = glm::vec3(-m_cam.x, -m_cam.y, -m_cam.z);
			m_camU = glm::normalize(m_camU - d * glm::dot(m_camU, d));
			m_camL = glm::normalize(glm::cross(m_camU, -d));
		}
	}

	void SceneWindow::wheelEvent(QWheelEvent *_event)
	{
		int numDegrees = _event->delta() / 8;
		int numSteps = numDegrees / 15;

		if(_event->orientation() == Qt::Vertical) {
			m_camDist -= numSteps*0.25f;
		}
		_event->accept();
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
		m_shaderMan->getProgram()->setUniformValueArray("u_Camera", glm::value_ptr((m_camDist*m_cam)), 1, 3);
		m_shaderMan->getProgram()->setUniformValueArray("u_CameraUp", glm::value_ptr(m_camU), 1, 3);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_shaderMan->getProgram()->disableAttributeArray("a_Position");
    m_shaderMan->getProgram()->disableAttributeArray("a_FragCoord");
    m_shaderMan->getProgram()->release();

    m_vbo.release();
    m_vao->release();

		++m_frames;
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
      std::string shadercode;
      Mat4f translation;
			hsitho::Expressions::flushUnknowns();
      for(auto connection : m_outputNode->nodeState().connection(PortType::In, 0))
      {
        if(connection.get() && connection->getNode(PortType::Out).lock())
        {
          shadercode += recurseNodeTree(connection->getNode(PortType::Out).lock(), translation);
//					branches.m_branches.push_back(recurseNodeTree(connection->getNode(PortType::Out).lock()));
        }
      }

      if(shadercode != "")
      {
				std::string fragmentShader = m_shaderStart;

				fragmentShader += hsitho::Expressions::getUnknowns();
				fragmentShader += "pos = ";
				fragmentShader += hsitho::Expressions::replaceUnknowns(shadercode);
				fragmentShader += ";";
				std::cout << hsitho::Expressions::getUnknowns() << "\n";
				std::cout << hsitho::Expressions::replaceUnknowns(shadercode) << "\n";

        fragmentShader += m_shaderEnd;

        m_shaderMan->updateShader(fragmentShader.c_str());
      }
    }
  }

	std::string SceneWindow::recurseNodeTree(std::shared_ptr<Node> _node, Mat4f _t, PortIndex portIndex, unsigned int _cp)
	{
		unsigned int iter = 1;
		std::string shadercode;
		_t.setCpn(_cp);
		_node->nodeDataModel()->setCopyNum(_cp);

    if(_node->nodeDataModel()->getNodeType() == DFNodeType::TRANSFORM)
		{
			_t = _t * _node->nodeDataModel()->getTransform();
    }
    else if(_node->nodeDataModel()->getNodeType() == DFNodeType::PRIMITIVE)
    {
      _node->nodeDataModel()->setTransform(_t);
      shadercode += _node->nodeDataModel()->getShaderCode();
    }
    else if(_node->nodeDataModel()->getNodeType() == DFNodeType::MIX)
    {
      shadercode += _node->nodeDataModel()->getShaderCode();
		}
		else if(_node->nodeDataModel()->getNodeType() == DFNodeType::COPY)
		{
			iter = boost::lexical_cast<unsigned int>(_node->nodeDataModel()->getShaderCode());
		}

		for(unsigned int it = 0; it < iter; ++it)
		{
			if(iter > 1)
			{
				_cp = it;
				if(iter - it > 1)
				{
					shadercode += "opUnion(";
				}
			}
			std::vector<std::shared_ptr<Connection>> inConns = _node->nodeState().connection(PortType::In);
			if(_node->nodeDataModel()->getNodeType() == DFNodeType::COLLAPSED) {
				std::vector<std::shared_ptr<Connection>> inConnsTmp;
				std::shared_ptr<Node> o = dynamic_cast<CollapsedNodeDataModel *>(_node->nodeDataModel().get())->getOutputs()[portIndex];
				for(auto &c : o->nodeState().connection(PortType::In)) {
					inConnsTmp.push_back(c);
				}
				inConns.swap(inConnsTmp);
				inConnsTmp.clear();
			}

			unsigned int i = 0;
			for(auto connection : inConns)
			{
				if(connection.get() && connection->getNode(PortType::Out).lock()) {
					++i;
					shadercode += recurseNodeTree(connection->getNode(PortType::Out).lock(), _t, connection->getPortIndex(PortType::Out), _cp);
					if(_node->nodeDataModel()->getNodeType() == DFNodeType::MIX) {
						if(i < inConns.size())
							shadercode += ",";
						else
							shadercode += _node->nodeDataModel()->getExtraParams() + ")";
					}
				}
			}
			if(iter > 1 && iter - it > 1)
			{
				shadercode += ",";
			}
		}
		if(iter > 1)
		{
			for(unsigned int it = 0; it < iter - 1; ++it)
				shadercode += ")";
		}
    return shadercode;
  }
}
