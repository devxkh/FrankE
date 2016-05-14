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

#include <XEngine/Animation/Nodes/MathClampNode.h>
#include <XEngine/Animation/Helper/Clamp.h>
#include <XEngine/Animation/Port.h>

using namespace XE;

MathClampNode::MathClampNode()
: Node()
, m_minValuePort( NULL )
, m_maxValuePort( NULL )
, m_valuePort( NULL )
{
	m_minValuePort = createPort(17); // "min" );
	m_maxValuePort = createPort(18); //"max" );
	m_valuePort = createPort(19); // "value" );
}

MathClampNode::~MathClampNode()
{
}

Port* MathClampNode::getMinValuePort()
{
	return m_minValuePort;
}

const Port* MathClampNode::getMinValuePort() const
{
	return m_minValuePort;
}

Port* MathClampNode::getMaxValuePort()
{
	return m_maxValuePort;
}

const Port* MathClampNode::getMaxValuePort() const
{
	return m_maxValuePort;
}

Port* MathClampNode::getValuePort()
{
	return m_valuePort;
}

const Port* MathClampNode::getValuePort() const
{
	return m_valuePort;
}

float MathClampNode::evaluateValue(double deltaTime)
{
	float minValue = getMinValuePort()->evaluateValue(deltaTime);
	float maxValue = getMaxValuePort()->evaluateValue(deltaTime);
	float value = getValuePort()->evaluateValue(deltaTime);
	
	return helper::clamp( value, minValue, maxValue );
}