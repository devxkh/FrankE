#pragma once


#include <ThirdParty/sfml/include/sfml/System/Vector2.hpp>

#include <XERenderer/GUI/RenderableShape.hpp>

#include <XEUI/Object.hpp>
#include <memory>

#include <SDL.h>
#include <map>
#include <string>
#include <cstdint>
#include <vector>

namespace XE {

class Container;



/** Base class for widgets.
 */
class Widget : public Object, public std::enable_shared_from_this<Widget> {
	public:
		typedef std::shared_ptr<Widget> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const Widget> PtrConst; //!< Shared pointer.
		typedef std::vector<Widget::Ptr> WidgetsList;

		/** Widget state.
		 */
		enum class State : std::uint8_t {
			NORMAL = 0, /*!< Normal. */
			ACTIVE, /*!< Active, e.g. when a button is pressed. */
			PRELIGHT, /*!< Prelight, e.g. when the mouse moves over a widget. */
			SELECTED, /*!< Selected, e.g. when a list item in a list is selected. */
			INSENSITIVE /*!< Insensitive, disabled widget. */
		};

		/** Destructor.
		 */
		virtual ~Widget();

		/** Check if widget is locally visible, i.e. is rendered when allowed to.
		 * This DOES NOT take into account the global visibility of it's parents.
		 * @return true when locally visible.
		 */
		bool IsLocallyVisible() const;

		/** Check if widget is globaly visible, i.e. is currently rendered.
		 * This takes into account the global visibility of it's parents.
		 * @return true when globally visible.
		 */
		bool IsGloballyVisible() const;

		/** Show (or hide) widget.
		 * @param show true to show, false to hide.
		 */
		void Show( bool show = true );

		/** Get name of widget.
		 * The name of a widget is a descriptive name of the widget itself. E.g.
		 * "CheckButton" for the CheckButton widget. The name is mainly used by the
		 * style parser.
		 * @return Name.
		 */
		virtual const std::string& GetName() const = 0;

		/** Grab focus.
		 */
		void GrabFocus();

		/** Check if widget has focus.
		 * @return true if widget has focus.
		 */
		bool HasFocus() const;

		virtual void ParentPositionChanged();

		/** Set this widget to be active.
		 * Only one widget at a time can be active. This often happens when a
		 * widget is gaining focus. You normally don't want to call this yourself.
		 */
		void SetActiveWidget();

		/** Check if widget is active widget.
		 * @return true if widget is active widget.
		 */
		bool IsActiveWidget() const;
		
		/** Set parent widget.
		 * Note that the parent must be a subclass of sfg::Container. You mostly
		 * don't want to call this method directly.
		 * @param parent Parent.
		 */
		void SetParent( Widget::Ptr parent );

		/** Get parent.
		 * @return Parent.
		 */
		std::shared_ptr<Container> GetParent();

		/** Get parent.
		 * @return Parent.
		 */
		std::shared_ptr<const Container> GetParent() const;

		/** Set widget's state.
		 * @param state State.
		 */
		void SetState( State state );

		/** Get widget's state.
		 * @return State.
		 */
		State GetState() const;

		virtual void onPointMoved( const float& x, const float& y);
		virtual void onPointDown( const float& x, const float& y);
		virtual void onPointUp( const float& x, const float& y);
		virtual void onKeyEvent(const  SDL_KeyboardEvent& key);
		virtual void onTextEvent(const SDL_TextInputEvent& text);
		virtual void onNav(NavAction navAction);
		/** Handle global visibility changes.
		 */
		virtual void HandleGlobalVisibilityChange();

		virtual void Update(float seconds);


		virtual void HandleNavEvent(NavAction navAction);

		/** Update position of drawable.
		 */
		virtual void UpdateDrawablePosition();

		/** Set ID.
		 * Mostly used for identification and by styles (#widget_id).
		 * @param id ID.
		 */
		void SetId( const std::string& id );

