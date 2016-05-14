////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "UIState_1.h"

#include "UIState_2.h"
#include <sstream>
#include <XEngine/Components/ScreenComponent.hpp>

void UIState_1::ButtonClick() {

	// Generate random value for progress bar percent done
	auto random_percentage = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		m_progressbar->SetFraction(random_percentage);

	std::ostringstream oss;
	oss << "I was clicked, fraction " << random_percentage;

	// When the Button is clicked it's label should change.
	m_btnTest->SetLabel(oss.str());
	
	auto sc = m_entity.component<XE::ScreenComponent>();
	
	sc->mUIStateManager.addUIState(sc->mUIStateManager.build <UIState_2>(2, m_entity, true));
	sc->mUIStateManager.destroyUIState(1);
}

void UIState_1::MouseEnter() {
	// When the Button is clicked it's label should change.
		m_btnTest->SetLabel("Mouse Entered --");
}


UIState_1::UIState_1(const XE::Uint16& id, entityx::Entity entity, bool replace = true)
	: UIState(id, replace)
	, m_entity(entity)
{
	XE::WLayer& layer = entity.component<XE::ScreenComponent>()->wLayer;

	m_Box = XE::Box::Create(layer, XE::Box::Orientation::VERTICAL, 10.f);

	m_btnTest = XE::Button::Create(layer, "Hello World!\nAnother Line");
	m_btnTest->size = sf::Vector2f(200, 30);
	m_btnTest->SetLabel("test geht noch nicht mit font size berechnen!!"); 

	m_entry = XE::Entry::Create(layer);
	m_entry->size = sf::Vector2f(200.f, 30.f);
	
	m_imageTest = XE::Image::Create(layer, "item_ball_hover.png");
	m_imageTest->size = sf::Vector2f(200.f, 100);
	
	m_progressbar = XE::ProgressBar::Create(layer);
	m_progressbar->size = sf::Vector2f(200.f, 40.f);	

	m_Box->Pack(m_entry);
	m_Box->Pack(m_progressbar);
	m_Box->Pack(m_btnTest);
	m_Box->Pack(m_imageTest);

	//m_window = XE::UIWindow::Create(layer);
	//m_window->size = sf::Vector2f(250.f, 200.f);
	//m_window->Add(m_Box);

	m_alignment = XE::Alignment::Create();
	m_alignment->Add(m_Box);
	m_alignment->SetScale(sf::Vector2f(.0f, .0f)); //smallest possible

	entity.component<XE::ScreenComponent>()->getDesktop()->Add(m_alignment);

	m_alignment->SetAlignment(sf::Vector2f(.5f, .5f));

	m_btnTest->GetSignal(XE::Widget::OnLeftClick).Connect(std::bind(&UIState_1::ButtonClick, this));
	m_btnTest->GetSignal(XE::Widget::OnMouseEnter).Connect(std::bind(&UIState_1::MouseEnter, this));
}

UIState_1::~UIState_1()
{
	m_Box->RemoveAll();
	m_alignment->Remove(m_Box);
	m_entity.component<XE::ScreenComponent>()->getDesktop()->Remove(m_alignment);
}

void UIState_1::create(const char* fbdata)
{

}
void UIState_1::reload(const char* fbdata) {

}

void UIState_1::resume()
{

}
void UIState_1::pause()
{
	
}

void UIState_1::update(float delta)
{
}

void UIState_1::draw()
{

}