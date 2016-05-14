#ifndef UINavigation_HPP
#define UINavigation_HPP

//#include <XEUI/PanelElementCallback.hpp>
#include <XEUI/Widget.hpp>

namespace XE {


	class UIPanel;
	class NavItem;
	class UISerializer;
	class ScreenPanel;

	typedef Ogre::vector<NavItem*>::type NavItemVector;
	typedef Ogre::vector<NavItem*>::iterator NavItemIt;
	/*! class. Navigation
		desc.
		A Navigation which allows the user to navigate threw panels
		*/
	class Navigation : public Widget
	{
	public:
		/** \brief Use Panel::makeMenu
		*/
		Navigation(const Ogre::String& name,
			Ogre::Real x,
			Ogre::Real y,
			size_t width,
			size_t height,
			unsigned int nbDisplayedElements,
			UIPanel* parentContainer);

		/** \brief Use Panel::deleteMenu
		*/
		~Navigation();

		NavItem* Navigation::addItem(const Ogre::String& name,
			Ogre::uint16 idx,
			const Ogre::String text);

		NavItem* addItem(NavItem* item);
		NavItem* getItemPIdx(const Ogre::uint16& idx);
		void selectPIdx(const Ogre::uint16& idx);
		//void injectKeyPressed(const OIS::KeyEvent& evt);

		//void injectKeyReleased(const OIS::KeyEvent& evt);

		//void injectKeys(std::vector<OIS::KeyCode>& keys);
		bool makePrevItemOver();
		bool makeNextItemOver();
		void pointSelectStart(const Ogre::Vector2& point);

		void pointSelectEnd(const Ogre::Vector2& point);

		bool isOver(const Ogre::Vector2& pos);

		void setPosition(int left, int top);
		//Ogre::Vector2 getPosition();
		void setSize(int width, int height);

		void pointSelection(const Ogre::Vector2& point);

		void parentResized();
		//	void setStyle(ElementStyle* style, bool  resizedOnly);

		void injectTimeAndMousePosition(double time, const Ogre::Vector2& pos);

		/** \brief Define the callback when a value has changed
	  */
		//   template<typename T>
		//   void setValueChangedCallback(T* object, bool(T::*method)(PanelElement*))
		//   {
		//       changeCallback(OGRE_NEW  MemberFunction<T>(object, method));
		//   }

		//void setValueChangedCallback( FunctorBase* memberFunc)
		//   {
		//       changeCallback(memberFunc);
		//   }

		/** \brief Return the value of the combobox
		*/
		// Ogre::String getValue();
		NavItem* getItemPID(Ogre::uint16 id);
		NavItem* getNavItem(const Ogre::String& name);

		void selectOveredItem();
		NavItem* getSelectedItem();
		/** \brief Set the current value of this combobox. If the element
		isn't found, nothing is changed.
		*/
		//   void setCurrentValue(String& itemName);

		void highlight();

		//void removeActualPanel();
		//void setActualPanel( UIPanel* uiPanel );
		//UIPanel* getActualPanel() { return mActualPanel; }
		/*void setLastStateID( const Ogre::uint16& id ) { mLastStateID = id; }
		const Ogre::uint16& getLastStateID() { return mLastStateID; }*/

	protected:

		//

		/** \brief The actual overed element.
		If it's >= 0, it's a selector value element, else it's a speial case.
		See implementation : can be NO_ELEMENT, PREVIOUS_ELEMENT_BUTTON or NEXT_ELEMENT_BUTTON
		*/
		Ogre::int32 mOveredIdx;

		unsigned int mNumTopVisibleElement; //!< \brief Number of the top element that is shown

		unsigned int mMaxNumberOfVisibleNavItems; //!< \brief Number of elements that can be seen in the selector

		Ogre::uint16 mSelectedIdx; //!< \brief The actual selected element

		NavItemIt mNavItemIt;
		NavItemVector mNavItems; //!< \brief Contains the displayed caption of the combobox

		void _actualize();

		//Panel Navigation

		//   UIPanel* mActualPanel; // The panel that is actually focused
		//UIPanel* mPrevPanel; //last panel in memory
		//UIPanel* mNextPanel; //prebuffer of the next panel
	};


} //namespace XE

#endif // UINavigation_HPP