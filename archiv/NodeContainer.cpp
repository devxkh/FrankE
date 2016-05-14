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

#include <XEngine/Animation/NodeContainer.h>

#include <algorithm>
#include <cassert>
#include <sstream>

#include <XEngine/Animation/NodeFactory.h>
#include <XEngine/Animation/SharedData.h>

#include <XEngine/Animation/Property/Property.h>

using namespace tecnofreak;
using namespace tecnofreak::property;

const int NodeContainer::INVALID_NODE_ID( -1 );

NodeContainer::NodeContainer()
: m_outputNode( NULL )
, m_sharedData( NULL )
{
	m_sharedData = new SharedData();

	createOutputNode();
}

NodeContainer::~NodeContainer()
{
	clearNodes();

	delete m_sharedData;
}

void NodeContainer::createOutputNode()
{
	m_outputNode = new OutputNode();
	addNode( m_outputNode );
}

void NodeContainer::clearNodes()
{
	for ( unsigned int i = 0; i < m_nodes.size(); i++ )
	{
		delete m_nodes[ i ];
	}
	m_nodes.clear();
}

int NodeContainer::addNode( INode* node )
{
	assert( node );

	std::vector< INode* >::iterator it = std::find( m_nodes.begin(), m_nodes.end(), node );
	bool nodeAlreadyAdded = ( it != m_nodes.end() );

	assert( ! nodeAlreadyAdded );
	if ( nodeAlreadyAdded )
	{
		return INVALID_NODE_ID;
	}

	node->setSharedData( getSharedData() );

	int nodeId = int( m_nodes.size() );
	m_nodes.push_back( node );

	return nodeId;
}

INode* NodeContainer::getNode( const int nodeId )
{
	if ( ! hasNode( nodeId ) )
	{
		return NULL;
	}

	return m_nodes[ nodeId ];
}

const INode* NodeContainer::getNode( const int nodeId ) const
{
	if ( ! hasNode( nodeId ) )
	{
		return NULL;
	}

	return m_nodes[ nodeId ];
}

bool NodeContainer::hasNode( const int nodeId ) const
{
	return ( 0 <= nodeId && nodeId < getNodeCount() );
}

int NodeContainer::getNodeCount() const
{
	return int( m_nodes.size() );
}

OutputNode* NodeContainer::getOutputNode()
{
	return m_outputNode;
}

const OutputNode* NodeContainer::getOutputNode() const
{
	return m_outputNode;
}

void NodeContainer::initialise( const Property* rootElement )
{
	clearNodes();
	createOutputNode();

	loadContainer( rootElement );
}

void NodeContainer::loadContainer( const Property* rootElement )
{
	if ( rootElement == NULL )
	{
		throw std::runtime_error( "Could not get root element" );
	}

	try
	{
		std::map< int, int > idAssociations;

		const Property* nodesElement = rootElement->getChild( "nodes" );
		loadNodes( nodesElement, idAssociations );

		const Property* connectionsElement = rootElement->getChild( "connections" );
		loadConnections( connectionsElement, idAssociations );

		const Property* outputElement = rootElement->getChild( "output" );
		loadOutputConnection( outputElement, idAssociations );

		const Property* constantsElement = rootElement->getChild( "constants" );
		loadConstants( constantsElement, idAssociations );
	}
	catch ( std::runtime_error e )
	{
		throw e;
	}
}

void NodeContainer::loadNodes( const Property* nodesElement, std::map< int, int >& idAssociations )
{
	if ( nodesElement == NULL )
	{
		throw std::runtime_error( "Could not get nodes element" );
	}

	for ( int i = 0; i < nodesElement->getChildCount(); i++ )
	{
		const Property* nodeElement = nodesElement->getChild( i );
		loadNode( nodeElement, idAssociations );
	}
}

void NodeContainer::loadNode( const Property* nodeElement, std::map< int, int >& idAssociations )
{
	assert( nodeElement );

	if ( ! nodeElement->hasChild( "type" ) )
	{
		throw std::runtime_error( "Node without type attribute" );
	}

	if ( ! nodeElement->hasChild( "id" ) )
	{
		throw std::runtime_error( "Node without id attribute" );
	}

	std::string nodeType = nodeElement->getChild( "type" )->getValue();

	int nodeIdInFile = nodeElement->getChild( "id" )->getValueAsInteger();

	INode* node = NodeFactory::getSingleton().createNode( nodeType );
	if ( node == NULL )
	{
		std::stringstream message;
		message << "Could not create node of type " << nodeType << " with id " << nodeIdInFile;
		throw std::runtime_error( message.str().c_str() );
	}

	const Property* customData = nodeElement->getChild( "custom" );
	node->init( customData );

	int nodeIdInContainer = addNode( node );
	idAssociations[ nodeIdInFile ] = nodeIdInContainer;

}

