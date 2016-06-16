#include <XEUI/Widgets/ProgressBar.hpp>
//#include <SFGUI/Context.hpp>
//#include <SFGUI/RenderQueue.hpp>
//#include <SFGUI/Engine.hpp>

#include <ThirdParty/sfml/include/sfml/Graphics/Rect.hpp>
#include <XEUI/Container.hpp>

namespace XE {

	ProgressBar::ProgressBar(WLayer& parentLayer, Orientation orientation) :
		m_fraction(0.f),
		m_orientation(orientation)
		, m_pane(parentLayer, 0, 0, 0, 0)
		, m_barPane(parentLayer, 0, 0, 0, 0)
	{

		m_pane.setBackground(Ogre::ColourValue::Green); //debug
		m_barPane.setBackground(Ogre::ColourValue::Black); //debug
		m_barPane.setBackgroundImage("itembox.png");
	}

	ProgressBar::Ptr ProgressBar::Create(WLayer& parentLayer, Orientation orientation) {
		return Ptr(new ProgressBar(parentLayer, orientation));
	}

	void ProgressBar::SetFraction(float fraction) {
		m_fraction = std::max(0.f, std::min(1.f, fraction));
		draw();
	}

	float ProgressBar::GetFraction() const {
		return m_fraction;
	}

	const std::string& ProgressBar::GetName() const {
		static const std::string name("ProgressBar");
		return name;
	}

	sf::Vector2f ProgressBar::CalculateRequisition() {
		if (m_orientation == Orientation::HORIZONTAL) {
			return sf::Vector2f(20.f, 10.f);
		}

		return sf::Vector2f(10.f, 20.f);
	}

	void ProgressBar::draw() {

		// Pane.
		/*sf::FloatRect req(GetAllocation());
		sf::FloatRect parentAllocation(GetParent()->GetAllocation());*/

		m_pane.setPosition(Widget::getPosition());//  sf::Vector2f(parentAllocation.left + req.left, parentAllocation.top + req.top));
		m_pane.setSize(sf::Vector2f(size.x, size.y));// .width, req.height));

		//return Context::Get().GetEngine().CreateProgressBarDrawable(std::dynamic_pointer_cast<const ProgressBar>(shared_from_this()));
		float bar_border_width = 0;
		float border_width = 0;

		if (GetFraction() > 0.f) {
			sf::FloatRect bar_rect;

			if (GetOrientation() == ProgressBar::Orientation::HORIZONTAL) {
				float frac_width(std::max(2.f * bar_border_width, size.x * GetFraction()));

				bar_rect = sf::FloatRect{
					border_width,
					border_width,
					std::max(0.f, frac_width - 2.f * border_width),
					std::max(0.f, size.y - 2.f * border_width)
				};
			}
			else {
				float frac_height(std::max(2.f * bar_border_width, size.y * GetFraction()));

				bar_rect = sf::FloatRect{
					border_width,
					std::max(0.f, size.y - frac_height + border_width),
					std::max(0.f, size.x - 2.f * border_width),
					std::max(0.f, frac_height - 2.f * border_width)
				};
			}

			// Bar Pane.
			m_barPane.setPosition(sf::Vector2f(Widget::getPosition().x + bar_rect.left, Widget::getPosition().y + bar_rect.top));
			m_barPane.setSize(sf::Vector2f(bar_rect.width, bar_rect.height));
		}
	}

	void ProgressBar::SetOrientation(Orientation orientation) {
		m_orientation = orientation;
	//	RequestResize();
	}

	ProgressBar::Orientation ProgressBar::GetOrientation() const {
		return static_cast<Orientation>(m_orientation);
	}

}