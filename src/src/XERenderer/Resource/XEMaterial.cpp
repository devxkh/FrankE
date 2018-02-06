#include <XERenderer/Resource/XEMaterial.hpp>

#include <XERenderer/Resource/gltfAsset.h>

//#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsJsonPbs.h>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbsDatablock.h>
#include <Ogre/OgreMain/include/OgreHlmsManager.h>
#include <Ogre/OgreMain/include/OgreHlms.h>
#include <Ogre/OgreMain/include/OgreColourValue.h>
#include <Ogre/OgreMain/include/OgreHlmsTextureManager.h>
#include <Ogre/OgreMain/include/OgreTextureManager.h>

#include "OgreHlmsJson.h"
#include "OgreHlmsJsonCompute.h"
#include "OgreHlmsManager.h"
#include "OgreHlms.h"
#include "OgreVector2.h"
#include "OgreLwString.h"

namespace XE
{
	struct XENamedBlocks
	{
		Ogre::map<Ogre::LwConstString, const Ogre::HlmsMacroblock*>::type macroblocks;
		Ogre::map<Ogre::LwConstString, const Ogre::HlmsBlendblock*>::type blendblocks;
		Ogre::map<Ogre::LwConstString, const Ogre::HlmsSamplerblock*>::type samplerblocks;
	};

	XEMaterial::XEMaterial(Ogre::HlmsManager *hlmsManager)
		: mHlmsManager(hlmsManager)
	{


	}

	void loadSampler(const gltf::Sampler& sampler, const Ogre::HlmsSamplerblock* samplerblock)
	{
		//rapidjson::Value::ConstMemberIterator itor = samplers.FindMember("min");
		//if (itor != samplers.MemberEnd() && itor->value.IsString())
		//	samplerblock.mMinFilter = parseFilterOptions(itor->value.GetString());

		//itor = samplers.FindMember("mag");
		//if (itor != samplers.MemberEnd() && itor->value.IsString())
		//	samplerblock.mMagFilter = parseFilterOptions(itor->value.GetString());

		//itor = samplers.FindMember("mip");
		//if (itor != samplers.MemberEnd() && itor->value.IsString())
		//	samplerblock.mMipFilter = parseFilterOptions(itor->value.GetString());

		//itor = samplers.FindMember("u");
		//if (itor != samplers.MemberEnd() && itor->value.IsString())
		//	samplerblock.mU = parseTextureAddressingMode(itor->value.GetString());

		//itor = samplers.FindMember("v");
		//if (itor != samplers.MemberEnd() && itor->value.IsString())
		//	samplerblock.mV = parseTextureAddressingMode(itor->value.GetString());

		//itor = samplers.FindMember("w");
		//if (itor != samplers.MemberEnd() && itor->value.IsString())
		//	samplerblock.mW = parseTextureAddressingMode(itor->value.GetString());

		//itor = samplers.FindMember("miplodbias");
		//if (itor != samplers.MemberEnd() && itor->value.IsNumber())
		//	samplerblock.mMipLodBias = static_cast<float>(itor->value.GetDouble());

		//itor = samplers.FindMember("max_anisotropic");
		//if (itor != samplers.MemberEnd() && itor->value.IsNumber())
		//	samplerblock.mMaxAnisotropy = static_cast<float>(itor->value.GetDouble());

		//itor = samplers.FindMember("compare_function");
		//if (itor != samplers.MemberEnd() && itor->value.IsString())
		//	samplerblock.mCompareFunction = parseCompareFunction(itor->value.GetString());

		//itor = samplers.FindMember("border");
		//if (itor != samplers.MemberEnd() && itor->value.IsArray())
		//{
		//	const rapidjson::Value& array = itor->value;
		//	const rapidjson::SizeType arraySize = std::min(4u, array.Size());
		//	for (rapidjson::SizeType i = 0; i<arraySize; ++i)
		//	{
		//		if (array[i].IsNumber())
		//			samplerblock.mBorderColour[i] = static_cast<float>(array[i].GetDouble());
		//	}
		//}

		//itor = samplers.FindMember("min_lod");
		//if (itor != samplers.MemberEnd() && itor->value.IsNumber())
		//	samplerblock.mMinLod = static_cast<float>(itor->value.GetDouble());

		//itor = samplers.FindMember("max_lod");
		//if (itor != samplers.MemberEnd() && itor->value.IsNumber())
		//	samplerblock.mMaxLod = static_cast<float>(itor->value.GetDouble());
	}


