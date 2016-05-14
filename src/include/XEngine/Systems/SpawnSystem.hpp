#ifndef __SPAWNSYSTEM_HPP__
#define __SPAWNSYSTEM_HPP__


#include <XESystem/Entityx/System.h>
#include <sfml/System/Vector3.hpp>

#include <unordered_set>

namespace XE {


	////////////////////////////////////////////////////////////
	/// \brief SpawnSystem class that spawns entities in a scene
	///
	////////////////////////////////////////////////////////////
	class SpawnSystem : public entityx::System < SpawnSystem >
	{

	public:

		SpawnSystem();// sf::Uint16 id, GraphicsManager& graphicsMgr, Scene& scene);// , Cam_Type style = CA_FREE);

		void configure(entityx::EventManager &events) override {
		//	events.subscribe<SpawnSystem>(*this);
		}

		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		
			for (entityx::Entity entity : spawns) {
			//	emit_particles(es, entity);
			//	entity.destroy();


				spawns.erase(entity);
			}
		}

		//void receive(const AnimationCreatedEvent &animcreated) {
		//	// Events are immutable, so we can't destroy the entities here. We defer
		//	// the work until the update loop.
		//	//collided.insert(collision.left);
		//	//collided.insert(collision.right);
		//}

		void spawn(entityx::Entity entity)
		{
			spawns.insert(entity);
		}

	private:
	
		std::unordered_set<entityx::Entity> spawns;


	};


} // namespace XE

#endif //__SPAWNSYSTEM_HPP__