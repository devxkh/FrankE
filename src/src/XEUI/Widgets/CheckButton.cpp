#include <XEUI/widgets/CheckButton.hpp>

#include <XEUI/Container.hpp>

#include <XERenderer/GUI/WRectangle.hpp>
#include <XERenderer/GUI/WCaption.hpp>

namespace XE {

	CheckButton::CheckButton(WLayer& parentLayer, Uint16 fontId)
		: ToggleButton(parentLayer, fontId)
		//, m_checkedRectangle(parentLayer,0,0,20,20)
	{
		m_shapesContainer.shapes.emplace_back(std::move(std::unique_ptr<WRectangle>(new WRectangle(parentLayer, 0, 0, 20, 20))));
		m_checkedRectangle = static_cast<WRectangle*>(m_shapesContainer.shapes.back().get());


		//SetAlignment(sf::Vector2f(.5f, .5f));
		//Invalidate();

	}

	CheckButton::~CheckButton()
	{

	}

	CheckButton::Ptr CheckButton::Create(WLayer& parentLayer, const sf::String& label, Uint16 fontId) {
		auto ptr = Ptr(new CheckButton(parentLayer, fontId));
		ptr->SetLabel(label);
		return ptr;
	}

	void CheckButton::draw() {
		
		m_checkedRectangle->setPosition(Widget::getPosition());

		m_rectangle->setPosition(Widget::getPosition());
		m_rectangle->setSize(sf::Vector2f(size.x, size.y));

		//if (GetState() == State::PRELIGHT)
		//	m_rectangle.setBackgroundImage("item_unknown.png");
		//else if (GetState() == State::ACTIVE)
		//	m_rectangle.setBackgroundImage("messagebox_bg.png");
		//else
		//	m_rectangle.setBackgroundImage("itembox.png");

		if (GetState() == State::ACTIVE || IsActive())
			m_checkedRectangle->setBackground(Ogre::ColourValue::Black);
		else if (GetState() == State::PRELIGHT)
			m_checkedRectangle->setBackground(Ogre::ColourValue::Red);
		else
			m_checkedRectangle->setBackground(Ogre::ColourValue::Green);

		//text right aligned to the checkedRectangle
		//auto textPos = sf::Vector2f(Widget::getPosition().x + 20, Widget::getPosition().y);
		//m_wcaption.setPosition(textPos);
		m_wcaption->setSize(size.x, size.y);

		sf::Vector2i textSize = m_wcaption->GetTextStringMetrics(m_wcaption->getText());

		auto offsetx = 20;

		auto posx = Widget::getPosition().x;
		auto offsety = (size.y * 0.5f) - (textSize.y / 2);
		auto posy = Widget::getPosition().y;
		sf::Vector2f newTextPos(posx + offsetx, posy + offsety + 18);
		m_wcaption->setPosition(newTextPos);
	}

	const std::string& CheckButton::GetName() const {
		static const std::string name("CheckButton");
		return name;
	}
}