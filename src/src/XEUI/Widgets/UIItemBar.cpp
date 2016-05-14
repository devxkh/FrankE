#include <XEUI/Widgets/UIItemBar.hpp>

#include <XEUI/Widgets/UIItemBox.hpp>

namespace XE {
namespace UI {

Signal::SignalID ItemBar::OnContinue = 0;
Signal::SignalID ItemBar::OnBack = 0;
Signal::SignalID ItemBar::OnClose = 0;
Signal::SignalID ItemBar::OnExit = 0;

ItemBar::ItemBar(XEUI* pXEUI,Uint32 id,Math::Vector2f& position)
	: UIElement(id)
{
	if(!pXEUI) return;
	XE_G::Screen* pScreen = pXEUI->getScreen("WorldState");
	m_pLayer = pXEUI->createLayerScreen(pScreen, "ItemBar");

	m_vPosition = position;// Math::Vector2f(0, pScreen->getHeight() - 300);
	m_iLeftIndex = 0;
	m_vItemOffset = Math::Vector2f(0, 50);

//	m_pBackground = m_pLayer->createRectangle(m_vPosition.x, m_vPosition.y, pScreen->getWidth(), 300);
//	m_pBackground->background_image("itembar");

	// special layer for scroll buttons so item buttons don't draw overtop
	/*XE_G::Layer* scrolllayer = pXEUI->createLayerScreen(pScreen, "ItemBarScroll");
	m_pScrollRight = scrolllayer->createRectangle(Math::Vector2f(pScreen->getWidth() - 100, m_vPosition.y + 110), Math::Vector2f(100, 175));
	m_pScrollRight->background_image("scrollright");

	m_pScrollLeft = scrolllayer->createRectangle(m_vPosition + Math::Vector2f(0,110), Math::Vector2f(100, 175));
	m_pScrollLeft->background_image("scrollleft");*/
}

void ItemBar::addItem(ItemBox* item)
{
	// add new item if an item with the same id doesnt exist
	if(!m_mItems[item->getItemID()])
	{
		m_mItems[item->getItemID()] = item;
		m_vOrderedItems.push_back(item);
		item->setPosition(m_vPosition + m_vItemOffset * (m_vOrderedItems.size()-1) + Math::Vector2f(95, 110));

		if(m_vOrderedItems.size() == 1)
		{
			item->setSelected(true);
			m_ItemSelected = item->getItemID();
		}
	}
}

ItemBox* ItemBar::getItem(ITEM_ID id)
{
	return m_mItems[id];
}

void ItemBar::setSelectedItem(ITEM_ID id)
{
	m_mItems[m_ItemSelected]->setSelected(false);
	m_mItems[id]->setSelected(true);
	m_ItemSelected = id;
}

bool ItemBar::mouseDown(unsigned int x, unsigned int y)
{
	GetSignals().Emit( OnContinue );

		// register item clicks and highlight selected item
	for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
		if(m_vOrderedItems[i]->isOver(Math::Vector2f(x,y)))
		{
			setSelectedItem(m_vOrderedItems[i]->getItemID());
			return false;
		}

	// prevent click through
	//if(m_pBackground->intersects(Math::Vector2f(x, y)))
	//	return false;
	return true;
}

bool ItemBar::mouseUp(unsigned int x, unsigned int y)
{

	// scroll items left
	//if(m_pScrollLeft->intersects(Math::Vector2f(x, y)))
	//{
	//	if(m_iLeftIndex < 0)
	//	{
	//		for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
	//			m_vOrderedItems[i]->setPosition(m_vOrderedItems[i]->getPosition() + Math::Vector2f(230, 0));
	//		++m_iLeftIndex;
	//	}
	//	return false;
	//}

	//// scroll items right
	//if(m_pScrollRight->intersects(Math::Vector2f(x, y)))
	//{
	//	if(((int)m_vOrderedItems.size()) - 1 + m_iLeftIndex > 0)
	//	{
	//		for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
	//			m_vOrderedItems[i]->setPosition(m_vOrderedItems[i]->getPosition() - Math::Vector2f(230, 0));
	//		--m_iLeftIndex;
	//	}
	//	return false;
	//}

	// register item clicks and highlight selected item
	for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
		if(m_vOrderedItems[i]->isOver(Math::Vector2f(x,y)))
		{
			setSelectedItem(m_vOrderedItems[i]->getItemID());
			return false;
		}


		// prevent clickthrough
	/*	if(m_pBackground->intersects(Math::Vector2f(x, y)))
		return false;*/
	return true;
}

void ItemBar::mouseMoved(unsigned int x, unsigned int y)
{
	// show hover image
	for(unsigned int i = 0; i < m_vOrderedItems.size(); i++)
		m_vOrderedItems[i]->isOver(Math::Vector2f(x,y));
}

} // namespace UI
} // namespace XE