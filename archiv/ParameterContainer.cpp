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

#include <XEngine/Animation/ParameterContainer.h>
#include <XEngine/Animation/Parameter.h>

#include <sstream>
#include <cassert>

#include <XEngine/Animation/Property/Property.h>

using namespace tecnofreak;
using namespace tecnofreak::property;

const int ParameterContainer::INVALID_PARAMETER_ID( -1 );

ParameterContainer::ParameterContainer()
{
}

ParameterContainer::~ParameterContainer()
{
	clearParameters();
}

void ParameterContainer::clearParameters()
{
	for ( unsigned int i = 0; i < m_parameters.size(); i++ )
	{
		delete m_parameters[ i ];
	}
	m_parameters.clear();
}

int ParameterContainer::addParameter( IParameter* parameter )
{
	assert( parameter );
	if ( parameter == NULL )
	{
		// TODO: throw exception instead
		return INVALID_PARAMETER_ID;
	}

	bool parameterExists = hasParameter( parameter->getName() );
	assert( ! parameterExists );
	if ( parameterExists )
	{
		return INVALID_PARAMETER_ID;
	}


	int parameterId = int( m_parameters.size() );
	m_parameters.push_back( parameter );
	m_parameterNames[ parameter->getName() ] = parameterId;

	return parameterId;
}

IParameter* ParameterContainer::getParameter( const int parameterId )
{
	if ( ! validParameterId( parameterId ) )
	{
		return NULL;
	}

	return m_parameters[ parameterId ];
}

const IParameter* ParameterContainer::getParameter( const int parameterId ) const
{
	if ( ! validParameterId( parameterId ) )
	{
		return NULL;
	}

	return m_parameters[ parameterId ];
}

int ParameterContainer::getParameterId( const std::string& parameterName ) const
{
	std::map< std::string, int >::const_iterator cit = m_parameterNames.find( parameterName );
	bool hasParameter = ( cit != m_parameterNames.end() );

	if ( ! hasParameter )
	{
		return INVALID_PARAMETER_ID;
	}

	int parameterId = cit->second;
	return parameterId;
}

bool ParameterContainer::validParameterId( const int parameterId ) const
{
	return ( 0 <= parameterId && parameterId < int( m_parameters.size() ) );
}

bool ParameterContainer::hasParameter( const std::string& parameterName ) const
{
	int parameterId = getParameterId( parameterName );
	return validParameterId( parameterId );
}

IParameter* ParameterContainer::getParameter( const std::string& parameterName )
{
	int parameterId = getParameterId( parameterName );
	return getParameter( parameterId );
}

const IParameter* ParameterContainer::getParameter( const std::string& parameterName ) const
{
	int parameterId = getParameterId( parameterName );
	return getParameter( parameterId );
}

void ParameterContainer::initialise( const tecnofreak::property::Property* rootElement )
{
	clearParameters();

	loadContainer( rootElement );
}

void ParameterContainer::loadContainer( const Property* rootElement )
{
	if ( rootElement == NULL )
	{
		throw std::runtime_error( "Could not get root element" );
	}

	const Property* parametersElement = rootElement->getChild( "parameters" );
	loadParameters( parametersElement );
}

void ParameterContainer::loadParameters( const Property* parametersElement )
{
	if ( parametersElement == NULL )
	{
		throw std::runtime_error( "Could not get parameters element" );
	}

	for ( int i = 0; i < parametersElement->getChildCount(); i++ )
	{
		const Property* parameterElement = parametersElement->getChild( i );
		loadParameter( parameterElement );
	}
}

void ParameterContainer::loadParameter( const Property* parameterElement )
{
	assert( parameterElement );

	if ( ! parameterElement->hasChild( "name" ) )
	{
		throw std::runtime_error( "Parameter without name attribute" );
	}

	if ( ! parameterElement->hasChild( "value" ) )
	{
		throw std::runtime_error( "Parameter without value attribute" );
	}

	std::string name = parameterElement->getChild( "name" )->getValue();

	if ( hasParameter( name ) )
	{
		std::stringstream message;
		message << "Parameter name '" << name << "' not unique";
		throw std::runtime_error( message.str().c_str() );
	}

	Parameter* parameter = new Parameter( name );
	addParameter( parameter );

	float value = parameterElement->getChild( "value" )->getValueAsFloat();
	parameter->setValue( value );

}