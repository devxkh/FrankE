#pragma once

#include <XESystem/SystemConfig.hpp>
#include <XESystem/TransportData.hpp>
#include <XEDAL/Objects/FBEngineTypes_generated.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreMatrix4.h>

namespace XE
{
	class Scene;

	/// Transform space for translations and rotations.
	enum TransformSpace
	{
		TS_LOCAL = 0,
		TS_PARENT,
		TS_WORLD
	};

	//Component
	struct BodyComponent {

		BodyComponent();

		BodyComponent(const XFBType::BodyComponent* transform);
		
		~BodyComponent();

		/// set parent scene node. Retains the world transform.
		void setParent(BodyComponent* parent) { m_parent = parent; }
		
		/// Return parent scene node.
		BodyComponent* getParent() const { return m_parent; }

		/// Return scene.
		Scene* getScene() const { return m_scene; }

		/// Return whether is enabled. Disables nodes effectively disable all their components.
		bool IsEnabled() const { return m_isEnabled; }
		
		/// Return whether transform has changed and world transform needs recalculation.
		bool isDirty() const { return _isDirty; }

		/// Return immediate child scene nodes.
		const std::vector<std::shared_ptr<BodyComponent> >& getChildren() const { return m_children; }

		void isDirty(bool isDirty);
		
		/// set scene. Called by Scene.
	//	void setScene(Scene* scene);
		/// set enabled/disabled state with optional recursion. Optionally affect the remembered enable state.
		void setEnabled(bool enable, bool recursive, bool storeSelf)
		{
			m_isEnabled = enable;
		}


		/** Tells the node whether to yaw around it's own local Y axis or a fixed axis of choice.
		@remarks
		This method allows you to change the yaw behaviour of the node - by default, it
		yaws around it's own local Y axis when told to yaw with TS_LOCAL, this makes it
		yaw around a fixed axis.
		You only really need this when you're using auto tracking (see setAutoTracking,
		because when you're manually rotating a node you can specify the TransformSpace
		in which you wish to work anyway.
		@param
		useFixed If true, the axis passed in the second parameter will always be the yaw axis no
		matter what the node orientation. If false, the node returns to it's default behaviour.
		@param
		fixedAxis The axis to use if the first parameter is true.
		*/
		void setFixedYawAxis(bool useFixed, const Ogre::Vector3& fixedAxis = Ogre::Vector3::UNIT_Y);

		bool isYawFixed(void) const { return mYawFixed; }

		/** Sets the node's direction vector ie it's local -z.
		@remarks
		Note that the 'up' vector for the orientation will automatically be
		recalculated based on the current 'up' vector (i.e. the roll will
		remain the same). If you need more control, use setOrientation.
		@param x,y,z The components of the direction vector
		@param relativeTo The space in which this direction vector is expressed
		@param localDirectionVector The vector which normally describes the natural
		direction of the node, usually -Z
		*/
		virtual void setDirection(Ogre::Real x, Ogre::Real y, Ogre::Real z,
			TransformSpace relativeTo = TransformSpace::TS_LOCAL,
			const Ogre::Vector3& localDirectionVector = Ogre::Vector3::NEGATIVE_UNIT_Z);

		/** Sets the node's direction vector ie it's local -z.
		@remarks
		Note that the 'up' vector for the orientation will automatically be
		recalculated based on the current 'up' vector (i.e. the roll will
		remain the same). If you need more control, use setOrientation.
		@param vec The direction vector
		@param relativeTo The space in which this direction vector is expressed
		@param localDirectionVector The vector which normally describes the natural
		direction of the node, usually -Z
		*/
		virtual void setDirection(const Ogre::Vector3& vec, TransformSpace relativeTo = TransformSpace::TS_LOCAL,
			const Ogre::Vector3& localDirectionVector = Ogre::Vector3::NEGATIVE_UNIT_Z);
		/** Points the local -Z direction of this node at a point in space.
		@param targetPoint A vector specifying the look at point.
		@param relativeTo The space in which the point resides
		@param localDirectionVector The vector which normally describes the natural
		direction of the node, usually -Z
		*/
		virtual void lookAt(const Ogre::Vector3& targetPoint, TransformSpace relativeTo,
			const Ogre::Vector3& localDirectionVector = Ogre::Vector3::NEGATIVE_UNIT_Z);
	
