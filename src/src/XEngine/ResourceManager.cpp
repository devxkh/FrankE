#include <XEngine/ResourceManager.hpp>

#include <Ogre/OgreMain/include/OgreSingleton.h>
#include <Ogre/OgreMain/include/OgreResourceGroupManager.h>

namespace XE {

	void ResourceManager::_t_addLocationForRender(const std::string& location, const std::string& group, bool recursive, bool readOnly, const std::string& locType)
	{

		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(location, locType, group, recursive, readOnly);

	}

	void ResourceManager::_t_initResourceGroup(const std::string& nameOfResourceGroup) {
		
		//initialise for gorilla shaders intitialization
		/*std::string lNameOfResourceGroup = "General";
		{*/
			Ogre::ResourceGroupManager& lRgMgr = Ogre::ResourceGroupManager::getSingleton();

			lRgMgr.initialiseResourceGroup(nameOfResourceGroup, false);
			lRgMgr.loadResourceGroup(nameOfResourceGroup);
	//	}
	}


	void ResourceManager::_t_registerHLMSResources()
	{		
			


			//loading
			//GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true); //Make sure it's enabled.
			//DataStreamPtr shaderCacheFile = mRoot->openFileStream("F:/Projekte/coop/XGame/data/MyCache.cache");
			//GpuProgramManager::getSingleton().loadMicrocodeCache(shaderCacheFile);

			//		_t_createCustomTextures(mRoot, _t_RenderWindow);
			//	_t_createExtraEffectsFromCode(mRoot);
	
	}

}