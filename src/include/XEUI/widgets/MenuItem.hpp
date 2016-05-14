#ifndef MENUITEM_HPP
#define MENUITEM_HPP

//#include <XEUI/Container.hpp>
//#include <XEUI/PanelElement.hpp>
//#include <XEUI/PanelElementCallback.hpp>
#include <XEUI/UIPanel.hpp>
#include <XEUI/Widget.hpp>

//#include <XEUI/UISerializer.hpp>

namespace XE {

	class WRectangle;
	class Menu;

/*! class. MenuItem
    desc.
      Baseclass for MenuItems.
*/
class MenuItem : public Ogre::GeneralAllocatedObject
{
public:
    /** \brief Use Panel::makeMenu
    */
    MenuItem( const Ogre::String& name,
			 Ogre::uint16 idx,  
			 const Ogre::String text,
			  Menu* owner);

    ~MenuItem();

    //void injectKeyPressed(const OIS::KeyEvent& evt);
    //
    //void injectKeyReleased(const OIS::KeyEvent& evt);

    //void injectKeys(std::vector<OIS::KeyCode>& keys);

    //void injectMousePressed(const OIS::MouseEvent& evt, 
    //                        OIS::MouseButtonID id);

    //void injectMouseReleased(const OIS::MouseEvent& evt, 
    //                         OIS::MouseButtonID id);
	virtual void pointSelectStart(const Ogre::Vector2& point)
	{
		if(hasSubMenu())
		{
			//std::cout << "onSelectChar" << std::endl;

			//UISerializer serializer( &mXEUI );

			//serializer.addCallback( "onContinue", this, &GUI::onContinue );
			//serializer.addCallback( "onSelectExit", this, &GUI::onSelectExit );
			//
			//serializer.setScreen( mXEUI.getScreen( "WorldState" ) );
			//mXEUI.getNav()->stepTo( serializer, "menuChar", "General" );
	
			//XE::UI::NavItem* navItem = OGRE_NEW  XE::UI::NavItem(2,1,"blub", mXEUI.getNav()->getPanelContainer());
			//mXEUI.getNav()->addItem(navItem);
			//close Menu -> in navigation ... 
			//letztes panel immer behalten da objekte erst nach neu erstellten panel gelscht werden können
			
			//open Menu
			//UISerializer serializer(&mXEUI);

			//serializer.addCallback("onSelectChar",this, &GUI::onSelectChar);
			//serializer.addCallback("onSelectExit",this, &GUI::onSelectExit);

			//serializer.loadPanel2D("settingPanel.xml" , "General");


			//getPanelContainer()->makeMenu();
		}
	};

	void pointSelectEnd(const Ogre::Vector2& point)
	{
	
	};

	 bool isOver(const Ogre::Vector2& pos)
	{
			return true;
	};

   // virtual bool isOver(const Ogre::Vector2& pos);

	//WRectangle* getDesign() { return mDesign; }

    void setSize(int width, int height);
    
    void setPosition(int left, int top);

	void parentResized();
	//void setStyle(ElementStyle* style, bool  resizedOnly);

    void injectTimeAndMousePosition(double time, const Ogre::Vector2& pos);

    void highlight();

	void text(Ogre::String s);

    Ogre::String text();

	void setImage( const Ogre::String& sprite, const Ogre::Vector2 imageSize );

	void setSubMenu(Ogre::String subMenu) { mSubMenu = subMenu; }

	bool hasSubMenu()
	{
		if(mSubMenu.length() > 0)
			return true;
		else 
			return false;
	}
    /** \brief Set the background to a sprite from the texture atlas.
        note.
            To remove the images pass on "none" or a empty string to the sprite name.
    */
    void setBackgroundImage(const Ogre::String& backgroundSpriteName);

	void MenuItem::setText( const Ogre::String& text );

	Ogre::Vector2&  getSubMenuPosition();



	//void setPosition(const Ogre::Vector3& pos);
	//void pointSelectStart(const Ogre::Vector2& point);
	//void pointSelectEnd(const Ogre::Vector2& point);
	//void parentResized();
	//bool isOver(const Ogre::Vector2& pos);
	//void setSize(int width, int height);
	//void setPosition(int left, int top);
	//Ogre::Vector3& getPosition();
	//void injectTimeAndMousePosition(double time, const Ogre::Vector2& pos);
	//void highlight();
	//void _actualize();

protected:

    Menu* mOwner;
	WRectangle* mSplitButton;
	Ogre::String mSubMenu; // Name of Submenu
	WRectangle* m_pImage;
	Ogre::Vector2 m_vImageOffset;

	Ogre::String mBackgroundSpriteName;

    virtual void _actualize();

};


} //namespace XE

#endif // MENUITEM_HPP