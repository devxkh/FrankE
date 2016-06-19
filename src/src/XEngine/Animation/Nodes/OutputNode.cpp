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

#include <XEngine/Animation/Nodes/OutputNode.h>
#include <XEngine/Animation/Port.h>

#include <cassert>

using namespace XE;

OutputNode::OutputNode()
: Node()
, m_animationInPort( NULL )
{
	m_animationInPort = createPort(1); //"in" );
}

OutputNode::~OutputNode()
{
}

void OutputNode::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	assert( m_animationInPort != NULL );

	getAnimationInPort()->evaluateAnimations( deltaTime, 1, mask, reachedAnimationNodes );
}

Port* OutputNode::getAnimationInPort()
{
	return m_animationInPort;
}

const Port* OutputNode::getAnimationInPort() const
{
	return m_animationInPort;
}