		//------------------------ Node
		/** Triggers the node to update it's combined transforms.
		@par
		This method is called internally by Ogre to ask the node
		to update it's complete transformation based on it's parents
		derived transform.
		*/
		void _updateFromParent(void);

		/** Class-specific implementation of _updateFromParent.
		@remarks
		Splitting the implementation of the update away from the update call
		itself allows the detail to be overridden without disrupting the
		general sequence of updateFromParent (e.g. raising events)
		*/
		virtual void updateFromParentImpl(void);

		/** Returns a Ogre::Quaternion representing the nodes orientation.
		@remarks
		Don't call this function too often, as we need to convert from SoA
		*/
		virtual_l2 Ogre::Quaternion getOrientation() const;

		/** Sets the orientation of this node via a Ogre::Quaternion.
		@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
		Don't call this function too often, as we need to convert to SoA
		@par
		Note that rotations are oriented around the node's origin.
		*/
		virtual_l1 void setOrientation(Ogre::Quaternion q);

		/** Sets the orientation of this node via Ogre::Quaternion parameters.
		@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
		Don't call this function too often, as we need to convert to SoA
		@par
		Note that rotations are oriented around the node's origin.
		*/
		virtual_l1 void setOrientation(Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z);

		/** Sets the position of the node relative to it's parent.
		@remarks
		Don't call this function too often, as we need to convert to SoA
		*/
		virtual_l1 void setPosition(const Ogre::Vector3& pos);

		/** Sets the position of the node relative to it's parent.
		@remarks
		Don't call this function too often, as we need to convert to SoA
		*/
		virtual_l1 void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);

		/** Gets the position of the node relative to it's parent.
		@remarks
		Don't call this function too often, as we need to convert from SoA
		*/
		virtual_l2 const Ogre::Vector3& getPosition(void) const;

		/** Sets the scaling factor applied to this node.
		@remarks
		Scaling factors, unlike other transforms, are not always inherited by child nodes.
		Whether or not scalings affect the size of the child nodes depends on the setInheritScale
		option of the child. In some cases you want a scaling factor of a parent node to apply to
		a child node (e.g. where the child node is a part of the same object, so you want it to be
		the same relative size based on the parent's size), but not in other cases (e.g. where the
		child node is just for positioning another object, you want it to maintain it's own size).
		The default is to inherit as with other transforms.
		Don't call this function too often, as we need to convert to SoA
		@par
		Note that like rotations, scalings are oriented around the node's origin.
		*/
		virtual_l1 void setScale(const Ogre::Vector3& scale);

