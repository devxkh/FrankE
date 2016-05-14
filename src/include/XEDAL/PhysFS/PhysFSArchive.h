#ifndef __PHYSFS_ARCHIVE_H__
#define __PHYSFS_ARCHIVE_H__

#include <Ogre/OgreMain/include/OgreArchiveFactory.h>
#include <Ogre/OgreMain/include/OgreArchive.h>
#include <Ogre/OgreMain/include/OgreArchiveManager.h>

namespace PhysFS
{
	void init(const char* argv0, bool symLinks = false);

	void deinit();
	
	void addToSearchPath(const std::string& location, bool append);

	/** Archive implementation for Ogre */
	class PhysFSArchive : public Ogre::Archive
	{
	public:
		
		PhysFSArchive(const Ogre::String& name, const Ogre::String& type) 
			: Ogre::Archive(name, type)
		{ 
			PhysFS::addToSearchPath(name, true);
			//		PhysFS::addToSearchPath("F:/Projekte/coop/XGame/data/assets", true);


			m_fileList = listFileInfo(true,true);

		}

		/** PhysFS is case sensitive in general */
		bool isCaseSensitive() const { return true; }

		/** Nothing to load */
		void load() { }
		/** Nothing to unload */
		void unload() { }

		/// @copydoc Archive::open
		Ogre::DataStreamPtr open(const Ogre::String& filename, bool readOnly = true) ;
	//	Ogre::DataStreamPtr open(const Ogre::String& filename) const;


		Ogre::StringVectorPtr list(bool recursive = true, bool dirs = false);
		Ogre::FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false);

		Ogre::StringVectorPtr find(const Ogre::String& pattern, bool recursive = true, bool dirs = false);


		bool exists(const Ogre::String& filename);

		/// @copydoc Archive::findFileInfo
		Ogre::FileInfoListPtr findFileInfo(const Ogre::String& pattern, bool recursive = true, bool dirs = false) ;
		//Ogre::FileInfoListPtr findFileInfo(const Ogre::String& pattern, bool recursive = true, bool dirs = false);

		/// @copydoc Archive::getModifiedTime
		time_t getModifiedTime(const Ogre::String& filename);

	private:
		Ogre::FileInfoListPtr m_fileList;

		void listInfoRecursive(const Ogre::String& base, bool recursive, bool dirs, Ogre::FileInfoListPtr fileInfoList);
		void listRecursive(const Ogre::String& base, bool recursive, bool dirs, Ogre::StringVectorPtr fileList);
	};


	/** ArchiveFactory for PhysFS */
	class PhysFSArchiveFactory : public Ogre::ArchiveFactory
	{
	public:
		/** ArchiveFactory typename: PhysFS */
		const Ogre::String& getType() const { static const Ogre::String type = "PhysFS"; return type; }

		Ogre::Archive *createInstance(const Ogre::String& name, bool readonly)
		{
			return OGRE_NEW PhysFSArchive(name, getType());
		}
		
		Ogre::Archive* createInstance(const Ogre::String& name)
		{
			return OGRE_NEW PhysFSArchive(name, getType());
		}

		void destroyInstance(Ogre::Archive* instance)
		{
			OGRE_DELETE instance;
		}

		//static PhysFSArchiveFactory* getInstance()
		//{
		//	static PhysFSArchiveFactory instance;
		//	return &instance;
		//}

	private:
		/*PhysFSArchiveFactory() {}
		PhysFSArchiveFactory(const PhysFSArchiveFactory& o);
		PhysFSArchiveFactory& operator=(const PhysFSArchiveFactory& o);*/
	};

  /**
   * Register the PhysFS system to Ogre's archive manager.
   * This allows you to use the PhysFS system for your resources, just
   * pass "PhysFS" as the location type when adding PhysFS locations
   * to Ogre's resource group manager.
   *
   * Note that this function instantiates a singleton inheriting from
   * Ogre::ArchiveFactory. The singleton will live until the application
   * is shut down. By then, you should have destroyed the Ogre system.
   * Also note that, naturally, you must have PhysFS initialised in order
   * to successfully access any resources with it.
   * I suggest that you initialise PhysFS before Ogre and shut it down after
   * Ogre. This way, you should be fine. Call this function only after
   * Ogre has been initialised!
   */
  void registerPhysFSToOgre();
}

#endif
