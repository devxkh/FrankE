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

#include <XEngine/Animation/Property/Xml/PropertyBuilder.h>
#include <XEngine/Animation/XML/tinyxml/tinyxml.h>

using namespace tecnofreak::property;
using namespace tecnofreak::property::xml;


Property* PropertyBuilder::createFromData( const std::string& data )
{
	TiXmlDocument xmlDocument;

	const char* status = xmlDocument.Parse( data.c_str() );
	if ( xmlDocument.Error() )
	{
		// TODO: store error message.
		return NULL;
	}
	
	return createFromTiXmlDocument( &xmlDocument );
}

Property* PropertyBuilder::createFromFile( const std::string& filename )
{
	TiXmlDocument xmlDocument( filename );

	bool loadFileSuccess = xmlDocument.LoadFile();
	if ( ! loadFileSuccess )
	{
		// TODO: store error message.
		return NULL;
	}

	return createFromTiXmlDocument( &xmlDocument );
}

Property* PropertyBuilder::createFromTiXmlDocument( TiXmlDocument* xmlDocument )
{
	return createFromTiXmlElement( xmlDocument->FirstChildElement() );
}

Property* PropertyBuilder::createFromTiXmlElement( const TiXmlElement* xmlElement )
{
	std::string elementName = ( xmlElement->Value() == NULL ) ? "" : xmlElement->Value();

	Property* element = new Property();
	initialiseFromTiXmlElement( element, xmlElement );

	return element;
}


void PropertyBuilder::initialiseFromData( tecnofreak::property::Property* element, const std::string& data )
{
	TiXmlDocument xmlDocument;

	const char* status = xmlDocument.Parse( data.c_str() );
	if ( xmlDocument.Error() )
	{
		// TODO: store error message.
		return;
	}

	initialiseFromTiXmlDocument( element, &xmlDocument );
}


void PropertyBuilder::initialiseFromFile( tecnofreak::property::Property* element, const std::string& filename )
{
	TiXmlDocument xmlDocument( filename );

	bool loadFileSuccess = xmlDocument.LoadFile();

	if ( ! loadFileSuccess )
	{
		// TODO: store error message.
		return;
	}

	initialiseFromTiXmlDocument( element, &xmlDocument );
}


void PropertyBuilder::initialiseFromTiXmlDocument( tecnofreak::property::Property* element, TiXmlDocument* xmlDocument )
{
	initialiseFromTiXmlElement( element, xmlDocument->FirstChildElement() );
}

void PropertyBuilder::initialiseFromTiXmlElement( Property* element, const TiXmlElement* xmlElement )
{
	element->setValue( ( xmlElement->GetText() == NULL ) ? "" : xmlElement->GetText() );
	for ( const TiXmlElement* childXmlElement = xmlElement->FirstChildElement(); childXmlElement != NULL; childXmlElement = childXmlElement->NextSiblingElement() )
	{
		std::string childElementName = ( childXmlElement->Value() == NULL ) ? "" : childXmlElement->Value();
		Property* childElement = element->createChild( childElementName );

		initialiseFromTiXmlElement( childElement, childXmlElement );
	}

	for ( const TiXmlAttribute* childXmlAttribute = xmlElement->FirstAttribute(); childXmlAttribute != NULL; childXmlAttribute = childXmlAttribute->Next() )
	{
		std::string childAttributeName = ( childXmlAttribute->Name() == NULL ) ? "" : childXmlAttribute->Name();
		Property* childElement = element->createChild( childAttributeName );

		initialiseFromTiXmlAttribute( childElement, childXmlAttribute );
	}
}

void PropertyBuilder::initialiseFromTiXmlAttribute( Property* element, const TiXmlAttribute* xmlAttribute )
{
	element->setValue( ( xmlAttribute->Value() == NULL ) ? "" : xmlAttribute->Value() );
}