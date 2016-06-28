#ifndef __NETIDCOMPONENT_HPP__
#define __NETIDCOMPONENT_HPP__

#include <XESystem/SystemConfig.hpp>
#include <XESystem/TransportData.hpp>

struct _ENetPeer;
typedef _ENetPeer ENetPeer;

namespace XE
{
	///net object
	struct NetIdComponent {

	public:
		NetIdComponent()
			: id (0)
		{

		}

		NetIdComponent(Uint16 id)
			: id(id)
		{

		}

		/// unique network objectid
		Uint16 id;

		Uint8 sceneId;

		///entityID 
		Uint32 entityID;

	};

	struct NetPeerComponent {

	public:
		NetPeerComponent()
			: peerId(0)
		{

		}

		NetPeerComponent(Uint16 peerId)
			: peer(0)
			, peerId(peerId)
		{

		}
		///enet peerID
		ENetPeer* peer;

		Uint16 peerId;
	};

}

#endif //__NETIDCOMPONENT_HPP__