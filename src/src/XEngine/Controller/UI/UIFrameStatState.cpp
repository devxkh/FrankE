////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <XEngine/Controller/UI/UIFrameStatState.hpp>
#include <XEngine/Components/Controller.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XEUI/UIManager.hpp>
#include <XESystem/Entityx/Entity.h>
#include <XEngine/Components/ScreenComponent.hpp>
#include <XEngine/Components/Controller.hpp>
#include <XERenderer/CameraRenderable.hpp>
#include <XEUI/widgets/Label.hpp>
#include <XEUI/Alignment.hpp>
#include <XEUI/Box.hpp>

namespace XE {

	UIDebug::UIDebug(const Ogre::uint16& id, entityx::Entity entity, bool replace = true)
		: UIState(id, replace)
		, m_screen(entity.component<XE::ScreenComponent>().get())
		//, m_controller(entity.component<XE::ControllerComponent>().get())
		, m_cameraRenderable(entity.component<XE::CameraRenderable>().get())
	{
		XE::WLayer& layer = *m_screen->wLayer.get();

		m_Box = Box::Create(layer, Box::Orientation::VERTICAL, 2.f);
		m_FpsRendererThread = Label::Create(layer, "Hello World!\nAnother Line");
		m_FpsMainThread = Label::Create(layer, "Hello World!\nAnother Line");
		m_FpsAvqThread = Label::Create(layer, "Hello World!\nAnother Line");
		m_BatchCount = Label::Create(layer, "Hello World!\nAnother Line");


		m_FpsRendererThread->size = sf::Vector2f(200, 15); //todo req per text len
		m_FpsMainThread->size = sf::Vector2f(200, 15); //todo req per text len
		m_FpsAvqThread->size = sf::Vector2f(200, 15); //todo req per text len
		m_BatchCount->size = sf::Vector2f(200, 15); //todo req per text len
		//-------------------------------------------------------------------------------

		m_Box->Pack(m_FpsRendererThread);
		m_Box->Pack(m_FpsAvqThread);
		m_Box->Pack(m_BatchCount);
		m_Box->Pack(m_FpsMainThread);

		m_alignment = XE::Alignment::Create();
		m_alignment->Add(m_Box);	// Add m_Box to the alignment.
		m_alignment->SetScale(sf::Vector2f(.0f, .0f)); //smallest possible
		m_alignment->SetAlignment(sf::Vector2f(1.0f, .5f));

		m_screen->getDesktop()->Add(m_alignment); //add alignment to desktop -> so alignment get the desktop as parent
	}

	UIDebug::~UIDebug()
	{
		m_Box->RemoveAll();
		m_alignment->Remove(m_Box);
		m_screen->getDesktop()->Remove(m_alignment);
	}

	void UIDebug::create(const char* fbdata)
	{

	}
	void UIDebug::reload(const char* fbdata) {

	}

	void UIDebug::resume()
	{

	}

	void UIDebug::pause()
	{

	}

	float getFPS(const sf::Time& time) {
		return (1000000.0f / time.asMicroseconds());
	}

	sf::Clock FPSClock;

	void UIDebug::update(float delta)
	{
		GraphicsManager::FrameStats& stats = m_cameraRenderable->getGraphicsManager().getFrameStats();
		std::stringstream fpsAvg;
		fpsAvg << (int)stats.AvgFps << " AvgFps RThread";
		m_FpsAvqThread->SetText(fpsAvg.str());

		std::stringstream fps;
		fps << (int)stats.Fps << " Fps RThread";
		m_FpsRendererThread->SetText(fps.str());


		std::stringstream fpsWorst;
		fpsWorst << (int)stats.WorstTime << " Worst RThread";
		m_BatchCount->SetText(fpsWorst.str());

		//m_controller->get()->engine.
		std::stringstream fpsMain;
		fpsMain << (int)getFPS(FPSClock.restart()) << " MainThread";
		m_FpsMainThread->SetText(fpsMain.str());
	}

	void UIDebug::draw()
	{
	}

} // namespace XE
