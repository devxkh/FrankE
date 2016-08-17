
# XEPhysics

set(SRC_BULLET_ROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/bullet)
set(SRC_BULLET_COLLISION_ROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/bullet/BulletCollision)
set(SRC_BULLET_DYNAMICS_ROOT ${PROJECT_SOURCE_DIR}/src/ThirdParty/bullet/BulletDynamics)

# ----------------------- bullet -------------------------------
set(XEPhysics_BULLET_SOURCES
    ${SRC_BULLET_ROOT}/btBulletCollisionCommon.h
    ${SRC_BULLET_ROOT}/btBulletDynamicsCommon.h
)
source_group("src" FILES ${XEPhysics_BULLET_SOURCES})


INCLUDE_DIRECTORIES( ${SRC_BULLET_ROOT}  )

SET(BulletCollision_SRCS
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btAxisSweep3.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btBroadphaseProxy.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btDbvt.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btDbvtBroadphase.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btDispatcher.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btMultiSapBroadphase.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btOverlappingPairCache.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btQuantizedBvh.cpp
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btSimpleBroadphase.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btActivatingCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btBoxBoxDetector.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionDispatcher.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionObject.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionWorld.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionWorldImporter.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCompoundCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCompoundCompoundCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btConvexConvexAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btConvex2dConvex2dAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btDefaultCollisionConfiguration.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btEmptyCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btGhostObject.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btHashedSimplePairCache.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btInternalEdgeUtility.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btInternalEdgeUtility.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btManifoldResult.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btSimulationIslandManager.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btUnionFind.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/SphereTriangleDetector.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btBoxShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btBox2dShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btBvhTriangleMeshShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCapsuleShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCollisionShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCompoundShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConcaveShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConeShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexHullShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexInternalShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexPointCloudShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexPolyhedron.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvex2dShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexTriangleMeshShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCylinderShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btEmptyShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btHeightfieldTerrainShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btMinkowskiSumShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btMultimaterialTriangleMeshShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btMultiSphereShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btOptimizedBvh.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btPolyhedralConvexShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btScaledBvhTriangleMeshShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btShapeHull.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btSphereShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btStaticPlaneShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btStridingMeshInterface.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTetrahedronShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleBuffer.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleCallback.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleIndexVertexArray.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleMesh.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleMeshShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btUniformScalingShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btContactProcessing.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGenericPoolAllocator.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactBvh.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactCollisionAlgorithm.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactQuantizedBvh.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactShape.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btTriangleShapeEx.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_box_set.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_contact.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_memory.cpp
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_tri_collision.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btContinuousConvexCollision.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btConvexCast.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btGjkConvexCast.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btGjkEpa2.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btGjkPairDetector.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btPersistentManifold.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btRaycastCallback.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btSubSimplexConvexCast.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btPolyhedralContactClipping.cpp
)

source_group("src\\bullet\\collision" FILES ${BulletCollision_SRCS})


