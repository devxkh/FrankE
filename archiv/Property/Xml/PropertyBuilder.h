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

#ifndef __TECNOFREAK__PROPERTY__XML__PROPERTY_CUSTOM_BUILDER__H__
#define __TECNOFREAK__PROPERTY__XML__PROPERTY_CUSTOM_BUILDER__H__

#include <XEngine/Animation/Common.h>
#include <XEngine/Animation/Property/Property.h>

class TiXmlAttribute;
class TiXmlElement;
class TiXmlDocument;

namespace tecnofreak
{

namespace property
{

namespace xml
{

class TecnoFreakDllExport PropertyBuilder
{
public:

	static tecnofreak::property::Property* createFromData( const std::string& data );
	static tecnofreak::property::Property* createFromFile( const std::string& filename );
	
	static void initialiseFromData( tecnofreak::property::Property* element, const std::string& data );
	static void initialiseFromFile( tecnofreak::property::Property* element, const std::string& filename );
	
protected:

	static tecnofreak::property::Property* createFromTiXmlDocument( TiXmlDocument* xmlDocument );
	static tecnofreak::property::Property* createFromTiXmlElement( const TiXmlElement* xmlElement );

	static void initialiseFromTiXmlDocument( tecnofreak::property::Property* element, TiXmlDocument* xmlDocument );
	static void initialiseFromTiXmlElement( tecnofreak::property::Property* element, const TiXmlElement* xmlElement );
	static void initialiseFromTiXmlAttribute( tecnofreak::property::Property* element, const TiXmlAttribute* xmlAttribute );

};

}

}

}

#endif