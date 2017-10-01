#include <XERenderer/Hlms/XEHlmsProjection.hpp>

#include "OgreStableHeaders.h"

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>
//#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>
#include <XERenderer/Hlms/XEHlmsProjectionDatablock.hpp>
#include "OgreHlmsListener.h"

#if !OGRE_NO_JSON
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsJsonUnlit.h>
#endif

#include "OgreViewport.h"
#include "OgreRenderTarget.h"
#include "OgreCamera.h"
#include "OgreHighLevelGpuProgramManager.h"
#include "OgreHighLevelGpuProgram.h"

#include "OgreSceneManager.h"
#include "Compositor/OgreCompositorShadowNode.h"
#include "Vao/OgreVaoManager.h"
#include "Vao/OgreConstBufferPacked.h"
#include "Vao/OgreTexBufferPacked.h"
#include "Vao/OgreStagingBuffer.h"

#include "OgreHlmsManager.h"
#include "OgreLogManager.h"

#include "CommandBuffer/OgreCommandBuffer.h"
#include "CommandBuffer/OgreCbTexture.h"
#include "CommandBuffer/OgreCbShaderBuffer.h"
#include <Ogre/Components/Hlms/Unlit/include/OgreUnlitProperty.h>


#include <XERenderer/private/ScreenRenderable.hpp>

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>

namespace XE {

	using namespace Ogre;

	XEHlmsProjection::XEHlmsProjection(Ogre::Archive *dataFolder, Ogre::ArchiveVec *libraryFolders,
		Ogre::HlmsTypes type, const Ogre::String &typeName) :
		Ogre::HlmsUnlit(dataFolder, libraryFolders,	type, typeName)
	{
	}

