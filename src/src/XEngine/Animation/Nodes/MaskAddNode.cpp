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

#include <XEngine/Animation/Nodes/MaskAddNode.h>
#include <XEngine/Animation/Port.h>

#include <cassert>


using namespace XE;

MaskAddNode::MaskAddNode()
{
}

MaskAddNode::~MaskAddNode()
{
}

void MaskAddNode::evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask )
{
	if ( mask == NULL )
	{
		// If there's no previous mask applied, we'll set the mask for the node as current.
		// The more coherent and alternative, but perhaps less useful behaviour, would be
		// assume a value of 1 for each joint previous to the addition.
		m_animationInPort->evaluateAnimations(deltaTime, getWeight(), &m_skelMask, reachedAnimationNodes );
	}
	else
	{
		assert( m_skelMask.size() == mask->size() );

		for ( unsigned int i = 0; i < m_skelMask.size(); i++ )
		{
			m_skelMaskBranch[ i ] = m_skelMask[ i ] + ( *mask )[ i ];
		}
		m_animationInPort->evaluateAnimations(deltaTime, getWeight(), &m_skelMaskBranch, reachedAnimationNodes );
	}
}

void MaskAddNode::init( const void* fbData )
{
	MaskBaseNode::init(fbData);

	m_skelMaskBranch.resize( m_skelMask.size() );
}