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

#include <XEngine/Animation/NodeFactory.h>
#include <XEngine/Animation/NodeInstanceCreator.h>
#include <cassert>

#include <XEngine/Animation/Nodes/OutputNode.h>
#include <XEngine/Animation/Nodes/AnimationNode.h>
#include <XEngine/Animation/Nodes/BlendNode.h>
#include <XEngine/Animation/Nodes/ParameterNode.h>
#include <XEngine/Animation/Nodes/MixNode.h>
#include <XEngine/Animation/Nodes/AverageNode.h>

#include <XEngine/Animation/Nodes/TransitionSelectNode.h>
#include <XEngine/Animation/Nodes/RandomSelectNode.h>

#include <XEngine/Animation/Nodes/MathAbsNode.h>
#include <XEngine/Animation/Nodes/MathCeilNode.h>
#include <XEngine/Animation/Nodes/MathClampNode.h>
#include <XEngine/Animation/Nodes/MathDivNode.h>
#include <XEngine/Animation/Nodes/MathMapNode.h>
#include <XEngine/Animation/Nodes/MathMaxNode.h>
#include <XEngine/Animation/Nodes/MathMinNode.h>
#include <XEngine/Animation/Nodes/MathMinusNode.h>
#include <XEngine/Animation/Nodes/MathMulNode.h>
#include <XEngine/Animation/Nodes/MathPlusNode.h>

#include <XEngine/Animation/Nodes/MaskMulNode.h>
#include <XEngine/Animation/Nodes/MaskAddNode.h>
#include <XEngine/Animation/Nodes/MaskSetNode.h>
#include <XEngine/Animation/Nodes/MaskSubNode.h>

#include <XEngine/Animation/Nodes/LookAtNode.h>

#include <XEngine/Animation/Nodes/SmoothValueNode.h>

using namespace tecnofreak;


NodeFactory::NodeFactory()
{
	registerFactoryMethod( "OutputNode", createNodeInstance< OutputNode > );
	registerFactoryMethod( "AnimationNode", createNodeInstance< AnimationNode > );
	registerFactoryMethod( "BlendNode", createNodeInstance< BlendNode > );
	registerFactoryMethod( "ParameterNode", createNodeInstance< ParameterNode > );
	registerFactoryMethod( "MixNode", createNodeInstance< MixNode > );
	registerFactoryMethod( "AverageNode", createNodeInstance< AverageNode > );

	registerFactoryMethod( "TransitionSelectNode", createNodeInstance< TransitionSelectNode > );
	registerFactoryMethod( "RandomSelectNode", createNodeInstance< RandomSelectNode > );
	
	registerFactoryMethod( "MathAbsNode", createNodeInstance< MathAbsNode > );
	registerFactoryMethod( "MathCeilNode", createNodeInstance< MathCeilNode > );
	registerFactoryMethod( "MathClampNode", createNodeInstance< MathClampNode > );
	registerFactoryMethod( "MathDivNode", createNodeInstance< MathDivNode > );
	registerFactoryMethod( "MathMapNode", createNodeInstance< MathMapNode > );
	registerFactoryMethod( "MathMaxNode", createNodeInstance< MathMaxNode > );
	registerFactoryMethod( "MathMinNode", createNodeInstance< MathMinNode > );
	registerFactoryMethod( "MathMinusNode", createNodeInstance< MathMinusNode > );
	registerFactoryMethod( "MathMulNode", createNodeInstance< MathMulNode > );
	registerFactoryMethod( "MathPlusNode", createNodeInstance< MathPlusNode > );

	registerFactoryMethod( "MaskMulNode", createNodeInstance< MaskMulNode > );
	registerFactoryMethod( "MaskAddNode", createNodeInstance< MaskAddNode > );
	registerFactoryMethod( "MaskSetNode", createNodeInstance< MaskSetNode > );
	registerFactoryMethod( "MaskSubNode", createNodeInstance< MaskSubNode > );

	registerFactoryMethod( "LookAtNode", createNodeInstance< LookAtNode > );

	registerFactoryMethod( "SmoothValueNode", createNodeInstance< SmoothValueNode > );
}

NodeFactory::NodeFactory( const NodeFactory& nodeFacotry )
{
}

NodeFactory::~NodeFactory()
{
}

NodeFactory& NodeFactory::getSingleton()
{
	static NodeFactory sInstance;
	return sInstance;
}

NodeFactory* NodeFactory::getSingletonPtr()
{
	return &( getSingleton() );
}

INode* NodeFactory::createNode( const std::string& type ) const
{
	NodeFactoryMethodDictionary::const_iterator cit = m_nodeFactoryMethod.find( type );
	bool hasFactoryMethodForType = ( cit != m_nodeFactoryMethod.end() );

	if ( ! hasFactoryMethodForType )
	{
		return NULL;
	}

	NodeFactoryMethodPointer factoryMethod = cit->second;
	INode* node = factoryMethod();
	
	return node;
}

void NodeFactory::registerFactoryMethod( const std::string& type, NodeFactoryMethodPointer factoryMethod )
{
	assert( factoryMethod != NULL );
	if ( factoryMethod == NULL )
	{
		return;
	}

	m_nodeFactoryMethod[ type ] = factoryMethod;
}