// automatically generated, do not modify

namespace XFBType
{

using FlatBuffers;

///optional filtering to cull potential collisions
public enum CollisionFilterGroups : sbyte
{
 AllFilter = -1,
 DefaultFilter = 1,
 StaticFilter = 2,
 KinematicFilter = 4,
 DebrisFilter = 8,
 SensorTrigger = 16,
 CharacterFilter = 32,
};

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

public enum FileLocation : sbyte
{
 FILELOC_Asset = 0,
 FILELOC_DBDataFile = 1,
};

public enum TextureType : sbyte
{
 Unlit = 0,
 Pbs = 1,
};

public enum UMesh : byte
{
 NONE = 0,
 MeshFile = 1,
 MeshCube = 2,
 MeshPlane = 3,
 MeshSphere = 4,
};

public enum MemoryMgrType : byte
{
 SCENE_DYNAMIC = 0,
 SCENE_STATIC = 1,
};

public enum SpawnType : byte
{
 STYPE_RANDOM = 0,
 STYPE_ROUND_ROBIN = 1,
};

public enum LightType : byte
{
 LT_DIRECTIONAL = 0,
 LT_POINT = 1,
 LT_SPOTLIGHT = 2,
};

public enum TimeType : byte
{
 absolute = 0,
 relative = 1,
};

public enum UAnimationNode : byte
{
 NONE = 0,
 AnimationNode = 1,
 TransitionSelectNode = 2,
 LookAtNode = 3,
 MixNode = 4,
 ParameterNode = 5,
 AverageNode = 6,
 MaskAddNode = 7,
 RandomSelectNode = 8,
 SmoothValueNode = 9,
};

public sealed class Vec3f : Struct {
  public Vec3f __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float X { get { return bb.GetFloat(bb_pos + 0); } }
  public float Y { get { return bb.GetFloat(bb_pos + 4); } }
  public float Z { get { return bb.GetFloat(bb_pos + 8); } }

  public static Offset<Vec3f> CreateVec3f(FlatBufferBuilder builder, float X, float Y, float Z) {
    builder.Prep(4, 12);
    builder.PutFloat(Z);
    builder.PutFloat(Y);
    builder.PutFloat(X);
    return new Offset<Vec3f>(builder.Offset);
  }
};

public sealed class Quat4f : Struct {
  public Quat4f __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float W { get { return bb.GetFloat(bb_pos + 0); } }
  public float X { get { return bb.GetFloat(bb_pos + 4); } }
  public float Y { get { return bb.GetFloat(bb_pos + 8); } }
  public float Z { get { return bb.GetFloat(bb_pos + 12); } }

  public static Offset<Quat4f> CreateQuat4f(FlatBufferBuilder builder, float W, float X, float Y, float Z) {
    builder.Prep(4, 16);
    builder.PutFloat(Z);
    builder.PutFloat(Y);
    builder.PutFloat(X);
    builder.PutFloat(W);
    return new Offset<Quat4f>(builder.Offset);
  }
};

public sealed class Colour : Struct {
  public Colour __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float R { get { return bb.GetFloat(bb_pos + 0); } }
  public float G { get { return bb.GetFloat(bb_pos + 4); } }
  public float B { get { return bb.GetFloat(bb_pos + 8); } }
  public float A { get { return bb.GetFloat(bb_pos + 12); } }

