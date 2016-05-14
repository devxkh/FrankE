#ifndef __WIDGET_HPP
#define __WIDGET_HPP

#include <Ogre/OgreMain/include/OgreVector2.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreMemoryAllocatedObject.h>
#include <XEUI/Object.hpp>
#include <XERenderer/GUI/WRectangle.hpp>
#include <SFML/Window/Event.hpp>

#include <cstdint>

namespace XE {

	class WRectangle;
	class WLayer;
	class UIPanel;

	class Widget : public Object, public std::enable_shared_from_this < Widget >
	{
	public:
		typedef std::shared_ptr<Widget> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const Widget> PtrConst; //!< Shared pointer.
	//	typedef std::vector<Widget::Ptr> WidgetsList;

		Widget(WLayer* parentLayer, const std::string& name);
		~Widget();

		/** Widget state.
		*/
		enum class State : std::uint8_t {
			NORMAL = 0, /*!< Normal. */
			ACTIVE, /*!< Active, e.g. when a button is pressed. */
			PRELIGHT, /*!< Prelight, e.g. when the mouse moves over a widget. */
			SELECTED, /*!< Selected, e.g. when a list item in a list is selected. */
			INSENSITIVE /*!< Insensitive, disabled widget. */
		};


		virtual Ogre::Vector2& getSize() { return m_size; }
		virtual Ogre::Vector3& getPosition() { return  m_pos; }

		virtual void setPosition(const Ogre::Vector3& pos);


		virtual void destroy();

		bool isDestroying() { return m_destroy; }
		bool isEnabled() { return m_enabled; }


		void setID(Ogre::uint16 id) { mID = id; }
		void setTabIdx(Ogre::uint16 id) { mTabIdx = id; }

		Ogre::uint16 getTabIdx() { return mTabIdx; }
		Ogre::uint16 getID() { return mID; }
		Ogre::String& getName() { return mName; }
	

		virtual void SetStyle(const char* menuElement, const  char* menuStyle) = 0;
		virtual void pointSelectStart(const Ogre::Vector2& point) = 0;
		virtual void pointSelectEnd(const Ogre::Vector2& point) = 0;

		virtual void parentResized() = 0;

		/** \brief Tests if the element isOver by something at the position pos
		*/
		virtual bool isOver(const Ogre::Vector2& pos) = 0;
		//	virtual void setStyle(ElementStyle* style, bool  resizedOnly) = 0;

		/** \brief Define the position of the element
		*/
		virtual void setPosition(int left, int top) = 0;

		/** \brief Define the size of the element
		*/
		virtual void setSize(int width, int height) = 0;

		/** \brief Inject the time and the mouse position
		*/
		virtual void injectTimeAndMousePosition(double time, const Ogre::Vector2& pos) = 0;


		/** \brief Highlight this element
		*/
		virtual void highlight() = 0;



		UIPanel* getPanelContainer() { return mPanelContainer; }
		//Container* getParentContainer() { return mParentContainer; }
		/** \brief Get if the element is overed
		*/
		bool getOvered();

		/** \brief Get if the element has the focus
		*/
		bool getFocus();


		/** \brief Set if the element has the focus
		*/
		void setFocus(bool hasFocus);

		/** \brief Set if the element should be overed
		*/
		void setOvered(bool overed);

		/** \brief Reset the state of the element
		*/
		virtual void resetState();

		virtual void selectOveredItem() { }
		virtual bool makeNextItemOver() { return false; }
		virtual	bool makePrevItemOver() { return false; }

		/** Set the focused widget.
		* @param widget Focused widget.
		*/
		static void GrabFocus(Ptr widget);

		/** Update.
		* Update the widget's state, i.e. invalidate graphics, process animations
		* etc.
		* @param seconds Elapsed time in seconds.
		*/
		void Update(float seconds);

		/** Invalidate widget.
		* When a widget is about to invalidate it will recreate itself in a
		* graphical manner. This happens automatically when code detects the
		* visual representation needs to be regenerated, so you normally don't
		* have to call it yourself.
		*
		* Implement InvalidateImpl() for your own code.
		*/
		void Invalidate() const;

		/** Set parent widget.
		* Note that the parent must be a subclass of sfg::Container. You mostly
		* don't want to call this method directly.
		* @param parent Parent.
		*/
		void SetParent(Widget::Ptr parent);

		/** Get parent.
		* @return Parent.
		*/
		std::shared_ptr<UIPanel> GetParent();

		/** Get parent.
		* @return Parent.
		*/
		std::shared_ptr<const UIPanel> GetParent() const;

		/** Set widget's state.
		* @param state State.
		*/
		void SetState(State state);

		/** Refresh.
		* Invalidate the widget and request resize.
		*/
		virtual void Refresh();

		/** Get widget's state.
		* @return State.
		*/
		State GetState() const;

		/** Handle SFML event.
		* Handle an SFML event and fire proper signals. Normally reimplemented by
		* containers only.
		* @param event SFML event.
		*/
		virtual void HandleEvent(const sf::Event& event);


		/** Handle focus change.
		* @param focused_widget Widget currently being focused.
		*/
		virtual void HandleFocusChange(Widget::Ptr focused_widget);


		/** Handle update.
		*/
		virtual void HandleUpdate(float seconds);


		/** Get allocation (position and size).
		* @return Allocation.
		*/
		const Ogre::FloatRect& GetAllocation() const;


		/** Check if a widget has focus.
		* @param widget Checked widget.
		* @return true if widget has focus.
		*/
		static bool HasFocus(PtrConst widget);


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

	protected:

		/** Invalidate implementation (redraw internally).
		* Gets called whenever the widget needs to be redrawn, e.g. due to a call
		* to Invalidate().
		* @return Pointer to std::unique_ptr<RenderQueue> -- ownership is taken by caller.
		*/
		virtual void InvalidateImpl() const;

		bool mHasFocus;
		bool mOvered;

		Ogre::String mName;
		Ogre::uint16 mTabIdx;
		Ogre::uint16 mID;
		UIPanel* mPanelContainer;
		//  Container* mParentContainer; //!< \brief Pointer to the layer that created this element

		/** \brief Internal use to get the gui panel colors
		*/
		//PanelColors* getColors();
		//ElementStyle* getStyle(StyleType type);

		/** \brief Internal Use. Actualize the design of the element depending of its state.
		*/
		virtual void _actualize() = 0;


	private:
		struct ClassId {
			std::string id;
			std::string class_;
		};

		static void SetActiveWidget(Ptr widget);
		static bool IsActiveWidget(PtrConst widget);

		std::weak_ptr<UIPanel> m_parent;
		static std::weak_ptr<Widget> m_focus_widget;
		static std::weak_ptr<Widget> m_active_widget;
		static std::weak_ptr<Widget> m_modal_widget;

		std::unique_ptr<ClassId> m_class_id;

		Ogre::FloatRect m_allocation;
		Ogre::Vector2 m_size;
		Ogre::Vector3 m_pos;
		bool m_enabled;
		bool m_visible;
		bool m_hovered;
		WRectangle* m_mousePointer;
		WRectangle* m_background;
		WLayer* m_layer;
		bool m_destroy;
		State m_state;
		
		mutable bool m_invalidated;
		mutable bool m_parent_notified;

	};



} // namespace XE

#endif // __WIDGET_HPP