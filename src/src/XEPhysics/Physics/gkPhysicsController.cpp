/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Charlie C.

    Contributor(s): Thomas Trocha(dertom)
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/

#include <XEPhysics/Physics/gkDynamicsWorld.h>
#include <XEPhysics/Physics/gkPhysicsController.h>
//#include "gkMesh.h"
#include <XEPhysics/Physics/gkCharacter.h>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletCollision/Gimpact/btGImpactShape.h"

#include <XEngine/Components/PhysicsComponents.hpp>
#include <XEngine/Components/Body.hpp>
#include <XESystem/TransportData.hpp>
#include <ThirdParty/plog/Log.h>

gkPhysicsController::gkPhysicsController(gkDynamicsWorld* owner)
	:    m_owner(owner),
	     m_object(),
	     m_collisionObject(0),
	     m_shape(0),
	     m_suspend(false),
		 m_dbvtMark(true),
		 m_type(XFBType::PhysicsType_PT_NO_COLLISION),
		 m_mode(0)
		, m_renderOffset(Ogre::Vector3::ZERO)
	, m_isGhost(false)
{
	// initial copy from object
//	if (object)
	//	m_props = object->getProperties().m_physics;
}



gkPhysicsController::~gkPhysicsController()
{
	if (m_shape)
	{
		destroyShape(m_shape);
		m_shape = 0;
	}
}

void gkPhysicsController::destroyShape(btCollisionShape* shape)
{
	if (!shape) return;

	if (shape->isCompound())
	{
		btCompoundShape* compShape = static_cast<btCompoundShape*>(shape);
		int i;
		for (i = 0; i < compShape->getNumChildShapes(); i++)
		{
			btCollisionShape* childShape = compShape->getChildShape(i);
			if (childShape->isCompound())
				destroyShape(childShape);
			else
				delete childShape;
		}
	}

	delete shape;
}

void gkPhysicsController::setShape(btCollisionShape* shape)
{
	if (m_collisionObject)
	{
		destroyShape(m_shape);

		m_shape = shape;
		m_collisionObject->setCollisionShape(m_shape);
	}
}

gkContactInfo::Array& gkPhysicsController::getContacts(void)
{
	return m_localContacts;
}


gkContactInfo::Iterator gkPhysicsController::getContactIterator(void)
{
	return gkContactInfo::Iterator(m_localContacts);
}



bool gkPhysicsController::collidesWith(entityx::Entity ob, gkContactInfo* cpy)
{
	if (!m_localContacts.empty())
	{
		UTsize i, s;
		gkContactInfo::Array::Pointer p;

		i = 0;
		s = m_localContacts.size();
		p = m_localContacts.ptr();

		while (i < s)
		{
			assert(p[i].collider);

			if (&p[i].collider->getObject() == &ob)
			{
				if (cpy) *cpy = p[i];
				return true;
			}
			++i;
		}
	}
	return false;
}



bool gkPhysicsController::collidesWith(const std::string& name, gkContactInfo* cpy, bool emptyFilter)
{
	if (m_suspend)
		return false;

	if (!m_localContacts.empty())
	{
		if (name.empty() && emptyFilter)
		{
			if (cpy) *cpy = m_localContacts.at(0);
			return true;
		}


		UTsize i, s;
		gkContactInfo::Array::Pointer p;

		i = 0;
		s = m_localContacts.size();
		p = m_localContacts.ptr();

		while (i < s)
		{
			assert(p[i].collider);
			entityx::Entity gobj = p[i].collider->getObject();
			entityx::ComponentHandle<XE::BodyComponent> body = m_object.component<XE::BodyComponent>();

			/*if (name.find(body->name) != std::string::npos)
			{
				if (cpy) *cpy = p[i];
				return true;
			}*/

			++i;
		}
	}

	return false;
}




