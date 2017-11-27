#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <XESystem/SystemConfig.hpp>
#include <XEEffect/Decal/OgreDecal.hpp>
//#include <XEEffect/Decal/BulletMesh.hpp>
//#include <ThirdParty/selene/selene.h>
//#include <XEDAL/IDALObject.hpp>

#include <XESystem/Entityx/entityx.h>

#include <memory>

namespace XFBType
{
	class Node;
}
namespace sol
{
	class state;
}

namespace XE {

	//forwarding
	class GameEntity;
	class AIEntity;
	class CharEntity;
	class GraphicsManager;
	class IDAL;
	class XEngine;
	class SceneListener;
	class OgreSceneManager;

	class Scene : public  entityx::EntityX
{

public:
	Scene(XEngine& engine, IDAL& idal, GraphicsManager& gmanager);
	~Scene();

	void registerObject(sol::state& lua);

	//IDALObject load/create functions
	void create(Uint16 sceneID, void* fbData = nullptr);
	void reload(void* fbData = nullptr);

	void createT(Uint16 sceneID) {}

	entityx::Entity  createEntityWithId(Uint16 entityID, bool replicateEntity);


	Uint16 getSceneID() {return m_sceneID;}

//KH	inline void setTerrain(Ogre::TerrainGroup* terrainGrp) { mTerrainGrp = terrainGrp; }
	virtual void update(float deltaTime);

	virtual void loadRendererResources() {};
	virtual void loadResources() {};

	//inline OgreDecal::BulletMesh& getWorldMesh() { return mWorldMesh; }
	inline DecalGenerator& getDecalGenerator() { return mDecalGenerator; }
//	void initDecalGenerator(btCollisionObject* meshPtr);

	virtual entityx::Entity createEntity(Int32 entityID, void* entityData, bool replicateEntity);
	static int callbackNewNode(Scene& scenePointer, Int32 entityID, char* entityData, bool replicateEntity);

	XEngine& getEngine() { return m_engine;  }
	void collision();

	GraphicsManager& getGraphicsManager() { return mGraphicsManager; }
	OgreSceneManager& getOgreSceneManager() { return m_OgreSceneManager; }

	void addListener(std::unique_ptr<SceneListener> obs);
	void removeListener(std::unique_ptr<SceneListener> obs);

	Uint16 nextRenderableID();

	void createSoundComponent( entityx::Entity entity, Uint16 scendId, const void* fbData);
	void updateSoundComponent( entityx::Entity entity, Uint16 scendId, const void* fbData);

	void createPhysicsComponent( entityx::Entity entity, Uint16 scendId, const void* fbData);
	void updatePhysicsComponent( entityx::Entity entity, Uint16 scendId, const void* fbData);

	//from network
	void createRenderableComponent( entityx::Entity entity, Uint16 scendId, const void* fbData);
	void updateRenderableComponent( entityx::Entity entity, Uint16 scendId, const void* fbData);

	void createBodyComponent( entityx::Entity entity, const void* fbData);
	void updateBodyComponent( entityx::Entity entity, const void* fbData);

	//from network
	void updateScene(Uint16 scendId, const void* fbData);

	void createSpawnPointComponent( entityx::Entity entity, const void* fbData);
	void updateSpawnPointComponent( entityx::Entity entity, const void* fbData);
	
	void createSpawnComponent(entityx::Entity entity, const void* fbData);
	void updateSpawnComponent(entityx::Entity entity, const void* fbData);

	void createLightComponent( entityx::Entity entity, const void* fbData);
	void updateLightComponent( entityx::Entity entity, const void* fbData);

	void createAnimationComponent( entityx::Entity entity, const void* fbData);
	void updateAnimationComponent( entityx::Entity entity, const void* fbData);
	
	bool createEntity(entityx::Entity entity,  Uint16 sceneID, Uint32 entityID, void* entityData, bool replicateEntity = false);

	Ogre::ColourValue ambientColor;

protected:

	virtual bool createEntityType(entityx::Entity entity, void* entityData) { return false; };

	XEngine& m_engine;
	IDAL& m_IDAL;
	DecalGenerator mDecalGenerator;
	GraphicsManager& mGraphicsManager;
	OgreSceneManager& m_OgreSceneManager;
	Uint16 m_sceneID;

private:
	std::vector<std::unique_ptr<SceneListener>> _listenerVector;
	
	Uint16 _renderableCount;

	//KH	Ogre::TerrainGroup* mTerrainGrp;
	bool mTerrainImported;
//geht!!!	OgreDecal::BulletMesh mWorldMesh;
};

class SceneListener
{
public:
	virtual void entityAdded(entityx::Entity entity) = 0;
	virtual void entityRemoved(entityx::Entity entity) = 0;
};

} // namespace XE

#endif // __SCENE_HPP__