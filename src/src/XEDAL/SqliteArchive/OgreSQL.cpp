#include <XEDAL/SqliteArchive/OgreSQL.hpp>

#include <Ogre/OgreMain/include/OgreArchiveManager.h>
#include <Ogre/OgreMain/include/OgreLogManager.h>
#include <Ogre/OgreMain/include/OgreException.h>
// #include "OgreArchiveFactory.h"
#include <Ogre/OgreMain/include/OgreStringVector.h>
#include <stdio.h>

namespace Ogre
{
	DataStreamPtr OgreSQL::open(const String& filename, bool readOnly ) 
	{
		return DataStreamPtr();
	}

	/// @copydoc Archive::create
	DataStreamPtr OgreSQL::create(const String& filename) const
	{
		return DataStreamPtr();
	}

	/// @copydoc Archive::remove
	void OgreSQL::remove(const String& filename) const
	{

	}

	/// @copydoc Archive::list
	StringVectorPtr OgreSQL::list(bool recursive , bool dirs )
	{
		StringVectorPtr tmp;
		return tmp;
	}

	/// @copydoc Archive::listFileInfo
	FileInfoListPtr OgreSQL::listFileInfo(bool recursive , bool dirs )
	{
		FileInfoListPtr tmp;
		return tmp;
	}

	/// @copydoc Archive::find
	StringVectorPtr OgreSQL::find(const String& pattern, bool recursive , bool dirs )
	{
		StringVectorPtr tmp;
		return tmp;
	}

	/// @copydoc Archive::findFileInfo
	FileInfoListPtr OgreSQL::findFileInfo(const String& pattern, bool recursive, bool dirs) 
	{
		FileInfoListPtr tmp;
		return tmp;
	}

	/// @copydoc Archive::exists
	bool OgreSQL::exists(const String& filename)
	{
		return false;
	}

	/// @copydoc Archive::getModifiedTime
	time_t OgreSQL::getModifiedTime(const String& filename)
	{
		time_t tmp;
		return tmp;
	}

    //-----------------------------------------------------------------------
    bool OgreSQL::fileOpen( const String& strFile, FILE** ppFile ) 
    {
     
		int Result = 0;

		// pFileOpen
		// SELECT Data FROM Assets WHERE ResourceName = ? ORDER BY Version DESC LIMIT 1

		// Reset the statement

			Result = sqlite3_reset(pFileOpen);

			if(Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileOpen" );

			}

		// Bind Filename to the wildcard.

			Result = sqlite3_bind_text(pFileOpen, 1, strFile.c_str(), (int)strFile.size(), SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception(Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileOpen");

			}

		// Execute the statement

			Result = sqlite3_step(pFileOpen);

		// Retrieve the result

			if(Result == SQLITE_ROW)
			{

				// Determine the size of the data

					size_t DataSize = (size_t)sqlite3_column_bytes(pFileOpen, 0);

					if(DataSize == 0)
					{
						// File is empty
						return false;
					}

					// Copy the data into the new buffer
					fwrite(sqlite3_column_blob(pFileOpen,0), 1, DataSize, *ppFile);
					fseek(*ppFile, 0, SEEK_SET);

					return true;
		            
			}

			if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay

					LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
					return false;

			}

		// "File not found"

			return false;



    }

