#ifndef XE_RESOURCESTREAM_HPP
#define XE_RESOURCESTREAM_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <sfml/System/InputStream.hpp>
#include <Ogre/OgreMain/include/OgreDataStream.h>

namespace XE {

	class ResourceStream : public sf::InputStream
	{
	public:
		ResourceStream();
		~ResourceStream();

		ResourceStream(Ogre::DataStreamPtr* dataStreamPtr);
		sf::Int64 read(void* data, sf::Int64 size);

		sf::Int64 seek(sf::Int64 position);
		sf::Int64 tell();
		sf::Int64 getSize();

		Ogre::DataStreamPtr* mDataStreamPtr;
	};

}

#endif // XE_RESOURCESTREAM_HPP