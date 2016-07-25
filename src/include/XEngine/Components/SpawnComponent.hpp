#pragma once

#include <XESystem/SystemConfig.hpp>

namespace XFBType
{
	enum SpawnType;
}

namespace XE
{
	struct SpawnComponent {
		
	public:

		SpawnComponent();

		Uint16 spawnPointId;
		Uint8  group; //e.g. player group
		XFBType::SpawnType type;
	};
}