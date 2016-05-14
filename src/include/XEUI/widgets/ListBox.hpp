
#ifndef Gui3DListbox_H
#define Gui3DListbox_H

#include <XEUI/Widgets/VerticalSelector.hpp>

namespace XE {
namespace UI {

/** class. Listbox
    desc.
        A Listbox which allows the user to make multiple choices.
*/
class Listbox : public VerticalSelector
{
public:
    /** \brief Use Panel::makeListbox
    */
    Listbox(Uint32 id,
			Float x, 
            Float y,
            size_t width,
            size_t height,
            const SYS::vector<SYS::String>::type& items,
            unsigned int nbDisplayedElements,
            PanelContainer* parentContainer);
    
    /** \brief Use Panel::destroyListbox
    */
    ~Listbox();

   /* void injectKeyPressed(const OIS::KeyEvent& evt);

    void injectKeyReleased(const OIS::KeyEvent& evt);

    void injectKeys(std::vector<OIS::KeyCode>& keys);
*/
    void pointSelection(const Math::Vector2f& point);

    bool isOver(const Math::Vector2f& pos);

    void setCurrentValue(SYS::String& itemName);

    void setCurrentValues(SYS::vector<SYS::String>::type& itemsName);

    SYS::vector<SYS::String>::type getValues();

    void setFocus(bool hasFocus);

    void highlight();

protected:
    bool addedMode; //!< \brief The Listbox will add elements to previous selected elements

	SYS::map<int, bool>::type mSelectedElements;

    void _actualize();
};

} // namespace UI
} // namespace XE

#endif