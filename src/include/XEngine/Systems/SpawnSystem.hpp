#pragma once

#include <XESystem/Entityx/System.h>

namespace XE {

	class Scene;

	////////////////////////////////////////////////////////////
	/// \brief SpawnSystem class that spawns entities in a scene
	///
	////////////////////////////////////////////////////////////
	class SpawnSystem : public entityx::System < SpawnSystem >
	{

	public:

		SpawnSystem(Scene& scene);

		//void configure(entityx::EventManager &events) override {
		////	events.subscribe<SpawnSystem>(*this);
		//}

		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

		//void receive(const AnimationCreatedEvent &animcreated) {
		//	// Events are immutable, so we can't destroy the entities here. We defer
		//	// the work until the update loop.
		//	//collided.insert(collision.left);
		//	//collided.insert(collision.right);
		//}

	private:
		Scene& m_scene;

	};

} // namespace XE