#ifndef __ENTITYRENDERSYSTEM_HPP__
#define __ENTITYRENDERSYSTEM_HPP__


#include <XESystem/Entityx/System.h>
#include <XERenderer/Renderable.hpp>

namespace XE
{

	// Updates a body's position and rotation.
	struct EntityRenderSystem : public entityx::System<EntityRenderSystem> {
		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {

			entityx::ComponentHandle<Renderable> renderable;

			for (entityx::Entity entity : es.entities_with_components(renderable)) {
				/*body->position += body->direction * static_cast<float>(dt);
				body->rotation += body->rotationd * dt;*/
			}

		};
	};


}

#endif // __ENTITYRENDERSYSTEM_HPP__