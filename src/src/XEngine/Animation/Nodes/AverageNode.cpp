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

#include <XEngine/Animation/Nodes/AverageNode.h>
#include <XEDAL/Objects/FBEngineTypes_generated.h>
#include <XEngine/Animation/Port.h>

#include <sstream>
#include <cassert>


using namespace XE;

AverageNode::AverageNode()
: Node()
{
}

AverageNode::~AverageNode()
{
}

void AverageNode::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	if ( m_animationPortList.size() == 0 )
	{
		return;
	}


	float portWeight = getWeight() / m_animationPortList.size();
	for ( unsigned int i = 0; i < m_animationPortList.size(); i++ )
	{
		Port* currentPort = m_animationPortList[ i ];
		currentPort->evaluateAnimations( deltaTime, portWeight, mask, reachedAnimationNodes );
	}
}

void AverageNode::createAnimationPorts( const int animationPortCount )
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
		m_animationPortList[ i ] = createPort( i + 100 );
	}
}


void AverageNode::init(const void* nodeData)
{
	auto averageNode = (const XFBType::AverageNode*)nodeData;

	int nodeSize = averageNode->size();
	
	createAnimationPorts( nodeSize );
}