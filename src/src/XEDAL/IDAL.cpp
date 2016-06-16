#include <XEDAL/IDAL.hpp>
//#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
//#include <XEPhysics/Physics/gkCharacter.h>
#include <Ogre/OgreMain/include/OgreLogManager.h>

#include <Ogre/OgreMain/include/OgreStreamSerialiser.h>

#include <Ogre/OgreMain/include/OgreArchive.h>

//#include <XEDAL/Objects/ProtoType.pb.h>

#include <Sqlite/sqlite3.h>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#include <iostream>

namespace XE {

	IDAL::IDAL(XEngine& engine)
		: DB(engine)
	{
	}

	IDAL::~IDAL()
	{
		close();
	}

	void IDAL::open()
	{
		DB::open();
	}
	//void IDAL::getPhysicsProperties(Ogre::uint16 id, gkPhysicsProperties& props)
	//{
	//	
	//
	//}
	//
	//void IDAL::getGameEntityProperties(Ogre::uint16 id, GameEntityProperties& props)
	//{
	//	getPhysicsProperties(id, props.m_physics);
	//
	//	//todo komplette Game entity daten12 !!!
	//	//GameEntityProperties props;
	//
	//	//execute("SELECT * FROM PHYSICOBJECT WHERE PO_ID=0;");
	//	//execute("SELECT * FROM GAMEOBJECT WHERE PO_ID=0;");
	//
	//
	//	//GameEntityProperties& props = this->getProperties();
	//	//props.m_physics.Object.shape = SH_CAPSULE;
	//	//props.m_physics.Object.friction = 1.0f;
	//	//props.m_physics.Object.restitution = 0.0f; //for bouncing
	//	//props.m_physics.Object.colgroupmask = btBroadphaseProxy::CharacterFilter;
	//	//props.m_physics.Object.colmask = btBroadphaseProxy::DefaultFilter;
	//	//props.m_physics.Object.charjumpspeed = 10;
	//	//props.m_physics.Object.charfallspeed = 10;
	//	//props.m_physics.Object.charstepheight = 0.0f;
	//
	//
	//	//return props;
	//}

	//void IDAL::setGameEntityProperties(Ogre::uint16 id, GameEntityProperties& props)
	//{
	//
	//}
	//
	//void IDAL::setPhysicProperties(Ogre::uint16 id, gkPhysicsProperties& props)
	//{
	//
	//}


	//void IDAL::getRaceData(Ogre::uint16 sceneID, RaceMap& raceMap)
	//{
	//	
	//
	//}