SET(Root_HDRS
	${SRC_BULLET_ROOT}/btBulletCollisionCommon.h
)
SET(BroadphaseCollision_HDRS
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btAxisSweep3.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btBroadphaseInterface.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btBroadphaseProxy.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btDbvt.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btDbvtBroadphase.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btDispatcher.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btMultiSapBroadphase.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btOverlappingPairCache.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btOverlappingPairCallback.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btQuantizedBvh.h
	${SRC_BULLET_COLLISION_ROOT}/BroadphaseCollision/btSimpleBroadphase.h
)
SET(CollisionDispatch_HDRS
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btActivatingCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btBoxBoxCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btBoxBoxDetector.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionConfiguration.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionCreateFunc.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionDispatcher.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionObject.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionObjectWrapper.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionWorld.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCollisionWorldImporter.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCompoundCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btCompoundCompoundCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btConvexConcaveCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btConvexConvexAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btConvex2dConvex2dAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btConvexPlaneCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btDefaultCollisionConfiguration.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btEmptyCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btGhostObject.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btHashedSimplePairCache.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btManifoldResult.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btSimulationIslandManager.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btSphereBoxCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btSphereSphereCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/btUnionFind.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionDispatch/SphereTriangleDetector.h
)
SET(CollisionShapes_HDRS
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btBoxShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btBox2dShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btBvhTriangleMeshShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCapsuleShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCollisionMargin.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCollisionShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCompoundShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConcaveShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConeShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexHullShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexInternalShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexPointCloudShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexPolyhedron.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvex2dShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btConvexTriangleMeshShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btCylinderShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btEmptyShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btHeightfieldTerrainShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btMaterial.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btMinkowskiSumShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btMultimaterialTriangleMeshShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btMultiSphereShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btOptimizedBvh.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btPolyhedralConvexShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btScaledBvhTriangleMeshShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btShapeHull.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btSphereShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btStaticPlaneShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btStridingMeshInterface.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTetrahedronShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleBuffer.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleCallback.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleIndexVertexArray.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleIndexVertexMaterialArray.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleInfoMap.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleMesh.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleMeshShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btTriangleShape.h
	${SRC_BULLET_COLLISION_ROOT}/CollisionShapes/btUniformScalingShape.h
)
SET(Gimpact_HDRS
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btBoxCollision.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btClipPolygon.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btContactProcessing.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGenericPoolAllocator.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGeometryOperations.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactBvh.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactCollisionAlgorithm.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactMassUtil.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactQuantizedBvh.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btGImpactShape.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btQuantization.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/btTriangleShapeEx.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_array.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_basic_geometry_operations.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_bitset.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_box_collision.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_box_set.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_clip_polygon.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_contact.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_geom_types.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_geometry.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_hash_table.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_linear_math.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_math.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_memory.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_radixsort.h
	${SRC_BULLET_COLLISION_ROOT}/Gimpact/gim_tri_collision.h
)
SET(NarrowPhaseCollision_HDRS
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btContinuousConvexCollision.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btConvexCast.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btDiscreteCollisionDetectorInterface.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btGjkConvexCast.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btGjkEpa2.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btGjkPairDetector.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btManifoldPoint.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btPersistentManifold.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btPointCollector.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btRaycastCallback.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btSimplexSolverInterface.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btSubSimplexConvexCast.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btVoronoiSimplexSolver.h
	${SRC_BULLET_COLLISION_ROOT}/NarrowPhaseCollision/btPolyhedralContactClipping.h
)

SET(BulletCollision_HDRS
	${Root_HDRS}
	${BroadphaseCollision_HDRS}
	${CollisionDispatch_HDRS}
	${CollisionShapes_HDRS}
	${Gimpact_HDRS}
	${NarrowPhaseCollision_HDRS}
)


source_group("include\\bullet\\collision" FILES ${BulletCollision_HDRS})

SET(BulletDynamics_SRCS
	${SRC_BULLET_DYNAMICS_ROOT}/Character/btKinematicCharacterController.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btConeTwistConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btContactConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btFixedConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btGearConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btGeneric6DofConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btGeneric6DofSpringConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btGeneric6DofSpring2Constraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btHinge2Constraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btHingeConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btPoint2PointConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btNNCGConstraintSolver.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btSliderConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btSolve2LinearConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btTypedConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btUniversalConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Dynamics/btDiscreteDynamicsWorld.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Dynamics/btRigidBody.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Dynamics/btSimpleDynamicsWorld.cpp
#	Dynamics/Bullet-C-API.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Vehicle/btRaycastVehicle.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Vehicle/btWheelInfo.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBody.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyConstraintSolver.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyDynamicsWorld.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyJointLimitConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyConstraint.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyPoint2Point.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyJointMotor.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btDantzigLCP.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btMLCPSolver.cpp
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btLemkeAlgorithm.cpp
)


source_group("src\\bullet\\dynamic" FILES ${BulletDynamics_SRCS})


SET(Root_HDRS
	${SRC_BULLET_ROOT}/btBulletDynamicsCommon.h
	${SRC_BULLET_ROOT}/btBulletCollisionCommon.h
)
SET(ConstraintSolver_HDRS
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btConeTwistConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btConstraintSolver.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btContactConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btContactSolverInfo.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btFixedConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btGearConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btGeneric6DofConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btGeneric6DofSpringConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btGeneric6DofSpring2Constraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btHinge2Constraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btHingeConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btJacobianEntry.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btPoint2PointConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btSequentialImpulseConstraintSolver.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btNNCGConstraintSolver.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btSliderConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btSolve2LinearConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btSolverBody.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btSolverConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btTypedConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/ConstraintSolver/btUniversalConstraint.h
)
SET(Dynamics_HDRS
	${SRC_BULLET_DYNAMICS_ROOT}/Dynamics/btActionInterface.h
	${SRC_BULLET_DYNAMICS_ROOT}/Dynamics/btDiscreteDynamicsWorld.h
	${SRC_BULLET_DYNAMICS_ROOT}/Dynamics/btDynamicsWorld.h
	${SRC_BULLET_DYNAMICS_ROOT}/Dynamics/btSimpleDynamicsWorld.h
	${SRC_BULLET_DYNAMICS_ROOT}/Dynamics/btRigidBody.h
)
SET(Vehicle_HDRS
	${SRC_BULLET_DYNAMICS_ROOT}/Vehicle/btRaycastVehicle.h
	${SRC_BULLET_DYNAMICS_ROOT}/Vehicle/btVehicleRaycaster.h
	${SRC_BULLET_DYNAMICS_ROOT}/Vehicle/btWheelInfo.h
)

