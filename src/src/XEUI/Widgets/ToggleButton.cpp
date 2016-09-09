#include <XEUI/widgets/ToggleButton.hpp>

#include <XEUI/Container.hpp>

namespace XE {

	// Signals.
	Signal::SignalID ToggleButton::OnToggle = 0;

	ToggleButton::ToggleButton(WLayer& parentLayer, Uint16 fontId)
		: Button(parentLayer, fontId)
		, m_active(false)
	{
		//SetAlignment(sf::Vector2f(.5f, .5f));
		//Invalidate();

	}

	ToggleButton::~ToggleButton()
	{

	}

	ToggleButton::Ptr ToggleButton::Create(WLayer& parentLayer, const sf::String& label, Uint16 fontId) {
		auto ptr = Ptr(new ToggleButton(parentLayer, fontId));
		ptr->SetLabel(label);
		return ptr;
	}

	void ToggleButton::draw() {
		
		//sf::FloatRect req(GetAllocation());
		//sf::Vector2f parentPosition(GetParent()->GetAllocation());

		sf::Vector2f glyphPosition(Widget::getPosition().x, Widget::getPosition().y - 10);

		m_wcaption.setPosition(glyphPosition); // sf::Vector2f(parentAllocation.left + position.x, parentAllocation.top + position.y));
		m_wcaption.setSize(size.x, size.y);

		m_rectangle.setPosition(Widget::getPosition()); // sf::Vector2f(parentAllocation.left + position.x, parentAllocation.top + position.y));
		m_rectangle.setSize(sf::Vector2f(size.x, size.y));

		//if (GetState() == State::PRELIGHT)
		//	m_rectangle.setBackgroundImage("item_unknown.png");
		//else if (GetState() == State::ACTIVE)
		//	m_rectangle.setBackgroundImage("messagebox_bg.png");
		//else
		//	m_rectangle.setBackgroundImage("itembox.png");

		if (GetState() == State::ACTIVE || IsActive())
			m_rectangle.setBackground(Ogre::ColourValue::Black);
		else if (GetState() == State::PRELIGHT)
			m_rectangle.setBackground(Ogre::ColourValue::Red);
		else
			m_rectangle.setBackground(Ogre::ColourValue::Green);
	}

	void ToggleButton::HandleMouseButtonEvent(bool press, int x, int y) {
		
		if (!IsMouseInWidget()) {
			return;
		}

		if (press) {
			SetActive(!IsActive());
		}

		Button::HandleMouseClick(x, y);
	}

	const std::string& ToggleButton::GetName() const {
		static const std::string name("ToggleButton");
		return name;
	}


	void ToggleButton::SetActive(bool active) {
		if (active == m_active) {
			return;
		}

		m_active = active;

		if (active) {
			SetState(State::SELECTED);
		}
		else {
			SetState(State::NORMAL);
		}

		draw();
		GetSignals().Emit(OnToggle);
	}

	bool ToggleButton::IsActive() const {
		return m_active;
	}

}