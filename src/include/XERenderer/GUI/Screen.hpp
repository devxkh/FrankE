
#ifndef _SCREEN_HPP
#define _SCREEN_HPP

#include <map>

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <Ogre/OgreMain/include/OgreVector2.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreRenderOperation.h>
#include <Ogre/OgreMain/include/OgreMatrix4.h>
#include <Ogre/OgreMain/include/OgreRenderSystem.h>
#include <Ogre/OgreMain/include/OgreFrustum.h>

#include <Ogre/OgreMain/include/OgreRenderQueueListener.h>

#include <XERenderer/GUI/GorillaRenderer.hpp>
#include <XERenderer/GUI/LayerRenderer.hpp>

namespace XE
{
	class CameraRenderable;
	///Structure for a single vertex.		
	struct Vertex;

	class Screen : public LayerRenderer //, public Ogre::GeneralAllocatedObject //, public Ogre::RenderQueueListener
	{
	public:

		inline void setSize(const float width, const float height) { update(width, height); }

		/*! desc. isVisible
		Is the screen and it's contents visible or not?
		note.
		If the screen is hidden, then it is not rendered which decrease the batch count by one.
		*/
		inline bool isVisible() const { return mIsVisible; }

		/*! desc. setVisible
		Show or hide the screen.
		*/
		inline void setVisible(bool value) { mIsVisible = value; }

		/*! desc. hide
		Hide the screen and the all of layers within it.
		*/
		inline void hide() { mIsVisible = false; }

		/*! desc. show
		Show the screen and the visible layers within it.
		*/
		inline void show() { mIsVisible = true; }

#if OGRE_NO_VIEWPORT_ORIENTATIONMODE == 1
		inline void setOrientation(Ogre::OrientationMode o)
		{
			mOrientation = o; mOrientationChanged = true;

			if (mOrientation == Ogre::OR_DEGREE_90 || mOrientation == Ogre::OR_DEGREE_270)
			{
				std::swap(mWidth, mHeight);
				std::swap(mInvWidth, mInvHeight);
			}
		}
#endif

		Screen(TextureAtlas* atlas, CameraRenderable* camera);

		~Screen();

		void update(float width, float height);

		// Internal -- Renders mVertexData to screen.
		void renderOnce();

		Ogre::SceneManager*   mSceneMgr;
	protected:

		// Internal -- Prepares RenderSystem for rendering.
		void _prepareRenderSystem();


		// Internal -- Used to transform vertices using units of pixels into screen coordinates.
		void _transform(std::vector<Vertex>& vertices, size_t begin, size_t end);
	private:
	

		bool					mForce;
		Ogre::v1::RenderOperation mRenderOp;
		Ogre::RenderSystem*   mRenderSystem;
	//	Ogre::Viewport*       mViewport;
		float            mWidth, mHeight, mInvWidth, mInvHeight;
		Ogre::OrientationMode mOrientation;
#if OGRE_NO_VIEWPORT_ORIENTATIONMODE == 1
		bool                  mOrientationChanged;
#endif
		Ogre::Vector3         mScale;
		bool                  mIsVisible;
		bool                  mCanRender;
		Ogre::Matrix4         mVertexTransform;

	};

} // ns XE
#endif // _SCREEN_HPP