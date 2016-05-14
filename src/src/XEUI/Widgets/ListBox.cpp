#include <XEUI/Widgets/ListBox.hpp>

#include <XEUI/Widgets/Caption.hpp>
#include <XEUI/PanelContainer.hpp>
#include <XEUI/ElementStyle.hpp>

namespace XE {
namespace UI {

Listbox::Listbox(Uint32 id,
				 Float x, 
                 Float y,
                 size_t width,
                 size_t height,
                 const SYS::vector<SYS::String>::type& items,
                 unsigned int nbDisplayedElements,
                 PanelContainer* parentContainer)
                 : VerticalSelector(id,x, y, width, height, items, nbDisplayedElements, parentContainer),
                   addedMode(false)
{
	ElementStyle* style = parentContainer->getStyle(StyleType::ListBox);

	if(style->background.type == BackgroundType::Colour)
		mDesign->background_colour(style->background.colour);
	else if(style->background.type == BackgroundType::Sprite)
		mDesign->background_image(style->background.sprite);
	else if(style->background.type == BackgroundType::Transparent)
		mDesign->no_background();
	else if(style->background.type == BackgroundType::Gradient)
	{
		mDesign->background_gradient(style->background.gradientType,
                                 style->background.gradientStart,
                                 style->background.gradientEnd);
	}
	
	mDesign->border(style->border.width, style->border.brush);

    _actualize();

    // init
    for (size_t i=0; i < items.size(); i++)
        mSelectedElements[i] = false;

    for (size_t i=0; i < mMaxNumberOfVisibleElements; i++)
    {
/*        mCaptions[i]->textColor(getColors()->listboxText);
        mCaptions[i]->getCaption()->font(getColors()->listboxTextSize)*/;
    }
}


Listbox::~Listbox()
{
}


//void Listbox::injectKeyPressed(const OIS::KeyEvent& evt)
//{
//    if (evt.key == OIS::KC_LCONTROL ||
//        evt.key == OIS::KC_RCONTROL)
//    {
//        addedMode = true;
//    }
//}
//
//
//void Listbox::injectKeyReleased(const OIS::KeyEvent& evt)
//{
//    if (evt.key == OIS::KC_LCONTROL ||
//        evt.key == OIS::KC_RCONTROL)
//    {
//        addedMode = false;
//    }
//}
//
//
//void Listbox::injectKeys(vector<OIS::KeyCode>& keys)
//{
//    for (size_t i=0; i < keys.size(); i++)
//    {
//        if (keys.at(i) == OIS::KC_LCONTROL ||
//            keys.at(i) == OIS::KC_RCONTROL)
//        {
//            addedMode = true;
//        }
//    }
//}


void Listbox::pointSelection(const Math::Vector2f& point)
{
	VerticalSelector::pointSelectStart(point);

	// Actualize selected elements if the overed element is set
	if (mActualOveredElement >= 0)
	{
		// AddedMode is set when the user has control button down
		if (!addedMode)
		{
			for (size_t i=0; i < mValues.size(); i++)
				mSelectedElements[i] = false;
		}

		mSelectedElements[mActualOveredElement + mNumTopVisibleElement] = 
			!mSelectedElements[mActualOveredElement + mNumTopVisibleElement];

		// The selected element can't be overed
		mActualOveredElement = MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT;
		_actualize();
		callCallback();
	}
}


bool Listbox::isOver(const Math::Vector2f& pos)
{
    if (VerticalSelector::isOver(pos))
        return true;

    // Consider the cursor over something
    mOvered = true;

    // Consider there's no elements overed
    if (mActualOveredElement >= 0)
    {
        if (mSelectedElements[mNumTopVisibleElement + mActualOveredElement])
        {
            mCaptions[mActualOveredElement]
                ->background(getColors()->listboxNotOveredSelectedElement);
        }
        else
        {
            mCaptions[mActualOveredElement]
                ->background(getColors()->listboxNotOveredElement);
        }
    }

    mActualOveredElement = MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT;

    for (size_t i=0; i < mCaptions.size(); i++)
    {
        if (mCaptions[i]->isOver(pos))
        {
            mActualOveredElement = i;
            // Is it a selected element ?
            if (mSelectedElements[mNumTopVisibleElement + i])
            {
                mCaptions[mActualOveredElement]
                    ->background(getColors()->listboxOveredSelectedElement);
            }
            else
            {
                mCaptions[mActualOveredElement]
                    ->background(getColors()->listboxOveredElement);
            }
            return true;
        }
    }

    // mOvered now depends on design intersects
    mOvered = mDesign->intersects(pos);
    // We don't _actualize() because this function take care of
    //  actualizing the captions elements instead of _actualize() (optimisation)
    return mOvered;
}


void Listbox::setCurrentValues(SYS::vector<SYS::String>::type& itemsName)
{
    for (size_t i=0; i < itemsName.size(); i++)
    {
        for (size_t j=0; j < mValues.size(); j++)
        {
            if (itemsName.at(i).compare(mValues.at(j))==0)
            {
                mSelectedElements[j] = true;
                break;
            }
        }
    }

    _actualize();
    callCallback();
}


void Listbox::setCurrentValue(SYS::String& itemName)
{
	SYS::vector<SYS::String>::type v;
    v.push_back(itemName);
    setCurrentValues(v);
}


SYS::vector<SYS::String>::type Listbox::getValues()
{
	SYS::vector<SYS::String>::type values;
    SYS::map<int, bool>::iterator it = mSelectedElements.begin();
    while (it != mSelectedElements.end())
    {
        if ((*it).second)
            values.push_back(mValues[(*it).first]);
        ++it;
    }
    return values;
}


void Listbox::_actualize()
{
    for (size_t i = 0; i < mCaptions.size(); i++)
    {
        XE_G::ColourValue color;

        unsigned int actualElementIndice = i + mNumTopVisibleElement;
        if (mSelectedElements[actualElementIndice])
            color = getColors()->listboxNotOveredSelectedElement;
        else if (i == mActualOveredElement)
            color = getColors()->listboxOveredElement;
        else
            color = getColors()->listboxNotOveredElement;
        
        mCaptions[i]->text(mValues[actualElementIndice]);
        mCaptions[i]->background(color);
    }
}


void Listbox::setFocus(bool hasFocus)
{
    VerticalSelector::setFocus(hasFocus);
    if (!mHasFocus)
        addedMode = false;
}


void Listbox::highlight()
{
    mDesign->border_colour(getColors()->listboxBorderHighlight);
}

} //namespace UI
} //namespace XE