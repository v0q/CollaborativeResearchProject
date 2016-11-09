#include <algorithm>
#include "NodeState.hpp"

#include "NodeDataModel.hpp"

NodeState::
NodeState(std::unique_ptr<NodeDataModel> const &model)
  : _inConnections(model->nPorts(PortType::In))
  , _outConnections(model->nPorts(PortType::Out))
  , _reaction(NOT_REACTING)
  , _reactingPortType(PortType::None)
  , _resizing(false)
{
	for(unsigned int i = 0; i < _inConnections.size(); ++i)
		_inConnections[i].resize(1);
}

std::vector<std::vector<std::weak_ptr<Connection>>> const&
NodeState::
getEntries(PortType portType) const
{
	Q_ASSERT(portType != PortType::None);

	if (portType == PortType::Out)
		return _outConnections;
	else
		return _inConnections;
}


std::vector<std::vector<std::weak_ptr<Connection>>> &
NodeState::
getEntries(PortType portType)
{
	Q_ASSERT(portType != PortType::None);

	if (portType == PortType::Out)
		return _outConnections;
	else
		return _inConnections;
}

std::vector<std::shared_ptr<Connection>>
NodeState::
connection(PortType portType, PortIndex portIndex) const
{
	auto const &connections = getEntries(portType);
	std::vector<std::shared_ptr<Connection>> c;
	for(auto const &conn : connections[portIndex]) {
		c.push_back(conn.lock());
	}

	return c;
}

void
NodeState::
setConnection(PortType portType,
              PortIndex portIndex,
              std::shared_ptr<Connection> connection)
{
	auto &connections = getEntries(portType);

	if(portType == PortType::Out) {
		unsigned int i = 0;
		for(auto &conn : connections[portIndex])
		{
			if(!conn.lock()) {
				connections[portIndex].erase(connections[portIndex].begin() + i);
			}
			++i;
		}

		connections[portIndex].push_back(connection);
	} else {
		connections[portIndex][0] = connection;
	}
}

void
NodeState::
removeConnection(PortType portType,
								 std::shared_ptr<Connection> connection)
{
	auto &connections = getEntries(portType);

	for(auto &port : connections)
	{
		unsigned int i = 0;
		for(auto &conn : port)
		{
			if((conn.lock()).get() == connection.get()) {
				break;
			}
			++i;
		}
		if(port.begin() + i != port.end()) {
			port.erase(port.begin() + i);
		}
	}
}

NodeState::ReactToConnectionState
NodeState::
reaction() const
{
  return _reaction;
}


PortType
NodeState::
reactingPortType() const
{
  return _reactingPortType;
}


NodeDataType
NodeState::
reactingDataType() const
{
  return _reactingDataType;
}


void
NodeState::
setReaction(ReactToConnectionState reaction,
            PortType reactingPortType,
            NodeDataType reactingDataType)
{
  _reaction = reaction;

  _reactingPortType = reactingPortType;

  _reactingDataType = reactingDataType;
}


bool
NodeState::
isReacting() const
{
  return _reaction == REACTING;
}


void
NodeState::
setResizing(bool resizing)
{
  _resizing = resizing;
}


bool
NodeState::
resizing() const
{
  return _resizing;
}