	void loadMacroblock(const rapidjson::Value &macroblocksJson, Ogre::HlmsMacroblock &macroblock)
	{
		//rapidjson::Value::ConstMemberIterator itor = macroblocksJson.FindMember("scissor_test");
		//if (itor != macroblocksJson.MemberEnd() && itor->value.IsBool())
		//	macroblock.mScissorTestEnabled = itor->value.GetBool();

		//itor = macroblocksJson.FindMember("depth_check");
		//if (itor != macroblocksJson.MemberEnd() && itor->value.IsBool())
		//	macroblock.mDepthCheck = itor->value.GetBool();

		//itor = macroblocksJson.FindMember("depth_write");
		//if (itor != macroblocksJson.MemberEnd() && itor->value.IsBool())
		//	macroblock.mDepthWrite = itor->value.GetBool();

		//itor = macroblocksJson.FindMember("depth_function");
		//if (itor != macroblocksJson.MemberEnd() && itor->value.IsString())
		//	macroblock.mDepthFunc = parseCompareFunction(itor->value.GetString());

		//itor = macroblocksJson.FindMember("depth_bias_constant");
		//if (itor != macroblocksJson.MemberEnd() && itor->value.IsNumber())
		//	macroblock.mDepthBiasConstant = static_cast<float>(itor->value.GetDouble());

		//itor = macroblocksJson.FindMember("depth_bias_slope_scale");
		//if (itor != macroblocksJson.MemberEnd() && itor->value.IsNumber())
		//	macroblock.mDepthBiasSlopeScale = static_cast<float>(itor->value.GetDouble());

		//itor = macroblocksJson.FindMember("cull_mode");
		//if (itor != macroblocksJson.MemberEnd() && itor->value.IsString())
		//	macroblock.mCullMode = parseCullMode(itor->value.GetString());

		//itor = macroblocksJson.FindMember("polygon_mode");
		//if (itor != macroblocksJson.MemberEnd() && itor->value.IsString())
		//	macroblock.mPolygonMode = parsePolygonMode(itor->value.GetString());
	}
	//-----------------------------------------------------------------------------------
	void loadBlendblock(const rapidjson::Value &blendblocksJson, Ogre::HlmsBlendblock &blendblock)
	{
		//rapidjson::Value::ConstMemberIterator itor = blendblocksJson.FindMember("alpha_to_coverage");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsBool())
		//	blendblock.mAlphaToCoverageEnabled = itor->value.GetBool();

		//itor = blendblocksJson.FindMember("blendmask");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsString())
		//{
		//	uint8 mask = 0;
		//	const char *blendmask = itor->value.GetString();
		//	if (strchr(blendmask, 'r'))
		//		mask |= HlmsBlendblock::BlendChannelRed;
		//	if (strchr(blendmask, 'g'))
		//		mask |= HlmsBlendblock::BlendChannelGreen;
		//	if (strchr(blendmask, 'b'))
		//		mask |= HlmsBlendblock::BlendChannelBlue;
		//	if (strchr(blendmask, 'a'))
		//		mask |= HlmsBlendblock::BlendChannelAlpha;

		//	blendblock.mBlendChannelMask = mask;
		//}

		//itor = blendblocksJson.FindMember("separate_blend");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsBool())
		//	blendblock.mSeparateBlend = itor->value.GetBool();

		//itor = blendblocksJson.FindMember("src_blend_factor");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsString())
		//	blendblock.mSourceBlendFactor = parseBlendFactor(itor->value.GetString());

		//itor = blendblocksJson.FindMember("dst_blend_factor");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsString())
		//	blendblock.mDestBlendFactor = parseBlendFactor(itor->value.GetString());

		//itor = blendblocksJson.FindMember("src_alpha_blend_factor");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsString())
		//	blendblock.mSourceBlendFactorAlpha = parseBlendFactor(itor->value.GetString());

		//itor = blendblocksJson.FindMember("dst_alpha_blend_factor");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsString())
		//	blendblock.mDestBlendFactorAlpha = parseBlendFactor(itor->value.GetString());

		//itor = blendblocksJson.FindMember("blend_operation");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsString())
		//	blendblock.mBlendOperation = parseBlendOperation(itor->value.GetString());

		//itor = blendblocksJson.FindMember("blend_operation_alpha");
		//if (itor != blendblocksJson.MemberEnd() && itor->value.IsString())
		//	blendblock.mBlendOperationAlpha = parseBlendOperation(itor->value.GetString());
	}

