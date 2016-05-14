#include <XEDAL/IDAL.hpp>
#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <XEPhysics/gkCharacter.h>
#include <Ogre/OgreMain/include/OgreLogManager.h>

#include <Ogre/OgreMain/include/OgreStreamSerialiser.h>

#include <Ogre/OgreMain/include/OgreArchive.h>

#include <XEDAL/Objects/ProtoType.pb.h>

#include <Sqlite/sqlite3.h>


#include <iostream>

namespace XE {

IDAL::IDAL()
{
	open();
}

IDAL::~IDAL()
{
	close();
}

void IDAL::getPhysicsProperties(Ogre::uint16 id, gkPhysicsProperties& props)
{
	//gkPhysicsProperties pProp;

	//Ogre::String strFile;
//	Ogre::FileInfo** ppInfo;
	//Ogre::String mName = "D:\\Projekte\\Src Game\\Data\\Data_Release\\gameData.s3db";/// Archive name
	//sqlite3* pSQLiteDB;/// SQLite Database Connection
	sqlite3_stmt* pFileInfo;/// SQLite Prepared statements.
	const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
	std::string SQLStatement;
	int Result = 0;

	// initialize engine
	if (SQLITE_OK != (Result = sqlite3_initialize()))
		printf("Failed to initialize library: %d\n", Result);

	//Result = sqlite3_open(mName.c_str(), &pSQLiteDB);

	//SQLStatement.assign("SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1");
	SQLStatement.assign("SELECT CID,Data FROM PHYSICOBJECT WHERE PO_ID = ? LIMIT 1");
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

	// Execute the statement
	Result = sqlite3_step(pFileInfo);

	Ogre::StreamSerialiser::Chunk** ppChunk;

	// Retrieve the result
	if (Result == SQLITE_ROW)
	{
		// The full filename is the same, of course.
		//strcpy(const_cast<char*>((*ppInfo)->filename.c_str()), strFile.c_str());

		// Determine the size of the data column
	//	(*ppInfo)->uncompressedSize = sqlite3_column_bytes(pFileInfo, 0);
		int len = sqlite3_column_bytes(pFileInfo, 1);

		// This database doesn't compress data...yet
		//(*ppInfo)->compressedSize = (*ppInfo)->uncompressedSize;

		// Copy the data into the new buffer
		//(*ppChunk)-> allocate(DataSize, (const Ogre::uchar *)sqlite3_column_blob(pFileInfo, 0));
	
	//	std::vector<char> data(length);
		int cid = sqlite3_column_int(pFileInfo, 0);
	
		//int len = r.at(1);
		//int len_uncomp = r.at(2);

		char *data = OGRE_ALLOC_T(char, len, Ogre::MEMCATEGORY_GENERAL);
		
		char* test = new char[len];

		//if (len_uncomp > len){
		//	//unsigned long uncompressed_len_ret;
		//	//int err = uncompress(data, &uncompressed_len_ret, (char *)r.raw_data(0), len);
		//	//if (err != Z_OK){
		//		//log->logMessage("Failed uncompression of resource : " + filename);
		//		//return DataStreamPtr();
		//	//}
		//	assert(uncompressed_len_ret == len_uncomp);
		//}
		//else{

		const char * tmp = reinterpret_cast< char const* >(sqlite3_column_blob(pFileInfo, 1));
		memcpy(test, tmp, len);
	//	}

		// Copy the data into the new buffer
	//	(*ppChunk)->allocate(len, (const Ogre::uchar *)sqlite3_column_blob(pFileInfo, 1));

		//Ogre::StreamSerialiser* sr = new Ogre::StreamSerialiser();

	// const char *pBuffer = reinterpret_cast<const char *>(sqlite3_column_blob(pFileInfo, 0));
	//
	//std::ifstream in(pBuffer, std::ios::binary);

	////	byte[] value;
		std::string s(reinterpret_cast< char const* >(test), len);

	//	in.read(reinterpret_cast<char *>(&pBuffer), sizeof(len));
	
		std::cout << "##" << s;

		
	//	std::copy(pBuffer, pBuffer + data.size(), &data[0]);

		ProtoType::PhysicsObject pobj;		
		if (!pobj.ParsePartialFromArray(test, len)) {
		//	//cerr << "Failed to parse person.pb." << endl;
		//	//exit(1);
		}

		props.Object = pobj;

		// Retrieve the timestamp
		//KH### (*ppInfo)->iLastMod = sqlite3_column_int(pFileInfo, 1);

		// Reset the query to release the data
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK)
		{
			// Reset failed.
			/// \todo Add sqlite3 errmsg support.
			Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo");
		}
//		return true;
	}
	else if (Result == SQLITE_DONE)
	{ }	// File not found	return false;
	else if (Result == SQLITE_BUSY)/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
		Ogre::LogManager::getSingleton().logMessage("OgreSQL DB connection reported SQLITE_BUSY, failed");//		return false;

