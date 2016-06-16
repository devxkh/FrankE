#include <XEngine/Systems/RenderBodySystem.hpp>

#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Components/Body.hpp>
#include <XERenderer/Renderable.hpp>

namespace XE
{

	RenderBodySystem::RenderBodySystem(GraphicsManager& gMgr)
		: _graphicsMgr(gMgr)
	{

	}

	void RenderBodySystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
	
		if (!_graphicsMgr.GetRenderTask(RenderTaskID::RenderBody).isDone) // wait until render has done all tasks
			return;
		
		_graphicsMgr.GetRenderTask(RenderTaskID::RenderBody).isDone = false;

		entityx::ComponentHandle<BodyComponent> body;
		entityx::ComponentHandle<Renderable> renderable;

		for (entityx::Entity entity : es.entities_with_components(body, renderable)) {
			
			if (body->isDirty())
			{
				//TODO use transformation for performance?
				renderable->setWorldPosition(body->getPosition());
				renderable->setOrientation(body->getOrientation()); 
				body->isDirty(false);
			}			
		}

		_graphicsMgr.getIntoRendererQueue().push([this]()
		{
			for each (auto _t_renderable in _graphicsMgr._t_Renderables)
			{
				if (_t_renderable->isDirty)
					_t_renderable->_t_update();
			}

			_graphicsMgr.GetRenderTask(RenderTaskID::RenderBody).isDone = true;
		});
	};
}