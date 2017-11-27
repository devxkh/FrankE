#ifndef __OGREWORKSPACE_HPP__
#define __OGREWORKSPACE_HPP__

#include <Ogre/OgreMain/include/OgrePrerequisites.h>
#include <Ogre/OgreMain/include/OgreTexture.h>
#include <Ogre/OgreMain/include/OgreSharedPtr.h>

#include <Ogre/OgreMain/include/Compositor/Pass/OgreCompositorPass.h>
#include <Ogre/OgreMain/include/Compositor/Pass/OgreCompositorPassDef.h>
#include <Ogre/OgreMain/include/Compositor/Pass/OgreCompositorPassProvider.h>

#include <Ogre/OgreMain/include/Compositor/OgreCompositorWorkspaceListener.h>


#include <XERenderer/Editor/ImgGuiRenderable.hpp>

#include <memory>

class SDL_Window;

namespace Ogre
{
	class CompositorManager2;
	class CompositorWorkspace;
	class RenderTarget;
	class RenderWindow;
	//class Camera;
//	class Root;
}

namespace XE {
	
	class ImgGuiRenderable;

	class ImGuiCompositorWorkspaceListener : public Ogre::CompositorWorkspaceListener
	{
	public:
		ImGuiCompositorWorkspaceListener();
		ImGuiCompositorWorkspaceListener(Ogre::Camera* camera);

		void passPreExecute(Ogre::CompositorPass *pass);
	
		Ogre::Camera* m_camera;
		ImgGuiRenderable* m_ImgGuiRenderable;
	private:
	

	};


	class Scene;
//	class Controller;
	class XEngine;
	class GraphicsManager;
	class OgreCamera;

	//class ImGuiPassDef : public Ogre::CompositorPassDef
	//{
	//public:
	//	ImGuiPassDef(Ogre::uint32 rtIndex)
	//		: Ogre::CompositorPassDef(Ogre::PASS_CUSTOM, rtIndex)
	//	{
	//	}
	//};

	//// TODO: The compositor manager allows adding this pass to any number of targets,
	//// but MyGUI was designed to handle one window target only. For example,
	//// when we add the pass to multiple targets, all RTTLayers would be unnecessarily updated multiple times.
	//class ImGuiPass : public Ogre::CompositorPass
	//{
	//public:
	//	ImGuiPass(const Ogre::CompositorPassDef *definition, const Ogre::CompositorChannel &target,
	//		Ogre::CompositorNode *parentNode, GraphicsManager& graphicsMgr);

	//	virtual void execute(const Ogre::Camera *lodCameraconst);

	//private:
	//	GraphicsManager& m_GraphicsManager;
	//};


	// TODO: The compositor manager allows adding this pass to any number of targets,
	// but MyGUI was designed to handle one window target only. For example,
	// when we add the pass to multiple targets, all RTTLayers would be unnecessarily updated multiple times.
	class MyGUIPass : public Ogre::CompositorPass
	{
	public:
		MyGUIPass(const Ogre::CompositorPassDef *definition, const Ogre::CompositorChannel &target,
			Ogre::CompositorNode *parentNode, GraphicsManager& graphicsMgr, Ogre::Camera* camera);

		virtual void execute(const Ogre::Camera *lodCameraconst);

	private:
		GraphicsManager& m_GraphicsManager;
		Ogre::Camera* m_camera;
	};

	//CompositorPassDef(CompositorPassType passType, CompositorTargetDef *parentTargetDef) :

	class MyGUIPassDef : public Ogre::CompositorPassDef
	{
	public:
		MyGUIPassDef(Ogre::CompositorTargetDef *parentTargetDef)
			: Ogre::CompositorPassDef(Ogre::PASS_CUSTOM, parentTargetDef) //rtIndex)
		{
		}
	};
	// The factory for the MyGUI compositor pass. Note that only one provider can be
	// registered with Ogre at a time, which is why we have exposed the MyGUIPass and MyGUIPassDef classes
	// publicly in this header. If users need their own custom passes, they can implement their own provider
	// which would return either a MyGUI pass or other custom passes depending on the customId.
	class OgreCompositorPassProvider : public Ogre::CompositorPassProvider
	{
	public:

		OgreCompositorPassProvider(GraphicsManager& graphicsMgr, Ogre::Camera* camera) :
			m_GraphicsManager(graphicsMgr),
			m_camera(camera)
		{

		}

		Ogre::CompositorPassDef* addPassDef(Ogre::CompositorPassType passType,
			Ogre::IdString customId,
			Ogre::CompositorTargetDef *parentTargetDef,
			Ogre::CompositorNodeDef *parentNodeDef)
		{
			if (customId == mPassId)
				return OGRE_NEW MyGUIPassDef(parentTargetDef);
		}

		Ogre::CompositorPass* addPass(const Ogre::CompositorPassDef *definition, Ogre::Camera *defaultCamera,
			Ogre::CompositorNode *parentNode, const Ogre::CompositorChannel &target,
			Ogre::SceneManager *sceneManager)
		{
			return OGRE_NEW MyGUIPass(definition, target, parentNode, m_GraphicsManager, m_camera);
		}

		static Ogre::IdString mPassId;

	private:
		GraphicsManager& m_GraphicsManager;
		Ogre::Camera* m_camera;
	};

	class OgreWorkspace
	{

	public:

		OgreWorkspace(XEngine& engine, GraphicsManager& graphicsMgr);
		~OgreWorkspace();
		
		static Ogre::RenderWindow* _t_createRenderWindow(void* window = nullptr);
		
		static Ogre::TexturePtr createTextureRenderTarget(int width, int height);
		Ogre::RenderTarget* createRenderTarget(int width, int height, Ogre::RenderTarget* renderTarget = nullptr);
		void UpdateViews();
		//sf::Window* createWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default);
		//sf::Window* createWindow(sf::WindowHandle hwnd);

		//use only in renderthread!
		void _t_createWorkspace(Ogre::RenderWindow* renderWindow, Ogre::Camera* camera);

		//inline sf::Window* getWindow() { return mWindow; }
		
		Ogre::CompositorWorkspace*  _t_compositorWorkspace;
		
	protected:

	private:

		std::auto_ptr<ImGUICompositorPassProvider> _t_ImGUIPassProvider;


		std::auto_ptr<OgreCompositorPassProvider> mPassProvider;
		//obsolete
		//void createViewport(Controller& controller, Ogre::RenderWindow* renderWindow = nullptr, Ogre::RenderTarget* renderTarget = nullptr);
		ImGuiCompositorWorkspaceListener m_imguilistener;

		Ogre::TexturePtr mRtt_texture;

		GraphicsManager& mGraphicsManager;
		XEngine& mEngine;
	//	sf::Window* mWindow;
	//	Ogre::RenderWindow* mRenderWindow;
	};

} // namespace XE

#endif // __OGREWORKSPACE_HPP__