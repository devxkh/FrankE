#ifndef XE_SOUNDFACTORY_HPP
#define XE_SOUNDFACTORY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre/OgreMain/include/OgreMovableObject.h>

namespace XE {

	//! MovableFactory for creating Sound instances 
	class SoundFactory : public Ogre::MovableObjectFactory
	{

	protected:
		Ogre::MovableObject* createInstanceImpl(const Ogre::String& name, const Ogre::NameValuePairList* params);
	
	public:
		SoundFactory() {}
		~SoundFactory() {}

		static Ogre::String FACTORY_TYPE_NAME;

		const Ogre::String& getType(void) const;
		void destroyInstance(Ogre::MovableObject* obj);

	};

}	// namespace XE
#endif // XE_SOUNDFACTORY_HPP