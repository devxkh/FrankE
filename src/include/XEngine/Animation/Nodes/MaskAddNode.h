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

#ifndef __TECNOFREAK__MASK_ADD_NODE__H__
#define __TECNOFREAK__MASK_ADD_NODE__H__

#include <XEngine/Animation/Nodes/MaskBaseNode.h>


namespace XE
{

class MaskAddNode
	: public MaskBaseNode
{
public:
	MaskAddNode();
	virtual ~MaskAddNode();

	virtual void evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask );

	virtual void init( const void* fbData );

private:
	BoneWeightList m_skelMaskBranch;
};

}


#endif
