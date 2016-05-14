#include <XEEditor/Editor.hpp>

#include <XEUI/Widgets/OgreConsoleForGorilla.hpp>
//#include <EditorI/EditorCommands.h>

//#include "E:/Projekte/Src Game/_Engine/XEngine/TestXE/XETRecastNav/ControllerState.h"
//#include "E:/Projekte/Src Game/_Engine/XEngine/TestXE/XETCharacter/CharacterState.h"

#include <XEState.h>
#include <Ogre/OgreMain/include/OgreTextureManager.h>
#include <XEEditor/Event/ConvertEvent.hpp>

namespace EI {

	Editor::Editor():
		m_engine(nullptr),
		//todo ####################		m_console(nullptr),
		mEditorCommand(nullptr)
	{

	}

	unsigned char* Editor::consoleCmd(const char* command, unsigned char* data, int len)
	{
		Ogre::String str(command);

		std::cout << "consoleCmd: " << str << std::endl;

		//todo ####################		m_console->SetPrompt(str);


		//XE::StateData* test = engine->getCurrentState()->getStateData();
		//test->mScene->createCharEntity(id);

		return 0;
	}

	bool Editor::moveToState(const char* stateName)
	{
		return false;
	}

	//
	//void Editor::test(sf::String str, std::function<void()> fkttest)
	//{
	//	command_map[str] = std::move(fkttest);
	//}

	int Editor::pushEvent(const sfEvent& event)
	{
		sf::Event SFMLEvent;

	
		SFMLEvent = convertEvent(event);
		
		std::cout << "pushEvent:" << SFMLEvent.type << "#" << event.type << std::endl;
	
	/*	XE::Controller& controller = m_engine->getCtrlMgr().getController(0);
		controller.pushEvent(SFMLEvent);*/

		
		return SFMLEvent.key.code;
	}
	
	//todo global = bad
	Ogre::TexturePtr _textureRenderTarget;

	void* Editor::InitState(const char* stateName, int width, int height)
	{

		//return true;
		//XE::LogManager::getSingleton().logMessage("TecnoFreak: Initialising Ogre Viewport");

		//todo ressfile per parameter
		m_engine = new XE::XEngine("E:/Projekte/coop/XEngine/data/Test/XETUI/resources.cfg", "", true);

		std::cout << "initState run";

		
		//XE::Controller& controller = m_engine->getCtrlMgr().getController(0);
	//todo ####################	m_console = controller->getConsole();

		//http://stackoverflow.com/questions/2397160/how-to-get-a-windowless-application-in-ogre

		/*m_window = m_root->initialise(true, "App");
		m_window->setHidden(true);
		Ogre::WindowEventUtilities::messagePump(); */// Force the window to be hidden (necessary under Ubuntu for my case)

	//	m_camera = m_sceneMgr->createCamera("Cam");



		//Ogre::RenderTexture* m_tex = rtt_texture->getBuffer()->getRenderTarget();
		//Ogre::Viewport* vp = controller->getView().mViewport; // m_tex->addViewport(controller->getView().mViewport); //m_camera);
		//vp->setClearEveryFrame(true);
		//vp->setBackgroundColour(Ogre::ColourValue::Black);
		//vp->setOverlaysEnabled(false);
		//m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

		//controller->getView().
		// Create Render Target
		//Ogre::RenderTarget * _renderTarget = m_engine->getRoot()->getRenderSystem()->getRenderTarget("RenderWindow");
		
		_textureRenderTarget = m_engine->getGraphicsManager().createTextureRenderTarget(width, height);
		Ogre::RenderTarget* _renderTarget = _textureRenderTarget->getBuffer()->getRenderTarget();
	//	m_engine->getViewMgr().createViewport(*controller, nullptr, _renderTarget);

		//m_engine->getViewMgr().UpdateViews();
		// Set D3DImage Back Buffer to Render Target
		//void* surface;
		//_renderTarget->getCustomAttribute("DDBACKBUFFER", surface);
		
		LPVOID bbSurf;
		_renderTarget->getCustomAttribute("DDBACKBUFFER", &bbSurf);

	//## ----todo	m_engine->run(m_engine->build<EditorState>(m_engine, true));
		
		//activate realtime input -- standard mäßig true !! nicht notwendig .. entfernen 
		//sf::Event SFMLEvent;
		//SFMLEvent.type = sf::Event::EventType::GainedFocus;
		//controller->pushEvent(SFMLEvent);

		return bbSurf;
		//Game game;
		//Help helper;
		//command_map["quit"] = [] { exit(); };
		//command_map["play"] = [&] { game.play(); };
		//command_map["help"] = [&] { helper.help(); };

	//	test("", std::bind(&EditorCommand::createObject, std::function<void(std::string)>(std::bind(&EditorCommand::createObject, &mEditorCommand, std::placeholders::_1))));

	//	test("", std::bind(&EditorCommand::createObject, mEditorCommand));

	//	test("", [&] { mEditorCommand->updateObject(); });
	//	test("", [] { mEditorCommand->updateObject; });
		//test("", [&] { mEditorCommand->updateObject(); });

		/*m_console->addCommand("create", &EditorCommand::createObject);
		m_console->addCommand("update", mEditorCommand->updateObject);
		m_console->addCommand("delete", mEditorCommand->deleteObject);*/
	}

	void Editor::renderTargetSize(const char* rtName, Ogre::Real x, Ogre::Real y)
	{
		std::cout << "renderTargetSize x:" << x << ",y:" << y;

		_textureRenderTarget->setWidth(x);
		_textureRenderTarget->setHeight(y);
	//	XE::Controller* controller = m_engine->getCtrlMgr().getController(0);
		//controller->getView().mViewport->setDimensions(0, 0, 10, 10);
	}
		

} // ns EI