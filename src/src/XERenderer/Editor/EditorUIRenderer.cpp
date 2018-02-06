#include <XERenderer/Editor/EditorUIRenderer.hpp>

#include <ThirdParty/imgui/imgui.h>

#include <XERenderer/Editor/ImGuizmo.h>
#include <OgrePixelBox.h>
#include <XERenderer/Editor/ImgGuiRenderable.hpp>

#include <OgreHardwarePixelBuffer.h>
#include <Ogre/OgreMain/include/OgreMatrix3.h>
#include <Ogre/OgreMain/include/OgreMatrix4.h>
#include <Ogre/OgreMain/include/OgreCamera.h>
#include <Ogre/OgreMain/include/OgreResourceGroupManager.h>

#include <Ogre/OgreMain/include/OgreRoot.h>
#include <Ogre/OgreMain/include/OgreTextureManager.h>

#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/GUI/GUIRenderer.hpp>


static double       g_Time = 0.0f;
static float        g_MouseWheel = 0.0f;
static bool         g_MousePressed[3] = { false, false, false };

namespace XE {
	
	

	EditorUIRenderer::EditorUIRenderer(GraphicsManager& graphicsManager, Ogre::Camera* camera)
		: m_graphicsManager(graphicsManager)
		, m_camera(camera)
	{

	}

	EditorUIRenderer::~EditorUIRenderer() {

		/*
		renderthread?
		while (_t_ImgGuiMovableObject->mRenderables.size() > 0)
		{
		delete _t_ImgGuiMovableObject->mRenderables.back();
		_t_ImgGuiMovableObject->mRenderables.pop_back();
		}
		delete _t_ImgGuiMovableObject;
		_t_ImgGuiMovableObject = nullptr;*/
	}

	void EditorUIRenderer::init() {
		_t_createFontTexture(); //imgui only


								//TODO do this on Editor stuff
		std::string lNameOfResourceGroup = "Editor";
		{
			Ogre::ResourceGroupManager& lRgMgr = Ogre::ResourceGroupManager::getSingleton();

			lRgMgr.initialiseResourceGroup(lNameOfResourceGroup, false);
			lRgMgr.loadResourceGroup(lNameOfResourceGroup);
		}
	}


	IEditorUIState& EditorUIRenderer::createUIState(std::unique_ptr<IEditorUIState> uiState)
	{
		m_EditorUIStates.push_back(std::move(uiState));

		return *m_EditorUIStates.back().get();
	}

	IEditorUIState* EditorUIRenderer::getUIState(int ID)
	{
		for each (auto& uiState in m_EditorUIStates)
		{
			if (uiState.get()->ID == ID)
				return uiState.get();
		}
	}

