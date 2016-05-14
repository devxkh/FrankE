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

#include <XEngine/Animation/Nodes/MathMapNode.h>
#include <XEngine/Animation/Helper/Clamp.h>
#include <XEngine/Animation/Port.h>

#include <cmath>

using namespace XE;

MathMapNode::MathMapNode()
: Node()
, m_minValueInPort( NULL )
, m_maxValueInPort( NULL )
, m_minValueOutPort( NULL )
, m_maxValueOutPort( NULL )
, m_valueInPort( NULL )
{
	m_minValueInPort = createPort(20); // "min_in" );
	m_maxValueInPort = createPort(21); // "max_in" );
	m_minValueOutPort = createPort(22); // "min_out" );
	m_maxValueOutPort = createPort(23); // "max_out" );
	m_valueInPort = createPort(9);// "value" );
}

MathMapNode::~MathMapNode()
{
}

Port* MathMapNode::getMinValueInPort()
{
	return m_minValueInPort;
}

const Port* MathMapNode::getMinValueInPort() const
{
	return m_minValueInPort;
}

Port* MathMapNode::getMaxValueInPort()
{
	return m_maxValueInPort;
}

const Port* MathMapNode::getMaxValueInPort() const
{
	return m_maxValueInPort;
}

Port* MathMapNode::getMinValueOutPort()
{
	return m_minValueOutPort;
}

const Port* MathMapNode::getMinValueOutPort() const
{
	return m_minValueOutPort;
}

Port* MathMapNode::getMaxValueOutPort()
{
	return m_maxValueOutPort;
}

const Port* MathMapNode::getMaxValueOutPort() const
{
	return m_maxValueOutPort;
}

Port* MathMapNode::getValueInPort()
{
	return m_valueInPort;
}

const Port* MathMapNode::getValueInPort() const
{
	return m_valueInPort;
}

float MathMapNode::evaluateValue(double deltaTime)
{
	float minValueIn = getMinValueInPort()->evaluateValue(deltaTime);
	float maxValueIn = getMaxValueInPort()->evaluateValue(deltaTime);
	float inRange = std::abs( maxValueIn - minValueIn );

	if ( inRange == 0 )
	{
		return 0;
	}

	float minValueOut = getMinValueOutPort()->evaluateValue(deltaTime);
	float maxValueOut = getMaxValueOutPort()->evaluateValue(deltaTime);
	float outRange = std::abs( maxValueOut - minValueOut );

	float valueIn = getValueInPort()->evaluateValue(deltaTime);
	valueIn = helper::clamp( valueIn, minValueIn, maxValueIn );

	
	float normalizedValueIn = ( ( valueIn - minValueIn ) / inRange );
	float valueOut = minValueOut + ( normalizedValueIn * outRange );

	return valueOut;
}