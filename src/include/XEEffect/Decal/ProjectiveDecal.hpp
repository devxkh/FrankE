#ifndef ProjectiveDecal_H
#define ProjectiveDecal_H

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreVector2.h>

namespace OgreDecal {

class TerrainDecal
{
protected:
	Ogre::Vector3 mPos;            // center
	Ogre::Vector2 mSize;        // size of decal

	std::string mTexture;        // texture to apply

	Ogre::SceneNode* mNode;        // the projection node
	Ogre::Frustum* mFrustum;    // the projection frustum

	Ogre::SceneManager* mSceneManager;    // pointer to PLSM2

	bool mVisible;                // is the decal visible/active or not?

	// info about materials that are receiving the decal
	std::map<std::string, Ogre::Pass*> mTargets;            // passes mapped by material names

	bool isPosOnTerrain(Ogre::Vector3 pos);

	std::string getMaterialAtPosition(Ogre::Vector3 pos);

	void addMaterial(std::string matName);

	std::map<std::string, Ogre::Pass*>::iterator removeMaterial(std::string matName);

public:
	TerrainDecal();

	~TerrainDecal();

	void init(Ogre::SceneManager* man, Ogre::Vector2 size, std::string tex);

	void show();

	void hide();

	void updatePosition(Ogre::Vector3 pos);

	void updateSize(Ogre::Vector2 size);

	bool isVisible();
};

} // ns OgreDecal

#endif // ProjectiveDecal_H