#include <XERenderer/private/DynamicRenderable.hpp>

#include <Ogre/OgreMain/include/OgreEntity.h>
#include <Ogre/OgreMain/include/OgreSubMesh.h>
#include <Ogre/OgreMain/include/OgreSubEntity.h>

#include <Ogre/OgreMain/include/Vao/OgreVaoManager.h>
//#include <Ogre/OgreMain/include/OgreHardwareBufferManager.h>
//#include <Ogre/OgreMain/include/Vao/OgreVertexArrayObject.h>
#include <Ogre/OgreMain/include/OgreSceneManager.h>

using namespace Ogre;

namespace XE {

/*
 * =============================================================================================
 * BtOgre::DynamicRenderable
 * =============================================================================================
 */

	DynamicRenderable::DynamicRenderable(IdType id, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr)
		: MovableObject(id, objManager, sceneMgr, 0)
		, mVertexBufferCapacity(0)
      , mIndexBufferCapacity(0)
	  , mVaoManager(sceneMgr->getDestinationRenderSystem()->getVaoManager())
	  , mVao(nullptr)
	 // , SimpleRenderable(0, objManager, sceneMgr)
    {

    }

    //------------------------------------------------------------------------------------------------
    DynamicRenderable::~DynamicRenderable()
    {
      //  delete mRenderOp.vertexData;
      //  delete mRenderOp.indexData;
    }

    //------------------------------------------------------------------------------------------------
	void DynamicRenderable::initialize(Ogre::v1::RenderOperation::OperationType operationType,
                                       bool useIndices)
    {
		m_operationType = operationType;
        // Initialize render operation
  //      mRenderOp.operationType = operationType;
  //      mRenderOp.useIndexes = useIndices;
		//mRenderOp.vertexData = new Ogre::v1::VertexData;
  //      if (mRenderOp.useIndexes)
		//	mRenderOp.indexData = new Ogre::v1::IndexData;


        // Reset buffer capacities
        mVertexBufferCapacity = 0;
        mIndexBufferCapacity = 0;

        // Create vertex declaration
        createVertexDeclaration();


    }

    //------------------------------------------------------------------------------------------------
    void DynamicRenderable::prepareHardwareBuffers(size_t vertexCount,
                                                   size_t indexCount)
    {
        // Prepare vertex buffer
        size_t newVertCapacity = mVertexBufferCapacity;
        if ((vertexCount > mVertexBufferCapacity) ||
                (!mVertexBufferCapacity))
        {
            // vertexCount exceeds current capacity!
            // It is necessary to reallocate the buffer.

            // Check if this is the first call
            if (!newVertCapacity)
                newVertCapacity = 1;

            // Make capacity the next power of two
            while (newVertCapacity < vertexCount)
                newVertCapacity <<= 1;
        }
        else if (vertexCount < mVertexBufferCapacity>>1) {
            // Make capacity the previous power of two
            while (vertexCount < newVertCapacity>>1)
                newVertCapacity >>= 1;
        }
        if (newVertCapacity != mVertexBufferCapacity)
        {
            mVertexBufferCapacity = newVertCapacity;
           
			
			// Create new vertex buffer
			//Ogre::v1::HardwareVertexBufferSharedPtr vbuf =
			//	Ogre::v1::HardwareBufferManager::getSingleton().createVertexBuffer(
   //                     mRenderOp.vertexData->vertexDeclaration->getVertexSize(0),
   //                     mVertexBufferCapacity,
			//			Ogre::v1::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?

            // Bind buffer
         //   mRenderOp.vertexData->vertexBufferBinding->setBinding(0, vbuf);




	
        }
        // Update vertex count in the render operation
       // mRenderOp.vertexData->vertexCount = vertexCount;

  //      if (mRenderOp.useIndexes)
  //      {
            OgreAssert(indexCount <= std::numeric_limits<unsigned short>::max(), "indexCount exceeds 16 bit");

            size_t newIndexCapacity = mIndexBufferCapacity;
            // Prepare index buffer
            if ((indexCount > newIndexCapacity) ||
                    (!newIndexCapacity))
            {
                // indexCount exceeds current capacity!
                // It is necessary to reallocate the buffer.

                // Check if this is the first call
                if (!newIndexCapacity)
                    newIndexCapacity = 1;

                // Make capacity the next power of two
                while (newIndexCapacity < indexCount)
                    newIndexCapacity <<= 1;

            }
            else if (indexCount < newIndexCapacity>>1)
            {
                // Make capacity the previous power of two
                while (indexCount < newIndexCapacity>>1)
                    newIndexCapacity >>= 1;
            }

            if (newIndexCapacity != mIndexBufferCapacity)
            {
                mIndexBufferCapacity = newIndexCapacity;
                // Create new index buffer
				//mRenderOp.indexData->indexBuffer =
				//	Ogre::v1::HardwareBufferManager::getSingleton().createIndexBuffer(
				//	Ogre::v1::HardwareIndexBuffer::IT_16BIT,
    //                        mIndexBufferCapacity,
				//			Ogre::v1::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?


				//char * indexData = static_cast<char *>(indexBuffer->map(0, indexBuffer->getNumElements()));
				//
				//if (m32BitIndices)
				// {
				//	memcpy(indexData, mIndexBuffer, mIndices * sizeof(uint32));
				//}
				//else
				//{

				//}

            }

			

            // Update index count in the render operation
         //   mRenderOp.indexData->indexCount = indexCount;
        }
   

		void DynamicRenderable::getRenderOperation(v1::RenderOperation& op)
		{
			OGRE_EXCEPT(Exception::ERR_NOT_IMPLEMENTED,
				"ManualObject does not implement getRenderOperation. "
				 "Use MovableObject::setRenderQueueGroup to change the group.",
				"ManualObjectSection::getRenderOperation");
			//op = m_operationType;
		}
		//-----------------------------------------------------------------------------
		void DynamicRenderable::getWorldTransforms(Matrix4* xform) const
		{
			OGRE_EXCEPT(Exception::ERR_NOT_IMPLEMENTED,
				"ManualObject does not implement getWorldTransforms. "
				 "Use MovableObject::setRenderQueueGroup to change the group.",
				"ManualObjectSection::getWorldTransforms");
		//	*xform = mWorldTransform * mParentNode->_getFullTransform();
		}

		const LightList& DynamicRenderable::getLights(void) const
		{
			return queryLights();
		}


    //------------------------------------------------------------------------------------------------
    Real DynamicRenderable::getBoundingRadius(void) const
    {
        return Math::Sqrt(std::max(mBox.getMaximum().squaredLength(), mBox.getMinimum().squaredLength()));
    }

    //------------------------------------------------------------------------------------------------
    Real DynamicRenderable::getSquaredViewDepth(const Camera* cam) const
    {
        Vector3 vMin, vMax, vMid, vDist;
        vMin = mBox.getMinimum();
        vMax = mBox.getMaximum();
        vMid = ((vMax - vMin) * 0.5) + vMin;
        vDist = cam->getDerivedPosition() - vMid;

        return vDist.squaredLength();
    }
	


		const String& DynamicRenderable::getMovableType(void) const

		{
			return "DynamicLines";//ManualObjectFactory::FACTORY_TYPE_NAME;
		}

} // namespace XE
