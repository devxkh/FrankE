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

#ifndef __TECNOFREAK__TRIGGER_FUNCTOR__H__
#define __TECNOFREAK__TRIGGER_FUNCTOR__H__

//#include "Common.h"
#include "ITriggerSubscriber.h"

namespace XE
{

/**
Sample implementation of a trigger subscriber.
Uses a member function of a class as the function to be called when a trigger fires.
*/
template < typename T >
class TriggerFunctor
	: public ITriggerSubscriber
{
public:
	TriggerFunctor( T* object, void( T::*memberFunction )( const ITrigger* ) )
		: m_object( object )
		, m_memberFunction( memberFunction )
	{
	}

	virtual void operator() ( const ITrigger* trigger)
	{
		( *m_object.*m_memberFunction )( trigger);
	}

private:
	void ( T::*m_memberFunction )( const ITrigger* );
	T* m_object;

};

}

#endif