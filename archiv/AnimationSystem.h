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

#ifndef __TECNOFREAK__OGRE_ANIMATION_SYSTEM__H__
#define __TECNOFREAK__OGRE_ANIMATION_SYSTEM__H__

//#include <xe"../Common.h"
//#include "Nodes/OutputNode.h"
//#include "Nodes/AnimationNode.h"
//#include "ExampleAnimationSystem.h"


namespace Ogre
{
	namespace v1 {
		class Entity;
		class AnimationStateSet;
		class AnimationState;
	}
}

#include <vector>

namespace XE
{
	class GraphicsManager;

	class TecnoFreakDllExport AnimationSystem
		: public tecnofreak::ExampleAnimationSystem
	{
	public:
		AnimationSystem(GraphicsManager& gMgr, entityx::Entity entity);
		//AnimationSystem( Ogre::AnimationStateSet* animationStateSet );
		virtual ~AnimationSystem();

		virtual void loadAnimationTree(const std::string& animationTreeOgreResourceName, const std::string& ogreResourceResourceGroupName);
		virtual void loadAnimationInfo(const std::string& animationInfoOgreResourceName, const std::string& ogreResourceResourceGroupName);

		using ExampleAnimationSystem::loadAnimationTree;
		using ExampleAnimationSystem::loadAnimationInfo;

		//	void createAnimRenderer(XE::OgreEntity& ogreEntity);// Ogre::v1::Entity* entity);


		//void _MT_createAnimation(AnimationSystem* animSystem, Ogre::v1::AnimationState* animationState, float length, bool loop);
		//virtual void _RT_createAnimations(XE::OgreEntity& ogreEntity);

		//Ogre::AnimationStateSet* getAnimationStateSet();
		//const Ogre::AnimationStateSet* getAnimationStateSet() const;
		//void addAnimListener(entityx::Entity *obs) { m_AnimListener.push_back(obs); }

		////todo check if works? obs removed?
		//void removeAnimListener(entityx::Entity *obs) {

		//	m_AnimListener.erase(std::find(m_AnimListener.begin(), m_AnimListener.end(), obs));
		//}

		//renderthread
		void _RT_createAnimations(entityx::EventManager &events, entityx::Entity entity) override;


	private:

		XE::GraphicsManager& m_GraphicsManager;


	};


} // ns XE

#endif
