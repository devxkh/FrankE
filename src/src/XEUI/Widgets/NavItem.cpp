#include <XEUI/Widgets/NavItem.hpp>
#include <XEUI/PanelContainer.hpp>
#include <XEUI/Widgets/Navigation.hpp>

#include <iostream>

namespace XE {


NavItem::NavItem( const Ogre::String& name,
			 Ogre::uint16 idx,  
			 const Ogre::String text,
			 Navigation* owner)
			: PanelElementCallback( name, owner->getPanelContainer()), mIdx(idx), m_pImage(nullptr),
			mIsClicked(false)
{
	setTabIdx( idx );

	ElementStyle* style = getStyle(StyleType::S_NavItem);

	mCaption = mPanelContainer->getGUILayer()->createCaption(style->font, 0, 0, text);
	
	// calculate size with Glyphs
	Ogre::Vector2 testsize;
	mCaption->_calculateDrawSize(testsize);
//	mCaption->size(testsize.x, testsize.y);


	styleCaption(mCaption,style,ES_Default);

	//zuerst NavItem hintergrund erstellen dann erst das bild .. sonst bild hinter Navi
	mDesign = mPanelContainer->getGUILayer()->createRectangle(0, 0);

//	setPosition(style->left, style->top);
	setSize(testsize.x, style->height == 0 ? owner->_size.y : style->height);

    _actualize();
}
    
NavItem::~NavItem()
{
    mPanelContainer->getGUILayer()->destroyCaption(mCaption);
    mPanelContainer->getGUILayer()->destroyRectangle(mDesign);
}

void NavItem::setImage( const Ogre::String& sprite, const Ogre::Vector2 imageSize )
{
	// item image 
	m_vImageOffset = Ogre::Vector2(_pos.x+10, _pos.y+10);
	m_pImage = mPanelContainer->getGUILayer()->createRectangle(m_vImageOffset, imageSize);
	m_pImage->background_image(sprite);
}

//void NavItem::injectKeyPressed(const OIS::KeyEvent& evt)
//{
//}
//    
//
//void NavItem::injectKeyReleased(const OIS::KeyEvent& evt)
//{
//}

//
//void NavItem::injectKeys(vector<OIS::KeyCode>& keys)
//{
//}
//
//
//void NavItem::injectMousePressed(const OIS::MouseEvent& evt, 
//    OIS::MouseButtonID id)
//{
//}
//
//
//void NavItem::injectMouseReleased(const OIS::MouseEvent& evt, 
//    OIS::MouseButtonID id)
//{
//}


//bool NavItem::isOver(const Ogre::Vector2& pos)
//{
//    mOvered = mCaption->intersects(pos);
//    return mOvered;
//}


void NavItem::setSize(int width, int height)
{
	_size.x = width;
	_size.y = height;

    mCaption->size(width, height);
	mDesign->width( width);
    mDesign->height(height);
}


void NavItem::setPosition(int left, int top)
{
	_pos.x = left;
	_pos.y = top;

    mCaption->left(left);
    mCaption->top(top); // + mDesign->height() / 2); // wieso ohne heigth/2 immer oben???

    mDesign->left(left);
    mDesign->top(top);
	
	if(m_pImage)
		m_pImage->position(Ogre::Vector2(left,top) + m_vImageOffset);

}


Ogre::Vector2 NavItem::getPosition()
{
    return mDesign->position();
}

void NavItem::parentResized()
{

}

void NavItem::setStyle(ElementStyle* style, bool  resizedOnly)
{

}


void NavItem::injectTimeAndMousePosition(double time, const Ogre::Vector2& pos)
{
}


void NavItem::highlight()
{
}


void NavItem::text(Ogre::String s)
{
    mCaption->text(s);
}


Ogre::String NavItem::text()
{
    return mCaption->text();
}

void NavItem::setBackgroundImage(const Ogre::String& backgroundSpriteName)
{
    _clearRectangleDesign();

    //if (backgroundSpriteName.length() == 0 || backgroundSpriteName == "none")
    //    mBackgroundSpriteName = "";
    //else
    //    mBackgroundSpriteName = backgroundSpriteName;

    _actualize();
}

void NavItem::pointSelectStart(const Ogre::Vector2& point)
{
	std::cout << "NavItem::pointSelectStart" << std::endl;

	if (!_enabled)
		return;

	mIsClicked = true;

	_actualize();
}


void NavItem::pointSelectEnd(const Ogre::Vector2& point)
{
	mIsClicked = false;

	if (!_enabled)
		return;

	//setFocus(false);
	callCallback(); 
}
    

void NavItem::resetState()
{
    mIsClicked = false;
    _enabled = true;

    PanelElement::resetState();
}


void NavItem::_inactive()
{
	ElementStyle* style = getStyle(S_NavItem);

	styleRectangle(mDesign,style,ES_Disabled);
	styleCaption(mCaption,style,ES_Disabled);
}


void NavItem::_over()
{
	ElementStyle* style = getStyle(S_NavItem);

	styleRectangle(mDesign,style,ES_Over);
	styleCaption(mCaption,style,ES_Over);
}


void NavItem::_unOver()
{
   	ElementStyle* style = getStyle(S_NavItem);

	styleRectangle(mDesign,style,ES_Default);
	styleCaption(mCaption,style,ES_Default);
}


void NavItem::_clicked()
{
    ElementStyle* style = getStyle(S_NavItem);

	styleRectangle(mDesign,style,ES_Selected);
	styleCaption(mCaption,style,ES_Selected);
}

bool NavItem::isOver(const Ogre::Vector2& pos)
{
    if (!_enabled)
        return false;

    mOvered = mDesign->intersects(pos);
    _actualize();
    return mOvered;
}

void NavItem::_actualize()
{
    if (_enabled)
    {
        if (mIsClicked)
            _clicked();
        else
            mOvered ? _over() : _unOver();
    }
    else
        _inactive();
}
    

} //namespace XE