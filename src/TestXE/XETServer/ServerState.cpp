#include "ServerState.hpp"


ServerState::ServerState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)
{
	LOG(XE::info) << "InitState - Initialization";

	//--------------------------------------------------------
	//------------------ Server -------------------------------
	m_engine.getNetworkManager().startLoop(false);

	LOG(XE::info) << "InitState - Initialized";
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

