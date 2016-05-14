#ifndef __OGRE_SQL_ARCHIVE_H__
#define __OGRE_SQL_ARCHIVE_H__


// #include "OgrePrerequisites.h"
#include <Ogre/OgreMain/include/Ogre.h>
#include <XEDAL/SqliteArchive/OgreSQLPrereq.hpp>
#include <Ogre/OgreMain/include/OgreArchiveFactory.h>


namespace Ogre
{

	/// Specialization of ArchiveFactory for SQLite DB access.
	/**
	* \ingroup Client
	*
	* \brief
	* ArchiveFactory implementation that allows OGRE to use an OgreSQL object.
	*
	* \par requirements
	* SQLite 3.0 or higher (http://www.sqlite.org/) (tested against 3.0.6b)
	*
	* \version 1.0
	* First version
	*
	* \date 09-04-2004
	*
	* \author Pispor Studios: Anthony Clay
	*
	* \par license This code is hereby released into the public domain, I only ask that you tell me about any
	* improvements that you make, or useful application.
	* 
	* \todo I can't verify that this works on all platforms for right now, but it should. I'll be sure to get
	* around to it, though.
	*
	* \warning Taken directly from Ogre::ZipArchiveFactory
	*
	* \bugs There are no bugs to report.
	*
	*/
	class _OgreSQLExport OgreSQLArchiveFactory : public Ogre::ArchiveFactory
	{
	public:
		OgreSQLArchiveFactory();
		virtual ~OgreSQLArchiveFactory();

		String getArchiveType(void) const;       
		Archive *createInstance(const String& name);
		Archive *createInstance(const String& name, bool readonly);

		/// @copydoc FactoryObj::getType
		const String& getType(void) const;


		/// @copydoc FactoryObj::destroyInstance
		void destroyInstance(Archive* ptr) { OGRE_DELETE ptr; }

	private:
		OgreSQL* mOgreSQL;
	};


}

#endif