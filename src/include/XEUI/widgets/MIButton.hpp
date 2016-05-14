#ifndef MIBUTTON_H
#define MIBUTTON_H


#include <XEUI/Widgets/MenuItem.hpp>


namespace XE {


	class Menu;

/*! class. ItemButton
    desc.
       A Menubutton.
*/
class MIButton : public MenuItem // public Button ,
{
public:
    /** \brief Use Panel::makeMenu
    */
    MIButton( const Ogre::String& name,
			 Ogre::uint16 idx, 
			 const Ogre::String text,
			  Menu* owner );
    
    /** \brief Use Panel::deleteMenu
    */
    ~MIButton();

	/** \brief Define the callback when the button has been released
    */
    //template<typename T>
    //void setPressedCallback(T* object, bool(T::*method)(PanelElement*))
    //{
    //    changeCallback(OGRE_NEW  MemberFunction<T>(object, method));
    //}

    //void setPressedCallback( FunctorBase* memberFunc)
    //{
    //    changeCallback(memberFunc);
    //}


	void pointSelectStart(const Ogre::Vector2& point);

	void pointSelectEnd(const Ogre::Vector2& point);
    
    bool isOver(const Ogre::Vector2& pos);
   
	void resetState();
    
protected:
	 bool mIsActive; //!< \brief The button can be clicked

    bool mIsClicked; //!< \brief The button is currently clicked

    void _over();

    void _unOver();

    void _inactive();

    void _clicked();

    void _actualize();
   
};


} //namespace XE
#endif // MIBUTTON_H