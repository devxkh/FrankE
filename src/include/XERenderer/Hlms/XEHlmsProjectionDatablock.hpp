#pragma once

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>

namespace XE
{
	class XEHlmsProjection;

	class XEHlmsProjectionDatablock : public Ogre::HlmsUnlitDatablock
	{
		friend class XEHlmsProjection;

	};


}