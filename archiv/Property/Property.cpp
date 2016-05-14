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

#include <XEngine/Animation/Property/Property.h>

#include <sstream>
#include <algorithm>
#include <cctype>

using namespace tecnofreak::property;

Property::Property()
{

}

Property::~Property()
{
	for ( unsigned int i = 0; i < m_children.size(); i++ )
	{
		delete m_children[ i ];
	}
}

const std::string& Property::getValue() const
{
	return m_value;
}

void Property::setValue( const std::string& value )
{
	m_value = value;
}

Property* Property::getChild( const std::string& name )
{
	int childId = getChildId( name );
	return getChild( childId );
}

const Property* Property::getChild( const std::string& name ) const
{
	int childId = getChildId( name );
	return getChild( childId );
}

Property* Property::getChild( const int childId )
{
	if ( ! hasChild( childId ) )
	{
		return NULL;
	}

	return m_children[ childId ];
}

const Property* Property::getChild( const int childId ) const
{
	if ( ! hasChild( childId ) )
	{
		return NULL;
	}

	return m_children[ childId ];
}

bool Property::hasChild( const std::string& name ) const
{
	int childId = getChildId( name );
	return hasChild( childId );
}

bool Property::hasChild( const int childId ) const
{
	return ( 0 <= childId && childId < getChildCount() );
}

int Property::getChildId( const std::string& name ) const
{
	std::map< std::string, int >::const_iterator cit = m_nameIndexDictionary.find( name );
	bool idFound = ( cit != m_nameIndexDictionary.end() );

	if ( ! idFound )
	{
		return -1;
	}

	int childId = cit->second;
	return childId;
}

int Property::getChildCount() const
{
	return int( m_children.size() );
}

Property* Property::createChild( const std::string& name )
{
	// If a child with the same name already exists, it doesn't matter, carry on.
	// Only the last child created will be accessible by name though.

	Property* newChild = new Property();
	m_children.push_back( newChild );

	int newChildId = int( m_children.size() - 1 );
	m_nameIndexDictionary[ name ] = newChildId;

	return newChild;
}

Property* Property::createChild()
{
	Property* newChild = new Property();
	m_children.push_back( newChild );

	return newChild;
}

int Property::getValueAsInteger() const
{
	int value = 0;

	std::istringstream iss( getValue() );
	bool failed = ( iss >> std::dec >> value ).fail();

	if ( failed )
	{
		throw std::runtime_error( "Failed to convert value to integer." );
	}

	return value;
}

float Property::getValueAsFloat() const
{
	float value = 0;

	std::istringstream iss( getValue() );
	bool failed = ( iss >> std::dec >> value ).fail();

	if ( failed )
	{
		throw std::runtime_error( "Failed to convert value to float." );
	}

	return value;

}

// Necessary to remove ambiguity caused by declaration
// of std::tolower in both iostream and cctype.
int toLower( int c )
{
    return std::tolower( c );
}

bool Property::getValueAsBoolean() const
{
	std::string valueString = getValue();
	std::transform( valueString.begin(), valueString.end(), valueString.begin(), toLower );

	if ( valueString == "true" || valueString == "yes" || valueString == "1" )
	{
		return true;
	}
	else if ( valueString == "false" || valueString == "no" || valueString == "0" )
	{
		return false;
	}
	else
	{
		throw std::runtime_error( "Failed to convert value to boolean." );
	}
}