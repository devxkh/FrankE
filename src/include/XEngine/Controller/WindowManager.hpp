#ifndef __WINDOWMANAGER_HPP__
#define __WINDOWMANAGER_HPP__

#include <sfml/Window/Window.hpp>
#include <sfml/System/String.hpp>

#include <memory>

namespace XE {

	class Scene;
	class Controller;
	class XEngine;


	class WindowManager
	{

	public:

		WindowManager();
		~WindowManager();

		//void UpdateViews();
		sf::Window* createWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default);
		sf::Window* createWindow(sf::WindowHandle hwnd);
		
		sf::Window* getWindow(sf::Uint8 id) { return _window; }

		//void createWorkspace(Controller& controller);

		//inline sf::Window* getWindow() { return mWindow; }

	protected:

	private:
		//obsolete
		//void createViewport(Controller& controller, Ogre::RenderWindow* renderWindow = nullptr, Ogre::RenderTarget* renderTarget = nullptr);

		//Ogre::TexturePtr mRtt_texture;

		XEngine* mEngine;
		sf::Window* _window;
		//Ogre::RenderWindow* mRenderWindow;
	};

} // namespace XE

#endif // __WINDOWMANAGER_HPP__