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

#include <XEngine/Animation/ExampleAnimationSystem.h>

#include <XEngine/Animation/ExampleDummyAnimation.h>

#include <XEngine/Animation/NodeFactory.h>

#include <XEngine/Animation/Nodes/ParameterNode.h>

#include <XEngine/Animation/Helper/Clamp.h>

#include <cassert>
#include <sstream>

#include <XEngine/Animation/Property/Xml/PropertyBuilder.h>
#include <XEngine/Animation/Property/Property.h>


#include <XERenderer/GraphicsManager.hpp>

using namespace tecnofreak;
using namespace tecnofreak::property;

ExampleAnimationSystem::ExampleAnimationSystem(XE::GraphicsManager& gMgr, entityx::Entity entity)
: NodeContainer()
, ParameterContainer()
, m_GraphicsManager(gMgr)
,_entity(entity)
{
	assert( INVALID_ANIMATION_ID < 0 );
}

ExampleAnimationSystem::~ExampleAnimationSystem()
{
}

bool ExampleAnimationSystem::hasParameter( const std::string& parameterName ) const
{
	return ParameterContainer::hasParameter( parameterName );
}

IParameter* ExampleAnimationSystem::getParameter( const std::string& parameterName )
{
	return ParameterContainer::getParameter( parameterName );
}

const IParameter* ExampleAnimationSystem::getParameter( const std::string& parameterName ) const
{
	return ParameterContainer::getParameter( parameterName );
}

void ExampleAnimationSystem::loadAnimationTree( const tecnofreak::property::Property* animationInfo )
{
///todo	createAnimations();

//	m_GraphicsManager.getIntoRendererQueue().push([this, animationInfo](){

	NodeContainer::initialise( animationInfo );
	ParameterContainer::initialise( animationInfo );

	for ( int i = 0; i < getNodeCount(); i++ )
	{
		INode* node = getNode( i );
		AnimationNode* animationNode = dynamic_cast< AnimationNode* >( node );
		if ( animationNode )
		{
			const std::string& animationName = animationNode->getAnimationName();
			int animationId = getAnimationId( animationName );

			if ( animationId == INVALID_ANIMATION_ID )
			{
				ExampleDummyAnimation* animation = new ExampleDummyAnimation( animationName );
				addAnimation( animation );
				animationId = getAnimationId( animationName );
				assert( animationId != INVALID_ANIMATION_ID );
			}

			animationNode->setAnimationId( animationId );

			animationNode->setAnimation( getAnimation( animationId ) );
		}

		ParameterNode* parameterNode = dynamic_cast< ParameterNode* >( node );
		if ( parameterNode )
		{
			const std::string& parameterName = parameterNode->getParameterName();
			IParameter* parameter = getParameter( parameterName );
			assert( parameter );
			if ( ! parameter )
			{
				throw std::runtime_error( "missing parameter" );
			}
			parameterNode->setParameter( parameter );
		}
	}
//	});
}

void ExampleAnimationSystem::loadAnimationTree( const std::string& animationTreeFilename )
{
	Property animationInfo;
	xml::PropertyBuilder::initialiseFromFile( &animationInfo, animationTreeFilename );

	loadAnimationTree( &animationInfo );
}

void ExampleAnimationSystem::update(entityx::Entity entity, const float dt)// const float elapsedSeconds)
{
	getSharedData()->setElapsedSeconds( dt );
	getSharedData()->increaseUpdateId();

	getCurrentAnimations().clear();

	getReachedAnimationNodes().clear();

	getOutputNode()->evaluateAnimations( getReachedAnimationNodes(), NULL );

	flattenReachedAnimations();

	updateCurrentAnimations( dt );

	disableOrphanedAnimations();
}