		/** Get ID.
		 * @return ID or empty.
		 */
		std::string GetId() const;

		/** Set class.
		 * Mostly used by style (.widget_class).
		 * @param cls Class.
		 */
		void SetClass( const std::string& cls );

		/** Get class.
		 * @return Class or empty.
		 */
		std::string GetClass() const;

		/** Get all widgets with the specified ID.
		 * @param id ID the widget should have.
		 * @return Widget::Ptr of the first found widget with the specified ID or Widget::Ptr() if none found.
		 */
		static Widget::Ptr GetWidgetById( const std::string& id );

		/** Get all widgets with the specified class.
		 * @param class_name Class the widget should have.
		 * @return sfg::Widget::WidgetsList of all found widgets with the specified class. Empty if none found.
		 */
		static WidgetsList GetWidgetsByClass( const std::string& class_name );

		/** Refresh.
		 * Invalidate the widget and request resize.
		 */
		virtual void Refresh();

		/** Refreshes all root widgets, which should refresh all widgets in the hierarchy.
		 */
		static void RefreshAll();

		/** Check if a widget is currently a modal widget.
		 * @return true if a widget is currently a modal widget.
		 */
		static bool HasModal();

		// Signals.
		static Signal::SignalID OnStateChange; //!< Fired when state changed.
		static Signal::SignalID OnGainFocus; //!< Fired when focus gained.
		static Signal::SignalID OnLostFocus; //!< Fired when focus lost.

		static Signal::SignalID OnExpose; //!< Fired when widget is being rendered.

		static Signal::SignalID OnSizeAllocate; //!< Fired when widget's allocation changed.
		static Signal::SignalID OnSizeRequest; //!< Fired when size was requested.

		static Signal::SignalID OnMouseEnter; //!< Fired when mouse entered widget.
		static Signal::SignalID OnMouseLeave; //!< Fired when mouse left widget.
		static Signal::SignalID OnMouseMove; //!< Fired when mouse moved over widget.
		static Signal::SignalID OnMouseLeftPress; //!< Fired when left button pressed.
		static Signal::SignalID OnMouseRightPress; //!< Fired when right button pressed.
		static Signal::SignalID OnMouseLeftRelease; //!< Fired when left button released.
		static Signal::SignalID OnMouseRightRelease; //!< Fired when right button released.

		static Signal::SignalID OnLeftClick; //!< Fired when left button clicked.
		static Signal::SignalID OnRightClick; //!< Fired when right button clicked.

		static Signal::SignalID OnKeyPress; //!< Fired when a key is pressed while State == Active.
		static Signal::SignalID OnKeyRelease; //!< Fired when a key is released while State == Active.
		static Signal::SignalID OnText; //!< Fired when text is entered while State == Active.

		static Signal::SignalID OnNav; //!< Fired on navigation left,right,top,down
		static Signal::SignalID OnNavSelect; //!< Fired on navigation select
		static Signal::SignalID OnNavEnter; //!< Fired on navigation enter

		const sf::Vector2f& getPosition() const;

		virtual void setPosition(const sf::Vector2f& pos);

		sf::Vector2f size;

	protected:
		/** Constructor.
		 */
		Widget();

		/** Invalidate implementation (redraw internally).
		 * Gets called whenever the widget needs to be redrawn, e.g. due to a call
		 * to Invalidate().
		 * @return Pointer to std::unique_ptr<RenderQueue> -- ownership is taken by caller.
		 */
	//	virtual std::unique_ptr<RenderQueue> draw() const;
		virtual void draw() ;


		/** Check if mouse is inside widget.
		 * @return true if mouse is inside.
		 */
		bool IsMouseInWidget() const;

		/** Set whether the mouse is in the widget or not.
		 * @param in_widget true if mouse should be in widget.
		 */
		void SetMouseInWidget( bool in_widget );