	sqlite3_finalize(pFileInfo);

//	Result = sqlite3_close(pSQLiteDB);

}

void IDAL::getGameEntityProperties(Ogre::uint16 id, GameEntityProperties& props)
{
	getPhysicsProperties(id, props.m_physics);

	//todo komplette Game entity daten12 !!!
	//GameEntityProperties props;

	//execute("SELECT * FROM PHYSICOBJECT WHERE PO_ID=0;");
	//execute("SELECT * FROM GAMEOBJECT WHERE PO_ID=0;");


	//GameEntityProperties& props = this->getProperties();
	//props.m_physics.Object.shape = SH_CAPSULE;
	//props.m_physics.Object.friction = 1.0f;
	//props.m_physics.Object.restitution = 0.0f; //for bouncing
	//props.m_physics.Object.colgroupmask = btBroadphaseProxy::CharacterFilter;
	//props.m_physics.Object.colmask = btBroadphaseProxy::DefaultFilter;
	//props.m_physics.Object.charjumpspeed = 10;
	//props.m_physics.Object.charfallspeed = 10;
	//props.m_physics.Object.charstepheight = 0.0f;


	//return props;
}

void IDAL::setGameEntityProperties(Ogre::uint16 id, GameEntityProperties& props)
{

}

void IDAL::setPhysicProperties(Ogre::uint16 id, gkPhysicsProperties& props)
{

}


void IDAL::getRaceData(Ogre::uint16 sceneID, RaceMap& raceMap)
{
	sqlite3_stmt* pStmt;/// SQLite Prepared statements.
	const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
	std::string SQLStatement;
	int Result = 0;

	// initialize engine
	if (SQLITE_OK != (Result = sqlite3_initialize()))
		printf("Failed to initialize library: %d\n", Result);

	SQLStatement.assign("SELECT DISTINCT Race.RaceID,Race.Data FROM Scene LEFT JOIN SceneNodes ON SceneNodes.EntID = GameEntity.EntID INNER JOIN GameEntity ON SceneNodes.EntID = GameEntity.EntID INNER JOIN Race ON GameEntity.RaceID = Race.RaceID WHERE Scene.SceneID = ? AND GameEntity.RaceID > 0 ");
	//SQLStatement.assign("SELECT Scene.Data,SceneNodes.NodeID,SceneNodes.EntID,SceneNodes.Data,SceneNodes.Name,GameEntity.EntType,GameEntity.Name,GameEntity.Data FROM Scene INNER JOIN SceneNodes ON Scene.SceneID = SceneNodes.SceneID LEFT JOIN GameEntity ON SceneNodes.EntID= GameEntity.EntID WHERE Scene.SceneID = ? ");
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

		if (Result == SQLITE_DONE)
			break;

		if (Result == SQLITE_BUSY)
		{
			/// \warning If you are getting SQLITE_BUSY problems, you could be brave and use "continue".
			// continue;
			break;
		}

		Ogre::StreamSerialiser::Chunk** ppChunk;


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

		int raceID = sqlite3_column_int(pStmt, 0);
	//	int entityID = sqlite3_column_int(pStmt, 2);

		//raceData
		len = sqlite3_column_bytes(pStmt, 1);
		char* raceData = new char[len];
		const char * tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pStmt, 1));
		memcpy(raceData, tmp, len);
		ProtoType::RaceGender raceGenderObj;
		if (!raceGenderObj.ParsePartialFromArray(raceData, len)) {
			//	//cerr << "Failed to parse person.pb." << endl;
			//	//exit(1);
		}

		raceMap.insert({ raceID, raceGenderObj });
		//raceData.
	//	const unsigned char* nodeName = sqlite3_column_text(pStmt, 4);
	//	int entType = sqlite3_column_int(pStmt, 5);
	//	const unsigned char* ebtName = sqlite3_column_text(pStmt, 6);

		//entity Data
	//	len = sqlite3_column_bytes(pStmt, 7);
	//	char* gameEntData = new char[len]; //todo delete?
	//	tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pStmt, 7));
	//	memcpy(gameEntData, tmp, len);
		//ProtoType::StaticEntity gameEntObj;
		//if (!gameEntObj.ParsePartialFromArray(gameEntData, len)) {
		//	//	//cerr << "Failed to parse person.pb." << endl;
		//	//	//exit(1);
		//}

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
		//xCallback(scene, sceneNodeObj, entityID, entType, gameEntData, len);

		delete raceData;

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

}

