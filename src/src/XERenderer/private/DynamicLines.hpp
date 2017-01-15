/*
 * =====================================================================================
 *
 *       Filename:  BtOgreExtras.h
 *
 *    Description:  Contains the Ogre Mesh to Bullet Shape converters.
 *
 *        Version:  1.0
 *        Created:  27/12/2008 01:45:56 PM
 *
 *         Author:  Nikhilesh (nikki)
 modified: Nuke
 *
 * =====================================================================================
 */

#ifndef __DYNAMICLINES_HPP__
#define __DYNAMICLINES_HPP__

//#include <bullet/btBulletDynamicsCommon.h>
#include <Ogre/OgreMain/include/OgreSimpleRenderable.h>
#include <Ogre/OgreMain/include/OgreCamera.h>
#include <Ogre/OgreMain/include/OgreHardwareBufferManager.h>
#include <Ogre/OgreMain/include/OgreMaterialManager.h>
#include <Ogre/OgreMain/include/OgreTechnique.h>
#include <Ogre/OgreMain/include/OgrePass.h>
#include <Ogre/OgreMain/include/OgreSceneNode.h>

#include <Ogre/OgreMain/include/OgreLogManager.h>
#include <Ogre/OgreMain/include/OgreManualObject2.h>
//#include <XERenderer/private/ManualObject.hpp>


#include <XERenderer/private/DynamicRenderable.hpp>

namespace Ogre
{
	class Vector3;
}

namespace XE
{

	class DynamicLines : public Ogre::ManualObject
	{
		//typedef Ogre::Vector3 Vector3;
		typedef Ogre::Quaternion Quaternion;
		typedef Ogre::Camera Camera;
		typedef float Real;
		typedef Ogre::OperationType OperationType;

	public:
		/// Constructor - see setOperationType() for description of argument.
		DynamicLines( Ogre::IdType id, Ogre::ObjectMemoryManager* objManager, Ogre::SceneManager* sceneMgr, OperationType opType = Ogre::OperationType::OT_LINE_STRIP);
		virtual ~DynamicLines();

		/// Add a point to the point list
		void addPoint(const Ogre::Vector3 &p);
		/// Add a point to the point list
		void addPoint(Real x, Real y, Real z);

		/// Change the location of an existing point in the point list
		void setPoint(unsigned short index, const Ogre::Vector3 &value);

		/// Return the location of an existing point in the point list
		const Ogre::Vector3& getPoint(unsigned short index) const;

		/// Return the total number of points in the point list
		unsigned short getNumPoints(void) const;

		/// Remove all points from the point list
		void clear();

		/// Call this to update the hardware buffer after making changes.
		void update();

		/** Set the type of operation to draw with.
		 * @param opType Can be one of
		 *    - RenderOperation::OT_LINE_STRIP
		 *    - RenderOperation::OT_LINE_LIST
		 *    - RenderOperation::OT_POINT_LIST
		 *    - RenderOperation::OT_TRIANGLE_LIST
		 *    - RenderOperation::OT_TRIANGLE_STRIP
		 *    - RenderOperation::OT_TRIANGLE_FAN
		 *    The default is OT_LINE_STRIP.
		 */
		void setOperationType(OperationType opType);
		OperationType getOperationType() const;


		std::vector<Ogre::Vector3> _t_Points;

	protected:
		/// Implementation DynamicRenderable, creates a simple vertex-only decl
		virtual void createVertexDeclaration();
		/// Implementation DynamicRenderable, pushes point list out to hardware memory
		virtual void fillHardwareBuffers();


	private:
		Ogre::OperationType m_operationType;

		bool mDirty;
	};

} // namespace XE

#endif // __DYNAMICLINES_HPP__





