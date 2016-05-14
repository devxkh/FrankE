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

#ifndef __TECNOFREAK__PARAMETER_CONTAINER__H__
#define __TECNOFREAK__PARAMETER_CONTAINER__H__

#include "Common.h"
#include "IParameter.h"
#include <map>
#include <vector>
#include <string>

namespace tecnofreak
{

namespace property
{
	class Property;
}

class TecnoFreakDllPrivate ParameterContainer
{
public:
	static const int INVALID_PARAMETER_ID;

	ParameterContainer();
	virtual ~ParameterContainer();

	void clearParameters();

	// the parameter container will be responsible of deleting any parameter added to it.
	int addParameter( IParameter* parameter );
	
	IParameter* getParameter( const int parameterId );
	const IParameter* getParameter( const int parameterId ) const;

	int getParameterId( const std::string& parameterName ) const;
	bool validParameterId( const int parameterId ) const;
	bool hasParameter( const std::string& parameterName ) const;

	IParameter* getParameter( const std::string& parameterName );
	const IParameter* getParameter( const std::string& parameterName ) const;

	void initialise( const tecnofreak::property::Property* rootElement );

private:

	void loadContainer( const tecnofreak::property::Property* rootElement );

	void loadParameters( const tecnofreak::property::Property* parametersElement );
	void loadParameter( const tecnofreak::property::Property* parameterElement );

private:

	std::vector< IParameter* > m_parameters;
	std::map< std::string, int > m_parameterNames;
};

}

#endif