#pragma once

#include <XESystem/SystemConfig.hpp>
#include <XEUI/UIStateManager.hpp>
#include <XEUI/Desktop.hpp>


class SDL_Window;

namespace XE
{
	class WLayer;
	class CameraRenderable;

	struct ScreenComponent
	{
	public:
		ScreenComponent(CameraRenderable& camRenderable, Uint32 width, Uint32 height, const Uint16 atlasId = 0);
	
		ScreenComponent(CameraRenderable& camRenderable, SDL_Window* window, const Uint16 atlasId = 0);

		~ScreenComponent();

		inline Desktop::Ptr getDesktop(){ return m_Desktop; }

		//void createConsole()
		//{
		//	mUIStateManager.addUIState(mUIStateManager.build <XE::UIConsole>(10, this, true));


		//	//todo KH	UIPanel* panel = mEngine->getUIMgr().getUIPanel("panelConsole");
		//	//todo KH	mConsole = static_cast<OgreConsole*> (panel->getItem("consoleMain"));


		//	//		mStateData->mUIStateManager.addUIState(std::move(state));

		//	//mStateData->mUIManager.crea
		//	//mConsole = new OgreConsole();
		//	//	mConsole->init(mStateData->mUIManager.getScreen("WorldState"));
		//	//	mConsole->addCommand("whoami", whoami);
		//}

		//void createDebugState()
		//{
		//	mUIStateManager.addUIState(mUIStateManager.build <XE::UIDebug>(11, this, true));
		//}

		void setSize(const Uint32 width, const Uint32 height);

		std::shared_ptr<WLayer> wLayer;
		Desktop::Ptr m_Desktop;
		std::shared_ptr<UIStateManager>		mUIStateManager;
		bool isActive;

		Int32 width;
		Int32 height;
	};

} // ns XE