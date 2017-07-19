#include "yDebugDrawer.h"

#include "OgreMesh2.h"
#include "OgreMeshManager2.h"
#include "OgreSubMesh2.h"
#include "Vao/OgreVertexArrayObject.h"
#include "OgreRoot.h"
#include <Ogre/OgreMain/include/OgreItem.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>
#include <Ogre/OgreMain/include/OgreHlmsManager.h>
#include <Ogre/OgreMain/include/OgreHlms.h>

namespace XE {

	//yDebugDrawer& yDebugDrawer::getSingleton()
	//{
	//	static yDebugDrawer instance;
	//	return instance;
	//}
	yDebugDrawer::yDebugDrawer()
	{
	}

	void yDebugDrawer::init()
	{
		sceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("MyFirstSceneManager");
		isDebuggingPhysics = false;

		auto hlmsManager = Ogre::Root::getSingletonPtr()->getHlmsManager();
		Ogre::HlmsUnlit *hlmsUnlit = static_cast<Ogre::HlmsUnlit*>(hlmsManager->getHlms(Ogre::HLMS_UNLIT));

		Ogre::String datablockName = "DebugLineMat";
		Ogre::HlmsUnlitDatablock *datablock = static_cast<Ogre::HlmsUnlitDatablock*>(hlmsUnlit->createDatablock(datablockName,
			datablockName,
			Ogre::HlmsMacroblock(),
			Ogre::HlmsBlendblock(),
			Ogre::HlmsParamVec()));

		vertexCount = 0;
		int maxVertexCount = 10000000;


		Ogre::Root *root = Ogre::Root::getSingletonPtr();
		Ogre::RenderSystem *renderSystem = root->getRenderSystem();
		Ogre::VaoManager *vaoManager = renderSystem->getVaoManager();

		Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("PhysicsDebuggingMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::SubMesh *subMesh = mesh->createSubMesh();

		Ogre::VertexElement2Vec vertexElements;
		vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT3, Ogre::VES_POSITION));
		vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT3, Ogre::VES_DIFFUSE));

		size_t vertexSize = vaoManager->calculateVertexSize(vertexElements);

		Ogre::Real* vertexData = static_cast<Ogre::Real*>(OGRE_MALLOC_SIMD(vertexSize * maxVertexCount, Ogre::MEMCATEGORY_GEOMETRY));

		Ogre::VertexBufferPackedVec vertexBuffers;

		pVertexBuffer = vaoManager->createVertexBuffer(vertexElements, maxVertexCount, Ogre::BT_DYNAMIC_PERSISTENT, vertexData, false);
		vertexBuffers.push_back(pVertexBuffer);


		vao = vaoManager->createVertexArrayObject(
			vertexBuffers, 0, Ogre::OperationType::OT_LINE_LIST);

		subMesh->mVao[0].push_back(vao);
		subMesh->mVao[1].push_back(vao);


		mesh->_setBounds(Ogre::Aabb::BOX_INFINITE);


		item = sceneManager->createItem(mesh, Ogre::SCENE_DYNAMIC);
		item->setDatablock(datablock);
		item->setCastShadows(false);
		Ogre::SceneNode *sceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
		sceneNode->attachObject(item);


		debugModes = (DebugDrawModes)DBG_DrawWireframe;

	}

	yDebugDrawer::~yDebugDrawer()
	{
	}

	void yDebugDrawer::deinit() {
		if (isDebuggingPhysics) debugPhysics(false);
	}

	void yDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
	{
		if (!isDebuggingPhysics) return;

		if (pVertexBuffer->isCurrentlyMapped()) {
			meshVertices[vertIndex++] = from.x();
			meshVertices[vertIndex++] = from.y();
			meshVertices[vertIndex++] = from.z();

			meshVertices[vertIndex++] = color.getX()*0.9;
			meshVertices[vertIndex++] = color.getY()*0.9;
			meshVertices[vertIndex++] = color.getZ()*0.9;

			meshVertices[vertIndex++] = to.x();
			meshVertices[vertIndex++] = to.y();
			meshVertices[vertIndex++] = to.z();

			meshVertices[vertIndex++] = color.getX()*0.9;
			meshVertices[vertIndex++] = color.getY()*0.9;
			meshVertices[vertIndex++] = color.getZ()*0.9;

			vertexCount += 2;

			vao->setPrimitiveRange(0, vertexCount);
		}
	}

	bool yDebugDrawer::frameStarted(const Ogre::FrameEvent& evt) {
		vertIndex = 0;
		vertexCount = 0;
		meshVertices = reinterpret_cast<Ogre::Real*>(pVertexBuffer->map(0, pVertexBuffer->getNumElements()));

		return true;
	}

	bool yDebugDrawer::frameEnded(const Ogre::FrameEvent& evt) {
		if (pVertexBuffer->isCurrentlyMapped()) pVertexBuffer->unmap(Ogre::UO_KEEP_PERSISTENT);

		return true;
	}

	void yDebugDrawer::debugPhysics(bool enable) {
		isDebuggingPhysics = enable;
		if (isDebuggingPhysics) {
			item->setVisible(true);
			Ogre::Root::getSingleton().addFrameListener(this);
		}
		else {
			item->setVisible(false);
			Ogre::Root::getSingleton().removeFrameListener(this);
		}
	}

	void yDebugDrawer::setDebugMode(int debugMode)
	{
		debugModes = (DebugDrawModes)debugMode;
	}

	int yDebugDrawer::getDebugMode() const
	{
		return debugModes;
	}

}