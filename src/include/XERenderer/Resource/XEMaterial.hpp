#pragma once


//#include "OgreHlmsPbsPrerequisites.h"
//#include "OgreHlmsJson.h"
#include "OgreHlmsPbsDatablock.h"

namespace gltf {

	struct Asset;
	struct Material;
}

namespace Ogre {
//	class SceneManager;
//	class HlmsDatablock;
//	class HlmsManager;
//	struct HlmsSamplerblock;
////	class HlmsJson;
//	enum PbsTextureTypes;
//	class HlmsPbsDatablock;
//	struct PackedTexture;
}

namespace XE
{

	/** \addtogroup Component
	*  @{
	*/
	/** \addtogroup Material
	*  @{
	*/
	class XEMaterial // HlmsJsonPbs
	{
		Ogre::HlmsManager *mHlmsManager;

		//static HlmsPbsDatablock::Workflows parseWorkflow(const char *value);
		//static PbsBrdf::PbsBrdf parseBrdf(const char *value);
		/*static HlmsPbsDatablock::TransparencyModes parseTransparencyMode(const char *value);
		static PbsBlendModes parseBlendMode(const char *value);
		static void parseFresnelMode(const char *value, bool &outIsColoured, bool &outUseIOR);
		static void parseOffset(const rapidjson::Value &jsonArray, Vector4 &offsetScale);
		static void parseScale(const rapidjson::Value &jsonArray, Vector4 &offsetScale);

		static inline Vector3 parseVector3Array(const rapidjson::Value &jsonArray);
		static inline ColourValue parseColourValueArray(
		const rapidjson::Value &jsonArray,
		const ColourValue &defaultValue = ColourValue::White);*/

		void loadTexture(const gltf::Asset& asset, const gltf::Material& gltfMaterial,
			Ogre::PbsTextureTypes textureType, int32_t gltfTexIdx, Ogre::HlmsPbsDatablock *datablock,
			Ogre::PackedTexture textures[Ogre::NUM_PBSM_TEXTURE_TYPES]);

		//static void toQuotedStr(HlmsPbsDatablock::Workflows value, String &outString);
		//static void toQuotedStr(uint32 value, String &outString);
		//static void toQuotedStr(HlmsPbsDatablock::TransparencyModes value, String &outString);

	public:
		XEMaterial(Ogre::HlmsManager *hlmsManager);

		void loadMaterial(const gltf::Asset& asset, const gltf::Material& gltfMaterial,
			Ogre::HlmsDatablock *datablock);

		static void collectSamplerblocks(const Ogre::HlmsDatablock *datablock,
			Ogre::set<const Ogre::HlmsSamplerblock*>::type &outSamplerblocks);
	};

	/** @} */
	/** @} */

}