#pragma once

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>

namespace Ogre
{/*
	struct QueuedRenderable;
	struct HlmsCache;*/
}

namespace XE
{

	class XEHlmsProjection : public Ogre::HlmsUnlit
	{
	public:
		XEHlmsProjection(Ogre::Archive *dataFolder, Ogre::ArchiveVec *libraryFolders,
			Ogre::HlmsTypes type, const Ogre::String &typeName);

		virtual Ogre::uint32 fillBuffersForV1(const Ogre::HlmsCache *cache,
			const Ogre::QueuedRenderable &queuedRenderable,
			bool casterPass, Ogre::uint32 lastCacheHash,
			Ogre::CommandBuffer *commandBuffer);

		virtual Ogre::uint32 fillBuffersForV2(const Ogre::HlmsCache *cache,
			const Ogre::QueuedRenderable &queuedRenderable,
			bool casterPass, Ogre::uint32 lastCacheHash,
			Ogre::CommandBuffer *commandBuffer);

		Ogre::uint32 XEfillBuffersFor(const Ogre::HlmsCache *cache, const Ogre::QueuedRenderable &queuedRenderable,
			bool casterPass, Ogre::uint32 lastCacheHash,
			Ogre::CommandBuffer *commandBuffer, bool isV1);
	};
}