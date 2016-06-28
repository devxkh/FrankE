#include <XEngine/Components/Body.hpp>


namespace XE
{
	BodyComponent::BodyComponent()
		: m_bodyDirection(0, 0, 0)
		, m_bodyGoalDirection(1, 0, 0, 0)
		, m_id(0)
		, m_parent(nullptr)
		, mYawFixed(true)
		, mYawFixedAxis(Ogre::Vector3::UNIT_Y)
		,mPosition(0,0,0),
		 _isDirty(true)	
		,_isNetIDDirty(true)
		,mOrientation(1,0,0,0),
		mScale(1,1,1),
		mDerivedPosition(0,0,0),
		mDerivedOrientation(1,0,0,0),
		mDerivedScale(1,1,1),
		mDerivedTransform(),
		mInheritOrientation(true),
		mInheritScale(true)
	{
	}

	BodyComponent::BodyComponent(const XFBType::BodyComponent* transform)
		:
		m_bodyDirection(0, 0, 0)
		, m_bodyGoalDirection(1, 0, 0, 0)
		, m_id(0)
		, mYawFixed(true)
		, mYawFixedAxis(Ogre::Vector3::UNIT_Y)
		,mPosition(0, 0, 0),
		mOrientation(1, 0, 0, 0),
		mScale(1, 1, 1),
		mDerivedPosition(0, 0, 0),
		mDerivedOrientation(1, 0, 0, 0),
		mDerivedScale(1, 1, 1),
		mDerivedTransform(),
		mInheritOrientation(true),
		mInheritScale(true)
		,_isDirty(true)
		, _isNetIDDirty(true)
		, m_parent(nullptr)
	{
		setPosition(transform->position()->x(), transform->position()->y(), transform->position()->z());

		setScale(transform->scale()->x(), transform->scale()->y(), transform->scale()->z());

		setOrientation(transform->rotation()->w(), transform->rotation()->x(), transform->rotation()->y(), transform->rotation()->z());
	}


	void BodyComponent::isDirty(bool isDirty)
	{
		_isDirty = isDirty;

		if(isDirty)
			_isNetIDDirty = true; //only set to false in serversystem!

		for each (auto& child in m_children)
		{
			child->isDirty(_isDirty);
		}
	}

	//-----------------------------------------------------------------------
	void BodyComponent::setFixedYawAxis(bool useFixed, const Ogre::Vector3& fixedAxis)
	{
		mYawFixed = useFixed;
		mYawFixedAxis = fixedAxis;
	}

