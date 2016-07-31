#include <XEDAL/IDAL.hpp>

#include <XEngine.hpp>

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

IDAL::IDAL(XEngine& engine)
	: m_engine(engine)
{

}

void IDAL::open()
{
	char *zErrMsg = 0;

	//Attempt to open database. If it does not exist create it.
	mSQLCode = sqlite3_open((m_engine.settings.dataRootFolder + "/dbData.s3db").c_str(), &mDB);

	if (mSQLCode){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(mDB));
		sqlite3_close(mDB);
		exit(1);
	}
}

void IDAL::close()
{
	sqlite3_close(mDB); //Always close db when done with it
	printf("\nPress Enter.");
	getch();
}

void IDAL::execute(std::string sql)
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

