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

//#include <XEngine/Animation/Common.h>
#include <XEngine/Animation/INode.h>
//#include <XEngine/Animation/SharedData.h>

#include <XEDAL/Objects/FBEngineTypes_generated.h>

#include <vector>
#include <map>

namespace XE
{


class Node : public INode
{
public:

	static const int INVALID_PORT_ID;

	Node();
	virtual ~Node();

	virtual float getWeight() const;
	virtual void setWeight( const float weight );

	virtual void evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask = nullptr );

	virtual void getAnimations( AnimationNodeList& reachedAnimationNodes );

	virtual float evaluateValue(double deltaTime);

	//virtual float getElapsedSeconds() const;

	//virtual int getPortCount() const;

	virtual bool hasPort( const int id ) const;
	virtual bool isValidPortId( const int id ) const;
	virtual Port* getPort( const int id );
	virtual const Port* getPort( const int id ) const;

	virtual void init(const void* nodeData);
	
	int getNodeId() const;
	void setNodeId(const int id);

//protected:
	Port* createPort( const int id);

	XFBType::UAnimationNode _type;

private:
	float m_weight;
	int _nodeId;

	typedef std::vector< Port* > PortVector;
	PortVector m_ports;
};

}