		/** Sets the scaling factor applied to this node.
		@remarks
		Scaling factors, unlike other transforms, are not always inherited by child nodes.
		Whether or not scalings affect the size of the child nodes depends on the setInheritScale
		option of the child. In some cases you want a scaling factor of a parent node to apply to
		a child node (e.g. where the child node is a part of the same object, so you want it to be
		the same relative size based on the parent's size), but not in other cases (e.g. where the
		child node is just for positioning another object, you want it to maintain it's own size).
		The default is to inherit as with other transforms.
		Don't call this function too often, as we need to convert to SoA
		@par
		Note that like rotations, scalings are oriented around the node's origin.
		*/
		virtual_l1 void setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z);

		/** Gets the scaling factor of this node.
		@remarks
		Don't call this function too often, as we need to convert from SoA
		*/
		virtual_l2 Ogre::Vector3 getScale(void) const;

		/** Tells the node whether it should inherit orientation from it's parent node.
		@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
		@param inherit If true, this node's orientation will be affected by its parent's orientation.
		If false, it will not be affected.
		*/
		virtual_l2 void setInheritOrientation(bool inherit);

		/** Returns true if this node is affected by orientation applied to the parent node.
		@remarks
		Orientations, unlike other transforms, are not always inherited by child nodes.
		Whether or not orientations affect the orientation of the child nodes depends on
		the setInheritOrientation option of the child. In some cases you want a orientating
		of a parent node to apply to a child node (e.g. where the child node is a part of
		the same object, so you want it to be the same relative orientation based on the
		parent's orientation), but not in other cases (e.g. where the child node is just
		for positioning another object, you want it to maintain it's own orientation).
		The default is to inherit as with other transforms.
		@remarks
		See setInheritOrientation for more info.
		*/
		virtual_l2 bool getInheritOrientation(void) const;

		/** Tells the node whether it should inherit scaling factors from it's parent node.
		@remarks
		Scaling factors, unlike other transforms, are not always inherited by child nodes.
		Whether or not scalings affect the size of the child nodes depends on the setInheritScale
		option of the child. In some cases you want a scaling factor of a parent node to apply to
		a child node (e.g. where the child node is a part of the same object, so you want it to be
		the same relative size based on the parent's size), but not in other cases (e.g. where the
		child node is just for positioning another object, you want it to maintain it's own size).
		The default is to inherit as with other transforms.
		@param inherit If true, this node's scale will be affected by its parent's scale. If false,
		it will not be affected.
		*/
		virtual_l2 void setInheritScale(bool inherit);

		/** Returns true if this node is affected by scaling factors applied to the parent node.
		@remarks
		See setInheritScale for more info.
		*/
		virtual_l2 bool getInheritScale(void) const;

		/** Scales the node, combining it's current scale with the passed in scaling factor.
		@remarks
		This method applies an extra scaling factor to the node's existing scale, (unlike setScale
		which overwrites it) combining it's current scale with the new one. E.g. calling this
		method twice with Ogre::Vector3(2,2,2) would have the same effect as setScale(Vector3(4,4,4)) if
		the existing scale was 1.
		@par
		Note that like rotations, scalings are oriented around the node's origin.
		*/
		virtual_l2 void scale(const Ogre::Vector3& scale);

		/** Scales the node, combining it's current scale with the passed in scaling factor.
		@remarks
		This method applies an extra scaling factor to the node's existing scale, (unlike setScale
		which overwrites it) combining it's current scale with the new one. E.g. calling this
		method twice with Ogre::Vector3(2,2,2) would have the same effect as setScale(Vector3(4,4,4)) if
		the existing scale was 1.
		@par
		Note that like rotations, scalings are oriented around the node's origin.
		*/
		virtual_l2 void scale(Ogre::Real x, Ogre::Real y, Ogre::Real z);

		/** Moves the node along the Cartesian axes.
		@par
		This method moves the node by the supplied vector along the
		world Cartesian axes, i.e. along world x,y,z
		@param d
		Vector with x,y,z values representing the translation.
		@param relativeTo
		The space which this transform is relative to.
		*/
		virtual_l2 void translate(const Ogre::Vector3& d, TransformSpace relativeTo = TransformSpace::TS_PARENT);
		/** Moves the node along the Cartesian axes.
		@par
		This method moves the node by the supplied vector along the
		world Cartesian axes, i.e. along world x,y,z
		@param x
		Real @c x value representing the translation.
		@param y
		Real @c y value representing the translation.
		@param z
		Real @c z value representing the translation.
		@param relativeTo
		The space which this transform is relative to.
		*/
		virtual_l2 void translate(Ogre::Real x, Ogre::Real y, Ogre::Real z, TransformSpace relativeTo = TransformSpace::TS_PARENT);
		/** Moves the node along arbitrary axes.
		@remarks
		This method translates the node by a vector which is relative to
		a custom set of axes.
		@param axes
		A 3x3 Matrix containing 3 column vectors each representing the
		axes X, Y and Z respectively. In this format the standard cartesian
		axes would be expressed as:
		<pre>
		1 0 0
		0 1 0
		0 0 1
		</pre>
		i.e. the identity matrix.
		@param move
		Vector relative to the axes above.
		@param relativeTo
		The space which this transform is relative to.
		*/
		virtual_l2 void translate(const Ogre::Matrix3& axes, const Ogre::Vector3& move, TransformSpace relativeTo = TransformSpace::TS_PARENT);
		/** Moves the node along arbitrary axes.
		@remarks
		This method translates the node by a vector which is relative to
		a custom set of axes.
		@param axes
		A 3x3 Matrix containing 3 column vectors each representing the
		axes X, Y and Z respectively. In this format the standard cartesian
		axes would be expressed as
		<pre>
		1 0 0
		0 1 0
		0 0 1
		</pre>
		i.e. the identity matrix.
		@param x
		The @c x translation component relative to the axes above.
		@param y
		The @c y translation component relative to the axes above.
		@param z
		The @c z translation component relative to the axes above.
		@param relativeTo
		The space which this transform is relative to.
		*/
		virtual_l2 void translate(const Ogre::Matrix3& axes, Ogre::Real x, Ogre::Real y, Ogre::Real z, TransformSpace relativeTo = TransformSpace::TS_PARENT);

		/** Rotate the node around the Z-axis.
		*/
		virtual_l2 void roll(const Ogre::Radian& angle, TransformSpace relativeTo = TransformSpace::TS_LOCAL);

		/** Rotate the node around the X-axis.
		*/
		virtual_l2 void pitch(const Ogre::Radian& angle, TransformSpace relativeTo = TransformSpace::TS_LOCAL);

		/** Rotate the node around the Y-axis.
		*/
		virtual_l2 void yaw(const Ogre::Radian& angle, TransformSpace relativeTo = TransformSpace::TS_LOCAL);

		/** Rotate the node around an arbitrary axis.
		*/
		virtual_l2 void rotate(const Ogre::Vector3& axis, const Ogre::Radian& angle, TransformSpace relativeTo = TransformSpace::TS_LOCAL);

		/** Rotate the node around an aritrary axis using a Quarternion.
		*/
		virtual_l2 void rotate(const Ogre::Quaternion& q, TransformSpace relativeTo = TransformSpace::TS_LOCAL);

		/** Gets a matrix whose columns are the local axes based on
		the nodes orientation relative to it's parent. */
		virtual_l2 Ogre::Matrix3& getLocalAxes(void) const;

		/** Sets the final world position of the node directly.
		@remarks
		It's advisable to use the local setPosition if possible
		*/
		virtual_l2 void _setDerivedPosition(const Ogre::Vector3& pos);

		/** Sets the final world orientation of the node directly.
		@remarks
		It's advisable to use the local setOrientation if possible, this simply does
		the conversion for you.
		*/
		virtual_l2 void _setDerivedOrientation(const Ogre::Quaternion& q);

		/** Gets the orientation of the node as derived from all parents.
		@remarks
		Assumes the caches are already updated. Will trigger an assert
		otherwise.
		@See _getDerivedOrientationUpdated if you need the update process
		to be guaranteed
		*/
		virtual_l2 Ogre::Quaternion _getDerivedOrientation(void) const;

		/** Gets the orientation of the node as derived from all parents.
		@remarks
		Unlike _getDerivedOrientation, this function guarantees the
		cache stays up to date.
		It is strongly advised against calling this function for a large
		number of nodes. Refactor your queries so that they happen
		after SceneManager::UpdateAllTransforms() has been called
		*/
		virtual_l2 Ogre::Quaternion _getDerivedOrientationUpdated(void);

		/** Gets the position of the node as derived from all parents.
		@remarks
		Assumes the caches are already updated. Will trigger an assert
		otherwise.
		@See _getDerivedPositionUpdated if you need the update process
		to be guaranteed
		*/
		virtual_l2 Ogre::Vector3 _getDerivedPosition(void) const;

		/** Gets the position of the node as derived from all parents.
		@remarks
		Unlike _getDerivedPosition, this function guarantees the
		cache stays up to date.
		It is strongly advised against calling this function for a large
		number of nodes. Refactor your queries so that they happen
		after SceneManager::UpdateAllTransforms() has been called
		*/
		virtual_l2 Ogre::Vector3 _getDerivedPositionUpdated(void);

		/** Gets the scaling factor of the node as derived from all parents.
		@remarks
		Assumes the caches are already updated. Will trigger an assert
		otherwise.
		@See _getDerivedScaleUpdated if you need the update process
		to be guaranteed
		*/
		virtual_l2 Ogre::Vector3 _getDerivedScale(void) const;

		/** Gets the scalling factor of the node as derived from all parents.
		@remarks
		Unlike _getDerivedScale, this function guarantees the
		cache stays up to date.
		It is STRONGLY advised against calling this function for a large
		number of nodes. Refactor your queries so that they happen
		after SceneManager::UpdateAllTransforms() has been called
		*/
		virtual_l2 Ogre::Vector3 _getDerivedScaleUpdated(void);
		
		/** Gets the local position, relative to this node, of the given world-space position */
		virtual_l2 Ogre::Vector3 convertWorldToLocalPosition(const Ogre::Vector3 &worldPos);

		/** Gets the world position of a point in the node local space
		useful for simple transforms that don't require a child node.*/
		virtual_l2 Ogre::Vector3 convertLocalToWorldPosition(const Ogre::Vector3 &localPos);

		/** Gets the local orientation, relative to this node, of the given world-space orientation */
		virtual_l2 Ogre::Quaternion convertWorldToLocalOrientation(const Ogre::Quaternion &worldOrientation);

		/** Gets the world orientation of an orientation in the node local space
		useful for simple transforms that don't require a child node.*/
		virtual_l2 Ogre::Quaternion convertLocalToWorldOrientation(const Ogre::Quaternion &localOrientation);

		mutable bool _isNetIDDirty;

		///original sceneid of the entity
		Uint16 sceneId;

		
		const Ogre::Vector3& getTargetPosition();
		void setTargetPosition(const Ogre::Vector3& targetPosition);

		bool hasTargetPosition();
		void setHasTargetPosition(bool hasTargetPosition);

		const Ogre::Vector3& getTargetDirection();
		void setTargetDirection(const Ogre::Vector3& direction);

		Ogre::Real getTargetDistance();
		void setTargetDistance(Ogre::Real distance);

		/// Return world space transform matrix.
		const Ogre::Matrix4& GetWorldTransform() const;

		bool isSelected;

