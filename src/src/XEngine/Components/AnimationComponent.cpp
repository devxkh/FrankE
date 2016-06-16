#include <XEngine/Components/AnimationComponent.hpp>

#include <XEngine/Animation/HandleAnimation.h>

#include <Ogre/OgreMain/include/Animation/OgreSkeletonAnimation.h>
//#include <Ogre/OgreMain/include/Animation/OgreSkeletonAnimationDef.h>

#include <XEngine/Animation/Nodes/AnimationNode.h>
#include <XEngine/Animation/Nodes/OutputNode.h>
#include <XEngine/Animation/Nodes/ParameterNode.h>
#include <XEngine/Animation/Nodes/MixNode.h>
#include <XEngine/Animation/Nodes/TransitionSelectNode.h>
#include <XEDAL/Objects/FBEngineTypes_generated.h>

#include <XESystem/Logging.hpp>

namespace XE
{

	AnimationComponent::AnimationComponent(GraphicsManager& graphicsManager, entityx::Entity entity)
		:
		graphicsManager(graphicsManager)
		//, animationSystem(graphicsManager, entity)
		, _animations()
		, _nodes()
		, animIdMap()
		, m_reachedAnimationNodes()
		, animationState(nullptr)
	{
		//outputnode has id = 0
		_nodes.emplace(0, std::unique_ptr<Node>(new OutputNode));
	}

	AnimationComponent::~AnimationComponent()
	{
		removeAllSubscribers();
	}

	void AnimationComponent::initialize(const XFBType::AnimationComponent* fbData)
	{
		auto nodes = fbData->nodes();
		if (nodes)
		{
			//add animationstate -> nodeid = 0
			auto test = std::unique_ptr<ParameterNode>(new ParameterNode);
			animationState = static_cast<ParameterNode*>(test.get());
			_nodes.emplace(0, std::move(test));

			for (auto var : *nodes)
			{
				std::unique_ptr<Node> newNode = nullptr;

				//std::cout << "meshes:" << var->Name()->c_str() << std::endl;
				if (var->node_type() == XFBType::UAnimationNode::UAnimationNode_AnimationNode)
				{
					newNode = std::unique_ptr<AnimationNode>(new AnimationNode);

					auto fbAnimationNode = reinterpret_cast<const XFBType::AnimationNode*>(var->node());
										
					auto tes2 = fbAnimationNode->animation()->id();
					auto test = fbAnimationNode->animation()->name()->c_str();
					animIdMap.emplace(test, fbAnimationNode->animation()->id());

					std::unique_ptr<HandleAnimation> newAnimation = std::unique_ptr<HandleAnimation>(new HandleAnimation(graphicsManager, fbAnimationNode->animation()->id()));
					newAnimation->setLoop(fbAnimationNode->animation()->loop());

					AnimationNode* animationNode = static_cast<AnimationNode*>(newNode.get());
					animationNode->setAnimation(newAnimation.get());
				
					_animations.emplace_back(std::move(newAnimation));
				}
				else if (var->node_type() == XFBType::UAnimationNode::UAnimationNode_ParameterNode)
					newNode = std::unique_ptr<ParameterNode>(new ParameterNode);
				else if (var->node_type() == XFBType::UAnimationNode::UAnimationNode_TransitionSelectNode)
					newNode = std::unique_ptr<TransitionSelectNode>(new TransitionSelectNode);
				else if (var->node_type() == XFBType::UAnimationNode::UAnimationNode_MixNode)
					newNode = std::unique_ptr<MixNode>(new MixNode);

				if (newNode)
				{
					newNode->setNodeId(var->id());
					newNode->init(var->node());

					_nodes.emplace(var->id(), std::move(newNode));
				}
			}
		}
		
		auto connections = fbData->connections();
		if (connections)
		{
			for (auto connection : *connections)
			{
				auto t1 = connection->nodeIn(); //debug
				auto t2 = connection->nodeOut();

				INode* nodeIn = _nodes[connection->nodeIn()].get(); // getNode(idAssociations[nodeInId]);
				INode* nodeOut = _nodes[connection->nodeOut()].get();

				if (nodeIn == NULL)
				{
					LOG(ERROR) << "Connection with invalid node_in: " << connection->nodeIn();
				}

				if (nodeOut == NULL)
				{
					LOG(ERROR) << "Connection with invalid node_out: " << connection->nodeOut();
				}

				Port* port = nodeIn->getPort(connection->portIn());
				if (port == NULL)
				{
					LOG(ERROR) << "Connection with invalid port: " << connection->portIn() << " for node " << connection->nodeIn();
				}

				port->setConnectedNode(nodeOut);
			}
		}

		//loadOutputConnection
	//	INode* nodeConnectedToOutputNode = _nodes[fbData->output()].get();
	//	static_cast<OutputNode*>(_nodes[0].get())->getAnimationInPort()->setConnectedNode(nodeConnectedToOutputNode);

		auto constants = fbData->constants();
		if (constants)
		{
			for (auto constant : *constants)
			{
				INode* node = _nodes[constant->nodeId()].get();

				if (node == NULL)
				{
					LOG(ERROR) << "Connection with invalid node_id: " << constant->nodeId();
				}

				bool validPort = node->hasPort(constant->portId());
				
				if (!validPort)
				{
					LOG(ERROR) << "Constant with invalid port " << constant->portId() << " for node " << constant->nodeId();
				}
				else
				{
					Port* port = node->getPort(constant->portId());

					port->setDefaultValue(constant->value());
				}
			}
		}
	}
	
