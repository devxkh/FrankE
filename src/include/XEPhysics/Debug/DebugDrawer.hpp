/*
 * =====================================================================================
 *
 *       Filename:  BtXEExtras.h
 *
 *    Description:  Contains the XE Mesh to Bullet Shape converters.
 *
 *        Version:  1.0
 *        Created:  27/12/2008 01:45:56 PM
 *
 *         Author:  Nikhilesh (nikki)
		modified: Konrad Huber
 *
 * =====================================================================================
 */

#ifndef __DEBUGDRAWER_HPP_
#define __DEBUGDRAWER_HPP_

#include <bullet/btBulletDynamicsCommon.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreQuaternion.h>
#include <XERenderer/DrawDynamicLines.hpp>

namespace XE
{
	//forwarding
	class DynamicLines;
	class Scene;

//Converts from and to Bullet and XE stuff. Pretty self-explanatory.
class Convert
{
public:
    Convert() {};
    ~Convert() {};

    static btQuaternion toBullet(const Ogre::Quaternion &q)
    {
        return btQuaternion(q.x, q.y, q.z, q.w);
    }
    static btVector3 toBullet(const Ogre::Vector3 &v)
    {
        return btVector3(v.x, v.y, v.z);
    }

    static Ogre::Quaternion toXE(const btQuaternion &q)
    {
        return Ogre::Quaternion(q.w(), q.x(), q.y(), q.z());
    }
    static Ogre::Vector3 toXE(const btVector3 &v)
    {
        return Ogre::Vector3(v.x(), v.y(), v.z());
    }
};

class DebugDrawer : public btIDebugDraw
{

public:

	DebugDrawer(Scene& scene, btDynamicsWorld *world);
	~DebugDrawer();
	
	void step();

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	void reportErrorWarning(const char* warningString);

	void draw3dText(const btVector3& location, const char* textString);

    //0 for off, anything else for on.
	void setDebugMode(int isOn);

    //0 for off, anything else for on.
	int getDebugMode() const;
protected:

    btDynamicsWorld *mWorld;
    bool mDebugOn;
private:
	DrawDynamicLines m_DrawDynamicLines;

};

} //namespace XE

#endif // __DEBUGDRAWER_HPP_





