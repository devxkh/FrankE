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

#ifndef __TECNOFREAK__I_ANIMATION_SYSTEM__H__
#define __TECNOFREAK__I_ANIMATION_SYSTEM__H__

#include <XEAnimation/Common.h>
#include <XEAnimation/Interfaces/IParameter.h>
#include <XEAnimation/Interfaces/ITriggerSystem.h>
#include <XEAnimation/Property/Property.h>

#include <string>

namespace XE
{

class TecnoFreakDllExport IAnimationSystem
	: public ITriggerSystem
{
public:

	virtual void update( const float elapsedSeconds ) = 0;

	virtual void loadAnimationTree(const std::string& animationTreeFilename, const std::string& ogreResourceResourceGroupName) = 0;
	virtual void loadAnimationTree( const Property* animationTree ) = 0;

	virtual void loadAnimationInfo(const std::string& animationInfoFilename, const std::string& ogreResourceResourceGroupName) = 0;
	virtual void loadAnimationInfo( const Property* animationInfo ) = 0;


	virtual bool hasParameter( const std::string& parameterName ) const = 0;
	virtual IParameter* getParameter( const std::string& parameterName ) = 0;
	virtual const IParameter* getParameter( const std::string& parameterName ) const = 0;


	virtual ~IAnimationSystem() {}
};

}

#endif
