#include <XEUI/widgets/Button.hpp>

#include <XEUI/Container.hpp>


//#include <SFGUI/Button.hpp>
//#include <SFGUI/Context.hpp>
//#include <SFGUI/Engine.hpp>
//#include <SFGUI/Image.hpp>
//#include <SFGUI/RenderQueue.hpp>

namespace XE {

	Button::Button(WLayer& parentLayer) :
		 m_label(parentLayer)
		, m_rectangle(parentLayer, 0, 0, 0, 0)
	{
		//SetAlignment(sf::Vector2f(.5f, .5f));
		//Invalidate();

		m_rectangle.setBackground(Ogre::ColourValue::Green);
	}

	Button::~Button()
	{

	}

	Button::Ptr Button::Create(WLayer& parentLayer, const sf::String& label) {
		auto ptr = Ptr(new Button(parentLayer));
		ptr->SetLabel(label);
		return ptr;
	}

	void Button::draw() {
		
		//sf::FloatRect req(GetAllocation());
		//sf::Vector2f parentPosition(GetParent()->GetAllocation());

		sf::Vector2f glyphPosition(Widget::getPosition().x, Widget::getPosition().y - 10);

		m_label.setPosition(glyphPosition); // sf::Vector2f(parentAllocation.left + position.x, parentAllocation.top + position.y));
		m_label.setSize(size.x, size.y);

		m_rectangle.setPosition(Widget::getPosition()); // sf::Vector2f(parentAllocation.left + position.x, parentAllocation.top + position.y));
		m_rectangle.setSize(sf::Vector2f(size.x, size.y));

		if (GetState() == State::PRELIGHT)
			m_rectangle.setBackgroundImage("item_unknown.png");
		else if (GetState() == State::ACTIVE)
			m_rectangle.setBackgroundImage("messagebox_bg.png");
		else
			m_rectangle.setBackgroundImage("itembox.png");

		
		if (GetState() == State::PRELIGHT)
			m_rectangle.setBackground(Ogre::ColourValue::Red);
		else if (GetState() == State::ACTIVE)
			m_rectangle.setBackground(Ogre::ColourValue::Black);
		else
			m_rectangle.setBackground(Ogre::ColourValue::Green);
		
		
		//m_label.setText(GetLabel());

		//todo
		//return Context::Get().GetEngine().CreateButtonDrawable(std::dynamic_pointer_cast<const Button>(shared_from_this()));
	}

	void Button::SetLabel(const sf::String& label) {
		m_label.setText(label);

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