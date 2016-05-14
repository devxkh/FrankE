#ifndef __NETIDCOMPONENT_HPP__
#define __NETIDCOMPONENT_HPP__

#include <XESystem/SystemConfig.hpp>
#include <XESystem/TransportData.hpp>

namespace XE
{
	///net object
	struct NetIdComponent {

	public:
		NetIdComponent()
			: id (0)
			, peerID(0)
		{

		}

		NetIdComponent(sf::Uint16 id)
			: id(id)
			, peerID(0)
		{

		}

		/// unique network objectid
		sf::Uint16 id;

		///enet peerID
		sf::Uint16 peerID;

		sf::Uint8 sceneId;

		///entityID 
		XE::Uint32 entityID;

	};

}

#endif //__NETIDCOMPONENT_HPP__