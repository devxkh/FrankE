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
#include <XEngine/Animation/Nodes/AnimationNode.h>
#include <XEDAL/Objects/FBEngineTypes_generated.h>

#include <cassert>

namespace XE {

	const int AnimationNode::INVALID_ANIMATION_ID(-1);

	AnimationNode::AnimationNode()
		: Node()
		, m_animationId(INVALID_ANIMATION_ID)
		, m_speedPort(NULL)
		, m_synchPort(NULL)
		, m_animation(NULL)
		, m_mask(NULL)
	{
		m_speedPort = createPort(0); //"speed");
		getSpeedPort()->setDefaultValue(1);

		m_synchPort = createPort(1);//"synch");
	}

	AnimationNode::~AnimationNode()
	{
	}

	void AnimationNode::evaluateAnimations(AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask)
	{
		if (!hasValidAnimation())
		{
			return;
		}

		if (getSynchPort()->isConnected())
		{
			AnimationNodeList synchChildrenAnimationNodes;
			getSynchPort()->getAnimations(synchChildrenAnimationNodes);
			for (AnimationNodeList::iterator it = synchChildrenAnimationNodes.begin(); it != synchChildrenAnimationNodes.end(); it++)
			{
				AnimationNode* animationNode = *it;
				HandleAnimation* synchAnimation = animationNode->getAnimation();
				getAnimation()->addSynchedChild(synchAnimation);
			}
		}

		setMask(mask);
		reachedAnimationNodes.push_back(this);
	}

	void AnimationNode::getAnimations(AnimationNodeList& reachedAnimationNodes)
	{
		if (!hasValidAnimation())
		{
			return;
		}

		reachedAnimationNodes.push_back(this);
	}
	
	int AnimationNode::getAnimationId() const
	{
		return m_animationId;
	}

	bool AnimationNode::hasValidAnimation() const
	{
		return (getAnimationId() != INVALID_ANIMATION_ID);
	}

	float AnimationNode::evaluateAnimationSpeed(double deltaTime)
	{
		float animationSpeed = getSpeedPort()->evaluateValue(deltaTime);
		return animationSpeed;
	}

	Port* AnimationNode::getSpeedPort()
	{
		return m_speedPort;
	}

	const Port* AnimationNode::getSpeedPort() const
	{
		return m_speedPort;
	}

	Port* AnimationNode::getSynchPort()
	{
		return m_synchPort;
	}

	const Port* AnimationNode::getSynchPort() const
	{
		return m_synchPort;
	}

	HandleAnimation* AnimationNode::getAnimation()
	{
		return m_animation;
	}

	const HandleAnimation* AnimationNode::getAnimation() const
	{
		return m_animation;
	}

	void AnimationNode::setAnimation(HandleAnimation* animation)
	{
		assert(animation != NULL);

		m_animation = animation;
	}

	const BoneWeightList* AnimationNode::getMask() const
	{
		return m_mask;
	}

	void AnimationNode::setMask(const BoneWeightList* mask)
	{
		m_mask = mask;
	}

	void AnimationNode::init(const void* nodeData)
	{
		auto animationNode = (const XFBType::AnimationNode*)nodeData;

		m_animationId = animationNode->animation()->id();
	}
}