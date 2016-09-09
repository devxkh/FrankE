#include <XEUI/widgets/Button.hpp>

#include <XEUI/Container.hpp>


//#include <SFGUI/Button.hpp>
//#include <SFGUI/Context.hpp>
//#include <SFGUI/Engine.hpp>
//#include <SFGUI/Image.hpp>
//#include <SFGUI/RenderQueue.hpp>

namespace XE {

	Button::Button(WLayer& parentLayer, Uint16 fontId) :
		m_wcaption(parentLayer, fontId)
		, m_rectangle(parentLayer, 0, 0, 0, 0)
	{
		//SetAlignment(sf::Vector2f(.5f, .5f));
		//Invalidate();

		//m_rectangle.setBackground(Ogre::ColourValue::Green);
	}

	Button::~Button()
	{

	}

	Button::Ptr Button::Create(WLayer& parentLayer, const sf::String& label, Uint16 fontId) {
		auto ptr = Ptr(new Button(parentLayer, fontId));
		ptr->SetLabel(label);
		return ptr;
	}

	void Button::draw() {
		
		//sf::FloatRect req(GetAllocation());
		//sf::Vector2f parentPosition(GetParent()->GetAllocation());

		//sf::Vector2f glyphPosition(Widget::getPosition().x, Widget::getPosition().y - 10);

		m_wcaption.setPosition(Widget::getPosition());//glyphPosition); // sf::Vector2f(parentAllocation.left + position.x, parentAllocation.top + position.y));
		m_wcaption.setSize(size.x, size.y);
		sf::Vector2i textSize = m_wcaption.GetTextStringMetrics(m_wcaption.getText());
		/*--------
		xxxx*/
		auto offsetx = (size.x * 0.5f) - (textSize.x / 2);
		auto posx = Widget::getPosition().x;
		auto offsety = (size.y * 0.5f) - (textSize.y / 2);
		auto posy = Widget::getPosition().y;
		sf::Vector2f textPos(posx + offsetx, posy + offsety);
		m_wcaption.setPosition(textPos);
		

		m_rectangle.setPosition(Widget::getPosition()); // sf::Vector2f(parentAllocation.left + position.x, parentAllocation.top + position.y));
		m_rectangle.setSize(sf::Vector2f(size.x, size.y));

		if (GetState() == State::PRELIGHT)
			m_rectangle.setBackgroundImage("Button_hover.png");
		else if (GetState() == State::ACTIVE)
			m_rectangle.setBackgroundImage("Button_pressed.png");
		else
			m_rectangle.setBackgroundImage("Button_default.png");

		
	/*	if (GetState() == State::PRELIGHT)
			m_rectangle.setBackground(Ogre::ColourValue::Red);
		else if (GetState() == State::ACTIVE)
			m_rectangle.setBackground(Ogre::ColourValue::Black);
		else
			m_rectangle.setBackground(Ogre::ColourValue::Green);*/
		
		
		//m_label.setText(GetLabel());

		//todo
		//return Context::Get().GetEngine().CreateButtonDrawable(std::dynamic_pointer_cast<const Button>(shared_from_this()));
	}

	void Button::SetLabel(const sf::String& label) {
		m_wcaption.setText(label);

	/*	RequestResize();
		Invalidate();*/
	}

	const sf::String& Button::GetLabel() const {
		return "todo";// m_label.getText();// m_label;
	}

	void Button::SetImageName(const std::string& imageName) {
		m_imageName = imageName;
	}


	//void Button::SetImage(std::shared_ptr<Image> image) {
	//	ClearImage();
	//	Add(image);
	//}

	//Image::PtrConst Button::GetImage() const {
	//	return std::static_pointer_cast<Image>(GetChild());
	//}

	void Button::ClearImage() {
		auto child = GetChild();

		if (child) {
			Remove(child);
		}
	}

	void Button::HandleMouseEnter(int /*x*/, int /*y*/) {
		if (GetState() == State::NORMAL) {
			SetState(State::PRELIGHT);
		}
	}

	void Button::HandleMouseLeave(int /*x*/, int /*y*/) {
		if (GetState() == State::PRELIGHT) {
			SetState(State::NORMAL);
		}
	}

	void Button::HandleMouseButtonEvent(bool press, int /*x*/, int /*y*/) {
		if (!IsMouseInWidget()) {
			if (GetState() == State::ACTIVE) {
				SetState(State::NORMAL);
			}

			return;
		}

		//if (button == sf::Mouse::Left) {
			if (press) {
				SetState(State::ACTIVE);
			}
			else if (GetState() == State::ACTIVE) {
				SetState(State::PRELIGHT);
			}
		//}
	}

	const std::string& Button::GetName() const {
		static const std::string name("Button");
		return name;
	}

	void Button::HandleStateChange(State old_state) {

		Bin::HandleStateChange(old_state);

		draw();
	}
}