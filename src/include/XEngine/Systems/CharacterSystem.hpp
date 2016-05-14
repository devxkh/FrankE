#ifndef __CHARACTERSYSTEM_HPP__
#define __CHARACTERSYSTEM_HPP__


#include <XESystem/Entityx/System.h>
#include <sfml/System/Vector3.hpp>

#include <XEngine/Components/Character.hpp>
#include <XEngine/Components/Animation.hpp>

namespace XE {


	////////////////////////////////////////////////////////////
	/// \brief Charactersystem class that can be controlled by a controller
	///
	////////////////////////////////////////////////////////////
	class CharacterSystem : public entityx::System < CharacterSystem >
		, public entityx::Receiver<CharacterSystem>  //: public Ogre::GeneralAllocatedObject
	{

	public:

		CharacterSystem();// sf::Uint16 id, GraphicsManager& graphicsMgr, Scene& scene);// , Cam_Type style = CA_FREE);

		void configure(entityx::EventManager &events) override {
			events.subscribe<CharacterSystem>(*this);
		}

		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		/*	for (entityx::Entity entity : collided) {
				emit_particles(es, entity);
				entity.destroy();
			}*/
		}

		void receive(const AnimationCreatedEvent &animcreated) {
			// Events are immutable, so we can't destroy the entities here. We defer
			// the work until the update loop.
			//collided.insert(collision.left);
			//collided.insert(collision.right);
		}

	private:



	};


} // namespace XE

#endif //__CHARACTERSYSTEM_HPP__