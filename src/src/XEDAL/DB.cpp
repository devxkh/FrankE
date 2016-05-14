#include <XEDAL/DB.hpp>

#include <Sqlite/sqlite3.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>

using namespace XE;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){

	int i;

	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

void DB::open()
{
	char *zErrMsg = 0;

	std::string dbName = "F:\\Projekte\\coop\\XGame\\data\\dbData.s3db";

	//Attempt to open database. If it does not exist create it.
	mSQLCode = sqlite3_open(dbName.c_str(), &mDB);

	if (mSQLCode){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(mDB));
		sqlite3_close(mDB);
		exit(1);
	}
}

void DB::close()
{
	sqlite3_close(mDB); //Always close db when done with it
	printf("\nPress Enter.");
	getch();
}

void DB::execute(Ogre::String sql)
{

	//--------------------------
	//All UPPERCASE !!!!!!!
	//---------------------------
	mQuery = sql;//"SELECT * FROM PHYSICOBJECT WHERE PO_ID=0;";
	mSQLCode = sqlite3_exec(mDB, mQuery.c_str(), callback, 0, &mErrMsg);

	if (mSQLCode != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", mErrMsg);
		sqlite3_free(mErrMsg);
	}

}

