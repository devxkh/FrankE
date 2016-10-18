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
		
		m_wcaption.setPosition(Widget::getPosition());
		m_wcaption.setSize(size.x, size.y);
		
		sf::Vector2i textSize = m_wcaption.GetTextStringMetrics(m_wcaption.getText());
		
		
		auto offsetx =0;

		auto posx = Widget::getPosition().x;
		auto offsety = (size.y * 0.5f) - (textSize.y / 2);
		auto posy = Widget::getPosition().y;
		sf::Vector2f textPos(posx + offsetx, posy + offsety + 18);
		m_wcaption.setPosition(textPos);

		m_rectangle.setPosition(Widget::getPosition());
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