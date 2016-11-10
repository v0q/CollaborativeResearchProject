#include <iostream>
#include <string>
#include <memory>

#include "nodeEditor/Node.hpp"
#include "nodeEditor/NodeDataModel.hpp"
#include "SceneWindow.hpp"


void printBranch(Branch _b, int _level, int _bn)
{
	if(_b.m_sc != "")
	{
		std::cout << "L" << _level << " - B" << _bn << ":\n";
		std::cout << _b.m_sc << "\n";
	}
	int i = 0;
	for(auto &e : _b.m_branches)
	{
		printBranch(e, _level + 1, i);
		++i;
	}
}
namespace hsitho
{
  SceneWindow::SceneWindow(QWidget *_parent) :
    GLWindow(_parent),
		m_shaderMan(ShaderManager::instance()),
		m_outputNode(nullptr)
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
			Branch branches;
			std::string shadercode;
			Vec4f translation;
			for(auto connection : m_outputNode->nodeState().connection(PortType::In, 0))
			{
				if(connection.get() && connection->getNode(PortType::Out).lock())
				{
					shadercode += recurseNodeTree(connection->getNode(PortType::Out).lock(), translation);
//					branches.m_branches.push_back(recurseNodeTree(connection->getNode(PortType::Out).lock()));
				}
			}
			std::cout << shadercode << "\n";

			if(shadercode != "")
			{
				std::string fragmentShader = "#version 410 core\n"
							"uniform float u_GlobalTime;"
							"uniform vec2 u_Resolution;"
							"in vec2 o_FragCoord;"
							"out vec4 o_FragColor;"

							"float cube(vec3 _position, float _w)"
							"{"
							"  vec3 pos = abs(_position);"
							"  float dx = pos.x - _w;"
							"  float dy = pos.y - _w;"
							"  float dz = pos.z - _w;"
							"  float m = max(dx, max(dy, dz));"
							"  return m;"
							"}"

							"float p_union(float a, float b)"
							"{"
							"  return min(a, b);"
							"}"

							"float map(vec3 _position)"
							"{"
							"  float pos = 1.f;";

				//    char userInput[35];

							fragmentShader += "pos = p_union(pos, ";
							fragmentShader += shadercode;
							fragmentShader += ");";
				//    char fragmentShader[32768];
				//    strcat(fragmentShader, fragmentStart);
				//    strcat(fragmentShader, userInput);
				//    strcat(fragmentShader, fragmentEnd);

						fragmentShader += " return pos;"
															"}"

															"mat2x3 createRay(vec3 _origin, vec3 _lookAt, vec3 _upV, vec2 _uv, float _fov, float _aspect)"
															"{"
															"  mat2x3 ray;"
															"  vec3 direction, rayUpV, rightV;"
															"  vec2 uv;"
															"  float fieldOfViewRad;"

															"  ray[0] = _origin;"
															"  direction = normalize(_lookAt - _origin);"
															"  rayUpV = normalize( _upV - direction * dot(direction, _upV));"
															"  rightV = cross(direction, rayUpV);"
															"  uv = _uv * 2 - vec2(1.);"
															"  fieldOfViewRad = _fov * 3.1415 / 180;"

															"  ray[1] = direction + tan(fieldOfViewRad / 2.f) * rightV * uv.x + tan(fieldOfViewRad / 2.f) / _aspect * rayUpV * uv.y;"
															"  ray[1] = normalize(ray[1]);"

															"  return ray;"
															"}"

															"vec3 render(mat2x3 _ray)"
															"{"
															"  float distance = 1.f;"
															"  float traceprecision = 0.01f;"
															"  float position;"
															"  int  i;"
															"  for(i = 0; i < 60; ++i)"
															"  {"
															"    position = map(_ray[0] + distance * _ray[1]);"
															"    if(position <= traceprecision) {"
															"      break;"
															"    }"
															"    distance += position;"
															"  }"

															"  if(position <= traceprecision)"
															"  {"
															"    vec3 diffuse = vec3(0.8f, 0.6f, 0.f);"
															"    return vec3(i/60.f, 1 - i/60.f, 0.f);"
															"  }"
															"  return vec3(1.f);"
															"}"

															"void main()"
															"{"
															"  vec3 cameraPosition = vec3(5.f, 2.5f, 5.f);"
															"  vec3 lookAt = vec3(0.f);"
															"  vec3 upVector = vec3(0.f, 1.f, 0.f);"
															"  float aspectRatio = u_Resolution.x / u_Resolution.y;"

															"  mat2x3 ray = createRay(cameraPosition, lookAt, upVector, o_FragCoord, 90.f, aspectRatio);"
															"  vec3 color = render(ray);"
															"  o_FragColor = vec4(color, 1.f);"
															"}";

						m_shaderMan->updateShader(fragmentShader.c_str());
			}
		}
  }

	std::string SceneWindow::recurseNodeTree(std::shared_ptr<Node> _node, Vec4f _t)
	{
		std::string shadercode;
		if(_node->nodeDataModel()->getNodeType() == DFNodeType::TRANSFORM)
		{
			_t = _t + _node->nodeDataModel()->addTranslation();
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

		std::vector<std::shared_ptr<Connection>> inConns = _node->nodeState().connection(PortType::In);
		unsigned int i = 0;
		for(auto connection : inConns)
		{
			if(connection.get() && connection->getNode(PortType::Out).lock()) {
				++i;
				shadercode += recurseNodeTree(connection->getNode(PortType::Out).lock(), _t);
				if(_node->nodeDataModel()->getNodeType() == DFNodeType::MIX) {
					if(i < inConns.size())
						shadercode += ",";
					else
						shadercode += ")";
				}
			}
		}
		return shadercode;
	}

//	Branch SceneWindow::recurseNodeTree(std::shared_ptr<Node> _node)
//	{
//		Branch currentBranch;
//		currentBranch.m_sc = _node->nodeDataModel()->getShaderCode();
//		for(auto connection : _node->nodeState().connection(PortType::In))
//		{
//			if(connection.get() && connection->getNode(PortType::Out).lock())
//			{
//				currentBranch.m_branches.push_back(recurseNodeTree(connection->getNode(PortType::Out).lock()));
//			}
//		}
//		return currentBranch;
//	}
}
