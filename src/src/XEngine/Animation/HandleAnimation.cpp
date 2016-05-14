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

#include <XEngine/Animation/HandleAnimation.h>

#include <XEngine/Animation/Helper/Clamp.h>

#include <XERenderer/Animation.h>

#include <cassert>
#include <cmath>

using namespace XE;

HandleAnimation::HandleAnimation(XE::GraphicsManager& gMgr, const uint32_t id)
: Animation(gMgr, id)
 , m_activeReferencingNodesCount( 0 )
, m_accumulatedWeight( 0 )
, m_accumulatedSpeed( 0 )
, m_triggerSystem( NULL )
, m_synched( false )
, m_preUpdateTriggersRelativeTime( 0 )
, m_lastUpdateId( 0 )
, m_accumulatedMaskSafeSize( 0 )
{
}

HandleAnimation::~HandleAnimation()
{
	delete m_triggerSystem;
	m_triggerSystem = NULL;
	//if (m_t_boneWeightPtrs) // created in renderable -> renderthread
	//{
	//	delete m_t_boneWeightPtrs;
	//	m_t_boneWeightPtrs = nullptr;
	//}
	//if (m_boneWeightList) // created in renderable -> renderthread
	//{
	//	delete m_boneWeightList;
	//	m_boneWeightList = nullptr;
	//}
}

void HandleAnimation::setAnimationPtr(Ogre::SkeletonAnimation* animation, std::vector< float* >* boneWeightPtrs, std::vector< float >* boneWeightList)
{
	Animation::_t_animation = animation;
	Animation::_hasRenderAnimation = true;
	Animation::m_t_boneWeightPtrs = boneWeightPtrs;
	Animation::m_boneWeightList = boneWeightList;
}


int HandleAnimation::getActiveReferencingNodesCount() const
{
	return m_activeReferencingNodesCount;
}

void HandleAnimation::resetActiveReferencingNodesCount()
{
	m_activeReferencingNodesCount = 0;
}

void HandleAnimation::increaseActiveReferencingNodeCount()
{
	m_activeReferencingNodesCount++;
}

float HandleAnimation::getAccumulatedWeight() const
{
	return m_accumulatedWeight;
}

void HandleAnimation::resetAccumulatedWeight()
{
	m_accumulatedWeight = 0;
}

void HandleAnimation::increaseAccumulatedWeight( const float weightIncrease )
{
	m_accumulatedWeight += weightIncrease;
}

void HandleAnimation::update(const float elapsedSeconds, const bool updateRenderer)
{
	preUpdateSynchChildren();
	preUpdateTriggers();

	float animationUpdateSeconds = elapsedSeconds * Animation::getSpeed();

	//m_TimePos = m_TimePos + animationUpdateSeconds;//getAnimationState()->addTime( animationUpdateSeconds );
	Animation::setTimePosition(Animation::m_TimePos + animationUpdateSeconds); //addTime

	Animation::addTime(animationUpdateSeconds);

	postUpdateTriggers(animationUpdateSeconds);
	postUpdateSynchChildren();

	if(updateRenderer)
		Animation::updateRenderer();
}


const BoneWeightList* HandleAnimation::calculateAccumulatedMask()
{
	if ( m_accumulatedMaskInfo.size() == 0 )
	{
		return NULL;
	}

	float accumulatedWeight = getAccumulatedWeight();
	if ( accumulatedWeight <= 0 )
	{
		return NULL;
	}

	if ( m_accumulatedMaskSafeSize == 0 )
	{
		return NULL;
	}

	if ( m_accumulatedMaskInfo.size() == 1 )
	{
		const AccumulatedMaskInfo& info = m_accumulatedMaskInfo[ 0 ];
		return info.mask;
	}

	m_accumulatedMask.clear();
	m_accumulatedMask.resize( m_accumulatedMaskSafeSize, 0 );
		
	// We should only take this path when more than 1 node is actively referencing this animation and it has a mask applied...
	for ( size_t i = 0; i < m_accumulatedMask.size(); ++i )
	{
		for ( size_t j = 0; j < m_accumulatedMaskInfo.size(); ++j )
		{
			const AccumulatedMaskInfo& info = m_accumulatedMaskInfo[ j ];
			const BoneWeightList* mask = info.mask;

			float weight = 1;
			if ( mask != NULL )
			{
				weight = ( *mask )[ i ];
			}
		
			m_accumulatedMask[ i ] += ( weight * info.weight / accumulatedWeight );
		}

		m_accumulatedMask[ i ] = helper::clamp( m_accumulatedMask[ i ], 0.0f, 1.0f );
	}

	return &m_accumulatedMask;
}

void HandleAnimation::resetAccumulatedMask()
{
	m_accumulatedMaskSafeSize = 0;
	m_accumulatedMaskInfo.clear();
}

void HandleAnimation::increaseAccumulatedMask( const BoneWeightList* maskIncrement, const float animationWeight )
{
	AccumulatedMaskInfo info;
	info.mask = maskIncrement;
	info.weight = animationWeight;

	if ( info.mask != NULL )
	{
		m_accumulatedMaskSafeSize  = std::max( m_accumulatedMaskSafeSize, info.mask->size() );
	}

	m_accumulatedMaskInfo.push_back( info );
}

float HandleAnimation::getAccumulatedSpeed() const
{
	return m_accumulatedSpeed;
}

void HandleAnimation::resetAccumulatedSpeed()
{
	m_accumulatedSpeed = 0;
}

void HandleAnimation::increaseAccumulatedSpeed( const float speedIncrease )
{
	m_accumulatedSpeed += speedIncrease;
}