bool gkPhysicsController::sensorCollides(const std::string& prop, const std::string& material, bool onlyActor, bool testAllMaterials, utArray<entityx::Entity*>* collisionList)
{
	if (collisionList){
		collisionList->clear();
	}
	if (onlyActor && !m_mode & PhysicsObjectMode::GK_ACTOR)
		return false;


	if (!m_localContacts.empty())
	{
		if (!collisionList && prop.empty() && material.empty())
		{
			// there are contacts and we do not care about property, nor empty, nor we need a list of objects (list = NULL)
			// any filter
			return true;
		}

		UTsize i, s;
		gkContactInfo::Array::Pointer p;

		i = 0;
		s = m_localContacts.size();
		p = m_localContacts.ptr();

		while (i < s)
		{
			assert(p[i].collider);
			entityx::Entity gobj = p[i].collider->getObject();


			if (onlyActor)
			{

				if (prop.empty() && material.empty())
					return true;

				if (m_mode & PhysicsObjectMode::GK_ACTOR)
				{
					if (!prop.empty())
					{
						/*if (gobj->hasVariable(prop)){
							if (!collisionList){
								return true;
							}
							else if (collisionList->find(gobj)==UT_NPOS)
								collisionList->push_back(gobj);
						}*/
					}
					else if (!material.empty())
					{
						/*if (gobj->hasSensorMaterial(material, !testAllMaterials))
						{
							if (!collisionList)
							{
								return true;
							}
							else if (collisionList->find(gobj)==UT_NPOS){
								collisionList->push_back(gobj);
							}
						}*/
					}
				}
			}
			else
			{
				if (prop.empty() && material.empty())
					if (!collisionList)
					{
						return true;
					}
					else if (collisionList->find(&gobj)==UT_NPOS)
					{
						collisionList->push_back(&gobj); //??? works?
					}

				if (!prop.empty())
				{
					/*if (gobj->hasVariable(prop))
					{
						if (!collisionList)
						{
							return true;
						}
						else if (collisionList->find(gobj)==UT_NPOS)
						{
							collisionList->push_back(gobj);
						}
					}*/
				}
				else if (!material.empty())
				{
					/*if (gobj->hasSensorMaterial(material, !testAllMaterials)){
						if (!collisionList)
						{
							return true;
						}
						else if (collisionList->find(gobj)==UT_NPOS)
						{
							collisionList->push_back(gobj);
						}
					}*/
				}
			}

			++i;
		}
	}
	if (!collisionList)
		return false;
	else if (collisionList->empty())
		return false;
	else
		return true;
}




bool gkPhysicsController::_markDbvt(bool v)
{
	if (m_suspend)
		return false;

	bool result = false;
	if (m_dbvtMark != v)
	{
		/*m_dbvtMark = v;
		if ( m_object->getType() == GK_ENTITY &&  !m_object->getProperties().isInvisible())
		{
			Ogre::MovableObject* mov = m_object->getMovable();

			if (mov)
			{
				result = mov->isVisible() != m_dbvtMark;
				mov->setVisible(m_dbvtMark);
			}
		}*/
	}
	return result;
}



bool gkPhysicsController::sensorTest(entityx::Entity ob, const std::string& prop, const std::string& material, bool onlyActor, bool testAllMaterials)
{
//	assert(ob);

	if (onlyActor)
	{
		//if (m_mode & PhysicsObjectMode::GK_ACTOR)
		//{
		//	if (prop.empty() && material.empty())
		//		return true;

		//	if (!prop.empty())
		//	{
		//		/*if (ob->hasVariable(prop))
		//			return true;*/
		//	}
		//	else if (!material.empty())
		//	{
		//		/*if (ob->hasSensorMaterial(material, !testAllMaterials))
		//			return true;*/
		//	}
		//}
	}
	else
	{
		if (prop.empty() && material.empty())
			return true;

		if (!prop.empty())
		{
			/*if (ob->hasVariable(prop))
				return true;*/
		}
		else if (!material.empty())
		{
			/*if (ob->hasSensorMaterial(material, !testAllMaterials))
				return true;*/
		}
	}

	return false;
}



void gkPhysicsController::setTransformState(const TransformState& state)
{
	if (m_suspend || !m_collisionObject)
		return;

	m_collisionObject->setWorldTransform(state.toTransform());
}