void NodeContainer::loadConnections( const Property* connectionsElement, std::map< int, int >& idAssociations )
{
	if ( connectionsElement == NULL )
	{
		throw std::runtime_error( "Could not get connections element" );
	}

	for ( int i = 0; i < connectionsElement->getChildCount(); i++ )
	{
		const Property* connectionElement = connectionsElement->getChild( i );
		loadConnection( connectionElement, idAssociations );
	}
}

void NodeContainer::loadOutputConnection( const Property* outputElement, std::map< int, int >& idAssociations )
{
	if ( outputElement == NULL )
	{
		// not necessary an invalid system... although quite pointless.
		return;
	}

	int nodeConnectedToOutputIdInFile = outputElement->getValueAsInteger();
	int nodeConnectedToOutputIdInContainer = idAssociations[ nodeConnectedToOutputIdInFile ];
	INode* nodeConnectedToOutputNode = getNode( nodeConnectedToOutputIdInContainer );
	getOutputNode()->getAnimationInPort()->setConnectedNode( nodeConnectedToOutputNode );
}

void NodeContainer::loadConnection( const Property* connectionElement, std::map< int, int >& idAssociations )
{
	assert( connectionElement );

	if ( ! connectionElement->hasChild( "node_in" ) )
	{
		throw std::runtime_error( "Connection without node_in attribute" );
	}

	if ( ! connectionElement->hasChild( "port_in" ) )
	{
		throw std::runtime_error( "Connection without port_in attribute" );
	}

	if ( ! connectionElement->hasChild( "node_out" ) )
	{
		throw std::runtime_error( "Connection without node_out attribute" );
	}



	int nodeInId = connectionElement->getChild( "node_in" )->getValueAsInteger();

	std::string portIn = connectionElement->getChild( "port_in" )->getValue();

	int nodeOutId = connectionElement->getChild( "node_out" )->getValueAsInteger();

	bool nodeInDefined = ( idAssociations.find( nodeInId ) != idAssociations.end() );
	bool nodeOutDefined = ( idAssociations.find( nodeOutId ) != idAssociations.end() );

	INode* nodeIn = getNode( idAssociations[ nodeInId ] );
	INode* nodeOut = getNode( idAssociations[ nodeOutId ] );

	if ( ! nodeInDefined || nodeIn == NULL )
	{
		std::stringstream message;
		message << "Connection with invalid node_in " << nodeInId;
		throw std::runtime_error( message.str().c_str() );
	}

	if ( ! nodeOutDefined || nodeOut == NULL )
	{
		std::stringstream message;
		message << "Connection with invalid node_out " << nodeOutId;
		throw std::runtime_error( message.str().c_str() );
	}


	IPort* port = nodeIn->getPort( portIn );
	if ( port == NULL )
	{
		std::stringstream message;
		message << "Connection with invalid port " << portIn << " for node " << nodeInId;
		throw std::runtime_error( message.str().c_str() );
	}

	port->setConnectedNode( nodeOut );
}

void NodeContainer::loadConstants( const Property* constantsElement, std::map< int, int >& idAssociations )
{
	if ( constantsElement == NULL )
	{
		throw std::runtime_error( "Could not get constants element" );
	}


	for ( int i = 0; i < constantsElement->getChildCount(); i++ )
	{
		const Property* constantElement = constantsElement->getChild( i );
		loadConstant( constantElement, idAssociations );
	}
}

void NodeContainer::loadConstant( const Property* constantElement, std::map< int, int >& idAssociations )
{
	assert( constantElement );

	if ( ! constantElement->hasChild( "node_id" ) )
	{
		throw std::runtime_error( "Constant without node_id attribute" );
	}

	if ( ! constantElement->hasChild( "port" ) )
	{
		throw std::runtime_error( "Constant without port attribute" );
	}

	if ( ! constantElement->hasChild( "value" ) )
	{
		throw std::runtime_error( "Constant without value attribute" );
	}

	int nodeId = constantElement->getChild( "node_id" )->getValueAsInteger();

	std::string portName = constantElement->getChild( "port" )->getValue();

	float value = constantElement->getChild( "value" )->getValueAsFloat();

	bool nodeDefined = ( idAssociations.find( nodeId ) != idAssociations.end() );

	INode* node = getNode( idAssociations[ nodeId ] );

	if ( ! nodeDefined || node == NULL )
	{
		std::stringstream message;
		message << "Constant with invalid node_id " << nodeId;
		throw std::runtime_error( message.str().c_str() );
	}



	bool validPort = node->hasPort( portName );
	if ( ! validPort )
	{
		std::stringstream message;
		message << "Constant with invalid port " << portName << " for node " << nodeId;
		throw std::runtime_error( message.str().c_str() );
	}

	IPort* port = node->getPort( portName );

	port->setDefaultValue( value );
}

SharedData* NodeContainer::getSharedData()
{
	return m_sharedData;
}

const SharedData* NodeContainer::getSharedData() const
{
	return m_sharedData;
}
