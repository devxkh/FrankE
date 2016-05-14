//
//#ifndef __UIPANEL_HPP
//#define __UIPANEL_HPP
//
//#include <XEUI/Container.hpp>
//#include <XEUI/Widget.hpp>
//#include <XEUI/Misc.hpp>
//#include <XEUI/Desktop.hpp>
//#include <XERenderer/GUI/WRectangle.hpp>
//
//#include <vector>
//
//namespace XE {
//
//	class Menu;
//	//class Button;
//	//class Listbox;
//	//class Combobox;
//	//class Caption;
//	//class Navigation;
//	//class OgreConsole;
//	class UIManager;
//	class WLayer;
//
//	//typedef std::vector<Widget*> WidgetVector;
//
//	/*! class. UIPanel  ->> SFGUI Fixed equivalent
//		desc.
//		A container contains a layer and the gui object that created it
//		*/
//	class UIPanel : public Container, public Misc
//	{
//	public:
//		//	typedef std::vector<Widget::Ptr> WidgetsList;
//
//		UIPanel( WLayer&  layer, const Ogre::uint16& grp = 0);
//
//		virtual ~UIPanel();
//
//		typedef std::shared_ptr<UIPanel> Ptr; //!< Shared pointer.
//		typedef std::shared_ptr<const UIPanel> PtrConst; //!< Shared pointer.
//
//		
//		static Ptr Create( WLayer& layer);
//
//		virtual const std::string& GetName() const override;
//
//		void setDesktop(std::shared_ptr<Desktop> desktopPtr);
//
//		void SetStyle(const char* menuElement, const  char* menuStyle);
//
//		/** Add a widget to this fixed at given position.
//		* @param widget Widget to add.
//		* @param position Position to place the widget at.
//		*/
//		void Put(Widget::Ptr widget, const sf::Vector2f& position);
//
//		/** Move a child widget to the given position.
//		* @param widget Widget to move.
//		* @param position Position to move the widget to.
//		*/
//		void Move(Widget::Ptr widget, const sf::Vector2f& position);
//
//		/** Set label.
//		* @param label Label.
//		*/
//		void SetLabel(const sf::String& label);
//
//		/** Get label.
//		* @return Label.
//		*/
//		const sf::String& GetLabel() const;
//
//		void HandleSizeChange();
//
//		void HandleAbsolutePositionChange();
//		
//		void HandleAlignmentChange(const sf::Vector2f& old_alignment);
//		
//		/** Handle widget (relative) position changes.
//		*/
//		void HandlePositionChange();
//
//		void HandleUpdate(float seconds);
//
//		/*void pointSelectStart( const Ogre::Vector2& point );
//
//		void pointSelectEnd( const Ogre::Vector2& point );*/
//
//		/** \brief Inject time to have animations with panel elements, such as
//		a flash on and off of a cursor in Textzones
//		*/
//		//    void injectTime( double time );
//		//
//		//    /** \brief UnOver all elements.
//		//    */
//		//    void unOverAllElements();
//		//
//		//    /** \brief Hide the mouse pointer of this panel
//		//    */
//		//    void hideInternalMousePointer();
//		//
//		//    /** \brief Show the mouse pointer of this panel
//		//    */
//		//    void showInternalMousePointer();
//		//
//		////	PanelElement* getItem ( Ogre::uint16 id );
//		//
//		//	 /** \brief Give coordinates of the external mouse to this screen
//		//	 */
//		//	 virtual bool injectMouseMoved(const  Ogre::Real& x, const  Ogre::Real& y) = 0;
//		//
//		//	 /** \brief Send a ray from a part of the screen to this panel to
//		//	 actualize the internal mouse position on the panel.
//		//	 Return if the ray intersects with the panel.
//		//	 */
//		//	 virtual bool injectMouseMoved(const Ogre::Ray& ray) = 0;
//		//	 virtual void parentResized() = 0;
//		//
//		//	 Widget* getItem(const Ogre::String& name);
//
//		Ogre::uint16& getGrp() { return mGroup; }
//		//Ogre::String getName() { return mName; }
//		//WLayer& getLayer(sf::Uint16 id){ return m_Layer; }
//		UIManager* getUIManager() { return mXEUI; }
//
//		void selectOveredItem();
//		bool makeNextItemOver();
//		bool makePrevItemOver();
//
//		//virtual void update(const Ogre::Real& timeElapsed) = 0;
//
//		//virtual const std::string& GetName() const override;
//
//	protected:
//		void draw();
//
//
//		/** Get requisition.
//		* @return Requisition.
//		*/
//	//	sf::Vector2f CalculateRequisition() override;
//
//
//		//WidgetsList m_children;
//
//		//   Ogre::Vector2 mInternalMousePos; //!< \brief The Internal position of the mouse in the panel
//
//		//	WidgetVector mWidgets;
//		//Widget* mFocusedPanelElement; //!< \brief The element that actually have the focus
//
//	private:
//		Desktop::Ptr m_Desktop;
//		WLayer& m_layer;
//
//		typedef std::map<Widget::Ptr, sf::Vector2f> ChildrenPositionMap;
//
//		bool HandleAdd(Widget::Ptr child);
//		void HandleRemove(Widget::Ptr child);
//
//		ChildrenPositionMap m_children_position_map;
//		
//		//initialization order!
//		WRectangle m_DebugRectangle;
//	//	GUIRenderer& m_guiRenderer;
//
//		sf::String m_label;
//
//	
//		UIManager* mXEUI; 
//
//		Ogre::String mCurrentItemName;
//		Ogre::uint16 mGroup;		//Panelgroup
//		//	Ogre::String mName;
//	};
//
//} // namespace XE
//
//#endif // __UIPANEL_HPP