		/** Check if the given mouse button is down
		 * @param button Given mouse button. Defaults to check if ANY button is down.
		 * @return true if the given mouse button is down.
		 */
		//bool IsMouseButtonDown( sf::Mouse::Button button = sf::Mouse::ButtonCount ) const;

		///** Set whether the given mouse button is down.
		// * @param button Given mouse button. Defaults to clear button down state for all buttons.
		// */
		//void SetMouseButtonDown( sf::Mouse::Button button = sf::Mouse::ButtonCount );

		// Internal handling methods.

		/** Handle mouse move event.
		 * @param x Mouse X position.
		 * @param y Mouse Y position.
		 */
		virtual void HandleMouseMoveEvent( int x, int y );

		/** Handle mouse button event.
		 * @param button Mouse button.
		 * @param press true if button was pressed, false if released.
		 * @param x Mouse X position.
		 * @param y Mouse Y position.
		 */
		virtual void HandleMouseButtonEvent( bool press, int x, int y );

		/** Handle update.
					 */
		virtual void HandleUpdate(float seconds);

		/** Handle key event.
		 * @param key Key.
		 * @param press true if button was pressed, false if released.
		 */
		virtual void HandleKeyEvent(const SDL_KeyboardEvent& key, bool press );
		
		/** Handle state changes.
		 * The default behaviour is to accept any state change and invalidate the
		 * widget.
		 * @param old_state Old state.
		 */
		virtual void HandleStateChange( State old_state );

		/** Handle text event.
		 * @param character Character.
		 */
		virtual void HandleTextEvent(const char* character );
	

		/** Handle mouse enter.
		 * @param x Mouse X position.
		 * @param y Mouse Y position.
		 */
		virtual void HandleMouseEnter( int x, int y );

		/** Handle mouse leave.
		 * @param x Mouse X position.
		 * @param y Mouse Y position.
		 */
		virtual void HandleMouseLeave( int x, int y );

		/** Handle mouse click.
		 * @param button Button.
		 * @param x Mouse X position.
		 * @param y Mouse Y position.
		 */
		virtual void HandleMouseClick( int x, int y );

		/** Handle focus change.
		 * @param focused_widget Widget currently being focused.
		 */
		virtual void HandleFocusChange( Widget::Ptr focused_widget );

		/** Handle local visibility change.
		 */
		virtual void HandleLocalVisibilityChange();
		
		/** Set the focused widget.
		 * @param widget Focused widget.
		 */
		static void GrabFocus( Ptr widget );

		/** Check if a widget has focus.
		 * @param widget Checked widget.
		 * @return true if widget has focus.
		 */
		static bool HasFocus( PtrConst widget );

		/** Set this widget as the current modal widget.
		 * Consumes all events.
		 */
		void GrabModal();

		/** Unset this widget as the current modal widget.
		 * Restores normal event propagation.
		 */
		void ReleaseModal();

		/** Check if this widget is the modal widget.
		 * @return true if this widget is the modal widget.
		 */
		bool IsModal() const;

		sf::Uint16 tabIdx;


		RenderableShapesContainer m_shapesContainer;

	private:
		struct ClassId {
			std::string id;
			std::string class_;
		};

		bool HandleEvent();

		static void SetActiveWidget( Ptr widget );
		static bool IsActiveWidget( PtrConst widget );

		static const std::vector<Widget*>& GetRootWidgets();

		std::weak_ptr<Container> m_parent;

		static std::weak_ptr<Widget> m_focus_widget;
		static std::weak_ptr<Widget> m_active_widget;
		static std::weak_ptr<Widget> m_modal_widget;

		static std::vector<Widget*> m_root_widgets;

		std::unique_ptr<ClassId> m_class_id;

		sf::Vector2f m_position;
		
		int m_hierarchy_level;
		int m_z_order;
		
		State m_state;
		unsigned char m_mouse_button_down : 6; // 64 buttons, might not be enough for some people
		bool m_mouse_in : 1;
		bool m_visible : 1;

};

}
