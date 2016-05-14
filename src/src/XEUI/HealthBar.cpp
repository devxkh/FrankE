#include <XEUI/HealthBar.hpp>

namespace XE {
namespace UI {

HealthBar::HealthBar(XE::XE_G::Silverback* silverback,SM::SceneNode* node, Math::Vector3f offset)
{
	m_pSceneNode = node->createChildSceneNode(Math::Vector3f(offset));
	if(!m_pSceneNode) return;
	m_pMaxSize = Math::Vector2f(100, 10);

	m_pScreen = silverback->createScreenRenderable(Math::Vector2f(1, 0), "world.gorilla");
	m_pSceneNode->attachObject(m_pScreen);
	m_pUnderLayer = m_pScreen->createLayer();
	m_pOverLayer = m_pScreen->createLayer();
	m_pGrid = m_pOverLayer->createRectangle(Math::Vector2f::ZERO, m_pMaxSize);
	m_pGrid->background_image("healthbar_grid");
	m_pColour = m_pUnderLayer->createRectangle(Math::Vector2f::ZERO, m_pMaxSize);
	m_pColour->background_image("healthbar_colour");
	m_pBlack = 0;
	setValue(1);
	setVisible(true);
}

void HealthBar::setValue(XE::Float percent)
{
	m_rValue = (percent > 1) ? 1 : (percent < 0) ? 0 : percent;
	if(m_pBlack)
		m_pUnderLayer->destroyRectangle(m_pBlack);
	m_pBlack = m_pUnderLayer->createRectangle(Math::Vector2f(m_pMaxSize.x * m_rValue, 0), Math::Vector2f(m_pMaxSize.x * (1 - m_rValue), m_pMaxSize.y));
	m_pBlack->background_image("healthbar_black");
}

void HealthBar::setVisible(bool value)
{
	m_bVisible = value;
	m_pScreen->setVisible(m_bVisible);
	m_pUnderLayer->setVisible(m_bVisible);
}

} // namespace UI
} // namespace XE