SET(Featherstone_HDRS
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBody.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyConstraintSolver.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyDynamicsWorld.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyLink.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyLinkCollider.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodySolverConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyJointLimitConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyConstraint.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyPoint2Point.h
	${SRC_BULLET_DYNAMICS_ROOT}/Featherstone/btMultiBodyJointMotor.h
)

SET(MLCPSolvers_HDRS
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btDantzigLCP.h
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btDantzigSolver.h
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btMLCPSolver.h
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btMLCPSolverInterface.h
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btPATHSolver.h
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btSolveProjectedGaussSeidel.h	
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btLemkeSolver.h
	${SRC_BULLET_DYNAMICS_ROOT}/MLCPSolvers/btLemkeAlgorithm.h
)

SET(Character_HDRS
	${SRC_BULLET_DYNAMICS_ROOT}/Character/btCharacterControllerInterface.h
	${SRC_BULLET_DYNAMICS_ROOT}/Character/btKinematicCharacterController.h
)



SET(BulletDynamics_HDRS
	${Root_HDRS}
	${ConstraintSolver_HDRS}
	${Dynamics_HDRS}
	${Vehicle_HDRS}
	${Character_HDRS}
	${Featherstone_HDRS}
	${MLCPSolvers_HDRS}
)

source_group("include\\bullet\\dynamic" FILES ${BulletDynamics_HDRS})

INCLUDE_DIRECTORIES(
 ${SRC_BULLET_ROOT}/LinearMath
)

SET(LinearMath_SRCS
	${SRC_BULLET_ROOT}/LinearMath/btAlignedAllocator.cpp
	${SRC_BULLET_ROOT}/LinearMath/btConvexHull.cpp
	${SRC_BULLET_ROOT}/LinearMath/btConvexHullComputer.cpp
	${SRC_BULLET_ROOT}/LinearMath/btGeometryUtil.cpp
	${SRC_BULLET_ROOT}/LinearMath/btPolarDecomposition.cpp
	${SRC_BULLET_ROOT}/LinearMath/btQuickprof.cpp
	${SRC_BULLET_ROOT}/LinearMath/btSerializer.cpp
	${SRC_BULLET_ROOT}/LinearMath/btVector3.cpp
)

source_group("src\\bullet\\math" FILES ${LinearMath_SRCS})


SET(LinearMath_HDRS
	${SRC_BULLET_ROOT}/LinearMath/btAabbUtil2.h
	${SRC_BULLET_ROOT}/LinearMath/btAlignedAllocator.h
	${SRC_BULLET_ROOT}/LinearMath/btAlignedObjectArray.h
	${SRC_BULLET_ROOT}/LinearMath/btConvexHull.h
	${SRC_BULLET_ROOT}/LinearMath/btConvexHullComputer.h
	${SRC_BULLET_ROOT}/LinearMath/btDefaultMotionState.h
	${SRC_BULLET_ROOT}/LinearMath/btGeometryUtil.h
	${SRC_BULLET_ROOT}/LinearMath/btGrahamScan2dConvexHull.h
	${SRC_BULLET_ROOT}/LinearMath/btHashMap.h
	${SRC_BULLET_ROOT}/LinearMath/btIDebugDraw.h
	${SRC_BULLET_ROOT}/LinearMath/btList.h
	${SRC_BULLET_ROOT}/LinearMath/btMatrix3x3.h
	${SRC_BULLET_ROOT}/LinearMath/btMinMax.h
	${SRC_BULLET_ROOT}/LinearMath/btMotionState.h
	${SRC_BULLET_ROOT}/LinearMath/btPolarDecomposition.h
	${SRC_BULLET_ROOT}/LinearMath/btPoolAllocator.h
	${SRC_BULLET_ROOT}/LinearMath/btQuadWord.h
	${SRC_BULLET_ROOT}/LinearMath/btQuaternion.h
	${SRC_BULLET_ROOT}/LinearMath/btQuickprof.h
	${SRC_BULLET_ROOT}/LinearMath/btRandom.h
	${SRC_BULLET_ROOT}/LinearMath/btScalar.h
	${SRC_BULLET_ROOT}/LinearMath/btSerializer.h
	${SRC_BULLET_ROOT}/LinearMath/btStackAlloc.h
	${SRC_BULLET_ROOT}/LinearMath/btTransform.h
	${SRC_BULLET_ROOT}/LinearMath/btTransformUtil.h
	${SRC_BULLET_ROOT}/LinearMath/btVector3.h
)

