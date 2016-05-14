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

#ifndef __TECNOFREAK__TRIGGER_SYSTEM__H__
#define __TECNOFREAK__TRIGGER_SYSTEM__H__

//#include "Common.h"
#include "Trigger.h"

#include <map>


namespace XE
{

class AnimationTriggerSystem 
{
public:
	AnimationTriggerSystem();
	virtual ~AnimationTriggerSystem();

	void addTrigger( Trigger* trigger );


	/**
	Adds a subscriber for all the triggers currently handled by this TriggerSystem.

	@param subscriber A subscriber that will be notified for all fired triggers.
	*/
	void addSubscriber( ITriggerSubscriber* subscriber );

	/**
	Adds a subscriber for all the triggers currently handled by this TriggerSystem with the name triggerName.

	@param triggerName Name of the trigger to associate the subscriber to.
	@param subscriber Trigger subscriber that will be notified when a trigger with triggerName is fired.
	*/
	void addSubscriber( const uint16_t triggerId, ITriggerSubscriber* subscriber );


	/**
	Removes the passed subscriber from any trigger it may have been associated to.

	@param subscriber Subscriber to remove.
	*/
	void removeSubscriber( ITriggerSubscriber* subscriber );
	/**
	Removes all subscribers associated to any trigger that matches the name triggerName.

	@param triggerName Name of the trigger to remove subscribers from.
	*/
	void removeSubscriber( const uint16_t triggerId );
	
	/**
	Removes a specific subscriber from a specific trigger.

	@param triggerName Name of the trigger to remove the subscriber from.
	@param subscriber The subscriber to be removed.
	*/
	void removeSubscriber( const uint16_t triggerId, ITriggerSubscriber* subscriber );
	
	/**
	Removes all subscribers from the trigger system.
	*/
	void removeAllSubscribers();

	void update( const float currentRelativeTime, const float nextRelativeTime, const float currentWeight );
private:
	typedef std::multimap< float, Trigger* > TriggerContainer;
	TriggerContainer m_triggers;
};

}

#endif