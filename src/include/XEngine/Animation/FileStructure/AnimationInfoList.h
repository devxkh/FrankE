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


#ifndef __TECNOFREAK__FILE_STRUCTURE__ANIMATION_INFO_LIST__H__
#define __TECNOFREAK__FILE_STRUCTURE__ANIMATION_INFO_LIST__H__

#include "Reader/Xml.h"

namespace tecnofreak
{

namespace file_structure
{

typedef enum
{
	TIME_TYPE_RELATIVE,
	TIME_TYPE_ABSOLUTE
} TimeTypeEnum;

class TimeType
	: public reader::Enumeration< TimeTypeEnum >
{
public:
	TimeType()
	{
		registerValue( "relative", TIME_TYPE_RELATIVE );
		registerValue( "absolute", TIME_TYPE_ABSOLUTE );
	}
};

class TriggerInfo
	: public reader::PropertyMap
{
public:
	TriggerInfo()
	{
		addFactoryMethod( "TimeType", reader::GenericPropertyCreator< TimeType > );

		registerProperty( "name", "String" );
		registerProperty( "time", "Float" );
		registerProperty( "time_type", "TimeType" );
		registerProperty( "min_weight_threshold", "Float", new reader::Float( 0 ) );
	}
};

class TriggerInfoList
	: public reader::PropertyList< TriggerInfo >
{
public:
	TriggerInfoList()
	{
		addFactoryMethod( "TriggerInfo", reader::GenericPropertyCreator< TriggerInfo > );

		registerProperty( "trigger_info", "TriggerInfo" );
	}
};

class AnimationInfo
	: public reader::PropertyMap
{
public:
	AnimationInfo()
	{
		addFactoryMethod( "TriggerInfoList", reader::GenericPropertyCreator< TriggerInfoList > );

		registerProperty( "name", "String" );
		registerProperty( "loop", "Boolean", new reader::Boolean( true ) );
		registerProperty( "trigger_info_list", "TriggerInfoList" );
	}
};



class AnimationInfoList
	: public reader::PropertyList< AnimationInfo >
{
public:
	AnimationInfoList()
	{
		addFactoryMethod( "AnimationInfo", reader::GenericPropertyCreator< AnimationInfo > );

		registerProperty( "animation_info", "AnimationInfo" );
	}
};

}

}

#endif