source_group("include\\bullet\\math" FILES ${LinearMath_HDRS})


INCLUDE_DIRECTORIES(
 ${SRC_BULLET_ROOT}/Extras/ConvexDecomposition
)

SET(ConvexDecomposition_SRCS
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/bestfitobb.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/ConvexBuilder.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/cd_wavefront.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/fitsphere.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/meshvolume.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/raytri.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/vlookup.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/bestfit.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/cd_hull.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/ConvexDecomposition.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/concavity.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/float_math.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/planetri.cpp
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/splitplane.cpp
)
source_group("src\\bullet\\ConvexDecomposition" FILES ${ConvexDecomposition_SRCS})

SET(ConvexDecomposition_HDRS
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/ConvexDecomposition.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/cd_vector.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/concavity.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/bestfitobb.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/ConvexBuilder.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/cd_wavefront.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/fitsphere.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/meshvolume.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/raytri.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/vlookup.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/bestfit.h
	${SRC_BULLET_ROOT}/Extras/ConvexDecomposition/cd_hull.h
)

source_group("include\\bullet\\ConvexDecomposition" FILES ${ConvexDecomposition_HDRS})

# ----------------------- bullet end -------------------------------

set(INCROOT ${PROJECT_SOURCE_DIR}/src/include/XEPhysics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/src/XEPhysics)

# ----------------------- XEPhysics_INCLUDES -------------------------------
set(XEPhysics_INCLUDES
    ${INCROOT}/HeightfieldTerrainShape.h
	 ${INCROOT}/BulletMesh.hpp
	 #${INCROOT}/PhysicsInterface.hpp
	 #${INCROOT}/PhysicsComponents.hpp
	${INCROOT}/Export.hpp
)
source_group("include" FILES ${XEPhysics_INCLUDES})


# ----------------------- XEPhysics_SOURCES -------------------------------
set(XEPhysics_SOURCES
    ${SRCROOT}/BulletMesh.cpp
    ${SRCROOT}/HeightfieldTerrainShape.cpp
)
source_group("src" FILES ${XEPhysics_SOURCES})

# ----------------------- XEPhysics_Util_SOURCES -------------------------------
set(XEPhysics_Util_SOURCES
   #  ${SRCROOT}/Util/CollisionsMeshToShapeConverter.cpp
)
source_group("src\\Util" FILES ${XEPhysics_Util_SOURCES})


# ----------------------- header files -------------------------------
set(XEPhysics_HEADER
	# todo ${INCROOT}/Serialize.hpp
)
source_group("include" FILES ${XEPhysics_HEADER}) # Create named folders for the sources within the .vcproj

# ----------------------- XEPhysics_Debug_INCLUDES -------------------------------
set(XEPhysics_Debug_SRC
    ${SRCROOT}/Debug/DebugDrawer.cpp
)
source_group("src\\debug" FILES ${XEPhysics_Debug_SRC})

set(XEPhysics_Debug_INCLUDE
    ${INCROOT}/Debug/DebugDrawer.hpp
)
source_group("include\\debug" FILES ${XEPhysics_Debug_INCLUDE})



# ----------------------- Physics_SOURCES -------------------------------
set(Physics_SOURCES
    ${SRCROOT}/Physics/gkCharacter.cpp
  #  ${SRCROOT}/gkDbvt.cpp
    ${SRCROOT}/Physics/gkDynamicsWorld.cpp
    ${SRCROOT}/Physics/gkGhost.cpp
    ${SRCROOT}/Physics/gkPhysicsController.cpp
    ${SRCROOT}/Physics/gkRagDoll.cpp
    ${SRCROOT}/Physics/gkRayTest.cpp
    ${SRCROOT}/Physics/gkRigidBody.cpp
    ${SRCROOT}/Physics/gkSoftBody.cpp
    ${SRCROOT}/Physics/gkSweptTest.cpp
    ${SRCROOT}/Physics/gkVehicle.cpp
    ${SRCROOT}/Physics/PhysTerrain.cpp
)
source_group("src\\Physics" FILES ${Physics_SOURCES})