float HandleAnimation::calculateRealWeight() const
{
	assert( getActiveReferencingNodesCount() != 0 );
	return ( getAccumulatedWeight() / getActiveReferencingNodesCount() );
}

float HandleAnimation::calculateRealSpeed() const
{
	assert( getActiveReferencingNodesCount() != 0 );
	return ( getAccumulatedSpeed() / getActiveReferencingNodesCount() );
}

void HandleAnimation::clearTriggers()
{
	delete m_triggerSystem;
	m_triggerSystem = NULL;
}

void HandleAnimation::addTrigger( Trigger* trigger )
{
	if ( m_triggerSystem == NULL )
		m_triggerSystem = new AnimationTriggerSystem();

	m_triggerSystem->addTrigger( trigger );
}

void HandleAnimation::updateTriggers( const float currentRelativeTime, const float nextRelativeTime )
{
	if ( m_triggerSystem == NULL )
		return;

	m_triggerSystem->update( currentRelativeTime, nextRelativeTime, Animation::getWeight() );
}

void HandleAnimation::addTriggerSubscriber( ITriggerSubscriber* subscriber )
{
	if ( m_triggerSystem == NULL )
		m_triggerSystem = new AnimationTriggerSystem();

	m_triggerSystem->addSubscriber( subscriber );
}

void HandleAnimation::addTriggerSubscriber( const uint16_t triggerId, ITriggerSubscriber* subscriber )
{
	if ( m_triggerSystem == NULL )
		m_triggerSystem = new AnimationTriggerSystem();

	m_triggerSystem->addSubscriber(triggerId, subscriber );

}

void HandleAnimation::removeTriggerSubscriber( ITriggerSubscriber* subscriber )
{
	if ( m_triggerSystem == NULL )
		return;

	m_triggerSystem->removeSubscriber( subscriber );
}

void HandleAnimation::removeTriggerSubscriber( const uint16_t triggerId)
{
	if ( m_triggerSystem == NULL )
		return;

	m_triggerSystem->removeSubscriber(triggerId);
}

void HandleAnimation::removeTriggerSubscriber( const uint16_t triggerId, ITriggerSubscriber* subscriber )
{
	if ( m_triggerSystem == NULL )
		return;

	m_triggerSystem->removeSubscriber(triggerId, subscriber );
}

void HandleAnimation::clearTriggerSubscribers()
{
	if ( m_triggerSystem == NULL )
		return;

	m_triggerSystem->removeAllSubscribers();
}

void HandleAnimation::setSynched( const bool synched )
{
	m_synched = synched;
}

bool HandleAnimation::getSynched() const
{
	return m_synched;
}

void HandleAnimation::addSynchedChild( HandleAnimation* synchedAnimation )
{
	assert( synchedAnimation != NULL );
	if ( synchedAnimation == NULL )
	{
		return;
	}

	synchedAnimation->setSynched( true );

	m_synchedChildren.push_back( synchedAnimation );
}

void HandleAnimation::clearSynchedChildren()
{
	for ( unsigned int i = 0; i < m_synchedChildren.size(); i++ )
	{
		HandleAnimation* synchedChild = getSynchedChild( i );
		synchedChild->setSynched( false );
	}

	m_synchedChildren.clear();
}

unsigned int HandleAnimation::getSynchedChildrenCount() const
{
	return ( unsigned int )( m_synchedChildren.size() );
}

HandleAnimation* HandleAnimation::getSynchedChild( const unsigned int synchedChildrenId )
{
	if ( m_synchedChildren.size() <= synchedChildrenId )
	{
		return NULL;
	}

	return m_synchedChildren[ synchedChildrenId ];
}

void HandleAnimation::setLastUpdateId( const unsigned int lastUpdateId )
{
	m_lastUpdateId = lastUpdateId;
}

unsigned int HandleAnimation::getLastUpdateId() const
{
	return m_lastUpdateId;
}

void HandleAnimation::preUpdateSynchChildren()
{
	const float relativeTime = Animation::getRelativeTimePosition();
	for ( unsigned int i = 0; i < m_synchedChildren.size(); i++ )
	{
		HandleAnimation* synchedChild = m_synchedChildren[ i ];
		synchedChild->setRelativeTimePosition( relativeTime );
	}
}

void HandleAnimation::postUpdateSynchChildren()
{
	float relativeTime = Animation::getRelativeTimePosition();
	for ( unsigned int i = 0; i < m_synchedChildren.size(); i++ )
	{
		HandleAnimation* synchedChild = m_synchedChildren[ i ];
		synchedChild->setSpeed( 1 );

		float childRelativeTime = synchedChild->getRelativeTimePosition();
		float synchDifference = relativeTime - childRelativeTime;
		float childUpdateTime = synchDifference * synchedChild->getLength();

		synchedChild->update( childUpdateTime );
	}

	clearSynchedChildren();
}

void HandleAnimation::preUpdateTriggers()
{
	m_preUpdateTriggersRelativeTime = Animation::getRelativeTimePosition();
}

void HandleAnimation::postUpdateTriggers( const float animationUpdateSeconds )
{
	float postUpdateRelativeTime = Animation::getRelativeTimePosition();

	float animationAdvancing = ( 0 <= animationUpdateSeconds );
	if ( animationAdvancing )
	{
		updateTriggers( m_preUpdateTriggersRelativeTime, postUpdateRelativeTime );
	}
	else
	{
		// FIXME: Update order within the trigger update won't be 100% correct, as they will
		// still be called in chronological order instead of reverse chronological order.
		updateTriggers( postUpdateRelativeTime, m_preUpdateTriggersRelativeTime );
	}
}