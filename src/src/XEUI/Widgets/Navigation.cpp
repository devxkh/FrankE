
#include <XEUI/Widgets/Navigation.hpp>

#include <XEUI/Widgets/NavItem.hpp>
#include <XEUI/PanelContainer.hpp>
#include <XEUI/UISerializer.hpp>
#include <XEUI/UIPanel.hpp>
#include <XEUI/Panel2D.hpp>

namespace XE {


using namespace std;

Navigation::Navigation( const Ogre::String& name,
				    Ogre::Real x, 
				    Ogre::Real y,
                   size_t width,
                   size_t height,
                   unsigned int nbDisplayedElements,
                   PanelContainer* parentContainer)
                   :  PanelElementCallback( name, parentContainer ), 
                     mSelectedIdx(0), mNumTopVisibleElement(0)
					// mPrevPanel(nullptr), mActualPanel(nullptr), mLastStateID(0)
{

	mMaxNumberOfVisibleNavItems = std::min<unsigned int>(nbDisplayedElements, mNavItems.size());


	 mDesign = mPanelContainer->getGUILayer()->createRectangle(x, y, width, height);


	// mDesign->background_colour(XE::ColourValue::Black);
		   	
	ElementStyle* style = getStyle(StyleType::S_Navigation);
	styleRectangle(mDesign,style,ES_Default);

	//for (size_t i=0; i < mMaxNumberOfVisibleNavItems; i++)
 //   {     
	//   mNavItems.push_back(items[i]);
	//}

    //for (size_t i=0; i < mMaxNumberOfVisibleNavItems; i++)
    //{
    //    mNavItems[i]->textColor(getColors()->comboboxText);
    //    mNavItems[i]->getCaption()->font(getColors()->comboboxTextSize);
    //}

	setPosition(x, y);
    setSize(width, height);

    _actualize();
}


Navigation::~Navigation()
{
}

NavItem* Navigation::addItem( const Ogre::String& name,
			 Ogre::uint16 idx, 
			const Ogre::String text )
{

	NavItem* newNavItem = OGRE_NEW  NavItem( name, idx, text, this );

	mNavItems.push_back(newNavItem);
	
	unsigned int nbDisplayedElements = 10;
	mMaxNumberOfVisibleNavItems = std::min<unsigned int>(nbDisplayedElements, mNavItems.size());

	_actualize();

	return newNavItem;
}

NavItem* Navigation::addItem(NavItem* item)
{
	mNavItems.push_back(item);
	
	unsigned int nbDisplayedElements = 10;
	mMaxNumberOfVisibleNavItems = std::min<unsigned int>(nbDisplayedElements, mNavItems.size());

	_actualize();

	return item;
}

void Navigation::injectTimeAndMousePosition(double time, const Ogre::Vector2& pos)
{

}

void Navigation::pointSelectStart(const Ogre::Vector2& point)
{
	/*if (mOveredIdx == MULTIPLE_ELEMENT_SELECTOR_PREVIOUS_ELEMENT_BUTTON)
	{
		mPreviousElementsButton->pointSelectStart(point);
		return;
	}
	else if (mOveredIdx == MULTIPLE_ELEMENT_SELECTOR_NEXT_ELEMENT_BUTTON)
	{
		mNextElementsButton->pointSelectStart(point);
		return;
	}*/
	if(mOveredIdx >= 0)
		for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
			if((*mNavItemIt)->getTabIdx() == mOveredIdx)
					(*mNavItemIt)->pointSelectStart(point);
}


void Navigation::pointSelectEnd(const Ogre::Vector2& point)
{
	/*if (mOveredIdx == MULTIPLE_ELEMENT_SELECTOR_PREVIOUS_ELEMENT_BUTTON)
	mPreviousElementsButton->pointSelectEnd(point);
	else if (mOveredIdx == MULTIPLE_ELEMENT_SELECTOR_NEXT_ELEMENT_BUTTON)
	mNextElementsButton->pointSelectEnd(point);*/
	//  Actualize the selected element if the overed element is set

	if (mOveredIdx >= 0)
	{
		
		//mNavItems[mOveredIdx]->getDesign()->background_image(getColors()->buttonNotOveredSpriteName);
		for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
			if((*mNavItemIt)->getTabIdx() == mOveredIdx)
					(*mNavItemIt)->pointSelectEnd(point);

		//If Selected Item Changed -> Fire Callback
		if(mOveredIdx != mSelectedIdx)
		{
			mSelectedIdx = mOveredIdx + mNumTopVisibleElement;

			callCallback(); 
		}else
			mSelectedIdx = mOveredIdx + mNumTopVisibleElement;
	
		// The selected element can't be overed
		mOveredIdx = -1;// MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT;
		_actualize();	
	}
}

void Navigation::setSize(int width, int height){
	
	_size.x = width;
	_size.y = height;

	mDesign->width(width);
    mDesign->height(height);
};

void Navigation::setPosition(int left, int top)
{
     Ogre::Real decalLeft = left - mDesign->left();
     Ogre::Real decalTop = top - mDesign->top();

    mDesign->left(mDesign->left()+decalLeft);
    mDesign->top(mDesign->top()+decalTop);

  /*  Ogre::Vector2 pButtonPos = mPreviousElementsButton->getPosition() + Ogre::Vector2(decalLeft, decalTop);
    mPreviousElementsButton->setPosition(pButtonPos.x, pButtonPos.y);

    Ogre::Vector2 nButtonPos = mNextElementsButton->getPosition() + Ogre::Vector2(decalLeft, decalTop);
    mNextElementsButton->setPosition(nButtonPos.x, nButtonPos.y);*/
}

Ogre::Vector2 Navigation::getPosition()
{
    return mDesign->position();
}


void Navigation::parentResized()
{

}

void Navigation::setStyle(ElementStyle* style, bool  resizedOnly)
{

}

//
//void Navigation::injectKeyPressed(const OIS::KeyEvent& evt)
//{
//}
//
//
//void Navigation::injectKeyReleased(const OIS::KeyEvent& evt)
//{
//}
//
//
//void Navigation::injectKeys(vector<OIS::KeyCode>& keys)
//{
//}


void Navigation::pointSelection(const Ogre::Vector2& point)
{
	/*VerticalSelector::pointSelectStart(point);
*/

       
    
}

bool Navigation::makePrevItemOver()
{
	if(mOveredIdx < 0)
		mOveredIdx = mSelectedIdx;
	else {
		if(mOveredIdx > 0)
			mOveredIdx -=1;
		else
			return false;
	}

	for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
	{
		if ((*mNavItemIt)->getTabIdx() == mOveredIdx)
		{   (*mNavItemIt)->_over();
		//	mNavItems[mOveredIdx]->setOvered(true);
		}
		else if((*mNavItemIt)->getTabIdx() == mSelectedIdx)
			(*mNavItemIt)->_clicked();
		else
			(*mNavItemIt)->_unOver();
	}

	return true;
}

void Navigation::selectOveredItem()
{
	for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
	{	
		if ((*mNavItemIt)->getTabIdx() == mOveredIdx)
		{
			mSelectedIdx = mOveredIdx;
			(*mNavItemIt)->_clicked();
			callCallback(); //Achtung ohne "mSelectedIdx = mOveredIdx;" endlos loop da navchanged aufgerufen wird!!
		}
		else
			(*mNavItemIt)->_unOver();
	}
}

bool Navigation::makeNextItemOver()
{
	if(mOveredIdx < 0)
		mOveredIdx = mSelectedIdx;
	else
	{
		if((mOveredIdx + 1) < mNavItems.size())
			mOveredIdx +=1;
		else
			return false;
	}
	
	for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
	{
		if ((*mNavItemIt)->getTabIdx() == mOveredIdx)
           (*mNavItemIt)->_over();
		else if((*mNavItemIt)->getTabIdx() == mSelectedIdx)
			(*mNavItemIt)->_clicked();
		else
			(*mNavItemIt)->_unOver();
    }

	return true;
}

NavItem* Navigation::getSelectedItem() 
{ 
	for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
		if((*mNavItemIt)->getTabIdx() == mSelectedIdx)
			return (*mNavItemIt);

	return nullptr;
}

bool Navigation::isOver(const Ogre::Vector2& pos)
{
  /*  if (VerticalSelector::isOver(pos))
        return true;*/

    // Consider the cursor over something
    mOvered = true;

    // Consider nothing is overed
 //   int save_actualOveredElement = mOveredIdx;
  //  if (save_actualOveredElement >= 0)
	//	mNavItems[save_actualOveredElement]->isOver()//->background(getColors()->comboboxNotOveredElement);

    //mOveredIdx = -1; //MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT;

	for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
	{
		 // Don't need to do anything for the selected element
		if((*mNavItemIt)->getTabIdx() == mSelectedIdx)
			continue;

		if ((*mNavItemIt)->isOver(pos))
        {
			mOveredIdx = (*mNavItemIt)->getTabIdx();
           return true;
        }
	}

    //for (int i=0; i < mNavItems.size(); i++)
    //{
    //   
    //    if (i == mSelectedIdx)
    //        continue;

    //    if (mNavItems[i]->isOver(pos))
    //    {
    //        mOveredIdx = i;
    // //       mNavItems[mOveredIdx]->background(getColors()->comboboxOveredElement);
    //        return true;
    //    }
    //}

    //// mOvered now depends on design intersects
    mOvered = mDesign->intersects(pos);
    // We don't _actualize() because this function take care of
    //  actualizing the captions elements instead of _actualize() (optimisation)
    return mOvered;
}


//void Navigation::setCurrentValue(String& itemName)
//{
//   /* for (size_t i=0; i < mCaptions.size(); i++)
//    {
//        if (mValues[i].compare(itemName) == 0)
//        {
//            mSelectedIdx = i;
//            _actualize();
//            return;
//        }
//    }*/
//}


//String Navigation::getValue()
//{
//	if(mNavItems.size() >= mSelectedIdx)
//		return Ogre::StringConverter::toString(mNavItems[mSelectedIdx]->getIdx());
//	
//	OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND,
//				"Could not find the NavItem ", "Navigation::getValue" );
//}

NavItem* Navigation::getNavItem( const Ogre::String& name )
{
	for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
	{
		if((*mNavItemIt)->getName() == name)
			return (*mNavItemIt);
	}
	/*for (int i=0; i < mNavItems.size(); i++)
    {
		if (mNavItems[i]->getName() == name)
        {
			return mNavItems[i];
		}
	}
*/
	OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Could not find NavItem per Name ", "Navigation::getNavItem");
}

void Navigation::selectPIdx( const Ogre::uint16& idx )
{
	for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
	{
		if((*mNavItemIt)->getTabIdx() == idx)
			(*mNavItemIt)->_clicked();
		else
			(*mNavItemIt)->_unOver();
	}

	mSelectedIdx = idx;
}

NavItem* Navigation::getItemPIdx( const Ogre::uint16& idx )
{
	for(mNavItemIt = mNavItems.begin();mNavItemIt != mNavItems.end();mNavItemIt++)
	{
		if((*mNavItemIt)->getTabIdx() == idx)
			return (*mNavItemIt);
	}

	OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Could not find Index ", "Navigation::getItemIdx");
}

NavItem* Navigation::getItemPID( Ogre::uint16 id )
{
	for (int i=0; i < mNavItems.size(); i++)
    {
		if (mNavItems[i]->getID() == id)
        {
			return mNavItems[i];
		}
	}

	OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Could not find NavItemPID ", "Navigation::getItemPID");
}

void Navigation::_actualize()
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
    //                                   (mMaxNumberOfVisibleNavItems - 1) *  5)) / // VERTICAL_SELECTOR_CAPTION_HEIGHT_SPACING)) / 
    //                             mMaxNumberOfVisibleNavItems;

