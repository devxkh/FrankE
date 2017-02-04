#ifndef _XEHlmsUnlit_H_
#define _XEHlmsUnlit_H_

#include <XESystem/SystemConfig.hpp>
#include <Ogre/OgreMain/include/OgreMatrix4.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitPrerequisites.h>
#include "OgreHlmsBufferManager.h"
#include "OgreConstBufferPool.h"
#include "OgreHeaderPrefix.h"

namespace Ogre
{
	class CompositorShadowNode;
	struct QueuedRenderable;

	/** \addtogroup Component
	*  @{
	*/
	/** \addtogroup Material
	*  @{
	*/

	class XEHlmsUnlitDatablock;

	/** Implementation without lighting or skeletal animation specfically designed for
	OpenGL 3+, D3D11 and other RenderSystems which support uniform buffers.
	Useful for GUI, ParticleFXs, other misc objects that don't require lighting.
	*/
	class _OgreHlmsUnlitExport XEHlmsUnlit : public HlmsBufferManager, public ConstBufferPool
	{
	protected:
		typedef vector<HlmsDatablock*>::type HlmsDatablockVec;

		struct PassData
		{
			Matrix4 viewProjMatrix[2];
		};

		PassData                mPreparedPass;
		ConstBufferPackedVec    mPassBuffers;
		uint32                  mCurrentPassBuffer;     /// Resets every to zero every new frame.

		ConstBufferPool::BufferPool const *mLastBoundPool;

		uint32 mLastTextureHash;



		virtual const HlmsCache* createShaderCacheEntry(uint32 renderableHash,
			const HlmsCache &passCache,
			uint32 finalHash,
			const QueuedRenderable &queuedRenderable);

		virtual HlmsDatablock* createDatablockImpl(IdString datablockName,
			const HlmsMacroblock *macroblock,
			const HlmsBlendblock *blendblock,
			const HlmsParamVec &paramVec);

		void setTextureProperty(IdString propertyName, XEHlmsUnlitDatablock *datablock,
			uint8 texType);

		virtual void calculateHashForPreCreate(Renderable *renderable, PiecesMap *inOutPieces);
		virtual void calculateHashForPreCaster(Renderable *renderable, PiecesMap *inOutPieces);

		virtual void destroyAllBuffers(void);

		FORCEINLINE uint32 fillBuffersFor(const HlmsCache *cache,
			const QueuedRenderable &queuedRenderable,
			bool casterPass, uint32 lastCacheHash,
			CommandBuffer *commandBuffer, bool isV1);

	public:
		XEHlmsUnlit(Archive *dataFolder, ArchiveVec *libraryFolders);
		XEHlmsUnlit(Archive *dataFolder, ArchiveVec *libraryFolders,
			HlmsTypes type, const String &typeName);
		virtual ~XEHlmsUnlit();

		virtual void _changeRenderSystem(RenderSystem *newRs);

		/// Not supported
		virtual void setOptimizationStrategy(OptimizationStrategy optimizationStrategy) {}

		virtual HlmsCache preparePassHash(const Ogre::CompositorShadowNode *shadowNode,
			bool casterPass, bool dualParaboloid,
			SceneManager *sceneManager);

		virtual uint32 fillBuffersFor(const HlmsCache *cache, const QueuedRenderable &queuedRenderable,
			bool casterPass, uint32 lastCacheHash,
			uint32 lastTextureHash);

		virtual uint32 fillBuffersForV1(const HlmsCache *cache,
			const QueuedRenderable &queuedRenderable,
			bool casterPass, uint32 lastCacheHash,
			CommandBuffer *commandBuffer);

		virtual uint32 fillBuffersForV2(const HlmsCache *cache,
			const QueuedRenderable &queuedRenderable,
			bool casterPass, uint32 lastCacheHash,
			CommandBuffer *commandBuffer);

		virtual void frameEnded(void);
#if !OGRE_NO_JSON
		/// @copydoc Hlms::_loadJson
		virtual void _loadJson(const rapidjson::Value &jsonValue, const HlmsJson::NamedBlocks &blocks,
			HlmsDatablock *datablock) const;
		/// @copydoc Hlms::_saveJson
		virtual void _saveJson(const HlmsDatablock *datablock, String &outString) const;

		/// @copydoc Hlms::_collectSamplerblocks
		virtual void _collectSamplerblocks(set<const HlmsSamplerblock*>::type &outSamplerblocks,
			const HlmsDatablock *datablock) const;
#endif
	};



	/** @} */
	/** @} */

}

#include "OgreHeaderSuffix.h"

#endif