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

#ifndef __TECNOFREAK__PARAMETER__H__
#define __TECNOFREAK__PARAMETER__H__

#include "IParameter.h"

#include <string>


/*
TODO:
Change to multiple type of parameters, with a parameter factory:
eg. string parameter, bool parameter, float parameter.
common interface to create from / convert to most types implemented in subclass.
node evaluate value should be modified to take this into account, by expecting an element
of this type instead of a float ( or passing a parameter to be modified?
*/
namespace XE
{

class Parameter
	: public IParameter
{
public:
	Parameter( const std::string& name );
	virtual ~Parameter();

	virtual const std::string& getName() const;

	virtual float getFloatValue() const;
	virtual void setValue( const float value );

private:
	std::string m_name;
	float m_value;
};

}

#endif