    int captionsYPadding        =    5;// * VERTICAL_SELECTOR_CAPTION_HEIGHT_SPACING;
    int captionsYStartPosition  = y; //+ 4;// height;// * VERTICAL_SELECTOR_MARGIN_TOP;

	int appendPosition = 0;

    for (size_t i=0; i < mMaxNumberOfVisibleNavItems; i++)
    {
		//mNavItems.at(i)->setPosition((captionsXPosition+ (mNavItems.at(i)->getDesign()->width() + captionsYPadding))
		//							+ (4 + appendPosition)
		//							, 							
		mNavItems.at(i)->setPosition( captionsXPosition + 4 + appendPosition, 
                                     captionsYStartPosition );

		appendPosition += mNavItems.at(i)->_size.x + 4;
      //  mNavItems.at(i)->setSize(captionsXSize, captionsYSize);
    }

    //for (size_t i = 0; i < mNavItems.size(); i++)
    //{
    //    Ogre::ColourValue color;

    //  /*  unsigned int actualNavItemIndice = i + mNumTopVisibleElement;
    //    if (actualElementIndice == mActualSelectedNavItem)
    //        color = getColors()->comboboxSelectedElement;
    //    else if (i == mActualOveredNavItem)
    //        color = getColors()->comboboxOveredElement;
    //    else
    //        color = getColors()->comboboxNotOveredElement;*/
    //    
    //   /* mNavItems[i]->text(mValues[actualElementIndice]);
    //    mNavItems[i]->background(color);*/
    //}
}


