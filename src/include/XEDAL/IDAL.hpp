#ifndef __DB_H__
#define __DB_H__

#include <XESystem/SystemConfig.hpp>
#include <string>

typedef struct sqlite3 sqlite3;

namespace XE {

	class XEngine;
	class Scene;

	typedef int(*sceneNodes_callback)(XE::Scene& scenePointer, XE::Int32 entID, char* entityData, bool replicateEntity);

	class XEngine;

	class IDAL
	{
	public:

		struct BinaryResult
		{
		public:
			const void* binData;
			int len;
		};

		IDAL(XEngine& engine);

		void open();
		void close();

		virtual const void* getState(const char* name, int namelen) = 0;
		virtual char* getScene(XE::Uint16 id) = 0;
		virtual char* getEntity(XE::Uint16 id) = 0;
		virtual void getSceneNodes(XE::Scene& scene, XE::Uint16 sceneID, sceneNodes_callback xCallback) = 0;

	protected:
		
		void execute(std::string sql);
	protected:
		sqlite3* mDB;

	private:

		XEngine& m_engine;
		int mSQLCode;
		std::string mQuery = "";
		char* mErrMsg = 0;
	};

} // ns XE

#endif // __DB_H__