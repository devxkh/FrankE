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
	
	sc->mUIStateManager.addUIState(sc->mUIStateManager.build <UIState_2>(98, m_entity, true));
	sc->mUIStateManager.destroyUIState(99);
}

void UIState_1::MouseEnter() {
	// When the Button is clicked it's label should change.
		m_btnTest->SetLabel("Mouse Entered");
}


UIState_1::UIState_1(const XE::Uint16& id, entityx::Entity entity, bool replace = true)
	: UIState(id, replace)
	, m_entity(entity)
{
	auto screen = entity.component<XE::ScreenComponent>();
	XE::WLayer& layer = screen->wLayer;

	m_Box = XE::Box::Create(layer, XE::Box::Orientation::VERTICAL, 10.f);

	m_btnTest = XE::Button::Create(layer, "Hello World!");
	m_btnTest->size = sf::Vector2f(161, 36);
	m_btnTest->SetLabel("all widgets having a fixed width"); 

	m_checkBoxTest = XE::CheckButton::Create(layer, "checkboxText");
	m_checkBoxTest->size = sf::Vector2f(200.f, 20);

	m_entry = XE::Entry::Create(layer);
	m_entry->size = sf::Vector2f(200.f, 30.f);
	screen->m_Desktop->AddEntry(m_entry);

	m_imageTest = XE::Image::Create(layer, "OgreHead.png");
	m_imageTest->size = sf::Vector2f(48.f, 47.f);
	
	m_progressbar = XE::ProgressBar::Create(layer);
	m_progressbar->size = sf::Vector2f(200.f, 40.f);	

	m_Box->Pack(m_entry);
	m_Box->Pack(m_progressbar);
	m_Box->Pack(m_checkBoxTest);
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
	m_entity.component<XE::ScreenComponent>()->m_Desktop->RemoveEntry(m_entry);
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