#ifndef _WSCREENRENDERABLE_HPP
#define _WSCREENRENDERABLE_HPP

#include <map>

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>


namespace XE
{
	//forwarding
	class ScreenRenderable;
	class Layer;

	class WScreenRenderable
	{

	private:
		ScreenRenderable* m_screenRenderable;
		std::map<Ogre::String, Layer*> m_layers;
	};

} // namespace XE


#endif // _WSCREENRENDERABLE_HPP