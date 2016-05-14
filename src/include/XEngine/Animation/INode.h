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

#ifndef __TECNOFREAK__I_NODE__H__
#define __TECNOFREAK__I_NODE__H__

//#include <XEngine/Animation/Common.h>
//#include "IAnimation.h"
//#include "AnimationNodeList.h"
//#include "BoneWeightList.h"

#include <vector>
#include <list>

namespace XE
{

class Port;
class SharedData;
class AnimationNode;

	typedef std::vector< float > BoneWeightList;
	typedef std::list< AnimationNode* > AnimationNodeList;

class INode
{
public:
		/**
		Obtain the weight of this node.

		It should be a value between 0 and 1.

		@return Weight of this node.
		*/
	virtual float getWeight() const = 0;


		/**
		Set the weight of this node.

		It should be a value between 0 and 1.

		@param weight Weight to assign to the node.
		*/
	virtual void setWeight( const float weight ) = 0;


		/**
		Evaluate the current node.

		When overloading, suppose that the weight is already set for the current node.

		Do necessary operations and traverse children nodes through the animation ports to 
		obtain a list of reached animations.

		@param[out] reachedAnimationNodes List containing the animation nodes reached when 
			traversing down the nodes connected to this one.
		@param mask Bone weight mask to use for the animations in this branch. Can be NULL.
		*/
	virtual void evaluateAnimations( AnimationNodeList& reachedAnimationNodes, double deltaTime, const BoneWeightList* mask = nullptr) = 0;

		/**
		Obtain the animation nodes connected to the current node further down the animation
		tree.

		Child nodes may overload the behaviour of this function.

		@param[out] reachedAnimationNodes List containing the animation nodes reached when 
			traversing down the nodes connected to this one.
		*/
	virtual void getAnimations( AnimationNodeList& reachedAnimationNodes ) = 0;


		/**
		Obtains the value associated with this node as a float value.

		@return Value associated to this node.
		*/
	virtual float evaluateValue(double deltaTime) = 0;


		/**
		Get the elapsed seconds since the last tree traversal.

		@return Elapsed seconds since the last tree traversal.
		*/
	//virtual float getElapsedSeconds() const = 0;


		/**
		Check the number of ports.

		@return Number of ports.
		*/
	//virtual int getPortCount() const = 0;


		/**
		Check if the node has a port by its name.

		@param name Name of the port.
		@return True if it has a port with this name, false otherwise.
		*/
	virtual bool hasPort( const int id ) const = 0;


		/**
		Check if a port id is valid.

		@param id The id to be checked.
		@return True if the id is a valid id, false otherwise.
		*/
	virtual bool isValidPortId( const int id ) const = 0;


		/**
		Get a port by id.

		@param id The id of the port. It must be a valid id.
		@return Port with the desired id.
		*/
	virtual Port* getPort( const int id ) = 0;


		/**
		Get a port by id.

		@param id The id of the port. It must be a valid id.
		@return Port with the desired id.
		*/
	virtual const Port* getPort( const int id ) const = 0;

		/**
		Initialise a node from a generic property.

		@param description Generic property that should contain the data to initialise the node.
		*/
	virtual void init(const void* nodeData) = 0;


	virtual ~INode() {}
};

}

#endif
