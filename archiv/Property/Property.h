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

#ifndef __TECNOFREAK__PROPERTY__PROPERTY__H__
#define __TECNOFREAK__PROPERTY__PROPERTY__H__

#include <XEngine/Animation/Common.h>

#include <map>
#include <vector>

namespace tecnofreak
{

namespace property
{

class TecnoFreakDllExport Property
{
public:
	Property();
	virtual ~Property();

	const std::string& getValue() const;
	void setValue( const std::string& value );

	Property* getChild( const std::string& name );
	const Property* getChild( const std::string& name ) const;

	Property* getChild( const int childId );
	const Property* getChild( const int childId ) const;

	bool hasChild( const std::string& name ) const;
	bool hasChild( const int childId ) const;

	int getChildId( const std::string& name ) const;
	int getChildCount() const;

	Property* createChild( const std::string& name );
	Property* createChild();

	int getValueAsInteger() const;
	float getValueAsFloat() const;
	bool getValueAsBoolean() const;

private:
	std::string m_value;
	std::map< std::string, int > m_nameIndexDictionary;
	std::vector< Property* > m_children;
};

}

}

#endif