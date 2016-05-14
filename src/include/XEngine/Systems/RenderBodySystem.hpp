#ifndef __RENDERBODYSYSTEM_HPP__
#define __RENDERBODYSYSTEM_HPP__

#include <XESystem/Entityx/System.h>

namespace XE
{
	class Renderable;
	class BodyComponent;
	class GraphicsManager;

	// Updates a body's position and rotation.
	class RenderBodySystem : public entityx::System<RenderBodySystem> {
	public:
		RenderBodySystem(GraphicsManager& gMgr);

		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

	private:
		GraphicsManager& _graphicsMgr;
	};


}

#endif //__RENDERBODYSYSTEM_HPP__