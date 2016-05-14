#ifndef _RENDERABLELAYER_HPP
#define _RENDERABLELAYER_HPP

#include <XESystem/SystemConfig.hpp>
//#include <Ogre/OgreMain/include/OgreManualObject2.h>
#include <Ogre/OgreMain/include/OgreMovableObject.h>
#include <Ogre/OgreMain/include/OgreRenderable.h>

//Ogre::v1
#include <Ogre/OgreMain/include/OgreRenderOperation.h>

#include <vector>
#include <memory>

namespace Ogre {
	class VertexBufferPacked;
	class ObjectMemoryManager;
	class SceneManager;

	typedef std::string String;
}

namespace XE {

	struct Vertex;
	class CameraRenderable;
	class GUIRenderer;
	class RenderableShape;

	class RenderableLayer : public Ogre::MovableObject, public Ogre::Renderable//public Ogre::ManualObject
	{
	public:
		
		RenderableLayer(XE::Uint32 id, GUIRenderer& guiRenderer,
						Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr, const XE::Uint16 atlasId = 0);


		~RenderableLayer();

		// MovableObject overrides
		/** @copydoc MovableObject::getMovableType. */
		const Ogre::String& getMovableType(void) const;

		void updateVertices(std::queue<Vertex>& vertices);

		// Renderable overrides
		/** @copydoc Renderable::getRenderOperation. */
		virtual void getRenderOperation(Ogre::v1::RenderOperation& op, bool casterPass) OGRE_OVERRIDE;

		/** @copydoc Renderable::getWorldTransforms. */
		virtual void getWorldTransforms(Ogre::Matrix4* xform) const OGRE_OVERRIDE {}
		/** @copydoc Renderable::getLights. */
		virtual const Ogre::LightList &getLights(void) const OGRE_OVERRIDE { return queryLights(); }
		/** @copydoc Renderable::getCastsShadows. */
		virtual bool getCastsShadows(void) const { return false; }

	protected:
		 //called from Ogre::Renderable
		Ogre::v1::RenderOperation::OperationType mOperationType;

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

		Uint32 m_currentVertexBufferSize;
		Uint32 m_currentIndexBufferSize;
		Ogre::SceneManager* m_sceneMgr;
		Ogre::SceneNode* m_sceneNodeLines;
	};
}


#endif