void Navigation::highlight()
{
//    mDesign->border_colour(getColors()->comboboxBorderHighlight);
}

//void Navigation::removeActualPanel( )
//{
//	if(mActualPanel)
//	{	
////		mActualPanel->_destroy = true;
//	//	mActualPanel = nullptr;
//	}
//}

//void Navigation::setActualPanel( UIPanel* uiPanel )
//{
//	if(mActualPanel)
//		mPrevPanel = mActualPanel;
//
//	//disable other Panels for Input
//	if(mPrevPanel)
//	{
//		mPrevPanel->_enabled = false;
//		mPrevPanel->_visible = false;
//
//		removeActualPanel();
//	}
//
//	if(uiPanel)
//	{
//		// Then static_cast is not safe type of casting. It can cast to your type but if its wrong it will 
//		//not throw any error/message. So you will get bad object from that. 
//		//And the dynamic_cast is throwing error if the casting failed
//		//!!!!! ------------ static und dynamic_cast verursacht hier heap corruption wenn uipanel nicht erstellt --------------!!!!!!!!
//			mPrevPanel = mActualPanel = nullptr;
//		mActualPanel = dynamic_cast<ScreenPanel*>(uiPanel);
////		mActualPanel->_enabled = true;
//	//	mActualPanel->_visible = true;
//		
//	}else
//	{
//	//	removeActualPanel();
//	}
//}


} //namespace XE