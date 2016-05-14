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

#include <XEngine/Animation/Nodes/TransitionSelectNode.h>
#include <XEngine/Animation/Nodes/AnimationNode.h>
#include <XEngine/Animation/Helper/Clamp.h>
#include <XEngine/Animation/HandleAnimation.h>
#include <XEDAL/Objects/FBEngineTypes_generated.h>
#include <XEngine/Animation/Port.h>

#include <cassert>
#include <sstream>

using namespace XE;

TransitionSelectNode::TransitionSelectNode()
: Node()
, m_selectedAnimationIdPort( NULL )
, m_timeInPort( NULL )
, m_timeOutPort( NULL )
, m_selectedAnimationId( -1 )
{
	m_selectedAnimationIdPort = createPort(3);// "select" );
	m_timeInPort = createPort(4);//"time in" );
	m_timeOutPort = createPort(5);//"time out" );
}

TransitionSelectNode::~TransitionSelectNode()
{
}

int TransitionSelectNode::getSelectedAnimationId() const
{
	return m_selectedAnimationId;
}

void TransitionSelectNode::setSelectedAnimationId(double deltaTime, const int selectedAnimationId, const float minTransitionSeconds )
{
	assert( 0 <= selectedAnimationId );
	assert( selectedAnimationId < getAnimationPortCount() );

	if ( selectedAnimationId == getSelectedAnimationId() )
	{
		return;
	}

	float timeIn = std::max< float >( getTimeInPort()->evaluateValue(deltaTime), minTransitionSeconds );
	float timeOut = std::max< float >( getTimeOutPort()->evaluateValue(deltaTime), minTransitionSeconds );

	// Mark all current active animations to transition out.
	for ( int i = 0; i < getAnimationPortCount(); i++ )
	{
		TransitionInfo& info = m_transtionInfoList[ i ];

		info.transitionIn = false;
		info.transitionOut = false;
		info.remainingSeconds = 0;

		bool animationIsActive = ( 0.0001f < info.weight );
		if ( animationIsActive )
		{
			info.transitionOut = true;
			info.remainingSeconds = timeOut;
		}
	}

	// Mark new selected animation to transition in.
	m_transtionInfoList[ selectedAnimationId ].transitionIn = true;
	m_transtionInfoList[ selectedAnimationId ].remainingSeconds = timeIn;

	m_selectedAnimationId = selectedAnimationId;
}

void TransitionSelectNode::updateAnimations( const float elapsedSeconds, AnimationNodeList& reachedAnimationNodes, const BoneWeightList* mask, bool selectedAnimationIdChanged )
{
	for ( int i = 0; i < getAnimationPortCount(); i++ )
	{
		TransitionInfo& info = m_transtionInfoList[ i ];

		bool animationInTransition = ( info.transitionIn || info.transitionOut );
		if ( animationInTransition )
		{
			
			float desiredWeight = ( info.transitionIn ) ? 1.f : 0.f;

			if ( info.remainingSeconds - elapsedSeconds <= 0 )
			{
				// The transition has finished.
				info.remainingSeconds = 0;
				info.weight = desiredWeight;
				info.transitionIn = false;
				info.transitionOut = false;
			}
			else
			{
				
				float remainingWeight = desiredWeight - info.weight;
				float weightIncreasePerSecond = remainingWeight / info.remainingSeconds;

				info.weight += weightIncreasePerSecond * elapsedSeconds;
				info.remainingSeconds -= elapsedSeconds;
			}

			float weight = info.weight * getWeight();
			if ( selectedAnimationIdChanged && i == getSelectedAnimationId() )
			{
				// The animations entering the transition must be reset so they start at
				// time position zero.

				AnimationNodeList animationsToReset;
				getAnimationPort( i )->evaluateAnimations(elapsedSeconds, weight, mask, animationsToReset );
				
				for ( AnimationNodeList::iterator it = animationsToReset.begin(); it != animationsToReset.end(); it++ )
				{
					AnimationNode* animationNode = (*it);

					animationNode->getAnimation()->reset();

					reachedAnimationNodes.push_back( animationNode );
				}
			}
			else
			{
				getAnimationPort( i )->evaluateAnimations(elapsedSeconds, weight, mask, reachedAnimationNodes );
			}
		}
		else
		{
			// Animation that has finished a transition:
			// it will be either at full weight or at zero weight.

			bool animationHasWeight = ( 0.1f < info.weight ); // only checking if not zero here.
			if ( animationHasWeight )
			{
				float weight = getWeight() * info.weight;
				getAnimationPort( i )->evaluateAnimations(elapsedSeconds, weight, mask, reachedAnimationNodes );
			}
		}
	}
}

void TransitionSelectNode::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	//const float elapsedSeconds = deltaTime;

	int selectedAnimationId = int( getSelectedAnimationIdPort()->evaluateValue(deltaTime) );
	selectedAnimationId = helper::clamp( selectedAnimationId, 0, getAnimationPortCount() - 1 );

	bool selectedAnimationIdChanged = ( selectedAnimationId != getSelectedAnimationId() );
	if ( selectedAnimationIdChanged )
	{
		float minTransitionSeconds = deltaTime * 0.1f;
		setSelectedAnimationId(deltaTime, selectedAnimationId, minTransitionSeconds );
	}

	updateAnimations(deltaTime, reachedAnimationNodes, mask, selectedAnimationIdChanged );
}

Port* TransitionSelectNode::getSelectedAnimationIdPort()
{
	return m_selectedAnimationIdPort;
}

const Port* TransitionSelectNode::getSelectedAnimationIdPort() const
{
	return m_selectedAnimationIdPort;
}

Port* TransitionSelectNode::getTimeInPort()
{
	return m_timeInPort;
}

const Port* TransitionSelectNode::getTimeInPort() const
{
	return m_timeInPort;
}

Port* TransitionSelectNode::getTimeOutPort()
{
	return m_timeOutPort;
}

const Port* TransitionSelectNode::getTimeOutPort() const
{
	return m_timeOutPort;
}

Port* TransitionSelectNode::getAnimationPort( const int animationPortId )
{
	assert( 0 <= animationPortId );
	assert( animationPortId < getAnimationPortCount() );

	return m_animationPortList[ animationPortId ];
}

const Port* TransitionSelectNode::getAnimationPort( const int animationPortId ) const
{
	assert( 0 <= animationPortId );
	assert( animationPortId < getAnimationPortCount() );

	return m_animationPortList[ animationPortId ];
}

int TransitionSelectNode::getAnimationPortCount() const
{
	return int( m_animationPortList.size() );
}

void TransitionSelectNode::createAnimationPorts( const int animationPortCount )
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
	m_transtionInfoList.resize( animationPortCount );
	for ( unsigned int i = 0; i < m_animationPortList.size(); i++ )
	{
		m_animationPortList[ i ] = createPort(i + 100); //port 3-5 already used in this node

		m_transtionInfoList[ i ].transitionIn = false;
		m_transtionInfoList[ i ].transitionOut = false;
		m_transtionInfoList[ i ].weight = 0;
		m_transtionInfoList[ i ].remainingSeconds = 0;
	}

	m_transtionInfoList[ 0 ].weight = 1;
}

void TransitionSelectNode::init(const void* nodeData)
{
	auto transSelectNode = (const XFBType::TransitionSelectNode*)nodeData;

	int nodeSize = transSelectNode->size();

	createAnimationPorts( nodeSize );
}