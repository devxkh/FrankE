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
			, peer(0)
			, peerId(0)
		{

		}

		NetIdComponent(Uint16 id)
			: id(id)
			, peer(0)
			, peerId(0)
		{

		}

		/// unique network objectid
		Uint16 id;

		///enet peerID
		ENetPeer* peer;
		
		Uint16 peerId;

		Uint8 sceneId;

		///entityID 
		Uint32 entityID;

	};

}

#endif //__NETIDCOMPONENT_HPP__