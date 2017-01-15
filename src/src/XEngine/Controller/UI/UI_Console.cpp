////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <XEngine/Controller/UI/UI_Console.hpp>

#include <XEUI/UIManager.hpp>

#include <XEngine/Components/Controller.hpp>
//#include <XEUI/UISerializer.hpp>
#include <XEUI/DAL/FB_UI_StateData_generated.h>
//#include <XEUI/UIPanel.hpp>
//#include <XEUI/PanelContainer.hpp>
//#include <XEUI/UIScreen.hpp>

//#include <States/UIStates/UI_Controller.hpp>
//#include <States/UIStates/UI_Character.hpp>
//#include <States/UIStates/UI_Controls.hpp>
//#include <States/UIStates/UI_Games.hpp>
//#include <States/UIStates/UI_GameStart.hpp>
//#include <States/UIStates/UI_Scene.hpp>
//#include <States/UIStates/UI_Team.hpp>

#include <XERenderer/GraphicsManager.hpp>
#include <XESystem/Entityx/Entity.h>
#include <XEngine/Components/ScreenComponent.hpp>
#include <XERenderer/CameraRenderable.hpp>


namespace XE {

	UIConsole::UIConsole(const Ogre::uint16& id, entityx::Entity entity, bool replace = true)
		: UIState(id, replace)
		, m_screen(entity.component<ScreenComponent>().get())
	{
		WLayer& layer = *m_screen->wLayer.get();
		
		m_consoleWidgetContainer = Box::Create(layer, Box::Orientation::VERTICAL, 0.f);

		m_linesOfText.emplace_back(Label::Create(layer));
		m_linesOfText.emplace_back(Label::Create(layer));
		m_linesOfText.emplace_back(Label::Create(layer));
		m_linesOfText.emplace_back(Label::Create(layer));
		m_linesOfText.emplace_back(Label::Create(layer));


		m_entry = Entry::Create(layer);
		m_entry->size = sf::Vector2f(200.f, 30.f);
		m_screen->m_Desktop->AddEntry(m_entry);

		for each (auto label in m_linesOfText)
		{
			label->size = sf::Vector2f(200,30);
			label->SetText("xxx");
			m_consoleWidgetContainer->Pack(label);
		}

		m_consoleWidgetContainer->Pack(m_entry);

		m_alignment = Alignment::Create();
		m_alignment->Add(m_consoleWidgetContainer);
		m_alignment->SetScale(sf::Vector2f(.0f, .0f)); //smallest possible

		m_screen->getDesktop()->Add(m_alignment);

		m_alignment->SetAlignment(sf::Vector2f(0.0f, 1.0f));
	}

	UIConsole::~UIConsole()
	{
		m_linesOfText.clear();
		m_screen->m_Desktop->RemoveEntry(m_entry);
		m_consoleWidgetContainer->RemoveAll();
		m_alignment->Remove(m_consoleWidgetContainer);
		m_screen->getDesktop()->Remove(m_alignment);
	}

	void UIConsole::create(const char* fbdata)
	{

	}
	void UIConsole::reload(const char* fbdata)		{

	}
	
	void UIConsole::resume()
	{
		// let the state update the game
		//	m_states.top()->update();
	}
	void UIConsole::pause()
	{
		// let the state update the game
		//	m_states.top()->update();
	}

	void UIConsole::update(float delta)
	{

	//	m_Ogreconsole->update();

		// let the state update the game
		//	m_states.top()->update();
	}

	void UIConsole::draw()
	{
		// let the state draw the screen
		//	m_states.top()->draw();
	}
} // namespace XE
