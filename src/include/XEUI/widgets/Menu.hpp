#ifndef UIMenu_H
#define UIMenu_H

#include <vector>

//#include <XEGraphics/Gorilla.h>
//#include "UIContainer.h"
//#include <XEUI/PanelElementCallback.hpp>
#include <XERenderer/GUI/WRectangle.hpp>
#include <XEUI/Widget.hpp>
//#include <XEUI/PanelElement.hpp>
//#include "UIButton.h"
//#include "UICaption.h"
//
//#include "UIMemberFunction.h"

namespace XFBType
{
	class Menu;
	class Style;
}

namespace XE {


	class MenuItem;

	typedef Ogre::vector<MenuItem*>::type MenuItemVector;
	typedef Ogre::vector<MenuItem*>::iterator MenuItemIt;

/*! class. Menu
    desc.
        A Menu which allows the user to make one choice.
*/
class Menu : public Widget
{
public:
    /** \brief Use Panel::makeMenu
    */
	Menu(UIPanel* parentPanel, XFBType::Menu* menuElement, XFBType::Style* menuStyle);
    
    /** \brief Use Panel::deleteMenu
    */
    ~Menu();

	UIPanel* getParent();
	MenuItem* addItem(MenuItem* item);
	MenuItem* getItemPID( Ogre::uint16 id );

    //void injectKeyPressed(const OIS::KeyEvent& evt);

    //void injectKeyReleased(const OIS::KeyEvent& evt);

    //void injectKeys(std::vector<OIS::KeyCode>& keys);

    void pointSelectStart(const Ogre::Vector2& point);

    void pointSelectEnd(const Ogre::Vector2& point);

	bool isOver(const Ogre::Vector2& pos);

	void clear() ;

	
	void setSize(int width, int height);

	void parentResized();
//	void setStyle(ElementStyle* style, bool  resizedOnly);

    void pointSelection(const Ogre::Vector2& point);
    
	void injectTimeAndMousePosition(double time, const Ogre::Vector2& pos);

	  /** \brief Define the callback when a value has changed
    */
  //  template<typename T>
  //  void setValueChangedCallback(T* object, bool(T::*method)(PanelElement*))
  //  {
  //      changeCallback(OGRE_NEW  MemberFunction<T>(object, method));
  //  }

	 //void setValueChangedCallback( FunctorBase* memberFunc)
  //  {
  //      changeCallback(memberFunc);
  //  }

	Ogre::Vector2&  getSubMenuPosition();
	MenuItem* getSelectedItem() {  return mMenuItems[mActualSelectedElement]; }     
    /** \brief Return the value of the combobox
    */
    Ogre::String getValue();

    /** \brief Set the current value of this combobox. If the element 
    isn't found, nothing is changed.
    */
	void setCurrentValue(Ogre::String& itemName);

    void highlight();
    
	void setPosition(const Ogre::Vector3& pos);
	void setPosition(int left, int top);
	Ogre::Vector3& getPosition();


protected:

	
	/** \brief The actual overed element.
    If it's >= 0, it's a selector value element, else it's a speial case.
    See implementation : can be NO_ELEMENT, PREVIOUS_ELEMENT_BUTTON or NEXT_ELEMENT_BUTTON
    */
    int mActualOveredElement;
	
    unsigned int mNumTopVisibleElement; //!< \brief Number of the top element that is shown

	unsigned int mMaxNumberOfVisibleMenuItems; //!< \brief Number of elements that can be seen in the selector

    unsigned int mActualSelectedElement; //!< \brief The actual selected element

	MenuItemIt	   mMenuItemIt;
	MenuItemVector mMenuItems; //!< \brief Contains the displayed caption of the combobox

    void _actualize();

private:
	XFBType::Menu* m_element;
	XFBType::Style* m_style;


	WRectangle m_Design;
	WRectangle m_IconLine; //!< \brief The design of the element
   
};


} //namespace XE
#endif