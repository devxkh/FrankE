#pragma once

#include <XESystem/SystemConfig.hpp>
#include <vector>
#include <list>
#include <memory>
#include <Ogre/OgreMain/include/OgreRenderable.h>
#include <Ogre/OgreMain/include/OgreMovableObject.h>

//Ogre::v1
#include <Ogre/OgreMain/include/OgreRenderOperation.h>

#include <XERenderer/GUI/RenderableShape.hpp>

namespace Ogre
{
	class ObjectMemoryManager;
	class SceneManager;
	class Vector3;
	class ColourValue;
	class ManualObject;
}

namespace XE
{
	typedef std::pair<Ogre::Vector3, Ogre::ColourValue> VertexPair;

	class GraphicsManager;
	class Scene;
	class DebugRenderable;

	/*
	Wrapper class for render dynamic lines
	*/
	class DebugRenderer : public Ogre::MovableObject
	{

	public:
		/// Constructor - see setOperationType() for description of argument.
		DebugRenderer(Uint32 id, Scene& scene, Ogre::ObjectMemoryManager* objManager, float fillAlpha);
		virtual ~DebugRenderer();



		void updateVertices(std::queue<Vertex>& vertices);


		// MovableObject overrides
		/** @copydoc MovableObject::getMovableType. */
		const Ogre::String& getMovableType(void) const;

		/// Add a point to the point list
	//	void addPoint(const Ogre::Vector3 &p);
		/// Add a point to the point list
//		void addPoint(float x, float y, float z);

		/// Change the location of an existing point in the point list
//		void setPoint(unsigned short index, const Ogre::Vector3 &value);

		/// Remove all points from the point list
		void clear();

		/// Call this to update the hardware buffer after making changes.
	//	void update();
		

	private:

		std::vector<std::unique_ptr<DebugRenderable>> _t_renderables;

		float m_fillAlpha;

		GraphicsManager& m_GraphicsManager;
		//modify only in renderthread!
	//	DynamicLines* __t_DynamicLines;
		//Ogre::ManualObject* _t_manualObject;
		Ogre::ObjectMemoryManager* _t_ObjectMemoryManager;
		Ogre::SceneManager* _t_sceneMrg;


		bool m_rendererIsDone;

		//std::vector<Ogre::Vector3> _PointsBuf1;
		//std::vector<Ogre::Vector3> _PointsBuf2;



		Ogre::SceneNode* m_sceneNodeLines;

		bool m_initalized;
	};

	class DebugRenderable : public Ogre::Renderable
	{
	public:

		DebugRenderable(GraphicsManager& gMgr);

		~DebugRenderable();
			
		void updateVertices(std::queue<Vertex>& vertices);
		
		/// Remove all points from the point list
		void clear();

		// Renderable overrides
		/** @copydoc Renderable::getRenderOperation. */
		virtual void getRenderOperation(Ogre::v1::RenderOperation& op, bool casterPass) OGRE_OVERRIDE;

		/** @copydoc Renderable::getWorldTransforms. */
		virtual void getWorldTransforms(Ogre::Matrix4* xform) const OGRE_OVERRIDE {}
		/** @copydoc Renderable::getLights. */
		virtual const Ogre::LightList &getLights(void) const OGRE_OVERRIDE { return mLightList; }
		/** @copydoc Renderable::getCastsShadows. */
		virtual bool getCastsShadows(void) const { return false; }

	protected:
		//called from Ogre::Renderable
		Ogre::v1::RenderOperation::OperationType mOperationType;

	private:
		/// List of lights for this object
		Ogre::LightList mLightList;


		Uint32 m_currentVertexBufferSize;
		Uint32 m_currentIndexBufferSize;


		Ogre::VertexArrayObject * m_Vao;
		Ogre::VaoManager * m_VaoManager;
		Ogre::VertexElement2Vec m_VertexElements;

		Ogre::VertexBufferPacked *m_vertexBuffer;
		Ogre::IndexBufferPacked* m_indexBuffer;
	};

} // namespace XE





