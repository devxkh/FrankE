#ifndef ITEMBOX_H
#define ITEMBOX_H

#include <XEUI/XEUI.hpp>
#include <XEUI/Widgets/UIElement.hpp>

#include <functional>

namespace XE {
namespace UI {

//predefinition
enum ITEM_ID;
class ItemBar;

class ItemBox : public UIElement
{
public:
	/// @brief Function type of listeners associated with Event
	///
	typedef std::function< void(const ItemBox&) >		Listener;

	ItemBox(XEUI* pXEUI, ITEM_ID id, SYS::String caption,  SYS::String baseImage,  SYS::String hoverImage);

	void			setPosition(Math::Vector2f pos);
	Math::Vector2f	getPosition();
	void			setCaption( SYS::String str);

	ITEM_ID			getItemID() { return m_ID; };
	void			setSelected(bool value);
	
	bool			isOver(const Math::Vector2f& pos);
	bool			isEnabled() { return m_bEnabled; };
	void			setEnabled(bool value);

	/*void connect(const Listener& listener)
	{
		 mListeners.push_back(listener);
	}*/
	static Signal::SignalID OnTriggered; //!< Fired when mouse entered widget.

private:

	// Container type
	typedef std::vector<const ItemBox*>	ListenerVector;
	ListenerVector mListeners;
	ItemBar* mItemBar;

	XE_G::Screen*	m_pScreen;
	XE_G::Layer*		m_pLayer;

	XE_G::Caption*	m_pCaption;
	XE_G::Rectangle* m_pBackground;
	XE_G::Rectangle* m_pImage;
	XE_G::Rectangle* m_pDisabled;

	bool			m_bEnabled;
	bool			m_bHovered;

	 SYS::String	m_sBaseImage;
	 SYS::String	m_sHoverImage;
	Math::Vector2f	m_vPosition;
	Math::Vector2f	m_vImageOffset;
	Math::Vector2f	m_vCaptionOffset;
	Math::Vector2f	m_vCaptionSize;

	int				m_iCapacity;

	std::string		m_sCaption;
	ITEM_ID			m_ID;
};

} // namespace UI
} // namespace XE

#endif // ITEMBOX_H