    //-----------------------------------------------------------------------
	bool OgreSQL::fileRead(const String& strFile, StreamSerialiser::Chunk** ppChunk) 
    {
        int Result = 0;

		// pFileOpen
		// SELECT Data FROM Assets WHERE ResourceName = ? ORDER BY Version DESC LIMIT 1

		// Reset the statement

			Result = sqlite3_reset(pFileOpen);

			if(Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.

				Exception(Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileRead");

			}

		// Bind Filename to the wildcard.

			Result = sqlite3_bind_text(pFileOpen, 1, strFile.c_str(), (int)strFile.size(), SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception(Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileRead");

			}

		// Execute the statement

			Result = sqlite3_step(pFileOpen);

		// Retrieve the result

			if(Result == SQLITE_ROW)
			{

				// Determine the size of the data

					size_t DataSize = (size_t)sqlite3_column_bytes(pFileOpen, 0);

					if(DataSize == 0)
					{
						// File is empty
						return false;
					}

					// Copy the data into the new buffer
			//KH###		(*ppChunk)->allocate(DataSize, (const Ogre::uchar *)sqlite3_column_blob(pFileOpen,0));

					return true;
		            
			}

			if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
				LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
				return false;

			}

			return false;

    }

    //-----------------------------------------------------------------------
    bool OgreSQL::fileSave( ::FILE* pFile, const String& strPath, bool bOverwrite /* = false */ )
    {
    
		int Result = 0;

		// Pointer to select the appropriate action.
		sqlite3_stmt* pStatement = pFileSave;


		// Make sure the specified file doesn't exist already.

			if(this->fileTest(strPath))
			{
				if(!bOverwrite)
					return false;

				// Perform an UPDATE instead
				
					pStatement = pFileUpdate;
			}


		// Reset the statement

			Result = sqlite3_reset(pStatement);

			if(Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileSave" );

			}

		// Bind Filename to the wildcard 1.

			Result = sqlite3_bind_text(pStatement, 1, strPath.c_str(), (int)strPath.size(), SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileSave" );

			}

		// Determine the size of the file

			fseek(pFile, 0, SEEK_END);
			size_t DataSize = ftell(pFile);

		// Read the file into a buffer

			char *pBuffer = new char[DataSize];

			fseek(pFile, 0, SEEK_SET);
			fread(pBuffer, 1, DataSize, pFile);
			fseek(pFile, 0, SEEK_SET);

		// Bind the Buffer to wildcard 2.
            
			/// \todo Implementing a destructor inplace of SQLite_Transient would vastly improve memory performance.
			Result = sqlite3_bind_blob(pStatement, 2, (const void*)pBuffer, (int)DataSize, SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileSave" );

			}

		// Execute the statement

			Result = sqlite3_step(pStatement);

		// Delete the buffer.

			delete pBuffer;

		// Retrieve the result

			if(Result == SQLITE_DONE)
			{

				// Check for changes
				if(sqlite3_changes(pSQLiteDB) > 0)
				{
					// Operation was successful.
						return true;
				}

			}

			if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
				LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
				return false;

			}

			return false;

    }

    //-----------------------------------------------------------------------
	bool OgreSQL::fileWrite(const StreamSerialiser::Chunk& refChunk, const String& strPath, bool bOverwrite /* = false */)
    {

        int Result = 0;

		// Pointer to select the appropriate action.

			sqlite3_stmt* pStatement = pFileSave;


		// Make sure the specified file doesn't exist already.

			if(this->fileTest(strPath))
			{
				if(!bOverwrite)
					return false;

				// Perform an UPDATE instead
				
					pStatement = pFileUpdate;
			}


		// Reset the statement

			Result = sqlite3_reset(pStatement);

			if(Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileWrite" );

			}

		// Bind Filename to the wildcard 1.

			Result = sqlite3_bind_text(pStatement, 1, strPath.c_str(), (int)strPath.size(), SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileWrite" );

			}

		// Bind the Buffer to wildcard 2.
            
			/// \todo Implementing a destructor inplace of SQLite_Transient would vastly improve memory performance.
		//KH###	Result = sqlite3_bind_blob(pStatement, 2, (const void*)refChunk.getPtr(), (int)refChunk.getSize(), SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileWrite" );

			}

		// Execute the statement

			Result = sqlite3_step(pStatement);

		// Retrieve the result

			if(Result == SQLITE_DONE)
			{

				// Check for changes
				if(sqlite3_changes(pSQLiteDB) > 0)
				{
					// Operation was successful.
						return true;
				}

			}