	void IDAL::getSceneNodes(Scene& scene, sf::Uint16 sceneID, sceneNodes_callback xCallback)
	{
		//gkPhysicsProperties pProp;

		//Ogre::String strFile;
		//	Ogre::FileInfo** ppInfo;
		//Ogre::String mName = "D:\\Projekte\\Src Game\\Data\\Data_Release\\gameData.s3db";/// Archive name
		//sqlite3* pSQLiteDB;/// SQLite Database Connection
		sqlite3_stmt* pStmt;/// SQLite Prepared statements.
		const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
		std::string SQLStatement;
		int Result = 0;

		// initialize engine
		if (SQLITE_OK != (Result = sqlite3_initialize()))
			printf("Failed to initialize library: %d\n", Result);

		//Result = sqlite3_open(mName.c_str(), &pSQLiteDB);

		//SQLStatement.assign("SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1");
		SQLStatement.assign("SELECT Scene.Data,SceneNode.NodeID,SceneNode.EntID,SceneNode.Data,SceneNode.Name,Entity.EntType,Entity.Name,Entity.EntDID,Entity.Data,Entity.Script,Entity.replicate FROM Scene INNER JOIN SceneNode ON Scene.SceneID = SceneNode.SceneID LEFT JOIN Entity ON SceneNode.EntID= Entity.EntID WHERE Scene.SceneID = ? ");
		Result = sqlite3_prepare(mDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pStmt, &pzTail);

		if (Result != SQLITE_OK)
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load");

		if (sqlite3_bind_parameter_count(pStmt) == 0)
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileRename", "OgreSQL::load");

		// pFileInfo
		// SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1

		// Reset the statement
		Result = sqlite3_reset(pStmt);

		if (Result != SQLITE_OK) // Reset failed./// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");

		// Bind Filename to the wildcard.
		//int sqlite3_bind_int(sqlite3_stmt*, int, int);
		Result = sqlite3_bind_int(pStmt, 1, sceneID);
		//Result = sqlite3_bind_text(pFileInfo, 1, strFile.c_str(), (int)strFile.size(), SQLITE_TRANSIENT);

		if (Result != SQLITE_OK)// bind failed.	/// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileInfo");

		//ProtoType::Scene sceneObj;


		do
		{
			// Execute the statement
			Result = sqlite3_step(pStmt);

			//if (Result == SQLITE_DONE)
			//	break;

			if (Result == SQLITE_BUSY)
			{
				/// \warning If you are getting SQLITE_BUSY problems, you could be brave and use "continue".
				// continue;
				break;
			}

			//Ogre::StreamSerialiser::Chunk** ppChunk;


			//----------------------------------------------
			//Columns
			//----------------------------------------------
			//Scene.Data, SceneNodes.NodeID, SceneNodes.EntID, SceneNodes.Data, SceneNodes.Name,
			//GameEntity.EntType,GameEntity.Name,GameEntity.Data


			//Scene Data
			// Determine the size of the data column
			int len = sqlite3_column_bytes(pStmt, 0);

			//char* sceneData = new char[len];
			//const char * tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pStmt, 0));
			//memcpy(sceneData, tmp, len);
			//if (!sceneObj.ParsePartialFromArray(sceneData, len)) {
			//	//	//cerr << "Failed to parse person.pb." << endl;
			//	//	//exit(1);
			//}

			int nodeID = sqlite3_column_int(pStmt, 1);
			int entityID = sqlite3_column_int(pStmt, 2);

			//SceneNode Data
			len = sqlite3_column_bytes(pStmt, 3);
			char* sceneNodeData = new char[len];
			//const char * tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pStmt, 3));
			memcpy(sceneNodeData, sqlite3_column_blob(pStmt, 3), len);
			//ProtoType::Node sceneNodeObj;
			//if (!sceneNodeObj.ParsePartialFromArray(sceneNodeData, len)) {
			//	//	//cerr << "Failed to parse person.pb." << endl;
			//	//	//exit(1);
			//}

			const unsigned char* nodeName = sqlite3_column_text(pStmt, 4);
			int entType = sqlite3_column_int(pStmt, 5);
			const unsigned char* ebtName = sqlite3_column_text(pStmt, 6);

			int raceID = sqlite3_column_int(pStmt, 7); //entdataid

			//entity Data
			len = sqlite3_column_bytes(pStmt, 8);
			char* gameEntData = new char[len]; //todo delete?
			//tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pStmt, 8));
			memcpy(gameEntData, sqlite3_column_blob(pStmt, 8), len);
			//ProtoType::StaticEntity gameEntObj;
			//if (!gameEntObj.ParsePartialFromArray(gameEntData, len)) {
			//	//	//cerr << "Failed to parse person.pb." << endl;
			//	//	//exit(1);
			//}
			//int replicate = sqlite3_column_int(pStmt, 9); //script
			int replicateEntity = sqlite3_column_int(pStmt, 10);

			//for (int i = 0; i < gameEntObj.gameentity().physics().size(); i++)
			//{
			//	int shape = gameEntObj.gameentity().physics(i).shape();
			//	std::cout << "shape" << shape << std::endl;
			//}

			//ProtoType::PhysicsObject physObj0 = gameEntObj.gameentity().physics(0);


			//----------------------------------------------
			// SCene Manager create objects
			//----------------------------------------------
			//Callback to create a new node
			if (entityID > 0)
				xCallback(scene, entityID, gameEntData, replicateEntity);

			//delete sceneNodeData;

			//props.Object = pobj;

			// Retrieve the timestamp
			//KH### (*ppInfo)->iLastMod = sqlite3_column_int(pFileInfo, 1);



			if (Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.
				Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");
			}
			//		return true;

		} while (Result == SQLITE_ROW);

		// Reset the query to release the data
		Result = sqlite3_reset(pStmt);

		if (Result == SQLITE_BUSY)/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
			Ogre::LogManager::getSingleton().logMessage("OgreSQL DB connection reported SQLITE_BUSY, failed");//		return false;

		sqlite3_finalize(pStmt);

		//	Result = sqlite3_close(pSQLiteDB);
	}


