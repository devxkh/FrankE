#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <XEScene/XESceneNode.hpp>
#include <XEMath/Vectors/Vector3.hpp>

#include <XEGraphics.hpp>


// caption Text ! ..........
// http://www.ogre3d.org/forums/viewtopic.php?f=11&t=59984&start=325
//http://www.ogre3d.org/forums/viewtopic.php?f=11&t=59984&start=450#p429016

// BFG Editor
// http://www.ogre3d.org/forums/viewtopic.php?f=11&t=59984&start=525#p437220

//Sprite Rotation
// http://www.ogre3d.org/forums/viewtopic.php?f=11&t=59984&start=550#p438323

namespace XE {
namespace UI {

class HealthBar
{
public:
	HealthBar(XE::XE_G::Silverback* silverback,SM::SceneNode* node, Math::Vector3f offset);

	void setValue(XE::Float percent); // 0 - 1
	void setVisible(bool value);
	bool isVisible() { return m_bVisible; };

private:
	Float						m_rValue;
	bool						m_bVisible;
	Math::Vector2f				m_pMaxSize;

	SM::SceneNode*				m_pSceneNode; 

	XE_G::ScreenRenderable*		m_pScreen;
	XE_G::Layer*				m_pOverLayer;
	XE_G::Layer*				m_pUnderLayer;
	XE_G::Rectangle*			m_pGrid;
	XE_G::Rectangle*			m_pColour;
	XE_G::Rectangle*			m_pBlack;
};

} // namespace UI
} //namespace XE

#endif//HEALTHBAR_H