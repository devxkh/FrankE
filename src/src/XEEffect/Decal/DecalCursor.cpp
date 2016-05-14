/**
* @file DecalCursor.cpp
* @author Jesse Wright - www.cutthroatstudios.com
* @date Created on 12/25/2007
* @date Last modified 5/19/2007
* @note Modified from Brocan's example on the Ogre forums
*/

#include "OgreSceneManager.h"
#include "OgreTextureManager.h"
#include "OgreSceneNode.h"
#include "OgreFrustum.h"
#include "OgreTextureUnitState.h"
#include "OgrePass.h"
#include "OgreTechnique.h"

#include <XEEffect/Decal/DecalCursor.hpp>

/**
* @brief The length of one meter in ogre units
* @todo Set this to something meaningful for your project!
*/
static const float METER_SCALE = 1.0f;

DecalCursor::DecalCursor(Ogre::SceneManager* man, Ogre::MaterialPtr terrainMat, const Ogre::Vector2& size,
	const std::string& tex)

	: m_bVisible(false), m_nodeProj(0), m_pass(0), m_frustProj(0), m_texState(0), m_sceneMgr(man),
	m_terrainMat(terrainMat), m_pos(Ogre::Vector3::ZERO), m_size(Ogre::Vector2::ZERO)
{
	init(size, tex);
}

DecalCursor::~DecalCursor()
{
	hide();

	// remove the decal pass
	if (m_pass)
	{
		m_terrainMat->getTechnique(0)->removePass(m_pass->getIndex());
		m_pass = 0;
	}

	// delete frustum
	m_nodeProj->detachAllObjects();
	delete m_frustProj;

	// destroy node
	m_nodeProj->getParentSceneNode()->removeAndDestroyChild(m_nodeProj);
}

void DecalCursor::init(const Ogre::Vector2& size, const std::string& tex)
{
	// create a new pass in the material to render the decal
	m_pass = m_terrainMat->getTechnique(0)->getPass("Decal");
	if (!m_pass)
	{
		Ogre::Technique* techPref = m_terrainMat->getTechnique(0);
		m_pass = techPref->createPass();
		m_pass->setName("Decal");
		//KH
		//m_pass->setLightingEnabled(false);
		//m_pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
		//m_pass->setDepthBias(2.5, 2.5);
		m_pass->setFog(true);
		m_pass->createTextureUnitState("Decal.png");
	}

	// init projective decal
	// set up the main decal projection frustum
//todo KH	m_frustProj = new Ogre::Frustum();
	m_nodeProj = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
	m_nodeProj->attachObject(m_frustProj);
	m_frustProj->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	m_nodeProj->setOrientation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X));

	/* Commented out for general use. If you are using mouse picking in your scene, set this to an unselectable flag otherwise you may find the frustum in your ray queries. */
	//m_frustProj->setQueryFlags(Sanguis::UNSELECTABLE);

	// set given values
	setSize(size);
	m_sTexName = tex;      // texture to apply

	// load the images for the decal and the filter
	Ogre::TextureManager::getSingleton().load(m_sTexName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 1);

	m_bVisible = false;
}

Ogre::Vector3 DecalCursor::getPosition() const
{
	return m_pos;
}

void DecalCursor::show()
{
	if (!m_bVisible)
	{
		m_bVisible = true;
		showTerrainDecal();
		setPosition(m_pos);

		m_frustProj->setVisible(true);
	}
}

void DecalCursor::hide()
{
	if (m_bVisible)
	{
		m_bVisible = false;
		hideTerrainDecal();
	}
}

void DecalCursor::setPosition(const Ogre::Vector3& pos)
{
	m_pos = pos;

	// Set the projection coming from some distance above the current position.
	m_nodeProj->setPosition(pos.x, pos.y + (10.0 * METER_SCALE), pos.z);
}

void DecalCursor::setSize(const Ogre::Vector2& size)
{
	if (m_size != size)
	{
		m_size = size;

		// update aspect ratio
#if OGRE_VERSION_MAJOR == 1 && OGRE_VERSION_MINOR <= 4
		m_frustProj->setAspectRatio(m_size.x / m_size.y);
#else
		m_frustProj->setOrthoWindow(m_size.x, m_size.y);
#endif

		// set fovy so that tan = 1, so 45 degrees
		m_frustProj->setFOVy(Ogre::Degree(45));

		// set near clip plane according to fovy:
		m_frustProj->setNearClipDistance(m_size.y);
	}
}

// Protected

void DecalCursor::showTerrainDecal()
{
	if (!m_texState)
	{
		// set up the decal's texture unit
		m_texState = m_pass->createTextureUnitState(m_sTexName);
		m_texState->setProjectiveTexturing(true, m_frustProj);
	//KH	m_texState->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
		//KH	m_texState->setTextureFiltering(Ogre::FO_POINT, Ogre::FO_LINEAR, Ogre::FO_NONE);
		m_texState->setAlphaOperation(Ogre::LBX_ADD);
	}
}

void DecalCursor::hideTerrainDecal()
{
	if (m_texState)
	{
		m_pass->removeTextureUnitState(m_pass->getTextureUnitStateIndex(m_texState));
		m_texState = 0;
	}
}