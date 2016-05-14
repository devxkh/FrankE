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

#include <XEngine/Animation/Nodes/BlendNode.h>
#include <XEngine/Animation/Helper/Clamp.h>
#include <XEngine/Animation/Port.h>

using namespace XE;

BlendNode::BlendNode()
: Node()
, m_animationAPort( NULL )
, m_animationBPort( NULL )
, m_animationAWeightPort( NULL )
{
	m_animationAPort = createPort(6);// "in0" );
	m_animationBPort = createPort(7);//"in1" );
	m_animationAWeightPort = createPort(8);//"weight" );
}

BlendNode::~BlendNode()
{
}

void BlendNode::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	float animationAWeight = getAnimationAWeightPort()->evaluateValue(deltaTime);
	animationAWeight = helper::clamp< float >( animationAWeight, 0, 1 );

	float animationBWeight = 1 - animationAWeight;

	getAnimationAPort()->evaluateAnimations(deltaTime, animationAWeight * getWeight(), mask, reachedAnimationNodes );
	getAnimationBPort()->evaluateAnimations( deltaTime, animationBWeight * getWeight(), mask, reachedAnimationNodes );
}

Port* BlendNode::getAnimationAPort()
{
	return m_animationAPort;
}

const Port* BlendNode::getAnimationAPort() const
{
	return m_animationAPort;
}

Port* BlendNode::getAnimationBPort()
{
	return m_animationBPort;
}

const Port* BlendNode::getAnimationBPort() const
{
	return m_animationBPort;
}


Port* BlendNode::getAnimationAWeightPort()
{
	return m_animationAWeightPort;
}

const Port* BlendNode::getAnimationAWeightPort() const
{
	return m_animationAWeightPort;
}