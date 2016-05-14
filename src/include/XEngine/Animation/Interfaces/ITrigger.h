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

#ifndef __TECNOFREAK__I_TRIGGER__H__
#define __TECNOFREAK__I_TRIGGER__H__

#include <string>

#include <XEAnimation/Common.h>


namespace XE
{

/**
A Trigger is an event that fires at a certain time during the playback of an animation.
This class only holds information about when this event should be fired.
*/
class TecnoFreakDllExport ITrigger
{
public:
	
		/**
		Get the trigger's name.

		\return Name of the trigger.
		*/
	virtual const std::string& getName() const = 0;

		/**
		Get the relative time at which the trigger will fire for the animation.
		It is always a value between 0 and 1.
		0 represents the start of the animation, and 1 represents the end of the animation.
		
		\return Relative time ( value 0 to 1 ) at which the trigger should be fired.
		*/
	virtual float getRelativeTime() const = 0;


		/**
		Get the minimum weight the animation should have to consider firing the trigger.
		It will probably be a value between 0 and 1.

		\return Minimum weight the animation should have to fire the trigger.
		*/
	virtual float getMinWeightThreshold() const = 0;

	virtual ~ITrigger() {}

};


}

#endif
