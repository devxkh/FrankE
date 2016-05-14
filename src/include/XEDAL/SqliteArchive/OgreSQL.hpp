#ifndef __OGRE_SQL_H__
#define __OGRE_SQL_H__


// #include "OgrePrerequisites.h"
#include <Ogre/OgreMain/include/Ogre.h>
#include <Ogre/OgreMain/include/OgrePrerequisites.h>
//#include <Ogre/OgreMain/include/OgreArchiveManager.h>
// #include "OgreArchiveEx.h"
#include <vector>
#include <Ogre/OgreMain/include/OgreStreamSerialiser.h>

extern "C"
{
#include <Sqlite/sqlite3.h>
}

using namespace Ogre;

namespace Ogre {

	/**
	* \ingroup Client
	*
	* \brief An SQLlite archive codec for OGRE.
	*
	* \par requirements
	* ANSI compliance
	* SQLite 3.0 or higher (http://www.sqlite.org/) (tested against 3.0.6b)
	*
	* \version 1.0
	* First version
	*
	* \date 09-04-2004
	*
	* \author Pispor Studios: Anthony Clay
	*
	* \par license This code provided free of charge with no warranty or guarantees whatsoever - express or implied.
	*
	* \warning I bothered to implement most of the ArchiveEx base class for some reason.  But if you wish to use this
	* database to it's fullest potential, then I advise that you not become dependant on too much more than basic file
	* reading operations.  I'll be sure to post why on the OGRE forums.
	*
	* \warning I've decided not to implement any of the directory functions, at least for now. The operations involved
	* (while perfectly possible) are memory/disk intensive, and complex.  This is enough for an initial version.
	*
	* \warning This database does not compress it's data.  It may be possible to build a trigger into the database
	* that compresses data, or add a function that does the same (as a component of the db).
	*
	* \todo I can't verify that this works on all platforms for right now, but it should. I'll be sure to get
	* around to it, though.  Feel free to beat me to it.
	*
	* \todo Add network support.  Support for other database types. (possibly separate plugins.)
	*
	* \todo My judicious use of new[]/delete[] may offend people.  Consider switching to using Ogre's dataChunk class.
	*
	* \bug It should be expressly noted that out of the box, SQLite (once?) had an approx ~1MB limit on row sizes.
	* This appears to not be true.  If anyone is willing to test the limits of just how big a file you can insert,
	* I'd be eternally grateful.  (My hunch is that it's limited only by memory now.)
	*
	* \todo sfrtime() doesn't seem to work correctly on inserts, I'm working on it. But it's broken for now.
	*
	*/
    class OgreSQL : public Archive
	{
    public:
      //  OgreSQL();
        OgreSQL(const String& name );
        ~OgreSQL();

		/// @copydoc Archive::isCaseSensitive
		bool isCaseSensitive(void) const { return false; }

		/// @copydoc Archive::load
		void load();
		/// @copydoc Archive::unload
		void unload();

		/// @copydoc Archive::open
		DataStreamPtr open(const String& filename, bool readOnly = true);

		/// @copydoc Archive::create
		DataStreamPtr create(const String& filename) const;

		/// @copydoc Archive::remove
		void remove(const String& filename) const;

		/// @copydoc Archive::list
		StringVectorPtr list(bool recursive = true, bool dirs = false);

		/// @copydoc Archive::listFileInfo
		FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false);

		/// @copydoc Archive::find
		StringVectorPtr find(const String& pattern, bool recursive = true,
			bool dirs = false);

		/// @copydoc Archive::findFileInfo
		FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true,
			bool dirs = false)  ;

		/// @copydoc Archive::exists
		bool exists(const String& filename);

		/// @copydoc Archive::getModifiedTime
		time_t getModifiedTime(const String& filename);

        bool fileOpen( const String& strFile, FILE** ppFile );
		bool fileRead(const String& strFile, StreamSerialiser::Chunk** ppChunk);

        bool fileSave( FILE* pFile, const String& strPath, bool bOverwrite = false );
        bool fileWrite( const StreamSerialiser::Chunk& refChunk, const String& strPath, bool bOverwrite = false );

        bool fileDele( const String& strFile );
        bool fileMove( const String& strSrc, const String& strDest, bool bOverwrite );

        bool fileInfo( const String& strFile, FileInfo** ppInfo );
        bool fileCopy( const String& strSrc, const String& strDest, bool bOverwrite );

        bool fileTest( const String& strFile );

        std::vector<String> dirGetFiles( const String& strDir );
        std::vector<String> dirGetSubs( const String& strDir );

        bool dirDele( const String& strDir, bool bRecursive );
        bool dirMove( const String& strSrc, const String& strDest, bool bOverwrite );

        bool dirInfo( const String& strDir, FileInfo** ppInfo ) ;
        bool dirCopy( const String& strSrc, const String& strDest, bool bOverwrite );

        bool dirTest( const String& strDir ) ;

		std::vector<String> getAllNamesLike(const String& strStartPath, const String& strPattern, bool bRecursive = true);

        bool _allowFileCaching(void) ;

    private:

		/// SQLite Database Connection
        sqlite3* pSQLiteDB;

		/// SQLite Prepared statements.
		sqlite3_stmt* pFileOpen;

		sqlite3_stmt* pFileSave;

		sqlite3_stmt* pFileUpdate;

		sqlite3_stmt* pFileDelete;

		sqlite3_stmt* pFileRename;

		sqlite3_stmt* pFileInfo;

		sqlite3_stmt* pFileCopy;

		sqlite3_stmt* pFileTest;

		sqlite3_stmt* pRecursiveFileNames;

		sqlite3_stmt* pNonRecursiveFileNames;


    };

}

#endif