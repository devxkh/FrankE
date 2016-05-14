
#include <XEUI/Widgets/Menu.hpp>

#include <XEUI/Widgets/MenuItem.hpp>

#include <XEUI/DAL/FB_UI_StateData_generated.h>
#include <XEUI/DAL/FB_UI_StyleData_generated.h>

#include <XEUI/UIPanel.hpp>

namespace XE {

using namespace Ogre;
using namespace std;

Menu::Menu(UIPanel* parentPanel, XFBType::Menu* menuElement, XFBType::Style* menuStyle)
	: mActualSelectedElement(0), mNumTopVisibleElement(0), m_element(menuElement), m_style(menuStyle), m_base(parentPanel)
{
	//mMaxNumberOfVisibleMenuItems = std::min<unsigned int>(menuElement->displayedElements(), mMenuItems.size());

	// mDesign = parentContainer->getGUILayer()->createRectangle(x, y, width, height);

	// mIconLine = parentContainer->getGUILayer()->createRectangle(x, y, 50, height);
	// mIconLine->background_colour(Colours::Black);
	//
	// ElementStyle* style = getStyle(S_Menu);

//	 mDesign->background_image("buttonInactive");

	// mDesign->background_colour(XE::ColourValue::Black);
//   mDesign->background_gradient(Gradient::Gradient_NorthSouth,
//	   webcolour(Colours::BlueViolet),
//					 rgb(255, 0, 255, 50));

	//styleRectangle(mDesign,style,ES_Default);

	 
	 
	 //	styleCaption(mCaption,style,ElementState::ES_UnOver);

	//for (size_t i=0; i < mMaxNumberOfVisibleMenuItems; i++)
 //   {     
	//   mMenuItems.push_back(items[i]);
	//}

    //for (size_t i=0; i < mMaxNumberOfVisibleMenuItems; i++)
    //{
    //    mMenuItems[i]->textColor(getColors()->comboboxText);
    //    mMenuItems[i]->getCaption()->font(getColors()->comboboxTextSize);
    //}

	//setPosition(x, y);
 //   setSize(width, height);

 //   _actualize();
}


Menu::~Menu()
{
	//dont delete here or destroy in xeui crashs!!!
	 // mPanelContainer->getGUILayer()->destroyRectangle(mDesign);
}


UIPanel*  Menu::getParent()
{
	return m_base._parent;
}

MenuItem* Menu::addItem(MenuItem* item)
{
	mMenuItems.push_back(item);
	unsigned int nbDisplayedElements = 5;
	mMaxNumberOfVisibleMenuItems = std::min<unsigned int>(nbDisplayedElements, mMenuItems.size());

	_actualize();

	return item;
}

MenuItem* Menu::getItemPID( Ogre::uint16 id )
{
	for (int i=0; i < mMenuItems.size(); i++)
    {
		if (mMenuItems[i]->getID() == id)
        {
			return mMenuItems[i];
		}
	}

	OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND, "Could not find MenuItemPID ", "Menu::getItemPID" );
	return nullptr;
}

void Menu::injectTimeAndMousePosition(double time, const Ogre::Vector2& pos)
{
}

void Menu::pointSelectStart(const Ogre::Vector2& point)
{
	/*if (mActualOveredElement == MULTIPLE_ELEMENT_SELECTOR_PREVIOUS_ELEMENT_BUTTON)
	{
		mPreviousElementsButton->pointSelectStart(point);
		return;
	}
	else if (mActualOveredElement == MULTIPLE_ELEMENT_SELECTOR_NEXT_ELEMENT_BUTTON)
	{
		mNextElementsButton->pointSelectStart(point);
		return;
	}*/
	if( mActualOveredElement >= 0 )
		mMenuItems[mActualOveredElement]->pointSelectStart(point);
}


void Menu::pointSelectEnd(const Ogre::Vector2& point)
{
	/*if (mActualOveredElement == MULTIPLE_ELEMENT_SELECTOR_PREVIOUS_ELEMENT_BUTTON)
	mPreviousElementsButton->pointSelectEnd(point);
	else if (mActualOveredElement == MULTIPLE_ELEMENT_SELECTOR_NEXT_ELEMENT_BUTTON)
	mNextElementsButton->pointSelectEnd(point);*/
	//  Actualize the selected element if the overed element is set

	if (mActualOveredElement >= 0)
	{
		
		//mMenuItems[mActualOveredElement]->getDesign()->background_image(getColors()->buttonNotOveredSpriteName);
		mMenuItems[mActualOveredElement]->pointSelectEnd(point);

		mActualSelectedElement = mActualOveredElement + mNumTopVisibleElement;
		// The selected element can't be overed
		mActualOveredElement = -1;// MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT;
		_actualize();

	//todo	callCallback(); 
	}
}

