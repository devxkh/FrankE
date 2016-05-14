/*
TecnoFreak Animation System
http://sourceforge.net/projects/tecnofreakanima/

Copyright (c) 2008 Pau Novau Lebrato

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/

#include <XEngine/Animation/Node.h>
#include <XEngine/Animation/Port.h>
//#include <XEngine/Animation/SharedData.h>

#include <cassert>

using namespace XE;

const int Node::INVALID_PORT_ID( -1 );

Node::Node()
: m_weight( 0 )
{
}

Node::~Node()
{
	for ( unsigned int i = 0; i < m_ports.size(); i++ )
	{
		assert( m_ports[ i ] != NULL );

		delete m_ports[ i ];
		m_ports[ i ] = NULL;
	}
}

float Node::getWeight() const
{
	return m_weight;
}

void Node::setWeight( const float weight )
{
	m_weight = weight;
}

int Node::getNodeId() const
{
	return _nodeId;
}

void Node::setNodeId(const int id)
{
	_nodeId = id;
}

void Node::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	// Default action -> Do nothing.
	// This function should be overloaded by subclasses.
}

void Node::getAnimations( AnimationNodeList& reachedAnimationNodes )
{
	for ( unsigned int i = 0; i < m_ports.size(); i++ )
	{
		Port* port = m_ports[ i ];
		port->getAnimations( reachedAnimationNodes );
	}
}

float Node::evaluateValue(double deltaTime)
{
	// Default action -> Return a default value.
	// This function should be overloaded by subclasses.

	return 0;
}

//float Node::getElapsedSeconds() const
//{
//	return getSharedData()->getElapsedSeconds();
//}

//int Node::getPortCount() const
//{
//	return int( m_ports.size() );
//}

bool Node::hasPort( const int id) const
{
	bool portExists = isValidPortId( id );

	return portExists;
}

bool Node::isValidPortId( const int id ) const
{
	for each (auto& var in m_ports)
	{
		if (var->getId() == id)
			return true;
	}
	return false;
//	return ( 0 <= id && size_t( id ) < m_ports.size() );
}

Port* Node::getPort( const int id )
{
	assert( isValidPortId( id ) );
	// TODO: Throw exception if id isn't valid?

	for each (auto& var in m_ports)
	{
		if (var->getId() == id)
			return var;
	}
}

const Port* Node::getPort( const int id ) const
{
	assert( isValidPortId( id ) );
	// TODO: Throw exception if id isn't valid?

	for each (auto& var in m_ports)
	{
		if (var->getId() == id)
			return var;
	}
}


Port* Node::createPort( const int id)
{
	bool portWithThisNameExists = hasPort( id );
	assert( ! portWithThisNameExists );
	if ( portWithThisNameExists )
	{
		// throw exception?
		return NULL;
	}

	//int portId = int( m_ports.size() );
	Port* port = new Port( this, id);
	m_ports.push_back( port );

	// TODO: move this to a unit test?
	assert( getPort( port->getId() ) == port );

	return port;
}

void Node::init(const void* nodeData)
{

}
