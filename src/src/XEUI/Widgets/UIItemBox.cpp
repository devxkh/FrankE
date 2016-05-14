#include <XEUI/Widgets/UIItemBox.hpp>

namespace XE {
namespace UI {

Signal::SignalID ItemBox::OnTriggered = 0;

ItemBox::ItemBox(XEUI* pXEUI, ITEM_ID id, SYS::String caption,  SYS::String baseImage,  SYS::String hoverImage)
	: mItemBar(NULL)
	,UIElement(id)
{
	if(!pXEUI) return;
	m_vImageOffset = Math::Vector2f(23,21);
	m_vCaptionOffset = Math::Vector2f(23, 80);
	m_vCaptionSize = Math::Vector2f(205, 30);

	m_bEnabled = true;
	m_bHovered = false;

	m_sBaseImage = baseImage;
	m_sHoverImage = hoverImage;
	m_ID = id;

	m_pScreen = pXEUI->getScreen("WorldState");
	m_pLayer = pXEUI->getLayerScreen(m_pScreen, "ItemBar");

	// background / encapsulation
	m_pBackground = m_pLayer->createRectangle(Math::Vector2f(0,0), Math::Vector2f(250, 175));
	m_pBackground->background_image("itembox");
	
	// item image
	m_pImage = m_pLayer->createRectangle(m_vImageOffset, Math::Vector2f(205, 133));
	m_pImage->background_image(baseImage);

	// disabled overlay
	m_pDisabled = m_pLayer->createRectangle(m_vImageOffset, Math::Vector2f(205, 133));
	m_pDisabled->no_background();

	// caption
	m_pCaption = m_pLayer->createCaption(14, m_vCaptionOffset.x, m_vCaptionOffset.y, m_sCaption);
	m_pCaption->size(m_vCaptionSize.x, m_vCaptionSize.y);
	m_pCaption->align(XE_G::TextAlign_Centre);
	m_pCaption->vertical_align(XE_G::VerticalAlign_Middle);
	m_pCaption->background(XE_G::ColourValue(0.6f,0.6f,0.6f,0.4f));

	setCaption(caption);
}


void ItemBox::setPosition(Math::Vector2f pos)
{
	m_vPosition = pos;
	m_pBackground->position(pos);
	m_pDisabled->position(pos + m_vImageOffset);
	m_pImage->position(pos + m_vImageOffset);
	
	// no caption move have to recreate
	m_pLayer->destroyCaption(m_pCaption);
	m_pCaption = m_pLayer->createCaption(14, pos.x + m_vCaptionOffset.x, pos.y + m_vCaptionOffset.y, m_sCaption);
	m_pCaption->size(m_vCaptionSize.x, m_vCaptionSize.y);
	m_pCaption->align(XE_G::TextAlign_Centre);
	m_pCaption->vertical_align(XE_G::VerticalAlign_Middle);
	m_pCaption->background(XE_G::ColourValue(0.6f,0.6f,0.6f,0.4f));
}

Math::Vector2f ItemBox::getPosition()
{
	return m_vPosition;
}

void ItemBox::setEnabled(bool value)
{
	m_bEnabled = value;
	if(value)
		m_pDisabled->no_background();
	else
		m_pDisabled->background_colour(XE_G::ColourValue(0.4f, 0.4f, 0.4f, 0.4f));
}

bool ItemBox::isOver(const Math::Vector2f& pos)
{
	if(!m_bEnabled)
		return false;

	bool result = m_pImage->intersects(pos);
	
	if(result && !m_bHovered)
	{
		m_pImage->background_image(m_sHoverImage);
		m_pCaption->background(XE_G::ColourValue(0.6f,0.6f,0.6f,0.6f));
	}
	else if(!result && m_bHovered)
	{
		m_pImage->background_image(m_sBaseImage);
		m_pCaption->background(XE_G::ColourValue(0.6f,0.6f,0.6f,0.4f));
	}

	m_bHovered = result;
	return result;
}

void ItemBox::setSelected(bool value)
{
	if(value)
	{
		m_pImage->border(3, XE_G::ColourValue(0,0.7f,0,1));

		//KH
		GetSignals().Emit( OnTriggered );
	}
	else
		m_pImage->border(0, XE_G::ColourValue(0,0.7f,0,0));
}

void  ItemBox::setCaption( SYS::String str)
{
	m_sCaption = str;
	m_pCaption->text(m_sCaption);
}

} // namespace UI
} // namespace XE