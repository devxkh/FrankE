
#include <XERenderer/private/DynamicLines.hpp>

#include <Ogre/OgreMain/include/OgreVector3.h>

#include <Ogre/OgreMain/include/OgreEntity.h>
#include <Ogre/OgreMain/include/OgreSubMesh.h>
#include <Ogre/OgreMain/include/OgreSubEntity.h>

#include <Ogre/OgreMain/include/Vao/OgreIndexBufferPacked.h>
#include <Ogre/OgreMain/include/Vao/OgreVaoManager.h>


namespace XE {

	/*
	 * =============================================================================================
	 * BtOgre::DynamicLines
	 * =============================================================================================
	 */

	enum {
		POSITION_BINDING,
		TEXCOORD_BINDING
	};

	//------------------------------------------------------------------------------------------------
	DynamicLines::DynamicLines(Ogre::IdType id, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr, OperationType opType)
		: ManualObject(id, objManager, sceneMgr) //DynamicRenderable(id, objManager, sceneMgr)
	{
	//	initialize(opType, false);
		//   setMaterial("BaseWhiteNoLighting");
		mDirty = true;



	}

	//------------------------------------------------------------------------------------------------
	DynamicLines::~DynamicLines()
	{
	}

	//------------------------------------------------------------------------------------------------
	void DynamicLines::setOperationType(OperationType opType)
	{
	//	m_operationType = opType;
	}

	//------------------------------------------------------------------------------------------------
	Ogre::OperationType DynamicLines::getOperationType() const
	{
		return m_operationType;
	}

	//------------------------------------------------------------------------------------------------
	void DynamicLines::addPoint(const Ogre::Vector3 &p)
	{
		_t_Points.push_back(p);
		mDirty = true;
	}

	//------------------------------------------------------------------------------------------------
	void DynamicLines::addPoint(Real x, Real y, Real z)
	{
		_t_Points.push_back(Ogre::Vector3(x, y, z));
		mDirty = true;
	}

	//------------------------------------------------------------------------------------------------
	const Ogre::Vector3& DynamicLines::getPoint(unsigned short index) const
	{
		assert(index < _t_Points.size() && "Point index is out of bounds!!");
		return _t_Points[index];
	}

	//------------------------------------------------------------------------------------------------
	unsigned short DynamicLines::getNumPoints(void) const
	{
		return (unsigned short)_t_Points.size();
	}

	//------------------------------------------------------------------------------------------------
	void DynamicLines::setPoint(unsigned short index, const Ogre::Vector3 &value)
	{
		assert(index < _t_Points.size() && "Point index is out of bounds!!");

		_t_Points[index] = value;
		mDirty = true;
	}

	//------------------------------------------------------------------------------------------------
	void DynamicLines::clear()
	{
		_t_Points.clear();
		mDirty = true;
	}

	//------------------------------------------------------------------------------------------------
	void DynamicLines::update()
	{
		if (mDirty) 
			fillHardwareBuffers();
	}

	//------------------------------------------------------------------------------------------------
	void DynamicLines::createVertexDeclaration()
	{
		//    Ogre::v1::VertexDeclaration *decl = mRenderOp.vertexData->vertexDeclaration;
		//   decl->addElement(POSITION_BINDING, 0, VET_FLOAT3, VES_POSITION);
//		mVertexElements.push_back(VertexElement2(VET_FLOAT3, VES_POSITION));
	}

