#include <XENetwork/NetworkManager.hpp>
#include <XENetwork/NetObserver.hpp>
#include <XEngine/Components/NetId.hpp>
#include <XEScripts/LUAEngine.h>

namespace XE 
{
	NetworkManager::NetworkManager()
		: mReadLoopThread()// Exlicitly using the default constructor to underline the fact that it does get called 
		, m_Running(false)
		, m_isClient(true)
		, peer(nullptr)
		, host(nullptr)
		, _increment(0)
	{
	}

	NetworkManager::~NetworkManager()
	{
		m_Running = false;
		if (mReadLoopThread.joinable()) mReadLoopThread.join();
	}


	void NetworkManager::registerObject(sol::state& lua)
	{
		lua.new_usertype<NetworkManager>("NetworkManager",

			//properties
			//"graphicsMgr", sol::property(&XEngine::getGraphicsManager),

			//functions
			"startLoop", &NetworkManager::startLoop
			);

		auto stateView = lua.set("NetworkManager", this); //set object instance
	}

	void NetworkManager::startLoop(bool isClient)
	{
		m_isClient = isClient;

		if (enet_initialize() != 0)
		{
			fprintf(stderr, "An error occurred while initializing ENet.\n");
		}
		atexit(enet_deinitialize);

		printf("Initialized.\n");


		/* Bind the server to the default localhost.     */
		/* A specific host address can be specified by   */
		/* enet_address_set_host (& address, "x.x.x.x"); */

		address.port = 1234;

		if (!m_isClient)
		{
			//----------------------- Server -----------------------
			printf("I am server...\n");
			fflush(stdout);

			/* Bind the server to the default localhost.     */
			/* A specific host address can be specified by   */
			/* enet_address_set_host (& address, "x.x.x.x"); */

			address.host = ENET_HOST_ANY; 
			//enet_address_set_host(&address, "127.0.0.1");
			
			host = enet_host_create(&address, // the address to bind the server host to 
				50,   // allow only 1 client and/or outgoing connections
				2,      /* allow up to 2 channels to be used, 0 and 1 */
				0,   // assume any amount of incoming bandwidth
				0);  // assume any amount of outgoing bandwidth


			if (!host) {
				fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
				exit(EXIT_FAILURE);
			}
			printf("Host Created at %s.\n", address.host);
			//----------------------- Server end -----------------------
		}
		else
		{
			//----------------------- Client -------------------------------
			printf("I am client...\n");
			fflush(stdout);

			host = enet_host_create(0, // create a client host
				1, // allow only 1 outgoing connection
				2, /* allow up 2 channels to be used, 0 and 1 */
				0, // use 57600 / 8 for 56K modem with 56 Kbps downstream bandwidth
				0);// use 14400 / 8 for 56K modem with 14 Kbps upstream bandwidth

			if (!host) {
				fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
				exit(EXIT_FAILURE);
			}

			// Connect to some.server.net:1234. 
			enet_address_set_host(&address, ENET_HOST_ANY);// "localhost");
			peer = enet_host_connect(host, &address, 2, 0);
			peer->data = 0; // use this as mark that connection is not yet acknowledged
			if (!peer) {
				fprintf(stderr, "No available peers for initiating an ENet connection.\n");
				exit(EXIT_FAILURE);
			}

			/* Wait up to 5 seconds for the connection attempt to succeed. */
			if (enet_host_service(host, &event, 100) > 0 &&
				event.type == ENET_EVENT_TYPE_CONNECT)
			{
				//puts("Connection to some.server.net:1234 succeeded.");
				fprintf(stderr, "Connection to some.server.net:1234 succeeded.");
			/*...
					...
					...*/
			}
			else
			{
				/* Either the 5 seconds are up or a disconnect event was */
				/* received. Reset the peer in the event the 5 seconds   */
				/* had run out without any significant event.            */
				enet_peer_reset(peer);
				//puts("Connection to some.server.net:1234 failed.");
				fprintf(stderr, "Connection to some.server.net:1234 failed.");
			}
			//----------------------- Client end -------------------------------
		}

		if (!m_Running)
		{
			m_Running = true;
			mReadLoopThread = std::thread(&NetworkManager::ReadLoopThread, this); // This will start the thread. Notice move semantics! https://rafalcieslak.wordpress.com/2014/05/16/c11-stdthreads-managed-by-a-designated-class/
		}
	}

	void NetworkManager::stopLoop()
	{
		m_Running = false; //leak? test if calling start again
	}


	void NetworkManager::SendPacketToPeer(int Channel, const void * data, size_t dataLength)//, char pack[11])
	{
		/* Create a reliable packet of size 7 containing "packet\0" */
		ENetPacket * packet = enet_packet_create(data,	dataLength , ENET_PACKET_FLAG_RELIABLE);

		/* Send the packet to the peer over channel id 0. */
		/* One could also broadcast the packet by         */
		/* enet_host_broadcast (host, 0, packet);         */
		enet_peer_send(peer, Channel, packet);
		/* One could just use enet_host_service() instead. */
		enet_host_flush(host);

	}

