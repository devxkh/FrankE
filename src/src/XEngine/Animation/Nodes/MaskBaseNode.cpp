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

#include <XEngine/Animation/Nodes/MaskBaseNode.h>

using namespace XE;

MaskBaseNode::MaskBaseNode()
{
	m_animationInPort = createPort(2); //"in" );
}

MaskBaseNode::~MaskBaseNode()
{

}


void MaskBaseNode::init( const void* nodeData )
{
	/*if ( description == NULL )
	{
		return;
	}
	
	const tecnofreak::property::Property* bonesProperty = description->getChild( "bones" );
	if ( bonesProperty == NULL )
	{
		return;
	}

	const int numBones = bonesProperty->getChildCount();

	m_skelMask.clear();
	m_skelMask.resize( numBones, 0.0f );
	for ( int i = 0 ; i < numBones ; ++i )
	{
		const Property* boneProperty = bonesProperty->getChild( i );
		const float boneWeight = ( boneProperty != NULL ) ? boneProperty->getValueAsFloat() : 1.0f;
		m_skelMask[ i ] = boneWeight;
	}	*/
}