void gkPhysicsController::updateTransform(void)
{
	if (m_suspend || !m_collisionObject)
		return;


	btTransform worldTrans;
	worldTrans.setIdentity();

	Ogre::Quaternion rot;
	Ogre::Vector3 loc;

	entityx::ComponentHandle<XE::BodyComponent> body = m_object.component<XE::BodyComponent>();

	if (!body->getParent())
	{
		rot = body->_getDerivedOrientation();
		loc = body->_getDerivedPosition();
	}
	else
	{
		rot = body->getOrientation();
		loc = body->getPosition();
	}


	worldTrans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
	worldTrans.setOrigin(btVector3(loc.x, loc.y, loc.z));

	m_collisionObject->setWorldTransform(worldTrans);
}



void gkPhysicsController::enableContactProcessing(bool v)
{
	//if (m_object)
//	{
		if (v)
		{
			if (!isContactListener())
			{
			//	auto test = m_props.Object->GetStruct(0);
			//	//flatbuffers::Parser tt;

			//	flatbuffers::FlatBufferBuilder fbb;
			//	XFBType::PhysicsObjectBuilder mb(fbb);
			//	mb.add_type(m_props.Object->mode() | GK_CONTACT);
			//	auto mloc = mb.Finish();

				m_mode = (m_mode | GK_CONTACT);//KH (|= GK_CONTACT);
			}
		}
		else
		{
			if (isContactListener())
				m_mode = (m_mode ^ GK_CONTACT);
		}
//	}
}


gkPhysicsController* gkPhysicsController::castController(void* colObj)
{
	assert(colObj);
	return castController(static_cast<btCollisionObject*>(colObj));
}


gkPhysicsController* gkPhysicsController::castController(btCollisionObject* colObj)
{
	assert(colObj);
	return static_cast<gkPhysicsController*>(colObj->getUserPointer());
}


gkPhysicsController* gkPhysicsController::castController(const btCollisionObject* colObj)
{
	assert(colObj);
	return static_cast<gkPhysicsController*>(const_cast<btCollisionObject*>(colObj)->getUserPointer());
}



entityx::Entity gkPhysicsController::castObject(btCollisionObject* colObj)
{
	assert(colObj);
	gkPhysicsController* cont = static_cast<gkPhysicsController*>(colObj->getUserPointer());
	assert(cont);
	return cont->getObject();
}


entityx::Entity gkPhysicsController::castObject(const btCollisionObject* colObj)
{
	return castObject(const_cast<btCollisionObject*>(colObj));
}



void gkPhysicsController::suspend(bool v)
{
	if (m_suspend != v && m_collisionObject)
	{
		m_suspend = v;

		//KH commented out ???
		//if (m_suspend)
		//KH	m_object->getProperties().m_physics.m_type = XFBType::PhysicsType_PT_NO_COLLISION;
	//	else
		//	m_object->getProperties().m_physics.m_type = getProperties().m_type;

		//assert(m_owner);
		//btDynamicsWorld* dyn = getOwner();

		//btRigidBody* body = btRigidBody::upcast(m_collisionObject);
		//btGhostObject* ghost = btGhostObject::upcast(m_collisionObject);
		//if (m_suspend)
		//{
		//	if (body)
		//		dyn->removeRigidBody(body);
		//	else if (ghost)
		//	{				
		//		dyn->removeAction(static_cast<gkCharacter*>(this));
		//		dyn->removeCollisionObject(m_collisionObject);
		//	}
		//	else
		//		dyn->removeCollisionObject(m_collisionObject);
		//}
		//else
		//{
		//	if (body)
		//		dyn->addRigidBody(body);
		//	else if (ghost)
		//	{
		//		dyn->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter);
		//		dyn->addAction(static_cast<gkCharacter*>(this));
		//	}
		//	else
		//		dyn->addCollisionObject(m_collisionObject);
		//}
	}
}


btCollisionObject* gkPhysicsController::getCollisionObject(void)
{
	return m_collisionObject;
}



btCollisionShape* gkPhysicsController::getShape(void)
{
	return m_shape;
}




btDynamicsWorld* gkPhysicsController::getOwner(void)
{
	if (m_owner)
		return m_owner->getBulletWorld();
	return 0;
}



