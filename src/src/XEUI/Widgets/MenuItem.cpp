#include <XEUI/Widgets/MenuItem.hpp>
#include <XEUI/UIPanel.hpp>
#include <XEUI/Widgets/Menu.hpp>

namespace XE {



MenuItem::MenuItem( const Ogre::String& name,
			 Ogre::uint16 idx,  
			 const Ogre::String text,
			 Menu* owner)
			 :  m_pImage(nullptr), mOwner(owner), mSplitButton(nullptr), m_base(owner->getParent())
{
//	ElementStyle* style = getStyle(StyleType::S_MenuItem);
//
//	mCaption = mPanelContainer->getGUILayer()->createCaption(style->font, 0, 0, text);
//	
//	// calculate size with Glyphs
//	Ogre::Vector2 testsize = owner->_size;
//	//((mCaption->_calculateDrawSize(testsize);
//
//	//	mCaption->size(testsize.x, testsize.y);
//
//	styleCaption(mCaption,style,ES_Default);
//	
//	//zuerst NavItem hintergrund erstellen dann erst das bild .. sonst bild hinter Navi
//	mDesign = mPanelContainer->getGUILayer()->createRectangle(0, 0);
//
//	mSplitButton = mPanelContainer->getGUILayer()->createRectangle(_pos.x, _pos.y);
//
////	setPosition(style->left, style->top);
//	setSize(testsize.x, style->height);
//
//    _actualize();
}
    
MenuItem::~MenuItem()
{
 /*  mPanelContainer->getGUILayer()->destroyCaption(mCaption);
    mPanelContainer->getGUILayer()->destroyRectangle(mDesign);*/
}

Ogre::Vector2& MenuItem::getSubMenuPosition() 
{
	Ogre::Vector2 pos(m_base._pos.x, m_base._pos.y);
	
	pos.x += m_base._size.x;

	return pos;
}

void MenuItem::setText( const Ogre::String& text )
{
	//ElementStyle* style = getStyle( StyleType::S_MenuItem );

	//Ogre::Vector2 testsize = mOwner->_size;
	//mCaption->text( text );
	
	//mCaption->_calculateDrawSize( testsize );

	//	mCaption->size(testsize.x, testsize.y);

	//setSize(testsize.x, style->height);
}

void MenuItem::setImage( const Ogre::String& sprite, const Ogre::Vector2 imageSize )
{
	// item image 
	//m_vImageOffset = Ogre::Vector2(_pos.x+5, _pos.y+5);
	//m_pImage = mPanelContainer->getGUILayer()->createRectangle(m_vImageOffset, imageSize);
	//m_pImage->background_image(sprite);
}

//void MenuItem::injectKeyPressed(const OIS::KeyEvent& evt)
//{
//}
//    
//
//void MenuItem::injectKeyReleased(const OIS::KeyEvent& evt)
//{
//}

//
//void MenuItem::injectKeys(vector<OIS::KeyCode>& keys)
//{
//}
//
//
//void MenuItem::injectMousePressed(const OIS::MouseEvent& evt, 
//    OIS::MouseButtonID id)
//{
//}
//
//
//void MenuItem::injectMouseReleased(const OIS::MouseEvent& evt, 
//    OIS::MouseButtonID id)
//{
//}


//bool MenuItem::isOver(const Ogre::Vector2& pos)
//{
//    mOvered = mCaption->intersects(pos);
//    return mOvered;
//}


void MenuItem::setSize(int width, int height)
{
    m_base._size.x = width;
	m_base._size.y = height;

 //   mCaption->size(width, height);
	//mDesign->width( width);
 //   mDesign->height(height);
}


void MenuItem::setPosition(int left, int top)
{
	m_base._pos.x = left;
	m_base._pos.y = top;

 //   mCaption->left(left + 50); //pading left for icons
 //   mCaption->top(top);

 //   mDesign->left(left);
 //   mDesign->top(top);

	//if(m_pImage)
	//	m_pImage->position(Ogre::Vector2(left,top) + m_vImageOffset);


	//
	//mSplitButton->width(50);
	//mSplitButton->height(_size.y);
	//mSplitButton->left(_pos.x + _size.x - 50);
	//mSplitButton->top(top);
	//mSplitButton->background_colour(Ogre::ColourValue::Blue);

}


Ogre::Vector2& MenuItem::getPosition()
{
    return mDesign->position();
}



void MenuItem::parentResized()
{

}


void MenuItem::setStyle(ElementStyle* style, bool  resizedOnly)
{

}


void MenuItem::injectTimeAndMousePosition(double time, const Ogre::Vector2& pos)
{
}


void MenuItem::highlight()
{
}


void MenuItem::text(Ogre::String s)
{
  //  mCaption->text(s);
}


Ogre::String MenuItem::text()
{
	return ""; // mCaption->text();
}


void MenuItem::_actualize()
{
    //if (!mBackgroundSpriteName.empty())
    //    mDesign->background_image(mBackgroundSpriteName);
    //else
    //{
    //    mDesign->background_gradient(getColors()->captionBackgroundGradientType,
    //                                 getColors()->captionBackgroundGradientStart,
    //                                 getColors()->captionBackgroundGradientEnd);
    //    mDesign->border(getColors()->captionBorderSize, getColors()->captionBorder);
    //}
}


void MenuItem::setBackgroundImage(const Ogre::String& backgroundSpriteName)
{
   /* _clearRectangleDesign();

    if (backgroundSpriteName.length() == 0 || backgroundSpriteName == "none")
        mBackgroundSpriteName = "";
    else
        mBackgroundSpriteName = backgroundSpriteName;

    _actualize();*/
}


} //namespace XE