	//-----------------------------------------------------------------------
	void BodyComponent::yaw(const Ogre::Radian& angle, TransformSpace relativeTo)
	{
		if (mYawFixed)
		{
			rotate(mYawFixedAxis, angle, relativeTo);
		}
		else
		{
			rotate(Ogre::Vector3::UNIT_Y, angle, relativeTo);
		}

	}
	//-----------------------------------------------------------------------
	void BodyComponent::setDirection(Ogre::Real x, Ogre::Real y, Ogre::Real z, TransformSpace relativeTo,
		const Ogre::Vector3& localDirectionVector)
	{
		setDirection(Ogre::Vector3(x, y, z), relativeTo, localDirectionVector);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::setDirection(const Ogre::Vector3& vec, TransformSpace relativeTo,
		const Ogre::Vector3& localDirectionVector)
	{
		// Do nothing if given a zero vector
		if (vec == Ogre::Vector3::ZERO) return;

		_updateFromParent();

		// The direction we want the local direction point to
		Ogre::Vector3 targetDir = vec.normalisedCopy();

		const bool inheritOrientation = mInheritOrientation;

		// Transform target direction to world space
		switch (relativeTo)
		{
		case TS_PARENT:
			if (inheritOrientation)
			{
				if (m_parent)
				{
					targetDir = m_parent->_getDerivedOrientation() * targetDir;
				}
			}
			break;
		case TS_LOCAL:
			targetDir = _getDerivedOrientation() * targetDir;
			break;
		case TS_WORLD:
			// default orientation
			break;
		}

		// Calculate target orientation relative to world space
		Ogre::Quaternion targetOrientation;
		if (mYawFixed)
		{
			// Calculate the quaternion for rotate local Z to target direction
			Ogre::Vector3 xVec = mYawFixedAxis.crossProduct(targetDir);
			xVec.normalise();
			Ogre::Vector3 yVec = targetDir.crossProduct(xVec);
			yVec.normalise();
			Ogre::Quaternion unitZToTarget = Ogre::Quaternion(xVec, yVec, targetDir);

			if (localDirectionVector == Ogre::Vector3::NEGATIVE_UNIT_Z)
			{
				// Specail case for avoid calculate 180 degree turn
				targetOrientation =
					Ogre::Quaternion(-unitZToTarget.y, -unitZToTarget.z, unitZToTarget.w, unitZToTarget.x);
			}
			else
			{
				// Calculate the quaternion for rotate local direction to target direction
				Ogre::Quaternion localToUnitZ = localDirectionVector.getRotationTo(Ogre::Vector3::UNIT_Z);
				targetOrientation = unitZToTarget * localToUnitZ;
			}
		}
		else
		{
			const Ogre::Quaternion& currentOrient = _getDerivedOrientation();

			// Get current local direction relative to world space
			Ogre::Vector3 currentDir = currentOrient * localDirectionVector;

			if ((currentDir + targetDir).squaredLength() < 0.00005f)
			{
				// Oops, a 180 degree turn (infinite possible rotation axes)
				// Default to yaw i.e. use current UP
				targetOrientation =
					Ogre::Quaternion(-currentOrient.y, -currentOrient.z, currentOrient.w, currentOrient.x);
			}
			else
			{
				// Derive shortest arc to new direction
				Ogre::Quaternion rotQuat = currentDir.getRotationTo(targetDir);
				targetOrientation = rotQuat * currentOrient;
			}
		}

		// Set target orientation, transformed to parent space
		if (m_parent && inheritOrientation)
			setOrientation(m_parent->_getDerivedOrientation().UnitInverse() * targetOrientation);
		else
			setOrientation(targetOrientation);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::lookAt(const Ogre::Vector3& targetPoint, TransformSpace relativeTo,
		const Ogre::Vector3& localDirectionVector)
	{
		// Calculate ourself origin relative to the given transform space
		Ogre::Vector3 origin;
		switch (relativeTo)
		{
		default:    // Just in case
		case TS_WORLD:
			origin = _getDerivedPosition();
			break;
		case TS_PARENT:
			origin = mPosition; // ->getAsOgre::Vector3(origin, mIndex);
			break;
		case TS_LOCAL:
			origin = Ogre::Vector3::ZERO;
			break;
		}

		setDirection(targetPoint - origin, relativeTo, localDirectionVector);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::_updateFromParent(void)
	{
		if (m_parent)
			m_parent->_updateFromParent();

		updateFromParentImpl();
	}
	//-----------------------------------------------------------------------
	void BodyComponent::updateFromParentImpl(void)
	{
		if (!isDirty())
			return;

		if (!m_parent)
		{
			mDerivedPosition = mPosition;
			mDerivedOrientation = mOrientation;
			mDerivedScale = mScale;
		}
		else
		{
			// Scale own position by parent scale, NB just combine
			// as equivalent axes, no shearing
			mDerivedScale = m_parent->mDerivedScale * (mScale);

			// Combine orientation with that of parent
			mDerivedOrientation = m_parent->mDerivedOrientation * (mOrientation);

			// Change position vector based on parent's orientation & scale
			mDerivedPosition = m_parent->mDerivedOrientation * (m_parent->mDerivedScale * (mPosition));

			// Add altered position vector to parents
			mDerivedPosition += m_parent->mDerivedPosition;

		}
	
		isDirty(false);
	}

	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::getOrientation() const
	{
		return mOrientation;
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setOrientation(Ogre::Quaternion q)
	{
		assert(!q.isNaN() && "Invalid orientation supplied as parameter");
		q.normalise();
		mOrientation = q;

		isDirty(true);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setOrientation(Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z)
	{
		setOrientation(Ogre::Quaternion(w, x, y, z));
	}

	//-----------------------------------------------------------------------
	void BodyComponent::setPosition(const Ogre::Vector3& pos)
	{
		assert(!pos.isNaN() && "Invalid vector supplied as parameter");
		mPosition = pos;

		isDirty(true);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z)
	{
		setPosition(Ogre::Vector3(x, y, z));
	}
	//-----------------------------------------------------------------------
	const Ogre::Vector3& BodyComponent::getPosition(void) const
	{
		return mPosition;
	}
	//-----------------------------------------------------------------------
	Ogre::Matrix3& BodyComponent::getLocalAxes(void) const
	{
		Ogre::Matrix3 retVal;
		mOrientation.ToRotationMatrix(retVal);

		/* Equivalent code (easier to visualize):
		axisX = q.xAxis();
		axisY = q.yAxis();
		axisZ = q.zAxis();

		return Matrix3(axisX.x, axisY.x, axisZ.x,
		axisX.y, axisY.y, axisZ.y,
		axisX.z, axisY.z, axisZ.z);*/

		return retVal;
	}

	//-----------------------------------------------------------------------
	void BodyComponent::translate(const Ogre::Vector3& d, TransformSpace relativeTo)
	{
		switch (relativeTo)
		{
		case TS_LOCAL:
			// position is relative to parent so transform downwards
			mPosition += mOrientation * d;
			break;
		case TS_WORLD:
			// position is relative to parent so transform upwards
			if (m_parent)
			{
				mPosition += (m_parent->_getDerivedOrientation().Inverse() * d) / m_parent->_getDerivedScale();
			}
			else
			{
				mPosition += d;
			}
			break;
		case TS_PARENT:
			mPosition += d;
			break;
		}		

		isDirty(true);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::translate(Ogre::Real x, Ogre::Real y, Ogre::Real z, TransformSpace relativeTo)
	{
		Ogre::Vector3 v(x, y, z);
		translate(v, relativeTo);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::translate(const Ogre::Matrix3& axes, const Ogre::Vector3& move, TransformSpace relativeTo)
	{
		Ogre::Vector3 derived = axes * move;
		translate(derived, relativeTo);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::translate(const Ogre::Matrix3& axes, Ogre::Real x, Ogre::Real y, Ogre::Real z, TransformSpace relativeTo)
	{
		Ogre::Vector3 d(x, y, z);
		translate(axes, d, relativeTo);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::roll(const Ogre::Radian& angle, TransformSpace relativeTo)
	{
		rotate(Ogre::Vector3::UNIT_Z, angle, relativeTo);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::pitch(const Ogre::Radian& angle, TransformSpace relativeTo)
	{
		rotate(Ogre::Vector3::UNIT_X, angle, relativeTo);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::rotate(const Ogre::Vector3& axis, const Ogre::Radian& angle, TransformSpace relativeTo)
	{
		Ogre::Quaternion q;
		q.FromAngleAxis(angle, axis);
		rotate(q, relativeTo);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::rotate(const Ogre::Quaternion& q, TransformSpace relativeTo)
	{
		// Normalise quaternion to avoid drift
		Ogre::Quaternion qnorm = q;
		qnorm.normalise();

		switch (relativeTo)
		{
		case TS_PARENT:
			// Rotations are normally relative to local axes, transform up
			mOrientation = qnorm * mOrientation;
			break;
		case TS_WORLD:
			// Rotations are normally relative to local axes, transform up
			mOrientation = mOrientation * _getDerivedOrientation().Inverse()
				* qnorm * _getDerivedOrientation();
			break;
		case TS_LOCAL:
			// Note the order of the mult, i.e. q comes after
			mOrientation = mOrientation * qnorm;
			break;
		}	

		isDirty(true);
	}

	//-----------------------------------------------------------------------
	void BodyComponent::_setDerivedPosition(const Ogre::Vector3& pos)
	{
		//find where the node would end up in parent's local space
		if (m_parent)
			setPosition(m_parent->convertWorldToLocalPosition(pos));
	}
	//-----------------------------------------------------------------------
	void BodyComponent::_setDerivedOrientation(const Ogre::Quaternion& q)
	{
		//find where the node would end up in parent's local space
		if (m_parent)
			setOrientation(m_parent->convertWorldToLocalOrientation(q));
	}

	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::_getDerivedOrientation(void) const
	{
		
		return mDerivedOrientation;
	}
	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::_getDerivedOrientationUpdated(void)
	{
		_updateFromParent();
		return mDerivedOrientation;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::_getDerivedPosition(void) const
	{
		
		return mDerivedPosition;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::_getDerivedPositionUpdated(void)
	{
		_updateFromParent();
		return mDerivedPosition;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::_getDerivedScale(void) const
	{
		
		return mDerivedScale;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::_getDerivedScaleUpdated(void)
	{
		_updateFromParent();
		return mDerivedScale;
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::convertWorldToLocalPosition(const Ogre::Vector3 &worldPos)
	{
		return mDerivedOrientation.Inverse() * (worldPos - (mDerivedPosition)) / (mDerivedScale);
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::convertLocalToWorldPosition(const Ogre::Vector3 &localPos)
	{
		return ((mDerivedOrientation)* (localPos * (mDerivedScale)) ) + (mDerivedPosition);
	}

	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::convertWorldToLocalOrientation(const Ogre::Quaternion &worldOrientation)
	{
		return mDerivedOrientation.Inverse() * worldOrientation;
	}
	//-----------------------------------------------------------------------
	Ogre::Quaternion BodyComponent::convertLocalToWorldOrientation(const Ogre::Quaternion &localOrientation)
	{

		return mDerivedOrientation * localOrientation;
	}

	//-----------------------------------------------------------------------
	void BodyComponent::setScale(const Ogre::Vector3& inScale)
	{
		assert(!inScale.isNaN() && "Invalid vector supplied as parameter");
		mScale = inScale;	

		isDirty(true);
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z)
	{
		setScale(Ogre::Vector3(x, y, z));
	}
	//-----------------------------------------------------------------------
	Ogre::Vector3 BodyComponent::getScale(void) const
	{
		return mScale;
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setInheritOrientation(bool inherit)
	{
		mInheritOrientation = inherit;
		
	}
	//-----------------------------------------------------------------------
	bool BodyComponent::getInheritOrientation(void) const
	{
		return mInheritOrientation;
	}
	//-----------------------------------------------------------------------
	void BodyComponent::setInheritScale(bool inherit)
	{
		mInheritScale = inherit;
		
	}
	//-----------------------------------------------------------------------
	bool BodyComponent::getInheritScale(void) const
	{
		return mInheritScale;
	}
	//-----------------------------------------------------------------------
	void BodyComponent::scale(const Ogre::Vector3& inScale)
	{
		mScale *= inScale;	
	}
	//-----------------------------------------------------------------------
	void BodyComponent::scale(Ogre::Real x, Ogre::Real y, Ogre::Real z)
	{
		scale(Ogre::Vector3(x, y, z));
	}
}