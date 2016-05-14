#ifndef XE_SPAWNER_OBJECT_HPP
#define XE_SPAWNER_OBJECT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <XEGraphics.hpp>
#include <XEScene/XESceneObject.hpp>

namespace SM
{

//-----------------------------------------------------------------------------
// Spawner Object Type Define
//
// A derived scene object for supporting spawner objects. A spawner is an
// object that spawns other objects into the scene.
//-----------------------------------------------------------------------------
#define TYPE_SPAWNER_OBJECT 2

//-----------------------------------------------------------------------------
// Spawner Object Class
//-----------------------------------------------------------------------------
class XESpawnerObject : public XESceneObject
{
public:
	XESpawnerObject( char *name, char *path = "./", unsigned long type = TYPE_SPAWNER_OBJECT );
	virtual ~XESpawnerObject();

	virtual void Update( float elapsed, bool addVelocity = true );

	//virtual void CollisionOccurred( SceneObject *object, unsigned long collisionStamp );

	//Script *GetObjectScript();

private:
	char *m_name; // Name of the object that is spawned at this spawner.
	float m_frequency; // How often the spawner spawns its object (in seconds).
	float m_spawnTimer; // Timer used for spawning the object.
	//Sound *m_sound; // Sound to play when the object is collected.
	//AudioPath3D *m_audioPath; // Audio path to play the sound on.
	//Script *m_objectScript; // Script for the spawner's object.
};

} //namespace SM

#endif //SPAWNER_OBJECT_HPP