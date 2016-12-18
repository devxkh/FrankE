#pragma once
#ifndef OGREHELPER_H
#define OGREHELPER_H

#include <OgreString.h>

namespace Ogre
{
	class ResourceManager;
}

namespace OgreHelper
{
	void UnloadResource(Ogre::ResourceManager* resMgr, const Ogre::String& resourceName);
	void LoadResource(Ogre::ResourceManager* resMgr, const Ogre::String& resourceName, const Ogre::String& resourceGroup);
	void UnloadMaterials(const Ogre::String& filename);
	void UnloadVertexPrograms(const Ogre::String& filename);
	void UnloadFragmentPrograms(const Ogre::String& filename);
	void ReloadMaterial(const Ogre::String& materialName, const Ogre::String& groupName, const Ogre::String& filename, bool parseMaterialScript);
	void UpdateSceneManagersForMaterialChange();
}

#endif // OGREHELPER_H