	void IDAL::LoadFBJson(const std::string& schemafilePath, const std::string& jsonfilePath, BinaryResult& result)
	{
		//std::string root = "F:\\Projekte\\coop\\XGame\\data\\";
		std::string schemafile;
		std::string jsonfile;

		//	"FlatBufTypes\\Netmsg.fbs", "dbData\\State\\ServerState.json"

		std::string schemafileCstr = "F:\\Projekte\\coop\\XGame\\data\\FlatBufTypes\\Netmsg.fbs";// +schemafilePath;
		std::string jsonfileCstr = "F:\\Projekte\\coop\\XGame\\data\\dbData\\State\\ServerState.json";// +jsonfilePath;

		if (!flatbuffers::LoadFile(schemafileCstr.c_str(), false, &schemafile))
			return;
		if (!flatbuffers::LoadFile(jsonfileCstr.c_str(), false, &jsonfile))
			return;

		// parse schema first, so we can use it to parse the data after
		flatbuffers::Parser parser;

		//	const char *include_directories[] = { "samples", nullptr };
		//const char *include_directories[] = { nullptr };
		const char *include_directories[] = { "F:\\Projekte\\coop\\XGame\\data\\FlatBufTypes" };
		if (!parser.Parse(schemafile.c_str(), include_directories))
			return;

		if (!parser.SetRootType("GameState"))
			return;

		if (!parser.Parse(jsonfile.c_str(), include_directories))
			return;

		result.len = parser.builder_.GetSize();
		result.binData = parser.builder_.GetBufferPointer();
	}

	const void* IDAL::getState(const char* name, int namelen)
	{
		sqlite3_stmt* pFileInfo;/// SQLite Prepared statements.
		const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
		std::string SQLStatement;
		int Result = 0;

		// initialize engine
		if (SQLITE_OK != (Result = sqlite3_initialize()))
			printf("Failed to initialize library: %d\n", Result);


		//SQLStatement.assign("SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1");
		SQLStatement.assign("SELECT State.Data FROM State WHERE State.Name = ? LIMIT 1 ");
		//SQLStatement.assign("SELECT Scene.Data,SceneNodes.NodeID,SceneNodes.EntID,SceneNodes.Data,SceneNodes.Name,GameEntity.EntType,GameEntity.Name,GameEntity.Data FROM Scene LEFT JOIN SceneNodes ON Scene.SceneID = SceneNodes.SceneID LEFT JOIN GameEntity ON SceneNodes.EntID= GameEntity.EntID WHERE Scene.SceneID = ? ");

		Result = sqlite3_prepare(mDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileInfo, &pzTail);

		if (Result != SQLITE_OK)
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load");

		if (sqlite3_bind_parameter_count(pFileInfo) == 0)
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileRename", "OgreSQL::load");

		// pFileInfo
		// SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1

		// Reset the statement
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK) // Reset failed./// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");

		// Bind Filename to the wildcard.
		//int sqlite3_bind_int(sqlite3_stmt*, int, int);
		Result = sqlite3_bind_text(pFileInfo, 1, name, namelen, SQLITE_STATIC);
		//Result = sqlite3_bind_text(pFileInfo, 1, strFile.c_str(), (int)strFile.size(), SQLITE_TRANSIENT);

