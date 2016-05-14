#include <XEAudio/XEResourceStream.hpp>

namespace XE{

	ResourceStream::ResourceStream(){}
	ResourceStream::~ResourceStream(){}

	ResourceStream::ResourceStream(Ogre::DataStreamPtr* dataStreamPtr)
	{
		mDataStreamPtr = dataStreamPtr;
	}

	Ogre::int64 ResourceStream::read(void* data, Ogre::int64 size)
	{
		return mDataStreamPtr->get()->read(data,size);
	}

	Ogre::int64 ResourceStream::seek(Ogre::int64 position)
	{ 
		mDataStreamPtr->get()->seek(position);
		return position;
	}

	Ogre::int64 ResourceStream::tell()
	{
		return  mDataStreamPtr->get()->tell();
	}

	Ogre::int64 ResourceStream::getSize()
	{
		return  mDataStreamPtr->get()->size();
	}

} //namespace XE

