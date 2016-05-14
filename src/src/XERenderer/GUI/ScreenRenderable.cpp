#include <XERenderer/GUI/ScreenRenderable.hpp>

namespace XE
{

	//ScreenRenderable::ScreenRenderable(const Ogre::Vector2& maxSize, TextureAtlas* atlas, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr)
	//	: LayerContainer(atlas), Ogre::v1::SimpleRenderable(0, objManager, sceneMgr), mMaxSize(maxSize)
	//	//ScreenRenderable::ScreenRenderable(const Ogre::Vector2& maxSize, TextureAtlas* atlas)
	//	//: LayerContainer(atlas), mMaxSize(maxSize)
	//{
	//	mRenderOpPtr = &mRenderOp;

	//	mBox.setInfinite();
	//	setMaterial(mAtlas->get3DMaterialName());

	//	_createVertexBuffer(32);
	//}

	//ScreenRenderable::~ScreenRenderable()
	//{
	//}

	//void ScreenRenderable::frameStarted()
	//{
	//	renderOnce();
	//}

	//void ScreenRenderable::renderOnce()
	//{
	//	if (mIndexRedrawNeeded)
	//	{
	//		_renderVertices(false);
	//		calculateBoundingBox();
	//	}
	//}

	//void ScreenRenderable::calculateBoundingBox()
	//{
	//	IndexData* indexData = 0;
	//	mBox.setExtents(0, 0, 0, 0, 0, 0);
	//	size_t i = 0;
	//	for (std::map<Ogre::uint, IndexData*>::iterator it = mIndexData.begin(); it != mIndexData.end(); it++)
	//	{
	//		indexData = (*it).second;
	//		for (i = 0; i < indexData->mVertices.size(); i++)
	//		{
	//			mBox.merge(indexData->mVertices[i].position);
	//		}
	//	}
	//	if (mBox.isNull() == false)
	//	{
	//		mBox.merge(Ogre::Vector3(0, 0, -0.25f));
	//		mBox.merge(Ogre::Vector3(0, 0, 0.25f));

	//	}

	//	//Ogre::SceneNode* node = getParentSceneNode();
	//	//KH  if (node)
	//	//KH  node->_updateBounds();

	//}

	//void ScreenRenderable::_transform(buffer<Vertex>& vertices, size_t begin, size_t end)
	//{
	//	Ogre::Vector2 halfSize = mMaxSize * 0.5;
	//	for (size_t i = begin; i < end; i++)
	//	{
	//		vertices[i].position.x = (vertices[i].position.x * 0.01f) - halfSize.x;
	//		vertices[i].position.y = (vertices[i].position.y * -0.01f) + halfSize.y;
	//	}
	//}



}