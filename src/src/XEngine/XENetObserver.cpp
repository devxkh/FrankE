#include <XEngine/XENetObserver.hpp>

#include <XEngine.hpp>

namespace XE
{
	
	XENetObserver::XENetObserver(NetworkManager& mod, XEngine& engine) 
		: NetObserver(mod)
		, m_Engine(engine)
	{

	}

	bool XENetObserver::receivedMessage(const NWMessage& message)
	{
		return true; //autodeleteBuffer = true
	}


	//	
	//void XENetObserver::receivedMessage(const NWMessage& message) {
	//	//		// 6. "Pull" information of interest
	//	//		//int v = getSubject()->getVal(), d = getDivisor();
	//	//		//std::cout << v << " div " << d << " is " << v / d << '\n';
	//	entityx::Entity::Id eid;
	//	auto entity = m_Engine.getScene(0).getEntities().get(eid);
	//	
	//	Uint16 action = XFBType::NetAction::NetAction_Update;

	//	switch (action)
	//	{
	//	case  XFBType::NetAction::NetAction_Create: //create


	//		break;

	//	case  XFBType::NetAction::NetAction_Update: //update
	//		break;
	//	case  XFBType::NetAction::NetAction_Delete: //delete

	//		break;

	//		
	//	default:
	//		break;
	//	}
	//}
}