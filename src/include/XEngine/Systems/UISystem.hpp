#ifndef __UISYSTEM_HPP__
#define __UISYSTEM_HPP__


#include <XESystem/Entityx/System.h>
#include <XEngine/Components/ScreenComponent.hpp>

namespace XE
{

	// Updates a body's position and rotation.
	struct UISystem : public entityx::System<UISystem> {

		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {

			entityx::ComponentHandle<ScreenComponent> ui;

			for (entityx::Entity entity : es.entities_with_components(ui)) {
				/*body->position += body->direction * static_cast<float>(dt);
				body->rotation += body->rotationd * dt;*/
			}

		};




	};


}

#endif // __UISYSTEM_HPP__