#ifdef CompileEditor
		Ogre::Vector3 _t_nodeScaleStart;
#endif

	protected:
		/// Whether to yaw around a fixed axis.
		bool mYawFixed;
		/// Fixed axis to yaw around
		Ogre::Vector3 mYawFixedAxis;

	private:
		
		bool				m_hasTargetPosition;
		Ogre::Vector3       m_targetPosition;
		Ogre::Vector3       m_targetDirection;
		Ogre::Real			m_targetDistance;


		std::vector<std::shared_ptr<BodyComponent> > m_children;

		/// World transform needs update flag.
		mutable bool _isDirty;
		
		/// Enabled flag.
		bool m_isEnabled;

		/// Parent scene node.
		BodyComponent* m_parent;

		/// Scene (root node.)
		Scene* m_scene;

		Ogre::Vector3 m_bodyDirection;      // player's local intended direction based on WASD keys
		Ogre::Quaternion m_bodyGoalDirection;      // player's local intended direction based on WASD keys

		bool m_hasParent;
		
		Ogre::Vector3        mPosition;

		/// Stores the orientation of a node relative to it's parent.
		Ogre::Quaternion     mOrientation;

		/// Stores the scaling factor applied to a node
		Ogre::Vector3        mScale;

		/// Caches the combined position from all parent nodes.
		Ogre::Vector3        mDerivedPosition;

		/// Caches the combined orientation from all parent nodes.
		Ogre::Quaternion     mDerivedOrientation;

		/// Caches the combined scale from all parent nodes.
		Ogre::Vector3        mDerivedScale;

		/// Caches the full transform into a 4x4 matrix. Note it's not Array form! (It's AoS)
		Ogre::Matrix4             mDerivedTransform;

		/// Stores whether this node inherits orientation from it's parent.
		/// Ours is mInheritOrientation[mIndex]
		bool     mInheritOrientation;

		/// Stores whether this node inherits scale from it's parent.
		/// Ours is mInheritScale[mIndex]
		bool     mInheritScale;
	};

}