  public static Offset<Colour> CreateColour(FlatBufferBuilder builder, float R, float G, float B, float A) {
    builder.Prep(4, 16);
    builder.PutFloat(A);
    builder.PutFloat(B);
    builder.PutFloat(G);
    builder.PutFloat(R);
    return new Offset<Colour>(builder.Offset);
  }
};

public sealed class Clipping : Table {
  public static Clipping GetRootAsClipping(ByteBuffer _bb) { return GetRootAsClipping(_bb, new Clipping()); }
  public static Clipping GetRootAsClipping(ByteBuffer _bb, Clipping obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Clipping __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float NearClip { get { int o = __offset(4); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float FarClip { get { int o = __offset(6); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }

  public static Offset<Clipping> CreateClipping(FlatBufferBuilder builder,
      float nearClip = 0,
      float farClip = 0) {
    builder.StartObject(2);
    Clipping.AddFarClip(builder, farClip);
    Clipping.AddNearClip(builder, nearClip);
    return Clipping.EndClipping(builder);
  }

  public static void StartClipping(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddNearClip(FlatBufferBuilder builder, float nearClip) { builder.AddFloat(0, nearClip, 0); }
  public static void AddFarClip(FlatBufferBuilder builder, float farClip) { builder.AddFloat(1, farClip, 0); }
  public static Offset<Clipping> EndClipping(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Clipping>(o);
  }
};

public sealed class PhysicsConstraint : Table {
  public static PhysicsConstraint GetRootAsPhysicsConstraint(ByteBuffer _bb) { return GetRootAsPhysicsConstraint(_bb, new PhysicsConstraint()); }
  public static PhysicsConstraint GetRootAsPhysicsConstraint(ByteBuffer _bb, PhysicsConstraint obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public PhysicsConstraint __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Target { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public PCType Type { get { int o = __offset(6); return o != 0 ? (PCType)bb.GetSbyte(o + bb_pos) : PCType.GK_BALL_CONSTRAINT; } }
  public Vec3f Pivot { get { return GetPivot(new Vec3f()); } }
  public Vec3f GetPivot(Vec3f obj) { int o = __offset(8); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Vec3f Axis { get { return GetAxis(new Vec3f()); } }
  public Vec3f GetAxis(Vec3f obj) { int o = __offset(10); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public short Flag { get { int o = __offset(12); return o != 0 ? bb.GetShort(o + bb_pos) : (short)0; } }
  public float GetMinLimit(int j) { int o = __offset(14); return o != 0 ? bb.GetFloat(__vector(o) + j * 4) : (float)0; }
  public int MinLimitLength { get { int o = __offset(14); return o != 0 ? __vector_len(o) : 0; } }
  public float GetMaxLimit(int j) { int o = __offset(16); return o != 0 ? bb.GetFloat(__vector(o) + j * 4) : (float)0; }
  public int MaxLimitLength { get { int o = __offset(16); return o != 0 ? __vector_len(o) : 0; } }
  public bool DisableLinkedCollision { get { int o = __offset(18); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public string Name { get { int o = __offset(20); return o != 0 ? __string(o + bb_pos) : null; } }

  public static void StartPhysicsConstraint(FlatBufferBuilder builder) { builder.StartObject(9); }
  public static void AddTarget(FlatBufferBuilder builder, StringOffset targetOffset) { builder.AddOffset(0, targetOffset.Value, 0); }
  public static void AddType(FlatBufferBuilder builder, PCType type) { builder.AddSbyte(1, (sbyte)type, 0); }
  public static void AddPivot(FlatBufferBuilder builder, Offset<Vec3f> pivotOffset) { builder.AddStruct(2, pivotOffset.Value, 0); }
  public static void AddAxis(FlatBufferBuilder builder, Offset<Vec3f> axisOffset) { builder.AddStruct(3, axisOffset.Value, 0); }
  public static void AddFlag(FlatBufferBuilder builder, short flag) { builder.AddShort(4, flag, 0); }
  public static void AddMinLimit(FlatBufferBuilder builder, VectorOffset minLimitOffset) { builder.AddOffset(5, minLimitOffset.Value, 0); }
  public static VectorOffset CreateMinLimitVector(FlatBufferBuilder builder, float[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddFloat(data[i]); return builder.EndVector(); }
  public static void StartMinLimitVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddMaxLimit(FlatBufferBuilder builder, VectorOffset maxLimitOffset) { builder.AddOffset(6, maxLimitOffset.Value, 0); }
  public static VectorOffset CreateMaxLimitVector(FlatBufferBuilder builder, float[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddFloat(data[i]); return builder.EndVector(); }
  public static void StartMaxLimitVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddDisableLinkedCollision(FlatBufferBuilder builder, bool disableLinkedCollision) { builder.AddBool(7, disableLinkedCollision, false); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(8, nameOffset.Value, 0); }
  public static Offset<PhysicsConstraint> EndPhysicsConstraint(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<PhysicsConstraint>(o);
  }
};

public sealed class PhysicsObject : Table {
  public static PhysicsObject GetRootAsPhysicsObject(ByteBuffer _bb) { return GetRootAsPhysicsObject(_bb, new PhysicsObject()); }
  public static PhysicsObject GetRootAsPhysicsObject(ByteBuffer _bb, PhysicsObject obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public PhysicsObject __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Id { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public short ColMask { get { int o = __offset(6); return o != 0 ? bb.GetShort(o + bb_pos) : (short)0; } }
  public PhysicsType Type { get { int o = __offset(8); return o != 0 ? (PhysicsType)bb.GetSbyte(o + bb_pos) : PhysicsType.PT_NO_COLLISION; } }
  public uint Mode { get { int o = __offset(10); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public PhysicsShape Shape { get { int o = __offset(12); return o != 0 ? (PhysicsShape)bb.GetSbyte(o + bb_pos) : PhysicsShape.SH_BOX; } }
  public float Mass { get { int o = __offset(14); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Margin { get { int o = __offset(16); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Radius { get { int o = __offset(18); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float AngularDamp { get { int o = __offset(20); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float LinearDamp { get { int o = __offset(22); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float FormFactor { get { int o = __offset(24); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float MinVel { get { int o = __offset(26); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float MaxVel { get { int o = __offset(28); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Restitution { get { int o = __offset(30); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Friction { get { int o = __offset(32); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public short ColGroupMask { get { int o = __offset(34); return o != 0 ? bb.GetShort(o + bb_pos) : (short)0; } }
  public float CharStepHeight { get { int o = __offset(36); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float CharJumpSpeed { get { int o = __offset(38); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float CharFallSpeed { get { int o = __offset(40); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public string Boneparent { get { int o = __offset(42); return o != 0 ? __string(o + bb_pos) : null; } }
  public string CollMeshName { get { int o = __offset(44); return o != 0 ? __string(o + bb_pos) : null; } }
  public Vec3f Size { get { return GetSize(new Vec3f()); } }
  public Vec3f GetSize(Vec3f obj) { int o = __offset(46); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Vec3f Scale { get { return GetScale(new Vec3f()); } }
  public Vec3f GetScale(Vec3f obj) { int o = __offset(48); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Vec3f Offset { get { return GetOffset(new Vec3f()); } }
  public Vec3f GetOffset(Vec3f obj) { int o = __offset(50); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public bool ParentIsNode { get { int o = __offset(52); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public PhysicsConstraint GetPhysicsConstraints(int j) { return GetPhysicsConstraints(new PhysicsConstraint(), j); }
  public PhysicsConstraint GetPhysicsConstraints(PhysicsConstraint obj, int j) { int o = __offset(54); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int PhysicsConstraintsLength { get { int o = __offset(54); return o != 0 ? __vector_len(o) : 0; } }
  public string Name { get { int o = __offset(56); return o != 0 ? __string(o + bb_pos) : null; } }
  public LocalFile File { get { return GetFile(new LocalFile()); } }
  public LocalFile GetFile(LocalFile obj) { int o = __offset(58); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static void StartPhysicsObject(FlatBufferBuilder builder) { builder.StartObject(28); }
  public static void AddId(FlatBufferBuilder builder, ushort id) { builder.AddUshort(0, id, 0); }
  public static void AddColMask(FlatBufferBuilder builder, short colMask) { builder.AddShort(1, colMask, 0); }
  public static void AddType(FlatBufferBuilder builder, PhysicsType type) { builder.AddSbyte(2, (sbyte)type, 0); }
  public static void AddMode(FlatBufferBuilder builder, uint mode) { builder.AddUint(3, mode, 0); }
  public static void AddShape(FlatBufferBuilder builder, PhysicsShape shape) { builder.AddSbyte(4, (sbyte)shape, 0); }
  public static void AddMass(FlatBufferBuilder builder, float mass) { builder.AddFloat(5, mass, 0); }
  public static void AddMargin(FlatBufferBuilder builder, float margin) { builder.AddFloat(6, margin, 0); }
  public static void AddRadius(FlatBufferBuilder builder, float radius) { builder.AddFloat(7, radius, 0); }
  public static void AddAngularDamp(FlatBufferBuilder builder, float angularDamp) { builder.AddFloat(8, angularDamp, 0); }
  public static void AddLinearDamp(FlatBufferBuilder builder, float linearDamp) { builder.AddFloat(9, linearDamp, 0); }
  public static void AddFormFactor(FlatBufferBuilder builder, float formFactor) { builder.AddFloat(10, formFactor, 0); }
  public static void AddMinVel(FlatBufferBuilder builder, float minVel) { builder.AddFloat(11, minVel, 0); }
  public static void AddMaxVel(FlatBufferBuilder builder, float maxVel) { builder.AddFloat(12, maxVel, 0); }
  public static void AddRestitution(FlatBufferBuilder builder, float restitution) { builder.AddFloat(13, restitution, 0); }
  public static void AddFriction(FlatBufferBuilder builder, float friction) { builder.AddFloat(14, friction, 0); }
  public static void AddColGroupMask(FlatBufferBuilder builder, short colGroupMask) { builder.AddShort(15, colGroupMask, 0); }
  public static void AddCharStepHeight(FlatBufferBuilder builder, float charStepHeight) { builder.AddFloat(16, charStepHeight, 0); }
  public static void AddCharJumpSpeed(FlatBufferBuilder builder, float charJumpSpeed) { builder.AddFloat(17, charJumpSpeed, 0); }
  public static void AddCharFallSpeed(FlatBufferBuilder builder, float charFallSpeed) { builder.AddFloat(18, charFallSpeed, 0); }
  public static void AddBoneparent(FlatBufferBuilder builder, StringOffset boneparentOffset) { builder.AddOffset(19, boneparentOffset.Value, 0); }
  public static void AddCollMeshName(FlatBufferBuilder builder, StringOffset collMeshNameOffset) { builder.AddOffset(20, collMeshNameOffset.Value, 0); }
  public static void AddSize(FlatBufferBuilder builder, Offset<Vec3f> sizeOffset) { builder.AddStruct(21, sizeOffset.Value, 0); }
  public static void AddScale(FlatBufferBuilder builder, Offset<Vec3f> scaleOffset) { builder.AddStruct(22, scaleOffset.Value, 0); }
  public static void AddOffset(FlatBufferBuilder builder, Offset<Vec3f> offsetOffset) { builder.AddStruct(23, offsetOffset.Value, 0); }
  public static void AddParentIsNode(FlatBufferBuilder builder, bool parentIsNode) { builder.AddBool(24, parentIsNode, false); }
  public static void AddPhysicsConstraints(FlatBufferBuilder builder, VectorOffset physicsConstraintsOffset) { builder.AddOffset(25, physicsConstraintsOffset.Value, 0); }
  public static VectorOffset CreatePhysicsConstraintsVector(FlatBufferBuilder builder, Offset<PhysicsConstraint>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartPhysicsConstraintsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(26, nameOffset.Value, 0); }
  public static void AddFile(FlatBufferBuilder builder, Offset<LocalFile> fileOffset) { builder.AddOffset(27, fileOffset.Value, 0); }
  public static Offset<PhysicsObject> EndPhysicsObject(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<PhysicsObject>(o);
  }
};

public sealed class LocalFile : Table {
  public static LocalFile GetRootAsLocalFile(ByteBuffer _bb) { return GetRootAsLocalFile(_bb, new LocalFile()); }
  public static LocalFile GetRootAsLocalFile(ByteBuffer _bb, LocalFile obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public LocalFile __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public FileLocation FileLocation { get { int o = __offset(4); return o != 0 ? (FileLocation)bb.GetSbyte(o + bb_pos) : FileLocation.FILELOC_Asset; } }
  public string FileName { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }
  public string FilePath { get { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; } }
  public string ResourceGrp { get { int o = __offset(10); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<LocalFile> CreateLocalFile(FlatBufferBuilder builder,
      FileLocation fileLocation = FileLocation.FILELOC_Asset,
      StringOffset fileNameOffset = default(StringOffset),
      StringOffset filePathOffset = default(StringOffset),
      StringOffset resourceGrpOffset = default(StringOffset)) {
    builder.StartObject(4);
    LocalFile.AddResourceGrp(builder, resourceGrpOffset);
    LocalFile.AddFilePath(builder, filePathOffset);
    LocalFile.AddFileName(builder, fileNameOffset);
    LocalFile.AddFileLocation(builder, fileLocation);
    return LocalFile.EndLocalFile(builder);
  }

  public static void StartLocalFile(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddFileLocation(FlatBufferBuilder builder, FileLocation fileLocation) { builder.AddSbyte(0, (sbyte)fileLocation, 0); }
  public static void AddFileName(FlatBufferBuilder builder, StringOffset fileNameOffset) { builder.AddOffset(1, fileNameOffset.Value, 0); }
  public static void AddFilePath(FlatBufferBuilder builder, StringOffset filePathOffset) { builder.AddOffset(2, filePathOffset.Value, 0); }
  public static void AddResourceGrp(FlatBufferBuilder builder, StringOffset resourceGrpOffset) { builder.AddOffset(3, resourceGrpOffset.Value, 0); }
  public static Offset<LocalFile> EndLocalFile(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<LocalFile>(o);
  }
};

public sealed class Material : Table {
  public static Material GetRootAsMaterial(ByteBuffer _bb) { return GetRootAsMaterial(_bb, new Material()); }
  public static Material GetRootAsMaterial(ByteBuffer _bb, Material obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Material __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public LocalFile File { get { return GetFile(new LocalFile()); } }
  public LocalFile GetFile(LocalFile obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public string GetTextures(int j) { int o = __offset(6); return o != 0 ? __string(__vector(o) + j * 4) : null; }
  public int TexturesLength { get { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; } }
  public TextureType TextureType { get { int o = __offset(8); return o != 0 ? (TextureType)bb.GetSbyte(o + bb_pos) : TextureType.Unlit; } }
  public string Name { get { int o = __offset(10); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Material> CreateMaterial(FlatBufferBuilder builder,
      Offset<LocalFile> fileOffset = default(Offset<LocalFile>),
      VectorOffset texturesOffset = default(VectorOffset),
      TextureType textureType = TextureType.Unlit,
      StringOffset nameOffset = default(StringOffset)) {
    builder.StartObject(4);
    Material.AddName(builder, nameOffset);
    Material.AddTextures(builder, texturesOffset);
    Material.AddFile(builder, fileOffset);
    Material.AddTextureType(builder, textureType);
    return Material.EndMaterial(builder);
  }

  public static void StartMaterial(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddFile(FlatBufferBuilder builder, Offset<LocalFile> fileOffset) { builder.AddOffset(0, fileOffset.Value, 0); }
  public static void AddTextures(FlatBufferBuilder builder, VectorOffset texturesOffset) { builder.AddOffset(1, texturesOffset.Value, 0); }
  public static VectorOffset CreateTexturesVector(FlatBufferBuilder builder, StringOffset[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartTexturesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddTextureType(FlatBufferBuilder builder, TextureType textureType) { builder.AddSbyte(2, (sbyte)textureType, 0); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(3, nameOffset.Value, 0); }
  public static Offset<Material> EndMaterial(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Material>(o);
  }
};

public sealed class MeshFile : Table {
  public static MeshFile GetRootAsMeshFile(ByteBuffer _bb) { return GetRootAsMeshFile(_bb, new MeshFile()); }
  public static MeshFile GetRootAsMeshFile(ByteBuffer _bb, MeshFile obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public MeshFile __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public LocalFile File { get { return GetFile(new LocalFile()); } }
  public LocalFile GetFile(LocalFile obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public Material Material { get { return GetMaterial(new Material()); } }
  public Material GetMaterial(Material obj) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<MeshFile> CreateMeshFile(FlatBufferBuilder builder,
      Offset<LocalFile> fileOffset = default(Offset<LocalFile>),
      Offset<Material> materialOffset = default(Offset<Material>)) {
    builder.StartObject(2);
    MeshFile.AddMaterial(builder, materialOffset);
    MeshFile.AddFile(builder, fileOffset);
    return MeshFile.EndMeshFile(builder);
  }

  public static void StartMeshFile(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddFile(FlatBufferBuilder builder, Offset<LocalFile> fileOffset) { builder.AddOffset(0, fileOffset.Value, 0); }
  public static void AddMaterial(FlatBufferBuilder builder, Offset<Material> materialOffset) { builder.AddOffset(1, materialOffset.Value, 0); }
  public static Offset<MeshFile> EndMeshFile(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<MeshFile>(o);
  }
};

public sealed class MeshCube : Table {
  public static MeshCube GetRootAsMeshCube(ByteBuffer _bb) { return GetRootAsMeshCube(_bb, new MeshCube()); }
  public static MeshCube GetRootAsMeshCube(ByteBuffer _bb, MeshCube obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public MeshCube __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public Material Material { get { return GetMaterial(new Material()); } }
  public Material GetMaterial(Material obj) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public float Width { get { int o = __offset(8); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }

  public static Offset<MeshCube> CreateMeshCube(FlatBufferBuilder builder,
      StringOffset NameOffset = default(StringOffset),
      Offset<Material> materialOffset = default(Offset<Material>),
      float width = 0) {
    builder.StartObject(3);
    MeshCube.AddWidth(builder, width);
    MeshCube.AddMaterial(builder, materialOffset);
    MeshCube.AddName(builder, NameOffset);
    return MeshCube.EndMeshCube(builder);
  }

  public static void StartMeshCube(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddName(FlatBufferBuilder builder, StringOffset NameOffset) { builder.AddOffset(0, NameOffset.Value, 0); }
  public static void AddMaterial(FlatBufferBuilder builder, Offset<Material> materialOffset) { builder.AddOffset(1, materialOffset.Value, 0); }
  public static void AddWidth(FlatBufferBuilder builder, float width) { builder.AddFloat(2, width, 0); }
  public static Offset<MeshCube> EndMeshCube(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<MeshCube>(o);
  }
};

public sealed class MeshPlane : Table {
  public static MeshPlane GetRootAsMeshPlane(ByteBuffer _bb) { return GetRootAsMeshPlane(_bb, new MeshPlane()); }
  public static MeshPlane GetRootAsMeshPlane(ByteBuffer _bb, MeshPlane obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public MeshPlane __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public Material Material { get { return GetMaterial(new Material()); } }
  public Material GetMaterial(Material obj) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public Vec3f Normal { get { return GetNormal(new Vec3f()); } }
  public Vec3f GetNormal(Vec3f obj) { int o = __offset(8); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public float Constant { get { int o = __offset(10); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Width { get { int o = __offset(12); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Height { get { int o = __offset(14); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public uint Xsegments { get { int o = __offset(16); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public uint Ysegments { get { int o = __offset(18); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public bool Normals { get { int o = __offset(20); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public uint NumTexCoordSets { get { int o = __offset(22); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public float XTile { get { int o = __offset(24); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float YTile { get { int o = __offset(26); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public Vec3f UpVector { get { return GetUpVector(new Vec3f()); } }
  public Vec3f GetUpVector(Vec3f obj) { int o = __offset(28); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }

  public static void StartMeshPlane(FlatBufferBuilder builder) { builder.StartObject(13); }
  public static void AddName(FlatBufferBuilder builder, StringOffset NameOffset) { builder.AddOffset(0, NameOffset.Value, 0); }
  public static void AddMaterial(FlatBufferBuilder builder, Offset<Material> materialOffset) { builder.AddOffset(1, materialOffset.Value, 0); }
  public static void AddNormal(FlatBufferBuilder builder, Offset<Vec3f> normalOffset) { builder.AddStruct(2, normalOffset.Value, 0); }
  public static void AddConstant(FlatBufferBuilder builder, float constant) { builder.AddFloat(3, constant, 0); }
  public static void AddWidth(FlatBufferBuilder builder, float width) { builder.AddFloat(4, width, 0); }
  public static void AddHeight(FlatBufferBuilder builder, float height) { builder.AddFloat(5, height, 0); }
  public static void AddXsegments(FlatBufferBuilder builder, uint xsegments) { builder.AddUint(6, xsegments, 0); }
  public static void AddYsegments(FlatBufferBuilder builder, uint ysegments) { builder.AddUint(7, ysegments, 0); }
  public static void AddNormals(FlatBufferBuilder builder, bool normals) { builder.AddBool(8, normals, false); }
  public static void AddNumTexCoordSets(FlatBufferBuilder builder, uint numTexCoordSets) { builder.AddUint(9, numTexCoordSets, 0); }
  public static void AddXTile(FlatBufferBuilder builder, float xTile) { builder.AddFloat(10, xTile, 0); }
  public static void AddYTile(FlatBufferBuilder builder, float yTile) { builder.AddFloat(11, yTile, 0); }
  public static void AddUpVector(FlatBufferBuilder builder, Offset<Vec3f> upVectorOffset) { builder.AddStruct(12, upVectorOffset.Value, 0); }
  public static Offset<MeshPlane> EndMeshPlane(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<MeshPlane>(o);
  }
};

public sealed class MeshSphere : Table {
  public static MeshSphere GetRootAsMeshSphere(ByteBuffer _bb) { return GetRootAsMeshSphere(_bb, new MeshSphere()); }
  public static MeshSphere GetRootAsMeshSphere(ByteBuffer _bb, MeshSphere obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public MeshSphere __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public Material Material { get { return GetMaterial(new Material()); } }
  public Material GetMaterial(Material obj) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public float Rad { get { int o = __offset(8); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }

  public static Offset<MeshSphere> CreateMeshSphere(FlatBufferBuilder builder,
      StringOffset NameOffset = default(StringOffset),
      Offset<Material> materialOffset = default(Offset<Material>),
      float rad = 0) {
    builder.StartObject(3);
    MeshSphere.AddRad(builder, rad);
    MeshSphere.AddMaterial(builder, materialOffset);
    MeshSphere.AddName(builder, NameOffset);
    return MeshSphere.EndMeshSphere(builder);
  }

  public static void StartMeshSphere(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddName(FlatBufferBuilder builder, StringOffset NameOffset) { builder.AddOffset(0, NameOffset.Value, 0); }
  public static void AddMaterial(FlatBufferBuilder builder, Offset<Material> materialOffset) { builder.AddOffset(1, materialOffset.Value, 0); }
  public static void AddRad(FlatBufferBuilder builder, float rad) { builder.AddFloat(2, rad, 0); }
  public static Offset<MeshSphere> EndMeshSphere(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<MeshSphere>(o);
  }
};

public sealed class Mesh : Table {
  public static Mesh GetRootAsMesh(ByteBuffer _bb) { return GetRootAsMesh(_bb, new Mesh()); }
  public static Mesh GetRootAsMesh(ByteBuffer _bb, Mesh obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Mesh __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public UMesh MeshType { get { int o = __offset(4); return o != 0 ? (UMesh)bb.Get(o + bb_pos) : UMesh.NONE; } }
  public TTable GetMesh<TTable>(TTable obj) where TTable : Table { int o = __offset(6); return o != 0 ? __union(obj, o) : null; }

  public static Offset<Mesh> CreateMesh(FlatBufferBuilder builder,
      UMesh mesh_type = UMesh.NONE,
      int meshOffset = 0) {
    builder.StartObject(2);
    Mesh.AddMesh(builder, meshOffset);
    Mesh.AddMeshType(builder, mesh_type);
    return Mesh.EndMesh(builder);
  }

  public static void StartMesh(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddMeshType(FlatBufferBuilder builder, UMesh meshType) { builder.AddByte(0, (byte)meshType, 0); }
  public static void AddMesh(FlatBufferBuilder builder, int meshOffset) { builder.AddOffset(1, meshOffset, 0); }
  public static Offset<Mesh> EndMesh(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Mesh>(o);
  }
};

public sealed class RenderableComponent : Table {
  public static RenderableComponent GetRootAsRenderableComponent(ByteBuffer _bb) { return GetRootAsRenderableComponent(_bb, new RenderableComponent()); }
  public static RenderableComponent GetRootAsRenderableComponent(ByteBuffer _bb, RenderableComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public RenderableComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public MemoryMgrType MemType { get { int o = __offset(4); return o != 0 ? (MemoryMgrType)bb.Get(o + bb_pos) : MemoryMgrType.SCENE_DYNAMIC; } }
  public uint Renderqueue { get { int o = __offset(6); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public bool Visible { get { int o = __offset(8); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public Mesh GetMeshes(int j) { return GetMeshes(new Mesh(), j); }
  public Mesh GetMeshes(Mesh obj, int j) { int o = __offset(10); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int MeshesLength { get { int o = __offset(10); return o != 0 ? __vector_len(o) : 0; } }
  public uint VisibilityFlags { get { int o = __offset(12); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public uint LightMask { get { int o = __offset(14); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public bool CastShadows { get { int o = __offset(16); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public uint Mode { get { int o = __offset(18); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public bool ShowAABB { get { int o = __offset(20); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public float ShadowconstBias { get { int o = __offset(22); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public uint Group { get { int o = __offset(24); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }

  public static Offset<RenderableComponent> CreateRenderableComponent(FlatBufferBuilder builder,
      MemoryMgrType memType = MemoryMgrType.SCENE_DYNAMIC,
      uint renderqueue = 0,
      bool visible = false,
      VectorOffset meshesOffset = default(VectorOffset),
      uint visibilityFlags = 0,
      uint lightMask = 0,
      bool castShadows = false,
      uint mode = 0,
      bool showAABB = false,
      float shadowconstBias = 0,
      uint group = 0) {
    builder.StartObject(11);
    RenderableComponent.AddGroup(builder, group);
    RenderableComponent.AddShadowconstBias(builder, shadowconstBias);
    RenderableComponent.AddMode(builder, mode);
    RenderableComponent.AddLightMask(builder, lightMask);
    RenderableComponent.AddVisibilityFlags(builder, visibilityFlags);
    RenderableComponent.AddMeshes(builder, meshesOffset);
    RenderableComponent.AddRenderqueue(builder, renderqueue);
    RenderableComponent.AddShowAABB(builder, showAABB);
    RenderableComponent.AddCastShadows(builder, castShadows);
    RenderableComponent.AddVisible(builder, visible);
    RenderableComponent.AddMemType(builder, memType);
    return RenderableComponent.EndRenderableComponent(builder);
  }

  public static void StartRenderableComponent(FlatBufferBuilder builder) { builder.StartObject(11); }
  public static void AddMemType(FlatBufferBuilder builder, MemoryMgrType memType) { builder.AddByte(0, (byte)memType, 0); }
  public static void AddRenderqueue(FlatBufferBuilder builder, uint renderqueue) { builder.AddUint(1, renderqueue, 0); }
  public static void AddVisible(FlatBufferBuilder builder, bool visible) { builder.AddBool(2, visible, false); }
  public static void AddMeshes(FlatBufferBuilder builder, VectorOffset meshesOffset) { builder.AddOffset(3, meshesOffset.Value, 0); }
  public static VectorOffset CreateMeshesVector(FlatBufferBuilder builder, Offset<Mesh>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartMeshesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddVisibilityFlags(FlatBufferBuilder builder, uint visibilityFlags) { builder.AddUint(4, visibilityFlags, 0); }
  public static void AddLightMask(FlatBufferBuilder builder, uint lightMask) { builder.AddUint(5, lightMask, 0); }
  public static void AddCastShadows(FlatBufferBuilder builder, bool castShadows) { builder.AddBool(6, castShadows, false); }
  public static void AddMode(FlatBufferBuilder builder, uint mode) { builder.AddUint(7, mode, 0); }
  public static void AddShowAABB(FlatBufferBuilder builder, bool showAABB) { builder.AddBool(8, showAABB, false); }
  public static void AddShadowconstBias(FlatBufferBuilder builder, float shadowconstBias) { builder.AddFloat(9, shadowconstBias, 0); }
  public static void AddGroup(FlatBufferBuilder builder, uint group) { builder.AddUint(10, group, 0); }
  public static Offset<RenderableComponent> EndRenderableComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<RenderableComponent>(o);
  }
};

public sealed class Sound : Table {
  public static Sound GetRootAsSound(ByteBuffer _bb) { return GetRootAsSound(_bb, new Sound()); }
  public static Sound GetRootAsSound(ByteBuffer _bb, Sound obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Sound __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public LocalFile File { get { return GetFile(new LocalFile()); } }
  public LocalFile GetFile(LocalFile obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<Sound> CreateSound(FlatBufferBuilder builder,
      Offset<LocalFile> fileOffset = default(Offset<LocalFile>)) {
    builder.StartObject(1);
    Sound.AddFile(builder, fileOffset);
    return Sound.EndSound(builder);
  }

  public static void StartSound(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddFile(FlatBufferBuilder builder, Offset<LocalFile> fileOffset) { builder.AddOffset(0, fileOffset.Value, 0); }
  public static Offset<Sound> EndSound(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Sound>(o);
  }
};

public sealed class SpawnComponent : Table {
  public static SpawnComponent GetRootAsSpawnComponent(ByteBuffer _bb) { return GetRootAsSpawnComponent(_bb, new SpawnComponent()); }
  public static SpawnComponent GetRootAsSpawnComponent(ByteBuffer _bb, SpawnComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public SpawnComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint SPGroup { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public uint SpawnPointId { get { int o = __offset(6); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public SpawnType SpawnType { get { int o = __offset(8); return o != 0 ? (SpawnType)bb.Get(o + bb_pos) : SpawnType.STYPE_RANDOM; } }

  public static Offset<SpawnComponent> CreateSpawnComponent(FlatBufferBuilder builder,
      uint SPGroup = 0,
      uint spawnPointId = 0,
      SpawnType spawnType = SpawnType.STYPE_RANDOM) {
    builder.StartObject(3);
    SpawnComponent.AddSpawnPointId(builder, spawnPointId);
    SpawnComponent.AddSPGroup(builder, SPGroup);
    SpawnComponent.AddSpawnType(builder, spawnType);
    return SpawnComponent.EndSpawnComponent(builder);
  }

  public static void StartSpawnComponent(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddSPGroup(FlatBufferBuilder builder, uint SPGroup) { builder.AddUint(0, SPGroup, 0); }
  public static void AddSpawnPointId(FlatBufferBuilder builder, uint spawnPointId) { builder.AddUint(1, spawnPointId, 0); }
  public static void AddSpawnType(FlatBufferBuilder builder, SpawnType spawnType) { builder.AddByte(2, (byte)spawnType, 0); }
  public static Offset<SpawnComponent> EndSpawnComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<SpawnComponent>(o);
  }
};

public sealed class SpawnPointComponent : Table {
  public static SpawnPointComponent GetRootAsSpawnPointComponent(ByteBuffer _bb) { return GetRootAsSpawnPointComponent(_bb, new SpawnPointComponent()); }
  public static SpawnPointComponent GetRootAsSpawnPointComponent(ByteBuffer _bb, SpawnPointComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public SpawnPointComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint SPGroup { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public uint Id { get { int o = __offset(6); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public string Name { get { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<SpawnPointComponent> CreateSpawnPointComponent(FlatBufferBuilder builder,
      uint SPGroup = 0,
      uint id = 0,
      StringOffset nameOffset = default(StringOffset)) {
    builder.StartObject(3);
    SpawnPointComponent.AddName(builder, nameOffset);
    SpawnPointComponent.AddId(builder, id);
    SpawnPointComponent.AddSPGroup(builder, SPGroup);
    return SpawnPointComponent.EndSpawnPointComponent(builder);
  }

  public static void StartSpawnPointComponent(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddSPGroup(FlatBufferBuilder builder, uint SPGroup) { builder.AddUint(0, SPGroup, 0); }
  public static void AddId(FlatBufferBuilder builder, uint id) { builder.AddUint(1, id, 0); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(2, nameOffset.Value, 0); }
  public static Offset<SpawnPointComponent> EndSpawnPointComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<SpawnPointComponent>(o);
  }
};

public sealed class Trigger : Table {
  public static Trigger GetRootAsTrigger(ByteBuffer _bb) { return GetRootAsTrigger(_bb, new Trigger()); }
  public static Trigger GetRootAsTrigger(ByteBuffer _bb, Trigger obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Trigger __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Trigger> CreateTrigger(FlatBufferBuilder builder,
      StringOffset nameOffset = default(StringOffset)) {
    builder.StartObject(1);
    Trigger.AddName(builder, nameOffset);
    return Trigger.EndTrigger(builder);
  }

  public static void StartTrigger(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(0, nameOffset.Value, 0); }
  public static Offset<Trigger> EndTrigger(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Trigger>(o);
  }
};

public sealed class PhysicsComponent : Table {
  public static PhysicsComponent GetRootAsPhysicsComponent(ByteBuffer _bb) { return GetRootAsPhysicsComponent(_bb, new PhysicsComponent()); }
  public static PhysicsComponent GetRootAsPhysicsComponent(ByteBuffer _bb, PhysicsComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public PhysicsComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public PhysicsObject GetPhysics(int j) { return GetPhysics(new PhysicsObject(), j); }
  public PhysicsObject GetPhysics(PhysicsObject obj, int j) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int PhysicsLength { get { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; } }

  public static Offset<PhysicsComponent> CreatePhysicsComponent(FlatBufferBuilder builder,
      VectorOffset physicsOffset = default(VectorOffset)) {
    builder.StartObject(1);
    PhysicsComponent.AddPhysics(builder, physicsOffset);
    return PhysicsComponent.EndPhysicsComponent(builder);
  }

  public static void StartPhysicsComponent(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddPhysics(FlatBufferBuilder builder, VectorOffset physicsOffset) { builder.AddOffset(0, physicsOffset.Value, 0); }
  public static VectorOffset CreatePhysicsVector(FlatBufferBuilder builder, Offset<PhysicsObject>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartPhysicsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<PhysicsComponent> EndPhysicsComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<PhysicsComponent>(o);
  }
};

public sealed class SoundListener : Table {
  public static SoundListener GetRootAsSoundListener(ByteBuffer _bb) { return GetRootAsSoundListener(_bb, new SoundListener()); }
  public static SoundListener GetRootAsSoundListener(ByteBuffer _bb, SoundListener obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public SoundListener __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }


  public static void StartSoundListener(FlatBufferBuilder builder) { builder.StartObject(0); }
  public static Offset<SoundListener> EndSoundListener(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<SoundListener>(o);
  }
};

public sealed class Attenuation : Struct {
  public Attenuation __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float Range { get { return bb.GetFloat(bb_pos + 0); } }
  public float Constant { get { return bb.GetFloat(bb_pos + 4); } }
  public float Linear { get { return bb.GetFloat(bb_pos + 8); } }
  public float Quadratic { get { return bb.GetFloat(bb_pos + 12); } }

  public static Offset<Attenuation> CreateAttenuation(FlatBufferBuilder builder, float Range, float Constant, float Linear, float Quadratic) {
    builder.Prep(4, 16);
    builder.PutFloat(Quadratic);
    builder.PutFloat(Linear);
    builder.PutFloat(Constant);
    builder.PutFloat(Range);
    return new Offset<Attenuation>(builder.Offset);
  }
};

public sealed class Light : Table {
  public static Light GetRootAsLight(ByteBuffer _bb) { return GetRootAsLight(_bb, new Light()); }
  public static Light GetRootAsLight(ByteBuffer _bb, Light obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Light __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Colour ColourDiffuse { get { return GetColourDiffuse(new Colour()); } }
  public Colour GetColourDiffuse(Colour obj) { int o = __offset(4); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Colour ColourSpecular { get { return GetColourSpecular(new Colour()); } }
  public Colour GetColourSpecular(Colour obj) { int o = __offset(6); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Vec3f DirectionVector { get { return GetDirectionVector(new Vec3f()); } }
  public Vec3f GetDirectionVector(Vec3f obj) { int o = __offset(8); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public LightType LightType { get { int o = __offset(10); return o != 0 ? (LightType)bb.Get(o + bb_pos) : LightType.LT_DIRECTIONAL; } }
  public float PowerScale { get { int o = __offset(12); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public Attenuation Attenuation { get { return GetAttenuation(new Attenuation()); } }
  public Attenuation GetAttenuation(Attenuation obj) { int o = __offset(14); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public AmbientLight AmbientLight { get { return GetAmbientLight(new AmbientLight()); } }
  public AmbientLight GetAmbientLight(AmbientLight obj) { int o = __offset(16); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public string Name { get { int o = __offset(18); return o != 0 ? __string(o + bb_pos) : null; } }
  public bool CastShadows { get { int o = __offset(20); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public bool UseInstantRadiosity { get { int o = __offset(22); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public float IRVplThreshold { get { int o = __offset(24); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }

  public static void StartLight(FlatBufferBuilder builder) { builder.StartObject(11); }
  public static void AddColourDiffuse(FlatBufferBuilder builder, Offset<Colour> colourDiffuseOffset) { builder.AddStruct(0, colourDiffuseOffset.Value, 0); }
  public static void AddColourSpecular(FlatBufferBuilder builder, Offset<Colour> colourSpecularOffset) { builder.AddStruct(1, colourSpecularOffset.Value, 0); }
  public static void AddDirectionVector(FlatBufferBuilder builder, Offset<Vec3f> directionVectorOffset) { builder.AddStruct(2, directionVectorOffset.Value, 0); }
  public static void AddLightType(FlatBufferBuilder builder, LightType lightType) { builder.AddByte(3, (byte)lightType, 0); }
  public static void AddPowerScale(FlatBufferBuilder builder, float powerScale) { builder.AddFloat(4, powerScale, 0); }
  public static void AddAttenuation(FlatBufferBuilder builder, Offset<Attenuation> attenuationOffset) { builder.AddStruct(5, attenuationOffset.Value, 0); }
  public static void AddAmbientLight(FlatBufferBuilder builder, Offset<AmbientLight> ambientLightOffset) { builder.AddOffset(6, ambientLightOffset.Value, 0); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(7, nameOffset.Value, 0); }
  public static void AddCastShadows(FlatBufferBuilder builder, bool castShadows) { builder.AddBool(8, castShadows, false); }
  public static void AddUseInstantRadiosity(FlatBufferBuilder builder, bool useInstantRadiosity) { builder.AddBool(9, useInstantRadiosity, false); }
  public static void AddIRVplThreshold(FlatBufferBuilder builder, float IRVplThreshold) { builder.AddFloat(10, IRVplThreshold, 0); }
  public static Offset<Light> EndLight(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Light>(o);
  }
};

public sealed class Camera : Table {
  public static Camera GetRootAsCamera(ByteBuffer _bb) { return GetRootAsCamera(_bb, new Camera()); }
  public static Camera GetRootAsCamera(ByteBuffer _bb, Camera obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Camera __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Clipping Clipping { get { return GetClipping(new Clipping()); } }
  public Clipping GetClipping(Clipping obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public string Name { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Camera> CreateCamera(FlatBufferBuilder builder,
      Offset<Clipping> clippingOffset = default(Offset<Clipping>),
      StringOffset nameOffset = default(StringOffset)) {
    builder.StartObject(2);
    Camera.AddName(builder, nameOffset);
    Camera.AddClipping(builder, clippingOffset);
    return Camera.EndCamera(builder);
  }

  public static void StartCamera(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddClipping(FlatBufferBuilder builder, Offset<Clipping> clippingOffset) { builder.AddOffset(0, clippingOffset.Value, 0); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(1, nameOffset.Value, 0); }
  public static Offset<Camera> EndCamera(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Camera>(o);
  }
};

public sealed class System : Table {
  public static System GetRootAsSystem(ByteBuffer _bb) { return GetRootAsSystem(_bb, new System()); }
  public static System GetRootAsSystem(ByteBuffer _bb, System obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public System __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<System> CreateSystem(FlatBufferBuilder builder,
      StringOffset nameOffset = default(StringOffset)) {
    builder.StartObject(1);
    System.AddName(builder, nameOffset);
    return System.EndSystem(builder);
  }

  public static void StartSystem(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(0, nameOffset.Value, 0); }
  public static Offset<System> EndSystem(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<System>(o);
  }
};

public sealed class AmbientLight : Table {
  public static AmbientLight GetRootAsAmbientLight(ByteBuffer _bb) { return GetRootAsAmbientLight(_bb, new AmbientLight()); }
  public static AmbientLight GetRootAsAmbientLight(ByteBuffer _bb, AmbientLight obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public AmbientLight __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Colour UpperHemisphere { get { return GetUpperHemisphere(new Colour()); } }
  public Colour GetUpperHemisphere(Colour obj) { int o = __offset(4); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Colour LowerHemisphere { get { return GetLowerHemisphere(new Colour()); } }
  public Colour GetLowerHemisphere(Colour obj) { int o = __offset(6); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Vec3f HemisphereDir { get { return GetHemisphereDir(new Vec3f()); } }
  public Vec3f GetHemisphereDir(Vec3f obj) { int o = __offset(8); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public float EnvmapScale { get { int o = __offset(10); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }

  public static void StartAmbientLight(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddUpperHemisphere(FlatBufferBuilder builder, Offset<Colour> upperHemisphereOffset) { builder.AddStruct(0, upperHemisphereOffset.Value, 0); }
  public static void AddLowerHemisphere(FlatBufferBuilder builder, Offset<Colour> lowerHemisphereOffset) { builder.AddStruct(1, lowerHemisphereOffset.Value, 0); }
  public static void AddHemisphereDir(FlatBufferBuilder builder, Offset<Vec3f> hemisphereDirOffset) { builder.AddStruct(2, hemisphereDirOffset.Value, 0); }
  public static void AddEnvmapScale(FlatBufferBuilder builder, float envmapScale) { builder.AddFloat(3, envmapScale, 0); }
  public static Offset<AmbientLight> EndAmbientLight(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<AmbientLight>(o);
  }
};

public sealed class Scene : Table {
  public static Scene GetRootAsScene(ByteBuffer _bb) { return GetRootAsScene(_bb, new Scene()); }
  public static Scene GetRootAsScene(ByteBuffer _bb, Scene obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Scene __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Sceneid { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public System GetSystems(int j) { return GetSystems(new System(), j); }
  public System GetSystems(System obj, int j) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int SystemsLength { get { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; } }
  public string Type { get { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Scene> CreateScene(FlatBufferBuilder builder,
      ushort sceneid = 0,
      VectorOffset systemsOffset = default(VectorOffset),
      StringOffset typeOffset = default(StringOffset)) {
    builder.StartObject(3);
    Scene.AddType(builder, typeOffset);
    Scene.AddSystems(builder, systemsOffset);
    Scene.AddSceneid(builder, sceneid);
    return Scene.EndScene(builder);
  }

  public static void StartScene(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddSceneid(FlatBufferBuilder builder, ushort sceneid) { builder.AddUshort(0, sceneid, 0); }
  public static void AddSystems(FlatBufferBuilder builder, VectorOffset systemsOffset) { builder.AddOffset(1, systemsOffset.Value, 0); }
  public static VectorOffset CreateSystemsVector(FlatBufferBuilder builder, Offset<System>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartSystemsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddType(FlatBufferBuilder builder, StringOffset typeOffset) { builder.AddOffset(2, typeOffset.Value, 0); }
  public static Offset<Scene> EndScene(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Scene>(o);
  }
};

public sealed class Connection : Struct {
  public Connection __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint NodeIn { get { return bb.GetUint(bb_pos + 0); } }
  public uint NodeOut { get { return bb.GetUint(bb_pos + 4); } }
  public uint PortIn { get { return bb.GetUint(bb_pos + 8); } }

  public static Offset<Connection> CreateConnection(FlatBufferBuilder builder, uint NodeIn, uint NodeOut, uint PortIn) {
    builder.Prep(4, 12);
    builder.PutUint(PortIn);
    builder.PutUint(NodeOut);
    builder.PutUint(NodeIn);
    return new Offset<Connection>(builder.Offset);
  }
};

public sealed class Parameter : Struct {
  public Parameter __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float Value { get { return bb.GetFloat(bb_pos + 0); } }

  public static Offset<Parameter> CreateParameter(FlatBufferBuilder builder, float Value) {
    builder.Prep(4, 4);
    builder.PutFloat(Value);
    return new Offset<Parameter>(builder.Offset);
  }
};

public sealed class Constant : Struct {
  public Constant __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint Id { get { return bb.GetUint(bb_pos + 0); } }
  public uint NodeId { get { return bb.GetUint(bb_pos + 4); } }
  public uint PortId { get { return bb.GetUint(bb_pos + 8); } }
  public float Value { get { return bb.GetFloat(bb_pos + 12); } }

  public static Offset<Constant> CreateConstant(FlatBufferBuilder builder, uint Id, uint NodeId, uint PortId, float Value) {
    builder.Prep(4, 16);
    builder.PutFloat(Value);
    builder.PutUint(PortId);
    builder.PutUint(NodeId);
    builder.PutUint(Id);
    return new Offset<Constant>(builder.Offset);
  }
};

public sealed class AnimTrigger : Struct {
  public AnimTrigger __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint Id { get { return bb.GetUint(bb_pos + 0); } }
  public float Time { get { return bb.GetFloat(bb_pos + 4); } }
  public TimeType TimeType { get { return (TimeType)bb.Get(bb_pos + 8); } }
  public float MinWeightThreshold { get { return bb.GetFloat(bb_pos + 12); } }

  public static Offset<AnimTrigger> CreateAnimTrigger(FlatBufferBuilder builder, uint Id, float Time, TimeType TimeType, float MinWeightThreshold) {
    builder.Prep(4, 16);
    builder.PutFloat(MinWeightThreshold);
    builder.Pad(3);
    builder.PutByte((byte)TimeType);
    builder.PutFloat(Time);
    builder.PutUint(Id);
    return new Offset<AnimTrigger>(builder.Offset);
  }
};

public sealed class Animation : Table {
  public static Animation GetRootAsAnimation(ByteBuffer _bb) { return GetRootAsAnimation(_bb, new Animation()); }
  public static Animation GetRootAsAnimation(ByteBuffer _bb, Animation obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Animation __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint Id { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public bool Loop { get { int o = __offset(6); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public AnimTrigger GetTriggers(int j) { return GetTriggers(new AnimTrigger(), j); }
  public AnimTrigger GetTriggers(AnimTrigger obj, int j) { int o = __offset(8); return o != 0 ? obj.__init(__vector(o) + j * 16, bb) : null; }
  public int TriggersLength { get { int o = __offset(8); return o != 0 ? __vector_len(o) : 0; } }
  public string Name { get { int o = __offset(10); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Animation> CreateAnimation(FlatBufferBuilder builder,
      uint id = 0,
      bool loop = false,
      VectorOffset triggersOffset = default(VectorOffset),
      StringOffset nameOffset = default(StringOffset)) {
    builder.StartObject(4);
    Animation.AddName(builder, nameOffset);
    Animation.AddTriggers(builder, triggersOffset);
    Animation.AddId(builder, id);
    Animation.AddLoop(builder, loop);
    return Animation.EndAnimation(builder);
  }

  public static void StartAnimation(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddId(FlatBufferBuilder builder, uint id) { builder.AddUint(0, id, 0); }
  public static void AddLoop(FlatBufferBuilder builder, bool loop) { builder.AddBool(1, loop, false); }
  public static void AddTriggers(FlatBufferBuilder builder, VectorOffset triggersOffset) { builder.AddOffset(2, triggersOffset.Value, 0); }
  public static void StartTriggersVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(16, numElems, 4); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(3, nameOffset.Value, 0); }
  public static Offset<Animation> EndAnimation(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Animation>(o);
  }
};

public sealed class AnimationNode : Table {
  public static AnimationNode GetRootAsAnimationNode(ByteBuffer _bb) { return GetRootAsAnimationNode(_bb, new AnimationNode()); }
  public static AnimationNode GetRootAsAnimationNode(ByteBuffer _bb, AnimationNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public AnimationNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Animation Animation { get { return GetAnimation(new Animation()); } }
  public Animation GetAnimation(Animation obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<AnimationNode> CreateAnimationNode(FlatBufferBuilder builder,
      Offset<Animation> animationOffset = default(Offset<Animation>)) {
    builder.StartObject(1);
    AnimationNode.AddAnimation(builder, animationOffset);
    return AnimationNode.EndAnimationNode(builder);
  }

  public static void StartAnimationNode(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddAnimation(FlatBufferBuilder builder, Offset<Animation> animationOffset) { builder.AddOffset(0, animationOffset.Value, 0); }
  public static Offset<AnimationNode> EndAnimationNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<AnimationNode>(o);
  }
};

public sealed class ParameterNode : Table {
  public static ParameterNode GetRootAsParameterNode(ByteBuffer _bb) { return GetRootAsParameterNode(_bb, new ParameterNode()); }
  public static ParameterNode GetRootAsParameterNode(ByteBuffer _bb, ParameterNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public ParameterNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Parameter Param { get { return GetParam(new Parameter()); } }
  public Parameter GetParam(Parameter obj) { int o = __offset(4); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }

  public static void StartParameterNode(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddParam(FlatBufferBuilder builder, Offset<Parameter> paramOffset) { builder.AddStruct(0, paramOffset.Value, 0); }
  public static Offset<ParameterNode> EndParameterNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ParameterNode>(o);
  }
};

public sealed class TransitionSelectNode : Table {
  public static TransitionSelectNode GetRootAsTransitionSelectNode(ByteBuffer _bb) { return GetRootAsTransitionSelectNode(_bb, new TransitionSelectNode()); }
  public static TransitionSelectNode GetRootAsTransitionSelectNode(ByteBuffer _bb, TransitionSelectNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public TransitionSelectNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Select { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public float TimeIn { get { int o = __offset(6); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float TimeOut { get { int o = __offset(8); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public ushort Size { get { int o = __offset(10); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static Offset<TransitionSelectNode> CreateTransitionSelectNode(FlatBufferBuilder builder,
      ushort select = 0,
      float timeIn = 0,
      float timeOut = 0,
      ushort size = 0) {
    builder.StartObject(4);
    TransitionSelectNode.AddTimeOut(builder, timeOut);
    TransitionSelectNode.AddTimeIn(builder, timeIn);
    TransitionSelectNode.AddSize(builder, size);
    TransitionSelectNode.AddSelect(builder, select);
    return TransitionSelectNode.EndTransitionSelectNode(builder);
  }

  public static void StartTransitionSelectNode(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddSelect(FlatBufferBuilder builder, ushort select) { builder.AddUshort(0, select, 0); }
  public static void AddTimeIn(FlatBufferBuilder builder, float timeIn) { builder.AddFloat(1, timeIn, 0); }
  public static void AddTimeOut(FlatBufferBuilder builder, float timeOut) { builder.AddFloat(2, timeOut, 0); }
  public static void AddSize(FlatBufferBuilder builder, ushort size) { builder.AddUshort(3, size, 0); }
  public static Offset<TransitionSelectNode> EndTransitionSelectNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<TransitionSelectNode>(o);
  }
};

public sealed class AverageNode : Table {
  public static AverageNode GetRootAsAverageNode(ByteBuffer _bb) { return GetRootAsAverageNode(_bb, new AverageNode()); }
  public static AverageNode GetRootAsAverageNode(ByteBuffer _bb, AverageNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public AverageNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Size { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static Offset<AverageNode> CreateAverageNode(FlatBufferBuilder builder,
      ushort size = 0) {
    builder.StartObject(1);
    AverageNode.AddSize(builder, size);
    return AverageNode.EndAverageNode(builder);
  }

  public static void StartAverageNode(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddSize(FlatBufferBuilder builder, ushort size) { builder.AddUshort(0, size, 0); }
  public static Offset<AverageNode> EndAverageNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<AverageNode>(o);
  }
};

public sealed class MaskAddNode : Table {
  public static MaskAddNode GetRootAsMaskAddNode(ByteBuffer _bb) { return GetRootAsMaskAddNode(_bb, new MaskAddNode()); }
  public static MaskAddNode GetRootAsMaskAddNode(ByteBuffer _bb, MaskAddNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public MaskAddNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }


  public static void StartMaskAddNode(FlatBufferBuilder builder) { builder.StartObject(0); }
  public static Offset<MaskAddNode> EndMaskAddNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<MaskAddNode>(o);
  }
};

public sealed class SmoothValueNode : Table {
  public static SmoothValueNode GetRootAsSmoothValueNode(ByteBuffer _bb) { return GetRootAsSmoothValueNode(_bb, new SmoothValueNode()); }
  public static SmoothValueNode GetRootAsSmoothValueNode(ByteBuffer _bb, SmoothValueNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public SmoothValueNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float InitialValue { get { int o = __offset(4); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }

  public static Offset<SmoothValueNode> CreateSmoothValueNode(FlatBufferBuilder builder,
      float initial_value = 0) {
    builder.StartObject(1);
    SmoothValueNode.AddInitialValue(builder, initial_value);
    return SmoothValueNode.EndSmoothValueNode(builder);
  }

  public static void StartSmoothValueNode(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddInitialValue(FlatBufferBuilder builder, float initialValue) { builder.AddFloat(0, initialValue, 0); }
  public static Offset<SmoothValueNode> EndSmoothValueNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<SmoothValueNode>(o);
  }
};

public sealed class LookAtNode : Table {
  public static LookAtNode GetRootAsLookAtNode(ByteBuffer _bb) { return GetRootAsLookAtNode(_bb, new LookAtNode()); }
  public static LookAtNode GetRootAsLookAtNode(ByteBuffer _bb, LookAtNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public LookAtNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }


  public static void StartLookAtNode(FlatBufferBuilder builder) { builder.StartObject(0); }
  public static Offset<LookAtNode> EndLookAtNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<LookAtNode>(o);
  }
};

public sealed class RandomSelectNode : Table {
  public static RandomSelectNode GetRootAsRandomSelectNode(ByteBuffer _bb) { return GetRootAsRandomSelectNode(_bb, new RandomSelectNode()); }
  public static RandomSelectNode GetRootAsRandomSelectNode(ByteBuffer _bb, RandomSelectNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public RandomSelectNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Size { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static Offset<RandomSelectNode> CreateRandomSelectNode(FlatBufferBuilder builder,
      ushort size = 0) {
    builder.StartObject(1);
    RandomSelectNode.AddSize(builder, size);
    return RandomSelectNode.EndRandomSelectNode(builder);
  }

  public static void StartRandomSelectNode(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddSize(FlatBufferBuilder builder, ushort size) { builder.AddUshort(0, size, 0); }
  public static Offset<RandomSelectNode> EndRandomSelectNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<RandomSelectNode>(o);
  }
};

public sealed class MixNode : Table {
  public static MixNode GetRootAsMixNode(ByteBuffer _bb) { return GetRootAsMixNode(_bb, new MixNode()); }
  public static MixNode GetRootAsMixNode(ByteBuffer _bb, MixNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public MixNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Size { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static Offset<MixNode> CreateMixNode(FlatBufferBuilder builder,
      ushort size = 0) {
    builder.StartObject(1);
    MixNode.AddSize(builder, size);
    return MixNode.EndMixNode(builder);
  }

  public static void StartMixNode(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddSize(FlatBufferBuilder builder, ushort size) { builder.AddUshort(0, size, 0); }
  public static Offset<MixNode> EndMixNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<MixNode>(o);
  }
};

public sealed class AnimNode : Table {
  public static AnimNode GetRootAsAnimNode(ByteBuffer _bb) { return GetRootAsAnimNode(_bb, new AnimNode()); }
  public static AnimNode GetRootAsAnimNode(ByteBuffer _bb, AnimNode obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public AnimNode __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint Id { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public UAnimationNode NodeType { get { int o = __offset(6); return o != 0 ? (UAnimationNode)bb.Get(o + bb_pos) : UAnimationNode.NONE; } }
  public TTable GetNode<TTable>(TTable obj) where TTable : Table { int o = __offset(8); return o != 0 ? __union(obj, o) : null; }

  public static Offset<AnimNode> CreateAnimNode(FlatBufferBuilder builder,
      uint id = 0,
      UAnimationNode node_type = UAnimationNode.NONE,
      int nodeOffset = 0) {
    builder.StartObject(3);
    AnimNode.AddNode(builder, nodeOffset);
    AnimNode.AddId(builder, id);
    AnimNode.AddNodeType(builder, node_type);
    return AnimNode.EndAnimNode(builder);
  }

  public static void StartAnimNode(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddId(FlatBufferBuilder builder, uint id) { builder.AddUint(0, id, 0); }
  public static void AddNodeType(FlatBufferBuilder builder, UAnimationNode nodeType) { builder.AddByte(1, (byte)nodeType, 0); }
  public static void AddNode(FlatBufferBuilder builder, int nodeOffset) { builder.AddOffset(2, nodeOffset, 0); }
  public static Offset<AnimNode> EndAnimNode(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<AnimNode>(o);
  }
};

public sealed class BodyComponent : Table {
  public static BodyComponent GetRootAsBodyComponent(ByteBuffer _bb) { return GetRootAsBodyComponent(_bb, new BodyComponent()); }
  public static BodyComponent GetRootAsBodyComponent(ByteBuffer _bb, BodyComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public BodyComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Vec3f Position { get { return GetPosition(new Vec3f()); } }
  public Vec3f GetPosition(Vec3f obj) { int o = __offset(4); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Quat4f Rotation { get { return GetRotation(new Quat4f()); } }
  public Quat4f GetRotation(Quat4f obj) { int o = __offset(6); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Vec3f Scale { get { return GetScale(new Vec3f()); } }
  public Vec3f GetScale(Vec3f obj) { int o = __offset(8); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public uint SceneId { get { int o = __offset(10); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public bool Visible { get { int o = __offset(12); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)true; } }
  public bool Enabled { get { int o = __offset(14); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)true; } }
  public uint Group { get { int o = __offset(16); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }

  public static void StartBodyComponent(FlatBufferBuilder builder) { builder.StartObject(7); }
  public static void AddPosition(FlatBufferBuilder builder, Offset<Vec3f> positionOffset) { builder.AddStruct(0, positionOffset.Value, 0); }
  public static void AddRotation(FlatBufferBuilder builder, Offset<Quat4f> rotationOffset) { builder.AddStruct(1, rotationOffset.Value, 0); }
  public static void AddScale(FlatBufferBuilder builder, Offset<Vec3f> scaleOffset) { builder.AddStruct(2, scaleOffset.Value, 0); }
  public static void AddSceneId(FlatBufferBuilder builder, uint sceneId) { builder.AddUint(3, sceneId, 0); }
  public static void AddVisible(FlatBufferBuilder builder, bool visible) { builder.AddBool(4, visible, true); }
  public static void AddEnabled(FlatBufferBuilder builder, bool enabled) { builder.AddBool(5, enabled, true); }
  public static void AddGroup(FlatBufferBuilder builder, uint group) { builder.AddUint(6, group, 0); }
  public static Offset<BodyComponent> EndBodyComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<BodyComponent>(o);
  }
};

public sealed class AnimationComponent : Table {
  public static AnimationComponent GetRootAsAnimationComponent(ByteBuffer _bb) { return GetRootAsAnimationComponent(_bb, new AnimationComponent()); }
  public static AnimationComponent GetRootAsAnimationComponent(ByteBuffer _bb, AnimationComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public AnimationComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string AnimationTree { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public string AnimationInfo { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }
  public AnimNode GetNodes(int j) { return GetNodes(new AnimNode(), j); }
  public AnimNode GetNodes(AnimNode obj, int j) { int o = __offset(8); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int NodesLength { get { int o = __offset(8); return o != 0 ? __vector_len(o) : 0; } }
  public Connection GetConnections(int j) { return GetConnections(new Connection(), j); }
  public Connection GetConnections(Connection obj, int j) { int o = __offset(10); return o != 0 ? obj.__init(__vector(o) + j * 12, bb) : null; }
  public int ConnectionsLength { get { int o = __offset(10); return o != 0 ? __vector_len(o) : 0; } }
  public Constant GetConstants(int j) { return GetConstants(new Constant(), j); }
  public Constant GetConstants(Constant obj, int j) { int o = __offset(12); return o != 0 ? obj.__init(__vector(o) + j * 16, bb) : null; }
  public int ConstantsLength { get { int o = __offset(12); return o != 0 ? __vector_len(o) : 0; } }
  public string Boneparent { get { int o = __offset(14); return o != 0 ? __string(o + bb_pos) : null; } }
  public uint Output { get { int o = __offset(16); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }

  public static Offset<AnimationComponent> CreateAnimationComponent(FlatBufferBuilder builder,
      StringOffset animationTreeOffset = default(StringOffset),
      StringOffset animationInfoOffset = default(StringOffset),
      VectorOffset nodesOffset = default(VectorOffset),
      VectorOffset connectionsOffset = default(VectorOffset),
      VectorOffset constantsOffset = default(VectorOffset),
      StringOffset boneparentOffset = default(StringOffset),
      uint output = 0) {
    builder.StartObject(7);
    AnimationComponent.AddOutput(builder, output);
    AnimationComponent.AddBoneparent(builder, boneparentOffset);
    AnimationComponent.AddConstants(builder, constantsOffset);
    AnimationComponent.AddConnections(builder, connectionsOffset);
    AnimationComponent.AddNodes(builder, nodesOffset);
    AnimationComponent.AddAnimationInfo(builder, animationInfoOffset);
    AnimationComponent.AddAnimationTree(builder, animationTreeOffset);
    return AnimationComponent.EndAnimationComponent(builder);
  }

  public static void StartAnimationComponent(FlatBufferBuilder builder) { builder.StartObject(7); }
  public static void AddAnimationTree(FlatBufferBuilder builder, StringOffset animationTreeOffset) { builder.AddOffset(0, animationTreeOffset.Value, 0); }
  public static void AddAnimationInfo(FlatBufferBuilder builder, StringOffset animationInfoOffset) { builder.AddOffset(1, animationInfoOffset.Value, 0); }
  public static void AddNodes(FlatBufferBuilder builder, VectorOffset nodesOffset) { builder.AddOffset(2, nodesOffset.Value, 0); }
  public static VectorOffset CreateNodesVector(FlatBufferBuilder builder, Offset<AnimNode>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartNodesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddConnections(FlatBufferBuilder builder, VectorOffset connectionsOffset) { builder.AddOffset(3, connectionsOffset.Value, 0); }
  public static void StartConnectionsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(12, numElems, 4); }
  public static void AddConstants(FlatBufferBuilder builder, VectorOffset constantsOffset) { builder.AddOffset(4, constantsOffset.Value, 0); }
  public static void StartConstantsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(16, numElems, 4); }
  public static void AddBoneparent(FlatBufferBuilder builder, StringOffset boneparentOffset) { builder.AddOffset(5, boneparentOffset.Value, 0); }
  public static void AddOutput(FlatBufferBuilder builder, uint output) { builder.AddUint(6, output, 0); }
  public static Offset<AnimationComponent> EndAnimationComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<AnimationComponent>(o);
  }
};

public sealed class SoundComponent : Table {
  public static SoundComponent GetRootAsSoundComponent(ByteBuffer _bb) { return GetRootAsSoundComponent(_bb, new SoundComponent()); }
  public static SoundComponent GetRootAsSoundComponent(ByteBuffer _bb, SoundComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public SoundComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Sound GetSounds(int j) { return GetSounds(new Sound(), j); }
  public Sound GetSounds(Sound obj, int j) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int SoundsLength { get { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; } }

  public static Offset<SoundComponent> CreateSoundComponent(FlatBufferBuilder builder,
      VectorOffset soundsOffset = default(VectorOffset)) {
    builder.StartObject(1);
    SoundComponent.AddSounds(builder, soundsOffset);
    return SoundComponent.EndSoundComponent(builder);
  }

  public static void StartSoundComponent(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddSounds(FlatBufferBuilder builder, VectorOffset soundsOffset) { builder.AddOffset(0, soundsOffset.Value, 0); }
  public static VectorOffset CreateSoundsVector(FlatBufferBuilder builder, Offset<Sound>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartSoundsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<SoundComponent> EndSoundComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<SoundComponent>(o);
  }
};


}
