
#ifndef __XENETOBSERVER_HPP__
#define __XENETOBSERVER_HPP__

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <XENetwork/NetObserver.hpp>

namespace XE
{
	class NetworkManager;
	class XEngine;

	class XENetObserver : public NetObserver
	{
	public:
		XENetObserver(NetworkManager& mod, XEngine& engine);
			
			
		bool receivedMessage(const NWMessage& message);

	private:
		XEngine& m_Engine;

	};	
} // ns XE

#endif  // __XENETOBSERVER_HPP__
