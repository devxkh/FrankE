#ifndef __OGRECHARENTITY_HPP__
#define __OGRECHARENTITY_HPP__

#include <XERenderer/EntityRenderable.hpp>

namespace XE {

	class GraphicsManager;
	class Scene;

	class OgreCharEntity 
	{
	public:
		OgreCharEntity(OgreEntity& ogreEntity);

		virtual void create(const char* fbData);

	private:

		OgreEntity& m_ogreEntity;
	};
}


#endif //__OGRECHARENTITY_HPP__