# ----------------------- Physics_HDRS -------------------------------
set(Physics_HDRS
    ${INCROOT}/Physics/gkCharacter.h
    ${INCROOT}/Physics/gkContactTest.h
  #  ${SRCROOT}/gkDbvt.cpp
    ${INCROOT}/Physics/gkDynamicsWorld.h
    ${INCROOT}/Physics/gkGhost.h
    ${INCROOT}/Physics/gkPhysicsController.h
    ${INCROOT}/Physics/gkRagDoll.h
    ${INCROOT}/Physics/gkRayTest.h
    ${INCROOT}/Physics/gkRigidBody.h
    ${INCROOT}/Physics/gkSoftBody.h
    ${INCROOT}/Physics/gkSweptTest.h
    ${INCROOT}/Physics/gkVehicle.h
    ${INCROOT}/Physics/PhysTerrain.h
)
source_group("include\\Physics" FILES ${Physics_HDRS})


# ----------------------- XEMath_SOURCES -------------------------------
set(XEMath_SOURCES
 #   ${SRCROOT}/gkCurve.cpp
    ${SRCROOT}/Util/gkMathUtils.cpp
)
source_group("src\\math" FILES ${XEMath_SOURCES})

# ----------------------- header files -------------------------------
set(XEMath_HEADER
#	 ${INCROOT}/gkCurve.hpp
     ${INCROOT}/Util/gkMathUtils.hpp
     ${INCROOT}/Util/TransformState.hpp
)
source_group("include\\math" FILES ${XEMath_HEADER}) # Create named folders for the sources within the .vcproj

# ----------------------- Properties->C/C++->General->Additional Include Directories -------------------------------
include_directories (${PROJECT_SOURCE_DIR}/src/include)
include_directories (${PROJECT_SOURCE_DIR}/src/include/XEPhysics)
include_directories (${PROJECT_SOURCE_DIR}/src)
#include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty)
include_directories (${PROJECT_SOURCE_DIR}/src/ThirdParty/bullet)
include_directories (${PROJECT_SOURCE_DIR}/src/Ogre/OgreMain/include)

include_directories(${PROJECT_SOURCE_DIR}/src/ThirdParty/sfml/include)


#file(GLOB XEPhysics_SOURCES *.cpp)
#file(GLOB XEPhysics_HEADER *.hpp)


# Set Properties->General->Configuration Type to Dynamic Library(.lib)
# Creates math.dll with the listed sources collected in the variables

# Also adds sources to the Solution Explorer ----------------------------------------------------------------------------------
#bullet can only be used as static !!!
add_library(XEPhysics STATIC ${XEPhysics_SOURCES} ${XEPhysics_HEADER} ${XEPhysics_Util_SOURCES} ${XEPhysics_BULLET_SOURCES}  ${BulletCollision_SRCS} ${BulletCollision_HDRS} ${BulletDynamics_SRCS} ${BulletDynamics_HDRS} 
	${Physics_HDRS} ${Physics_SOURCES} ${XEMath_HEADER} ${XEMath_SOURCES} ${XEPhysics_INCLUDES}
	${LinearMath_SRCS} ${LinearMath_HDRS} ${ConvexDecomposition_SRCS} ${ConvexDecomposition_HDRS} ${XEPhysics_Debug_SRC} ${XEPhysics_Debug_INCLUDE} )


# define the sfml-graphics target
#sfml_add_library(XEPhysics
#	SOURCES ${XEPhysics_SOURCES} ${XEPhysics_HEADER} ${XEPhysics_Util_SOURCES} ${XEPhysics_BULLET_SOURCES}  ${BulletCollision_SRCS} ${BulletCollision_HDRS} ${BulletDynamics_SRCS} ${BulletDynamics_HDRS} 
#	${LinearMath_SRCS} ${LinearMath_HDRS} ${ConvexDecomposition_SRCS} ${ConvexDecomposition_HDRS} ${XEPhysics_INCLUDES}
#	DEPENDS OgreMain
#	EXTERNAL_LIBS ${XEPhysics_EXT_LIBS})

#set_property(TARGET XEPhysics PROPERTY LINK_FLAGS "-static-libgcc -static-libstdc++")

# Creates folder "libraries" and adds target project (XEngine.vcproj)
set_property(TARGET XEPhysics PROPERTY FOLDER "libraries")
set_property(TARGET XEPhysics PROPERTY LINK_FLAGS "-static-libgcc -static-libstdc++")

# set the output directory for SFML libraries
#set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")


target_compile_definitions(XEPhysics PUBLIC XEPHYSICS_EXPORTS)
#target_compile_definitions(XEPhysics PUBLIC USE_BRUTEFORCE_RAYBROADPHASE)

# Adds logic to INSTALL.vcproj to copy XEngine.lib to destination directory
#install (TARGETS XEPhysics
#		ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#		COMPONENT library)