	uint32 XEHlmsProjection::fillBuffersForV1(const HlmsCache *cache,
		const QueuedRenderable &queuedRenderable,
		bool casterPass, uint32 lastCacheHash,
		CommandBuffer *commandBuffer)
	{
		return XEfillBuffersFor(cache, queuedRenderable, casterPass,
			lastCacheHash, commandBuffer, true);
	}
	//-----------------------------------------------------------------------------------
	uint32 XEHlmsProjection::fillBuffersForV2(const Ogre::HlmsCache *cache,
		const Ogre::QueuedRenderable &queuedRenderable,
		bool casterPass, Ogre::uint32 lastCacheHash,
		Ogre::CommandBuffer *commandBuffer)
	{
		return XEfillBuffersFor(cache, queuedRenderable, casterPass,
			lastCacheHash, commandBuffer, false);
	}
	//-----------------------------------------------------------------------------------
	Ogre::uint32 XEHlmsProjection::XEfillBuffersFor(const Ogre::HlmsCache *cache, const Ogre::QueuedRenderable &queuedRenderable,
		bool casterPass, Ogre::uint32 lastCacheHash,
		Ogre::CommandBuffer *commandBuffer, bool isV1)
	{
//		assert(dynamic_cast<const XEHlmsProjectionDatablock*>(static_cast<const ScreenRenderable*>(queuedRenderable.renderable)->getDatablock()));
		const XEHlmsProjectionDatablock *datablock = static_cast<const XEHlmsProjectionDatablock*>(
			static_cast<const ScreenRenderable*>(queuedRenderable.renderable)->getDatablock());

		if (OGRE_EXTRACT_HLMS_TYPE_FROM_CACHE_HASH(lastCacheHash) != mType)
		{
			//We changed HlmsType, rebind the shared textures.
			mLastTextureHash = 0;
			mLastBoundPool = 0;

			//layout(binding = 0) uniform PassBuffer {} pass
			ConstBufferPacked *passBuffer = mPassBuffers[mCurrentPassBuffer - 1];
			*commandBuffer->addCommand<CbShaderBuffer>() = CbShaderBuffer(VertexShader,
				0, passBuffer, 0,
				passBuffer->
				getTotalSizeBytes());
			*commandBuffer->addCommand<CbShaderBuffer>() = CbShaderBuffer(PixelShader,
				0, passBuffer, 0,
				passBuffer->
				getTotalSizeBytes());

			//layout(binding = 2) uniform InstanceBuffer {} instance
			if (mCurrentConstBuffer < mConstBuffers.size() &&
				(size_t)((mCurrentMappedConstBuffer - mStartMappedConstBuffer) + 4) <=
				mCurrentConstBufferSize)
			{
				*commandBuffer->addCommand<CbShaderBuffer>() =
					CbShaderBuffer(VertexShader, 2, mConstBuffers[mCurrentConstBuffer], 0, 0);
				*commandBuffer->addCommand<CbShaderBuffer>() =
					CbShaderBuffer(PixelShader, 2, mConstBuffers[mCurrentConstBuffer], 0, 0);
			}

			rebindTexBuffer(commandBuffer);

			mListener->hlmsTypeChanged(casterPass, commandBuffer, datablock);
		}

		//Don't bind the material buffer on caster passes (important to keep
		//MDI & auto-instancing running on shadow map passes)
		if (mLastBoundPool != datablock->getAssignedPool() && !casterPass)
		{
			//layout(binding = 1) uniform MaterialBuf {} materialArray
			const ConstBufferPool::BufferPool *newPool = datablock->getAssignedPool();
			*commandBuffer->addCommand<CbShaderBuffer>() = CbShaderBuffer(PixelShader,
				1, newPool->materialBuffer, 0,
				newPool->materialBuffer->
				getTotalSizeBytes());
			if (newPool->extraBuffer)
			{
				TexBufferPacked *extraBuffer = static_cast<TexBufferPacked*>(newPool->extraBuffer);
				*commandBuffer->addCommand<CbShaderBuffer>() = CbShaderBuffer(VertexShader, 1,
					extraBuffer, 0,
					extraBuffer->
					getTotalSizeBytes());
			}

			mLastBoundPool = newPool;
		}

		uint32 * RESTRICT_ALIAS currentMappedConstBuffer = mCurrentMappedConstBuffer;
		float * RESTRICT_ALIAS currentMappedTexBuffer = mCurrentMappedTexBuffer;

		const Matrix4 &worldMat = queuedRenderable.movableObject->_getParentNodeFullTransform();

		bool exceedsConstBuffer = (size_t)((currentMappedConstBuffer - mStartMappedConstBuffer) + 4) >
			mCurrentConstBufferSize;

		const size_t minimumTexBufferSize = 16;
		bool exceedsTexBuffer = (currentMappedTexBuffer - mStartMappedTexBuffer) +
			minimumTexBufferSize >= mCurrentTexBufferSize;

		if (exceedsConstBuffer || exceedsTexBuffer)
		{
			currentMappedConstBuffer = mapNextConstBuffer(commandBuffer);

			if (exceedsTexBuffer)
				mapNextTexBuffer(commandBuffer, minimumTexBufferSize * sizeof(float));
			else
				rebindTexBuffer(commandBuffer, true, minimumTexBufferSize * sizeof(float));

			currentMappedTexBuffer = mCurrentMappedTexBuffer;
		}

		//---------------------------------------------------------------------------
		//                          ---- VERTEX SHADER ----
		//---------------------------------------------------------------------------
		bool useIdentityProjection = static_cast<const ScreenRenderable*>(queuedRenderable.renderable)->getUseCustomProjectionMatrix(); //>getUseIdentityProjection();

		//uint materialIdx[]
		*currentMappedConstBuffer = datablock->getAssignedSlot();
		*reinterpret_cast<float * RESTRICT_ALIAS>(currentMappedConstBuffer + 1) = datablock->
			mShadowConstantBias;
		*(currentMappedConstBuffer + 2) = useIdentityProjection;
		currentMappedConstBuffer += 4;

		//mat4 worldViewProj
	//	Matrix4 tmp = mPreparedPass.viewProjMatrix[useIdentityProjection] * worldMat;
		if (useIdentityProjection)
			mPreparedPass.viewProjMatrix[useIdentityProjection] = static_cast<ScreenRenderable*>(queuedRenderable.renderable)->getCustomProjectionMatrix();
		
			Matrix4 tmp = mPreparedPass.viewProjMatrix[useIdentityProjection] * worldMat;

#if !OGRE_DOUBLE_PRECISION
		memcpy(currentMappedTexBuffer, &tmp, sizeof(Matrix4));
		currentMappedTexBuffer += 16;
#else
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				*currentMappedTexBuffer++ = tmp[y][x];
			}
		}
#endif

		//---------------------------------------------------------------------------
		//                          ---- PIXEL SHADER ----
		//---------------------------------------------------------------------------

		if (!casterPass)
		{
			if (datablock->mTextureHash != mLastTextureHash)
			{
				//Rebind textures
				size_t texUnit = 2;

				UnlitBakedTextureArray::const_iterator itor = datablock->mBakedTextures.begin();
				UnlitBakedTextureArray::const_iterator end = datablock->mBakedTextures.end();

				while (itor != end)
				{
					*commandBuffer->addCommand<CbTexture>() =
						CbTexture(texUnit++, true, itor->texture.get(), itor->samplerBlock);
					++itor;
				}

				*commandBuffer->addCommand<CbTextureDisableFrom>() = CbTextureDisableFrom(texUnit);

				mLastTextureHash = datablock->mTextureHash;
			}
		}

		mCurrentMappedConstBuffer = currentMappedConstBuffer;
		mCurrentMappedTexBuffer = currentMappedTexBuffer;

		return ((mCurrentMappedConstBuffer - mStartMappedConstBuffer) >> 2) - 1;
	}

}