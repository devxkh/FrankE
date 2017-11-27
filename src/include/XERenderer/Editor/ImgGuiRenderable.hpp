#pragma once


#include <XESystem/SystemConfig.hpp>
//#include <Ogre/OgreMain/include/OgreManualObject2.h>
#include <Ogre/OgreMain/include/OgreMovableObject.h>
#include <Ogre/OgreMain/include/OgreRenderable.h>

#include <XERenderer/private/ScreenRenderable.hpp>

#include <Compositor/Pass/OgreCompositorPass.h>
#include <Compositor/Pass/OgreCompositorPassDef.h>
#include <Compositor/Pass/OgreCompositorPassProvider.h>

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

	class ImGUIPassDef : public Ogre::CompositorPassDef
	{
	public:
		ImGUIPassDef(Ogre::CompositorTargetDef *parentTargetDef)
			: Ogre::CompositorPassDef(Ogre::PASS_CUSTOM, parentTargetDef)
		{
		}
	};

	// TODO: The compositor manager allows adding this pass to any number of targets,
	// but ImGUI was designed to handle one window target only. For example,
	// when we add the pass to multiple targets, all RTTLayers would be unnecessarily updated multiple times.
	class ImGUIPass : public Ogre::CompositorPass
	{
	public:
		ImGUIPass(const Ogre::CompositorPassDef *definition, const Ogre::CompositorChannel &target,
			Ogre::CompositorNode *parentNode, Ogre::SceneManager* sceneMgr);

		virtual void execute(const Ogre::Camera *lodCameraconst);
	private:
		Ogre::SceneManager* m_sceneMgr;
	};

	// The factory for the ImGUI compositor pass. Note that only one provider can be
	// registered with Ogre at a time, which is why we have exposed the ImGUIPass and ImGUIPassDef classes
	// publicly in this header. If users need their own custom passes, they can implement their own provider
	// which would return either a ImGUI pass or other custom passes depending on the customId.
	class ImGUICompositorPassProvider : public Ogre::CompositorPassProvider
	{
	public:
		Ogre::CompositorPassDef* addPassDef(Ogre::CompositorPassType passType,
			Ogre::IdString customId,
			Ogre::CompositorTargetDef *parentTargetDef,
			Ogre::CompositorNodeDef *parentNodeDef)
		{
			if (customId == mPassId)
				return OGRE_NEW ImGUIPassDef(parentTargetDef);
		}

		Ogre::CompositorPass* addPass(const Ogre::CompositorPassDef *definition, Ogre::Camera *defaultCamera,
			Ogre::CompositorNode *parentNode, const Ogre::CompositorChannel &target,
			Ogre::SceneManager *sceneManager)
		{
			return OGRE_NEW ImGUIPass(definition, target, parentNode, sceneManager);
		}

		static Ogre::IdString mPassId;
	};


	class ImgGuiMovableObject: public Ogre::MovableObject
	{
	public :
		ImgGuiMovableObject(Uint32 id, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr);
		
		~ImgGuiMovableObject();

		// MovableObject overrides
		/** @copydoc MovableObject::getMovableType. */
		const Ogre::String& getMovableType(void) const;

		
		Ogre::SceneManager* _t_OgreSceneMgrPtr;
		Ogre::ObjectMemoryManager* _t_objectMemoryManager;

		Ogre::SceneManager* m_sceneMgr;

		Ogre::SceneNode* m_sceneNode;

		//called from Ogre::Renderable
		Ogre::OperationType mOperationType;
	};

	class ImgGuiRenderable :  public ScreenRenderable
	{
	public:

		ImgGuiRenderable(GUIRenderer& guiRenderer, ImgGuiMovableObject* imgGuiMovableObject);


		~ImgGuiRenderable();


		void updateVertexData(const ImDrawVert* vtxBuf, const ImDrawIdx* idxBuf, unsigned int vtxCount, unsigned int idxCount);

		// Renderable overrides
		/** @copydoc Renderable::getRenderOperation. */
		virtual void getRenderOperation(Ogre::v1::RenderOperation& op, bool casterPass) OGRE_OVERRIDE;

		/** @copydoc Renderable::getWorldTransforms. */
		virtual void getWorldTransforms(Ogre::Matrix4* xform) const OGRE_OVERRIDE;
		/** @copydoc Renderable::getLights. */
		virtual const Ogre::LightList &getLights(void) const OGRE_OVERRIDE { return m_ImgGuiMovableObject->queryLights(); }
		/** @copydoc Renderable::getCastsShadows. */
		virtual bool getCastsShadows(void) const { return false; }


		Ogre::TexturePtr mFontTex;

		ImgGuiMovableObject* m_ImgGuiMovableObject;

	protected:


	private:

		mutable Ogre::Matrix4 mTransform;

		void clear();

		bool _initialized;

		Ogre::VertexArrayObject * m_Vao;
		Ogre::VaoManager * m_VaoManager;
		Ogre::VertexElement2Vec m_VertexElements;

		Ogre::VertexBufferPacked *m_vertexBuffer;
		Ogre::IndexBufferPacked* m_indexBuffer;

		GUIRenderer& m_guiRenderer;		
		Uint32 m_currentVtxCount;		
		Uint32 m_currentIdxCount;
		
		
		Ogre::Camera* m_camera;
	};
}