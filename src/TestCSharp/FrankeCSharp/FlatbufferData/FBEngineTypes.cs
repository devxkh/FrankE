// automatically generated, do not modify

namespace XFBType
{
    
public enum PhysicsType : sbyte
{
 PT_NO_COLLISION = 0,
 PT_STATIC = 1,
 PT_DYNAMIC = 2,
 PT_RIGID = 3,
 PT_SOFT = 4,
 PT_SENSOR = 5,
 PT_NAVMESH = 6,
 PT_CHARACTER = 7,
};

public enum PhysicsShape : sbyte
{
 SH_BOX = 0,
 SH_CONE = 1,
 SH_CYLINDER = 2,
 SH_SPHERE = 3,
 SH_CONVEX_TRIMESH = 4,
 SH_GIMPACT_MESH = 5,
 SH_BVH_MESH = 6,
 SH_CAPSULE = 7,
 SH_PLANE = 8,
};

public enum PCType : sbyte
{
 GK_BALL_CONSTRAINT = 0,
 GK_HINGE_CONSTRAINT = 1,
 GK_CONETWIST_CONSTRAINT = 2,
 GK_VEHICLE_CONSTRAINT = 3,
 GK_D6_CONSTRAINT = 4,
 GK_SLIDER_CONSTRAINT = 5,
 GK_CONTACT_CONSTRAINT = 6,
};

public enum MemoryMgrType : byte
{
 SCENE_DYNAMIC = 0,
 SCENE_STATIC = 1,
};
   
}
