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

#include <XEngine/Animation/Nodes/RandomSelectNode.h>
#include <XEngine/Animation/Port.h>
#include <XEDAL/Objects/FBEngineTypes_generated.h>

#include <cassert>
#include <cstdlib>
#include <sstream>

using namespace XE;

RandomSelectNode::RandomSelectNode()
: m_selectedAnimationId( -1 )
, m_lastUpdateId( 0 )
{

}

RandomSelectNode::~RandomSelectNode()
{

}

int RandomSelectNode::getSelectedAnimationId() const
{
	return m_selectedAnimationId;
}

void RandomSelectNode::resetSelectedAnimationId()
{
	assert( getAnimationPortCount() != 0 );
	if ( getAnimationPortCount() == 0 )
	{
		return;
	}

	m_selectedAnimationId = rand() % getAnimationPortCount();
}

void RandomSelectNode::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	unsigned int currentUpdateId = 0;//todo !!//getSharedData()->getUpdateId();

	if ( currentUpdateId != getLastUpdateId() + 1 )
	{
		resetSelectedAnimationId();
	}

	setLastUpdateId( currentUpdateId );

	int selectedAnimationId = getSelectedAnimationId();

	Port* selectedPort = getAnimationPort( selectedAnimationId );

	selectedPort->evaluateAnimations( deltaTime, getWeight(), mask, reachedAnimationNodes );
}


Port* RandomSelectNode::getAnimationPort( const int animationPortId )
{
	assert( 0 <= animationPortId );
	assert( animationPortId < getAnimationPortCount() );

	return m_animationPortList[ animationPortId ];
}

const Port* RandomSelectNode::getAnimationPort( const int animationPortId ) const
{
	assert( 0 <= animationPortId );
	assert( animationPortId < getAnimationPortCount() );

	return m_animationPortList[ animationPortId ];
}

int RandomSelectNode::getAnimationPortCount() const
{
	return int( m_animationPortList.size() );
}

unsigned int RandomSelectNode::getLastUpdateId() const
{
	return m_lastUpdateId;
}

void RandomSelectNode::setLastUpdateId( const unsigned int lastUpdateId )
{
	m_lastUpdateId = lastUpdateId;
}

void RandomSelectNode::createAnimationPorts( const int animationPortCount )
{
	assert( 0 < animationPortCount );
	if ( animationPortCount <= 0 )
	{
		// TODO: throw exception?
		return;
	}

	assert( m_animationPortList.size() == 0 );
	if ( m_animationPortList.size() != 0 )
	{
		// TODO: throw exception?
		return;
	}

	m_animationPortList.resize( animationPortCount );
	for ( unsigned int i = 0; i < m_animationPortList.size(); i++ )
	{
	/*	std::stringstream portName;
		portName << "animation " << i;*/
		m_animationPortList[i] = createPort(i + 100);// portName.str() );
	}

	resetSelectedAnimationId();
}


void RandomSelectNode::init( const void* nodeData)
{


	auto randomSelectNode = (const XFBType::RandomSelectNode*)nodeData;

	int nodeSize = randomSelectNode->size();

	createAnimationPorts( nodeSize );
}