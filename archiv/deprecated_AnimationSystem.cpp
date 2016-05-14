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

#include <XEngine/Animation/AnimationSystem.h>
#include <XEngine/Animation/Animation.h>

#include <XEngine/Animation/Property/Xml/PropertyBuilder.h>
#include <XEngine/Animation/Property/Property.h>

#include <Ogre/OgreMain/include/OgreResourceManager.h>
//#include <Ogre/OgreMain/include/OgreEntity.h>
//#include <Ogre/OgreMain/include/OgreOldSkeletonInstance.h>

//#include <Ogre/OgreMain/include/Ogre.h>
//#include <XERenderer/OgreEntity.hpp>
#include <XERenderer/GraphicsManager.hpp>

#include <XERenderer/AnimationRenderable.hpp>
#include <XEngine/Components/Animation.hpp>
//#include <XEEntity/EntityAnimation.hpp>


#include <Ogre/OgreMain/include/OgreEntity.h>

#include <cassert>

using namespace tecnofreak;
//using namespace tecnofreak::ogre;

namespace XE
{
	AnimationSystem::AnimationSystem(GraphicsManager& gMgr, entityx::Entity entity)
		: ExampleAnimationSystem(gMgr, entity)
		, m_GraphicsManager(gMgr)
	{

	}

	//AnimationSystem::AnimationSystem( Ogre::AnimationStateSet* animationStateSet )
	//: ExampleAnimationSystem()
	//, m_animations( animationStateSet )
	//{
	//	assert( getAnimationStateSet() );
	//}


	AnimationSystem::~AnimationSystem()
	{
	}


	void AnimationSystem::loadAnimationTree(const std::string& animationTreeOgreResourceName, const std::string& ogreResourceResourceGroupName)
	{
		using namespace tecnofreak::property;

		Ogre::DataStreamPtr dataStream = Ogre::ResourceGroupManager::getSingleton().openResource(animationTreeOgreResourceName, ogreResourceResourceGroupName);

		std::string animationTreeData(dataStream->getAsString());

		Property animationTree;
		xml::PropertyBuilder::initialiseFromData(&animationTree, animationTreeData);

		loadAnimationTree(&animationTree);
	}


	void AnimationSystem::loadAnimationInfo(const std::string& animationInfoOgreResourceName, const std::string& ogreResourceResourceGroupName)
	{
		using namespace tecnofreak::property;

		Ogre::DataStreamPtr dataStream = Ogre::ResourceGroupManager::getSingleton().openResource(animationInfoOgreResourceName, ogreResourceResourceGroupName);

		std::string animationInfoData(dataStream->getAsString());

		Property animationInfo;
		xml::PropertyBuilder::initialiseFromData(&animationInfo, animationInfoData);

		loadAnimationInfo(&animationInfo);
	}



	//renderthread
	void AnimationSystem::_RT_createAnimations(entityx::EventManager &events, entityx::Entity entity)//XE::OgreEntity& ogreEntity)
	{

		m_GraphicsManager.getIntoRendererQueue().push([this, &entity](){

			entityx::ComponentHandle<AnimationRenderable> animRenderable = entity.component<AnimationRenderable>();

			animRenderable->_t_animations = animRenderable->getAllAnimationStates();


			//Ogre::AnimationStateSet* animationStates = getAnimationStateSet();

			// Although there is an assert for this condition in the constructor, added check for 
			// safety in a release build.
			if (animRenderable->_t_animations == NULL)
			{
				return;
			}

			Ogre::v1::AnimationStateIterator it = animRenderable->_t_animations->getAnimationStateIterator();
			while (it.hasMoreElements())
			{
				Ogre::v1::AnimationState* animationState = it.getNext();

				if (0 < animationState->getLength())
				{
					//todo debug if access to animation from renderthread cause problems!
					//mainthread
					m_GraphicsManager.getFromRendererQueue().push([this, animationState, &entity](){

						entityx::ComponentHandle<AnimationComponent> animation = entity.component<AnimationComponent>();

						//mit pointerübergabe
						animation->_MT_createAnimation(animationState, animationState->getLength(), animationState->getLoop());
					});
				}
			}

			//mainthread
			m_GraphicsManager.getFromRendererQueue().push([this](){

				// 5. Publisher broadcasts
				//for (int i = 0; i < m_AnimListener.size(); i++)

				//todo emit event for character animations!!!

			//	events.emit<AnimationCreatedEvent>(left.entity, right.entity);


				//for each (auto entity in m_AnimListener)
				//{
				//	entityx::ComponentHandle<XE::AnimationComponent> entityAnimation = entity->component<XE::AnimationComponent>();

				//	entityAnimation->EvtAnimCreated();
				//	//m_AnimListener[i]->EvtAnimCreated();
				//}
			});
		});


	}

	//Ogre::AnimationStateSet* AnimationSystem::getAnimationStateSet()
	//{
	//	return m_animations;
	//}
	//
	//const Ogre::AnimationStateSet* AnimationSystem::getAnimationStateSet() const
	//{
	//	return m_animations;
	//}

} // ns XE