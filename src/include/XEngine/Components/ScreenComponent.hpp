#ifndef __SCREENCOMPONENT_HPP__
#define __SCREENCOMPONENT_HPP__
//
//#include <sfml/System/Vector3.hpp>
//#include <XESystem/TransportData.hpp>
//#include <XEDAL/Objects/FBEngineTypes_generated.h>
#include <XEUI/UIStateManager.hpp>
#include <XEUI/Desktop.hpp>

#include <XERenderer/GUI/WLayer.hpp>

namespace sf { class Window; }

namespace XE
{
	class CameraRenderable;

	struct ScreenComponent
	{
	public:
		ScreenComponent(CameraRenderable& camRenderable, sf::Uint32 width, sf::Uint32 height, const XE::Uint16 atlasId = 0);

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

		WLayer wLayer;
		Desktop::Ptr m_Desktop;
		UIStateManager		mUIStateManager;
		bool isActive;

		sf::Uint32 width;
		sf::Uint32 height;
	};

} // ns XE

#endif // __SCREENCOMPONENT_HPP__