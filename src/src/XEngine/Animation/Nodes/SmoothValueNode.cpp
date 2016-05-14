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

#include <XEngine/Animation/Nodes/SmoothValueNode.h>
#include <XEngine/Animation/Helper/SmoothValue.h>
#include <XEDAL/Objects/FBEngineTypes_generated.h>
#include <XEngine/Animation/Port.h>

using namespace XE;

SmoothValueNode::SmoothValueNode()
: m_desiredValuePort( NULL )
, m_smoothTimePort( NULL )
, m_currentValue( 0 )
, m_velocity( 0 )
{
	m_desiredValuePort = createPort(9); // "value" );
	m_smoothTimePort = createPort(10); // "smooth_time" );
}

SmoothValueNode::~SmoothValueNode()
{

}

float SmoothValueNode::evaluateValue(double deltaTime)
{
	float desiredValue = getDesiredValue(deltaTime);
	float smoothTime = getSmoothTime(deltaTime);

	m_currentValue = helper::smoothValue( m_currentValue, desiredValue, m_velocity, smoothTime, deltaTime);

	return m_currentValue;
}

Port* SmoothValueNode::getDesiredValuePort()
{
	return m_desiredValuePort;
}

const Port* SmoothValueNode::getDesiredValuePort() const
{
	return m_desiredValuePort;
}

Port* SmoothValueNode::getSmoothTimePort()
{
	return m_smoothTimePort;
}
const Port* SmoothValueNode::getSmoothTimePort() const
{
	return m_smoothTimePort;
}

float SmoothValueNode::getDesiredValue(double deltaTime) const
{
	return m_desiredValuePort->evaluateValue(deltaTime);
}

float SmoothValueNode::getCurrentValue() const
{
	return m_currentValue;
}

float SmoothValueNode::getSmoothTime(double deltaTime) const
{
	return m_smoothTimePort->evaluateValue(deltaTime);
}

void SmoothValueNode::init( const void* nodeData)
{
	auto smoothValueNode = (const XFBType::SmoothValueNode*)nodeData;

	m_currentValue = smoothValueNode->initial_value();
}

