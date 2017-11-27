#include <XERenderer/LightRenderable.hpp>


#include <XEDAL/Objects/FBEngineTypes_generated.h>
#include <XERenderer/OgreSceneManager.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Scene.hpp>
#include <ThirdParty/plog/Log.h>

#include <XERenderer/Editor/LightVisualHelper.hpp>

#include <Ogre/Components/Hlms/Pbs/include/InstantRadiosity/OgreInstantRadiosity.h>
#include "OgreForward3D.h"

namespace XE
{
	LightRenderable::LightRenderable(GraphicsManager& gmanager, Scene& scene, const void* fbData)
		: m_GraphicsManager(gmanager)
		, m_Scene(scene)
		, m_LightAxisNode(0)
		, m_light(0)
		, mInstantRadiosity(0)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, fbData]() {

			m_light = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createLight();
			Ogre::SceneNode *rootNode = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode();

			m_LightAxisNode = rootNode->createChildSceneNode();

			//mLightAxisNode->setPosition(0,30,0);
			m_LightAxisNode->attachObject(m_light);
			//	mLightAxisNode->setScale(Ogre::Vector3(0.12f, 0.12f, 0.12f));

			_setLightData(fbData);
		});
	}
	
	LightRenderable::~LightRenderable()
	{
		m_GraphicsManager.getIntoRendererQueue().push([this]() {
			m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->destroyLight(m_light);
			m_LightAxisNode->getParentSceneNode()->removeAndDestroyChild(m_LightAxisNode);
			m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->destroySceneNode(m_LightAxisNode);
		});
	}

	void LightRenderable::setPosition(const Ogre::Vector3& pos)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, pos]() {
			m_LightAxisNode->setPosition(pos);
		});
	}

	void LightRenderable::setLightData(const void* fbData)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, fbData]() {

			
			_setLightData(fbData);
		});
	}

	void LightRenderable::_setLightData(const void* fbData)
	{
		const XFBType::Light* lightData = (const XFBType::Light*)fbData;

		LOG(plog::info) << "LightRenderable:fbData";

		if (lightData->colourDiffuse())
			LOG(plog::info) << "colourDiffuse:" << lightData->colourDiffuse()->r() << "," << lightData->colourDiffuse()->g() << "," << lightData->colourDiffuse()->b() << "," << lightData->colourDiffuse()->a();

		if (lightData->colourSpecular())
			LOG(plog::info) << "colourSpecular:" << lightData->colourSpecular()->r() << "," << lightData->colourSpecular()->g() << "," << lightData->colourSpecular()->b() << "," << lightData->colourSpecular()->a();

		if (lightData->directionVector())
			LOG(plog::info) << "directionVector:" << lightData->directionVector()->x() << "," << lightData->directionVector()->y() << "," << lightData->directionVector()->z();

		if (lightData->attenuation())
			LOG(plog::info) << "attenuation:" << lightData->attenuation()->range() << "," << lightData->attenuation()->constant() << "," << lightData->attenuation()->linear() << "," << lightData->attenuation()->quadratic();


		LOG(plog::info) << "lightType:" << lightData->lightType();
		LOG(plog::info) << "powerScale:" << lightData->powerScale();

		m_light->setPowerScale(lightData->powerScale()); //Ogre::Math::PI);// 1.0f);
		m_light->setCastShadows(lightData->castShadows());

	//	m_light->setAttenuationBasedOnRadius(10.0f, 0.01f);
		auto lightType = (Ogre::Light::LightTypes)lightData->lightType();

		if (lightData->colourDiffuse())
		{
			auto diffuse = Ogre::ColourValue(lightData->colourDiffuse()->r(), lightData->colourDiffuse()->g(), lightData->colourDiffuse()->b(), lightData->colourDiffuse()->a());
			m_light->setDiffuseColour(diffuse);// Ogre::ColourValue::White);
		}

		if (lightData->colourSpecular())
		{
			auto specular = Ogre::ColourValue(lightData->colourSpecular()->r(), lightData->colourSpecular()->g(), lightData->colourSpecular()->b(), lightData->colourSpecular()->a());
			m_light->setSpecularColour(specular); //Ogre::ColourValue::White);
		}

		m_light->setType(lightType); // Ogre::Light::LT_DIRECTIONAL);

		if (lightData->directionVector())
			m_light->setDirection(Ogre::Vector3(lightData->directionVector()->x(), lightData->directionVector()->y(), lightData->directionVector()->z()).normalisedCopy());
		
		//m_light->setDirection(Ogre::Vector3(-0.505, 3.4, 5.423867).normalisedCopy());

		if (lightData->attenuation())
			m_light->setAttenuation(lightData->attenuation()->range(),lightData->attenuation()->constant(),lightData->attenuation()->linear(),lightData->attenuation()->quadratic());
		
		if (lightType == Ogre::Light::LightTypes::LT_SPOTLIGHT)
		{
		/*	m_light->setSpotlightInnerAngle(Ogre::Radian(179));
			m_light->setSpotlightOuterAngle(Ogre::Radian(179));*/
		//	m_light->setAttenuationBasedOnRadius(1000,0.1);

			m_light->setSpotlightRange(Ogre::Degree(65), Ogre::Degree(90), 1);
		}


	//	m_light->setLightMask();
	//	m_light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50), 0.5);

		//old VEX directional light direction -> 0,-0.3,-0.8
		//m_light->setType(Ogre::Light::LT_SPOTLIGHT);
		//m_light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());
		//m_LightAxisNode->setPosition(Ogre::Vector3(-0.505, 3.4, 5.423867));
		//m_light->setPowerScale(100);
		//m_light->setAttenuation(23.0f, 0.5f, 0.0f, 0.5f);

	///	mCLightVisualHelper = new CLightVisualHelper(m_Scene, m_light);
	//	mCLightVisualHelper->Show(true);
		//light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());
		//light->setDirection(Ogre::Vector3(0, -1, 0));

		/*	Ogre::ManualObject * manualObject = new Ogre::ManualObject(10, &m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), m_Scene.getOgreSceneManager().__OgreSceneMgrPtr);

		manualObject->begin("BaseWhite", Ogre::OperationType::OT_LINE_LIST);

		manualObject->position(0, 30, 0);
		manualObject->position(0.0f, 1.0f, 0.0f);
		manualObject->line(0, 1);

		manualObject->end();

		Ogre::SceneNode *sceneNodeLines = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
		sceneNodeLines->attachObject(manualObject);*/

		/*m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f),
		Ogre::ColourValue(0, 0, 0),
		-m_light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);*/

		//----------------------------- InstantRadiosity
		if (lightData->useInstantRadiosity())
		{
			if (!mInstantRadiosity)
			{
				Ogre::HlmsManager *hlmsManager = m_Scene.getGraphicsManager().getRoot()->getHlmsManager();
				mInstantRadiosity = new Ogre::InstantRadiosity(m_Scene.getOgreSceneManager().__OgreSceneMgrPtr, hlmsManager);
				mInstantRadiosity->mVplThreshold = 0.0005f;

				//Guide where to shoot the rays for directional lights the 3 windows + the
				//hole in the ceiling). We use a sphere radius of 30 to ensure when the directional
				//light's dir is towards -X, we actually hit walls (instead of going through these
				//walls and generating incorrect results).
				mInstantRadiosity->mAoI.push_back(Ogre::InstantRadiosity::AreaOfInterest(
					Ogre::Aabb(Ogre::Vector3(-0.746887f, 7.543859f, 5.499001f),
						Ogre::Vector3(2.876101f, 2.716137f, 6.059607f) * 0.5f), 30.0f));
				mInstantRadiosity->mAoI.push_back(Ogre::InstantRadiosity::AreaOfInterest(
					Ogre::Aabb(Ogre::Vector3(-6.26f, 3.969576f, 6.628003f),
						Ogre::Vector3(1.673888f, 6.04f, 1.3284f) * 0.5f), 30.0f));
				mInstantRadiosity->mAoI.push_back(Ogre::InstantRadiosity::AreaOfInterest(
					Ogre::Aabb(Ogre::Vector3(-6.26f, 3.969576f, 3.083399f),
						Ogre::Vector3(1.673888f, 6.04f, 1.3284f) * 0.5f), 30.0f));
				mInstantRadiosity->mAoI.push_back(Ogre::InstantRadiosity::AreaOfInterest(
					Ogre::Aabb(Ogre::Vector3(-6.26f, 3.969576f, -0.415852f),
						Ogre::Vector3(1.673888f, 6.04f, 1.3284f) * 0.5f), 30.0f));

				mInstantRadiosity->build();

				m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->setForwardClustered(true, 16, 8, 24, 96, 2, 50);
				//Required by InstantRadiosity
				m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getForwardPlus()->setEnableVpls(true);
			}
			else
			{
				mInstantRadiosity->mVplThreshold = lightData->IRVplThreshold();
			}
		}
		else {

			delete mInstantRadiosity;
			mInstantRadiosity = 0;
		}
	}
}