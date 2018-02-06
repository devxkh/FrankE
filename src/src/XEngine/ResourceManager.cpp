#include <XEngine/ResourceManager.hpp>

#include <Ogre/OgreMain/include/OgreSingleton.h>
#include <Ogre/OgreMain/include/OgreResourceGroupManager.h>

#include <XEDAL/PhysFS/PhysFsStream.hpp>

#include <ThirdParty/plog/Log.h>

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

	void ResourceManager::getBufferFromFile(const std::string& filePath, FileResource& res)
	{
		PhysFsStream wonderfullStream;
		if (wonderfullStream.open(filePath.c_str()))//"UI/TestAtlas.fbbin"))
		{
			// Make sure that the stream's reading position is at the beginning
			wonderfullStream.seek(0);

			//std::unique_ptr<std::vector<char>> buffer(new std::vector<char>(wonderfullStream.getSize()));
			//std::vector<char> buffer(wonderfullStream.getSize());
			//if (wonderfullStream.read(buffer->data(), wonderfullStream.getSize()))
			res.bufferVec.resize(wonderfullStream.getSize());
			if (wonderfullStream.read(res.bufferVec.data(), wonderfullStream.getSize()))
			{
				res.buffer = &res.bufferVec[0];
			}
		}
		else
		{
			LOG(plog::error) << "GUIRenderer::getBufferFromFile -> atlasfile not found: " << filePath;
			//return false;
		}
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