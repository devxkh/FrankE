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

#include <XEDAL/Objects/FBEngineTypes_generated.h>
#include <XEngine/Animation/Nodes/MixNode.h>
#include <XEngine/Animation/Port.h>
#include <sstream>
#include <cassert>

using namespace XE;

MixNode::MixNode()
: Node()
{
}

MixNode::~MixNode()
{
}

void MixNode::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	float portWeight = getWeight();
	for ( unsigned int i = 0; i < m_animationPortList.size(); i++ )
	{
		Port* currentPort = m_animationPortList[ i ];
		currentPort->evaluateAnimations( deltaTime, portWeight, mask, reachedAnimationNodes );
	}
}

void MixNode::createAnimationPorts( const int animationPortCount )
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
		/*std::stringstream portName;
		portName << "in" << i;*/
		m_animationPortList[i] = createPort( i + 100);// portName.str() );
	}
}


void MixNode::init( const void* nodeData)
{

	auto mixNode = (const XFBType::MixNode*)nodeData;

	int nodeSize = mixNode->size();

	createAnimationPorts( nodeSize );
}