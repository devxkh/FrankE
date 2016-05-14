#ifndef __ANIMATIONCONTROLLERSYSTEM_HPP__
#define __ANIMATIONCONTROLLERSYSTEM_HPP__

//#include <XEEntity/Scene.hpp>
//#include <XEController/RendererEvent.hpp>
//#include <XERenderer/OgreCamera.hpp>
//#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <XESystem/Entityx/System.h>
#include <XESystem/TransportData.hpp>
#include <sfml/System/Vector3.hpp>


namespace XE {

	class Scene;
	//class GameEntity;
	class QueueManager;
	class GraphicsManager;
	class CameraRenderable;
	struct AnimationComponent;
	class AnimationNode;
	class HandleAnimation;



typedef std::list< AnimationNode* > AnimationNodeList;

////////////////////////////////////////////////////////////
/// \brief Camera class that can be controlled by a controller
///
////////////////////////////////////////////////////////////
class  AnimationControllerSystem : public entityx::System < AnimationControllerSystem >  //: public Ogre::GeneralAllocatedObject
{

public:
	AnimationControllerSystem(XE::GraphicsManager& gMgr, XE::Scene& scene);

	void updateAnimation(XE::AnimationComponent& animationComponent, entityx::TimeDelta dt, bool updateRenderer);
	
	void disableOrphanedAnimations(XE::AnimationComponent& animationComponent);

	void flattenReachedAnimations(XE::AnimationComponent& animationComponent, entityx::TimeDelta dt);

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

private:
	XE::Scene& m_Scene;
	XE::GraphicsManager& _graphicsMgr;

//	float m_elapsedSeconds;
	unsigned int m_updateId;


};

} // ns XE

#endif //__ANIMATIONCONTROLLERSYSTEM_HPP__