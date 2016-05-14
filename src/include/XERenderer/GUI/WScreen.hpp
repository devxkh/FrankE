#ifndef _WSCREEN_HPP
#define _WSCREEN_HPP

#include <XESystem/SystemConfig.hpp>
#include <XERenderer/GUI/WScreen.hpp>
#include <XERenderer/GUI/GorillaRenderer.hpp>

#include <string>

namespace sf
{
	class Window;
}

namespace XE
{
	//forwarding
	class GUIRenderer;
	class Screen;
	class CameraRenderable;

	class WScreen
	{
	public:
		WScreen(GUIRenderer& guiRenderer, CameraRenderable& camera, const XE::Uint16 atlasId = 0);
		~WScreen();

		void setSize(const float width, const float height);

		float getActualHeight();
		float getActualWidth();
		
		//change only in renderthread!
	//	Screen* _t_screen;
	private:
		GUIRenderer& m_guiRenderer;
		float m_height;
		float m_width;
	};

} // namespace XE


#endif // _WSCREEN_HPP