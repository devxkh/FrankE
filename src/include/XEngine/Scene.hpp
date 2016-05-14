#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <XESystem/SystemConfig.hpp>
#include <XEEffect/Decal/OgreDecal.hpp>
//#include <XEEffect/Decal/BulletMesh.hpp>
//#include <ThirdParty/selene/selene.h>
#include <XEDAL/IDALObject.hpp>

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

	class Scene : IDALObject, public  entityx::EntityX
{

public:
	Scene(XEngine& engine, IDAL& idal, GraphicsManager& gmanager);
	~Scene();

	void registerObject(sol::state& lua);

	//IDALObject load/create functions
	void create(XE::Uint16 sceneID, char* fbData = nullptr);
	void reload(char* fbData = nullptr);

	void createT(XE::Uint16 sceneID) {}

	XE::Uint16 getSceneID() {return m_sceneID;}

//KH	inline void setTerrain(Ogre::TerrainGroup* terrainGrp) { mTerrainGrp = terrainGrp; }
	virtual void update(float deltaTime);

	//inline OgreDecal::BulletMesh& getWorldMesh() { return mWorldMesh; }
	inline DecalGenerator& getDecalGenerator() { return mDecalGenerator; }
//	void initDecalGenerator(btCollisionObject* meshPtr);

	virtual void createEntity(XE::Int32 entityID, char* entityData, bool replicateEntity);
	static int callbackNewNode(Scene& scenePointer, XE::Int32 entityID, char* entityData, bool replicateEntity);

	XEngine& getEngine() { return m_engine;  }
	void collision();

	GraphicsManager& getGraphicsManager() { return mGraphicsManager; }
	OgreSceneManager& getOgreSceneManager() { return m_OgreSceneManager; }

	void addListener(std::unique_ptr<SceneListener> obs);
	void removeListener(std::unique_ptr<SceneListener> obs);

	XE::Uint16 nextRenderableID();

	void createSoundComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData);
	void updateSoundComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData);

	void createPhysicsComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData);
	void updatePhysicsComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData);

	//from network
	void createRenderableComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData);
	void updateRenderableComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData);

	void createBodyComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData);
	void updateBodyComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData);

	//from network
	void createScene(XE::XEngine& engine, const void* fbData);
	void updateScene(XE::XEngine& engine, XE::Uint16 scendId, const void* fbData);

	void createSpawnPointComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData);
	void updateSpawnPointComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData);

	void createLightComponent(XE::XEngine& engine, entityx::Entity entity, XE::Uint16 scendId, const void* fbData);
	void updateLightComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData);

	void createAnimationComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData);
	void updateAnimationComponent(XE::XEngine& engine, entityx::Entity entity, const void* fbData);
	
	bool createEntity(entityx::Entity entity, XE::XEngine& engine, XE::Uint16 sceneID, XE::Uint32 entityID, char* entityData, bool replicateEntity = false);

	Ogre::ColourValue ambientColor;

protected:

	virtual bool createEntityType(entityx::Entity entity, char* entityData) { return false; };

	XEngine& m_engine;
	IDAL& m_IDAL;
	DecalGenerator mDecalGenerator;
	GraphicsManager& mGraphicsManager;
	OgreSceneManager& m_OgreSceneManager;
	XE::Uint16 m_sceneID;

private:
	std::vector<std::unique_ptr<SceneListener>> _listenerVector;
	
	XE::Uint16 _renderableCount;

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