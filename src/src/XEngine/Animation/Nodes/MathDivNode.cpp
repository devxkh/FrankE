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

#include <XEngine/Animation/Nodes/MathDivNode.h>
#include <XEngine/Animation/Port.h>
#include <cassert>

using namespace XE;

MathDivNode::MathDivNode()
: Node()
, m_dividendPort( NULL )
, m_divisorPort( NULL )
{
	m_dividendPort = createPort( 6);//"in0" );
	m_divisorPort = createPort(7);//"in1" );
}

MathDivNode::~MathDivNode()
{
}

Port* MathDivNode::getDividendPort()
{
	return m_dividendPort;
}

const Port* MathDivNode::getDividendPort() const
{
	return m_dividendPort;
}

Port* MathDivNode::getDivisorPort()
{
	return m_divisorPort;
}

const Port* MathDivNode::getDivisorPort() const
{
	return m_divisorPort;
}

float MathDivNode::evaluateValue(double deltaTime)
{
	float dividend = getDividendPort()->evaluateValue(deltaTime);
	float divisor = getDivisorPort()->evaluateValue(deltaTime);

	assert( divisor != 0 );
	if ( divisor == 0 )
	{
		// Should probably throw an exception here...
		return 0;
	}

	float quotient = dividend / divisor;
	return quotient;
}

