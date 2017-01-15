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

#pragma once

#include <XESystem/SystemConfig.hpp>

#include <vector>

namespace Ogre
{
	/*namespace v1
	{*/
		//class AnimationState;
	class SkeletonAnimation;
	//}
}

namespace XE
{
	class GraphicsManager;

	typedef std::vector<float*>  BoneWeightPtrs;
	typedef std::vector< float > BoneWeightList;

class Animation
{
public:
	/*
		creates an Animation object: not in renderthread!
	*/
	Animation(XE::GraphicsManager& gMgr,const XE::Uint16 id);
	virtual ~Animation();

	virtual const XE::Uint16 getId() const;

	virtual bool getEnabled() const;
	virtual void setEnabled( const bool enabled );

	virtual float getWeight() const;
	virtual void setWeight( const float weight );

	virtual const BoneWeightList* getMask() const;
	virtual void setMask( const BoneWeightList* mask );

	virtual float getLength() const;

	virtual bool getLoop() const;
	virtual void setLoop( const bool loop );

	virtual float getSpeed() const;
	virtual void setSpeed( const float speed );

	virtual void reset();

	virtual void addTime(const float animationUpdateSeconds);

	virtual float getRelativeTimePosition() const;
	virtual void setRelativeTimePosition( const float relativeTimePosition );
	
	virtual float getTimePosition() const;
	virtual void setTimePosition( const float timePosition );

	void  setLength(float length);


	float m_addTime;

protected:

	void updateRenderer();
	//Ogre::v1::AnimationState* m_t_animationState;
	
	bool _hasRenderAnimation;
	//change only in renderthread!
	Ogre::SkeletonAnimation* _t_animation;
	BoneWeightPtrs* m_t_boneWeightPtrs;


	XE::GraphicsManager& m_GraphicsManager;

	BoneWeightList* m_boneWeightList;
	float m_TimePos;
private:


	//Ogre::AnimationState* _t_getAnimationState();
	//const Ogre::AnimationState* _t_getAnimationState() const;
	XE::Uint16 _id;
	bool m_Enabled;
	float m_Length;
	bool m_Loop;

	
	// weight must be stored because many references to a single animation state may exist.
	float m_weight;
	float m_speed;

};

} // XE