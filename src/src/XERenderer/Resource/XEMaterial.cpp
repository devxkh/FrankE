#include <XERenderer/Resource/XEMaterial.hpp>

#include <XERenderer/Resource/gltfAsset.h>

//#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsJsonPbs.h>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbsDatablock.h>
#include <Ogre/OgreMain/include/OgreHlmsManager.h>
#include <Ogre/OgreMain/include/OgreHlms.h>
#include <Ogre/OgreMain/include/OgreColourValue.h>
#include <Ogre/OgreMain/include/OgreHlmsTextureManager.h>
#include <Ogre/OgreMain/include/OgreTextureManager.h>


namespace XE
{

	XEMaterial::XEMaterial(Ogre::HlmsManager *hlmsManager)
		: mHlmsManager(hlmsManager)
	{


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

		Ogre::PackedTexture packedTextures[Ogre::NUM_PBSM_TEXTURE_TYPES];

		//itor = json.FindMember("diffuse");

		if (gltfMaterial.pbr.baseColorTexture.index != -1) //itor != json.MemberEnd() && itor->value.IsObject())
		{
			//const rapidjson::Value &subobj = itor->value;
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.pbr.baseColorTexture.index];  //https://github.com/Lugdunum3D/Lugdunum/blob/f4855b05b349daf5257d248742c8372929593e19/src/lug/Graphics/GltfLoader.cpp

			auto fileuri = asset.images[gltfTexture.source].uri;

			loadTexture(asset, gltfMaterial, Ogre::PBSM_DIFFUSE, gltfMaterial.pbr.baseColorTexture.index, pbsDatablock, packedTextures);

			/*itor = subobj.FindMember("value");
			if (itor != subobj.MemberEnd() && itor->value.IsArray())*/
			pbsDatablock->setDiffuse(Ogre::Vector3(gltfMaterial.pbr.baseColorFactor[0]
				, gltfMaterial.pbr.baseColorFactor[1]
				, gltfMaterial.pbr.baseColorFactor[2])); // parseVector3Array(itor->value));

/*itor = subobj.FindMember("background");
if (itor != subobj.MemberEnd() && itor->value.IsArray())
	pbsDatablock->setBackgroundDiffuse(parseColourValueArray(itor->value));*/
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
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.pbr.baseColorTexture.index];  //https://github.com/Lugdunum3D/Lugdunum/blob/f4855b05b349daf5257d248742c8372929593e19/src/lug/Graphics/GltfLoader.cpp

			auto fileuri = asset.images[gltfTexture.source].uri;

			loadTexture(asset, gltfMaterial, Ogre::PBSM_ROUGHNESS, gltfMaterial.pbr.baseColorTexture.index, pbsDatablock, packedTextures);
			//loadTexture(subobj, blocks, Ogre::PBSM_ROUGHNESS, pbsDatablock, packedTextures);

			pbsDatablock->setRoughness(gltfMaterial.pbr.roughnessFactor);

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

		//There used to be a typo, so allow the wrong spelling.
		//itor = json.FindMember("metalness");
		//if (itor == json.MemberEnd())
		//	itor = json.FindMember("metallness");

		if (gltfMaterial.pbr.metallicRoughnessTexture.index != -1)
	//	if (itor != json.MemberEnd() && itor->value.IsObject())
		{
			//const rapidjson::Value &subobj = itor->value;
			//loadTexture(subobj, blocks, PBSM_METALLIC, pbsDatablock, packedTextures);
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.pbr.metallicRoughnessTexture.index];  //https://github.com/Lugdunum3D/Lugdunum/blob/f4855b05b349daf5257d248742c8372929593e19/src/lug/Graphics/GltfLoader.cpp

			auto fileuri = asset.images[gltfTexture.source].uri;

			loadTexture(asset, gltfMaterial,  Ogre::PBSM_METALLIC, gltfMaterial.pbr.metallicRoughnessTexture.index, pbsDatablock, packedTextures);

			/*itor = subobj.FindMember("value");
			if (itor != subobj.MemberEnd() && itor->value.IsNumber())*/
			pbsDatablock->setMetalness(gltfMaterial.pbr.metallicFactor); //static_cast<float>(itor->value.GetDouble()));
		}

		if (gltfMaterial.normalTexture.index != -1)
		/*itor = json.FindMember("normal");
		if (itor != json.MemberEnd() && itor->value.IsObject())*/
		{
			const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.normalTexture.index];
			auto fileuri = asset.images[gltfTexture.source].uri;
			loadTexture(asset, gltfMaterial,  Ogre::PBSM_NORMAL, gltfMaterial.normalTexture.index, pbsDatablock, packedTextures);

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
	void XEMaterial::loadTexture(const gltf::Asset& asset, const gltf::Material& gltfMaterial, 
		Ogre::PbsTextureTypes textureType, int32_t gltfTexIdx, Ogre::HlmsPbsDatablock *datablock,
		Ogre::PackedTexture textures[Ogre::NUM_PBSM_TEXTURE_TYPES])
	{
		const Ogre::HlmsTextureManager::TextureMapType texMapTypes[Ogre::NUM_PBSM_TEXTURE_TYPES] =
		{
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_NORMALS,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_MONOCHROME,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_NON_COLOR_DATA,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DETAIL,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DETAIL,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DETAIL,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DETAIL,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DETAIL_NORMAL_MAP,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DETAIL_NORMAL_MAP,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DETAIL_NORMAL_MAP,
			Ogre::HlmsTextureManager::TEXTURE_TYPE_DETAIL_NORMAL_MAP,
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
		/*if (gltfTexture.sampler != -1) {
				const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];
				
				
				Ogre::map<Ogre::LwConstString, const Ogre::HlmsSamplerblock*>::type::const_iterator it =
				blocks.samplerblocks.find(Ogre::LwConstString::FromUnsafeCStr(itor->value.GetString()));
			
				if (it != blocks.samplerblocks.end())
			{
				textures[textureType].samplerblock = it->second;
				mHlmsManager->addReference(textures[textureType].samplerblock);
			}
		}

		itor = json.FindMember("uv");
		if (itor != json.MemberEnd() && itor->value.IsUint())
		{
			unsigned uv = itor->value.GetUint();
			datablock->setTextureUvSource(textureType, static_cast<Ogre::uint8>(uv));
		}*/
	}

}