void Menu::setSize(int width, int height){
	
	m_base._size.x = width;
	m_base._size.y = height;

	mDesign->width(width);
    mDesign->height(height);
};

void Menu::setPosition(Ogre::Vector2& position)
{
	m_base._pos.x = position.x;
	m_base._pos.y = position.y;

	//Ogre::Real decalLeft = position.x - mDesign->left();
	//Ogre::Real decalTop = position.y - mDesign->top();

	m_Design.setPosition(position);// m_Design.getPosition().x + decalLeft, m_Design.getPosition().y + decalTop);
  //  mDesign->top(mDesign->top()+decalTop);

	

	m_IconLine.setPosition(m_Design.getPosition());
//    m_IconLine.top(mDesign->top());
  /*  Ogre::Vector2 pButtonPos = mPreviousElementsButton->getPosition() + Ogre::Vector2(decalLeft, decalTop);
    mPreviousElementsButton->setPosition(pButtonPos.x, pButtonPos.y);

    Ogre::Vector2 nButtonPos = mNextElementsButton->getPosition() + Ogre::Vector2(decalLeft, decalTop);
    mNextElementsButton->setPosition(nButtonPos.x, nButtonPos.y);*/
}

Ogre::Vector2 Menu::getPosition()
{
    return mDesign->position();
}


void Menu::parentResized()
{
	setPosition(Ogre::Vector2(m_base._parent->getPosition().x, m_base._parent->getPosition().y));

	_actualize();
	//mConsoleText->left(mPanelContainer->_pos.x + 1);
	//mConsoleText->top(mPanelContainer->_pos.y + 1);

	//mPromptText->top(mPanelContainer->_pos.y + (CONSOLE_LINE_COUNT * mGlyphData->mLineHeight) + 1);
	//mPromptText->left(mPanelContainer->_pos.x + 1);

	//mDecoration->top(mPanelContainer->_pos.y + 1);
	//mDecoration->left(mPanelContainer->_pos.x + 1);
}


//void Menu::setStyle(ElementStyle* style, bool  resizedOnly)
//{
//
//}
//
//void Menu::injectKeyPressed(const OIS::KeyEvent& evt)
//{
//}
//
//
//void Menu::injectKeyReleased(const OIS::KeyEvent& evt)
//{
//}
//
//
//void Menu::injectKeys(vector<OIS::KeyCode>& keys)
//{
//}


void Menu::pointSelection(const Ogre::Vector2& point)
{
	/*VerticalSelector::pointSelectStart(point);
*/

       
    
}

void Menu::clear()
{
	for(mMenuItemIt = mMenuItems.begin(); mMenuItemIt != mMenuItems.end();mMenuItemIt ++ )
	{
		OGRE_DELETE (*mMenuItemIt);
		*mMenuItemIt = nullptr;
		mMenuItems.erase(mMenuItemIt);
	}

}

bool Menu::isOver(const Ogre::Vector2& pos)
{
	/*  if (VerticalSelector::isOver(pos))
        return true;*/

    // Consider the cursor over something
	m_base._hovered = true;

    // Consider nothing is overed
  /*  int save_actualOveredElement = mActualOveredElement;
    if (save_actualOveredElement >= 0)
        mMenuItems[save_actualOveredElement]->background(getColors()->comboboxNotOveredElement);*/

  //  mActualOveredElement = -1; //MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT;

    for (int i=0; i < mMenuItems.size(); i++)
    {
        // Don't need to do anything for the selected element
        if (i == mActualSelectedElement - mNumTopVisibleElement)
            continue;
		
	
        if (mMenuItems[i]->isOver(pos))
        {
            mActualOveredElement = i;
          //  mMenuItems[mActualOveredElement]->background(getStyle getColors()->comboboxOveredElement);
            return true;
        }
    }

    //// mOvered now depends on design intersects
	m_base._hovered = mDesign->intersects(pos);
    // We don't _actualize() because this function take care of
    //  actualizing the captions elements instead of _actualize() (optimisation)
	return m_base._hovered;
}


