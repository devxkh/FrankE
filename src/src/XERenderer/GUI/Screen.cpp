#include <XERenderer/GUI/Screen.hpp>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include <Ogre/OgreMain/include/OgreFrustum.h>
#include <XERenderer/CameraRenderable.hpp>
#include <Ogre/OgreMain/include/OgreCamera.h>

#include <Ogre/OgreMain/include/OgreHlmsManager.h>
#include <Ogre/OgreMain/include/OgreHlms.h>
#include <Ogre/OgreMain/include/OgrePass.h>

namespace XE
{
//	Ogre::HlmsBlendblock* blendblock;


	Screen::Screen(TextureAtlas* atlas, CameraRenderable* camera)
		: LayerRenderer(camera->getGraphicsManager()), mScale(1, 1, 1), mIsVisible(true), mCanRender(false)
	{
		//mRenderOpPtr = &mRenderOp;
		
		mSceneMgr = camera->getOgreCamera()->getSceneManager();

		mRenderSystem = camera->getOgreCamera()->getRenderSystem();

	/*	mWidth = mViewport->getActualWidth();
		mHeight = mViewport->getActualHeight();*/
#if OGRE_NO_VIEWPORT_ORIENTATIONMODE == 0
		mOrientation = mViewport->getOrientationMode();
#else
		mOrientation = Ogre::OR_DEGREE_0;
		mOrientationChanged = false;
#endif

		/*mInvWidth = 1.0f / mWidth;
		mInvHeight = 1.0f / mHeight;*/

		mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(1, 0, 0, 0));

	//	mSceneMgr->addRenderQueueListener(this);
	//	_createVertexBuffer(32);

	//	blendblock = new Ogre::HlmsBlendblock();
	}

	Screen::~Screen()
	{
	//	mSceneMgr->removeRenderQueueListener(this);
	}


	//void Screen::renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation)
	//{
	//	/*if (mRenderSystem->_getViewport() != mViewport || queueGroupId != SCREEN_RENDERQUEUE)
	//		return;*/
	//	if (mIsVisible && mLayers.size())
	//		renderOnce();
	//}

	void Screen::_prepareRenderSystem()
	{
		mRenderSystem->_setWorldMatrix(Ogre::Matrix4::IDENTITY);
		mRenderSystem->_setProjectionMatrix(Ogre::Matrix4::IDENTITY);
		mRenderSystem->_setViewMatrix(Ogre::Matrix4::IDENTITY);
	
		Ogre::Pass* pass =mAtlas->get2DPass();
		//Ogre::HlmsMacroblock macroblock;
		//Ogre::HlmsBlendblock blendblock;
		//macroblock.mCullMode = Ogre::CULL_NONE;
		//macroblock.mDepthCheck = false;
		//macroblock.mDepthWrite = false;
		////Alpha blending
		//blendblock.mSeparateBlend = true;
		//blendblock.mSourceBlendFactor = Ogre::SBF_SOURCE_ALPHA;
		//blendblock.mSourceBlendFactorAlpha = Ogre::SBF_SOURCE_ALPHA;
		//blendblock.mDestBlendFactor = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
		//blendblock.mDestBlendFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;

		//mRenderSystem->_setHlmsBlendblock(blendblock);

		mSceneMgr->_setPass(pass);
		mRenderSystem->_setHlmsBlendblock(pass->getBlendblock());


		//Ogre::HlmsCache test;
		//mRenderSystem->_setProgramsFromHlms(pass);
	}

	void Screen::update(float width, float height)
	{
		// force == true if viewport size changed.
		if (mWidth != width || height != mHeight
#if OGRE_NO_VIEWPORT_ORIENTATIONMODE == 0
			|| mOrientation != mViewport->getOrientationMode()
#else
			|| mOrientationChanged
#endif
			)
		{
			mWidth = width;
			mHeight = height;

			mInvWidth = 1.0f / mWidth;
			mInvHeight = 1.0f / mHeight;

#if OGRE_NO_VIEWPORT_ORIENTATIONMODE == 0
			mOrientation = mViewport->getOrientationMode();
#else
			if (mOrientation == Ogre::OR_DEGREE_90 || mOrientation == Ogre::OR_DEGREE_270)
			{
				std::swap(mWidth, mHeight);
				std::swap(mInvWidth, mInvHeight);
			}
			mOrientationChanged = false;
#endif

			if (mOrientation == Ogre::OR_DEGREE_90)
				mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Z));
			else if (mOrientation == Ogre::OR_DEGREE_180)
				mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Z));
			else if (mOrientation == Ogre::OR_DEGREE_270)
				mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(Ogre::Degree(270), Ogre::Vector3::UNIT_Z));
			else
				mVertexTransform.makeTransform(Ogre::Vector3::ZERO, mScale, Ogre::Quaternion(1, 0, 0, 0));


			mForce = true;
		}

	}

	void Screen::renderOnce()
	{
		/*if (mIsVisible && mLayers.size())
		{*/
			//_renderVertices(mForce);
			_t_update();
			mForce = false;

			/*if (mRenderOp.vertexData->vertexCount)
			{*/
				_prepareRenderSystem();
				mRenderSystem->_render(mRenderOp);
		//	}
	//	}
	}

	void  Screen::_transform(std::vector<Vertex>& vertices, size_t begin, size_t end)
	{


	/*	for (size_t i = begin; i < end; i++)
		{
			vertices[i].position.x = ((vertices[i].position.x) * mInvWidth) * 2 - 1;
			vertices[i].position.y = ((vertices[i].position.y) * mInvHeight) * -2 + 1;
		}

		if (mVertexTransform != Ogre::Matrix4::IDENTITY)
		{
			for (size_t i = begin; i < end; i++)
				vertices[i].position = mVertexTransform * vertices[i].position;
		}
*/
	}



}