#ifndef NavItem_HPP
#define NavItem_HPP

//#include <XEUI/Container.hpp>
#include <XEUI/Widget.hpp>
//#include <XEUI/PanelElementCallback.hpp>

namespace XE {

	class WRectangle;
	class Navigation;
/*! class. NavItem
    desc.
      Baseclass for NavItems.
*/
class NavItem : public Widget
{
public:
    /** \brief Use Panel::makeNavi
    */
    NavItem( const Ogre::String& name,
			 Ogre::uint16 idx, 
			const Ogre::String text, 
			Navigation* owner);

    ~NavItem();

    //void injectKeyPressed(const OIS::KeyEvent& evt);
    //
    //void injectKeyReleased(const OIS::KeyEvent& evt);

    //void injectKeys(std::vector<OIS::KeyCode>& keys);

    //void injectMousePressed(const OIS::MouseEvent& evt, 
    //                        OIS::MouseButtonID id);

    //void injectMouseReleased(const OIS::MouseEvent& evt, 
    //                         OIS::MouseButtonID id);
	void pointSelectStart(const Ogre::Vector2& point);
	void pointSelectEnd(const Ogre::Vector2& point);

	Ogre::uint16 getIdx() { return mIdx; }

	 bool isOver(const Ogre::Vector2& pos);
	 void resetState();
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

   // virtual bool isOver(const Ogre::Vector2& pos);

//	WRectangle* getDesign() { return mDesign; }

    void setSize(int width, int height);
    
    void setPosition(int left, int top);

  //  Ogre::Vector2 getPosition();
	
	void parentResized();
	//void setStyle(ElementStyle* style, bool  resizedOnly);

    void injectTimeAndMousePosition(double time, const Ogre::Vector2& pos);

    void highlight();

	void text(Ogre::String s);

    Ogre::String text();

    void setImage(const Ogre::String& sprite, const Ogre::Vector2 size);
	void setSubNavi(Ogre::String subNavi) { mSubNavi = subNavi; }

    /** \brief Set the background to a sprite from the texture atlas.
        note.
            To remove the images pass on "none" or a empty string to the sprite name.
    */
    void setBackgroundImage(const Ogre::String& backgroundSpriteName);

	  void _over();
	     void _unOver();
		     void _clicked();
protected:
   
	Ogre::uint16 mIdx;
	Ogre::String mSubNavi; // Name of SubNavi
	WRectangle* m_pImage;
	Ogre::Vector2 m_vImageOffset;

	Ogre::String mBackgroundSpriteName;

    bool mIsClicked; //!< \brief The button is currently clicked

  
 
    void _inactive();



    void _actualize();

};


} //namespace XE

#endif // NavItem_HPP