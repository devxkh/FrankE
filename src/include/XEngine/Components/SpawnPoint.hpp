#ifndef __SPAWNPOINTCOMPONENT_HPP__
#define __SPAWNPOINTCOMPONENT_HPP__

#include <XESystem/SystemConfig.hpp>

namespace XE
{
	struct SpawnPointComponent {
		SpawnPointComponent() 
			: m_group(0)
			 , id(0)
		{
		}

		XE::Uint8  m_group; //e.g. player group
		XE::Uint8 id;
	};

}

#endif //__SPAWNPOINTCOMPONENT_HPP__