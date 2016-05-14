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

#include <XEngine/Animation/Nodes/LookAtNode.h>
#include <XEngine/Animation/Helper/Clamp.h>
#include <XEngine/Animation/Port.h>

using namespace XE;

LookAtNode::LookAtNode()
: Node()
, m_horizontalDirectionAmountPort( NULL )
, m_verticalDirectionAmountPort( NULL )
{
	m_horizontalDirectionAmountPort = createPort(11); // "horizontal_amount" );
	m_verticalDirectionAmountPort = createPort(12); // "vertical_amount" );

	m_animationPort[ LOOK_AT_LEFT ] = createPort(13); // "left" );
	m_animationPort[ LOOK_AT_RIGHT ] = createPort(14); //"right" );
	m_animationPort[ LOOK_AT_UP ] = createPort(15); //"up" );
	m_animationPort[ LOOK_AT_DOWN ] = createPort(16); // "down" );
}

LookAtNode::~LookAtNode()
{

}

void LookAtNode::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	evaluateDirectionalAnimations( getHorizontalDirectionAmountPort(), getAnimationPort( LOOK_AT_LEFT ), getAnimationPort( LOOK_AT_RIGHT ), reachedAnimationNodes, deltaTime, mask );
	evaluateDirectionalAnimations( getVerticalDirectionAmountPort(), getAnimationPort( LOOK_AT_UP ), getAnimationPort( LOOK_AT_DOWN ), reachedAnimationNodes, deltaTime, mask );
}

void LookAtNode::evaluateDirectionalAnimations( Port* amountPort, Port* firstAnimation, Port* secondAnimation, AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	float directionAmount = amountPort->evaluateValue(deltaTime);
	directionAmount = helper::clamp< float >( directionAmount, 0, 1 );
	if ( directionAmount < 0.5f )
	{
		float weight = ( 0.5f - directionAmount ) * 2 * getWeight();
		firstAnimation->evaluateAnimations( deltaTime, weight, mask, reachedAnimationNodes );
	}
	else if ( 0.5f < directionAmount )
	{
		float weight = ( directionAmount - 0.5f ) * 2 * getWeight();
		secondAnimation->evaluateAnimations( deltaTime, weight, mask, reachedAnimationNodes );
	}
}

Port* LookAtNode::getAnimationPort( const LookAtAnimationDirection animationDirection )
{
	return m_animationPort[ animationDirection ];
}

const Port* LookAtNode::getAnimationPort( const LookAtAnimationDirection animationDirection) const
{
	return m_animationPort[ animationDirection ];
}

Port* LookAtNode::getHorizontalDirectionAmountPort()
{
	return m_horizontalDirectionAmountPort;
}

const Port* LookAtNode::getHorizontalDirectionAmountPort() const
{
	return m_horizontalDirectionAmountPort;
}

Port* LookAtNode::getVerticalDirectionAmountPort()
{
	return m_verticalDirectionAmountPort;
}

const Port* LookAtNode::getVerticalDirectionAmountPort() const
{
	return m_verticalDirectionAmountPort;
}
