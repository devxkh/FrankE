#include <XERenderer/GUI/WScreen.hpp>
#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/GUI/Screen.hpp>

#include <Ogre/OgreMain/include/OgreLogManager.h>


#include <XESystem/Logging.hpp>

namespace XE
{
	WScreen::WScreen(GUIRenderer& guiRenderer, CameraRenderable& camera, const XE::Uint16 atlasId)
		:m_guiRenderer(guiRenderer)//, _t_atlas(guiRenderer.getAtlas("todo xxx"))
	{
		guiRenderer.addScreen(this);

		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this, &camera, atlasId](){
		
			Ogre::LogManager::getSingleton().logMessage("RQ -> WScreen::WScreen");
			
			//std::string t = atlasFileName;
			//_t_screen = OGRE_NEW Screen(m_guiRenderer._t_getAtlas(atlasId), &camera);
		});
	}


	WScreen::~WScreen()
	{
		m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this](){
		//	OGRE_DELETE _t_screen;
		});
	}


	void WScreen::setSize(const float width, const float height){

		m_height = height;
		m_width = width;

		//m_guiRenderer.getGraphicsManager().getIntoRendererQueue().push([this, width, height](){
		//	_t_screen->setSize(width, height);
		//});
	}

	float WScreen::getActualHeight(){ return m_height; }
	float WScreen::getActualWidth(){ return m_width; }


} // namespace XE