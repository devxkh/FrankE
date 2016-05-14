#ifndef Gui3DCombobox_H
#define Gui3DCombobox_H

#include <vector>

//#include <XEGraphics/Gorilla.h>
//#include "Gui3DContainer.h"
#include <XEUI/Widgets/VerticalSelector.hpp>
//
//#include "Gui3DButton.h"
//#include "Gui3DCaption.h"
//
//#include "Gui3DMemberFunction.h"

namespace XE {
namespace UI {

/*! class. Combobox
    desc.
        A Combobox which allows the user to make one choice.
*/
class Combobox : public VerticalSelector
{
public:
    /** \brief Use Panel::makeCombobox
    */
    Combobox(Uint32 id,
			 Float x, 
             Float y,
             size_t width,
             size_t height,
             const SYS::vector<SYS::String>::type& items,
             unsigned int nbDisplayedElements,
             PanelContainer* parentContainer);
    
    /** \brief Use Panel::deleteCombobox
    */
    ~Combobox();

    //void injectKeyPressed(const OIS::KeyEvent& evt);

    //void injectKeyReleased(const OIS::KeyEvent& evt);

    //void injectKeys(std::vector<OIS::KeyCode>& keys);

    void pointSelection(const Math::Vector2f& point);
    
    bool isOver(const Math::Vector2f& pos);

    /** \brief Return the value of the combobox
    */
    SYS::String getValue();

    /** \brief Set the current value of this combobox. If the element 
    isn't found, nothing is changed.
    */
    void setCurrentValue(SYS::String& itemName);

    void highlight();
    
protected:
    unsigned int mActualSelectedElement; //!< \brief The actual selected element

    void _actualize();
};

} // namespace UI
} //namespace XE
#endif