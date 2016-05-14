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

#include <XEngine/Animation/Port.h>
#include <XEngine/Animation/INode.h>


using namespace XE;

Port::Port( INode* parentNode, int id )
: m_parentNode( parentNode )
, m_id( id )
, m_defaultValue( 0 )
, m_connectedNode( NULL )
{
}

Port::~Port()
{
}

INode* Port::getConnectedNode()
{
	return m_connectedNode;
}

const INode* Port::getConnectedNode() const
{
	return m_connectedNode;
}

void Port::setConnectedNode( INode* connectedNode )
{
	m_connectedNode = connectedNode;
}
	
bool Port::isConnected() const
{
	return ( getConnectedNode() != NULL );
}

INode* Port::getParentNode()
{
	return m_parentNode;
}

const INode* Port::getParentNode() const
{
	return m_parentNode;
}

int Port::getId() const
{
	return m_id;
}

void Port::evaluateAnimations(double deltaTime, const float weight, const BoneWeightList* mask, AnimationNodeList& reachedAnimationNodes )
{
	if ( ! isConnected() )
	{
		return;
	}
	
	getConnectedNode()->setWeight( weight );
	getConnectedNode()->evaluateAnimations( reachedAnimationNodes, deltaTime, mask );
}

void Port::getAnimations( AnimationNodeList& reachedAnimationNodes )
{
	if ( ! isConnected() )
	{
		return;
	}

	getConnectedNode()->getAnimations( reachedAnimationNodes );
}

float Port::evaluateValue(double deltaTime)
{
	if ( ! isConnected() )
	{
		return getDefaultValue();
	}

	return getConnectedNode()->evaluateValue(deltaTime);
}

void Port::setDefaultValue( const float defaultValue )
{
	m_defaultValue = defaultValue;
}

float Port::getDefaultValue() const
{
	return m_defaultValue;
}