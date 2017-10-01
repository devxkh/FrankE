#pragma once


#include <XESystem/SystemConfig.hpp>
//#include <Ogre/OgreMain/include/OgreManualObject2.h>
#include <Ogre/OgreMain/include/OgreMovableObject.h>
#include <Ogre/OgreMain/include/OgreRenderable.h>

#include <XERenderer/private/ScreenRenderable.hpp>

//Ogre::v1
#include <Ogre/OgreMain/include/OgreRenderOperation.h>

#include <ThirdParty/SDL/include/SDL.h>

#include <vector>
#include <memory>

//forwading
struct ImDrawList;
struct ImDrawVert;
typedef unsigned short ImDrawIdx;

namespace Ogre {

	//forwading
	class VertexBufferPacked;
	class ObjectMemoryManager;
	class SceneManager;

	typedef std::string String;
}

namespace XE {

	//forwading
	struct Vertex;
	class CameraRenderable;
	class GUIRenderer;
	class RenderableShape;

	class ImgGuiRenderable : public Ogre::MovableObject, public ScreenRenderable
	{
	public:

		ImgGuiRenderable(Uint32 id, GUIRenderer& guiRenderer,
			Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr);


		~ImgGuiRenderable();

		// MovableObject overrides
		/** @copydoc MovableObject::getMovableType. */
		const Ogre::String& getMovableType(void) const;

		void updateVertexData(const ImDrawVert* vtxBuf, const ImDrawIdx* idxBuf, unsigned int vtxCount, unsigned int idxCount);

		// Renderable overrides
		/** @copydoc Renderable::getRenderOperation. */
		virtual void getRenderOperation(Ogre::v1::RenderOperation& op, bool casterPass) OGRE_OVERRIDE;

		/** @copydoc Renderable::getWorldTransforms. */
		virtual void getWorldTransforms(Ogre::Matrix4* xform) const OGRE_OVERRIDE {}
		/** @copydoc Renderable::getLights. */
		virtual const Ogre::LightList &getLights(void) const OGRE_OVERRIDE { return queryLights(); }
		/** @copydoc Renderable::getCastsShadows. */
		virtual bool getCastsShadows(void) const { return false; }

		Ogre::SceneNode* m_sceneNodeLines;


		Ogre::SceneManager* m_sceneMgr;
		Ogre::TexturePtr mFontTex;

	protected:
		//called from Ogre::Renderable
		Ogre::OperationType mOperationType;


	private:


		void clear();

		bool _initalizied;
		Ogre::SceneManager* _t_OgreSceneMgrPtr;
		Ogre::ObjectMemoryManager* _t_objectMemoryManager;

		Ogre::VertexArrayObject * m_Vao;
		Ogre::VaoManager * m_VaoManager;
		Ogre::VertexElement2Vec m_VertexElements;

		Ogre::VertexBufferPacked *m_vertexBuffer;
		Ogre::IndexBufferPacked* m_indexBuffer;

		GUIRenderer& m_guiRenderer;		


		
		Ogre::Camera* m_camera;
	};
}