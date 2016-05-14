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

#include <XEngine/Animation/Nodes/MathAbsNode.h>
#include <XEngine/Animation/Port.h>
#include <cmath>

using namespace XE;

MathAbsNode::MathAbsNode()
: Node()
, m_inPort( NULL )
{
	m_inPort = createPort(2);//"in" );
}

MathAbsNode::~MathAbsNode()
{
}

Port* MathAbsNode::getInPort()
{
	return m_inPort;
}

const Port* MathAbsNode::getInPort() const
{
	return m_inPort;
}

float MathAbsNode::evaluateValue(double deltaTime)
{
	float inPortValue = getInPort()->evaluateValue(deltaTime);
	return std::abs( inPortValue );
}