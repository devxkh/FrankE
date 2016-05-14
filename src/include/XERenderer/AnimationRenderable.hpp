//#ifndef __ANIMATIONRENDERABLE_HPP__
//#define __ANIMATIONRENDERABLE_HPP__
//
////#include <Ogre/OgreMain/include/OgreMesh.h>
//#include <sfml/Config.hpp>
////#include <Ogre/OgreMain/include/OgreVector3.h>
////#include <Ogre/OgreMain/include/OgreQuaternion.h>
////#include <Ogre/OgreMain/include/OgreMatrix4.h>
//
////#include <Ogre/OgreMain/include/OgreNode.h>
//
//#include <XERenderer/Renderable.hpp>
//
//#include <XERenderer/GraphicsManager.hpp>
//
//namespace Ogre
//{
//	namespace v1
//	{
//		class AnimationStateSet;
//	}
//	//class SceneManager;
//	//class SceneNode;
//}
//
//namespace entityx
//{
//	class Entity;
//	class EventManager;
//}
//
//
//namespace XE {
//
//	class GraphicsManager;
//	class Scene;
//
//	//class OgreEntity
//	struct AnimationRenderable //: public Renderable
//	{
//	public:
//
//		explicit AnimationRenderable(sf::Uint16 id, GraphicsManager& gmanager, Scene& scene, Renderable& renderable);
//			
//		Ogre::v1::AnimationStateSet* getAllAnimationStates();
//
//		//change only in renderthread
//		Ogre::v1::AnimationStateSet* _t_animations;
//
//		GraphicsManager& m_GraphicsManager;
//
//	private:
//		void setBlendmode();
//
//		Renderable& _renderable;
//
//	};
//
//} // ns XE
//
//#endif // __ANIMATIONRENDERABLE_HPP__