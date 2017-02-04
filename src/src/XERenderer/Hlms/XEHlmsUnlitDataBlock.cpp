#include <XERenderer/Hlms/XEHlmsUnlitDatablock.hpp>

#include "OgreStableHeaders.h"

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>
#include "OgreHlmsManager.h"
#include "OgreHlmsTextureManager.h"
#include "OgreTexture.h"
#include "OgreLogManager.h"

namespace Ogre
{
	//extern const String c_unlitBlendModes[];
	const String c_unlitBlendModes[] =
	{
		"NormalNonPremul", "NormalPremul", "Add", "Subtract", "Multiply",
		"Multiply2x", "Screen", "Overlay", "Lighten", "Darken", "GrainExtract",
		"GrainMerge", "Difference"
	};

	const String c_diffuseMap[NUM_UNLIT_TEXTURE_TYPES] =
	{
		"diffuse_map",
		"diffuse_map1",
		"diffuse_map2",
		"diffuse_map3",
		"diffuse_map4",
		"diffuse_map5",
		"diffuse_map6",
		"diffuse_map7",
		"diffuse_map8",
		"diffuse_map9",
		"diffuse_map10",
		"diffuse_map11",
		"diffuse_map12",
		"diffuse_map13",
		"diffuse_map14",
		"diffuse_map15"
	};

	const size_t XEHlmsUnlitDatablock::MaterialSizeInGpu = 8 * 4 + NUM_UNLIT_TEXTURE_TYPES * 2;
	const size_t XEHlmsUnlitDatablock::MaterialSizeInGpuAligned = alignToNextMultiple(
		XEHlmsUnlitDatablock::MaterialSizeInGpu,
		4 * 4);
	const uint8 XEHlmsUnlitDatablock::R_MASK = 0;
	const uint8 XEHlmsUnlitDatablock::G_MASK = 1;
	const uint8 XEHlmsUnlitDatablock::B_MASK = 2;
	const uint8 XEHlmsUnlitDatablock::A_MASK = 3;
	//-----------------------------------------------------------------------------------
	XEHlmsUnlitDatablock::XEHlmsUnlitDatablock(IdString name, XEHlmsUnlit *creator,
		const HlmsMacroblock *macroblock,
		const HlmsBlendblock *blendblock,
		const HlmsParamVec &params) :
		HlmsDatablock(name, creator, macroblock, blendblock, params),
		mNumEnabledAnimationMatrices(0),
		mHasColour(false),
		mR(1.0f), mG(1.0f), mB(1.0f), mA(1.0f)
	{
		for (size_t i = 0; i<NUM_UNLIT_TEXTURE_TYPES; ++i)
		{
			mTextureMatrices[i] = Matrix4::IDENTITY;
			setTextureSwizzle(i, R_MASK, G_MASK, B_MASK, A_MASK);
		}

		memset(mUvSource, 0, sizeof(mUvSource));
		memset(mBlendModes, 0, sizeof(mBlendModes));

		memset(mTexIndices, 0, sizeof(mTexIndices));
		memset(mSamplerblocks, 0, sizeof(mSamplerblocks));

		memset(mEnabledAnimationMatrices, 0, sizeof(mEnabledAnimationMatrices));

		for (size_t i = 0; i<NUM_UNLIT_TEXTURE_TYPES; ++i)
			mTexToBakedTextureIdx[i] = NUM_UNLIT_TEXTURE_TYPES;

		String paramVal;

		if (Hlms::findParamInVec(params, "diffuse", paramVal))
		{
			mHasColour = true;

			if (!paramVal.empty())
			{
				ColourValue val = StringConverter::parseColourValue(paramVal);
				mR = val.r;
				mG = val.g;
				mB = val.b;
				mA = val.a;
			}
		}

		HlmsManager *hlmsManager = mCreator->getHlmsManager();
		HlmsTextureManager *hlmsTextureManager = hlmsManager->getTextureManager();

		UnlitBakedTexture textures[NUM_UNLIT_TEXTURE_TYPES];

		const HlmsSamplerblock *defaultSamplerblock = hlmsManager->getSamplerblock(HlmsSamplerblock());

		for (size_t i = 0; i<sizeof(c_diffuseMap) / sizeof(String); ++i)
		{
			if (Hlms::findParamInVec(params, c_diffuseMap[i], paramVal))
			{
				mTexIndices[i] = 0;
				textures[i].texture = hlmsTextureManager->getBlankTexture().texture;
				mSamplerblocks[i] = defaultSamplerblock;
				hlmsManager->addReference(mSamplerblocks[i]);

				StringVector vec = StringUtil::split(paramVal);

				StringVector::const_iterator itor = vec.begin();
				StringVector::const_iterator end = vec.end();

				while (itor != end)
				{
					uint val = StringConverter::parseUnsignedInt(*itor, ~0);

					if (val != (uint)(~0))
					{
						//It's a number, must be an UV Set
						setTextureUvSource(i, val);
					}
					else if (!itor->empty())
					{
						//Is it a blend mode?
						const String *it = std::find(c_unlitBlendModes, c_unlitBlendModes +
							sizeof(c_unlitBlendModes) / sizeof(String),
							*itor);

						if (it == c_unlitBlendModes + sizeof(c_unlitBlendModes) / sizeof(String))
						{
							//Not blend mode, try loading a texture
							textures[i].texture = setTexture(*itor, i);
						}
						else
						{
							//It's a blend mode
							mBlendModes[i] = (it - c_unlitBlendModes);
						}
					}

					++itor;
				}
			}
		}

		//Remove the reference
		hlmsManager->destroySamplerblock(defaultSamplerblock);

		for (size_t i = 0; i<NUM_UNLIT_TEXTURE_TYPES; ++i)
			textures[i].samplerBlock = mSamplerblocks[i];

		if (Hlms::findParamInVec(params, "animate", paramVal))
		{
			size_t pos = paramVal.find_first_of(' ');
			while (pos != String::npos)
			{
				uint val = StringConverter::parseUnsignedInt(paramVal.substr(pos, 1), ~0);

				if (val >= NUM_UNLIT_TEXTURE_TYPES)
				{
					OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
						mName.getFriendlyText() +
						": animate parameters must be in range [0; " +
						StringConverter::toString(NUM_UNLIT_TEXTURE_TYPES) + ")",
						"XEHlmsUnlitDatablock::HlmsUnlitDatablock");
				}

				if (mEnabledAnimationMatrices[val])
				{
					LogManager::getSingleton().logMessage("WARNING: specified same texture unit twice "
						"in material '" + mName.getFriendlyText() +
						"'; parameter 'animate'. Are you sure this is correct?", LML_CRITICAL);
				}
				else
				{
					++mNumEnabledAnimationMatrices;
				}

				mEnabledAnimationMatrices[val] = true;

				pos = paramVal.find_first_of(' ');
			}
		}

