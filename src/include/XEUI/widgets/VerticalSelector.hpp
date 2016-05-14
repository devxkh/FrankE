#ifndef Gui3DVerticalSelector_H
#define Gui3DVerticalSelector_H

#include <XESystem/XEMemory/XEMemoryPrerequisites.hpp>
#include <XEUI/Widgets/MultipleElementsSelector.hpp>

namespace XE {
namespace UI {

	class Caption;

/*! class. VerticalSelector
    desc.
        An abstract class for all vertical selector such as Listbox or Combobox.
*/
class VerticalSelector : public MultipleElementsSelector
{
public:
    VerticalSelector(Uint32 id,
					 Float x, 
                     Float y,
                     size_t width,
                     size_t height,
                     const SYS::vector<SYS::String>::type& items,
                     unsigned int nbDisplayedElements,
                     PanelContainer* parentContainer);
    
    ~VerticalSelector();

    Math::Vector2f getPosition();

    void setPosition(int left, int top);
    
    void setSize(int width, int height);
    
protected:
    std::vector<Caption*> mCaptions; //!< \brief Contains the displayed caption of the combobox

    unsigned int mNumTopVisibleElement; //!< \brief Number of the top element that is shown

    unsigned int mMaxNumberOfVisibleElements; //!< \brief Number of elements that can be seen in the selector

    /** \brief Callback for allElementsGoTop method 
    */
    bool allElementsGoTopCallback(PanelElement*);

    /** \brief Callback for allElementsGoDown method
    */
    bool allElementsGoDownCallback(PanelElement*);

    /** \brief Visibles elements go top, then the down hidding elements
    are started to be seen
    */
    void allElementsGoTop();

    /** \brief Visibles elements go down, then the top hidding elements
    are started to be seen
    */
    void allElementsGoDown();
};

} // namespace UI
} // namespace XE

#endif