	void NetworkManager::ReadLoopThread()
	{
		while (isRunning())
		{
			// processing incoming events:
			while (enet_host_service(host, &event, 10) > 0) {
				
				bool autodeleteBuffer = true;

				printf("Checking Incoming");
				switch (event.type) {
				case ENET_EVENT_TYPE_CONNECT: {

					printf("A new client connected from %x:%u. peerid: %u\n",
						event.peer->address.host,
						event.peer->address.port,
						event.peer->incomingPeerID);
					fflush(stdout);

				//	m_peers[event.peer->incomingPeerID] = event.peer;

					char buf[64];
					sprintf(buf, "%u:%u", event.peer->address.host, event.peer->address.port);
					int buflen = strlen(buf);
					event.peer->data = malloc(buflen + 1);
					strncpy((char*)event.peer->data, buf, buflen);
					peer = event.peer;

					break;
				}
				case ENET_EVENT_TYPE_RECEIVE:

					printf("A packet of length %u containing %s was received from %s on channel %u. peerid: %u\n",
						event.packet->dataLength,
						event.packet->data,
						event.peer->data,
						event.channelID,
						event.peer->incomingPeerID);

					fflush(stdout);

					NWMessage msg;
					msg.data = event.packet->data; //evtl. flatbuffer data
					msg.len = event.packet->dataLength;
					msg.peer = event.peer;// ->incomingPeerID;

					autodeleteBuffer = receivedMessage(msg);

					//enet_packet_destroy(event.packet); // clean up the packet now that we're done using it
					if (event.packet != NULL)
					{
						if (event.packet->freeCallback != NULL)
							(*event.packet->freeCallback) (event.packet);

						if (autodeleteBuffer)
						{
							if (!(event.packet->flags & ENET_PACKET_FLAG_NO_ALLOCATE) &&
								event.packet->data != NULL)
								enet_free(event.packet->data);
						}

						enet_free(event.packet);
					}
					
					//SendPacket(0, "Data Received");
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					printf("  host disconnected.\n");
					fflush(stdout);
					free(event.peer->data);

					// 5. Publisher broadcasts
					for (int i = 0; i < views.size(); i++)
						views[i]->disconnected(event.peer);

				//	m_peers.erase(event.peer->incomingPeerID);

					event.peer->data = 0; // reset the peer's client information.
					peer = 0;


				default:
					break;
				}
			}

		}

		
	}


	bool NetworkManager::receivedMessage(NWMessage& msg) {

		//todo convert enet to message


		//flatbuffer pointer
	//	char* tmp; // received data
		bool autoDeleteBuffer = true;

		// 5. Publisher broadcasts
		for (int i = 0; i < views.size(); i++)
		{
			bool tmp = views[i]->receivedMessage(msg);
			autoDeleteBuffer = autoDeleteBuffer ? tmp : true;
		}

		//delete msg.data; //done with enet_packet_destroy(event.packet); !!!
//		delete tmp; // delete pointer after all observers handled that message!
		return autoDeleteBuffer;
	}

	sf::Uint32 NetworkManager::newNetID()
	{
		return _increment++;
	}

	//entityx::Entity NetworkManager::getEntity(sf::Uint16 netId)
	//{
	//	return m_entities[netId];
	//}

	//uint16_t NetworkManager::addEntity(entityx::Entity entity)
	//{
	//	_increment++;
	//	entityx::ComponentHandle<NetIdComponent> netId = entity.assign<NetIdComponent>(_increment);
	//	netId->Id = _increment;
	//	m_entities[_increment] = entity;
	//	
	//	return _increment;
	//}

	//void NetworkManager::removeEntity(entityx::Entity entity)
	//{
	//	auto netId = entity.component<NetIdComponent>();
	//	m_peers.erase(netId->Id());
	//	entity.remove<NetIdComponent>();
	//}

	void NetworkManager::attach(NetObserver *obs) {
		views.push_back(obs);
	}

	void NetworkManager::sendMessage(ENetPeer* peer, const void * data, size_t dataLength, _ENetPacketFlag flag){
		
	//	if (m_peers.size() <= 0)// || netComponent.peerID == 0)
	//		return;
		if (!peer)
			return;
		//const char* pack = "nodes mit size und orientation";
		
		/* Create a reliable packet of size 7 containing "packet\0" */
		//ENetPacket * packet = enet_packet_create(pack,
		//	strlen(pack) + 1,
		//	ENET_PACKET_FLAG_RELIABLE);
		ENetPacket * packet = enet_packet_create(data, dataLength, flag); //ENET_PACKET_FLAG_RELIABLE);

		/* Send the packet to the peer over channel id 0. */
		/* One could also broadcast the packet by         */
		/* enet_host_broadcast (host, 0, packet);         */
	//##	enet_peer_send(m_peers[0], 0, packet);


	// Pick channel for sending and broadcast to all peers
	//--->>todo 	enet_host_broadcast(host, 0, packet);

		enet_peer_send(peer, 0, packet);

		/* One could just use enet_host_service() instead. */
		enet_host_flush(host);
	}
}