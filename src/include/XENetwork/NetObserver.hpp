
#ifndef __NETOBSERVER_HPP__
#define __NETOBSERVER_HPP__

#include <XESystem/SystemConfig.hpp>
#include <XESystem/Entityx/entityx.h>
#include <memory>

struct _ENetPeer;
typedef _ENetPeer ENetPeer;

namespace XE
{
	class NetObserverListener;
	class NetworkManager;
	struct NWMessage;
	
	class NetObserver
	{

	public:
		NetObserver(NetworkManager& mod);

		virtual bool receivedMessage(NWMessage& message) = 0;
		virtual void disconnected(ENetPeer* peer) = 0;

		void addListener(std::unique_ptr<NetObserverListener> obs);
		void removeListener(std::unique_ptr<NetObserverListener> obs);


	protected:

		NetworkManager& getNetworkManager();

		std::vector<std::unique_ptr<NetObserverListener>> _listenerVector;

	private:
		


		NetworkManager* model;
	};

	class NetObserverListener
	{
	public:
		virtual void handleData(const XE::NWMessage& message, entityx::Entity entity) = 0;
	};

} // ns XE

#endif // __NETOBSERVER_HPP__