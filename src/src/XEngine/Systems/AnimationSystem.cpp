#include <XEngine/Systems/AnimationSystem.hpp>
#include <XEngine/Components/AnimationComponent.hpp>
#include <XERenderer/Animation.h>
#include <XEngine/Animation/HandleAnimation.h>
#include <XEngine/Animation/Nodes/AnimationNode.h>
#include <XEngine/Animation/Nodes/ParameterNode.h>

#include <XERenderer/GraphicsManager.hpp>

#include <unordered_map>

namespace XE {

	AnimationControllerSystem::AnimationControllerSystem(XE::GraphicsManager& gMgr, XE::Scene& scene)
		: m_Scene(scene)
		, _graphicsMgr(gMgr)
	{

	}

	void AnimationControllerSystem::updateAnimation(XE::AnimationComponent& animationComponent, entityx::TimeDelta dt, bool updateRenderer) {

		m_updateId++;

		animationComponent.m_currentAnimations.clear();
		animationComponent.m_reachedAnimationNodes.clear();

		//getOutputNode()->
		animationComponent._nodes[0]->evaluateAnimations(animationComponent.m_reachedAnimationNodes, dt);

		flattenReachedAnimations(animationComponent, dt);

		//updateCurrentAnimations
		for (auto& animation : animationComponent.m_currentAnimations)
		{
			// TODO: think how to deal with repeated animations.
			// float animationWeight = animation->calculateRealWeight();
			float animationWeight = animation->getAccumulatedWeight();
			animation->setWeight(animationWeight);
		
			const BoneWeightList* mask = animation->calculateAccumulatedMask();
			animation->setMask(mask);

			float animationSpeed = animation->calculateRealSpeed();
			animation->setSpeed(animationSpeed);

			if (!animation->getSynched())
			{
				animation->update(dt, updateRenderer);
			}

			animation->resetActiveReferencingNodesCount();

			animation->resetAccumulatedWeight();
			animation->resetAccumulatedMask();
			animation->resetAccumulatedSpeed();

			animation->setLastUpdateId(m_updateId);
		}

		disableOrphanedAnimations(animationComponent);


		//mAnimationState = mAnimSystem->getParameter("AnimationState");
		//mJumpPost = mAnimSystem->getParameter("Jump Post");
		//mLookDirectionHorizontal = mAnimSystem->getParameter("LookDirectionHorizontal");

		//mLookDirectionVertical = mAnimSystem->getParameter("LookDirectionVertical");


		//Idle = param 2
		/*if(animationComponent.animationState)
			animationComponent.animationState->setValue(2);*/
	//	mAnimationState->setValue(2);
	}

	void AnimationControllerSystem::disableOrphanedAnimations(XE::AnimationComponent& animationComponent)
	{
		for each (auto& animation in animationComponent._animations)
		{
			bool updatedNow = (animation->getLastUpdateId() == m_updateId);
			animation->setEnabled(updatedNow);
		}
	}

	void AnimationControllerSystem::flattenReachedAnimations(XE::AnimationComponent& animationComponent, entityx::TimeDelta dt)
	{
		for (AnimationNodeList::iterator it = animationComponent.m_reachedAnimationNodes.begin(); it != animationComponent.m_reachedAnimationNodes.end(); it++)
		{
			AnimationNode* animationNode = *it;
			int animationId = animationNode->getAnimationId();

			assert(animationNode->getAnimation());

			animationNode->getAnimation()->increaseActiveReferencingNodeCount();

			float animationWeight = animationNode->getWeight();
			animationNode->getAnimation()->increaseAccumulatedWeight(animationWeight);

			const BoneWeightList* mask = animationNode->getMask();
			animationNode->getAnimation()->increaseAccumulatedMask(mask, animationWeight);

			float animationSpeed = animationNode->evaluateAnimationSpeed(dt);
			animationNode->getAnimation()->increaseAccumulatedSpeed(animationSpeed);

			if (animationNode->getAnimation()->getActiveReferencingNodesCount() == 1)
			{
				animationComponent.m_currentAnimations.push_back(animationNode->getAnimation());
			}
		}
	}

	void AnimationControllerSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {


		bool updateRenderer = false;
		if (_graphicsMgr.GetRenderTask(RenderTaskID::AnimationTimes).isDone)
			updateRenderer = true;


		entityx::ComponentHandle<AnimationComponent> animation;

		for (entityx::Entity entity : es.entities_with_components(animation)) {

			updateAnimation(*animation.get(), dt, updateRenderer);
		}


		if (_graphicsMgr.GetRenderTask(RenderTaskID::AnimationTimes).isDone)
			_graphicsMgr.GetRenderTask(RenderTaskID::AnimationTimes).isDone = false;

	}

} // ns XE