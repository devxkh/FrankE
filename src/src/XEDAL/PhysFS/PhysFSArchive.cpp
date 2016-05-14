#include <XEDAL/PhysFS/PhysFSArchive.h>

#include <XEDAL/PhysFS/PhysFSWrapper.h>
#include <XEDAL/PhysFS/PhysFSDataStream.h>

//#include <Ogre/OgreMain/include/Ogre.h>
//#include <Ogre/OgreMain/include/OgreArchiveManager.h> // for singleton?
//#include <Ogre/OgreMain/include/OgreLogManager.h>

namespace PhysFS
{
  typedef std::vector<std::string> StringVector;

  void init(const char* argv0, bool symLinks)
  {
	  if (!PHYSFS_init(argv0))
		  Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND, PHYSFS_getLastError(), "PhysFS::init");

	  PHYSFS_permitSymbolicLinks(symLinks);
  }

  void deinit()
  {
	  if (!PHYSFS_deinit())
		  Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND, PHYSFS_getLastError(), "PhysFS::deinit");
  }

  void addToSearchPath(const std::string& location, bool append)
  {
    if (!PHYSFS_addToSearchPath(location.c_str(), append))
		Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND, PHYSFS_getLastError(), "PhysFS::deinit");
  }


  bool PhysFSArchive::exists(const Ogre::String& filename)
  {
	 // return  PHYSFS_exists((mName + '/' + filename).c_str()) != 0;
	  return  PHYSFS_exists(filename.c_str()) != 0;
  }

  StringVector enumerateFiles(const std::string& dir)
  {
    StringVector list;
    char** lst = PHYSFS_enumerateFiles(dir.c_str());
    for (char** l = lst; *l != 0; ++l)
      list.push_back(*l);
    PHYSFS_freeList(lst);
    return list;
  }

  bool isDirectory(const std::string& path)
  {
    return PHYSFS_isDirectory(path.c_str()) != 0;
  }

  Ogre::DataStreamPtr PhysFSArchive::open(const Ogre::String& filename, bool readOnly ) 
  {
   // Ogre::String fullName = mName + '/' + filename;
	Ogre::String fullName = filename;
	return Ogre::DataStreamPtr(new PhysFSDataStream(filename, fullName));
  }

  void PhysFSArchive::listInfoRecursive(const Ogre::String& base, bool recursive, bool dirs, Ogre::FileInfoListPtr fileInfoList)
  {
  //  Ogre::String baseDir = mName + '/' + base;
	Ogre::String baseDir = base;
	StringVector files = enumerateFiles(baseDir);

    Ogre::FileInfo fileInfo;
    fileInfo.archive = this;
    fileInfo.path = base;
    fileInfo.compressedSize = 0;

    // iterate over all files and directories in the given directory
    for (StringVector::iterator it = files.begin(); it != files.end(); ++it)
    {
      fileInfo.basename = *it;
      fileInfo.filename = base + *it;
      if (isDirectory(fileInfo.filename)) //*it))
      {
        if (dirs)
        {
          fileInfo.uncompressedSize = 0;
          fileInfoList->push_back(fileInfo);
        }
        if (recursive)
          listInfoRecursive(base+*it+'/', recursive, dirs, fileInfoList);
      }
      else
      {
        if (!dirs)
        {
          // get file size
		//	PHYSFS_File* file = PHYSFS_openRead((mName + '/' + fileInfo.filename).c_str());
			PHYSFS_File* file = PHYSFS_openRead((fileInfo.filename).c_str());
          fileInfo.uncompressedSize = (size_t) PHYSFS_fileLength(file);
          PHYSFS_close(file);

          fileInfoList->push_back(fileInfo);
        }
      }
    }
  }

  void PhysFSArchive::listRecursive(const Ogre::String& base, bool recursive, bool dirs, Ogre::StringVectorPtr fileList)
  {
 //   Ogre::String baseDir = mName + '/' + base;
	Ogre::String baseDir = base;
	StringVector files = enumerateFiles(baseDir);

    // iterate over all files and directories in the given directory
    for (StringVector::iterator it = files.begin(); it != files.end(); ++it)
    {
      if (isDirectory(*it))
      {
        if (dirs)
          fileList->push_back(base + *it);
        if (recursive)
          listRecursive(base+*it+'/', recursive, dirs, fileList);
      }
      else
      {
        if (!dirs)
          fileList->push_back(base + *it);
      }
    }
  }


  Ogre::FileInfoListPtr PhysFSArchive::listFileInfo(bool recursive, bool dirs)
  {
    Ogre::FileInfoListPtr fileInfoList (new Ogre::FileInfoList());
    listInfoRecursive("", recursive, dirs, fileInfoList);

    return fileInfoList;
  }

  Ogre::StringVectorPtr PhysFSArchive::list(bool recursive, bool dirs)
  {
    Ogre::StringVectorPtr fileList (new Ogre::StringVector());
    listRecursive("", recursive, dirs, fileList);
    return fileList;
  }


  Ogre::StringVectorPtr PhysFSArchive::find(const Ogre::String& pattern, bool recursive, bool dirs)
  {
    Ogre::StringVectorPtr fileList = list(recursive, dirs);
    Ogre::StringVectorPtr ret (new Ogre::StringVector());

    for (Ogre::StringVector::iterator it = fileList->begin(); it != fileList->end(); ++it)
    {
      if (Ogre::StringUtil::match(*it, pattern))
        ret->push_back(*it);
    }

    return ret;
  }

  Ogre::FileInfoListPtr PhysFSArchive::findFileInfo(const Ogre::String& pattern, bool recursive, bool dirs) 
  {
	  Ogre::FileInfoListPtr fileList = listFileInfo(recursive, dirs);
	  Ogre::FileInfoListPtr ret(new Ogre::FileInfoList());

	  for (Ogre::FileInfoList::iterator it = fileList->begin(); it != fileList->end(); ++it)
	  {
		  if (Ogre::StringUtil::match(it->filename, pattern))
			  ret->push_back(*it);
	  }


	  return ret;
	  //todo?
	 /* m_fileList = listFileInfo(recursive, dirs);

	  Ogre::FileInfoListPtr ret(OGRE_NEW_T(Ogre::FileInfoList, Ogre::MEMCATEGORY_GENERAL)(), Ogre::SharedPtrFreeMethod::SPFM_DELETE_T);

	  for (Ogre::FileInfoList::iterator it = m_fileList->begin(); it != m_fileList->end(); ++it)
	  {
		  if (Ogre::StringUtil::match(it->filename, pattern))
			  ret->push_back(*it);
	  }

	  return ret;*/
  }

  /// @copydoc Archive::getModifiedTime
  time_t PhysFSArchive::getModifiedTime(const Ogre::String& filename)
  {
	  time_t tmp;
	  return tmp;
  }

  void registerPhysFSToOgre()
  {
	  
	  //  PhysFSArchiveFactory* instance = PhysFSArchiveFactory::getInstance();//  new Ogre::OgreSQLArchiveFactory();
	//  instance->createInstance("PhysFSData");

	  //Ogre::ArchiveFactory *fac = new PhysFSArchiveFactory;
	  //PhysFSArchiveFactory *archive = (PhysFSArchiveFactory*)fac->createInstance("path");
	  ////   archive->exists("file");
	  ////   archive->remove("file");
	  //Ogre::LogManager::getSingleton().logMessage("");
	  //Ogre::ArchiveManager::getSingleton().addArchiveFactory(fac);
  }
}
