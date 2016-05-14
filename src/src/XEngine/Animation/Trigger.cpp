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

#include <XEngine/Animation/Trigger.h>
#include <iostream>
#include <algorithm>

using namespace XE;

Trigger::Trigger(entityx::Entity entity, const uint16_t id, const float relativeTime, const float minWeightThreshold )
: _id( id )
, m_relativeTime( relativeTime )
, m_minWeightThreshold( minWeightThreshold )
, _entity(entity)
{

}

Trigger::~Trigger()
{
	clearSubscribers();
}


entityx::Entity Trigger::getEntity() const
{
	return _entity;
}

const uint16_t Trigger::getId() const
{
	return _id;
}

float Trigger::getRelativeTime() const
{
	return m_relativeTime;
}

float Trigger::getMinWeightThreshold() const
{
	return m_minWeightThreshold;
}

void Trigger::notify( const float currentWeight ) const
{
	if ( currentWeight < getMinWeightThreshold() )
	{
		return;
	}
	
	for ( unsigned int i = 0; i < m_subscribers.size(); i++ )
	{
		ITriggerSubscriber* triggerFunctor = m_subscribers[ i ];
		( *triggerFunctor )( this );
	}

}

void Trigger::addSubscriber( ITriggerSubscriber* subscriber )
{
	/*if ( subscriber == NULL )
	{
		return;
	}*/

	std::vector< ITriggerSubscriber* >::const_iterator it;
	it = std::find( m_subscribers.begin(), m_subscribers.end(), subscriber );
	
	bool subscriberExists = ( it != m_subscribers.end() );
	if ( subscriberExists )
	{
		return;
	}

	m_subscribers.push_back( subscriber );
}

void Trigger::removeSubscriber( ITriggerSubscriber* subscriber )
{
	std::vector< ITriggerSubscriber* >::iterator it;
	it = std::find( m_subscribers.begin(), m_subscribers.end(), subscriber );

	bool subscriberExists = ( it != m_subscribers.end() );
	if ( ! subscriberExists )
	{
		return;
	}

	m_subscribers.erase( it );
}

void Trigger::clearSubscribers()
{
	m_subscribers.clear();
}