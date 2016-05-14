#ifndef __STATICRENDERABLE_HPP__
#define __STATICRENDERABLE_HPP__

//#include <Ogre/OgreMain/include/OgreMesh.h>
#include <sfml/Config.hpp>
//#include <Ogre/OgreMain/include/OgreVector3.h>
//#include <Ogre/OgreMain/include/OgreQuaternion.h>
//#include <Ogre/OgreMain/include/OgreMatrix4.h>
#include <XERenderer/Renderable.hpp>

namespace XE {

	class GraphicsManager;
	class Scene;

	//class OgreEntity
	struct StaticRenderable : Renderable {

	public:

		 StaticRenderable(sf::Uint16 id, GraphicsManager& gmanager, Scene& scene, const void* fbData);


	protected:

	private:



	};

}


#endif //__STATICRENDERABLE_HPP__