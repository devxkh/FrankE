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

#ifndef __TECNOFREAK__LOOK_AT_NODE__H__
#define __TECNOFREAK__LOOK_AT_NODE__H__

#include <XEngine/Animation/Node.h>

namespace XE
{
class Port;

class LookAtNode
	: public Node
{
public:
	typedef enum 
	{
		LOOK_AT_LEFT,
		LOOK_AT_RIGHT,
		LOOK_AT_UP,
		LOOK_AT_DOWN
	} LookAtAnimationDirection;

	LookAtNode();
	virtual ~LookAtNode();

	virtual void evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask );

	Port* getAnimationPort( const LookAtAnimationDirection animationDirection );
	const Port* getAnimationPort( const LookAtAnimationDirection animationDirection) const;

	Port* getHorizontalDirectionAmountPort();
	const Port* getHorizontalDirectionAmountPort() const;

	Port* getVerticalDirectionAmountPort();
	const Port* getVerticalDirectionAmountPort() const;

protected:
	void evaluateDirectionalAnimations( Port* amountPort, Port* firstAnimation, Port* secondAnimation, AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask );

private:
	Port* m_horizontalDirectionAmountPort;
	Port* m_verticalDirectionAmountPort;

	Port* m_animationPort[ 4 ];
};
}

#endif