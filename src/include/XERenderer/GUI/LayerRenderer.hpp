#ifndef _LAYERRENDERER_HPP
#define _LAYERRENDERER_HPP

#include <XESystem/SystemConfig.hpp>
#include <vector>

namespace Ogre {
	class VertexBufferPacked;
	class ObjectMemoryManager;
	class SceneManager;
}

namespace XE
{
	class GraphicsManager;
	class RenderableLayer;
	class TextureAtlas;
	class RenderableShape;
	class WLayer;

	class LayerRenderer
	{
	public:
		
		LayerRenderer(GraphicsManager& graphMgr);

		//----- Renderthread
		void _t_initRenderer(TextureAtlas* atlas, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr);
		RenderableLayer* _t_createRenderableLayer(XE::Uint32 id, const XE::Uint16 atlasId = 0);
		void _t_destroyRenderableLayer(RenderableLayer* layer);
	//	void _t_update();
		//-----------
				
		void addWlayer(WLayer* wlayer);
		void removeWlayer(WLayer* wlayer);
		
		///update (in mainthread)
		void update();
		
		void redrawAllLayers();
		//void swappedBuffer(bool swapped);
		
	private:
		
		bool _swappedBuffer;
		GraphicsManager&  m_graphMgr;

		std::vector<WLayer*> m_wLayers;

		//----- Renderthread		
		std::vector<RenderableLayer*> _t_renderableLayerPtrs;
		Ogre::SceneManager* _t_OgreSceneMgrPtr;
		//-----------


		float m_height;
		float m_width;
	};

} // ns XE


#endif