entityx::Entity gkPhysicsController::getObject(void)
{
	return m_object;
}


XE::AABB& gkPhysicsController::getAabb(void) const
{
	if (m_collisionObject)
	{
		btVector3 aabbMin;
		btVector3 aabbMax;

		m_collisionObject->getCollisionShape()->getAabb(m_collisionObject->getWorldTransform(), aabbMin, aabbMax);

		sf::Vector3f min_aabb(aabbMin.x(), aabbMin.y(), aabbMin.z());
		sf::Vector3f max_aabb(aabbMax.x(), aabbMax.y(), aabbMax.z());


		return XE::AABB(min_aabb, max_aabb);
	}

	return XE::AABB();
}

void gkPhysicsController::createShape(const XFBType::PhysicsObject* physData)
{
	assert(!m_shape);// && m_object);

	m_shape = _createShape(physData);
}

//void GetTrianglesFromMesh(Ogre::Mesh* mesh, std::vector<btVector3>& dest)
//{
//	dest.clear();
//
//	for (Ogre::uint32 i = 0; i < mesh->getNumSubMeshes(); ++i)
//	{
//		Ogre::SubMesh* submesh = mesh->getSubMesh(i);
//
//		Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
//		const Ogre::VertexElement* posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
//		Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
//		unsigned char* vertices = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
//		size_t vertexSize = vbuf->getVertexSize();
//		float* pReal = 0;
//
//		Ogre::IndexData* index_data = submesh->indexData;
//		size_t numTris = index_data->indexCount / 3;
//		Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
//		Ogre::uint32*  pLong = static_cast<Ogre::uint32*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
//		Ogre::uint16* pShort = reinterpret_cast<Ogre::uint16*>(pLong);
//		bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
//
//		if (use32bitindexes)
//		{
//			for (size_t k = 0; k < numTris * 3; k += 3)
//			{
//				Ogre::uint32 i1 = pLong[k];
//				Ogre::uint32 i2 = pLong[k + 1];
//				Ogre::uint32 i3 = pLong[k + 2];
//
//				posElem->baseVertexPointerToElement(vertices + i1 * vertexSize, &pReal);
//				dest.push_back(btVector3(pReal[0], pReal[1], pReal[2]));
//
//				posElem->baseVertexPointerToElement(vertices + i2 * vertexSize, &pReal);
//				dest.push_back(btVector3(pReal[0], pReal[1], pReal[2]));
//
//				posElem->baseVertexPointerToElement(vertices + i3 * vertexSize, &pReal);
//				dest.push_back(btVector3(pReal[0], pReal[1], pReal[2]));
//			}
//		}
//		else
//		{
//			for (size_t k = 0; k < numTris * 3; k += 3)
//			{
//				Ogre::uint32 i1 = pShort[k];
//				Ogre::uint32 i2 = pShort[k + 1];
//				Ogre::uint32 i3 = pShort[k + 2];
//
//				posElem->baseVertexPointerToElement(vertices + i1 * vertexSize, &pReal);
//				dest.push_back(btVector3(pReal[0], pReal[1], pReal[2]));
//
//				posElem->baseVertexPointerToElement(vertices + i2 * vertexSize, &pReal);
//				dest.push_back(btVector3(pReal[0], pReal[1], pReal[2]));
//
//				posElem->baseVertexPointerToElement(vertices + i3 * vertexSize, &pReal);
//				dest.push_back(btVector3(pReal[0], pReal[1], pReal[2]));
//			}
//		}
//
//		vbuf->unlock();
//		ibuf->unlock();
//	}
//}


//void GenerateTriangleMesh(Ogre::Mesh* mesh, btTriangleMesh* ptr)
//{
//	std::vector<btVector3> triangles;
//	GetTrianglesFromMesh(mesh, triangles);
//
//	for (Ogre::uint32 i = 0; i < triangles.size(); i += 3)
//		ptr->addTriangle(triangles[i], triangles[i + 1], triangles[i + 2]);
//}

