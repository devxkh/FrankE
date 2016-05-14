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

#ifndef __TECNOFREAK__ABSTRACT_ANIMATION_SYSTEM__H__
#define __TECNOFREAK__ABSTRACT_ANIMATION_SYSTEM__H__

#include "IAnimation.h"
#include "IAnimationSystem.h"

#include "Common.h"

#include "Nodes/AnimationNode.h"
#include "ExampleAnimation.h"

#include "NodeContainer.h"
#include "ParameterContainer.h"

#include "AnimationContainer.h"


#include <XESystem/Entityx/entityx.h>

namespace entityx {
	class Entity;
}

namespace XE
{
	class GraphicsManager;
	class OgreEntity;
}
namespace tecnofreak
{

class TecnoFreakDllPrivate ExampleAnimationSystem
	: public IAnimationSystem
	, protected NodeContainer
	, protected ParameterContainer
	, protected AnimationContainer< ExampleAnimation >
{
public:

	ExampleAnimationSystem(XE::GraphicsManager& gMgr, entityx::Entity entity);
	virtual ~ExampleAnimationSystem();



	virtual bool hasParameter( const std::string& parameterName ) const;
	virtual IParameter* getParameter( const std::string& parameterName );
	virtual const IParameter* getParameter( const std::string& parameterName ) const;

	virtual void update(entityx::Entity entity, const float dt) override;// (const float elapsedSeconds);

	virtual void loadAnimationTree( const std::string& animationTreeFilename );
	virtual void loadAnimationTree( const tecnofreak::property::Property* animationTree );
	
	virtual void loadAnimationInfo( const std::string& animationInfoFilename );
	virtual void loadAnimationInfo( const tecnofreak::property::Property* animationInfo );

	virtual void addSubscriber( ITriggerSubscriber* subscriber );
	virtual void addSubscriber( const std::string& triggerName, ITriggerSubscriber* subscriber );

	virtual void removeSubscriber( ITriggerSubscriber* subscriber );
	virtual void removeSubscriber( const std::string& triggerName );
	virtual void removeSubscriber( const std::string& triggerName, ITriggerSubscriber* subscriber );

	virtual void removeAllSubscribers();
protected:

	virtual void _RT_createAnimations(entityx::EventManager &events, entityx::Entity entity) = 0;
	
	void disableOrphanedAnimations();
	void updateCurrentAnimations( const float elapsedSeconds );

	void flattenReachedAnimations();

	ExampleAnimationList& getCurrentAnimations();
	const ExampleAnimationList& getCurrentAnimations() const;

	AnimationNodeList& getReachedAnimationNodes();
	const AnimationNodeList& getReachedAnimationNodes() const;

private:

	void parseAnimationInfo( const tecnofreak::property::Property* animationInfo );
	void parseTriggerInfo( ExampleAnimation* animation, const tecnofreak::property::Property* triggerInfo );

private:

	XE::GraphicsManager& m_GraphicsManager;

	ExampleAnimationList m_currentAnimations;

	AnimationNodeList m_reachedAnimationNodes;

	entityx::Entity _entity;
};

}

#endif
