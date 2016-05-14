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

#ifndef __TECNOFREAK__ANIMATION_NODE__H__
#define __TECNOFREAK__ANIMATION_NODE__H__

#include <XEngine/Animation/Node.h>
#include <XEngine/Animation/Port.h>
//#include <XEngine/Animation/IAnimation.h>
#include <string>

namespace XE
{
	class AnimationNode;
	class HandleAnimation;
	typedef std::list< AnimationNode* > AnimationNodeList;

class AnimationNode : public Node
{
public:

	static const int INVALID_ANIMATION_ID;

	AnimationNode();
	virtual ~AnimationNode();

	virtual void evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask );
	virtual void getAnimations( AnimationNodeList& reachedAnimationNodes );

	int getAnimationId() const;

	HandleAnimation* getAnimation();
	const HandleAnimation* getAnimation() const;
	void setAnimation(HandleAnimation* animation );

	bool hasValidAnimation() const;

	float evaluateAnimationSpeed(double deltaTime);

	Port* getSpeedPort();
	const Port* getSpeedPort() const;

	Port* getSynchPort();
	const Port* getSynchPort() const;

	virtual void init(const void* nodeData);

	const BoneWeightList* getMask() const;
	void setMask( const BoneWeightList* mask );
private:
	int m_animationId;

	Port* m_speedPort;
	Port* m_synchPort;

	HandleAnimation* m_animation;

	const BoneWeightList* m_mask;
};

}

#endif
