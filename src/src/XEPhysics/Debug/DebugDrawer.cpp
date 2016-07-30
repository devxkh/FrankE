#include <XEPhysics/Debug/DebugDrawer.hpp>


//#include <XEEntity/GameEntity.hpp>

namespace XE {

	DebugDrawer::DebugDrawer(Scene& scene, btDynamicsWorld *world)
		:m_DrawDynamicLines(scene),
		mWorld(world),
		mDebugOn(true)
	{
		//mLineDrawer->setVisibilityFlags (1024);
	}

	DebugDrawer::~DebugDrawer()
	{

	}

	void DebugDrawer::step()
	{
		if (mDebugOn)
		{
			//  mWorld->debugDrawWorld();
			m_DrawDynamicLines.update();
			//KH mNode->needUpdate();
			m_DrawDynamicLines.clear();
		}
		else
		{
			m_DrawDynamicLines.clear();
			m_DrawDynamicLines.update();
			//KH mNode->needUpdate();
		}
	}

	void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		m_DrawDynamicLines.addPoint(Convert::toXE(from));
		m_DrawDynamicLines.addPoint(Convert::toXE(to));
	}

	void DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{
		m_DrawDynamicLines.addPoint(Convert::toXE(PointOnB));
		m_DrawDynamicLines.addPoint(Convert::toXE(PointOnB) + (Convert::toXE(normalOnB) * distance * 20));
	}

	void DebugDrawer::reportErrorWarning(const char* warningString)
	{
	//	Ogre::LogManager::getSingleton().logMessage(warningString);
	}

	void DebugDrawer::draw3dText(const btVector3& location, const char* textString)
	{
	}

	//0 for off, anything else for on.
	void DebugDrawer::setDebugMode(int isOn)
	{
		mDebugOn = (isOn == 0) ? false : true;

		if (!mDebugOn)
			m_DrawDynamicLines.clear();
	}

	//0 for off, anything else for on.
	int DebugDrawer::getDebugMode() const
	{
		return mDebugOn;
	}
}
