#include <XEngine/Systems/RenderBodySystem.hpp>

#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Components/Body.hpp>
#include <XERenderer/Renderable.hpp>
#include <XERenderer/LightRenderable.hpp>

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
		
		for (entityx::Entity entity : es.entities_with_components(body)) {
			
			auto debug =  body->getPosition();

			if (body->isDirty())
			{
				//TODO use transformation for performance?
				if (entity.has_component<Renderable>())
				{
					entityx::ComponentHandle<Renderable> renderable = entity.component<Renderable>();
					renderable->setWorldPosition(body->getPosition());
					renderable->setOrientation(body->getOrientation());
					renderable->setScale(body->getScale());
				}
								
				if (entity.has_component<LightRenderable>())
				{
					entityx::ComponentHandle<LightRenderable> lightRenderable = entity.component<LightRenderable>();
					
					//TODO BAD!! creates each time a queue task!
					lightRenderable->setPosition(body->getPosition());
					lightRenderable->setDirection(body->getOrientation() * Ogre::Vector3::UNIT_SCALE);
				}

				body->isDirty(false);
			}	

#ifdef CompileEditor
			if (body->isSelected)
				_graphicsMgr.getGUIRenderer().m_CurrentGizmoOrigin = body->GetWorldTransform();
#endif
		}

		_graphicsMgr.getIntoRendererQueue().push([this]()
		{
			for each (auto _t_renderable in _graphicsMgr._t_Renderables)
			{
				if (_t_renderable->isDirty)
					_t_renderable->_t_update();
			}

			_graphicsMgr.getFromRendererQueue().push([this]() {
				_graphicsMgr.GetRenderTask(RenderTaskID::RenderBody).isDone = true;
			});
		});
	};
}