void ExampleAnimationSystem::disableOrphanedAnimations()
{
	unsigned int updateId = getSharedData()->getUpdateId();

	for ( int i = 0; i < getAnimationCount(); i++ )
	{
		ExampleAnimation* animation = getAnimation( i );
		bool updatedNow = ( animation->getLastUpdateId() == updateId );
		animation->setEnabled( updatedNow );
	}
}

void ExampleAnimationSystem::updateCurrentAnimations( const float elapsedSeconds )
{
	unsigned int updateId = getSharedData()->getUpdateId();

	for ( ExampleAnimationList::iterator it = getCurrentAnimations().begin(); it != getCurrentAnimations().end(); it++ )
	{
		ExampleAnimation* animation = *it;

		assert( animation );

		// TODO: think how to deal with repeated animations.
		// float animationWeight = animation->calculateRealWeight();
		float animationWeight = animation->getAccumulatedWeight();
		animation->setWeight( animationWeight );

		const BoneWeightList* mask = animation->calculateAccumulatedMask();
		animation->setMask( mask );

		float animationSpeed = animation->calculateRealSpeed();
		animation->setSpeed( animationSpeed );

		if ( ! animation->getSynched() )
		{
			animation->update( elapsedSeconds );
		}

		animation->resetActiveReferencingNodesCount();
		animation->resetAccumulatedWeight();
		animation->resetAccumulatedMask();
		animation->resetAccumulatedSpeed();

		animation->setLastUpdateId( updateId );
	}
}


void ExampleAnimationSystem::flattenReachedAnimations()
{
	for ( AnimationNodeList::iterator it = getReachedAnimationNodes().begin(); it != getReachedAnimationNodes().end(); it++ )
	{
		AnimationNode* animationNode = *it;
		int animationId = animationNode->getAnimationId();
		ExampleAnimation* animation = getAnimation( animationId );

		assert( animation );

		animation->increaseActiveReferencingNodeCount();

		float animationWeight = animationNode->getWeight();
		animation->increaseAccumulatedWeight( animationWeight );

		const BoneWeightList* mask = animationNode->getMask();
		animation->increaseAccumulatedMask( mask, animationWeight );

		float animationSpeed = animationNode->evaluateAnimationSpeed();
		animation->increaseAccumulatedSpeed( animationSpeed );

		if ( animation->getActiveReferencingNodesCount() == 1 )
		{
			getCurrentAnimations().push_back( animation );
		}
	}
}


ExampleAnimationList& ExampleAnimationSystem::getCurrentAnimations()
{
	return m_currentAnimations;
}

const ExampleAnimationList& ExampleAnimationSystem::getCurrentAnimations() const
{
	return m_currentAnimations;
}

AnimationNodeList& ExampleAnimationSystem::getReachedAnimationNodes()
{
	return m_reachedAnimationNodes;
}

const AnimationNodeList& ExampleAnimationSystem::getReachedAnimationNodes() const
{
	return m_reachedAnimationNodes;
}

void ExampleAnimationSystem::loadAnimationInfo( const std::string& animationInfoFilename )
{
	Property animationInfoList;
	xml::PropertyBuilder::initialiseFromFile( &animationInfoList, animationInfoFilename );

	loadAnimationInfo( &animationInfoList );
}

void ExampleAnimationSystem::loadAnimationInfo( const tecnofreak::property::Property* animationInfoList )
{
	for ( int i = 0; i < animationInfoList->getChildCount(); i++ )
	{
		const Property* animationInfo = animationInfoList->getChild( i );

		parseAnimationInfo( animationInfo );
	}
}

