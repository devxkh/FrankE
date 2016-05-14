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

#ifndef __TECNOFREAK__ABSTRACT_ANIMATION__H__
#define __TECNOFREAK__ABSTRACT_ANIMATION__H__

//#include "HandleAnimation.h"

#include "AnimationTriggerSystem.h"
#include <XERenderer/Animation.h>

#include <list>
#include <vector>

namespace XE
{

	class GraphicsManager;
	class Animation;

	typedef std::vector< float > BoneWeightList;

class HandleAnimation :  public Animation
{
public:
	HandleAnimation(XE::GraphicsManager& gMgr, const uint32_t id);
	virtual ~HandleAnimation();

	void update(const float elapsedSeconds, const bool updateRenderer = false);

	void setAnimationPtr(Ogre::SkeletonAnimation* animation, std::vector< float* >* boneWeightPtrs, std::vector< float >* boneWeightList);

	int getActiveReferencingNodesCount() const;
	void resetActiveReferencingNodesCount();
	void increaseActiveReferencingNodeCount();

	float getAccumulatedWeight() const;
	void resetAccumulatedWeight();
	void increaseAccumulatedWeight( const float weightIncrease );

	const BoneWeightList* calculateAccumulatedMask();
	void resetAccumulatedMask();
	void increaseAccumulatedMask( const BoneWeightList* mask, const float animationWeight );

	float getAccumulatedSpeed() const;
	void resetAccumulatedSpeed();
	void increaseAccumulatedSpeed( const float speedIncrease );

	float calculateRealWeight() const;
	float calculateRealSpeed() const;

	void updateTriggers( const float currentRelativeTime, const float nextRelativeTime );
	
	void clearTriggers();
	void addTrigger( Trigger* trigger );
	void addTriggerSubscriber( ITriggerSubscriber* subscriber );
	void addTriggerSubscriber( const uint16_t triggerId, ITriggerSubscriber* subscriber );
	void removeTriggerSubscriber( ITriggerSubscriber* subscriber );
	void removeTriggerSubscriber( const uint16_t triggerId);
	void removeTriggerSubscriber( const uint16_t triggerId, ITriggerSubscriber* subscriber );
	void clearTriggerSubscribers();


	virtual void setSynched( const bool );
	virtual bool getSynched() const;

	virtual void addSynchedChild( HandleAnimation* synchedAnimation );
	virtual void clearSynchedChildren();
	virtual unsigned int getSynchedChildrenCount() const;
	virtual HandleAnimation* getSynchedChild( const unsigned int synchedChildrenId );

	void setLastUpdateId( const unsigned int lastUpdateId );
	unsigned int getLastUpdateId() const;

protected:
	void preUpdateSynchChildren();
	void postUpdateSynchChildren();

	void preUpdateTriggers();
	void postUpdateTriggers( const float animationUpdateSeconds );

private:

	int m_activeReferencingNodesCount;
	float m_accumulatedWeight;
	float m_accumulatedSpeed;

	struct AccumulatedMaskInfo
	{
		float weight;
		const BoneWeightList* mask;
	};
	BoneWeightList m_accumulatedMask;
	size_t m_accumulatedMaskSafeSize;
	std::vector< AccumulatedMaskInfo > m_accumulatedMaskInfo;

	AnimationTriggerSystem* m_triggerSystem;

	bool m_synched;
	std::vector< HandleAnimation* > m_synchedChildren;

	float m_preUpdateTriggersRelativeTime;

	unsigned int m_lastUpdateId;
};

typedef std::list< HandleAnimation* > HandleAnimationList;
typedef std::vector< HandleAnimation* > HandleAnimationVector;

}

#endif