	//-----------------------------------------------------------------------------------
	void XEMaterial::loadMaterial(const gltf::Asset& asset, const gltf::Material& gltfMaterial,
		Ogre::HlmsDatablock *datablock)
	{
		assert(dynamic_cast<Ogre::HlmsPbsDatablock*>(datablock));
		Ogre::HlmsPbsDatablock *pbsDatablock = static_cast<Ogre::HlmsPbsDatablock*>(datablock);

		//gltfMaterial.pbr.metallicFactor

		//workflow
		pbsDatablock->setWorkflow(Ogre::HlmsPbsDatablock::Workflows::MetallicWorkflow); //parseWorkflow(itor->value.GetString()));

		//brdf
		//pbsDatablock->setBrdf(parseBrdf(itor->value.GetString()));

		//two_sided
		pbsDatablock->setTwoSidedLighting(gltfMaterial.doubleSided, true, pbsDatablock->getMacroblock(true)->mCullMode);

		//itor = json.FindMember("receive_shadows");
		//if (itor != json.MemberEnd() && itor->value.IsBool())
		//	pbsDatablock->setReceiveShadows(itor->value.GetBool());

		/*itor = json.FindMember("transparency");
		if (itor != json.MemberEnd() && itor->value.IsObject())
		{
			const rapidjson::Value &subobj = itor->value;

			float transparencyValue = pbsDatablock->getTransparency();
			HlmsPbsDatablock::TransparencyModes transpMode = pbsDatablock->getTransparencyMode();
			bool useAlphaFromTextures = pbsDatablock->getUseAlphaFromTextures();

			itor = subobj.FindMember("value");
			if (itor != subobj.MemberEnd() && itor->value.IsNumber())
				transparencyValue = static_cast<float>(itor->value.GetDouble());

			itor = subobj.FindMember("mode");
			if (itor != subobj.MemberEnd() && itor->value.IsString())
				transpMode = parseTransparencyMode(itor->value.GetString());

			itor = subobj.FindMember("use_alpha_from_textures");
			if (itor != subobj.MemberEnd() && itor->value.IsBool())
				useAlphaFromTextures = itor->value.GetBool();

			const bool changeBlendblock = !json.HasMember("blendblock");
			pbsDatablock->setTransparency(transparencyValue, transpMode,
				useAlphaFromTextures, changeBlendblock);
		}*/


		XENamedBlocks blocks;



		//Load macroblocks
		//itor = d.FindMember("macroblocks");
		//if (itor != d.MemberEnd() && itor->value.IsObject())
		//{
		//	const rapidjson::Value &macroblocksJson = itor->value;

		//	rapidjson::Value::ConstMemberIterator itMacros = macroblocksJson.MemberBegin();
		//	rapidjson::Value::ConstMemberIterator enMacros = macroblocksJson.MemberEnd();

		//	while (itMacros != enMacros)
		//	{
		//		HlmsMacroblock macroblock;
		//		loadMacroblock(itMacros->value, macroblock);

		//		LwConstString keyName(LwConstString(itMacros->name.GetString(),
		//			itMacros->name.GetStringLength() + 1u));

		//		blocks.macroblocks[keyName] = mHlmsManager->getMacroblock(macroblock);

		//		++itMacros;
		//	}
		//}

		////Load blendblocks
		//itor = d.FindMember("blendblocks");
		//if (itor != d.MemberEnd() && itor->value.IsObject())
		//{
		//	const rapidjson::Value &blendblocksJson = itor->value;

		//	rapidjson::Value::ConstMemberIterator itBlends = blendblocksJson.MemberBegin();
		//	rapidjson::Value::ConstMemberIterator enBlends = blendblocksJson.MemberEnd();

		//	while (itBlends != enBlends)
		//	{
		//		HlmsBlendblock blendblock;
		//		loadBlendblock(itBlends->value, blendblock);

		//		LwConstString keyName(LwConstString(itBlends->name.GetString(),
		//			itBlends->name.GetStringLength() + 1u));

		//		blocks.blendblocks[keyName] = mHlmsManager->getBlendblock(blendblock);

		//		++itBlends;
		//	}
		//}

		//rapidjson::Value::ConstMemberIterator itDatablock = d.MemberBegin();
		//rapidjson::Value::ConstMemberIterator enDatablock = d.MemberEnd();

		//while (itDatablock != enDatablock)
		//{
		//	const IdString typeName(itDatablock->name.GetString());

		//	for (int i = 0; i<HLMS_MAX; ++i)
		//	{
		//		Hlms *hlms = mHlmsManager->getHlms(static_cast<HlmsTypes>(i));

		//		if (hlms && typeName == hlms->getTypeName())
		//		{
		//			loadDatablocks(itDatablock->value, blocks, hlms, filename, resourceGroup);
		//		}
		//	}

		//	if (typeName == "compute")
		//	{
		//		HlmsJsonCompute jsonCompute(mHlmsManager);
		//		jsonCompute.loadJobs(itDatablock->value, blocks);
		//	}

		//	++itDatablock;
		//}

		//{
		//	map<LwConstString, const HlmsMacroblock*>::type::const_iterator it =
		//		blocks.macroblocks.begin();
		//	map<LwConstString, const HlmsMacroblock*>::type::const_iterator en =
		//		blocks.macroblocks.end();

		//	while (it != en)
		//	{
		//		mHlmsManager->destroyMacroblock(it->second);
		//		++it;
		//	}

		//	blocks.macroblocks.clear();
		//}
		//{
		//	map<LwConstString, const HlmsBlendblock*>::type::const_iterator it =
		//		blocks.blendblocks.begin();
		//	map<LwConstString, const HlmsBlendblock*>::type::const_iterator en =
		//		blocks.blendblocks.end();

		//	while (it != en)
		//	{
		//		mHlmsManager->destroyBlendblock(it->second);
		//		++it;
		//	}

		//	blocks.blendblocks.clear();
		//}
		//{
		//	map<LwConstString, const HlmsSamplerblock*>::type::const_iterator it =
		//		blocks.samplerblocks.begin();
		//	map<LwConstString, const HlmsSamplerblock*>::type::const_iterator en =
		//		blocks.samplerblocks.end();

		//	while (it != en)
		//	{
		//		mHlmsManager->destroySamplerblock(it->second);
		//		++it;
		//	}

		//	blocks.samplerblocks.clear();
		//}

		Ogre::PackedTexture packedTextures[Ogre::NUM_PBSM_TEXTURE_TYPES];

		if (gltfMaterial.pbr.baseColorTexture.index != -1) 
		{
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.pbr.baseColorTexture.index];  //https://github.com/Lugdunum3D/Lugdunum/blob/f4855b05b349daf5257d248742c8372929593e19/src/lug/Graphics/GltfLoader.cpp
		//	auto fileuri = asset.images[gltfTexture.source].uri;

			//Load samplerblock
			const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];
			const Ogre::HlmsSamplerblock* samplerblock = mHlmsManager->_getSamplerblock(0);
			loadSampler(sampler, samplerblock);
			
