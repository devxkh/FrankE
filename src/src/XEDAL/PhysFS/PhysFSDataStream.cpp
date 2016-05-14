#include <XEDAL/PhysFS/PhysFSDataStream.h>

namespace PhysFS
{
	PhysFSDataStream::PhysFSDataStream(const Ogre::String& filename)
	{
		file = PHYSFS_openRead(filename.c_str());
		if (!file)
			Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND, PHYSFS_getLastError(), "PhysFSDataStream::PhysFSDataStream");

		mSize = (size_t)PHYSFS_fileLength(file);
	}

	PhysFSDataStream::PhysFSDataStream(const Ogre::String& name, const Ogre::String& filename)
		: Ogre::DataStream(name)
	{
		file = PHYSFS_openRead(filename.c_str());
		if (!file)
			Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND, PHYSFS_getLastError(), "PhysFSDataStream::PhysFSDataStream");
		mSize = (size_t)PHYSFS_fileLength(file);
	}

	PhysFSDataStream::~PhysFSDataStream()
	{
		close();
	}

	size_t PhysFSDataStream::read(void* buf, size_t count)
	{
		Ogre::int64 read = PHYSFS_read(file, buf, 1, (PHYSFS_uint32)count);
		if (read == -1)
			Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND, PHYSFS_getLastError(), "PhysFSDataStream::PhysFSDataStream");
		return size_t(read);
	}

	void PhysFSDataStream::seek(size_t pos)
	{
		if (!PHYSFS_seek(file, pos))
			Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND, PHYSFS_getLastError(), "PhysFSDataStream::PhysFSDataStream");

	}

	size_t PhysFSDataStream::tell() const
	{
		return (size_t)PHYSFS_tell(file);
	}

	void PhysFSDataStream::skip(long count)
	{
		size_t pos = tell() + count;
		seek(pos);
	}

	bool PhysFSDataStream::eof() const
	{
		return PHYSFS_eof(file) != 0;
	}

	void PhysFSDataStream::close()
	{
		if (file)
			PHYSFS_close(file);
		file = 0;
	}

} //ns physfs
