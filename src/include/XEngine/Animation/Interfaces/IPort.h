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

#ifndef __TECNOFREAK__I_PORT__H__
#define __TECNOFREAK__I_PORT__H__

#include <string>

#include <XEAnimation/Common.h>
#include <XEAnimation/Interfaces/IAnimation.h>
#include <XEAnimation/AnimationNodeList.h>

namespace XE
{

class INode;

// Restriction: Ports are connected to nodes directly instead of other ports.
// This means that a node cannot have two outputs that opperate in a different way.
// All ports are of input type.

class TecnoFreakDllExport IPort
{
public:

		/**
		Obtain the node that is connected to this port.

		@return Node connected to this port. Null if it isn' connected.
		*/
	virtual INode* getConnectedNode() = 0;


		/**
		Obtain the node that is connected to this port.

		@return Node connected to this port. Null if it isn' connected.
		*/
	virtual const INode* getConnectedNode() const = 0;
	
		/**
			Connect the port to a node.

			@param connectedNode Node that this port has to be connected to.
		*/
	virtual void setConnectedNode( INode* connectedNode ) = 0;

		/**
		Check if this port is connected to another node.

		@return True if the port is connected to a node, false otherwise.
		*/
	virtual bool isConnected() const = 0;


		/**
		Get the node that this port pertains to.

		@return Node that this port pertains to.
		*/
	virtual INode* getParentNode() = 0;

		/**
		Get the node that this port pertains to.

		@return Node that this port pertains to.
		*/
	virtual const INode* getParentNode() const = 0;


		/**
		Get the id of the port within the parent node.

		@return Id of the port.
		*/
	virtual int getId() const = 0;

		/**
		Get the name of the port.

		@return Name of the port.
		*/
	virtual const std::string& getName() const = 0;


		/**
		Obtains the animations of the blend branch hanging from this port.

		Applies the desired weight to the node connected to this port and calls its evaluated
		function to obtain the reached animation nodes through that path.

		@param weight Weight to apply to the connected node before evaluating the node.
		@param mask Skeleton mask to apply to the connected node before evaluating the node.
		@param[out] reachedAnimations List containing the animation nodes reached when 
			traversing down the node tree connected to this port.
		*/
	virtual void evaluateAnimations( const float weight, const BoneWeightList* mask, AnimationNodeList& reachedAnimationNodes ) = 0;

		/**
		Obtain the animation nodes connected to the current port.

		@param[out] reachedAnimationNodes List containing the animation nodes reached when 
			traversing down the node tree connected to this port.
		*/
	virtual void getAnimations( AnimationNodeList& reachedAnimationNodes ) = 0;

		/**
		Obtains the value associated with the connected node as a float value.

		@return Value associated to the node connected to this port.
		If no node is connected it will return the default value obtained by getDefaultValue.
		*/
	virtual float evaluateValue() = 0;


		/**
		Sets the default value of the port.

		@param defaultValue Default value of the port.
		*/
	virtual void setDefaultValue( const float defaultValue ) = 0;

		/**
		Obtain the default value of the port.

		@return Default value of the port.
		*/
	virtual float getDefaultValue() const = 0;

	virtual ~IPort() {}
};

}

#endif