#include <XENetwork/NetObserver.hpp>

#include <XENetwork/NetworkManager.hpp>

namespace XE
{
	NetObserver::NetObserver(NetworkManager& mod) {
		model = &mod;

		model->attach(this);// 4. Observers register themselves 
	}

	NetworkManager& NetObserver::getNetworkManager() {
		return *model;
	}


	void NetObserver::addListener(std::unique_ptr<NetObserverListener> obs) {
		_listenerVector.push_back(std::move(obs));
	}

	void NetObserver::removeListener(std::unique_ptr<NetObserverListener> obs) {
		//todo _listenerVector.remove(std::move(obs));
	}

}