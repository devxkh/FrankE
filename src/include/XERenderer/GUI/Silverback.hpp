
#ifndef _SILVERBACK_HPP
#define _SILVERBACK_HPP

#include <map>

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <Ogre/OgreMain/include/OgreVector2.h>


//#include <

namespace XE
{

	/* class. Silverback
	desc.
	Main singleton class for Gorilla
	*/
	//class Silverback : public Ogre::GeneralAllocatedObject, public Ogre::FrameListener //public Ogre::Singleton<Silverback>,
	//{

	//public:

	//	/*! constructor. Silverback
	//	desc.
	//	Silverback constructor.
	//	*/
	//	Silverback();

	//	/*! destructor. Silverback
	//	desc.
	//	Silverback destructor.
	//	*/
	//	~Silverback();

	//	/*! function. loadAtlas
	//	desc.
	//	Create a TextureAtlas from a ".gorilla" file.

	//	Name is the name of the TextureAtlas, as well as the first part of the filename
	//	of the gorilla file; i.e. name.gorilla, the gorilla file can be loaded from a different
	//	resource group if you give that name as the second argument, otherwise it will assume
	//	to be "General".
	//	*/
	//	void loadAtlas(const Ogre::String& name, const Ogre::String& group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	//	/*! function. createScreen
	//	desc.
	//	Create a Screen using a Viewport and a name of a previously loaded TextureAtlas.
	//	Both must exist. The screen will register itself as a RenderQueueListener to the
	//	SceneManager that has the Camera which is tied to the Viewport.
	//	note.
	//	Each screen is considered a new batch. To reduce your batch count in Gorilla,
	//	reduce the number of screens you use.
	//	*/
	//	Screen* createScreen(Ogre::Viewport*, const Ogre::String& atlas);

	//	/*! function. destroyScreen
	//	desc.
	//	Destroy an existing screen, its layers and the contents of those layers.
	//	*/
	//	void destroyScreen(Screen*);

	//	/*! function. createScreenRenderable
	//	*/
	//	ScreenRenderable* createScreenRenderable(const Ogre::Vector2& maxSize, const Ogre::String& atlas, Ogre::ObjectMemoryManager* objManager);

	//	/*! function. destroyScreen
	//	desc.
	//	Destroy an existing screen, its layers and the contents of those layers.
	//	*/
	//	void destroyScreenRenderable(ScreenRenderable*);

	//	/*! function. frameStarted
	//	desc.
	//	Call ScreenRenderable draw
	//	*/
	//	bool frameStarted(const Ogre::FrameEvent& evt);

	//protected:

	//	std::map<Ogre::String, TextureAtlas*>  mAtlases;
	//	std::vector<Screen*>                   mScreens;
	//	std::vector<ScreenRenderable*>         mScreenRenderables;

	//};


} // ns XE
#endif // _SILVERBACK_HPP