btCollisionShape* gkPhysicsController::_createShape(const XFBType::PhysicsObject* physData)
{
	//Ogre::MeshPtr me;
	//Ogre::Entity* ent = m_object->getEntity();
	//if (ent != 0)
		//me = ent->getMesh();// getEntityProperties().m_mesh;

//	Ogre::Vector3 size(1.f, 1.f, 1.f);
	Ogre::Vector3 size(physData->size()->x(), physData->size()->y(), physData->size()->z());
	//if (!me.isNull())
	//	size = me->getBounds().getHalfSize();
	//else
	
	//	size *= physData->radius();

	btCollisionShape* shape = 0;	

	switch (physData->shape())
	{
	case XFBType::PhysicsShape_SH_BOX:
		shape = new btBoxShape(btVector3(size.x, size.y, size.z));
		break;
	case XFBType::PhysicsShape_SH_CONE:
		shape = new btConeShapeZ(gkMax(size.x, size.y), 2.f * size.z);
		break;
	case XFBType::PhysicsShape_SH_CYLINDER:
		shape = new btCylinderShapeZ(btVector3(size.x, size.y, size.z));
		break;
	case XFBType::PhysicsShape_SH_PLANE:
		shape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
		break;
	case XFBType::PhysicsShape_SH_CONVEX_TRIMESH:
	case XFBType::PhysicsShape_SH_GIMPACT_MESH:
	case XFBType::PhysicsShape_SH_BVH_MESH:
		{
		//todo mesh data import
		//if (!me.isNull())
		//	{

		//	btTriangleMesh* triMesh = new btTriangleMesh();

		//		GenerateTriangleMesh(ent->getMesh().get(), triMesh);
		//	
		//		if (triMesh->getNumTriangles() > 0)
		//		{
		//			switch (physData->shape())
		//			{
		//			case XFBType::PhysicsShape_SH_CONVEX_TRIMESH:
		//				shape = new btConvexTriangleMeshShape(triMesh);
		//				break;
		//			case XFBType::PhysicsShape_SH_GIMPACT_MESH:
		//			{
		//				btGImpactMeshShape* gimpactShape = new btGImpactMeshShape(triMesh);
		//				gimpactShape->setMargin(physData->margin());
		//				gimpactShape->setLocalScaling(MathUtils::get(m_object->getScale()));
		//				gimpactShape->updateBound();
		//				shape = gimpactShape;
		//				break;
		//			}					
		//			case XFBType::PhysicsShape_SH_BVH_MESH:
		//				shape = new btBvhTriangleMeshShape(triMesh, true);
		//				break;
		//			}
 	//				break;
		//		}
		//		else
		//			return 0;
		//	}
		}
	case XFBType::PhysicsShape_SH_SPHERE:
		shape = new btSphereShape(gkMax(size.x, gkMax(size.y, size.z)));
		break;
	case XFBType::PhysicsShape_SH_CAPSULE:
		// For some reason, the shape is a bit bigger than the actual capsule...
	//	float c_radius = gkMax(size.x, size.y);
	//	shape = new btCapsuleShapeZ(c_radius-0.05, (size.z-c_radius-0.05) * 2);
		//if (axe == Ogre::Vector3f::UNIT_X)
		//	mShape = new btCapsuleShapeX(radius, height);
		//else if (axe == Ogre::Vector3f::UNIT_Y)
		//	mShape = new btCapsuleShape(radius, height);
		//else if (axe == Ogre::Vector3f::UNIT_Z)
		//	mShape = new btCapsuleShapeZ(radius, height);
		//TODO per fb!!
		m_renderOffset = Ogre::Vector3(0,-4.7f,0);

		shape = new btCapsuleShape(size.x, size.y);//2.2f, 7.6f);
		break;
	}

	if (!shape)
		return 0;

	// these values are already set for gimpact-shape
	if (physData->shape() != XFBType::PhysicsShape_SH_GIMPACT_MESH) {
		shape->setMargin(physData->margin());

		//if (m_object.has_component<XE::BodyComponent>())
		//{
		//	entityx::ComponentHandle<XE::BodyComponent> body = m_object.component<XE::BodyComponent>();
		//	shape->setLocalScaling(MathUtils::get(body->getScale()));
		//}
	/*	else
			LOG(DEBUG) << "entity doesn't have a bodyComponent";*/
	}
	
	if ((m_mode & GK_COMPOUND) != 0)//isCompound())
	{
		btCompoundShape *compShape = new btCompoundShape();
		compShape->addChildShape(btTransform::getIdentity(), shape);
		return compShape;
	}
	
	return shape;
	
}

