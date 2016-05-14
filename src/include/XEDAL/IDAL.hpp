#ifndef __IDAL_H__
#define __IDAL_H__

#include <XEDAL/DB.hpp>
#include <sfml/Config.hpp>
#include <XEDAL/Objects/FBEngineTypes_generated.h>


namespace XE {

	class Scene;


	typedef int(*sceneNodes_callback)(Scene& scenePointer, sf::Int32 entID, char* entityData, bool replicateEntity);

	class IDAL : public DB
	{

	public:
		struct BinaryResult
		{
		public:
			const void* binData;
			int len;
		};

		IDAL();
		~IDAL();
		
		//void setGameEntityProperties(Ogre::uint16 id, GameEntityProperties& props);
		//void setPhysicProperties(Ogre::uint16 id, gkPhysicsProperties& props);
		//void  getPhysicsProperties(Ogre::uint16 id, gkPhysicsProperties& props);
		//void getGameEntityProperties(Ogre::uint16 id, GameEntityProperties& props);
		void LoadFBJson(const std::string& schemafilePath, const std::string& jsonfilePath, BinaryResult& result);
		
		const void* getState(const char* name, int namelen);
		//void getRaceData(Ogre::uint16 sceneID, RaceMap& raceMap);
		void getSceneNodes(Scene& scene, sf::Uint16 sceneID, sceneNodes_callback xCallback);
		char*  getScene(sf::Uint16 id);
		char*  getEntity(sf::Uint16 id);

	
	};

} // ns XE

#endif // __DBI_H__