void ExampleAnimationSystem::parseAnimationInfo( const Property* animationInfo )
{
	assert( animationInfo );

	if ( ! animationInfo->hasChild( "name" ) )
	{
		return;
	}

	std::string animationName = animationInfo->getChild( "name" )->getValue();

	ExampleAnimation* animation = getAnimation( animationName );

	if ( animationInfo->hasChild( "loop" ) )
	{
		bool animationLoop = animationInfo->getChild( "loop" )->getValueAsBoolean();
		animation->setLoop( animationLoop );
	}


	if ( animationInfo->hasChild( "trigger_info_list" ) )
	{
		const Property* triggerInfoList = animationInfo->getChild( "trigger_info_list" );
		for ( int i = 0; i < triggerInfoList->getChildCount(); i++ )
		{
			const Property* triggerInfo = triggerInfoList->getChild( i );
			parseTriggerInfo( animation, triggerInfo );
		}
	}
}


void ExampleAnimationSystem::parseTriggerInfo( ExampleAnimation* animation, const Property* triggerInfo )
{
	assert( animation );
	assert( triggerInfo );

	if ( ! triggerInfo->hasChild( "name" ) )
	{
		return;
	}
	std::string triggerName = triggerInfo->getChild( "name" )->getValue();

	if ( ! triggerInfo->hasChild( "time" ) )
	{
		return;
	}
	float triggerTime = triggerInfo->getChild( "time" )->getValueAsFloat();

	if ( ! triggerInfo->hasChild( "time_type" ) )
	{
		return;
	}

	float relativeTime = triggerTime;
	if ( triggerInfo->getChild( "time_type" )->getValue() == "absolute" )
	{
		float absoluteTime = triggerTime;
		if ( absoluteTime < 0 )
		{
			// Negative absolute times are read as an offset from the animation end.
			absoluteTime = animation->getLength() + absoluteTime;
		}
		relativeTime = absoluteTime / animation->getLength();
	}

	// Don't allow a relative time of 1, because it causes the trigger to dispatch every frame
	// when a non-looping animation reaches the end.
	relativeTime = helper::clamp< float >( relativeTime, 0, 0.999999f );

	float minWeightThreshold = 0;
	if ( triggerInfo->hasChild( "min_weight_threshold" ) )
	{
		minWeightThreshold = triggerInfo->getChild( "min_weight_threshold" )->getValueAsFloat();
	}

	Trigger* trigger = new Trigger( _entity, triggerName, relativeTime, minWeightThreshold );
	animation->addTrigger( trigger );
}

void ExampleAnimationSystem::addSubscriber( ITriggerSubscriber* subscriber )
{
	for ( int i = 0; i < getAnimationCount(); i++ )
	{
		ExampleAnimation* animation = getAnimation( i );
		animation->addTriggerSubscriber( subscriber );
	}
}

void ExampleAnimationSystem::addSubscriber( const std::string& triggerName, ITriggerSubscriber* subscriber )
{
	for ( int i = 0; i < getAnimationCount(); i++ )
	{
		ExampleAnimation* animation = getAnimation( i );
		animation->addTriggerSubscriber( triggerName, subscriber );
	}
}

void ExampleAnimationSystem::removeSubscriber( ITriggerSubscriber* subscriber )
{
	for ( int i = 0; i < getAnimationCount(); i++ )
	{
		ExampleAnimation* animation = getAnimation( i );
		animation->removeTriggerSubscriber( subscriber );
	}
}

void ExampleAnimationSystem::removeSubscriber( const std::string& triggerName )
{
	for ( int i = 0; i < getAnimationCount(); i++ )
	{
		ExampleAnimation* animation = getAnimation( i );
		animation->removeTriggerSubscriber( triggerName );
	}
}

void ExampleAnimationSystem::removeSubscriber( const std::string& triggerName, ITriggerSubscriber* subscriber )
{
	for ( int i = 0; i < getAnimationCount(); i++ )
	{
		ExampleAnimation* animation = getAnimation( i );
		animation->removeTriggerSubscriber( triggerName, subscriber );
	}
}

void ExampleAnimationSystem::removeAllSubscribers()
{
	for ( int i = 0; i < getAnimationCount(); i++ )
	{
		ExampleAnimation* animation = getAnimation( i );
		animation->clearTriggerSubscribers();
	}
}
