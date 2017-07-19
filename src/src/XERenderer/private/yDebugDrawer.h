#ifndef DebugDrawer_h__
#define DebugDrawer_h__


#include "OgreFrameListener.h"
#include "LinearMath/btIDebugDraw.h"

namespace XE {

	class yDebugDrawer : public btIDebugDraw, public Ogre::FrameListener {
	public:
		yDebugDrawer();
		~yDebugDrawer();
		//static yDebugDrawer &getSingleton();
		void init();
		void deinit();
		void debugPhysics(bool enable);
		virtual void     drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);
		virtual void     drawTriangle(const btVector3 &v0, const btVector3 &v1, const btVector3 &v2, const btVector3 &color, btScalar) { (void)v0; (void)v1; (void)v2; (void)color; }
		virtual void     drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) { (void)PointOnB; (void)normalOnB; (void)distance; (void)lifeTime; (void)color; }
		virtual void     reportErrorWarning(const char *warningString) { (void)warningString; }
		virtual void     draw3dText(const btVector3 &location, const char *textString) { (void)location; (void)textString; }
		virtual void     setDebugMode(int debugMode);
		virtual int     getDebugMode() const;

	protected:
		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameEnded(const Ogre::FrameEvent& evt);

	private:

		yDebugDrawer(yDebugDrawer const&); //don't implement!
		void operator=(yDebugDrawer const&); //don't implement!
	
		Ogre::SceneManager* sceneManager;
		DebugDrawModes               debugModes;

		bool isDebuggingPhysics;

		Ogre::VertexBufferPacked *pVertexBuffer;
		int vertexCount;
		Ogre::Item *item;
		Ogre::Real* meshVertices;
		int vertIndex;
		Ogre::VertexArrayObject *vao;
	};

}

#endif // DebugDrawer_h__
