////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "UIState_2.h"

#include "UIState_1.h"

#include "../XETCommon/TestController.hpp"

UIState_2::UIState_2(const XE::uint16& id, entityx::Entity entity, bool replace = true)
	: UIState(id, replace)
	, m_screen(entity.component<XE::ScreenComponent>().get())
	, m_controller(entity.component<XET::TestControllerComponent>().get())
{
	LOG(plog::info) << "UIState_2 Init";

	XE::WLayer& layer = *m_screen->wLayer.get();

	m_Box = XE::Box::Create(layer, XE::Box::Orientation::VERTICAL, 10.f);

	m_btnTest = XE::Button::Create(layer, "This is UIState 2");
	m_btnTest->size = sf::Vector2f(161, 36);

	m_Box->Pack(m_btnTest);// Add the Button to the Box
	
	m_alignment = XE::Alignment::Create();
	m_alignment->Add(m_Box);
	m_alignment->SetScale(sf::Vector2f(.0f, .0f)); //smallest possible

	m_screen->getDesktop()->Add(m_alignment);

	m_alignment->SetAlignment(sf::Vector2f(.5f, .5f));

	m_btnTest->GetSignal(XE::Widget::OnLeftClick).Connect(std::bind(&UIState_2::ButtonClick, this));
}

UIState_2::~UIState_2()
{
	m_Box->RemoveAll();
	m_alignment->Remove(m_Box);
	m_screen->getDesktop()->Remove(m_alignment);
}

void UIState_2::ButtonClick() {
		
	std::ostringstream oss;
	oss << "I was clicked ";

	// When the Button is clicked it's label should change.
	m_btnTest->SetLabel(oss.str());
	
	entityx::ComponentHandle<XET::TestControllerComponent>  controller;

	for (entityx::Entity entity : m_controller->get()->engine.getScene().entities.entities_with_components(controller)) {

		//todo condition for controller selection

		m_screen->mUIStateManager.get()->addUIState(m_screen->mUIStateManager.get()->build <UIState_1>(99, entity, true));
		m_screen->mUIStateManager.get()->destroyUIState(98);
	}

}

void UIState_2::create(const char* fbdata)
{

}
void UIState_2::reload(const char* fbdata) {

}

void UIState_2::resume()
{

}
void UIState_2::pause()
{

}

void UIState_2::update(float delta)
{
}

void UIState_2::draw()
{

}