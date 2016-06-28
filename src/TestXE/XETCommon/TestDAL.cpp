#include "TestDAL.hpp"

#include <ThirdParty/plog/Log.h>
#include <Sqlite/sqlite3.h>

#include "../XETCommon/Netmsg_generated.h"
#include <XEDAL/Objects/FBEngineTypes_generated.h>

namespace XET {

	TestDAL::TestDAL(XE::XEngine& engine)
		: XE::IDAL(engine)
	{
	}

	TestDAL::~TestDAL()
	{
		close();
	}

	void TestDAL::getSceneNodes(XE::Scene& scene, XE::Uint16 sceneID, XE::sceneNodes_callback xCallback)
	{
		sqlite3_stmt* pStmt;/// SQLite Prepared statements.
		const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
		std::string SQLStatement;
		int Result = 0;

		// initialize engine
		if (SQLITE_OK != (Result = sqlite3_initialize()))
			printf("Failed to initialize library: %d\n", Result);

		SQLStatement.assign("SELECT Scene.Data,SceneNode.NodeID,SceneNode.EntID,SceneNode.Data,SceneNode.Name,Entity.EntType,Entity.Name,Entity.EntDID,Entity.Data,Entity.Script,Entity.replicate FROM Scene INNER JOIN SceneNode ON Scene.SceneID = SceneNode.SceneID LEFT JOIN Entity ON SceneNode.EntID= Entity.EntID WHERE Scene.SceneID = ? ");
		Result = sqlite3_prepare(mDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pStmt, &pzTail);

		if (Result != SQLITE_OK)
			LOG(plog::fatal) << "sqlite3_prepare() failed! Assets table may be missing.";

		if (sqlite3_bind_parameter_count(pStmt) == 0)
			LOG(plog::fatal) << "sqlite3_prepare() failed to detect wildcards in pFileRename";

		// Reset the statement
		Result = sqlite3_reset(pStmt);

		if (Result != SQLITE_OK) // Reset failed./// \todo Add sqlite3 errmsg support.
			LOG(plog::fatal) << "sqlite3_reset() failed!", "OgreSQL::fileInfo";

		// Bind Filename to the wildcard.
		Result = sqlite3_bind_int(pStmt, 1, sceneID);

		if (Result != SQLITE_OK)// bind failed.	/// \todo Add sqlite3 errmsg support.
			LOG(plog::fatal) << "sqlite3_bind_* failed!", "OgreSQL::fileInfo";

		do
		{
			// Execute the statement
			Result = sqlite3_step(pStmt);

			if (Result == SQLITE_BUSY)
			{
				/// \warning If you are getting SQLITE_BUSY problems, you could be brave and use "continue".
				break;
			}

			// Determine the size of the data column
			int len = sqlite3_column_bytes(pStmt, 0);
			int nodeID = sqlite3_column_int(pStmt, 1);
			int entityID = sqlite3_column_int(pStmt, 2);

			//SceneNode Data
			len = sqlite3_column_bytes(pStmt, 3);
			char* sceneNodeData = new char[len];
			memcpy(sceneNodeData, sqlite3_column_blob(pStmt, 3), len);
			const unsigned char* nodeName = sqlite3_column_text(pStmt, 4);
			int entType = sqlite3_column_int(pStmt, 5);
			const unsigned char* ebtName = sqlite3_column_text(pStmt, 6);

			int raceID = sqlite3_column_int(pStmt, 7); //entdataid

			//entity Data
			len = sqlite3_column_bytes(pStmt, 8);
			char* gameEntData = new char[len]; //todo delete?
			memcpy(gameEntData, sqlite3_column_blob(pStmt, 8), len);
			int replicateEntity = sqlite3_column_int(pStmt, 10);

			if (entityID > 0)
				xCallback(scene, entityID, gameEntData, replicateEntity);	//Callback to create a new node

			if (Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.
				LOG(plog::fatal) << "sqlite3_reset() failed!, OgreSQL::fileInfo";
			}
		} while (Result == SQLITE_ROW);

		// Reset the query to release the data
		Result = sqlite3_reset(pStmt);

		if (Result == SQLITE_BUSY)/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
			LOG(plog::fatal) << "OgreSQL DB connection reported SQLITE_BUSY, failed";//		return false;

		sqlite3_finalize(pStmt);
	}


	const void* TestDAL::getState(const char* name, int namelen)
	{
		sqlite3_stmt* pFileInfo;/// SQLite Prepared statements.
		const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
		std::string SQLStatement;
		int Result = 0;

		// initialize engine
		if (SQLITE_OK != (Result = sqlite3_initialize()))
			printf("Failed to initialize library: %d\n", Result);

		SQLStatement.assign("SELECT State.Data FROM State WHERE State.Name = ? LIMIT 1 ");

		Result = sqlite3_prepare(mDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileInfo, &pzTail);

		if (Result != SQLITE_OK)
			LOG(plog::fatal) << "sqlite3_prepare() failed! Assets table may be missing.";

		if (sqlite3_bind_parameter_count(pFileInfo) == 0)
			LOG(plog::fatal) << "sqlite3_prepare() failed to detect wildcards in pFileRename";

		// Reset the statement
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK) // Reset failed./// \todo Add sqlite3 errmsg support.
			LOG(plog::fatal) << "sqlite3_reset() failed!";