			loadTexture(asset, gltfMaterial, samplerblock, Ogre::PBSM_DIFFUSE, gltfMaterial.pbr.baseColorTexture.index, pbsDatablock, packedTextures);

			pbsDatablock->setDiffuse(Ogre::Vector3(gltfMaterial.pbr.baseColorFactor[0]
				, gltfMaterial.pbr.baseColorFactor[1]
				, gltfMaterial.pbr.baseColorFactor[2])); 

			//TODO pbsDatablock->setBackgroundDiffuse(parseColourValueArray(itor->value));*/
		}

		/*itor = json.FindMember("specular");
		if (itor != json.MemberEnd() && itor->value.IsObject())*/
		//if (gltfMaterial.pbr..index != -1) {
		//	
		//	const rapidjson::Value &subobj = itor->value;
		//	loadTexture(subobj, blocks, PBSM_SPECULAR, pbsDatablock, packedTextures);

		//	//itor = subobj.FindMember("value");
		//	//if (itor != subobj.MemberEnd() && itor->value.IsArray())
		//	//
		//	//	pbsDatablock->setSpecular(//parseVector3Array(itor->value));
		//	//		Ogre::Vector3(gltfMaterial.pbr.[0]
		//	//			, gltfMaterial.pbr.baseColorFactor[1]
		//	//			, gltfMaterial.pbr.baseColorFactor[2]));
		//}

		//itor = json.FindMember("roughness");
		//if (itor != json.MemberEnd() && itor->value.IsObject())
		if (gltfMaterial.pbr.metallicRoughnessTexture.index != -1)
		{
			//const rapidjson::Value &subobj = itor->value;
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.pbr.metallicRoughnessTexture.index];  //https://github.com/Lugdunum3D/Lugdunum/blob/f4855b05b349daf5257d248742c8372929593e19/src/lug/Graphics/GltfLoader.cpp

			auto fileuri = asset.images[gltfTexture.source].uri;

			//--------------->TODO			loadTexture(asset, gltfMaterial, Ogre::PBSM_ROUGHNESS, gltfMaterial.pbr.baseColorTexture.index, pbsDatablock, packedTextures);
			//loadTexture(subobj, blocks, Ogre::PBSM_ROUGHNESS, pbsDatablock, packedTextures);
			//Load samplerblock
			const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];
			const Ogre::HlmsSamplerblock* samplerblock = mHlmsManager->_getSamplerblock(gltfMaterial.pbr.metallicRoughnessTexture.index);
			loadSampler(sampler, samplerblock);

		//	loadTexture(asset, gltfMaterial, samplerblock, Ogre::PBSM_METALLIC, gltfMaterial.pbr.metallicRoughnessTexture.index, pbsDatablock, packedTextures);
			loadTexture(asset, gltfMaterial, samplerblock, Ogre::PBSM_SPECULAR, gltfMaterial.pbr.metallicRoughnessTexture.index, pbsDatablock, packedTextures);
		
			
			pbsDatablock->setRoughness(gltfMaterial.pbr.roughnessFactor);
			pbsDatablock->setMetalness(gltfMaterial.pbr.metallicFactor); //static_cast<float>(itor->value.GetDouble()));

			/*itor = subobj.FindMember("value");
			if (itor != subobj.MemberEnd() && itor->value.IsNumber())
				pbsDatablock->setRoughness(static_cast<float>(itor->value.GetDouble()));*/
		}

		/*itor = json.FindMember("fresnel");
		if (itor != json.MemberEnd() && itor->value.IsObject())
		{
			const rapidjson::Value &subobj = itor->value;
			loadTexture(subobj, blocks, PBSM_SPECULAR, pbsDatablock, packedTextures);

			bool useIOR = false;
			bool isColoured = false;
			itor = subobj.FindMember("mode");
			if (itor != subobj.MemberEnd() && itor->value.IsString())
				parseFresnelMode(itor->value.GetString(), isColoured, useIOR);

			itor = subobj.FindMember("value");
			if (itor != subobj.MemberEnd() && (itor->value.IsArray() || itor->value.IsNumber()))
			{
				Vector3 value;
				if (itor->value.IsArray())
					value = parseVector3Array(itor->value);
				else
					value = static_cast<Real>(itor->value.GetDouble());

				if (!useIOR)
					pbsDatablock->setFresnel(value, isColoured);
				else
					pbsDatablock->setIndexOfRefraction(value, isColoured);
			}
		}*/

		if (gltfMaterial.occlusionTexture.index != -1)
		{
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.occlusionTexture.index]; 
			//	auto fileuri = asset.images[gltfTexture.source].uri;

			 //Load samplerblock
			const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];
			const Ogre::HlmsSamplerblock* samplerblock = mHlmsManager->_getSamplerblock(gltfMaterial.occlusionTexture.index);
			loadSampler(sampler, samplerblock);
			
			pbsDatablock->setDetailMapBlendMode(0, Ogre::PbsBlendModes::PBSM_BLEND_SUBTRACT);
			pbsDatablock->setDetailMapWeight(0, 0.32);

			loadTexture(asset, gltfMaterial, samplerblock, Ogre::PBSM_DETAIL0, gltfMaterial.occlusionTexture.index, pbsDatablock, packedTextures);
		}

		if (gltfMaterial.emissiveTexture.index != -1)
		{
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.emissiveTexture.index];
			//	auto fileuri = asset.images[gltfTexture.source].uri;

			//Load samplerblock
			const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];
			const Ogre::HlmsSamplerblock* samplerblock = mHlmsManager->_getSamplerblock(gltfMaterial.emissiveTexture.index);
			loadSampler(sampler, samplerblock);

			pbsDatablock->setEmissive(Ogre::Vector3(gltfMaterial.emissiveFactor[0], gltfMaterial.emissiveFactor[1], gltfMaterial.emissiveFactor[2])); 
		//	pbsDatablock->setDetailMapBlendMode(1,Ogre::PbsBlendModes::PBSM_BLEND_ADD);
		//	pbsDatablock->setDetailMapWeight(1, 6);

			loadTexture(asset, gltfMaterial, samplerblock, Ogre::PBSM_EMISSIVE, gltfMaterial.emissiveTexture.index, pbsDatablock, packedTextures);
		}

		//There used to be a typo, so allow the wrong spelling.
		//itor = json.FindMember("metalness");
		//if (itor == json.MemberEnd())
		//	itor = json.FindMember("metallness");

		//if (gltfMaterial.pbr.metallicRoughnessTexture.index != -1)
		//	//	if (itor != json.MemberEnd() && itor->value.IsObject())
		//{
		//	//const rapidjson::Value &subobj = itor->value;
		//	//loadTexture(subobj, blocks, PBSM_METALLIC, pbsDatablock, packedTextures);
		//	const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.pbr.metallicRoughnessTexture.index];  //https://github.com/Lugdunum3D/Lugdunum/blob/f4855b05b349daf5257d248742c8372929593e19/src/lug/Graphics/GltfLoader.cpp

		//	auto fileuri = asset.images[gltfTexture.source].uri;

		//	//--------------->TODO		loadTexture(asset, gltfMaterial,  Ogre::PBSM_METALLIC, gltfMaterial.pbr.metallicRoughnessTexture.index, pbsDatablock, packedTextures);
		//	const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];
		//	auto samplerblock = mHlmsManager->_getSamplerblock(gltfMaterial.pbr.metallicRoughnessTexture.index);
		//	loadSampler(sampler, samplerblock);

		//	loadTexture(asset, gltfMaterial, samplerblock, Ogre::PBSM_METALLIC, gltfMaterial.pbr.metallicRoughnessTexture.index, pbsDatablock, packedTextures);

		//			/*itor = subobj.FindMember("value");
		//			if (itor != subobj.MemberEnd() && itor->value.IsNumber())*/
		//	pbsDatablock->setMetalness(gltfMaterial.pbr.metallicFactor); //static_cast<float>(itor->value.GetDouble()));
		//}

		if (gltfMaterial.normalTexture.index != -1)
			/*itor = json.FindMember("normal");
			if (itor != json.MemberEnd() && itor->value.IsObject())*/
		{
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.normalTexture.index];
			auto fileuri = asset.images[gltfTexture.source].uri;
		
			//--------------->TODO	loadTexture(asset, gltfMaterial,  Ogre::PBSM_NORMAL, gltfMaterial.normalTexture.index, pbsDatablock, packedTextures);
			const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];
			auto samplerblock = mHlmsManager->_getSamplerblock(3);
			loadSampler(sampler, samplerblock);

			loadTexture(asset, gltfMaterial, samplerblock, Ogre::PbsTextureTypes::PBSM_NORMAL, gltfMaterial.normalTexture.index, pbsDatablock, packedTextures);
			pbsDatablock->setNormalMapWeight(1.0);

			/*const rapidjson::Value &subobj = itor->value;
			loadTexture(subobj, blocks, PBSM_NORMAL, pbsDatablock, packedTextures);*/

			//itor = subobj.FindMember("value");
			//if (itor != subobj.MemberEnd() && itor->value.IsNumber())
			//	pbsDatablock->setNormalMapWeight(gltfMaterial. //static_cast<float>(itor->value.GetDouble()));
		}

		/*itor = json.FindMember("detail_weight");
		if (itor != json.MemberEnd() && itor->value.IsObject())
		{
			const rapidjson::Value &subobj = itor->value;
			loadTexture(subobj, blocks, PBSM_DETAIL_WEIGHT, pbsDatablock, packedTextures);
		}

		for (int i = 0; i<4; ++i)
		{
			const String iAsStr = StringConverter::toString(i);
			String texTypeName = "detail_diffuse" + iAsStr;

			itor = json.FindMember(texTypeName.c_str());
			if (itor != json.MemberEnd() && itor->value.IsObject())
			{
				const rapidjson::Value &subobj = itor->value;
				loadTexture(subobj, blocks, static_cast<PbsTextureTypes>(PBSM_DETAIL0 + i),
					pbsDatablock, packedTextures);

				itor = subobj.FindMember("value");
				if (itor != subobj.MemberEnd() && itor->value.IsNumber())
					pbsDatablock->setDetailMapWeight(i, static_cast<float>(itor->value.GetDouble()));

				itor = subobj.FindMember("mode");
				if (itor != subobj.MemberEnd() && itor->value.IsString())
					pbsDatablock->setDetailMapBlendMode(i, parseBlendMode(itor->value.GetString()));

				Vector4 offsetScale(0, 0, 1, 1);

				itor = subobj.FindMember("offset");
				if (itor != subobj.MemberEnd() && itor->value.IsArray())
					parseOffset(itor->value, offsetScale);

				itor = subobj.FindMember("scale");
				if (itor != subobj.MemberEnd() && itor->value.IsArray())
					parseScale(itor->value, offsetScale);

				pbsDatablock->setDetailMapOffsetScale(i, offsetScale);
			}

			texTypeName = "detail_normal" + iAsStr;
			itor = json.FindMember(texTypeName.c_str());
			if (itor != json.MemberEnd() && itor->value.IsObject())
			{
				const rapidjson::Value &subobj = itor->value;
				loadTexture(subobj, blocks, static_cast<PbsTextureTypes>(PBSM_DETAIL0_NM + i),
					pbsDatablock, packedTextures);

				itor = subobj.FindMember("value");
				if (itor != subobj.MemberEnd() && itor->value.IsNumber())
				{
					pbsDatablock->setDetailNormalWeight(i,
						static_cast<float>(itor->value.GetDouble()));
				}

				Vector4 offsetScale(0, 0, 1, 1);

				itor = subobj.FindMember("offset");
				if (itor != subobj.MemberEnd() && itor->value.IsArray())
					parseOffset(itor->value, offsetScale);

				itor = subobj.FindMember("scale");
				if (itor != subobj.MemberEnd() && itor->value.IsArray())
					parseScale(itor->value, offsetScale);

				pbsDatablock->setDetailMapOffsetScale(i + 4, offsetScale);
			}
		}*/

		/*itor = json.FindMember("reflection");
		if (itor != json.MemberEnd() && itor->value.IsObject())
		{
			const rapidjson::Value &subobj = itor->value;
			loadTexture(subobj, blocks, PBSM_REFLECTION, pbsDatablock, packedTextures);
		}*/

		pbsDatablock->_setTextures(packedTextures);
	}

	//-----------------------------------------------------------------------------------
	void XEMaterial::loadTexture(const gltf::Asset& asset, const gltf::Material& gltfMaterial, const Ogre::HlmsSamplerblock* samplerblock,
		Ogre::PbsTextureTypes textureType, int32_t gltfTexIdx, Ogre::HlmsPbsDatablock *datablock,
		Ogre::PackedTexture textures[Ogre::NUM_PBSM_TEXTURE_TYPES])
	{
		const Ogre::HlmsTextureManager::TextureMapType texMapTypes[Ogre::NUM_PBSM_TEXTURE_TYPES] =
		{
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_NORMALS,

			datablock->getWorkflow() == Ogre::HlmsPbsDatablock::MetallicWorkflow
			? Ogre::HlmsTextureManager::TEXTURE_TYPE_MONOCHROME
			: Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE,

			Ogre::HlmsTextureManager::TEXTURE_TYPE_MONOCHROME,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_NON_COLOR_DATA,
#ifdef OGRE_TEXTURE_ATLAS
			HlmsTextureManager::TEXTURE_TYPE_DETAIL,
			HlmsTextureManager::TEXTURE_TYPE_DETAIL,
			HlmsTextureManager::TEXTURE_TYPE_DETAIL,
			HlmsTextureManager::TEXTURE_TYPE_DETAIL,
			HlmsTextureManager::TEXTURE_TYPE_DETAIL_NORMAL_MAP,
			HlmsTextureManager::TEXTURE_TYPE_DETAIL_NORMAL_MAP,
			HlmsTextureManager::TEXTURE_TYPE_DETAIL_NORMAL_MAP,
			HlmsTextureManager::TEXTURE_TYPE_DETAIL_NORMAL_MAP,
#else
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_NORMALS,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_NORMALS,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_NORMALS,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_NORMALS,
#endif
			Ogre::HlmsTextureManager::TEXTURE_TYPE_ENV_MAP
		};

		//rapidjson::Value::ConstMemberIterator itor = json.FindMember("texture");
		/*if (itor != json.MemberEnd() && itor->value.IsString())
		{*/

		const gltf::Texture& gltfTexture = asset.textures[gltfTexIdx];
		auto fileuri = asset.images[gltfTexture.source].uri;

		const char *textureName = fileuri.c_str(); // itor->value.GetString();

		Ogre::HlmsTextureManager *hlmsTextureManager = mHlmsManager->getTextureManager();
		Ogre::HlmsTextureManager::TextureLocation texLocation = hlmsTextureManager->
			createOrRetrieveTexture(textureName,
				texMapTypes[textureType]);

		assert(texLocation.texture->isTextureTypeArray() || textureType == Ogre::PBSM_REFLECTION);

		//If HLMS texture manager failed to find a reflection
		//texture, have look in standard texture manager.
		//NB we only do this for reflection textures as all other
		//textures must be texture arrays for performance reasons
		if (textureType == Ogre::PBSM_REFLECTION &&
			texLocation.texture == hlmsTextureManager->getBlankTexture().texture)
		{
			Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName(textureName);
			if (tex.isNull() == false)
			{
				texLocation.texture = tex;
				texLocation.xIdx = 0;
				texLocation.yIdx = 0;
				texLocation.divisor = 1;
			}
		}

		textures[textureType].texture = texLocation.texture;
		textures[textureType].xIdx = texLocation.xIdx;
		//	}


			//itor = json.FindMember("sampler");
			//if (itor != json.MemberEnd() && itor->value.IsString())
			//{
			//if (gltfTexture.sampler != -1) {
			//		const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];
			//		
			//		
			//		Ogre::map<Ogre::LwConstString, const Ogre::HlmsSamplerblock*>::type::const_iterator it =
			//			blocks.samplerblocks.find(Ogre::LwConstString::FromUnsafeCStr("Sampler 2")); // itor->value.GetString()));
			//	
			//		if (it != blocks.samplerblocks.end())
			//	{
		textures[textureType].samplerblock = samplerblock;
		mHlmsManager->addReference(textures[textureType].samplerblock);
		/*}
	}*/

	/*itor = json.FindMember("uv");
	if (itor != json.MemberEnd() && itor->value.IsUint())
	{
		unsigned uv = itor->value.GetUint();
		datablock->setTextureUvSource(textureType, static_cast<Ogre::uint8>(uv));
	}*/
	}

}