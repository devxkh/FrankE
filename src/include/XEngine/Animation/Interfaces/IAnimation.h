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

#ifndef __TECNOFREAK__I_ANIMATION__H__
#define __TECNOFREAK__I_ANIMATION__H__

#include <string>

#include <XEAnimation/Common.h>
#include <XEAnimation/BoneWeightList.h>

namespace XE
{

class TecnoFreakDllExport IAnimation
{
public:

		/**
		Get the animation name.

		@return Animation name.
		*/
	virtual const std::string& getName() const = 0;


		/**
		Check if the animation is enabled.

		@return True if the animation is enabled, false if it isn't.
		*/
	virtual bool getEnabled() const = 0;

		/**
		Enable or disable an animation.

		@param enabled Parameter indicating whether to enable or disable the animation.
		*/
	virtual void setEnabled( const bool enabled ) = 0;


		/**
		Get the amount by which this animation should be blended with others.

		An animation will only be blended if it's enabled.

		Values should be between 0 and 1. A value of 0 means no effect, 1 means full effect.

		@return Weight of the animation.
		*/
	virtual float getWeight() const = 0;

		/**
		Assign a weight by which the animation should be blended.

		An animation will only be blended if it's enabled.

		Values should be between 0 and 1. A value of 0 means no effect, 1 means full effect.

		Changing the weight of an animation may alter its enabled value.

		@param weight Weight to assign to the animation.
		*/
	virtual void setWeight( const float weight ) = 0;

		/**
		Get skeleton mask which this animation will effect.

		@return Skeleton Mask of the animation. Return value can be NULL.
		*/
	virtual const BoneWeightList* getMask() const = 0 ;

		/**
		Assign skeleton mask which this animation will effect.

		@param mask Skeleton Mask to assign to the animation. Can be NULL.
		*/
	virtual void setMask( const BoneWeightList* mask ) = 0;

		/**
		Get the total duration of an animation in seconds when speed is 1.

		@return Duration of the animation in seconds
		*/
	virtual float getLength() const = 0;

		/**
		Check if this animation is a looping animation.

		@return True if the animation is set to loop, false if it isn't.
		*/
	virtual bool getLoop() const = 0;

		/*
		Set the looping value of an animation.

		@param loop Looping value of the animation.
		*/
	virtual void setLoop( const bool loop ) = 0;

		/**
		Get the speed at which this animation is running relative to the 'real' animation
		speed.

		Examples:
		A value of 0 means completely stopped.
		A value of 0.5 means half speed.
		A value of 1 means normal speed.
		A value of 2 means double speed.
		A negative value will make it go backwards
		etc

		@return Speed of the animation.
		*/
	virtual float getSpeed() const = 0;

		/**
		Set the speed of the animation relative to the 'real' animation speed.

		Examples:
		A value of 0 means completely stopped.
		A value of 0.5 means half speed.
		A value of 1 means normal speed.
		A value of 2 means double speed.
		A negative value will make it go backwards
		etc

		@param speed Speed of the animation.
		*/
	virtual void setSpeed( const float speed ) = 0;

		/**
		Resets the time position of the animation.
		*/
	virtual void reset() = 0;

		/**
		Get the current time position of the animation in seconds.

		@return The current time position of the animation in seconds.
		*/
	virtual float getTimePosition() const = 0;

		/**
		Set the current time position of the animation in seconds.
		Setting the time position will not call any triggers.

		@param timePosition New time position for the animation in seconds.
		*/
	virtual void setTimePosition( const float timePosition ) = 0;

		/**
		Get the current relative time position of the animation.
		It is a value between 0 and 1.
		0 -> start of the animation.
		1 -> end of the animation.

		@return The current relative time position of the animation.
		*/
	virtual float getRelativeTimePosition() const = 0;

		/**
		Set the relative time position of the animation.
		It is a value between 0 and 1.
		0 -> start of the animation.
		1 -> end of the animation.

		@param relativeTimePosition Value from 0 to 1 to indicate the new
			relative time position of the animation.
		*/
	virtual void setRelativeTimePosition( const float relativeTimePosition ) = 0;

		/**
		Update the animation.

		@param elapsedSeconds Seconds that have passed since the last update.
		*/
	virtual void update( const float elapsedSeconds ) = 0;

		/**
		Mark the animation as being synched to another animation.
		The animation system will not update synched animations directly, it will
		leave that job to the parent animation ( the one that's synched to ).
		There is no need to set this parameter manually, as it will be done automatically
		when an animation is assigned as a child synched animation.

		@param synched True if the animation is to be synched to another animation, false
			otherwise.
		*/
	virtual void setSynched( const bool synched ) = 0;

		/**
		Check if the animation is synched to another animation.

		@return True if the animation is synched to another animation, false otherwise.
		*/
	virtual bool getSynched() const = 0;

		/**
		Adds an animation to be synched to this animation.

		@param synchedAnimation animation to be synched to the current animation.
		*/
	virtual void addSynchedChild( IAnimation* synchedAnimation ) = 0;

		/**
		Clears the list of synched animations.
		*/
	virtual void clearSynchedChildren() = 0;

		/**
		Get the number of animations synched to this one.

		@return Number of animations synched to the current animation.
		*/
	virtual unsigned int getSynchedChildrenCount() const = 0;

		/**
		Get the synched animation with the id synchedChildId.
		
		@param synchedChildId Id of the animation to obtain. Ids start at 0 and go up to 
			getSynchedChildrenCound() - 1.

		@return Synched child animation with id sychedChildId, or NULL if the id is not valid.
		*/
	virtual IAnimation* getSynchedChild( const unsigned int synchedChildId ) = 0;

	virtual ~IAnimation() {}
};

}

#endif