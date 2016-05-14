#ifndef __PHYSFS_DATASTREAM_H__
#define __PHYSFS_DATASTREAM_H__

#include <Ogre/OgreMain/include/OgreDataStream.h>

//important! physfs uses his own zlib version!
extern "C"
{
	#include <extlibs/headers/physfs/physfs.h>
}
namespace PhysFS
{
	/** Datastream implementation for Ogre */
	class PhysFSDataStream : public Ogre::DataStream
	{
	public:
		PhysFSDataStream(const Ogre::String& filename);
		PhysFSDataStream(const Ogre::String& name, const Ogre::String& filename);
		~PhysFSDataStream();

		size_t read(void* buf, size_t count);
		void skip(long count);
		void seek(size_t pos);
		size_t tell() const;
		bool eof() const;
		void close();

	private:
		PHYSFS_File* file;
	};

} //ns physfs

#endif