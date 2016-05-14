#ifndef ITEMBAR_H
#define ITEMBAR_H

#include <XEOSConfig.hpp>
#include <XEUI/XEUI.hpp>
#include <XEUI/Widgets/UIElement.hpp>

#include <map>
#include <vector>

namespace XE {
namespace UI {

class ItemBox;


enum ITEM_ID {
	UNKNOWN = -1,
	BALL,
	SMALLBALL
};

class ItemBar : public UIElement
{
public:
	ItemBar(XEUI* pXEUI,Uint32 id,Math::Vector2f& position);
	
	// return true for clickthrough allowed, false to disallow clickthrough
	bool mouseDown(unsigned int x, unsigned int y);
	bool mouseUp(unsigned int x, unsigned int y);
	void mouseMoved(unsigned int x, unsigned int y);

	void		addItem(ItemBox* item);
	ItemBox*	getItem(ITEM_ID id);

	ITEM_ID		getSelectedItem() { return m_ItemSelected; };
	void		setSelectedItem(ITEM_ID id);

	static Signal::SignalID OnContinue; //!< Fired when mouse entered widget.
	static Signal::SignalID OnBack; //!< Fired when mouse left widget.
	static Signal::SignalID OnClose; //!< Fired when mouse moved over widget.
	static Signal::SignalID OnExit; //!< Fired when left button pressed.
		

private:
	XE_G::Layer*			m_pLayer;
	XE_G::Rectangle*		m_pBackground;

	XE_G::Rectangle*		m_pScrollRight;
	XE_G::Rectangle*		m_pScrollLeft;

	std::map<ITEM_ID, ItemBox*> m_mItems;
	std::vector<ItemBox*>		m_vOrderedItems;
	int							m_iLeftIndex;

	Math::Vector2f			m_vPosition;
	Math::Vector2f			m_vItemOffset;

	ITEM_ID					m_ItemSelected;
};

} // namespace UI
} // namespace XE

#endif //ITEMBAR_H