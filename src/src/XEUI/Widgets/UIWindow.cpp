#include <XEUI/Widgets/UIWindow.hpp>
//#include <SFGUI/Context.hpp>
//#include <SFGUI/RenderQueue.hpp>
//#include <SFGUI/Engine.hpp>

#include <XERenderer/GUI/WRectangle.hpp>
#include <XERenderer/GUI/WCaption.hpp>


#include <SDL.h>

#include <limits>

namespace XE {

	// Signals.
	Signal::SignalID UIWindow::OnCloseButton = 0;

	UIWindow::UIWindow(WLayer& parentLayer, char style, Uint16 fontId) :
		m_style(style),
		m_dragging(false),
		m_resizing(false)
	{
		m_shapesContainer.shapes.emplace_back(std::move(std::unique_ptr<WCaption>(new WCaption(parentLayer, fontId))));
		m_label = static_cast<WCaption*>(m_shapesContainer.shapes.back().get());
		m_shapesContainer.shapes.emplace_back(std::move(std::unique_ptr<WRectangle>(new WRectangle(parentLayer, 0, 0, 0, 0))));
		m_rectangle = static_cast<WRectangle*>(m_shapesContainer.shapes.back().get());


	}

	UIWindow::Ptr UIWindow::Create(WLayer& parentLayer, char style, Uint16 fontId) {
		UIWindow::Ptr window(new UIWindow(parentLayer, style, fontId));

		return window;
	}

	void UIWindow::draw()  {
		/*if (GetChild()) {
			GetChild()->SetAllocation(GetClientRect());
		}*/

	//	return Context::Get().GetEngine().CreateUIWindowDrawable(std::dynamic_pointer_cast<const UIWindow>(shared_from_this()));
	}

	void UIWindow::SetTitle(const sf::String& title) {
		m_title = title;
	//	Invalidate();
	}

	const sf::String& UIWindow::GetTitle() const {
		return m_title;
	}

	SDL_Rect UIWindow::GetClientRect() const {
		SDL_Rect clientrect { 0, 0, size.x, size.y };
		float border_width(0); // (Context::Get().GetEngine().GetProperty<float>("BorderWidth", shared_from_this()));
		float gap(0); // (Context::Get().GetEngine().GetProperty<float>("Gap", shared_from_this()));

		clientrect.x += border_width + gap;
		clientrect.y += border_width + gap;
		clientrect.w -= 2 * border_width + 2 * gap;
		clientrect.h -= 2 * border_width + 2 * gap;

		/*if (HasStyle(TITLEBAR)) {
			unsigned int title_font_size(Context::Get().GetEngine().GetProperty<unsigned int>("FontSize", shared_from_this()));
			const sf::Font& title_font(*Context::Get().GetEngine().GetResourceManager().GetFont(Context::Get().GetEngine().GetProperty<std::string>("FontName", shared_from_this())));
			float title_height(
				Context::Get().GetEngine().GetFontLineHeight(title_font, title_font_size) +
				2 * Context::Get().GetEngine().GetProperty<float>("TitlePadding", shared_from_this())
				);

			clientrect.top += title_height;
			clientrect.height -= title_height;
		}*/

		return clientrect;
	}

	void UIWindow::SetStyle(char style) {
		m_style = style;

		// Make sure dragging and resizing operations are cancelled.
		m_dragging = false;
		m_resizing = false;

		/*RequestResize();
		Invalidate();*/

		/*if (GetChild()) {
			GetChild()->SetAllocation(GetClientRect());
		}*/
	}

	char UIWindow::GetStyle() const {
		return m_style;
	}

	bool UIWindow::HasStyle(Style style) const {
		return (m_style & style) == style;
	}

	//sf::Vector2f UIWindow::CalculateRequisition() {
	//	float visual_border_width(0); // (Context::Get().GetEngine().GetProperty<float>("BorderWidth", shared_from_this()));
	//	float gap(0);// Context::Get().GetEngine().GetProperty<float>("Gap", shared_from_this()));
	//	sf::Vector2f requisition(2 * visual_border_width + 2 * gap, 2 * visual_border_width + 2 * gap);

	//	/*if (HasStyle(TITLEBAR)) {
	//		unsigned int title_font_size(Context::Get().GetEngine().GetProperty<unsigned int>("FontSize", shared_from_this()));
	//		const sf::Font& title_font(*Context::Get().GetEngine().GetResourceManager().GetFont(Context::Get().GetEngine().GetProperty<std::string>("FontName", shared_from_this())));
	//		float title_height(
	//			Context::Get().GetEngine().GetFontLineHeight(title_font, title_font_size) +
	//			2 * Context::Get().GetEngine().GetProperty<float>("TitlePadding", shared_from_this())
	//			);

