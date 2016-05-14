
#ifndef __XE__NETWORKMANAGER_HPP
#define __XE__NETWORKMANAGER_HPP

#include <sfml/System/NonCopyable.hpp>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <strstream>

#include <XESystem/Entityx/Entity.h>

#pragma comment(lib, "Ws2_32.lib") //needed for enet?? http://stackoverflow.com/questions/1153900/unresolved-external-symbol

#include <enet/enet.h>

namespace sol { class state; }

namespace XE
{
	class NetObserver;
	class XEngine;
	struct NetIdComponent;

	const unsigned ENetChannels = 3; // 0 = Sequenced, 1 = Reliable, 2 = Unsequenced

	typedef enet_uint16 peer_id_t;

	enum PacketFlags {
		PACKET_SEQUENCED = 0,
		PACKET_RELIABLE = 1,
		PACKET_UNSEQUENCED = 2
	};

	/**
	* @brief Contains error codes that tell the reason of disconnecting.
	*/
	enum ErrorCodes
	{
		WRONG_PASSWORD = 1,
		INCOMPATIBLE_GAME_PROTOCOL,
		INCOMPATIBLE_MASTER_PROTOCOL
	};

	struct ClientData
	{
		bool isEditor;
		entityx::Entity entity;
	};

	typedef int8_t ClientID;

	/// Convert integer IPv4 address to dot-notation
	/*inline std::string IPv4(uint32_t i) {
		std::stringstream oss;
		oss << (i & 0xFF) << "." << ((i >> 8) & 0xFF) << "." << ((i >> 16) & 0xFF) << "." << ((i >> 24) & 0xFF);
		return oss.str();
	}*/

	/// Internet address struct
	struct Address {
		uint32_t host; ///< IPv4 address
		uint16_t port; ///< Port number
		Address(uint32_t initHost = 0, uint16_t initPort = 0) : host(initHost), port(initPort) { }
		//std::string str() const { return IPv4(host) + ":" + boost::lexical_cast<std::string>(port); }
		bool operator==(const Address& other) { return host == other.host && port == other.port; }
		bool operator!=(const Address& other) { return !(*this == other); }
		operator bool() { return port > 0; }
	};

	struct NWMessage
	{
		//length of the message
		int len;
		//message data
		void* data;

		//enet event peerId
		uint16_t peerID;
	};

	struct PeerInfo {
		ClientID id; ///< ID number, used with car state updates
		uint16_t peer_id; ///< ID associated by ENet
		int32_t random_id; ///< random number used to determine id
		Address address; ///< Address
		
		std::string name; ///< Nickname
		std::string car; ///< Car
		std::string password; ///< Password for connecting
		
		short peers; ///< Amount of peers connected
		bool ready; ///< Ready state
		bool loaded; ///< Can start race?
		unsigned ping; ///< Average packet round-trip time
		bool authenticated; ///< Handshaking completed?
		enum ConnectionState { DISCONNECTED = 0, CONNECTING = 1, CONNECTED = 2 } connection; ///< Connection state

		PeerInfo(Address addr = Address()) :
			id(-1), random_id(-1), peer_id(0), address(addr), name(), car(), peers(), ready(),
			loaded(), ping(0), authenticated(), connection(DISCONNECTED) {}

	};


	//typedef std::map<std::string, PeerInfo> PeerMap;
	typedef std::map<enet_uint16, ENetPeer*> PeerMap;

//	typedef std::map<uint16_t, entityx::Entity> NetEntityMap; //list of all network related objects

	/*
	// Starts a thread reading network messages
	*/
	class NetworkManager : public sf::NonCopyable
	{
	public:

		NetworkManager();
		~NetworkManager();


		void attach(NetObserver *obs);

		void sendMessage(NetIdComponent& netComponent, const void * data, size_t dataLength, _ENetPacketFlag flag = ENET_PACKET_FLAG_RELIABLE);


		void registerObject(sol::state& lua);

		void startLoop(bool isClient);
		void stopLoop();

		void ReadLoopThread();

		bool isRunning() { return m_Running; }

		void SendPacketToPeer(int Channel, const void * data, size_t dataLength);

		sf::Uint32 newNetID();

		///only a server can execute that function
		static void asServerAddNetId(NetworkManager& nwMgr, entityx::Entity entity)
		{
			if (nwMgr.isClient())
				return;

			//XE::NetIdComponent* netIDNew = entity.assign<XE::NetIdComponent>().get();
			////	netIDNew->peerID = message.peerID;
			//netIDNew->id = nwMgr.newNetID();
		}
		
		//uint16_t addEntity(entityx::Entity entity);
		//entityx::Entity getEntity(sf::Uint16 netId);

		//void removeEntity(entityx::Entity entity);

		bool isClient() { return m_isClient; }

		sf::Uint32 NetIDPool() { return _increment; }

	private:

		bool receivedMessage(NWMessage& event);
		

		bool m_Running;
		bool m_isClient;

		ENetEvent event;
		ENetHost * host = 0;
		ENetPeer * peer = 0;
		ENetAddress address;

		PeerMap m_peers;

		//NetEntityMap m_entities;

		std::mutex			mReadLoopMutex;// protects mControllerThread

		std::thread			mReadLoopThread;

		std::vector < class NetObserver * > views; // 3. Coupled only to "interface"

		sf::Uint32 _increment;
	};


	//TEST
	//class DivObserver : public NetObserver {
	//public:
	//	DivObserver(NetworkManager *mod) : NetObserver(mod){}
	//	
	//	void receivedMessage(int val) {
	//		// 6. "Pull" information of interest
	//		//int v = getSubject()->getVal(), d = getDivisor();
	//		//std::cout << v << " div " << d << " is " << v / d << '\n';
	//	}

	//};

//https://sourcemaking.com/design_patterns/observer/cpp/3
	//NetworkManager subj;
	//DivObserver divObs1(&subj, 4); // 7. Client configures the number and
	//DivObserver divObs2(&subj, 3); //    type of Observers
	//ModObserver modObs3(&subj, 3);
	//subj.setVal(14);


} // ns XE

#endif // __XE__NETWORKMANAGER_HPP