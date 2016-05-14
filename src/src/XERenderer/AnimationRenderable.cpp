//#include <XERenderer/AnimationRenderable.hpp>
//
//#include <XESystem/Entityx/entityx.h>
//
//#include <Ogre/OgreMain/include/OgreEntity.h>
//#include <Ogre/OgreMain/include/OgreOldSkeletonInstance.h>
//
//namespace XE {
//
//
//	AnimationRenderable::AnimationRenderable(sf::Uint16 id, GraphicsManager& gmanager, Scene& scene, Renderable& renderable) :
//	//	: Renderable(id, gmanager, scene)
//		 _t_animations(nullptr)
//		, m_GraphicsManager(gmanager)
//		, _renderable(renderable)
//	{
//		setBlendmode();
//	}
//	
//	Ogre::v1::AnimationStateSet* AnimationRenderable::getAllAnimationStates() {
//		return	_renderable._t_OgreEntityPtr->getAllAnimationStates();
//	}
//
//	void AnimationRenderable::setBlendmode()// Ogre::v1::Entity* _t_entity)
//	{
//		m_GraphicsManager.getIntoRendererQueue().push([this](){
//			//	assert(_t_entity);
//
//			//	m_t_animations = ogreEntity._t_getEntPtr()->getAllAnimationStates();
//
//			bool entityIsAnimated = (_renderable._t_OgreEntityPtr->getAllAnimationStates() != NULL);
//			assert(entityIsAnimated);
//
//			Ogre::v1::OldSkeletonInstance* skeleton = _renderable._t_OgreEntityPtr->getSkeleton();
//			skeleton->setBlendMode(Ogre::v1::ANIMBLEND_CUMULATIVE);
//		});
//
//
//	}
//
//
//} // ns XE