		bakeTextures(textures);

		calculateHash();

		//Use the same hash for everything (the number of materials per buffer is high)
		creator->requestSlot(mNumEnabledAnimationMatrices != 0, this,
			mNumEnabledAnimationMatrices != 0);
	}
	//-----------------------------------------------------------------------------------
	XEHlmsUnlitDatablock::~XEHlmsUnlitDatablock()
	{
		if (mAssignedPool)
			static_cast<HlmsUnlit*>(mCreator)->releaseSlot(this);

		HlmsManager *hlmsManager = mCreator->getHlmsManager();
		if (hlmsManager)
		{
			for (size_t i = 0; i<NUM_UNLIT_TEXTURE_TYPES; ++i)
			{
				if (mSamplerblocks[i])
					hlmsManager->destroySamplerblock(mSamplerblocks[i]);
			}
		}
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::calculateHash()
	{
		IdString hash;

		UnlitBakedTextureArray::const_iterator itor = mBakedTextures.begin();
		UnlitBakedTextureArray::const_iterator end = mBakedTextures.end();

		while (itor != end)
		{
			hash += IdString(itor->texture->getName());
			hash += IdString(itor->samplerBlock->mId);

			++itor;
		}

		if (mTextureHash != hash.mHash)
		{
			mTextureHash = hash.mHash;
			//static_cast<HlmsUnlit*>(mCreator)->requestSlot( mTextureHash, this );
		}
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::scheduleConstBufferUpdate(void)
	{
		static_cast<HlmsUnlit*>(mCreator)->scheduleForUpdate(this);
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::uploadToConstBuffer(char *dstPtr)
	{
		memcpy(dstPtr, &mAlphaTestThreshold, sizeof(float));
		dstPtr += 4 * sizeof(float);
		memcpy(dstPtr, &mR, MaterialSizeInGpu - 4 * sizeof(float));
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::uploadToExtraBuffer(char *dstPtr)
	{
#if !OGRE_DOUBLE_PRECISION
		memcpy(dstPtr, mTextureMatrices, sizeof(mTextureMatrices));
#else
		float * RESTRICT_ALIAS dstFloat = reinterpret_cast<float * RESTRICT_ALIAS>(dstPtr);

		for (size_t i = 0; i<NUM_UNLIT_TEXTURE_TYPES * 4; ++i)
			*dstFloat++ = (float)mTextureMatrices[0][0][i];
#endif
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::decompileBakedTextures(UnlitBakedTexture outTextures[NUM_UNLIT_TEXTURE_TYPES])
	{
		//Decompile the baked textures to know which texture is assigned to each type.
		for (size_t i = 0; i<NUM_UNLIT_TEXTURE_TYPES; ++i)
		{
			uint8 idx = mTexToBakedTextureIdx[i];

			if (idx < NUM_UNLIT_TEXTURE_TYPES)
			{
				outTextures[i] = UnlitBakedTexture(mBakedTextures[idx].texture, mSamplerblocks[i]);
			}
			else
			{
				//The texture may be null, but the samplerblock information may still be there.
				outTextures[i] = UnlitBakedTexture(TexturePtr(), mSamplerblocks[i]);
			}
		}
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::bakeTextures(const UnlitBakedTexture textures[NUM_UNLIT_TEXTURE_TYPES])
	{
		//The shader might need to be recompiled (mTexToBakedTextureIdx changed).
		//We'll need to flush.
		//Most likely mTexIndices also changed, so we need to update the const buffers as well
		mBakedTextures.clear();

		for (size_t i = 0; i<NUM_UNLIT_TEXTURE_TYPES; ++i)
		{
			if (!textures[i].texture.isNull())
			{
				UnlitBakedTextureArray::const_iterator itor = std::find(mBakedTextures.begin(),
					mBakedTextures.end(),
					textures[i]);

				if (itor == mBakedTextures.end())
				{
					mTexToBakedTextureIdx[i] = mBakedTextures.size();
					mBakedTextures.push_back(textures[i]);
				}
				else
				{
					mTexToBakedTextureIdx[i] = itor - mBakedTextures.begin();
				}
			}
			else
			{
				mTexToBakedTextureIdx[i] = NUM_UNLIT_TEXTURE_TYPES;
			}
		}

		calculateHash();
		flushRenderables();
		scheduleConstBufferUpdate();
	}
	//-----------------------------------------------------------------------------------
	TexturePtr XEHlmsUnlitDatablock::setTexture(const String &name, uint8 texUnit)
	{
		HlmsManager *hlmsManager = mCreator->getHlmsManager();
		HlmsTextureManager *hlmsTextureManager = hlmsManager->getTextureManager();
		HlmsTextureManager::TextureLocation texLocation = hlmsTextureManager->
			createOrRetrieveTexture(
				name,
				HlmsTextureManager::TEXTURE_TYPE_DIFFUSE);

		mTexIndices[texUnit] = texLocation.xIdx;

		return texLocation.texture;
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setUseColour(bool useColour)
	{
		if (mHasColour != useColour)
		{
			mHasColour = useColour;
			flushRenderables();
		}
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setColour(const ColourValue &diffuse)
	{
		assert(diffuse == ColourValue::White ||
			(mHasColour &&
				"Setting colour to a Datablock created w/out diffuse flag will be ignored"));
		mR = diffuse.r;
		mG = diffuse.g;
		mB = diffuse.b;
		mA = diffuse.a;

		scheduleConstBufferUpdate();
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setTexture(uint8 texType, uint16 arrayIndex,
		const TexturePtr &newTexture, const HlmsSamplerblock *refParams)
	{
		assert(texType < NUM_UNLIT_TEXTURE_TYPES);

		UnlitBakedTexture textures[NUM_UNLIT_TEXTURE_TYPES];

		//Decompile the baked textures to know which texture is assigned to each type.
		decompileBakedTextures(textures);

		//Set the new samplerblock
		if (refParams)
		{
			HlmsManager *hlmsManager = mCreator->getHlmsManager();
			const HlmsSamplerblock *oldSamplerblock = mSamplerblocks[texType];
			mSamplerblocks[texType] = hlmsManager->getSamplerblock(*refParams);

			if (oldSamplerblock)
				hlmsManager->destroySamplerblock(oldSamplerblock);
		}
		else if (!newTexture.isNull() && !mSamplerblocks[texType])
		{
			//Adding a texture, but the samplerblock doesn't exist. Create a default one.
			HlmsSamplerblock samplerBlockRef;
			HlmsManager *hlmsManager = mCreator->getHlmsManager();
			mSamplerblocks[texType] = hlmsManager->getSamplerblock(samplerBlockRef);
		}

		UnlitBakedTexture oldTex = textures[texType];

		//Set the texture and make the samplerblock changes to take effect
		textures[texType].texture = newTexture;
		textures[texType].samplerBlock = mSamplerblocks[texType];
		mTexIndices[texType] = arrayIndex;

		if (oldTex == textures[texType])
		{
			//Only the array index changed. Just update our constant buffer.
			scheduleConstBufferUpdate();
		}
		else
		{
			bakeTextures(textures);
		}
	}
	//-----------------------------------------------------------------------------------
	TexturePtr XEHlmsUnlitDatablock::getTexture(uint8 texType) const
	{
		assert(texType < NUM_UNLIT_TEXTURE_TYPES);

		TexturePtr retVal;

		if (mTexToBakedTextureIdx[texType] < mBakedTextures.size())
			retVal = mBakedTextures[mTexToBakedTextureIdx[texType]].texture;

		return retVal;
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setTextureSwizzle(uint8 texType, uint8 r, uint8 g, uint8 b, uint8 a)
	{
		assert(texType < NUM_UNLIT_TEXTURE_TYPES);
		mTextureSwizzles[texType] = (r << 6u) | ((g & 0x03u) << 4u) | ((b & 0x03u) << 2u) | (a & 0x03u);
		flushRenderables();
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setSamplerblock(uint8 texType, const HlmsSamplerblock &params)
	{
		const HlmsSamplerblock *oldSamplerblock = mSamplerblocks[texType];
		HlmsManager *hlmsManager = mCreator->getHlmsManager();
		mSamplerblocks[texType] = hlmsManager->getSamplerblock(params);

		if (oldSamplerblock)
			hlmsManager->destroySamplerblock(oldSamplerblock);

		if (oldSamplerblock != mSamplerblocks[texType])
		{
			UnlitBakedTexture textures[NUM_UNLIT_TEXTURE_TYPES];
			decompileBakedTextures(textures);
			bakeTextures(textures);
		}
	}
	//-----------------------------------------------------------------------------------
	const HlmsSamplerblock* XEHlmsUnlitDatablock::getSamplerblock(uint8 texType) const
	{
		assert(texType < NUM_UNLIT_TEXTURE_TYPES);
		return mSamplerblocks[texType];
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setTextureUvSource(uint8 sourceType, uint8 uvSet)
	{
		if (uvSet >= 8)
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "UV set must be in rage in range [0; 8)",
				"XEHlmsUnlitDatablock::setTextureUvSource");
		}

		if (sourceType >= NUM_UNLIT_TEXTURE_TYPES)
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "Invalid sourceType",
				"XEHlmsUnlitDatablock::setTextureUvSource");
		}

		if (mUvSource[sourceType] != uvSet)
		{
			mUvSource[sourceType] = uvSet;
			flushRenderables();
		}
	}
	//-----------------------------------------------------------------------------------
	uint8 XEHlmsUnlitDatablock::getTextureUvSource(uint8 sourceType) const
	{
		assert(sourceType < 8);
		return mUvSource[sourceType];
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setBlendMode(uint8 texType, UnlitBlendModes blendMode)
	{
		if (texType >= NUM_UNLIT_TEXTURE_TYPES)
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "Invalid blendMode",
				"XEHlmsUnlitDatablock::setBlendMode");
		}

		if (mBlendModes[texType] != blendMode)
		{
			mBlendModes[texType] = blendMode;
			flushRenderables();
		}
	}
	//-----------------------------------------------------------------------------------
	UnlitBlendModes XEHlmsUnlitDatablock::getBlendMode(uint8 texType) const
	{
		return static_cast<UnlitBlendModes>(mBlendModes[texType]);
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setEnableAnimationMatrix(uint8 textureUnit, bool bEnable)
	{
		assert(textureUnit < NUM_UNLIT_TEXTURE_TYPES);

		if (mEnabledAnimationMatrices[textureUnit] != bEnable)
		{
			mEnabledAnimationMatrices[textureUnit] = bEnable;
			mNumEnabledAnimationMatrices += (bEnable * 2) - 1; //bEnable ? +1 : -1

			if (!mNumEnabledAnimationMatrices || (mNumEnabledAnimationMatrices == 1 && bEnable))
			{
				static_cast<HlmsUnlit*>(mCreator)->requestSlot(mNumEnabledAnimationMatrices != 0, this,
					mNumEnabledAnimationMatrices != 0);
			}

			scheduleConstBufferUpdate();

			flushRenderables();
		}
	}
	//-----------------------------------------------------------------------------------
	bool XEHlmsUnlitDatablock::getEnableAnimationMatrix(uint8 textureUnit) const
	{
		return mEnabledAnimationMatrices[textureUnit];
	}
	//-----------------------------------------------------------------------------------
	void XEHlmsUnlitDatablock::setAnimationMatrix(uint8 textureUnit, const Matrix4 &matrix)
	{
		assert(textureUnit < NUM_UNLIT_TEXTURE_TYPES);

		mTextureMatrices[textureUnit] = matrix;
		if (mEnabledAnimationMatrices[textureUnit])
			scheduleConstBufferUpdate();
	}
	//-----------------------------------------------------------------------------------
	const Matrix4& XEHlmsUnlitDatablock::getAnimationMatrix(uint8 textureUnit) const
	{
		return mTextureMatrices[textureUnit];
	}
	//-----------------------------------------------------------------------------------
	uint8 XEHlmsUnlitDatablock::getBakedTextureIdx(uint8 texType) const
	{
		assert(texType < NUM_UNLIT_TEXTURE_TYPES);
		return mTexToBakedTextureIdx[texType];
	}
}
