
#include <XEUI/Widgets/ComboBox.hpp>

#include <XEUI/Widgets/Caption.hpp>

namespace XE {
namespace UI {

using namespace std;

Combobox::Combobox(Uint32 id,
				   Float x, 
				   Float y,
                   size_t width,
                   size_t height,
                   const SYS::vector<SYS::String>::type& items,
                   unsigned int nbDisplayedElements,
                   PanelContainer* parentContainer)
                   : VerticalSelector(id, x, y, width, height, items, nbDisplayedElements, parentContainer), 
                     mActualSelectedElement(0)
{
    mDesign->background_gradient(getColors()->comboboxBackgroundGradientType,
                                 getColors()->comboboxBackgroundGradientStart,
                                 getColors()->comboboxBackgroundGradientEnd);
    mDesign->border(getColors()->comboboxBorderSize,
                    getColors()->comboboxBorder);

    for (size_t i=0; i < mMaxNumberOfVisibleElements; i++)
    {
        mCaptions[i]->textColor(getColors()->comboboxText);
        mCaptions[i]->getCaption()->font(getColors()->comboboxTextSize);
    }

    _actualize();
}


Combobox::~Combobox()
{
}

//
//void Combobox::injectKeyPressed(const OIS::KeyEvent& evt)
//{
//}
//
//
//void Combobox::injectKeyReleased(const OIS::KeyEvent& evt)
//{
//}
//
//
//void Combobox::injectKeys(vector<OIS::KeyCode>& keys)
//{
//}


void Combobox::pointSelection(const Math::Vector2f& point)
{
	VerticalSelector::pointSelectStart(point);


        // Actualize the selected element if the overed element is set
        if (mActualOveredElement >= 0)
        {
            mActualSelectedElement = mActualOveredElement + mNumTopVisibleElement;
            // The selected element can't be overed
            mActualOveredElement = MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT;
            _actualize();
            callCallback();
        }
    
}


bool Combobox::isOver(const Math::Vector2f& pos)
{
    if (VerticalSelector::isOver(pos))
        return true;

    // Consider the cursor over something
    mOvered = true;

    // Consider nothing is overed
    int save_actualOveredElement = mActualOveredElement;
    if (save_actualOveredElement >= 0)
        mCaptions[save_actualOveredElement]->background(getColors()->comboboxNotOveredElement);

    mActualOveredElement = MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT;

    for (int i=0; i < mCaptions.size(); i++)
    {
        // Don't need to do anything for the selected element
        if (i == mActualSelectedElement - mNumTopVisibleElement)
            continue;

        if (mCaptions[i]->isOver(pos))
        {
            mActualOveredElement = i;
            mCaptions[mActualOveredElement]->background(getColors()->comboboxOveredElement);
            return true;
        }
    }

    // mOvered now depends on design intersects
    mOvered = mDesign->intersects(pos);
    // We don't _actualize() because this function take care of
    //  actualizing the captions elements instead of _actualize() (optimisation)
    return mOvered;
}


void Combobox::setCurrentValue(SYS::String& itemName)
{
    for (size_t i=0; i < mCaptions.size(); i++)
    {
        if (mValues[i].compare(itemName) == 0)
        {
            mActualSelectedElement = i;
            _actualize();
            return;
        }
    }
}


SYS::String Combobox::getValue()
{
    return mValues[mActualSelectedElement];
}


void Combobox::_actualize()
{
    for (size_t i = 0; i < mCaptions.size(); i++)
    {
        XE_G::ColourValue color;

        unsigned int actualElementIndice = i + mNumTopVisibleElement;
        if (actualElementIndice == mActualSelectedElement)
            color = getColors()->comboboxSelectedElement;
        else if (i == mActualOveredElement)
            color = getColors()->comboboxOveredElement;
        else
            color = getColors()->comboboxNotOveredElement;
        
        mCaptions[i]->text(mValues[actualElementIndice]);
        mCaptions[i]->background(color);
    }
}


void Combobox::highlight()
{
    mDesign->border_colour(getColors()->comboboxBorderHighlight);
}

} //namespace UI
} //namespace XE