void gkPhysicsController::setEntityWithBody(entityx::Entity object)
{
	assert(object.has_component<XE::BodyComponent>());

	m_object = object;

	//suspend(false);
}

void gkPhysicsController::setTransform(const btTransform& worldTrans)
{
	if (m_suspend)
		return;

	assert(m_object);// && m_object->isInstanced());
	
	//const Ogre::Quaternion& rot = MathUtils::get(worldTrans.getRotation());
	//const Ogre::Vector3& loc = MathUtils::get(worldTrans.getOrigin());

	// apply to the node and sync state next update

	//Ogre::SceneNode* node = m_object->getSceneNode();
	entityx::ComponentHandle<XE::BodyComponent> body = m_object.component<XE::BodyComponent>();

	if (body)
	{
		//node->setOrientation(rot);
		//node->setPosition(loc);
		auto rot = worldTrans.getRotation();
		body->setOrientation(Ogre::Quaternion(rot.w(), rot.x(), rot.y(), rot.z()));


	//	auto aabb = getAabb();

	//	btTransform& newTrans = m_collisionObject->getWorldTransform();
	////	newTrans.setOrigin(btVector3(newTrans.getOrigin().x(), newTrans.getOrigin().y() - aabb.maxaabb.y / 2, newTrans.getOrigin().z()));
	//	btVector3 newPos(newTrans.getOrigin().x(), newTrans.getOrigin().y() - aabb.maxaabb.y / 2, newTrans.getOrigin().z());

	//	body->setPosition(MathUtils::get(newPos));// worldTrans.getOrigin()));
		//auto correctPos = MathUtils::get(worldTrans.getOrigin());
		Ogre::Vector3 pos = MathUtils::get(worldTrans.getOrigin());
		if (m_renderOffset != Ogre::Vector3::ZERO)
			pos += m_renderOffset;

		body->setPosition(pos);
	}
//	m_object->notifyUpdate();
}



void gkPhysicsController::_handleManifold(btPersistentManifold* manifold)
{
	if (m_suspend || !isContactListener())//|| !m_object->isInstanced())
		return;


	gkPhysicsController* colA = castController(manifold->getBody0());
	gkPhysicsController* colB = castController(manifold->getBody1());

	gkPhysicsController* collider = colB;

	if (collider == this)
	{
		collider = colA;
	}

	//entity can be ghost object??
	//if (collider->m_object->isGhost()){
	//	m_localContacts.reserve(1);

	//	gkContactInfo cinf;
	//	cinf.collider = collider;
	//	m_localContacts.push_back(cinf);
	//}
	//else {
		int nrc = manifold->getNumContacts();

		if (nrc)
		{
			//-------------	m_localContacts.reserve(nrc);

			for (int j = 0; j < nrc; ++j)
			{
				gkContactInfo cinf;
				btManifoldPoint& pt = manifold->getContactPoint(j);

				if (pt.getDistance() < 0.f)
				{
					cinf.collider = collider;
					cinf.point    = pt;

					entityx::ComponentHandle<XE::PhysicsComponent> physicsComponent = m_object.component<XE::PhysicsComponent>();

					//FIXME attention !! takes only first physics object !! 
						physicsComponent->objects[0]->collided(collider->getObject(),
							MathUtils::get(pt.getPositionWorldOnB()), MathUtils::get(pt.m_normalWorldOnB), pt.getDistance(), pt.getAppliedImpulse());

				//-------------	m_localContacts.push_back(cinf);
				}
			}
		}
	//}
}



void gkPhysicsController::_resetContactInfo(void)
{
	if (isContactListener())
		m_localContacts.clear(true);
}
