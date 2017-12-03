#include "EditorControllerSystem.hpp"

#include <XEngine.hpp>

#include <ThirdParty/imgui/imgui.h>
#include <XERenderer/Editor/ImGuizmo.h>

#include <XEngine/Editor/SceneViewerUIState.hpp>

#include <memory>

namespace XET {

	EditorControllerSystem::EditorControllerSystem(XE::XEngine& engine)
		: m_engine(engine)
	{
	
	}

	EditorControllerSystem::~EditorControllerSystem()
	{
	}
	
	
	void EditorControllerSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
	{
		
		if (m_engine.getGraphicsManager()._isRenderThreadFinished)
		{
			//push scene data into rendererthread
			entityx::ComponentHandle<XE::EditorComponent> tmpEditorComponent;

			for (entityx::Entity entity : es.entities_with_components(tmpEditorComponent)) {

				XE::BodyComponent body = *entity.getComponent<XE::BodyComponent>();
				XE::EditorComponent editorComponent = *tmpEditorComponent.get();

				if (!body.isDirty())
					continue;

				m_engine.getGraphicsManager().getIntoRendererQueue().push([this, body, editorComponent]()
				{
					auto _t_uistate = static_cast<XE::SceneViewerUIState*>(m_engine.getGraphicsManager().getGUIRenderer()._t_EditorUIRenderer->getUIState(XE::EUSID::SceneHierarchy));

					//body id already displayed?
					for each (auto& displayedEntity in _t_uistate->_t_displayedEntities)
					{
						//found
						if (displayedEntity->id == editorComponent.id)
						{
							auto displayBody = static_cast<XE::DisplayBody*>(displayedEntity->displayInformation.get());
							displayBody->position = body.getPosition();
							displayBody->name = editorComponent.name;
							return;
						}
					}

					//not found -> add to vector
					std::unique_ptr<XE::EntityDebug> entityDebug(new XE::EntityDebug());
					entityDebug->id = editorComponent.id;

					std::unique_ptr<XE::DisplayBody> displayBody(new XE::DisplayBody());
					displayBody->position = body.getPosition();
					displayBody->name = editorComponent.name;
					entityDebug->displayInformation = std::move(displayBody);

					_t_uistate->_t_displayedEntities.push_back(std::move(entityDebug));
				});
			}
		}
	}

} // namespace XE
