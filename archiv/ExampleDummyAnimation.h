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

#ifndef __TECNOFREAK__EXAMPLE_DUMMY_ANIMATION__H__
#define __TECNOFREAK__EXAMPLE_DUMMY_ANIMATION__H__

#include "Common.h"
#include "ExampleAnimation.h"

namespace tecnofreak
{

class TecnoFreakDllExport ExampleDummyAnimation
	: public ExampleAnimation
{
public:
	ExampleDummyAnimation( const std::string& name );
	virtual ~ExampleDummyAnimation();

	virtual const std::string& getName() const;

	virtual bool getEnabled() const;
	virtual void setEnabled( const bool enabled );

	virtual float getWeight() const;
	virtual void setWeight( const float weight );

	virtual const BoneWeightList* getMask() const;
	virtual void setMask( const BoneWeightList* mask );

	virtual float getLength() const;

	virtual bool getLoop() const;
	virtual void setLoop( const bool loop );

	virtual float getSpeed() const;
	virtual void setSpeed( const float speed );

	virtual void reset();

	virtual void update( const float elapsedSeconds );

	virtual float getRelativeTimePosition() const;
	virtual void setRelativeTimePosition( const float relativeTimePosition );

	virtual float getTimePosition() const;
	virtual void setTimePosition( const float timePosition );

protected:
	void updateTimePosition( const float animationUpdateSeconds );

private:
	const std::string& m_name;
	float m_timePosition;
	float m_weight;
	BoneWeightList m_mask;
	bool m_enabled;
	bool m_loop;
	float m_speed;
};

}

#endif
