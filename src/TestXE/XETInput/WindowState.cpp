#include "WindowState.hpp"

#include <memory>
#include <iostream>

void WindowState::createFrameListener(void)
{

}

WindowState::WindowState(XE::XEngine& engine, bool replace)
	: XE::XEState(engine, replace)
{
	XE::LogManager::getSingleton().logMessage("InitState - Initialization");

	//SetResource();

	//--------------------------------------------------------
	//------------------ Controller -------------------------------
	//--------------------------------------------------------
	//one controller is always needed
	//std::unique_ptr<XE::Controller> controller = std::unique_ptr<XE::Controller>(new XE::Controller(0, &engine)); //creates camera
	//engine.getCtrlMgr().addController(std::move(controller));


	//mStateData->mUIStateManager.addUIState(mStateData->mUIStateManager.build <UI::UIInitGame>(UI::UISI_InitGame, controller, true));
	//Select Char
	//XE::CharEntity mChara(1, controller->getStateData()->mScene);
	//controller->getStateData()->mScene->addGameEntity(mChara);
	//controller->setCharEntity(mChara);
	//controller->getView().mCamera->setStyle(CA_CHARACTER);

//###	controller->getActionMap()[InputCmd::NavEnter] = XE::Action(XE::Keyboard::Return, XE::Action::PressOnce);
	//###	controller->getCallBackSystem().connect(InputCmd::CamRotate, std::bind(&Controller::updateCameraGoal, this));

	//lNameOfResourceGroup = "Init";
	//{
	//	XE::Entity* test = mStateData->mScene->getSceneMgr()->createEntity("test", "Geoset_0_1_tex_1.mesh", lNameOfResourceGroup);
	//	XE::SceneNode* lNode = mStateData->mScene->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	//	//		
	//	lNode->attachObject(test);

	//	lNode->scale(0.5, 0.5, 0.5);
	//	lNode->rotate(XE::Quaternion(XE::Degree(90), Ogre::Vector3::UNIT_X));

	//	// create a floor mesh resource
	//	XE::MeshManager::getSingleton().createPlane("floor", lNameOfResourceGroup,
	//		XE::Plane(Ogre::Vector3::UNIT_Y, -1), 250, 250, 25, 25, true, 1, 15, 15, Ogre::Vector3::UNIT_Z);

	//	// create a floor entity, give it a material, and place it at the origin
	//	XE::Entity* floor = mStateData->mScene->getSceneMgr()->createEntity("Floor", "floor", lNameOfResourceGroup);
	//	floor->setMaterialName("Examples/Rockwall", lNameOfResourceGroup);
	//	floor->setCastShadows(false);
	//	mStateData->mScene->getSceneMgr()->getRootSceneNode()->attachObject(floor);
	//}

	//	controller->getView().mCamera->setPivotPosition(XE::Vector3f(0, 1, 0)); //fixed camera

	XE::LogManager::getSingleton().logMessage("InitState - Initialized");
}

WindowState::~WindowState()
{

}

void WindowState::SetResource(){

	XE::ConfigFile cf;
	cf.load("E:/Projekte/Src Game/_Engine/XEngine/build/VS2010/XEngine/XEALL/Debug/resources.cfg", "\t:=", true);

	XE::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String secName, typeName, archName;
	Ogre::String sec, type, arch;

	// go through all specified resource groups
	while (seci.hasMoreElements())
	{
		sec = seci.peekNextKey();
		XE::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		XE::ConfigFile::SettingsMultiMap::iterator i;

		// go through all resource paths
		for (i = settings->begin(); i != settings->end(); i++)
		{
			type = i->first;
			arch = i->second;

			//#if XE_PLATFORM == XE_PLATFORM_APPLE || XE_PLATFORM == XE_PLATFORM_APPLE_IOS
			//				// OS X does not set the working directory relative to the app,
			//				// In order to make things portable on OS X we need to provide
			//				// the loading with it's own bundle path location
			//				if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
			//					arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
			//#endif
			XE::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}


	lNameOfResourceGroup = "General";
	{
		XE::ResourceGroupManager& lRgMgr = XE::ResourceGroupManager::getSingleton();

		lRgMgr.initialiseResourceGroup(lNameOfResourceGroup);
		lRgMgr.loadResourceGroup(lNameOfResourceGroup);

		// Create XE_NEW factory
		//XE::AL::SoundFactory* mOgreOggSoundFactory = XE_NEW_T(XE::AL::SoundFactory, MEMCATEGORY_GENERAL)();
		//mStateData->mRoot->addMovableObjectFactory(mOgreOggSoundFactory, true);

		//XE::AL::SoundManager* mOgreOggSoundManager = XE_NEW_T(XE::AL::SoundManager, MEMCATEGORY_GENERAL)();

		//if (XE::AL::SoundManager::getSingletonPtr()->init("",100,100,mStateData->mScene->getSceneMgr()))
		//{
		//	// Create a streamed sound, no looping, no prebuffering
		//	if (XE::AL::SoundManager::getSingletonPtr()->createSound("Sound1", "electricspark.ogg", false, false, false,mStateData->mScene->getSceneMgr()) )
		//	{
		//		
		//	}
		//}

		//geladene Materialien abfragen
		/*XE::ResourceManager::ResourceMapIterator materialIterator = XE::MaterialManager::getSingleton().getResourceIterator();
		while (materialIterator.hasMoreElements())
		{
		std::cout << "MaterialLoaded:" << (static_cast<XE::MaterialPtr>(materialIterator.peekNextValue()))->getName() << std::endl;
		materialIterator.moveNext();
		} */
	}

	//do this after long loading Times!
	//KH m_engine->getRoot()->clearEventTimes();
}

void WindowState::update(float deltaTime)
{
	//window.setMouseCursorVisible(false); // Hide cursor

	if (!m_breaked)
	{
		//	if(mStateData->mUIStateMgr->running())
		//		mStateData->mUIStateMgr->update();//update UI States

		
		//	XE::WindowEventUtilities::messagePump(); //dont use it or .net wrapper crash!
	}
}

void WindowState::cleanup()
{
	// Let's cleanup!
	{
		//mStateData->mUIManager.destroyScreen("WorldState");

		XE::ResourceGroupManager& lRgMgr = XE::ResourceGroupManager::getSingleton();
		lRgMgr.destroyResourceGroup(lNameOfResourceGroup);
	}
}

