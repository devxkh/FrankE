#ifndef _sfmlphysfs_
#define _sfmlphysfs_

//important! physfs uses his own zlib version!
extern "C"
{
	#include <extlibs/headers/PhysFS/physfs.h>
}

#include <sfml/System/InputStream.hpp>

namespace sf{

	class PhysFsStream : public sf::InputStream
	{
	public:

		PhysFsStream(const char* filename = 0x0) :
			m_File(0x0)
		{
			if (filename)
				open(filename);
		}

		virtual ~PhysFsStream()
		{
			close();
		}

		bool isOpen() const
		{
			return (m_File != 0x0);
		}

		bool open(const char* filename)
		{
			close();
			m_File = PHYSFS_openRead(filename);
			return isOpen();
		}

		void close()
		{
			if (isOpen())
				PHYSFS_close(m_File);
			m_File = 0x0;
		}

		virtual sf::Int64 read(void* data, sf::Int64 size)
		{
			if (!isOpen())
				return -1;

			// PHYSFS_read returns the number of 'objects' read or -1 on error.
			// We assume our objects are single bytes and request to read size
			// amount of them.
			return PHYSFS_read(m_File, data, 1, static_cast<PHYSFS_uint32>(size));
		}

		virtual sf::Int64 seek(sf::Int64 position)
		{
			if (!isOpen())
				return -1;

			// PHYSFS_seek return 0 on error and non zero on success
			if (PHYSFS_seek(m_File, position))
				return tell();
			else
				return -1;
		}

		virtual sf::Int64 tell()
		{
			if (!isOpen())
				return -1;

			// PHYSFS_tell returns the offset in bytes or -1 on error just like SFML wants.
			return PHYSFS_tell(m_File);
		}

		virtual sf::Int64 getSize()
		{
			if (!isOpen())
				return -1;

			// PHYSFS_fileLength also the returns length of file or -1 on error just like SFML wants.
			return PHYSFS_fileLength(m_File);
		}

	private:
		PHYSFS_File* m_File;

	};

}

#endif
