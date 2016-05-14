#ifndef __PHYSICSSYSTEM_HPP__
#define __PHYSICSSYSTEM_HPP__

#include <XESystem/Entityx/System.h>
#include <XEPhysics/Physics/gkDynamicsWorld.h>

namespace XE
{
	class PhysicsSystem : public entityx::System<PhysicsSystem> {
		static const int PARTITIONS = 200;

		struct Candidate {
			//sf::Vector2f position;
			float radius;
			entityx::Entity entity;
		};

	public:
		PhysicsSystem(XE::Scene& scene);

		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;


		gkDynamicsWorld& getDynamicsWorld();

	private:

		void reset();

		void collect(entityx::EntityManager &entities);

		void collide(entityx::EventManager &events);

		bool collided(const Candidate &left, const Candidate &right);

		gkDynamicsWorld        m_physicsWorld;
		std::vector<std::vector<Candidate>> grid;
		//sf::Vector2u size;

	};
}

#endif // __PHYSICSSYSTEM_HPP__