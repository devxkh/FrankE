#ifndef _UI_WINDOW_HPP
#define _UI_WINDOW_HPP

#include <XESystem/SystemConfig.hpp>
#include <XEUI/Bin.hpp>

#include <SFML/System/String.hpp>
#include <memory>

struct SDL_Rect;

namespace XE {
		
	class WRectangle;
	class WCaption;

	/** UIWindow.
	*/
	class XE_API UIWindow : public Bin {
	public:
		typedef std::shared_ptr<UIWindow> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const UIWindow> PtrConst; //!< Shared pointer.

		enum Style : char {
			NO_STYLE = 0, //!< Transparent window.
			TITLEBAR = 1 << 0, //!< Titlebar.
			BACKGROUND = 1 << 1, //!< Background.
			RESIZE = 1 << 2, //!< Resizable.
			SHADOW = 1 << 3, //!< Display Shadow.
			CLOSE = 1 << 4, //!< Display close button.
			TOPLEVEL = TITLEBAR | BACKGROUND | RESIZE //!< Toplevel window.
		};

		/** Create window.
		* @param style Style the UIWindow should have. Defaults to TopLevel.
		*/
		static Ptr Create(WLayer& parentLayer, char style = Style::TOPLEVEL, Uint16 fontId = 14);

		const std::string& GetName() const override;

		/** Set window title.
		* @param title Title.
		*/
		void SetTitle(const sf::String& title);

		/** Get window title.
		* @return Title.
		*/
		const sf::String& GetTitle() const;

		/** Get client area.
		* @return Rect.
		*/
		SDL_Rect GetClientRect() const;

		/** Set window style.
		* Can be a combination of UIWindow::Style values.
		* @param style New style.
		*/
		void SetStyle(char style);

		/** Get window style.
		* @return UIWindow style.
		*/
		char GetStyle() const;

		/** Check if the window has a specific style.
		* @param style Style to check.
		* @return true when window has desired style.
		*/
		bool HasStyle(Style style) const;

		// Signals.
		static Signal::SignalID OnCloseButton; //!< Fired when close button is pressed.


		virtual void setPosition(const sf::Vector2f& pos) override;

	protected:
		/** Constructor.
		* @param style UIWindow style.
		*/
		UIWindow(WLayer& parentLayer, char style, Uint16 fontId);

		void draw() override;

		//sf::Vector2f CalculateRequisition() override;

	private:
	//	void HandleSizeChange() override;
		void HandleMouseButtonEvent(bool press, int x, int y) override;
		void HandleMouseMoveEvent(int x, int y) override;
	//	bool HandleAdd(Widget::Ptr child) override;

		sf::Vector2f m_drag_offset;

		sf::String m_title;
		char m_style;

		bool m_dragging;
		bool m_resizing;


		WRectangle* m_rectangle;
		WCaption* m_label;
	};

} //ns XE

#endif