	void EditorUIRenderer::Render(const Ogre::Matrix4& projMatrix, const sf::Vector2f& viewportSize, const float delta) {


		//GizmoUIState* gus = static_cast<GizmoUIState*>(getUIState(XE::EUSID::Gizmo));
		
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = delta;
		// Setup display size (every frame to accommodate for window resizing)
		io.DisplaySize = ImVec2(viewportSize.x, viewportSize.y);

		// Setup time step
		Uint32	time = SDL_GetTicks();
		double current_time = time / 1000.0;
		io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
		g_Time = current_time;

		// Setup inputs
		// (we already got mouse wheel, keyboard keys & characters from SDL_PollEvent())
		int mx, my;
		Uint32 mouseMask = SDL_GetMouseState(&mx, &my);
		//if (SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS)
		io.MousePos = ImVec2((float)mx, (float)my);   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
													  //	else
													  //		io.MousePos = ImVec2(-1, -1);

		io.MouseDown[0] = g_MousePressed[0] || (mouseMask & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;		// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
		io.MouseDown[1] = g_MousePressed[1] || (mouseMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
		io.MouseDown[2] = g_MousePressed[2] || (mouseMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
		g_MousePressed[0] = g_MousePressed[1] = g_MousePressed[2] = false;

		io.MouseWheel = g_MouseWheel;
		g_MouseWheel = 0.0f;

		// Hide OS mouse cursor if ImGui is drawing it
		SDL_ShowCursor(io.MouseDrawCursor ? 0 : 1);

		ImGui::NewFrame();

		ImGuizmo::BeginFrame(); //gizmo

		auto scenemgr = m_graphicsManager.getRoot()->getSceneManager("MyFirstSceneManager");


		for each (auto& uiState in m_EditorUIStates)
		{
			uiState.get()->render();
		}

		bool show_test_window = true;

	//	ImGui::ShowTestWindow(&show_test_window);

		//Tell ImGui to create the buffers
		ImGui::Render();

		ImDrawData *draw_data = ImGui::GetDrawData();

		if (!draw_data)
			return;

		int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
		int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
		if (fb_width == 0 || fb_height == 0)
			return;
		draw_data->ScaleClipRects(io.DisplayFramebufferScale);

		//iterate through all lists (at the moment every window has its own)
		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			if (draw_data->CmdListsCount >= _t_ImgGuiMovableObject.size())
				_t_ImgGuiMovableObject.push_back(new ImgGuiMovableObject(20 + n, &scenemgr->_getEntityMemoryManager(Ogre::SCENE_STATIC), scenemgr));

			auto movableObj = _t_ImgGuiMovableObject[n];

			const ImDrawList* drawList = draw_data->CmdLists[n];

			const ImDrawVert* vtxBuf = drawList->VtxBuffer.Data;
			const ImDrawIdx* idxBuf = drawList->IdxBuffer.Data;

			unsigned int startIdx = 0;

			for (int i = 0; i < drawList->CmdBuffer.Size; i++)
			{
				const ImDrawCmd *drawCmd = &drawList->CmdBuffer[i];

				/*if (true)
				{*/
				//create renderables if necessary
				if (i >= movableObj->mRenderables.size())
				{
					auto newRenderable = new ImgGuiRenderable(m_graphicsManager.getGUIRenderer(), movableObj);

					newRenderable->mFontTex = mFontTex;
					//update their vertex buffers
					static_cast<ImgGuiRenderable*> (newRenderable)->updateVertexData(vtxBuf, &idxBuf[startIdx], drawList->VtxBuffer.Size, drawCmd->ElemCount);

					static_cast<ScreenRenderable*>(newRenderable)->setCustomProjectionMatrix(true, projMatrix);

					//render the object -> v1 version!
					//scenemgr->_renderSingleObject(newRenderable, newRenderable->m_ImgGuiMovableObject, false, false);
				}
				else {
					//update their vertex buffers
					static_cast<ImgGuiRenderable*> (movableObj->mRenderables[i])->updateVertexData(vtxBuf, &idxBuf[startIdx], drawList->VtxBuffer.Size, drawCmd->ElemCount);
					static_cast<ScreenRenderable*>(movableObj->mRenderables[i])->setCustomProjectionMatrix(true, projMatrix);

					//render the object -> v1 version!
					//scenemgr->_renderSingleObject(movableObj->mRenderables[i], static_cast<ImgGuiRenderable*>(movableObj->mRenderables[i])->m_ImgGuiMovableObject, false, false);
				}
				//}


				//increase start index of indexbuffer
				startIdx += drawCmd->ElemCount;
			}

			//delete unused renderables
			while (movableObj->mRenderables.size() > drawList->CmdBuffer.Size)
			{
				delete movableObj->mRenderables.back();
				movableObj->mRenderables.pop_back();
			}
		}

		//delete unused renderables
		while (_t_ImgGuiMovableObject.size() > draw_data->CmdListsCount)
		{
			delete _t_ImgGuiMovableObject.back();
			_t_ImgGuiMovableObject.pop_back();
		}
	}



	void EditorUIRenderer::_t_createFontTexture()
	{
		// Build texture atlas
		ImGuiIO& io = ImGui::GetIO();
		unsigned char* pixels;
		int width, height;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

		mFontTex = Ogre::TextureManager::getSingleton().createManual("ImguiFontTex", "General", Ogre::TEX_TYPE_2D, width, height, 1, 1, Ogre::PF_R8G8B8A8);

		const Ogre::PixelBox & lockBox = mFontTex->getBuffer()->lock(Ogre::Image::Box(0, 0, width, height), Ogre::v1::HardwareBuffer::HBL_DISCARD);
		size_t texDepth = Ogre::PixelUtil::getNumElemBytes(lockBox.format);

		memcpy(lockBox.data, pixels, width*height*texDepth);
		mFontTex->getBuffer()->unlock();

		//Ogre::Image dst;
		//mFontTex->convertToImage(dst, false);
		//dst.save("f:/font.tga");

		io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;                     // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
		io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
		io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
		io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
		io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
		io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
		io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
		io.KeyMap[ImGuiKey_A] = SDLK_a;
		io.KeyMap[ImGuiKey_C] = SDLK_c;
		io.KeyMap[ImGuiKey_V] = SDLK_v;
		io.KeyMap[ImGuiKey_X] = SDLK_x;
		io.KeyMap[ImGuiKey_Y] = SDLK_y;
		io.KeyMap[ImGuiKey_Z] = SDLK_z;
	}

	bool EditorUIRenderer::ProcessSDLEvent(SDL_Event* event)
	{
		ImGuiIO& io = ImGui::GetIO();
		switch (event->type)
		{
		case SDL_MOUSEWHEEL:
		{
			if (event->wheel.y > 0)
				g_MouseWheel = 1;
			if (event->wheel.y < 0)
				g_MouseWheel = -1;
			return true;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if (event->button.button == SDL_BUTTON_LEFT) g_MousePressed[0] = true;
			if (event->button.button == SDL_BUTTON_RIGHT) g_MousePressed[1] = true;
			if (event->button.button == SDL_BUTTON_MIDDLE) g_MousePressed[2] = true;
			return true;
		}
		case SDL_TEXTINPUT:
		{
			io.AddInputCharactersUTF8(event->text.text);
			return true;
		}
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
			int key = event->key.keysym.sym & ~SDLK_SCANCODE_MASK;
			io.KeysDown[key] = (event->type == SDL_KEYDOWN);
			io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
			io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
			io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
			io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
			return true;
		}
		}
		return false;
	}

}