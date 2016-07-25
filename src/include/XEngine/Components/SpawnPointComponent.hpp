#pragma once

#include <XESystem/SystemConfig.hpp>

namespace XE
{
	struct SpawnPointComponent {
		SpawnPointComponent();

		Uint8 group; //e.g. player group
		Uint16 id;
	};
}