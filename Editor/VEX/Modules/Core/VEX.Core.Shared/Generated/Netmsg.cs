// automatically generated, do not modify

namespace NetMsg
{
    using ControllerSettings;
    using FlatBuffers;
    using XFBType;

    public enum AbilityBehavior : ushort
{
 AB_None = 0,
 AB_Punch = 1,
 AB_Bolt = 2,
 AB_Block = 3,
};

public enum MsgStatus : ushort
{
 S_Unknown = 0,
 S_LoginSuccess = 1,
 S_AlreadyLoggedIn = 2,
 S_AccessDenied = 3,
};

public enum UIStateId : ushort
{
 Console = 0,
 Stats = 1,
 Settings = 2,
 Controller = 3,
 Welcome = 4,
 Cusomize = 5,
 Game = 6,
 GameMenu = 7,
 Count = 8,
};

public enum PlayerState : ushort
{
 Idling = 0,
 Joining = 1,
 Dying = 2,
 Dead = 3,
 Running = 4,
 Walking = 5,
 JumpStart = 6,
 InAir = 7,
 JumpLanding = 8,
 OnMenu = 9,
 IsCustomizing = 10,
 IsSpawning = 11,
 Spectating = 12,
 Casting = 13,
 Emote_1 = 14,
 Emote_2 = 15,
 Emote_3 = 16,
 Dancing_1 = 17,
 Dancing_2 = 18,
 Dancing_3 = 19,
 Blocking_1 = 20,
 Blocking_2 = 21,
 Blocking_3 = 22,
 Attack_1 = 23,
 Attack_2 = 24,
 Attack_3 = 25,
 Attack_4 = 26,
 Attack_5 = 27,
 Attack_6 = 28,
 Hitted_1 = 29,
 Hitted_2 = 30,
 Hitted_3 = 31,
 Hitted_4 = 32,
 Hitted_5 = 33,
 Hitted_6 = 34,
 Count = 35,
};

public enum AnimationParameterId : uint
{
 AnimationState = 0,
 LookDirectionHorizontal = 1,
 LookDirectionVertical = 2,
 JumpPost = 3,
};

public enum AnimationTriggerId : uint
{
 attack_end = 1,
 attack_start = 2,
};

public enum AnimPortId : uint
{
 Speed = 0,
 Synch = 1,
 In = 2,
 select = 3,
 timeIn = 4,
 timeOut = 5,
 in0 = 6,
 in1 = 7,
 weight = 8,
 value = 9,
 smoothTime = 10,
 horizontalAmount = 11,
 verticalAmount = 12,
 left = 13,
 right = 14,
 up = 15,
 down = 16,
 min = 17,
 max = 18,
 minIn = 20,
 maxIn = 21,
 minOut = 22,
 maxOut = 23,
};

public enum AnimationId : uint
{
 SliceHorizontal = 0,
 SliceVertical = 1,
 JumpStart = 2,
 JumpLoop = 3,
 RunTop = 4,
 JumpEnd = 5,
 RunBase = 6,
 IdleTop = 7,
 IdleBase = 8,
 HandsRelaxed = 9,
 HandsClosed = 10,
 Dance = 11,
 DrawSwords = 12,
};

public enum ComponentType : ushort
{
 CT_None = 0,
 CT_NetId = 1,
 CT_Body = 2,
 CT_Renderable = 3,
 CT_Controller = 4,
 CT_Player = 5,
 CT_Spell = 6,
 CT_Static = 7,
};

public enum UComponent : byte
{
 NONE = 0,
 CharacterComponent = 1,
 AIComponent = 2,
 SpawnPointComponent = 3,
 SpawnComponent = 4,
 AnimationComponent = 5,
 BodyComponent = 6,
 PlayerComponent = 7,
 SpellComponent = 8,
 RenderableComponent = 9,
 StaticComponent = 10,
 Camera = 11,
 Light = 12,
 SoundListener = 13,
 AbilityComponent = 14,
 PhysicsComponent = 15,
 SoundComponent = 16,
};

public enum Data : byte
{
 NONE = 0,
 Chatmessage = 1,
 Scene = 2,
 Login = 3,
 ReturnStatus = 4,
 InputEvent = 5,
 Entity = 6,
 GameState = 7,
 ExecCommand = 8,
};

public sealed class SpellComponent : Table {
  public static SpellComponent GetRootAsSpellComponent(ByteBuffer _bb) { return GetRootAsSpellComponent(_bb, new SpellComponent()); }
  public static SpellComponent GetRootAsSpellComponent(ByteBuffer _bb, SpellComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public SpellComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }


