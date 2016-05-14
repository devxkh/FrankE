
#include <XEUI/Widgets/MultipleElementsSelector.hpp>

#include <XEUI/Widgets/Button.hpp>
#include <XEUI/PanelContainer.hpp>

namespace XE {
namespace UI {

MultipleElementsSelector::MultipleElementsSelector(Uint32 id,
												   Float x, 
                                                   Float y,
                                                   size_t width,
                                                   size_t height,
                                                   const SYS::vector< SYS::String>::type& items,
                                                   PanelContainer* parentContainer)
                                                   : PanelElementCallback(id,parentContainer), 
                                                      mActualOveredElement(MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT)
{
    mDesign = mPanelContainer->getGUILayer()->createRectangle(x, y, width, height);

    mPreviousElementsButton = new Button(0, 0, 0, 30, 30, "", mPanelContainer);
    mNextElementsButton = new Button(0, 0, 0, 30, 30, "", mPanelContainer);

    for (size_t i = 0; i < items.size(); i++)
        addItem(items[i]);
}


MultipleElementsSelector::~MultipleElementsSelector()
{
    mPanelContainer->getGUILayer()->destroyRectangle(mDesign);

    delete mNextElementsButton;
    delete mPreviousElementsButton;
}


void MultipleElementsSelector::pointSelectStart(const Math::Vector2f& point)
{
	if (mActualOveredElement == MULTIPLE_ELEMENT_SELECTOR_PREVIOUS_ELEMENT_BUTTON)
	{
		mPreviousElementsButton->pointSelectStart(point);
		return;
	}
	else if (mActualOveredElement == MULTIPLE_ELEMENT_SELECTOR_NEXT_ELEMENT_BUTTON)
	{
		mNextElementsButton->pointSelectStart(point);
		return;
	}
}


void MultipleElementsSelector::pointSelectEnd(const Math::Vector2f& point)
{
	if (mActualOveredElement == MULTIPLE_ELEMENT_SELECTOR_PREVIOUS_ELEMENT_BUTTON)
		mPreviousElementsButton->pointSelectEnd(point);
	else if (mActualOveredElement == MULTIPLE_ELEMENT_SELECTOR_NEXT_ELEMENT_BUTTON)
		mNextElementsButton->pointSelectEnd(point);

}


bool MultipleElementsSelector::isOver(const Math::Vector2f& pos)
{
    // As the buttons are independant of the rest, first check
    //  if they are overed.
    if (mPreviousElementsButton->isOver(pos))
    {
        mActualOveredElement = MULTIPLE_ELEMENT_SELECTOR_PREVIOUS_ELEMENT_BUTTON;
        return true;
    }
    else if (mNextElementsButton->isOver(pos))
    {
        mActualOveredElement = MULTIPLE_ELEMENT_SELECTOR_NEXT_ELEMENT_BUTTON;
        return true;
    }

    return false;
}


void MultipleElementsSelector::addItem( SYS::String itemName)
{
    mValues.push_back(itemName);
}


void MultipleElementsSelector::injectTimeAndMousePosition(double time, const Math::Vector2f& pos)
{
}


void MultipleElementsSelector::resetState()
{
    mPreviousElementsButton->resetState();
    mNextElementsButton->resetState();

    PanelElement::resetState();
}


void MultipleElementsSelector::setBackgroundImageButtons(const  SYS::String& previousButtonOveredSpriteName,
                                                         const  SYS::String& previousButtonNotOveredSpriteName,
                                                         const  SYS::String& previousButtonInactiveSpriteName,
                                                         const  SYS::String& previousButtonClickedSpriteName,
                                                         const  SYS::String& nextButtonOveredSpriteName,
                                                         const  SYS::String& nextButtonNotOveredSpriteName,
                                                         const  SYS::String& nextButtonInactiveSpriteName,
                                                         const  SYS::String& nextButtonClickedSpriteName)
{
    // Make sure buttons background images are not empty or none
    //  to remove the text on buttons
    if (previousButtonOveredSpriteName.length() == 0    || previousButtonOveredSpriteName == "none"     ||
        previousButtonNotOveredSpriteName.length() == 0 || previousButtonNotOveredSpriteName == "none"  ||
        previousButtonInactiveSpriteName.length() == 0  || previousButtonInactiveSpriteName == "none"   ||
        previousButtonClickedSpriteName.length() == 0   || previousButtonClickedSpriteName == "none"    ||
        nextButtonOveredSpriteName.length() == 0        || nextButtonOveredSpriteName == "none"         ||
        nextButtonNotOveredSpriteName.length() == 0     || nextButtonNotOveredSpriteName == "none"      ||
        nextButtonInactiveSpriteName.length() == 0      || nextButtonInactiveSpriteName == "none"       ||
        nextButtonClickedSpriteName.length() == 0       || nextButtonClickedSpriteName == "none")
    {
        mPreviousElementsButton->setText("<");
        mNextElementsButton->setText(">");
    }
    else
    {
        mPreviousElementsButton->setBackgroundImage(previousButtonOveredSpriteName, 
                                                    previousButtonNotOveredSpriteName, 
                                                    previousButtonInactiveSpriteName,
                                                    previousButtonClickedSpriteName);
        mPreviousElementsButton->setText("");

        mNextElementsButton->setBackgroundImage(nextButtonOveredSpriteName, 
                                                nextButtonNotOveredSpriteName, 
                                                nextButtonInactiveSpriteName,
                                                nextButtonClickedSpriteName);
        mNextElementsButton->setText("");
    }
}


void MultipleElementsSelector::setPosition(int left, int top)
{
    XE::Float decalLeft = left - mDesign->left();
    XE::Float decalTop = top - mDesign->top();

    mDesign->left(mDesign->left()+decalLeft);
    mDesign->top(mDesign->top()+decalTop);

    Math::Vector2f pButtonPos = mPreviousElementsButton->getPosition() + Math::Vector2f(decalLeft, decalTop);
    mPreviousElementsButton->setPosition(pButtonPos.x, pButtonPos.y);

    Math::Vector2f nButtonPos = mNextElementsButton->getPosition() + Math::Vector2f(decalLeft, decalTop);
    mNextElementsButton->setPosition(nButtonPos.x, nButtonPos.y);
}


Button* MultipleElementsSelector::getPreviousElementsButton()
{
    return mPreviousElementsButton;
}


Button* MultipleElementsSelector::getNextElementsButton()
{
    return mNextElementsButton;
}

} //namespace UI
} //namespace XE