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

#include <XERenderer/Animation.h>

#include <cassert>

#include <Ogre/OgreMain/include/Animation/OgreSkeletonAnimation.h>
#include <Ogre/OgreMain/include/Animation/OgreSkeletonAnimationDef.h>
#include <Ogre/OgreMain/include/Animation/OgreSkeletonInstance.h>

#include <XERenderer/GraphicsManager.hpp>

namespace XE
{
	typedef std::vector< float > BoneWeightList;

	Animation::Animation(XE::GraphicsManager& gMgr, const XE::Uint16 id)
		: m_GraphicsManager(gMgr)
		, m_boneWeightList(nullptr)
		, m_t_boneWeightPtrs(nullptr)
		, m_weight(1)
		, m_speed(1)
		, m_Enabled(false)
		, _id(id)
		, m_Length(0)
		, m_Loop(false)
		, m_TimePos(0)
		, m_addTime(0)
		, _t_animation(0)
		, _hasRenderAnimation(false)
	{

	}

	Animation::~Animation()
	{
	}

	void Animation::updateRenderer()
	{
		float t_addTime = m_addTime;
		float t_timePos = m_TimePos;

		m_addTime = 0;

		if (!_hasRenderAnimation)
			return;

		m_GraphicsManager.getIntoRendererQueue().push([this, t_addTime, t_timePos]() {
			_t_animation->setTime(t_timePos);
			_t_animation->addTime(t_addTime);
		});
	}

	const XE::Uint16 Animation::getId() const
	{
		return _id;
	}

	bool Animation::getEnabled() const
	{
		return m_Enabled;
	}

	void Animation::setEnabled(const bool enabled)
	{
		if (!_hasRenderAnimation)
			return;

		if (m_Enabled != enabled)
		{
			m_Enabled = enabled;

			m_GraphicsManager.getIntoRendererQueue().push([this, enabled](){			
				_t_animation->setEnabled(enabled);			
			});
		}
	}

	float Animation::getWeight() const
	{
		return m_weight;
	}

	void Animation::setWeight(const float weight)
	{
		if (!_hasRenderAnimation)
			return;

		if (m_weight != weight)
		{
			m_weight = weight;

			m_GraphicsManager.getIntoRendererQueue().push([this, weight](){			
				_t_animation->mWeight= weight;
			});
		}

		// Enable or disable animation based on weight.
		bool validWeight = (0.0001 < weight);
		setEnabled(validWeight);
	}

	const BoneWeightList* Animation::getMask() const
	{
		return m_boneWeightList; // reinterpret_cast<const BoneWeightList*>(getAnimationState()->getBlendMask());
	}

	void Animation::setMask(const BoneWeightList* mask)
	{
		if (!m_boneWeightList) //still not set in from renderable
			return;

		//m_t_boneWeightPtrs is set in HandleAnimation from Renderable in the Renderthread
		auto refMaskList = *m_boneWeightList; //Create a reference

		if (mask == NULL)
		{
			for (int i = 0; i < refMaskList.size(); i++)
				refMaskList[i] = 1.0;
		}
		else
		{
			for (int i = 0; i < refMaskList.size(); i++)
				refMaskList[i] = mask->at(i);
		}

		if (!_hasRenderAnimation)
			return;

		m_GraphicsManager.getIntoRendererQueue().push([this, mask]() {
			
			//TODO threading problem with pointers!??
			//m_t_boneWeightPtrs is set in HandleAnimation from Renderable in the Renderthread
			//auto refMask = *m_t_boneWeightPtrs; //Create a reference

			//if (mask == NULL) //not thread safe!
			//{

			//	for (int i = 0; i < m_t_boneWeightPtrs->size(); i++)
			//	{
			//		if ((*m_t_boneWeightPtrs)[i] != NULL)
			//			*(*m_t_boneWeightPtrs)[i] = 1.0;
			//	}
			//}
			//else
			//{
			//	for (int i = 0; i < refMask.size(); i++)

			//		if (refMask[i] != NULL)
			//			*refMask[i] = mask->at(i);
			//}
		});
	}

	float Animation::getLength() const
	{
		return m_Length;
	}

	bool Animation::getLoop() const
	{
		return  m_Loop;
	}

	void Animation::setLoop(const bool loop)
	{
		if (m_Loop != loop)
		{
			m_Loop = loop;

			if (!_hasRenderAnimation)
				return;

			m_GraphicsManager.getIntoRendererQueue().push([this, loop](){
				_t_animation->setLoop(loop);
			});
		}
	}

	float Animation::getSpeed() const
	{
		return m_speed;
	}

	void Animation::setSpeed(const float speed)
	{
		m_speed = speed;
	}

	void Animation::reset()
	{
		if (!_hasRenderAnimation)
			return;

		m_GraphicsManager.getIntoRendererQueue().push([this](){
			_t_animation->setTime(0);
		});

		setTimePosition(0);
	}

	void Animation::addTime(const float animationUpdateSeconds)
	{
		m_addTime += animationUpdateSeconds;
	}

	float Animation::getRelativeTimePosition() const
	{
		return (getTimePosition() / getLength());
	}

	void Animation::setRelativeTimePosition(const float relativeTimePosition)
	{
		setTimePosition(relativeTimePosition * getLength());
	}

	float Animation::getTimePosition() const
	{
		return m_TimePos;
	}

	void Animation::setTimePosition(const float timePosition)
	{
		// Triggers are just called when the animation is updated.
		m_TimePos = timePosition;
	}

	void  Animation::setLength(float length)
	{
		m_Length = length;
	}

} // ns XE
