#include <XERenderer/GUI/GUIRenderer.hpp>

#include <Ogre/OgreMain/include/OgreVector2.h>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/GUI/Screen.hpp>
#include <XERenderer/GUI/WScreen.hpp>
#include <XERenderer/GUI/GorillaRenderer.hpp>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#include <Ogre/OgreMain/include/OgreTextureManager.h>
#include <Ogre/OgreMain/include/OgreHlmsTextureManager.h>

#include <XEUI/DAL/FB_UI_Atlas_generated.h>

#include <ThirdParty/plog/Log.h>

#include <XEDAL/PhysFS/PhysFsStream.hpp>

#include <XEScripts/LUAEngine.h>
#include <XEUI/Glyph.hpp>

#include <ThirdParty/imgui/imgui.h>

#include <XERenderer/Editor/ImgGuiRenderable.hpp>
#include <OgrePixelBox.h>

#include <OgreHardwarePixelBuffer.h>


#include <iostream>



static double       g_Time = 0.0f;
static float        g_MouseWheel = 0.0f;
static bool         g_MousePressed[3] = { false, false, false };

namespace XE
{

	GUIRenderer::GUIRenderer(GraphicsManager& graphicsManager)
		: m_graphicsManager(graphicsManager)
		, m_layerRenderer(graphicsManager)		
	{
		//create default atlas with id 0
		std::unique_ptr<AtlasData> atlasData = std::unique_ptr<AtlasData>(new AtlasData());
		_atlasData[0] = std::move(atlasData);

	}

	GUIRenderer::~GUIRenderer()
	{
		while (_t_ImgGuiRenderables.size() > 0)
		{
			delete _t_ImgGuiRenderables.back();
			_t_ImgGuiRenderables.pop_back();
		}
	}

