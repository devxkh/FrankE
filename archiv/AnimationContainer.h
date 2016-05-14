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

#ifndef __TECNOFREAK__ANIMATION_CONTAINER__H__
#define __TECNOFREAK__ANIMATION_CONTAINER__H__

#include "Common.h"

#include <vector>
#include <map>
#include <cassert>

namespace XE
{

template< typename AnimationType >
class TecnoFreakDllPrivate AnimationContainer
{
public:
	static const int INVALID_ANIMATION_ID;

	AnimationContainer();
	virtual ~AnimationContainer();

	void clearAnimations();

	void addAnimation( AnimationType* animation );

	int getAnimationId( const std::string& animationName ) const;
	AnimationType* getAnimation( const int animationId );
	const AnimationType* getAnimation( const int animationId ) const;
	bool hasAnimation( const int animationId ) const;

	AnimationType* getAnimation( const std::string& animationName );
	const AnimationType* getAnimation( const std::string& animationName ) const;
	bool hasAnimation( const std::string& AbstractAnimation ) const;
	
	int getAnimationCount() const;

	// TODO: animation name iterator.
	// TODO: animation iterator.
private:
	typedef std::map< std::string, int > NameIndexDictionary;
	NameIndexDictionary m_animationNameToIdDictionary;

	std::vector< AnimationType* > m_animations;
};

#include "AnimationContainerImplementation.h"

}

#endif
