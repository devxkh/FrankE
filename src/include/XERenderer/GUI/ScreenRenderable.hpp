
#ifndef _SCREENRENDERABLE_HPP
#define _SCREENRENDERABLE_HPP

#include <map>

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <Ogre/OgreMain/include/OgreVector2.h>
#include <Ogre/OgreMain/include/OgreSimpleRenderable.h>
#include <Ogre/OgreMain/include/OgreCamera.h>
#include <XERenderer/GUI/GorillaRenderer.hpp>

namespace XE
{


	//class ScreenRenderable : public LayerContainer, public Ogre::v1::SimpleRenderable
	//{

	//public:

	//	ScreenRenderable(const Ogre::Vector2& maxSize, TextureAtlas*, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr);

	//	~ScreenRenderable();

	//	void frameStarted();
	//	void renderOnce();
	//	void _transform(buffer<Vertex>& vertices, size_t begin, size_t end);
	//	void calculateBoundingBox();

	//	float getBoundingRadius(void) const { return mBox.getMaximum().squaredLength(); }

	//	float getSquaredViewDepth(const Ogre::Camera* cam) const
	//	{
	//		Ogre::Vector3 min, max, mid, dist;
	//		min = mBox.getMinimum();
	//		max = mBox.getMaximum();
	//		mid = ((max - min) * 0.5) + min;
	//		dist = cam->getDerivedPosition() - mid;
	//		return dist.squaredLength();
	//	}

	//protected:

	////	Ogre::SceneManager*   mSceneMgr;
	////	Ogre::RenderSystem*   mRenderSystem;
	////	Ogre::Viewport*       mViewport;
	//	Ogre::Vector2         mMaxSize;

	//};
} // ns XE
#endif // _SCREENRENDERABLE_HPP