	void  GUIRenderer::_t_resizeRenderWindow(size_t w, size_t h)
	{
		m_ViewportSize = sf::Vector2f(w,h);

		m_layerRenderer._t_onResizeRenderWindow(w, h);

		Ogre::Matrix4 projMatrix(2.0f / w, 0.0f, 0.0f, -1.0f,
			0.0f, -2.0f / h, 0.0f, 1.0f,
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		for each (auto renderable in _t_ImgGuiRenderables)
		{
			renderable->setCustomProjectionMatrix(true, projMatrix );
		}		
	}

	void GUIRenderer::_t_init(TextureAtlas* atlas, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr)
	{
		m_layerRenderer._t_initRenderer(atlas, objManager, sceneMgr);		
		_t_createFontTexture(); //imgui only
	}
	
	void GUIRenderer::update()
	{
		m_layerRenderer.update();
	}

	void GUIRenderer::_t_update(float delta)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = delta;
		// Setup display size (every frame to accommodate for window resizing)
		io.DisplaySize = ImVec2(m_ViewportSize.x, m_ViewportSize.y);

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

		bool show_test_window = true;

	//####	ImGui::ShowTestWindow(&show_test_window);

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

		int numberDraws = 0;

		auto scenemgr = m_graphicsManager.getRoot()->getSceneManager("MyFirstSceneManager");

		//iterate through all lists (at the moment every window has its own)
		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* drawList = draw_data->CmdLists[n];

			const ImDrawVert* vtxBuf = drawList->VtxBuffer.Data;
			const ImDrawIdx* idxBuf = drawList->IdxBuffer.Data;

			unsigned int startIdx = 0;
		
			for (int i = 0; i < drawList->CmdBuffer.Size; i++)
			{
				numberDraws++;
				
				//create renderables if necessary
				if (numberDraws >= _t_ImgGuiRenderables.size())
				{
					auto newRenderable = new ImgGuiRenderable(i,
						m_graphicsManager.getGUIRenderer(),
						&scenemgr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC)
						, scenemgr);

					_t_ImgGuiRenderables.push_back(newRenderable);

					newRenderable->mFontTex = mFontTex;
				}

				//update their vertex buffers
				const ImDrawCmd *drawCmd = &drawList->CmdBuffer[i];
				_t_ImgGuiRenderables[numberDraws -1]->updateVertexData(vtxBuf, &idxBuf[startIdx], drawList->VtxBuffer.Size, drawCmd->ElemCount);

				//increase start index of indexbuffer
				startIdx += drawCmd->ElemCount;
				
			}			
		}

		//delete unused renderables
		while (_t_ImgGuiRenderables.size() > numberDraws)
		{
			delete _t_ImgGuiRenderables.back();
			_t_ImgGuiRenderables.pop_back();
		}

		//todo lock m_screens (dont add delete while renderonce is called)
	/*		m_graphicsManager.getIntoRendererQueue().push([this]()
		{*/

		//	m_layerRenderer._t_update();
		//	done in gorilla renderqueue!?
				/*for each (WScreen* var in m_screens)
				{
					var->_t_screen->renderOnce();
				}*/
				//	});
	}

	void GUIRenderer::addScreen(WScreen* screen)
	{
		m_screens.push_back(screen);
	}


	const SpriteData* GUIRenderer::getSprite(const std::string& spriteName)
	{
		if (_sprites.find(spriteName) == _sprites.end())
			LOG(plog::error) << "sprite not found: " << spriteName;

		return _sprites[spriteName].get();
	}

	void GUIRenderer::registerObject(sol::state& lua)
	{
		lua.new_usertype<GUIRenderer>("GUIRenderer",

			//properties
			//"guiRenderer", sol::property(&GraphicsManager::getGUIRenderer)

			//functions
			"loadAtlas", &GUIRenderer::loadAtlas
			);

		auto stateView = lua.set("GUIRenderer", this); //set object instance
	}

	bool GUIRenderer::loadAtlas(const std::string& fileName)
	{
		PhysFsStream wonderfullStream;
		if (wonderfullStream.open(fileName.c_str()))//"UI/TestAtlas.fbbin"))
		{
			// Make sure that the stream's reading position is at the beginning
			wonderfullStream.seek(0);

			std::vector<char> buffer(wonderfullStream.getSize());
			if (wonderfullStream.read(buffer.data(), wonderfullStream.getSize()))
			{
				auto atlas = XFBType::GetAtlas(&buffer[0]);

				std::string atlasName = atlas->name()->c_str();
				addAtlas(atlasName, atlas->texture()->c_str(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

				LOG(plog::info) << "load sprite data";

				//sprites
				for (auto it = atlas->sprites()->begin(); it != atlas->sprites()->end(); ++it)
				{
					std::unique_ptr<SpriteData> newSprite = std::unique_ptr<SpriteData>(new SpriteData());
					newSprite->spriteWidth = (*it)->width(); // width
					newSprite->spriteHeight = (*it)->height(); // height
					newSprite->uvLeft = (*it)->posX();
					newSprite->uvBottom = (*it)->posY() - (*it)->height();
					newSprite->uvTop = (*it)->posY();
					newSprite->uvRight = newSprite->uvLeft + (*it)->posX();

					_sprites[(*it)->name()->c_str()] = std::move(newSprite);
				}

				//fonts
				for (auto it = atlas->fonts()->begin(); it != atlas->fonts()->end(); ++it)
				{
					Font newFont;
					

					//glyphs
					for (auto itGlyph = (*it)->glyphs()->begin(); itGlyph != (*it)->glyphs()->end(); ++itGlyph)
					{
						//LOG(plog::info) << "Glyph:";
					//	std::cout << "code:" << (*itGlyph)->code() << std::endl; //->> Attention!! causing sometimes a memory crash??

						FontGlyph newGlyph;
						newGlyph.glyphAdvance = (*itGlyph)->glyphAdvance();
						newGlyph.glyphHeight = (*itGlyph)->glyphHeight();
						newGlyph.glyphWidth = (*itGlyph)->glyphWidth();

						if ((*itGlyph)->kerningList())
						{
							//kerning
							for (auto itKerning = (*itGlyph)->kerningList()->begin(); itKerning != (*itGlyph)->kerningList()->end(); ++itKerning)							
							{
							//	std::cout << "itKerning:" << (*itKerning)->character() << std::endl; //->> Attention!! causing sometimes a memory crash??
								
								newGlyph.kerning.emplace_back(GlyphKerning((*itKerning)->character(), (*itKerning)->kerning()));
							}
						}

						newGlyph.uvBottom = (*itGlyph)->uvBottom();
						newGlyph.uvHeight = (*itGlyph)->uvHeight();
						newGlyph.uvLeft = (*itGlyph)->uvLeft();
						newGlyph.uvRight = (*itGlyph)->uvRight();
						newGlyph.uvTop = (*itGlyph)->uvTop();
						newGlyph.uvWidth = (*itGlyph)->uvWidth();
						newGlyph.verticalOffset = (*itGlyph)->verticalOffset();

						newFont.mGlyphs.emplace((*itGlyph)->code(),newGlyph);
					}
					
					newFont.mBaseline = (*it)->baseline();
					newFont.mLetterSpacing = (*it)->letterSpacing();
					newFont.mLineHeight = (*it)->lineHeight();
					newFont.mLineSpacing = (*it)->lineSpacing();
					newFont.mMonoWidth = (*it)->monoWidth();
					//	newFont->mRangeBegin = (*it)->rangeBegin();
					//	newFont->mRangeEnd = (*it)->rangeEnd();
					newFont.mSpaceLength = (*it)->spaceLength();

					_fonts.emplace((*it)->id(),newFont);
				}

				//todo from renderthread! ?? into main thread_calculateCoordinates();
			}
		}
		else
		{
			LOG(plog::error) << "GUIRenderer::loadAtlas -> atlasfile not found: " << fileName;
			return false;
		}
	}
	
	void  GUIRenderer::_calculateCoordinates(sf::Vector2f texelOffset, sf::Vector2f inverseTextureSize)
	{
		for (std::map<XE::Uint32, Font>::iterator gd_it = _fonts.begin(); gd_it != _fonts.end(); gd_it++)
		{
			for (std::unordered_map<Uint32, FontGlyph>::iterator it = (*gd_it).second.mGlyphs.begin(); it != (*gd_it).second.mGlyphs.end(); it++)
			{

				(*it).second.uvLeft -= texelOffset.x;
				(*it).second.uvTop += texelOffset.y;
				(*it).second.uvRight += texelOffset.x;
				(*it).second.uvBottom -= texelOffset.y;

				(*it).second.uvLeft *= inverseTextureSize.x;
				(*it).second.uvTop *= inverseTextureSize.y;
				(*it).second.uvRight *= inverseTextureSize.x;
				(*it).second.uvBottom *= inverseTextureSize.y;

				(*it).second.texCoords[TopLeft].x = (*it).second.uvLeft;
				(*it).second.texCoords[TopLeft].y = (*it).second.uvTop;
				(*it).second.texCoords[TopRight].x = (*it).second.uvRight;
				(*it).second.texCoords[TopRight].y = (*it).second.uvTop;
				(*it).second.texCoords[BottomRight].x = (*it).second.uvRight;
				(*it).second.texCoords[BottomRight].y = (*it).second.uvBottom;
				(*it).second.texCoords[BottomLeft].x = (*it).second.uvLeft;
				(*it).second.texCoords[BottomLeft].y = (*it).second.uvBottom;

				(*it).second.glyphWidth = (*it).second.uvWidth;
				(*it).second.glyphHeight = (*it).second.uvHeight;

			}
		}

		for (std::map<std::string, std::unique_ptr<SpriteData>>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
		{
			(*it).second->uvRight = (*it).second->uvLeft + (*it).second->spriteWidth;
			(*it).second->uvBottom = (*it).second->uvTop + (*it).second->spriteHeight;

			(*it).second->uvLeft *= inverseTextureSize.x;
			(*it).second->uvTop *= inverseTextureSize.y;
			(*it).second->uvRight *= inverseTextureSize.x;
			(*it).second->uvBottom *= inverseTextureSize.y;

			(*it).second->texCoords[TopLeft].x = (*it).second->uvLeft;
			(*it).second->texCoords[TopLeft].y = (*it).second->uvTop;
			(*it).second->texCoords[TopRight].x = (*it).second->uvRight;
			(*it).second->texCoords[TopRight].y = (*it).second->uvTop;
			(*it).second->texCoords[BottomRight].x = (*it).second->uvRight;
			(*it).second->texCoords[BottomRight].y = (*it).second->uvBottom;
			(*it).second->texCoords[BottomLeft].x = (*it).second->uvLeft;
			(*it).second->texCoords[BottomLeft].y = (*it).second->uvBottom;
		}
	}

	//todo dont use global func!?
	float _getAdvance(const FontGlyph* glyph, float kerning)
	{
		//if (mFixedWidth)
		//	return mGlyphData->mMonoWidth;
		//else
		return glyph->glyphAdvance + kerning;
	}

	//sf::Vector2i GUIRenderer::GetTextStringMetrics(const std::basic_string<XE::Uint32>& string, unsigned int font_size) const
	//{
	//	const Font* font = getFont(font_size); //fontsize 9 = Id

	//	sf::Vector2i retSize;

	//	if (!font)
	//		return retSize;

	//	float cursor = 0,
	//		kerning = 0;

	//	unsigned char thisChar = 0, lastChar = 0;
	//	const FontGlyph* glyph = 0;
	//	retSize.x = 0;
	//	retSize.y = font->mLineHeight;// GetFontLineHeight(font_size);// mGlyphData->mLineHeight;

	//	for (size_t i = 0; i < string.length(); i++)
	//	{
	//		thisChar = string[i];

	//		if (thisChar == ' ')
	//		{
	//			lastChar = thisChar;
	//			cursor += font->mSpaceLength;
	//			continue;
	//		}

	//		/*if (thisChar < font->mRangeBegin || thisChar > font->mRangeEnd)
	//		{
	//			lastChar = 0;
	//			continue;
	//		}*/

	//		glyph = font->getGlyph(thisChar);
	//		if (glyph == 0)
	//			continue;
	//		kerning = glyph->getKerning(lastChar);
	//		if (kerning == 0)
	//			kerning = font->mLetterSpacing;

	//		cursor += _getAdvance(glyph, kerning);
	//		lastChar = thisChar;

	//	} // for

	//	retSize.x = cursor - kerning;

	//	return retSize;
	//}

	const Font* GUIRenderer::getFont(const XE::Uint32 fontId) const
	{
		std::map<XE::Uint32, Font>::const_iterator it = _fonts.find(fontId);
		if (it == _fonts.end())
		{
			LOG(plog::error) << "Glyph not found: " << fontId;
			return 0;
		}
		else
			return &(*it).second;
	}

	sf::Vector2i GUIRenderer::GetTextStringMetrics(const sf::String& string, const Font* font) const
	{
		sf::Vector2i retSize;

		if (!font)
			return retSize;

		float cursor = 0,
			kerning = 0;

		unsigned char thisChar = 0, lastChar = 0;
		const FontGlyph* glyph = 0;
		const FontGlyph* lastGlyph = 0;
		
		retSize.x = 0;
		retSize.y = font->mLineHeight;

		for (size_t i = 0; i < string.getSize(); i++)
		{
			thisChar = string[i];

			if (thisChar == ' ')
			{
				lastChar = thisChar;
				lastGlyph = glyph;
				cursor += font->mSpaceLength;
				continue;
			}

			/*	if (thisChar < font->mRangeBegin || thisChar > font->mRangeEnd)
				{
					lastChar = 0;
					continue;
				}*/

			glyph = font->getGlyph(thisChar);
			if (glyph == 0)
				continue;
			if (lastGlyph == 0)
				lastGlyph = glyph;

			kerning = lastGlyph->getKerning(thisChar);
			if (kerning == 0)
				kerning = font->mLetterSpacing;

			cursor += _getAdvance(glyph, kerning);
			lastChar = thisChar;
			lastGlyph = glyph;

		} // for

		retSize.x = cursor - kerning;

		return retSize;
	}


	LayerRenderer& GUIRenderer::getLayerRenderer()
	{
		return m_layerRenderer;
	}

	AtlasData& GUIRenderer::getAtlasData(const XE::Uint16& id)
	{
		return *(*_atlasData.find(id)).second.get();
	}

	void GUIRenderer::addAtlas(const std::string& atlasName, const std::string& texName, const std::string& ressGroup, XE::Uint16 atlasId)
	{
		//create atlasdata in mainthread
		auto atlasDataPtr = &getAtlasData(atlasId);
		if (!atlasDataPtr)
		{
			std::unique_ptr<AtlasData> atlasData = std::unique_ptr<AtlasData>(new AtlasData());
			atlasDataPtr = (_atlasData[atlasId] = std::move(atlasData)).get();
		}

		m_graphicsManager.getIntoRendererQueue().push([this, atlasName, texName, ressGroup, atlasDataPtr, atlasId]() {

			//load Textures -> todo getByName without file extension!?
			Ogre::TexturePtr texture = Ogre::TextureManager::getSingletonPtr()->getByName(texName, ressGroup);

			if (texture.isNull())
				texture = Ogre::TextureManager::getSingletonPtr()->load(texName, ressGroup, Ogre::TEX_TYPE_2D, 0);

			std::unique_ptr<TextureAtlas> atlas = std::unique_ptr<TextureAtlas>(new TextureAtlas(texture)); // t1 + ".gorilla", t2));

			XE::Uint32 texWidth = texture->getWidth();
			XE::Uint32 textHeight = texture->getHeight();

			Ogre::RenderSystem* rs = m_graphicsManager.getRoot()->getRenderSystem();

			sf::Vector2f texelOffset;
			texelOffset.x = rs->getHorizontalTexelOffset();
			texelOffset.y = rs->getVerticalTexelOffset();

			sf::Vector2f inverseTextureSize;
			inverseTextureSize.x = 1.0f / texture->getWidth();
			inverseTextureSize.y = 1.0f / texture->getHeight();

			atlasDataPtr->_t_textureAtlasPtr = atlas.get();

			auto sceneMgr = m_graphicsManager.getRoot()->getSceneManager("MyFirstSceneManager");

			_t_init(atlasDataPtr->_t_textureAtlasPtr, &sceneMgr->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), sceneMgr);

			//calculation in mainthread
			m_graphicsManager.getFromRendererQueue().push([this, texelOffset, inverseTextureSize, atlasDataPtr, texWidth, textHeight]() {

				atlasDataPtr->texelOffset = texelOffset;
				atlasDataPtr->textureSize = sf::Vector2f(texWidth, textHeight);
				_calculateCoordinates(texelOffset, inverseTextureSize);

				auto tmp = getSprite("whitepixel.png");
				float texelOffsetX = atlasDataPtr->texelOffset.x, texelOffsetY = atlasDataPtr->texelOffset.y;
				texelOffsetX /= atlasDataPtr->textureSize.x;
				texelOffsetY /= atlasDataPtr->textureSize.y;
				_whitePixelPos.x = tmp->uvLeft - texelOffsetX;
				_whitePixelPos.y = tmp->uvTop + texelOffsetY;

				//redraw all uv's
				m_layerRenderer.redrawAllLayers();
			});

			_t_atlas[atlasId] = std::move(atlas);
		});
	}

	//void addAtlas(TextureAtlas* atlas){ _t_atlas.push_back(atlas); }

	//WScreenRenderable* createScreenRenderable(Ogre::Vector3 position, const std::string& atlasName);
	//WScreen* createScreen(const std::string& atlasName);

	//change only in renderthread!
	//	TextureAtlas* _t_atlas;

	//return value only usable in renderthread
	TextureAtlas* GUIRenderer::_t_getAtlas(const XE::Uint16 atlasId) {
		return (*_t_atlas.find(atlasId)).second.get();
	}


	void GUIRenderer::_t_createFontTexture()
	{
		// Build texture atlas
		ImGuiIO& io = ImGui::GetIO();
		unsigned char* pixels;
		int width, height;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

		mFontTex = Ogre::TextureManager::getSingleton().createManual("ImguiFontTex", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, width, height, 1, 1, Ogre::PF_R8G8B8A8);

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

	bool GUIRenderer::ProcessSDLEvent(SDL_Event* event)
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


} // namespace XE