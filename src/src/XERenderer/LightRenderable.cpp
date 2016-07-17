#include <XERenderer/LightRenderable.hpp>


#include <XEDAL/Objects/FBEngineTypes_generated.h>
#include <XERenderer/OgreSceneManager.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XEngine/Scene.hpp>
#include <ThirdParty/plog/Log.h>

namespace XE
{
	LightRenderable::LightRenderable(GraphicsManager& gmanager, Scene& scene, const void* fbData)
		: m_GraphicsManager(gmanager)
		, m_Scene(scene)
		, m_LightAxisNode(0)
		, m_light(0)
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

		LOG(plog::info) << "lightType:" << lightData->lightType();
		LOG(plog::info) << "powerScale:" << lightData->powerScale();

		m_light->setPowerScale(lightData->powerScale()); //Ogre::Math::PI);// 1.0f);

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

		m_light->setType((Ogre::Light::LightTypes)lightData->lightType()); // Ogre::Light::LT_DIRECTIONAL);

		if (lightData->directionVector())
			m_light->setDirection(Ogre::Vector3(lightData->directionVector()->x(), lightData->directionVector()->y(), lightData->directionVector()->z()).normalisedCopy());

		//light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());
		//light->setDirection(Ogre::Vector3(0, -1, 0));

		/*	Ogre::ManualObject * manualObject = new Ogre::ManualObject(10, &m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), m_Scene.getOgreSceneManager().__OgreSceneMgrPtr);

		manualObject->begin("BaseWhite", Ogre::v1::RenderOperation::OT_LINE_LIST);

		manualObject->position(0, 30, 0);
		manualObject->position(0.0f, 1.0f, 0.0f);
		manualObject->line(0, 1);

		manualObject->end();

		Ogre::SceneNode *sceneNodeLines = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
		sceneNodeLines->attachObject(manualObject);*/

		/*m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f,
		Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f,
		-light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);*/
	}
}