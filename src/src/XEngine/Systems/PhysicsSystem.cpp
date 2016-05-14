#include <XEngine/Systems/PhysicsSystem.hpp>
#include <XESystem/Entityx/System.h>
#include <XEngine/Components/PhysicsComponents.hpp>
#include <XEngine/Components/Body.hpp>

#include <XEPhysics/Physics/gkDynamicsWorld.h>

namespace XE
{
	PhysicsSystem::PhysicsSystem(XE::Scene& scene)
		: m_physicsWorld("", scene)
		//		: 	size(target.getSize()) 
	{
		/*size.x = size.x / PARTITIONS + 1;
		size.y = size.y / PARTITIONS + 1;*/

		//m_physicsWorld("", *this),
		//		mWorldMesh(this),
		//		mWorldMesh.setDebugDrawer(m_physicsWorld.getBulletWorld()->getDebugDrawer());
	}

	void PhysicsSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)  {

		entityx::ComponentHandle<PhysicsComponent> physicsComponent;
		entityx::ComponentHandle<BodyComponent> bodyComponent;

		for (entityx::Entity entity : es.entities_with_components(physicsComponent, bodyComponent)) {

			for (int i = 0; i < physicsComponent->objects.size(); i++)
			{
				
			//	TransformState tState(bodyComponent->getPosition(), bodyComponent->getOrientation(), bodyComponent->getScale());
			//	physicsComponent->objects[i]->setTransformState(tState);
			}

		}

		m_physicsWorld.step(dt);// .asMicroseconds());

		reset();
		collect(es);
		collide(events);
	};


	gkDynamicsWorld& PhysicsSystem::getDynamicsWorld()
	{
		//if (!m_physicsWorld)
		//	m_physicsWorld = OGRE_NEW_T(gkDynamicsWorld(mName, this), Ogre::MEMCATEGORY_GENERAL);

		return m_physicsWorld;
	}


	void PhysicsSystem::reset() {
		grid.clear();
		//	grid.resize(size.x * size.y);
	}

	void PhysicsSystem::collect(entityx::EntityManager &entities) {
		//entityx::ComponentHandle<Body> body;
		//entityx::ComponentHandle<Collideable> collideable;
		//for (entityx::Entity entity : entities.entities_with_components(body, collideable)) {
		//	unsigned int
		//		left = static_cast<int>(body->position.x - collideable->radius) / PARTITIONS,
		//		top = static_cast<int>(body->position.y - collideable->radius) / PARTITIONS,
		//		right = static_cast<int>(body->position.x + collideable->radius) / PARTITIONS,
		//		bottom = static_cast<int>(body->position.y + collideable->radius) / PARTITIONS;
		//	Candidate candidate{ body->position, collideable->radius, entity };
		//	//unsigned int slots[4] = {
		//	//	left + top * size.x,
		//	//	right + top * size.x,
		//	//	left + bottom * size.x,
		//	//	right + bottom * size.x,
		//	//};
		//	//grid[slots[0]].push_back(candidate);
		//	/*if (slots[0] != slots[1]) grid[slots[1]].push_back(candidate);
		//	if (slots[1] != slots[2]) grid[slots[2]].push_back(candidate);
		//	if (slots[2] != slots[3]) grid[slots[3]].push_back(candidate);*/
		//}
	}

	void PhysicsSystem::collide(entityx::EventManager &events) {
		for (const std::vector<Candidate> &candidates : grid) {
			for (const Candidate &left : candidates) {
				for (const Candidate &right : candidates) {
					if (left.entity == right.entity) continue;
					//if (collided(left, right))
					//	events.emit<CollisionEvent>(left.entity, right.entity);
				}
			}
		}
	}

	bool PhysicsSystem::collided(const Candidate &left, const Candidate &right) {
		return 0;// length(left.position - right.position) < left.radius + right.radius;
	}
}