void Menu::setCurrentValue(String& itemName)
{
   /* for (size_t i=0; i < mCaptions.size(); i++)
    {
        if (mValues[i].compare(itemName) == 0)
        {
            mActualSelectedElement = i;
            _actualize();
            return;
        }
    }*/
}

Ogre::Vector2& Menu::getSubMenuPosition() 
{
	Ogre::Vector2 pos;
	
	pos = mMenuItems[mActualSelectedElement]->getPosition();
	pos.x += mMenuItems[mActualSelectedElement]->getPosition().x;

	return pos;
}

String Menu::getValue()
{
    return ""; //mValues[mActualSelectedElement];
}


void Menu::_actualize()
{
    int x = mDesign->left();
    int y = mDesign->top();
	int width = mDesign->width();
	int height = mDesign->height();

    /*int decalXButtons = x + 
                        width * (VERTICAL_SELECTOR_MARGIN_LEFT + 
                                 VERTICAL_SELECTOR_MARGIN_CAPTIONS_BUTTONS + 
                                 VERTICAL_SELECTOR_CAPTION_X_SIZE);
    int decalYButtonPreviousElements = y + height * VERTICAL_SELECTOR_MARGIN_TOP;
    int decalYButtonNextElements     = y + height * (1 - VERTICAL_SELECTOR_MARGIN_BOTTOM);
    int sizeXYElementButton          =     width * VERTICAL_SELECTOR_BUTTON_SIZE;
    
    mPreviousElementsButton->setPosition(decalXButtons, decalYButtonPreviousElements);
    mPreviousElementsButton->setSize(sizeXYElementButton, sizeXYElementButton);

    mNextElementsButton->setPosition(decalXButtons, decalYButtonNextElements - sizeXYElementButton);
    mNextElementsButton->setSize(sizeXYElementButton, sizeXYElementButton);*/

    int captionsXPosition   = x + 4;// * VERTICAL_SELECTOR_MARGIN_LEFT;
    int captionsXSize       =     width;// * VERTICAL_SELECTOR_CAPTION_X_SIZE;

    int captionsYSize = 50;//;height * VERTICAL_SELECTOR_CAPTION_Y_SIZE;
    //int captionsYSize = height * (1 - ( //VERTICAL_SELECTOR_MARGIN_TOP + 
    //                                   (mMaxNumberOfVisibleMenuItems - 1) *  5)) / // VERTICAL_SELECTOR_CAPTION_HEIGHT_SPACING)) / 
    //                             mMaxNumberOfVisibleMenuItems;

    int captionsYPadding        =    5;// * VERTICAL_SELECTOR_CAPTION_HEIGHT_SPACING;
    int captionsYStartPosition  = y + 4;// height;// * VERTICAL_SELECTOR_MARGIN_TOP;
	int appendPosition = 0;

    for (size_t i=0; i < mMaxNumberOfVisibleMenuItems; i++)
    {
		mMenuItems.at(i)->setPosition( captionsXPosition, 
                                     captionsYStartPosition  + 4 + appendPosition);

		appendPosition += mMenuItems.at(i)->getPosition().y + 4;

       /* mMenuItems.at(i)->setPosition(captionsXPosition, 
                                     captionsYStartPosition + (captionsYSize + captionsYPadding)*i);*/
      //  mMenuItems.at(i)->setSize(captionsXSize, captionsYSize);
    }

    //for (size_t i = 0; i < mMenuItems.size(); i++)
    //{
    //    Ogre::ColourValue color;

    //  /*  unsigned int actualMenuItemIndice = i + mNumTopVisibleElement;
    //    if (actualElementIndice == mActualSelectedMenuItem)
    //        color = getColors()->comboboxSelectedElement;
    //    else if (i == mActualOveredMenuItem)
    //        color = getColors()->comboboxOveredElement;
    //    else
    //        color = getColors()->comboboxNotOveredElement;*/
    //    
    //   /* mMenuItems[i]->text(mValues[actualElementIndice]);
    //    mMenuItems[i]->background(color);*/
    //}
}


void Menu::highlight()
{
//    mDesign->border_colour(getColors()->comboboxBorderHighlight);
}


} //namespace XE