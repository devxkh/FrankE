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

#include <XEngine/Animation/ExampleDummyAnimation.h>
#include <XEngine/Animation/Helper/Clamp.h>

#include <cmath>

using namespace tecnofreak;

ExampleDummyAnimation::ExampleDummyAnimation( const std::string& name )
: ExampleAnimation()
, m_name( name )
, m_timePosition( 0 )
, m_weight( 0 )
, m_enabled( false )
, m_loop( true )
, m_speed( 1 )
{

}

ExampleDummyAnimation::~ExampleDummyAnimation()
{

}

const std::string& ExampleDummyAnimation::getName() const
{
	return m_name;
}

bool ExampleDummyAnimation::getEnabled() const
{
	return m_enabled;
}

void ExampleDummyAnimation::setEnabled( const bool enabled )
{
	m_enabled = enabled;
}

float ExampleDummyAnimation::getWeight() const
{
	return m_weight;
}

void ExampleDummyAnimation::setWeight( const float weight )
{
	m_weight = weight;

	// Enable or disable animation based on weight.
	bool validWeight = ( 0.0001 < weight );
	setEnabled( validWeight );
}

const BoneWeightList* ExampleDummyAnimation::getMask() const
{
	return &m_mask;
}

void ExampleDummyAnimation::setMask( const BoneWeightList* mask )
{
	if ( mask == NULL )
	{
		m_mask.clear();
	}
	else
	{
		m_mask = *mask;
	}
}

float ExampleDummyAnimation::getLength() const
{
	return 1;
}

bool ExampleDummyAnimation::getLoop() const
{
	return m_loop;
}

void ExampleDummyAnimation::setLoop( const bool loop )
{
	m_loop = loop;
}

float ExampleDummyAnimation::getSpeed() const
{
	return m_speed;
}

void ExampleDummyAnimation::setSpeed( const float speed )
{
	m_speed = speed;
}

void ExampleDummyAnimation::reset()
{
	m_timePosition = 0;
}

void ExampleDummyAnimation::update( const float elapsedSeconds )
{
	preUpdateSynchChildren();
	preUpdateTriggers();

	float updateTime = elapsedSeconds * getSpeed();
	updateTimePosition( updateTime );

	postUpdateTriggers( updateTime );
	postUpdateSynchChildren();
}

void ExampleDummyAnimation::updateTimePosition( const float animationUpdateSeconds )
{
	// Triggers may be skipped when looping if step size is too big.
	// eg. m_timePosition is 0.5 and elapsedSeconds and m_speed are 1.

	m_timePosition += animationUpdateSeconds;
	if ( getLoop() )
	{
		if ( m_timePosition < 0 )
		{
			float oldTimePosition = m_timePosition;
			m_timePosition = std::abs( m_timePosition );
		}

		if ( 1 < m_timePosition )
		{
			float oldTimePosition = m_timePosition;
			m_timePosition = m_timePosition - int( m_timePosition );
		}
	}
	else
	{
		m_timePosition = helper::clamp< float >( m_timePosition, 0, 1 );
	}
}

float ExampleDummyAnimation::getRelativeTimePosition() const
{
	// Length is hard coded to 1.
	return m_timePosition;
}

void ExampleDummyAnimation::setRelativeTimePosition( const float relativeTimePosition )
{
	// Length is hard coded to 1.
	setTimePosition( relativeTimePosition );
}

float ExampleDummyAnimation::getTimePosition() const
{
	return m_timePosition;
}

void ExampleDummyAnimation::setTimePosition( const float timePosition )
{
	m_timePosition = timePosition;
	updateTimePosition( 0 );
}