#ifndef __DB_H__
#define __DB_H__

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>

typedef struct sqlite3 sqlite3;

namespace XE {

	class DB
	{

	protected:
		void open();
		void close();
		void execute(Ogre::String sql);
	protected:
		sqlite3* mDB;

	private:
		int mSQLCode;
		Ogre::String mQuery = "";
		char* mErrMsg = 0;
	};

} // ns XE

#endif // __DB_H__