	//		requisition.y += title_height;
	//	}*/

	//	/*if (GetChild()) {
	//		requisition += GetChild()->GetRequisition();
	//	}
	//	else {*/
	//		requisition.x = std::max(50.f, requisition.x);
	//		requisition.y = std::max(50.f, requisition.y * 2.f);
	//	//}

	//	return requisition;
	//}

	const std::string& UIWindow::GetName() const {
		static const std::string name("UIWindow");
		return name;
	}

	void UIWindow::HandleMouseButtonEvent(bool press, int x, int y) {
		//if (button != sf::Mouse::Left) {
		//	return;
		//}

		if (!press) {
			m_dragging = false;
			m_resizing = false;
			return;
		}

		//unsigned int title_font_size(Context::Get().GetEngine().GetProperty<unsigned int>("FontSize", shared_from_this()));
	//	const sf::Font& title_font(*Context::Get().GetEngine().GetResourceManager().GetFont(Context::Get().GetEngine().GetProperty<std::string>("FontName", shared_from_this())));
		float title_height(0);
		/*	Context::Get().GetEngine().GetFontLineHeight(title_font, title_font_size) +
			2 * Context::Get().GetEngine().GetProperty<float>("TitlePadding", shared_from_this())
			);*/

		// Check for mouse being inside the title area.
		SDL_Rect area{
			Widget::getPosition().x,
			Widget::getPosition().y,
			size.x,
			title_height
		};

		SDL_Point point{ x, y };

		if (SDL_PointInRect(&point, &area)) {
			if (HasStyle(TITLEBAR) && !m_dragging) {
				if (HasStyle(CLOSE)) {
					/*auto close_height(Context::Get().GetEngine().GetProperty<float>("CloseHeight", shared_from_this()));

					auto button_margin = (title_height - close_height) / 2.f;

					auto close_rect = sf::FloatRect(
						GetAllocation().left + GetAllocation().width - button_margin - close_height,
						GetAllocation().top + button_margin,
						close_height,
						close_height
						);

					if (close_rect.contains(static_cast<float>(x), static_cast<float>(y))) {
						GetSignals().Emit(OnCloseButton);
						return;
					}*/
				}

				m_dragging = true;
				m_resizing = false;

				m_drag_offset = sf::Vector2f(
					static_cast<float>(x) - Widget::getPosition().x,
					static_cast<float>(y) - Widget::getPosition().y
					);
			}
		}
		else {
			float handle_size(0);// Context::Get().GetEngine().GetProperty<float>("HandleSize", shared_from_this()));

			area.x = Widget::getPosition().x + size.x - handle_size;
			area.y = Widget::getPosition().y + size.x - handle_size;
			area.w = handle_size;
			area.h = handle_size;

			if (SDL_PointInRect(&point, &area)) {
				m_dragging = false;
				m_resizing = true;

				m_drag_offset = sf::Vector2f(
					handle_size - static_cast<float>(x) + Widget::getPosition().x + size.x - handle_size,
					handle_size - static_cast<float>(y) + Widget::getPosition().y + size.y - handle_size
					);
			}
		}

	}


	void UIWindow::setPosition(const sf::Vector2f& pos) {

		Widget::setPosition(pos);

		GetChild()->setPosition(pos);
	}

	void UIWindow::HandleMouseMoveEvent(int x, int y) {
		if ((x == std::numeric_limits<int>::min()) || (y == std::numeric_limits<int>::min())) {
			return;
		}

		if (m_dragging) {
			Widget::setPosition(sf::Vector2f(static_cast<float>(x) - m_drag_offset.x, static_cast<float>(y) - m_drag_offset.y));
		}
		else if (m_resizing && (GetStyle() & RESIZE) == RESIZE) {
			/*size = (
				sf::FloatRect(
					GetAllocation().left,
					GetAllocation().top,
					std::max(GetRequisition().x, static_cast<float>(x) + m_drag_offset.x - GetAllocation().left),
					std::max(GetRequisition().y, static_cast<float>(y) + m_drag_offset.y - GetAllocation().top)
					)
				);*/
		}
	}

	//bool UIWindow::HandleAdd(Widget::Ptr child) {
	//	if (!Bin::HandleAdd(child)) {
	//		return false;
	//	}

	//	// Reset allocation so the window will be as large as required.
	//	SetAllocation(sf::FloatRect(GetAllocation().left, GetAllocation().top, 1.f, 1.f));
	//	RequestResize();

	//	return true;
	//}

}