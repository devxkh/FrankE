////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "UIState_2.h"

#include "UIState_1.h"

UIState_2::UIState_2(const XE::uint16& id, entityx::Entity entity, bool replace = true)
	: UIState(id, replace)
	, m_entity(entity)
{
	LOG(INFO) << "UIState_2 Init";

	XE::WLayer& layer = entity.component<XE::ScreenComponent>()->wLayer;

	m_Box = XE::Box::Create(layer, XE::Box::Orientation::VERTICAL, 10.f);

	m_btnTest = XE::Button::Create(layer, "This is UIState 2");
	m_btnTest->size = sf::Vector2f(200, 30);

	m_Box->Pack(m_btnTest);// Add the Button to the Box
	
	m_alignment = XE::Alignment::Create();
	m_alignment->Add(m_Box);
	m_alignment->SetScale(sf::Vector2f(.0f, .0f)); //smallest possible

	entity.component<XE::ScreenComponent>()->getDesktop()->Add(m_alignment);

	m_alignment->SetAlignment(sf::Vector2f(.5f, .5f));

	m_btnTest->GetSignal(XE::Widget::OnLeftClick).Connect(std::bind(&UIState_2::ButtonClick, this));
}

UIState_2::~UIState_2()
{
	m_Box->RemoveAll();
	m_alignment->Remove(m_Box);
	m_entity.component<XE::ScreenComponent>()->getDesktop()->Remove(m_alignment);
}

void UIState_2::ButtonClick() {
		
	std::ostringstream oss;
	oss << "I was clicked ";

	// When the Button is clicked it's label should change.
	m_btnTest->SetLabel(oss.str());
	
	auto sc = m_entity.component<XE::ScreenComponent>();

	sc->mUIStateManager.addUIState(sc->mUIStateManager.build <UIState_1>(1, m_entity, true));
	sc->mUIStateManager.destroyUIState(2);
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