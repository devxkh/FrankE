#pragma once

#include <ThirdParty/sfml/include/sfml/System/Vector2.hpp>
#include <XERenderer/Editor/IEditorUIState.hpp>

#include <OgreTexture.h>
#include <ThirdParty/SDL/include/SDL.h>

#include <vector>
#include <memory>
#include <atomic>

namespace Ogre {
	class Matrix4;
}

namespace XE {

	class GraphicsManager;
	class ImgGuiMovableObject;

	///lives in Rendererthread
	class EditorUIRenderer
	{

	public:
		EditorUIRenderer(GraphicsManager& graphicsManager, Ogre::Camera* camera);

		~EditorUIRenderer();

		void init();

		void Render(const Ogre::Matrix4& projMatrix, const sf::Vector2f& viewportSize, const float delta);
		
		static bool ProcessSDLEvent(SDL_Event* event);

		IEditorUIState& createUIState(std::unique_ptr<IEditorUIState> uiState);

		IEditorUIState* getUIState(int ID);

		std::atomic<bool> IsGizmoEnabled;

	private:	

		Ogre::Camera* m_camera;

		void _t_createFontTexture();
			
		GraphicsManager& m_graphicsManager;

		Ogre::TexturePtr mFontTex;
		
		std::vector<ImgGuiMovableObject*> _t_ImgGuiMovableObject;
	
		std::vector<std::unique_ptr<IEditorUIState>> m_EditorUIStates;
	};

}