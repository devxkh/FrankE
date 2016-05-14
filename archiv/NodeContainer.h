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

#ifndef __TECNOFREAK__NODE_CONTAINER__H__
#define __TECNOFREAK__NODE_CONTAINER__H__

#include "Common.h"
#include "INode.h"

#include "Nodes/OutputNode.h"

namespace tecnofreak
{

namespace property
{
	class Property;
}

class SharedData;

class TecnoFreakDllPrivate NodeContainer
{
public:

	static const int INVALID_NODE_ID;

	NodeContainer();
	virtual ~NodeContainer();

	// the node container will be responsible of deleting any node added to it.
	int addNode( INode* node );
	INode* getNode( const int nodeId );
	const INode* getNode( const int nodeId ) const;
	bool hasNode( const int nodeId ) const;
	int getNodeCount() const;

	OutputNode* getOutputNode();
	const OutputNode* getOutputNode() const;

	void initialise( const tecnofreak::property::Property* rootElement );

	SharedData* getSharedData();
	const SharedData* getSharedData() const;

private:

	void clearNodes();
	void createOutputNode();

	void loadContainer( const tecnofreak::property::Property* rootElement );

	void loadNodes( const tecnofreak::property::Property* nodesElement, std::map< int, int >& idAssociations );
	void loadNode( const tecnofreak::property::Property* nodeElement, std::map< int, int >& idAssociations );
	
	void loadConnections( const tecnofreak::property::Property* connectionsElement, std::map< int, int >& idAssociations );
	void loadConnection( const tecnofreak::property::Property* connectionElement, std::map< int, int >& idAssociations );

	void loadOutputConnection( const tecnofreak::property::Property* outputElement, std::map< int, int >& idAssociations );

	void loadConstants( const tecnofreak::property::Property* constantsElement, std::map< int, int >& idAssociations );
	void loadConstant( const tecnofreak::property::Property* constantElement, std::map< int, int >& idAssociations );
private:
	std::vector< INode* > m_nodes;

	OutputNode* m_outputNode;

	SharedData* m_sharedData;
};

}

#endif