	ParameterNode& AnimationComponent::getParameter(sf::Uint16 nodeId)
	{
		auto it = _nodes.find(nodeId);
		if (it != _nodes.end())
			return static_cast<ParameterNode&>(*it->second.get()); // geht das???
	}

	void AnimationComponent::_MT_setAnimationStatePtr(Ogre::SkeletonAnimation* animationPtr, const std::string& name, float length, std::vector< float* >* boneWeightPtrs, std::vector< float >* boneWeightList)
	{
		uint16_t animId = animIdMap[name];

		for (auto& animation : _animations)
		{
			if (animation->getId() == animId)
			{
				animation->setLength(length);
				animation->setAnimationPtr(animationPtr,boneWeightPtrs,boneWeightList);

				return;
			}
		}
	}

	void AnimationComponent::addSubscriber(ITriggerSubscriber* subscriber)
	{
		for (auto& animation : _animations)
			animation->addTriggerSubscriber(subscriber);
	}

	void AnimationComponent::addSubscriber(const int animationId, const int triggerId, ITriggerSubscriber* subscriber)
	{
		for (auto& animation : _animations)
		{
			if (animation->getId() == animationId)
			{
				animation->addTriggerSubscriber(subscriber);
				return;
			}
		}
	}

	void AnimationComponent::addSubscriber(const int triggerId, ITriggerSubscriber* subscriber)
	{
		for (auto& animation : _animations)
			animation->addTriggerSubscriber(triggerId, subscriber);
	}

	void AnimationComponent::removeSubscriber(ITriggerSubscriber* subscriber)
	{
		for (auto& animation : _animations)
			animation->removeTriggerSubscriber(subscriber);
	}

	void AnimationComponent::removeSubscriber(const int triggerId)
	{
		for (auto& animation : _animations)
			animation->removeTriggerSubscriber(triggerId);
	}

	void AnimationComponent::removeSubscriber(const int triggerId, ITriggerSubscriber* subscriber)
	{
		for (auto& animation : _animations)
			animation->removeTriggerSubscriber(triggerId, subscriber);
	}

	void AnimationComponent::removeAllSubscribers()
	{
		for (auto& animation : _animations)
			animation->clearTriggerSubscribers();
	}
}