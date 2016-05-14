#include "ServerState.hpp"

#include <memory>
#include <iostream>

ServerState::ServerState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)
{
	XE::LogManager::getSingleton().logMessage("InitState - Initialization");

	//--------------------------------------------------------
	//------------------ Server -------------------------------
	//--------------------------------------------------------
//	m_engine->getServer().start();

	//XE::Controller* controller = m_engine->getCtrlMgr().getController(0);

//	m_engine->getScene().create(1); //test

	//std::unique_ptr<XE::CharEntity>  charTest(new XE::CharEntity(1, m_engine->getGraphicsManager(), m_engine->getScene()));
	/*charTest->create(1);

	Server->setCharEntity(*charTest.get());
	Server->getCameraServer().setTarget(*charTest.get());
	Server->getCameraServer().setStyle(XE::Cam_Type::CA_CHARACTER);

	charTest->setPosition(Ogre::Vector3(0,0,0));
	m_engine->getScene().addGameEntity(std::move(charTest));*/

//	controller->createConsole();

	m_engine.getNetworkManager().startLoop(false);

	// create the builtin resource group
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(GK_BUILTIN_GROUP);

	XE::LogManager::getSingleton().logMessage("InitState - Initialized");
}

ServerState::~ServerState()
{


}


void ServerState::update(float deltaTime)
{
	
}

void ServerState::cleanup()
{
	
}