  public static void StartSpellComponent(FlatBufferBuilder builder) { builder.StartObject(0); }
  public static Offset<SpellComponent> EndSpellComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<SpellComponent>(o);
  }
};

public sealed class StaticComponent : Table {
  public static StaticComponent GetRootAsStaticComponent(ByteBuffer _bb) { return GetRootAsStaticComponent(_bb, new StaticComponent()); }
  public static StaticComponent GetRootAsStaticComponent(ByteBuffer _bb, StaticComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public StaticComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }


  public static void StartStaticComponent(FlatBufferBuilder builder) { builder.StartObject(0); }
  public static Offset<StaticComponent> EndStaticComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<StaticComponent>(o);
  }
};

public sealed class GameState : Table {
  public static GameState GetRootAsGameState(ByteBuffer _bb) { return GetRootAsGameState(_bb, new GameState()); }
  public static GameState GetRootAsGameState(ByteBuffer _bb, GameState obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public GameState __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Scene Scene { get { return GetScene(new Scene()); } }
  public Scene GetScene(Scene obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<GameState> CreateGameState(FlatBufferBuilder builder,
      Offset<Scene> sceneOffset = default(Offset<Scene>)) {
    builder.StartObject(1);
    GameState.AddScene(builder, sceneOffset);
    return GameState.EndGameState(builder);
  }

  public static void StartGameState(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddScene(FlatBufferBuilder builder, Offset<Scene> sceneOffset) { builder.AddOffset(0, sceneOffset.Value, 0); }
  public static Offset<GameState> EndGameState(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<GameState>(o);
  }
};

public sealed class AbilityInfo : Table {
  public static AbilityInfo GetRootAsAbilityInfo(ByteBuffer _bb) { return GetRootAsAbilityInfo(_bb, new AbilityInfo()); }
  public static AbilityInfo GetRootAsAbilityInfo(ByteBuffer _bb, AbilityInfo obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public AbilityInfo __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  ///entityID with the attached abilitycomponent
  public uint AbilityId { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  ///instant abilities are loaded at character creation
  public bool Instant { get { int o = __offset(6); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  ///ability is attached to an entity and is not a entity itself
  public bool IsAttached { get { int o = __offset(8); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }

  public static Offset<AbilityInfo> CreateAbilityInfo(FlatBufferBuilder builder,
      uint abilityId = 0,
      bool instant = false,
      bool isAttached = false) {
    builder.StartObject(3);
    AbilityInfo.AddAbilityId(builder, abilityId);
    AbilityInfo.AddIsAttached(builder, isAttached);
    AbilityInfo.AddInstant(builder, instant);
    return AbilityInfo.EndAbilityInfo(builder);
  }

  public static void StartAbilityInfo(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddAbilityId(FlatBufferBuilder builder, uint abilityId) { builder.AddUint(0, abilityId, 0); }
  public static void AddInstant(FlatBufferBuilder builder, bool instant) { builder.AddBool(1, instant, false); }
  public static void AddIsAttached(FlatBufferBuilder builder, bool isAttached) { builder.AddBool(2, isAttached, false); }
  public static Offset<AbilityInfo> EndAbilityInfo(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<AbilityInfo>(o);
  }
};

public sealed class CharacterComponent : Table {
  public static CharacterComponent GetRootAsCharacterComponent(ByteBuffer _bb) { return GetRootAsCharacterComponent(_bb, new CharacterComponent()); }
  public static CharacterComponent GetRootAsCharacterComponent(ByteBuffer _bb, CharacterComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public CharacterComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public float MoveSpeed { get { int o = __offset(6); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public ushort Hp { get { int o = __offset(8); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort ResourcePoints { get { int o = __offset(10); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public Vec3f OffsetPunch { get { return GetOffsetPunch(new Vec3f()); } }
  public Vec3f GetOffsetPunch(Vec3f obj) { int o = __offset(12); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public AbilityInfo GetAbilities(int j) { return GetAbilities(new AbilityInfo(), j); }
  public AbilityInfo GetAbilities(AbilityInfo obj, int j) { int o = __offset(14); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int AbilitiesLength { get { int o = __offset(14); return o != 0 ? __vector_len(o) : 0; } }

  public static void StartCharacterComponent(FlatBufferBuilder builder) { builder.StartObject(6); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(0, nameOffset.Value, 0); }
  public static void AddMoveSpeed(FlatBufferBuilder builder, float moveSpeed) { builder.AddFloat(1, moveSpeed, 0); }
  public static void AddHp(FlatBufferBuilder builder, ushort hp) { builder.AddUshort(2, hp, 0); }
  public static void AddResourcePoints(FlatBufferBuilder builder, ushort resourcePoints) { builder.AddUshort(3, resourcePoints, 0); }
  public static void AddOffsetPunch(FlatBufferBuilder builder, Offset<Vec3f> offsetPunchOffset) { builder.AddStruct(4, offsetPunchOffset.Value, 0); }
  public static void AddAbilities(FlatBufferBuilder builder, VectorOffset abilitiesOffset) { builder.AddOffset(5, abilitiesOffset.Value, 0); }
  public static VectorOffset CreateAbilitiesVector(FlatBufferBuilder builder, Offset<AbilityInfo>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartAbilitiesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<CharacterComponent> EndCharacterComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<CharacterComponent>(o);
  }
};

///per default just a ghost object
public sealed class AbilityComponent : Table {
  public static AbilityComponent GetRootAsAbilityComponent(ByteBuffer _bb) { return GetRootAsAbilityComponent(_bb, new AbilityComponent()); }
  public static AbilityComponent GetRootAsAbilityComponent(ByteBuffer _bb, AbilityComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public AbilityComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Id { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public bool HasPhysics { get { int o = __offset(6); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public float Duration { get { int o = __offset(8); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Cooldown { get { int o = __offset(10); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Power { get { int o = __offset(12); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public PhysicsShape Shape { get { int o = __offset(14); return o != 0 ? (PhysicsShape)bb.GetSbyte(o + bb_pos) : PhysicsShape.SH_BOX; } }
  public Vec3f Size { get { return GetSize(new Vec3f()); } }
  public Vec3f GetSize(Vec3f obj) { int o = __offset(16); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Vec3f Offset { get { return GetOffset(new Vec3f()); } }
  public Vec3f GetOffset(Vec3f obj) { int o = __offset(18); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public AbilityBehavior AbilityBehavior { get { int o = __offset(20); return o != 0 ? (AbilityBehavior)bb.GetUshort(o + bb_pos) : AbilityBehavior.AB_None; } }

  public static void StartAbilityComponent(FlatBufferBuilder builder) { builder.StartObject(9); }
  public static void AddId(FlatBufferBuilder builder, ushort id) { builder.AddUshort(0, id, 0); }
  public static void AddHasPhysics(FlatBufferBuilder builder, bool hasPhysics) { builder.AddBool(1, hasPhysics, false); }
  public static void AddDuration(FlatBufferBuilder builder, float duration) { builder.AddFloat(2, duration, 0); }
  public static void AddCooldown(FlatBufferBuilder builder, float cooldown) { builder.AddFloat(3, cooldown, 0); }
  public static void AddPower(FlatBufferBuilder builder, float power) { builder.AddFloat(4, power, 0); }
  public static void AddShape(FlatBufferBuilder builder, PhysicsShape shape) { builder.AddSbyte(5, (sbyte)shape, 0); }
  public static void AddSize(FlatBufferBuilder builder, Offset<Vec3f> sizeOffset) { builder.AddStruct(6, sizeOffset.Value, 0); }
  public static void AddOffset(FlatBufferBuilder builder, Offset<Vec3f> offsetOffset) { builder.AddStruct(7, offsetOffset.Value, 0); }
  public static void AddAbilityBehavior(FlatBufferBuilder builder, AbilityBehavior abilityBehavior) { builder.AddUshort(8, (ushort)abilityBehavior, 0); }
  public static Offset<AbilityComponent> EndAbilityComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<AbilityComponent>(o);
  }
};

public sealed class AIComponent : Table {
  public static AIComponent GetRootAsAIComponent(ByteBuffer _bb) { return GetRootAsAIComponent(_bb, new AIComponent()); }
  public static AIComponent GetRootAsAIComponent(ByteBuffer _bb, AIComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public AIComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Script { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<AIComponent> CreateAIComponent(FlatBufferBuilder builder,
      StringOffset scriptOffset = default(StringOffset)) {
    builder.StartObject(1);
    AIComponent.AddScript(builder, scriptOffset);
    return AIComponent.EndAIComponent(builder);
  }

  public static void StartAIComponent(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddScript(FlatBufferBuilder builder, StringOffset scriptOffset) { builder.AddOffset(0, scriptOffset.Value, 0); }
  public static Offset<AIComponent> EndAIComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<AIComponent>(o);
  }
};

public sealed class Chatmessage : Table {
  public static Chatmessage GetRootAsChatmessage(ByteBuffer _bb) { return GetRootAsChatmessage(_bb, new Chatmessage()); }
  public static Chatmessage GetRootAsChatmessage(ByteBuffer _bb, Chatmessage obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Chatmessage __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Group { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public string Text { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Chatmessage> CreateChatmessage(FlatBufferBuilder builder,
      ushort group = 0,
      StringOffset textOffset = default(StringOffset)) {
    builder.StartObject(2);
    Chatmessage.AddText(builder, textOffset);
    Chatmessage.AddGroup(builder, group);
    return Chatmessage.EndChatmessage(builder);
  }

  public static void StartChatmessage(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddGroup(FlatBufferBuilder builder, ushort group) { builder.AddUshort(0, group, 0); }
  public static void AddText(FlatBufferBuilder builder, StringOffset textOffset) { builder.AddOffset(1, textOffset.Value, 0); }
  public static Offset<Chatmessage> EndChatmessage(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Chatmessage>(o);
  }
};

public sealed class ExecCommand : Table {
  public static ExecCommand GetRootAsExecCommand(ByteBuffer _bb) { return GetRootAsExecCommand(_bb, new ExecCommand()); }
  public static ExecCommand GetRootAsExecCommand(ByteBuffer _bb, ExecCommand obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public ExecCommand __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Cmd { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public string CmdOpt { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<ExecCommand> CreateExecCommand(FlatBufferBuilder builder,
      StringOffset cmdOffset = default(StringOffset),
      StringOffset cmdOptOffset = default(StringOffset)) {
    builder.StartObject(2);
    ExecCommand.AddCmdOpt(builder, cmdOptOffset);
    ExecCommand.AddCmd(builder, cmdOffset);
    return ExecCommand.EndExecCommand(builder);
  }

  public static void StartExecCommand(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddCmd(FlatBufferBuilder builder, StringOffset cmdOffset) { builder.AddOffset(0, cmdOffset.Value, 0); }
  public static void AddCmdOpt(FlatBufferBuilder builder, StringOffset cmdOptOffset) { builder.AddOffset(1, cmdOptOffset.Value, 0); }
  public static Offset<ExecCommand> EndExecCommand(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ExecCommand>(o);
  }
};

public sealed class Login : Table {
  public static Login GetRootAsLogin(ByteBuffer _bb) { return GetRootAsLogin(_bb, new Login()); }
  public static Login GetRootAsLogin(ByteBuffer _bb, Login obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Login __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Identity { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Login> CreateLogin(FlatBufferBuilder builder,
      StringOffset identityOffset = default(StringOffset)) {
    builder.StartObject(1);
    Login.AddIdentity(builder, identityOffset);
    return Login.EndLogin(builder);
  }

  public static void StartLogin(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddIdentity(FlatBufferBuilder builder, StringOffset identityOffset) { builder.AddOffset(0, identityOffset.Value, 0); }
  public static Offset<Login> EndLogin(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Login>(o);
  }
};

public sealed class ReturnStatus : Table {
  public static ReturnStatus GetRootAsReturnStatus(ByteBuffer _bb) { return GetRootAsReturnStatus(_bb, new ReturnStatus()); }
  public static ReturnStatus GetRootAsReturnStatus(ByteBuffer _bb, ReturnStatus obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public ReturnStatus __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public MsgStatus Status { get { int o = __offset(4); return o != 0 ? (MsgStatus)bb.GetUshort(o + bb_pos) : MsgStatus.S_Unknown; } }

  public static Offset<ReturnStatus> CreateReturnStatus(FlatBufferBuilder builder,
      MsgStatus status = MsgStatus.S_Unknown) {
    builder.StartObject(1);
    ReturnStatus.AddStatus(builder, status);
    return ReturnStatus.EndReturnStatus(builder);
  }

  public static void StartReturnStatus(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddStatus(FlatBufferBuilder builder, MsgStatus status) { builder.AddUshort(0, (ushort)status, 0); }
  public static Offset<ReturnStatus> EndReturnStatus(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ReturnStatus>(o);
  }
};

public sealed class PlayerComponent : Table {
  public static PlayerComponent GetRootAsPlayerComponent(ByteBuffer _bb) { return GetRootAsPlayerComponent(_bb, new PlayerComponent()); }
  public static PlayerComponent GetRootAsPlayerComponent(ByteBuffer _bb, PlayerComponent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public PlayerComponent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public PlayerState PlayerState { get { int o = __offset(4); return o != 0 ? (PlayerState)bb.GetUshort(o + bb_pos) : PlayerState.Idling; } }

  public static Offset<PlayerComponent> CreatePlayerComponent(FlatBufferBuilder builder,
      PlayerState playerState = PlayerState.Idling) {
    builder.StartObject(1);
    PlayerComponent.AddPlayerState(builder, playerState);
    return PlayerComponent.EndPlayerComponent(builder);
  }

  public static void StartPlayerComponent(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddPlayerState(FlatBufferBuilder builder, PlayerState playerState) { builder.AddUshort(0, (ushort)playerState, 0); }
  public static Offset<PlayerComponent> EndPlayerComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<PlayerComponent>(o);
  }
};

public sealed class Entity : Table {
  public static Entity GetRootAsEntity(ByteBuffer _bb) { return GetRootAsEntity(_bb, new Entity()); }
  public static Entity GetRootAsEntity(ByteBuffer _bb, Entity obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Entity __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint EntityID { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public string Name { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }
  public bool DeleteEntity { get { int o = __offset(8); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public Component GetComponents(int j) { return GetComponents(new Component(), j); }
  public Component GetComponents(Component obj, int j) { int o = __offset(10); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int ComponentsLength { get { int o = __offset(10); return o != 0 ? __vector_len(o) : 0; } }
  public Component GetDeleteComponents(int j) { return GetDeleteComponents(new Component(), j); }
  public Component GetDeleteComponents(Component obj, int j) { int o = __offset(12); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int DeleteComponentsLength { get { int o = __offset(12); return o != 0 ? __vector_len(o) : 0; } }

  public static Offset<Entity> CreateEntity(FlatBufferBuilder builder,
      uint entityID = 0,
      StringOffset nameOffset = default(StringOffset),
      bool deleteEntity = false,
      VectorOffset componentsOffset = default(VectorOffset),
      VectorOffset deleteComponentsOffset = default(VectorOffset)) {
    builder.StartObject(5);
    Entity.AddDeleteComponents(builder, deleteComponentsOffset);
    Entity.AddComponents(builder, componentsOffset);
    Entity.AddName(builder, nameOffset);
    Entity.AddEntityID(builder, entityID);
    Entity.AddDeleteEntity(builder, deleteEntity);
    return Entity.EndEntity(builder);
  }

  public static void StartEntity(FlatBufferBuilder builder) { builder.StartObject(5); }
  public static void AddEntityID(FlatBufferBuilder builder, uint entityID) { builder.AddUint(0, entityID, 0); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(1, nameOffset.Value, 0); }
  public static void AddDeleteEntity(FlatBufferBuilder builder, bool deleteEntity) { builder.AddBool(2, deleteEntity, false); }
  public static void AddComponents(FlatBufferBuilder builder, VectorOffset componentsOffset) { builder.AddOffset(3, componentsOffset.Value, 0); }
  public static VectorOffset CreateComponentsVector(FlatBufferBuilder builder, Offset<Component>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartComponentsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddDeleteComponents(FlatBufferBuilder builder, VectorOffset deleteComponentsOffset) { builder.AddOffset(4, deleteComponentsOffset.Value, 0); }
  public static VectorOffset CreateDeleteComponentsVector(FlatBufferBuilder builder, Offset<Component>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartDeleteComponentsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<Entity> EndEntity(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Entity>(o);
  }
};

public sealed class InputEvent : Table {
  public static InputEvent GetRootAsInputEvent(ByteBuffer _bb) { return GetRootAsInputEvent(_bb, new InputEvent()); }
  public static InputEvent GetRootAsInputEvent(ByteBuffer _bb, InputEvent obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public InputEvent __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ActionType ActionType { get { int o = __offset(4); return o != 0 ? (ActionType)bb.GetUshort(o + bb_pos) : ActionType.None; } }
  public Vec3f ActionData { get { return GetActionData(new Vec3f()); } }
  public Vec3f GetActionData(Vec3f obj) { int o = __offset(6); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }

  public static void StartInputEvent(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddActionType(FlatBufferBuilder builder, ActionType actionType) { builder.AddUshort(0, (ushort)actionType, 0); }
  public static void AddActionData(FlatBufferBuilder builder, Offset<Vec3f> actionDataOffset) { builder.AddStruct(1, actionDataOffset.Value, 0); }
  public static Offset<InputEvent> EndInputEvent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<InputEvent>(o);
  }
};

public sealed class Component : Table {
  public static Component GetRootAsComponent(ByteBuffer _bb) { return GetRootAsComponent(_bb, new Component()); }
  public static Component GetRootAsComponent(ByteBuffer _bb, Component obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Component __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public UComponent CompType { get { int o = __offset(4); return o != 0 ? (UComponent)bb.Get(o + bb_pos) : UComponent.NONE; } }
  public TTable GetComp<TTable>(TTable obj) where TTable : Table { int o = __offset(6); return o != 0 ? __union(obj, o) : null; }

  public static Offset<Component> CreateComponent(FlatBufferBuilder builder,
      UComponent comp_type = UComponent.NONE,
      int compOffset = 0) {
    builder.StartObject(2);
    Component.AddComp(builder, compOffset);
    Component.AddCompType(builder, comp_type);
    return Component.EndComponent(builder);
  }

  public static void StartComponent(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddCompType(FlatBufferBuilder builder, UComponent compType) { builder.AddByte(0, (byte)compType, 0); }
  public static void AddComp(FlatBufferBuilder builder, int compOffset) { builder.AddOffset(1, compOffset, 0); }
  public static Offset<Component> EndComponent(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Component>(o);
  }
};

public sealed class MessageRoot : Table {
  public static MessageRoot GetRootAsMessageRoot(ByteBuffer _bb) { return GetRootAsMessageRoot(_bb, new MessageRoot()); }
  public static MessageRoot GetRootAsMessageRoot(ByteBuffer _bb, MessageRoot obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public MessageRoot __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint Netid { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public uint Scene { get { int o = __offset(6); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public Data DataType { get { int o = __offset(8); return o != 0 ? (Data)bb.Get(o + bb_pos) : Data.NONE; } }
  public TTable GetData<TTable>(TTable obj) where TTable : Table { int o = __offset(10); return o != 0 ? __union(obj, o) : null; }

  public static Offset<MessageRoot> CreateMessageRoot(FlatBufferBuilder builder,
      uint netid = 0,
      uint scene = 0,
      Data data_type = Data.NONE,
      int dataOffset = 0) {
    builder.StartObject(4);
    MessageRoot.AddData(builder, dataOffset);
    MessageRoot.AddScene(builder, scene);
    MessageRoot.AddNetid(builder, netid);
    MessageRoot.AddDataType(builder, data_type);
    return MessageRoot.EndMessageRoot(builder);
  }

  public static void StartMessageRoot(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddNetid(FlatBufferBuilder builder, uint netid) { builder.AddUint(0, netid, 0); }
  public static void AddScene(FlatBufferBuilder builder, uint scene) { builder.AddUint(1, scene, 0); }
  public static void AddDataType(FlatBufferBuilder builder, Data dataType) { builder.AddByte(2, (byte)dataType, 0); }
  public static void AddData(FlatBufferBuilder builder, int dataOffset) { builder.AddOffset(3, dataOffset, 0); }
  public static Offset<MessageRoot> EndMessageRoot(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<MessageRoot>(o);
  }
  public static void FinishMessageRootBuffer(FlatBufferBuilder builder, Offset<MessageRoot> offset) { builder.Finish(offset.Value); }
};


}