void IDAL::getSceneNodes(Scene* scene, Ogre::uint16 sceneID, sceneNodes_callback xCallback)
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
	SQLStatement.assign("SELECT Scene.Data,SceneNodes.NodeID,SceneNodes.EntID,SceneNodes.Data,SceneNodes.Name,GameEntity.EntType,GameEntity.Name,GameEntity.RaceID,GameEntity.Data FROM Scene INNER JOIN SceneNodes ON Scene.SceneID = SceneNodes.SceneID LEFT JOIN GameEntity ON SceneNodes.EntID= GameEntity.EntID WHERE Scene.SceneID = ? ");
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

		if (Result == SQLITE_DONE)
			break;

		if (Result == SQLITE_BUSY)
		{
			/// \warning If you are getting SQLITE_BUSY problems, you could be brave and use "continue".
			// continue;
			break;
		}

		Ogre::StreamSerialiser::Chunk** ppChunk;


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
		const char * tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pStmt, 3));
		memcpy(sceneNodeData, tmp, len);
		ProtoType::Node sceneNodeObj;
		if (!sceneNodeObj.ParsePartialFromArray(sceneNodeData, len)) {
			//	//cerr << "Failed to parse person.pb." << endl;
			//	//exit(1);
		}

		const unsigned char* nodeName = sqlite3_column_text(pStmt, 4);
		int entType = sqlite3_column_int(pStmt, 5);
		const unsigned char* ebtName = sqlite3_column_text(pStmt, 6);

		int raceID = sqlite3_column_int(pStmt, 7);

		//entity Data
		len = sqlite3_column_bytes(pStmt, 8);
		char* gameEntData = new char[len]; //todo delete?
		tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pStmt, 8));
		memcpy(gameEntData, tmp, len);
		//ProtoType::StaticEntity gameEntObj;
		//if (!gameEntObj.ParsePartialFromArray(gameEntData, len)) {
		//	//	//cerr << "Failed to parse person.pb." << endl;
		//	//	//exit(1);
		//}

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
		xCallback(scene, sceneNodeObj, entityID, raceID, entType, gameEntData, len);

		delete sceneNodeData;

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


void  IDAL::getScene(Ogre::uint16 id, IDAL::ProtoBinaryResult& result)
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
	// Determine the size of the data column
	result.len = sqlite3_column_bytes(pFileInfo, 0);
	char* sceneData = new char[result.len];
	const char * tmp = reinterpret_cast<char const*>(sqlite3_column_blob(pFileInfo, 0));
	memcpy(sceneData, tmp, result.len);
	

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

	result.binData = sceneData;

	//	Result = sqlite3_close(pSQLiteDB);

}


} // ns XE