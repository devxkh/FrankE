#include <XEngine/Systems/SpawnSystem.hpp>

#include <XEngine/Components/Body.hpp>
#include <XEngine/Components/SpawnComponent.hpp>
#include <XEngine/Components/SpawnPointComponent.hpp>
#include <XEngine/Components/PhysicsComponents.hpp>

#include <XEngine/Scene.hpp>

namespace XE
{
	SpawnSystem::SpawnSystem(Scene& scene)
		: m_scene(scene)
	{

	}

	//void configure(entityx::EventManager &events) override {
	////	events.subscribe<SpawnSystem>(*this);
	//}

	void SpawnSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) 
	{
		entityx::ComponentHandle<SpawnComponent>  spawn;
		entityx::ComponentHandle<PhysicsComponent> phyiscsComp;
		entityx::ComponentHandle<BodyComponent> body;

		//get all spawns
		for (entityx::Entity entity : m_scene.entities.entities_with_components(spawn, phyiscsComp, body)) {

			entityx::ComponentHandle<SpawnPointComponent>  spawnPoint;
			entityx::ComponentHandle<BodyComponent>  spBody;

			//get all spawnpoints
			for (entityx::Entity entity : m_scene.entities.entities_with_components(spawnPoint, spBody)) {

				if (spawn->spawnPointId > 0 && spawnPoint->id == spawn->spawnPointId) //get spawnpoint from spawnpoint Id
				{
					TransformState ts(spBody->getPosition(), body->getOrientation(), body->getScale());

					phyiscsComp->objects[0]->setTransformState(ts);
					spawn.remove();

					break;
				}
				else if (spawn->group == spawnPoint->group) //get spawnpoint group from spawn group
				{
					TransformState ts(spBody->getPosition(), body->getOrientation(), body->getScale());

					phyiscsComp->objects[0]->setTransformState(ts);
					spawn.remove();


					break;
				}
			}		
		}
	}
}