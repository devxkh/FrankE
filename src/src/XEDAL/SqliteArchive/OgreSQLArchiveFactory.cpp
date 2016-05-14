#include <XEDAL/SqliteArchive/OgreSQL.hpp>
#include <XEDAL/SqliteArchive/OgreSQLArchiveFactory.hpp>

namespace Ogre {

	OgreSQLArchiveFactory::OgreSQLArchiveFactory()
		: mOgreSQL(nullptr)
	{

	}
		
	OgreSQLArchiveFactory::~OgreSQLArchiveFactory()
    {
    }

    //-----------------------------------------------------------------------
    String OgreSQLArchiveFactory::getArchiveType(void) const
    {
        return "OgreSQL";
    }

    //-----------------------------------------------------------------------
	Archive *OgreSQLArchiveFactory::createInstance(const String& name)
    {
		return mOgreSQL = OGRE_NEW OgreSQL(name);
    }

	Archive *OgreSQLArchiveFactory::createInstance(const String& name, bool readonly)
	{
		return mOgreSQL = OGRE_NEW OgreSQL(name);
	}

	const String& OgreSQLArchiveFactory::getType(void) const
	{
		return "OgreSQL";
	}


    //String OgreSQLArchiveFactory::getType() const
    //{
    //    return "OgreSQL";
    //}

}