	//------------------------------------------------------------------------------------------------
	void DynamicLines::fillHardwareBuffers()
	{
		int size = _t_Points.size();

		ManualObject::clear();

		begin("BaseWhite", Ogre::OperationType::OT_LINE_LIST);

		for (int i = 0; i < size; i++)
		{
			position(_t_Points[i].x, _t_Points[i].y, _t_Points[i].z);
		//	colour(Ogre::ColourValue::Blue);
			index(i);
			//		*mVertexBuffer++ = _t_Points[i].y;
			//		*mVertexBuffer++ = _t_Points[i].z;

			//		if (m32BitIndices)
			//		{
			//			*((uint32 *)indexData) = i;
		}

		// Back
		//manualObject->position(0.0f, 0.0f, 0.0f);
		//manualObject->position(0.0f, 1.0f, 0.0f);
		//manualObject->line(0, 1);

		//manualObject->position(0.0f, 1.0f, 0.0f);
		//manualObject->position(1.0f, 1.0f, 0.0f);
		//manualObject->line(2, 3);

		//manualObject->position(1.0f, 1.0f, 0.0f);
		//manualObject->position(1.0f, 0.0f, 0.0f);
		//manualObject->line(4, 5);

		//manualObject->position(1.0f, 0.0f, 0.0f);
		//manualObject->position(0.0f, 0.0f, 0.0f);
		//manualObject->line(6, 7);

		//// Front
		//manualObject->position(0.0f, 0.0f, 1.0f);
		//manualObject->position(0.0f, 1.0f, 1.0f);
		//manualObject->line(8, 9);

		//manualObject->position(0.0f, 1.0f, 1.0f);
		//manualObject->position(1.0f, 1.0f, 1.0f);
		//manualObject->line(10, 11);

		//manualObject->position(1.0f, 1.0f, 1.0f);
		//manualObject->position(1.0f, 0.0f, 1.0f);
		//manualObject->line(12, 13);

		//manualObject->position(1.0f, 0.0f, 1.0f);
		//manualObject->position(0.0f, 0.0f, 1.0f);
		//manualObject->line(14, 15);

		//// Sides
		//manualObject->position(0.0f, 0.0f, 0.0f);
		//manualObject->position(0.0f, 0.0f, 1.0f);
		//manualObject->line(16, 17);

		//manualObject->position(0.0f, 1.0f, 0.0f);
		//manualObject->position(0.0f, 1.0f, 1.0f);
		//manualObject->line(18, 19);

		//manualObject->position(1.0f, 0.0f, 0.0f);
		//manualObject->position(1.0f, 0.0f, 1.0f);
		//manualObject->line(20, 21);

		//manualObject->position(1.0f, 1.0f, 0.0f);
		//manualObject->position(1.0f, 1.0f, 1.0f);
		//manualObject->line(22, 23);

		end();

		return;

	//	prepareHardwareBuffers(size, 0);

	//	if (!size) {
	//		mBox.setExtents(Vector3::ZERO, Vector3::ZERO);
	//		mDirty = false;
	//		return;
	//	}

	//	Vector3 vaabMin = _t_Points[0];
	//	Vector3 vaabMax = _t_Points[0];


	//	//reset ---------------------------------
	//	//reset ---------------------------------
	//	//reset ---------------------------------	
	//	mVertexBuffer = 0;
	//	//	mIndexBuffer = mIndexBufferCursor = 0;


	//	//clear -------------
	//	//clear -------------
	//	//clear -------------
	//	VertexArrayObject *vao = mVao;

	//	if (vao)
	//	{
	//		const VertexBufferPackedVec &vertexBuffers = vao->getVertexBuffers();
	//		VertexBufferPackedVec::const_iterator itBuffers = vertexBuffers.begin();
	//		VertexBufferPackedVec::const_iterator endBuffers = vertexBuffers.end();

	//		while (itBuffers != endBuffers)
	//		{
	//			VertexBufferPacked * vertexBuffer = *itBuffers;

	//			vertexBuffer->unmap(UO_UNMAP_ALL);

	//			mVaoManager->destroyVertexBuffer(vertexBuffer);

	//			++itBuffers;
	//		}

	//		IndexBufferPacked * indexBuffer = vao->getIndexBuffer();

	//		if (indexBuffer)
	//		{
	//			indexBuffer->unmap(UO_UNMAP_ALL);

	//			mVaoManager->destroyIndexBuffer(indexBuffer);
	//		}

	//		mVaoManager->destroyVertexArrayObject(vao);
	//	}
	//	mVao = 0;
	//	mVaoPerLod.clear();
	//	mRenderables.clear();
	//	mIndexBufferCursor = 0;
	//	//clear -------------
	//	//clear -------------
	//	//clear -------------


	//	mIndexBufferCapacity = size; // for each point an index
	//	//end ------------------------
	//	//end ------------------------
	//	//end ------------------------
	//	Ogre::VertexBufferPackedVec vertexBuffers;
	//	//Create the vertex buffer
	//	VertexBufferPacked * vertexBuffer = mVaoManager->createVertexBuffer(mVertexElements, mVertexBufferCapacity, BT_DYNAMIC_PERSISTENT, NULL, false);
	//	mVertexBuffer = reinterpret_cast<float *>(vertexBuffer->map(0, vertexBuffer->getNumElements()));

	//	Ogre::IndexBufferPacked *indexBuffer = mVaoManager->createIndexBuffer(m32BitIndices ? IndexBufferPacked::IT_32BIT : IndexBufferPacked::IT_16BIT, mIndexBufferCapacity, BT_DYNAMIC_PERSISTENT, NULL, false);
	//	char * indexData = reinterpret_cast<char *>(indexBuffer->map(0, indexBuffer->getNumElements()));
	//	mIndices = 0;

	//	//update --------------------
	//	for (int i = 0; i < size; i++)
	//	{
	//		*mVertexBuffer++ = _t_Points[i].x;
	//		*mVertexBuffer++ = _t_Points[i].y;
	//		*mVertexBuffer++ = _t_Points[i].z;

	//		if (m32BitIndices)
	//		{
	//			*((uint32 *)indexData) = i;
	//			indexData += sizeof(uint32);
	//		}
	//		else
	//		{
	//			*((uint16 *)indexData) = i;
	//			indexData += sizeof(uint16);
	//		}

	//		mIndices++;

	//		if (_t_Points[i].x < vaabMin.x)
	//			vaabMin.x = _t_Points[i].x;
	//		if (_t_Points[i].y < vaabMin.y)
	//			vaabMin.y = _t_Points[i].y;
	//		if (_t_Points[i].z < vaabMin.z)
	//			vaabMin.z = _t_Points[i].z;

	//		if (_t_Points[i].x > vaabMax.x)
	//			vaabMax.x = _t_Points[i].x;
	//		if (_t_Points[i].y > vaabMax.y)
	//			vaabMax.y = _t_Points[i].y;
	//		if (_t_Points[i].z > vaabMax.z)
	//			vaabMax.z = _t_Points[i].z;
	//	}

	//	vertexBuffer->unmap(Ogre::UO_KEEP_PERSISTENT);
	//	indexBuffer->unmap(Ogre::UO_KEEP_PERSISTENT);

	//	vertexBuffers.push_back(vertexBuffer);

	//	//Ogre::uint16 *cubeIndices = reinterpret_cast<Ogre::uint16*>(OGRE_MALLOC_SIMD(
	//	//	sizeof(Ogre::uint16) * 3 * 2 * 6,
	//	//	Ogre::MEMCATEGORY_GEOMETRY));
	//	//memcpy(cubeIndices, c_indexData, sizeof(c_indexData));

	////	Ogre::IndexBufferPacked *indexBuffer = mVaoManager->createIndexBuffer(m32BitIndices ? IndexBufferPacked::IT_32BIT : IndexBufferPacked::IT_16BIT, mIndices, BT_DYNAMIC_PERSISTENT, NULL, false);
	///*	char * indexData = reinterpret_cast<char *>(indexBuffer->map(0, indexBuffer->getNumElements()));

	//	assert(indexData);

	//	for (int i = 0; i < size; i++)
	//	{
	//		*indexData++ = _t_Points[i].x;
	//		*indexData++ = _t_Points[i].y;
	//		*indexData++ = _t_Points[i].z;

	//	}

	//	indexBuffer->unmap(UO_KEEP_PERSISTENT);*/


	//	mVao = mVaoManager->createVertexArrayObject(vertexBuffers, indexBuffer, m_operationType);

	//	mVaoPerLod.push_back(mVao);

	//	mRenderables.push_back(this);

	//	setDatablock("BaseWhite");



	//	//Real *prPos = static_cast<Real*>(vbuf->lock(Ogre::v1::HardwareBuffer::HBL_DISCARD));
	//	//      {
	//	//          for(int i = 0; i < size; i++)
	//	//          {
	//	//              *prPos++ = _t_Points[i].x;
	//	//              *prPos++ = _t_Points[i].y;
	//	//              *prPos++ = _t_Points[i].z;

	//	//              if(_t_Points[i].x < vaabMin.x)
	//	//                  vaabMin.x = _t_Points[i].x;
	//	//              if(_t_Points[i].y < vaabMin.y)
	//	//                  vaabMin.y = _t_Points[i].y;
	//	//              if(_t_Points[i].z < vaabMin.z)
	//	//                  vaabMin.z = _t_Points[i].z;

	//	//              if(_t_Points[i].x > vaabMax.x)
	//	//                  vaabMax.x = _t_Points[i].x;
	//	//              if(_t_Points[i].y > vaabMax.y)
	//	//                  vaabMax.y = _t_Points[i].y;
	//	//              if(_t_Points[i].z > vaabMax.z)
	//	//                  vaabMax.z = _t_Points[i].z;
	//	//          }
	//	//      }
	//	//      vbuf->unlock();

	//	mBox.setExtents(vaabMin, vaabMax);

		mDirty = false;
	}


}
