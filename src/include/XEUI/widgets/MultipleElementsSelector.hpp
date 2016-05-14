#ifndef Gui3DMultipleElementsSelector_H
#define Gui3DMultipleElementsSelector_H

#include <Ogre/OgreMain/include/OgrePrerequisites.h>
#include <XEUI/PanelElementCallback.hpp>

namespace XE {
namespace UI {

	class Button;

/*! class. MultipleElementsSelector
    desc.
        An abstract class for a selector with multiple elements and buttons.
*/
class MultipleElementsSelector : public PanelElementCallback, public RectangleDesigned
{
public:
    MultipleElementsSelector(Uint32 id,
							 Float x, 
                             Float y,
                             size_t width,
                             size_t height,
                             const SYS::vector<SYS::String>::type& items,
                             PanelContainer* parentContainer);

    ~MultipleElementsSelector();

    virtual void pointSelectStart(const Math::Vector2f& point);

    virtual void pointSelectEnd(const Math::Vector2f& point);

    virtual bool isOver(const Math::Vector2f& pos);

    /** \brief Add an item to the container
    */
    virtual void addItem(SYS::String itemName);

    void injectTimeAndMousePosition(double time, const Math::Vector2f& pos);

    void resetState();

    /** \brief Set the backgrounds images of the previous and next buttons from the texture atlas. 
        note.
            To remove the images pass "none" or a empty string to at least one parameter
    */
    void setBackgroundImageButtons(const SYS::String& previousButtonOveredSpriteName,
                                   const SYS::String& previousButtonNotOveredSpriteName,
                                   const SYS::String& previousButtonInactiveSpriteName,
                                   const SYS::String& previousButtonClickedSpriteName,
                                   const SYS::String& nextButtonOveredSpriteName,
                                   const SYS::String& nextButtonNotOveredSpriteName,
                                   const SYS::String& nextButtonInactiveSpriteName,
                                   const SYS::String& nextButtonClickedSpriteName);

    virtual void setPosition(int left, int top);

    /** \brief Define the callback when a value has changed
    */
    template<typename T>
    void setValueChangedCallback(T* object, bool(T::*method)(PanelElement*))
    {
        changeCallback(new MemberFunction<T>(object, method));
    }

    /** \brief Be careful when using this. Undesired behaviour
    can happened. You should then just use it to set some
    alignment/colors options.
    Return the previous elements button.
    */
    Button* getPreviousElementsButton();

    /** \brief Be careful when using this. Undesired behaviour
    can happened. You should then just use it to set some
    alignment/colors options.
    Return the next elements button.
    */
    Button* getNextElementsButton();

protected:
    enum
    {
        MULTIPLE_ELEMENT_SELECTOR_NEXT_ELEMENT_BUTTON = -3,
        MULTIPLE_ELEMENT_SELECTOR_PREVIOUS_ELEMENT_BUTTON,
        MULTIPLE_ELEMENT_SELECTOR_NO_ELEMENT
    };

    std::vector<SYS::String> mValues; //!< \brief Contains all the string elements that are in the combobox

    /** \brief The actual overed element.
    If it's >= 0, it's a selector value element, else it's a speial case.
    See implementation : can be NO_ELEMENT, PREVIOUS_ELEMENT_BUTTON or NEXT_ELEMENT_BUTTON
    */
    int mActualOveredElement;

    Button* mPreviousElementsButton;

    Button* mNextElementsButton;
};

} // namespace UI
} // namespace XE

#endif