			if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
				LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
				return false;

			}

			return false;
    }

    //-----------------------------------------------------------------------
    bool OgreSQL::fileTest( const String& strFile ) 
    {
		// pFileTest
		// SELECT ResourceName FROM Assets WHERE ResourceName = ? LIMIT 1

		// Reset the statement

			int Result = sqlite3_reset(pFileTest);

			if(Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileTest" );

			}

		// Bind Filename to the wildcard.

			Result = sqlite3_bind_text(pFileTest, 1, strFile.c_str(), (int)strFile.size(), SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileTest" );

			}

		// Execute the statement

			Result = sqlite3_step(pFileTest);

		// Retrieve the result

			if(Result == SQLITE_ROW)
			{

				// There is at least one occurance of the resource name.

					return true;
		            
			}

			if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay.
				LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
				return false;

			}

			// Result is likely SQLITE_DONE, but it doesn't matter.
			return false;


    }

    //-----------------------------------------------------------------------
    bool OgreSQL::fileCopy( const String& strSrc, const String& strDest, bool bOverwrite )
    {

		int Result = 0;

        // Retrieve the source row

			// pFileOpen
			// SELECT Data FROM Assets WHERE ResourceName = ? ORDER BY Version DESC LIMIT 1

			// Reset the statement

				Result = sqlite3_reset(pFileOpen);

				if(Result != SQLITE_OK)
				{
					// Reset failed.
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileCopy" );

				}

			// Bind Filename to the wildcard.

				Result = sqlite3_bind_text(pFileOpen, 1, strSrc.c_str(), (int)strSrc.size(), SQLITE_TRANSIENT);

				if(Result != SQLITE_OK)
				{
					// Bind failed.	
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileCopy" );

				}

			// Execute the statement

				Result = sqlite3_step(pFileOpen);

			// Retrieve the result

				switch(Result)
				{
				case SQLITE_ROW:

					// Leave the query open for use later.

					break;

				case SQLITE_DONE:

					// Source doesn't exist.

				case SQLITE_BUSY:

					/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay

					LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");

				default:

					return false;
				}

		// Determine if the destination already exists

			// pFileSave
			// INSERT INTO Assets (ResourceName, Data)(?1, ?2)

			sqlite3_stmt* pStatement = pFileSave;

			if(this->fileTest(strDest))
			{
				if(!bOverwrite)
					return false;

				// Perform an UPDATE instead

				// pUpdate
				// UPDATE Assets SET ResourceName = ?1, Data = ?2 WHERE ResourceName = ?1
				pStatement = pFileUpdate;
			}

		// Insert/Update to the destination row

			// Reset the statement

				Result = sqlite3_reset(pStatement);

				if(Result != SQLITE_OK)
				{
					// Reset failed.
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileCopy" );

				}

			// Bind Filename to the wildcard 1.

				Result = sqlite3_bind_text(pStatement, 1, strDest.c_str(), (int)strDest.size(), SQLITE_TRANSIENT);

				if(Result != SQLITE_OK)
				{
					// Bind failed.	
					/// \todo Add sqlite3 errmsg support.
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileCopy" );
				}

			// Bind the Source data to wildcard 2 directly from the first query results
	            
				Result = sqlite3_bind_blob(pStatement, 2, sqlite3_column_blob(pFileOpen, 0),
					sqlite3_column_bytes(pFileOpen, 0), SQLITE_TRANSIENT);

				if(Result != SQLITE_OK)
				{
					// Bind failed.	
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileCopy" );

				}

			// Execute the statement

				Result = sqlite3_step(pStatement);

		// Retrieve the result

			if(Result == SQLITE_DONE)
			{

				// Check for changes
				if(sqlite3_changes(pSQLiteDB) > 0)
				{
					// Operation was successful.
						return true;
				}

			}

			if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay
				LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
				return false;

			}

			return false;

    }

    //-----------------------------------------------------------------------
    bool OgreSQL::fileMove( const String& strSrc, const String& strDest, bool bOverwrite )
    {

		// if the source and destination match, return

			String sTSrc = strSrc;
			String sTDest = strDest;
			StringUtil::toLowerCase(sTDest);
			if(Ogre::StringUtil::startsWith(sTSrc, sTDest))
				return true;

		// Make sure the source exists
			if(!(this->fileTest(strSrc)))
				return false;

		// Make sure the target doesn't already exist.

			if(this->fileTest(strDest))
			{
				// Delete the file is overwriting is allowed.
				if(bOverwrite)
				{
					if(this->fileDele(strDest))
					{
						// Delete failed
						return false;
					}
					
				}
				else
				{
					// Cannot perform move.
					return false;
				}
			}

		// pFileRename
		// UPDATE Assets SET ResourceName = :001 WHERE ResourceName = :002

			int Result = 0;

			// Reset the statement

				Result = sqlite3_reset(pFileRename);

				if(Result != SQLITE_OK)
				{
					// Reset failed.
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileMove" );

				}

			// Bind source to wildcard 1.

				Result = sqlite3_bind_text(pFileRename, 1, strDest.c_str(), (int)strDest.size(), SQLITE_TRANSIENT);

				if(Result != SQLITE_OK)
				{
					// bind failed.	
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileMove" );

				}

			// Bind destination to wildcard 2.

				Result = sqlite3_bind_text(pFileRename, 2, strSrc.c_str(), (int)strSrc.size(), SQLITE_TRANSIENT);

				if(Result != SQLITE_OK)
				{
					// bind failed.	
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileMove" );

				}

			// Execute the statement

				Result = sqlite3_step(pFileRename);

			// Retrieve the result

				if(Result == SQLITE_DONE)
				{

					// Determine the # of changes
					if(sqlite3_changes(pSQLiteDB) > 0)
						return true;
			            
				}

				if(Result == SQLITE_BUSY)
				{

					/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay

						LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
						return false;

				}

			// Rename failed

				return false;
	        

    }

    //-----------------------------------------------------------------------
    bool OgreSQL::fileDele( const String& strFile )
    {
		int Result = 0;

		// pFileDelete
        // DELETE FROM Assets WHERE ResourceName = ?

		// Reset the statement

			Result = sqlite3_reset(pFileDelete);

			if(Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileDelete" );

			}

		// Bind Filename to the wildcard.

			Result = sqlite3_bind_text(pFileDelete, 1, strFile.c_str(), (int)strFile.size(), SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileDelete" );

			}

		// Execute the statement

			Result = sqlite3_step(pFileDelete);

		// Retrieve the result

			if(Result == SQLITE_DONE)
			{

				// Determine if there were any changes

				if(sqlite3_changes(pSQLiteDB) > 0)
					return true;
		            
			}

			if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay

					LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
					return false;

			}

		// "File not found"

			return false;
    }

    //-----------------------------------------------------------------------
    bool OgreSQL::fileInfo( const String& strFile, FileInfo** ppInfo ) 
    {
       
		int Result = 0;

		// pFileInfo
		// SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1

		// Reset the statement

			Result = sqlite3_reset(pFileInfo);

			if(Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo" );

			}

		// Bind Filename to the wildcard.

			Result = sqlite3_bind_text(pFileInfo, 1, strFile.c_str(), (int)strFile.size(), SQLITE_TRANSIENT);

			if(Result != SQLITE_OK)
			{
				// bind failed.	
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::fileInfo" );

			}

		// Execute the statement

			Result = sqlite3_step(pFileInfo);

		// Retrieve the result

			if(Result == SQLITE_ROW)
			{

				// The full filename is the same, of course.
				strcpy(const_cast<char*>((*ppInfo)->filename.c_str()), strFile.c_str());

				// Determine the size of the data column
				(*ppInfo)->uncompressedSize = sqlite3_column_bytes(pFileInfo, 0);

				// This database doesn't compress data...yet
				(*ppInfo)->compressedSize = (*ppInfo)->uncompressedSize;

				// Retrieve the timestamp
				//KH### (*ppInfo)->iLastMod = sqlite3_column_int(pFileInfo, 1);

				// Reset the query to release the data
				Result = sqlite3_reset(pFileInfo);

				if(Result != SQLITE_OK)
				{
					// Reset failed.
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::fileInfo" );

				}

				return true;


			}
			else if(Result == SQLITE_DONE)
			{

				// File not found

				return false;
			}
			else if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay

					LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY, failed");
					return false;

			}

		// Other error

			return false;


		

    }

    //-----------------------------------------------------------------------
    std::vector<String> OgreSQL::dirGetFiles( const String& strDir ) 
    {
        return const_cast<OgreSQL *>(this)->getAllNamesLike( strDir, "", false );
    }

    //-----------------------------------------------------------------------
    std::vector<String> OgreSQL::dirGetSubs( const String& strDir ) 
    {

		/// \todo Implement
		return std::vector<String>();




    }

    //-----------------------------------------------------------------------
    bool OgreSQL::dirDele( const String& strDir, bool bRecursive )
    {
		/// \todo Implement
        return false;
    };

    //-----------------------------------------------------------------------
    bool OgreSQL::dirMove( const String& strSrc, const String& strDest, bool bOverwrite )
    {
		/// \todo Implement
        return false;
    };

    //-----------------------------------------------------------------------
    bool OgreSQL::dirInfo( const String& strDir, FileInfo** ppInfo ) 
    {
		/// \todo Implement
        return false;
    };

    //-----------------------------------------------------------------------
    bool OgreSQL::dirCopy( const String& strSrc, const String& strDest, bool bOverwrite )
    {
		/// \todo Implement
        return false;
    };

    //-----------------------------------------------------------------------
    bool OgreSQL::dirTest( const String& strDir ) 
    {
		/// \todo Implement
        return false;
    };

    //-----------------------------------------------------------------------
	std::vector<String> OgreSQL::getAllNamesLike(const String& strStartPath, const String& strPattern, bool bRecursive /* = true */)
    {
		int Result = 0;
		std::vector<String> retVec;

		String Filename;

		// pRecursiveFileNames
		// SELECT DISTINCT ResourceName FROM Assets WHERE ResourceName LIKE ?
		// pNonRecursiveFileNames
		// SELECT DISTINCT ResourceName FROM Assets WHERE ResourceName LIKE ? NOT LIKE ?

		// Choose a command

			sqlite3_stmt *pFileNames = NULL;

			if(bRecursive)
				pFileNames = pRecursiveFileNames;
			else
				pFileNames = pNonRecursiveFileNames;

		// Reset the statement

			Result = sqlite3_reset(pFileNames);

			if(Result != SQLITE_OK)
			{
				// Reset failed.
				/// \todo Add sqlite3 errmsg support.

				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_reset() failed!", "OgreSQL::getAllNamesLike" );

			}

		// Create/Bind the first LIKE statement to wildcard 1
		// (Like contains the recursive component of the query)

			String Like;
			String temp = strStartPath;

            if((strStartPath != "./") && (strStartPath != ""))
			{
				// remove the leading "./" or "/"

				if(temp.substr(0,2) == "./")
					temp.erase(0,2);
				else if(temp.substr(0,1) == "/")
					temp.erase(0,1);
				
			}
			else
				temp.clear();

			Like.assign(temp);
			
			Like.append("%");

			Like.append(strPattern);

			Like.append("%");

			// Bind Like to the wildcard.

				Result = sqlite3_bind_text(pFileNames, 1, Like.c_str(), (int)Like.size(), SQLITE_TRANSIENT);

				if(Result != SQLITE_OK)
				{
					// bind failed.	
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::getAllNamesLike" );

				}

		// If this is a non recursive query,
		// Create/Bind the NOT LIKE statement to wildcard 2
		// (NotLike contains the nonrecursive component of the query

			String NotLike;

			NotLike.assign(temp);

			NotLike.append("%/%");

			if(!bRecursive)
			{

			// Bind NotLike to the wildcard.

				Result = sqlite3_bind_text(pFileNames, 2, NotLike.c_str(), (int)NotLike.size(), SQLITE_TRANSIENT);

				if(Result != SQLITE_OK)
				{
					// bind failed.	
					/// \todo Add sqlite3 errmsg support.

					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_bind_* failed!", "OgreSQL::getAllNamesLike" );

				}
			}

		//  Iterate through each name in the list

			do
			{

				// Execute the statement

					Result = sqlite3_step(pFileNames);

					if(Result == SQLITE_DONE)
						break;

					if(Result == SQLITE_BUSY)
					{

						/// \warning If you are getting SQLITE_BUSY problems, you could be brave and use "continue".

						// continue;
						break;
					}
					
				// Retrieve the string.

					Filename.assign((const char *)sqlite3_column_text(pFileNames,0));

				// Add the string to the result

					retVec.push_back(Filename);

			}while(Result == SQLITE_ROW);

		// Check for transaction problems.

			if(Result == SQLITE_BUSY)
			{

				/// \todo Attempt to deal with this more smoothly. Possibly wait and retry after a delay.
				LogManager::getSingleton().logMessage( "OgreSQL DB connection reported SQLITE_BUSY. (You can edit this code to ignore this and simply retry.)");

			}

        return retVec;
    };

    //-----------------------------------------------------------------------
    void OgreSQL::load()
	{
        
		// Open the db connection

			int Result = sqlite3_open(mName.c_str(), &pSQLiteDB);

			if(Result != SQLITE_OK)
			{
				/// \todo sqlite errmsg support

				Exception( Exception::ERR_FILE_NOT_FOUND, "OgreSQL DB connection " + mName + " failed.", "OgreSQL::load" );
			}

			LogManager::getSingleton().logMessage( "OgreSQL DB connection to " + mName + " created.");

		// Prepare compiled SQL statements

			std::string SQLStatement;
			const char *pzTail = NULL;	// Pointer to the unussed portion of SQLStatement.c_str() (IGNORED)

			std::string ErrorStatement;

			// pFileOpen

				SQLStatement.assign("SELECT Data FROM Assets WHERE ResourceName LIKE ? ORDER BY Version DESC LIMIT 1");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileOpen, &pzTail);

				if(Result != SQLITE_OK)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load" );
				}

				if(sqlite3_bind_parameter_count(pFileOpen) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileOpen", "OgreSQL::load" );
				}

			// pFileSave

				SQLStatement.assign("INSERT INTO Assets (ResourceName, Data) VALUES(?, ?)");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileSave, &pzTail);

				if(Result != SQLITE_OK)
				{
					ErrorStatement.assign("sqlite3_prepare() failed! (Assets table may be missing.)");
					ErrorStatement.append( sqlite3_errmsg(pSQLiteDB));
					Exception( Exception::ERR_INTERNAL_ERROR, ErrorStatement , "OgreSQL::load" );
				}

				if(sqlite3_bind_parameter_count(pFileSave) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileSave", "OgreSQL::load" );
				}

			// pFileUpdate

				SQLStatement.assign("UPDATE Assets SET ResourceName = :001, Data = :002, LastModified = NULL WHERE ResourceName = :001");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileUpdate, &pzTail);

				if(Result != SQLITE_OK)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load" );
				}

				if(sqlite3_bind_parameter_count(pFileUpdate) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileSave", "OgreSQL::load" );
				}

			// pFileDelete

				SQLStatement.assign("DELETE FROM Assets WHERE ResourceName = ?");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileDelete, &pzTail);

				if(Result != SQLITE_OK)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load" );
				}

				if(sqlite3_bind_parameter_count(pFileDelete) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileRename", "OgreSQL::load" );
				}

			// pFileRename

				SQLStatement.assign("UPDATE Assets SET ResourceName = :001, LastModified = NULL WHERE ResourceName = :002");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileRename, &pzTail);

				if(Result != SQLITE_OK)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load" );
				}

				if(sqlite3_bind_parameter_count(pFileRename) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileRename", "OgreSQL::load" );
				}

			// pFileInfo

				SQLStatement.assign("SELECT Data, LastModified FROM Assets WHERE ResourceName = ? LIMIT 1");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileInfo, &pzTail);

				if(Result != SQLITE_OK)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load" );
				}

				if(sqlite3_bind_parameter_count(pFileInfo) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileRename", "OgreSQL::load" );
				}

			// pFileTest

				SQLStatement.assign("SELECT ResourceName FROM Assets WHERE ResourceName LIKE ? LIMIT 1");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pFileTest, &pzTail);

				if(Result != SQLITE_OK)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load" );
				}

				if(sqlite3_bind_parameter_count(pFileTest) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pFileTest", "OgreSQL::load" );
				}

			// pRecursiveFileNames

				SQLStatement.assign("SELECT DISTINCT ResourceName FROM Assets WHERE ResourceName LIKE ?");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pRecursiveFileNames, &pzTail);

				if(Result != SQLITE_OK)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load" );
				}
				if(sqlite3_bind_parameter_count(pRecursiveFileNames) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pRecursiveFileNames", "OgreSQL::load" );
				}

			// pNonRecursiveFileNames

				SQLStatement.assign("SELECT DISTINCT ResourceName FROM Assets WHERE ResourceName LIKE ? NOT LIKE ?");
				Result = sqlite3_prepare(pSQLiteDB, SQLStatement.c_str(), (int)SQLStatement.size(), &pNonRecursiveFileNames, &pzTail);

				if(Result != SQLITE_OK)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed! Assets table may be missing.", "OgreSQL::load" );
				}
				if(sqlite3_bind_parameter_count(pNonRecursiveFileNames) == 0)
				{
					Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_prepare() failed to detect wildcards in pNonRecursiveFileNames", "OgreSQL::load" );
				}

		//KH###	mIsLoaded = true;


    };

    //-----------------------------------------------------------------------
    void OgreSQL::unload()
	{

		// Finalize the compiled sql statements

		/// \todo it'd be wiser not to ignore the return values here.
			sqlite3_finalize(pFileOpen);
			sqlite3_finalize(pFileDelete);
			sqlite3_finalize(pFileInfo);
			sqlite3_finalize(pFileCopy);
			sqlite3_finalize(pFileRename);
			sqlite3_finalize(pFileSave);
			sqlite3_finalize(pFileTest);
			sqlite3_finalize(pFileUpdate);
			sqlite3_finalize(pNonRecursiveFileNames);
			sqlite3_finalize(pRecursiveFileNames);

		// Close the connection

			if(sqlite3_close(pSQLiteDB) != SQLITE_OK)
			{
				Exception( Exception::ERR_INTERNAL_ERROR, "sqlite3_close() failed because at least one compiled sql statement is not finalized.", "OgreSQL::unload" );
			};

        LogManager::getSingleton().logMessage( "OgreSQL DB connection to " + mName + " closed." );

        delete this;
    };

	//-----------------------------------------------------------------------
	bool OgreSQL::_allowFileCaching(void)
	{

		/** \warning If you're allowing multiple connections to the db file it's best to change this to false.
		* This ensures that each load of a resource gets the newest db entry.  An example of when you
		* would want to do this is using a centralized resource database that's on a shared volume. Artists
		* and programmers can update scripts and assets while the game engine is running - with changes showing up
		* as resources are reloaded as long as the db users are connected to the same db file. Nifty huh?
		*/
		return true;

	}

    //-----------------------------------------------------------------------
	//OgreSQL::OgreSQL(): Archive("", "OgreSQL"), pSQLiteDB(NULL)
	//{
	//
	//}

    //-----------------------------------------------------------------------
	OgreSQL::OgreSQL(const String& name): Archive(name, "OgreSQL"), pSQLiteDB(NULL)
    {

        mName = name;

    }

    //-----------------------------------------------------------------------
    OgreSQL::~OgreSQL()
	{
	
	}

}
