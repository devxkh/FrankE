#ifndef __ANIMATIONCOMPONENT_HPP__
#define __ANIMATIONCOMPONENT_HPP__

#include <sfml/System/Vector3.hpp>
#include <XESystem/TransportData.hpp>

#include <XEngine/Animation/Node.h>
#include <XESystem/Entityx/entityx.h>
//#include <XEngine/Animation/AnimationSystem.h>

namespace XFBType
{
	struct AnimationComponent;
}
namespace Ogre
{
	class SkeletonAnimation; 
}

namespace XE
{
	class ITriggerSubscriber;
	class GraphicsManager;
	class HandleAnimation;
	class ParameterNode;

	typedef std::list< HandleAnimation* > AnimationList;
	
	// Emitted when two entities collide.
	struct AnimationCreatedEvent {
		AnimationCreatedEvent(entityx::Entity entity) : entity(entity) {}

		entityx::Entity entity;
	};

	struct AnimationComponent {
		AnimationComponent(GraphicsManager& graphicsManager, entityx::Entity entity);
		~AnimationComponent();

		void initialize(const XFBType::AnimationComponent* fbData);
		
		/// called from renderthread after item with animation is created
		void _MT_setAnimationStatePtr(Ogre::SkeletonAnimation* animationPtr, const std::string& , float length, std::vector< float* >* boneWeightPtrs, std::vector< float >* boneWeightList);

		ParameterNode& getParameter(sf::Uint16 nodeId);

		void addSubscriber(ITriggerSubscriber* subscriber);
		void addSubscriber(const int animationId, const int triggerId, ITriggerSubscriber* subscriber);
		void addSubscriber(const int  triggerId, ITriggerSubscriber* subscriber);

		void removeSubscriber(ITriggerSubscriber* subscriber);
		void removeSubscriber(const int triggerId);
		void removeSubscriber(const int triggerId, ITriggerSubscriber* subscriber);

		void removeAllSubscribers();


		std::unordered_map<sf::Uint16, std::unique_ptr<Node>> _nodes;
		std::vector<std::unique_ptr<HandleAnimation>> _animations;


		std::unordered_map<std::string, uint16_t> animIdMap;

		ParameterNode* animationState;
		//Animation* animation;
		GraphicsManager& graphicsManager;
		std::vector < class entityx::Entity *> animListener; // 3. Coupled only to "interface"
	
		float m_accumulatedWeight;

		AnimationList m_currentAnimations;
		AnimationNodeList m_reachedAnimationNodes;
	//	QuaternionData bodyDirection;      // player's local intended direction based on WASD keys
//		QuaternionData bodyGoalDirection;      // player's local intended direction based on WASD keys
	};

}

#endif //__ANIMATIONCOMPONENT_HPP__