		// Bind Filename to the wildcard.
		Result = sqlite3_bind_text(pFileInfo, 1, name, namelen, SQLITE_STATIC);

		if (Result != SQLITE_OK)// bind failed.	/// \todo Add sqlite3 errmsg support.
			LOG(plog::fatal) << "sqlite3_bind_* failed!";

		// Execute the statement
		Result = sqlite3_step(pFileInfo);

		int len = sqlite3_column_bytes(pFileInfo, 0);
		char* sceneDataBuffer = new char[len];

		memcpy(sceneDataBuffer, sqlite3_column_blob(pFileInfo, 0), len);

		// Reset the query to release the data
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK)
		{
			// Reset failed./// \todo Add sqlite3 errmsg support.
			LOG(plog::fatal) << "sqlite3_reset() failed!";
		}
		else if (Result == SQLITE_BUSY)
		{
			/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
			LOG(plog::fatal) << "OgreSQL DB connection reported SQLITE_BUSY, failed";//		return false;
		}
		else {

			flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(sceneDataBuffer), len);

			assert(verifier.VerifyBuffer<NetMsg::Entity>());
			
			return sceneDataBuffer;
		}

		sqlite3_finalize(pFileInfo);
		
		return 0;
	}

	char* TestDAL::getScene(XE::Uint16 id)
	{
		sqlite3_stmt* pFileInfo;/// SQLite Prepared statements.
		const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)
		std::string SQLStatement;
		int Result = 0;

		// initialize engine
		if (SQLITE_OK != (Result = sqlite3_initialize()))
			printf("Failed to initialize library: %d\n", Result);

		SQLStatement.assign("SELECT Scene.Data FROM Scene WHERE Scene.SceneID = ? LIMIT 1 ");

		Result = sqlite3_prepare(mDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileInfo, &pzTail);

		if (Result != SQLITE_OK)
			LOG(plog::fatal) << "sqlite3_prepare() failed! Assets table may be missing.";

		if (sqlite3_bind_parameter_count(pFileInfo) == 0)
			LOG(plog::fatal) << "sqlite3_prepare() failed to detect wildcards in pFileRename";

		// Reset the statement
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK) // Reset failed./// \todo Add sqlite3 errmsg support.
			LOG(plog::fatal) << "sqlite3_reset() failed!";

		// Bind Filename to the wildcard.
		Result = sqlite3_bind_int(pFileInfo, 1, id);

		if (Result != SQLITE_OK)// bind failed.	/// \todo Add sqlite3 errmsg support.
			LOG(plog::fatal) << "sqlite3_bind_* failed!";

		// Execute the statement
		Result = sqlite3_step(pFileInfo);

		int len = sqlite3_column_bytes(pFileInfo, 0);
		char* sceneDataBuffer = new char[len];

		memcpy(sceneDataBuffer, sqlite3_column_blob(pFileInfo, 0), len);

		// Reset the query to release the data
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK)
		{
			// Reset failed./// \todo Add sqlite3 errmsg support.
			LOG(plog::fatal) << "sqlite3_reset() failed!";
		}
		else if (Result == SQLITE_BUSY)
		{
			/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
			LOG(plog::info) << "OgreSQL DB connection reported SQLITE_BUSY, failed";//		return false;
		}
		else {

			flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(sceneDataBuffer), len);
			
			assert(verifier.VerifyBuffer<XFBType::Scene>());

			return sceneDataBuffer;
		}

		sqlite3_finalize(pFileInfo);

		return 0;
	}

	char*  TestDAL::getEntity(XE::Uint16 id)
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
			LOG(plog::fatal) << "sqlite3_prepare() failed! Assets table may be missing.";
			return 0;
		}

		if (sqlite3_bind_parameter_count(pFileInfo) == 0)
		{
			LOG(plog::fatal) << "sqlite3_prepare() failed to detect wildcards in pFileRename";
			return 0;
		}

		// Reset the statement
		Result = sqlite3_reset(pFileInfo);

		if (Result != SQLITE_OK) // Reset failed./// \todo Add sqlite3 errmsg support.
		{
			LOG(plog::fatal) << "sqlite3_reset() failed!";
			return 0;
		}

		// Bind Filename to the wildcard.
		Result = sqlite3_bind_int(pFileInfo, 1, id);

		if (Result != SQLITE_OK)// bind failed.	/// \todo Add sqlite3 errmsg support.
		{
			LOG(plog::fatal) << "sqlite3_bind_* failed!";
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
			LOG(plog::fatal) << "sqlite3_reset() failed!";
		}

		if (Result == SQLITE_BUSY)/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
			LOG(plog::info) << "OgreSQL DB connection reported SQLITE_BUSY, failed";

		sqlite3_finalize(pFileInfo);

		return entityDataBuffer;
	}

}