		if (Result != SQLITE_OK)// bind failed.	/// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileInfo");

		//ProtoType::Scene sceneObj;

		// Execute the statement
		Result = sqlite3_step(pFileInfo);

		//Scene Data
		//const char * tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pFileInfo, 0));
		// Determine the size of the data column

		//const char* data = reinterpret_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		//const char* datastatic = static_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		//void* datastaticv = (void*)(sqlite3_column_blob(pFileInfo, 0));

		int len = sqlite3_column_bytes(pFileInfo, 0);
		char* sceneDataBuffer = new char[len];
		//const void * tmp = sqlite3_column_blob(pFileInfo, 0);

		memcpy(sceneDataBuffer, sqlite3_column_blob(pFileInfo, 0), len);

		//std::vector<char> sceneData(len);

		//const char* data = static_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		//const int size = sqlite3_column_bytes(pFileInfo, 0);
		//std::vector<char> ggg = std::vector<char>(data, data + size);
		//std::istringstream sin(std::string(data, size));
		//std::istream& fin = sin;

		//const char *pBuffer = reinterpret_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		//std::copy(pBuffer, pBuffer + sceneData.size(), &sceneData[0]);

		//	std::copy(sceneData.begin(), sceneData.end(), sceneDataBuffer);

		// Reset the query to release the data
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK)
		{
			// Reset failed./// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");
		}
		else if (Result == SQLITE_BUSY)
		{
			/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
			Ogre::LogManager::getSingleton().logMessage("OgreSQL DB connection reported SQLITE_BUSY, failed");//		return false;
		}
		else {
			flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(sceneDataBuffer), len);

			if (verifier.VerifyBuffer<XFBType::Scene>())
				return sceneDataBuffer;
			else
			{
				Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "load scene failed!", "IDAL::getScene");
				return nullptr;
			}
		}

		sqlite3_finalize(pFileInfo);

		//	Result = sqlite3_close(pSQLiteDB);
	}

	char* IDAL::getScene(sf::Uint16 id)
	{
		sqlite3_stmt* pFileInfo;/// SQLite Prepared statements.
		const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
		std::string SQLStatement;
		int Result = 0;

		// initialize engine
		if (SQLITE_OK != (Result = sqlite3_initialize()))
			printf("Failed to initialize library: %d\n", Result);


		//SQLStatement.assign("SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1");
		SQLStatement.assign("SELECT Scene.Data FROM Scene WHERE Scene.SceneID = ? LIMIT 1 ");
		//SQLStatement.assign("SELECT Scene.Data,SceneNodes.NodeID,SceneNodes.EntID,SceneNodes.Data,SceneNodes.Name,GameEntity.EntType,GameEntity.Name,GameEntity.Data FROM Scene LEFT JOIN SceneNodes ON Scene.SceneID = SceneNodes.SceneID LEFT JOIN GameEntity ON SceneNodes.EntID= GameEntity.EntID WHERE Scene.SceneID = ? ");

		Result = sqlite3_prepare(mDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileInfo, &pzTail);

		if (Result != SQLITE_OK)
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load");

		if (sqlite3_bind_parameter_count(pFileInfo) == 0)
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileRename", "OgreSQL::load");

		// pFileInfo
		// SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1

		// Reset the statement
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK) // Reset failed./// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");

		// Bind Filename to the wildcard.
		//int sqlite3_bind_int(sqlite3_stmt*, int, int);
		Result = sqlite3_bind_int(pFileInfo, 1, id);
		//Result = sqlite3_bind_text(pFileInfo, 1, strFile.c_str(), (int)strFile.size(), SQLITE_TRANSIENT);

		if (Result != SQLITE_OK)// bind failed.	/// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileInfo");

		//ProtoType::Scene sceneObj;

		// Execute the statement
		Result = sqlite3_step(pFileInfo);

		//Scene Data
		//const char * tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pFileInfo, 0));
		// Determine the size of the data column

		//const char* data = reinterpret_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		//const char* datastatic = static_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		//void* datastaticv = (void*)(sqlite3_column_blob(pFileInfo, 0));

		int len = sqlite3_column_bytes(pFileInfo, 0);
		char* sceneDataBuffer = new char[len];
		//const void * tmp = sqlite3_column_blob(pFileInfo, 0);

		memcpy(sceneDataBuffer, sqlite3_column_blob(pFileInfo, 0), len);

		//std::vector<char> sceneData(len);

		//const char* data = static_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		//const int size = sqlite3_column_bytes(pFileInfo, 0);
		//std::vector<char> ggg = std::vector<char>(data, data + size);
		//std::istringstream sin(std::string(data, size));
		//std::istream& fin = sin;

		//const char *pBuffer = reinterpret_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		//std::copy(pBuffer, pBuffer + sceneData.size(), &sceneData[0]);

	//	std::copy(sceneData.begin(), sceneData.end(), sceneDataBuffer);

		// Reset the query to release the data
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK)
		{
			// Reset failed./// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");
		}
		else if (Result == SQLITE_BUSY)
		{
			/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
			Ogre::LogManager::getSingleton().logMessage("OgreSQL DB connection reported SQLITE_BUSY, failed");//		return false;
		}
		else {
			flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(sceneDataBuffer), len);

			if (verifier.VerifyBuffer<XFBType::Scene>())
				return sceneDataBuffer;
			else
			{
				Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "load scene failed!", "IDAL::getScene");
				return nullptr;
			}
		}

		sqlite3_finalize(pFileInfo);

		//	Result = sqlite3_close(pSQLiteDB);
	}

	char*  IDAL::getEntity(sf::Uint16 id)
	{
		sqlite3_stmt* pFileInfo;/// SQLite Prepared statements.
		const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
		std::string SQLStatement;
		int Result = 0;

		// initialize engine
		if (SQLITE_OK != (Result = sqlite3_initialize()))
			printf("Failed to initialize library: %d\n", Result);

		SQLStatement.assign("SELECT Entity.Data FROM Entity WHERE Entity.EntID = ? LIMIT 1 ");

		Result = sqlite3_prepare(mDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileInfo, &pzTail);

		if (Result != SQLITE_OK)
		{
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load");
			return 0;
		}

		if (sqlite3_bind_parameter_count(pFileInfo) == 0)
		{
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileRename", "OgreSQL::load");
			return 0;
		}

		// Reset the statement
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK) // Reset failed./// \todo Add sqlite3 errmsg support.
		{
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");
			return 0;
		}

		// Bind Filename to the wildcard.
		Result = sqlite3_bind_int(pFileInfo, 1, id);

		if (Result != SQLITE_OK)// bind failed.	/// \todo Add sqlite3 errmsg support.
		{
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileInfo");
			return 0;
		}

		// Execute the statement
		Result = sqlite3_step(pFileInfo);

		// Determine the size of the data column
		int len = sqlite3_column_bytes(pFileInfo, 0);

		if (len <= 0)
			return 0; //no data found!

		char* entityDataBuffer = new char[len];

		const char* data = reinterpret_cast<const char*>(sqlite3_column_blob(pFileInfo, 0));
		memcpy(entityDataBuffer, data, len);

		// Reset the query to release the data
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK)
		{
			// Reset failed.
			/// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");
		}

		if (Result == SQLITE_BUSY)/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
			Ogre::LogManager::getSingleton().logMessage("OgreSQL DB connection reported SQLITE_BUSY, failed");//		return false;

		sqlite3_finalize(pFileInfo);


		//flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(entityDataBuffer), len);

		//if (verifier.VerifyBuffer<XFBType::EntityBase>())
		return entityDataBuffer;
		//else
		//{
		//	Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "load entity failed!", "IDAL::getEntity");
		//	return nullptr;
		//}
	}

} // ns XE