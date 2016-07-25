// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_NETMSG_NETMSG_H_
#define FLATBUFFERS_GENERATED_NETMSG_NETMSG_H_

#include "flatbuffers/flatbuffers.h"

#include "Controllers_generated.h"
#include "FBEngineTypes_generated.h"

namespace XFBType {
struct Vec3f;
struct Quat4f;
struct Colour;
struct Clipping;
struct PhysicsConstraint;
struct PhysicsObject;
struct LocalFile;
struct Material;
struct MeshFile;
struct MeshCube;
struct MeshPlane;
struct MeshSphere;
struct Mesh;
struct RenderableComponent;
struct Sound;
struct SpawnComponent;
struct SpawnPointComponent;
struct Trigger;
struct PhysicsComponent;
struct SoundListener;
struct Light;
struct Camera;
struct System;
struct AmbientLight;
struct Scene;
struct Connection;
struct Parameter;
struct Constant;
struct AnimTrigger;
struct Animation;
struct AnimationNode;
struct ParameterNode;
struct TransitionSelectNode;
struct AverageNode;
struct MaskAddNode;
struct SmoothValueNode;
struct LookAtNode;
struct RandomSelectNode;
struct MixNode;
struct AnimNode;
struct BodyComponent;
struct AnimationComponent;
struct SoundComponent;
}  // namespace XFBType
namespace ControllerSettings {
struct Event;
struct Action;
struct ControllerMap;
struct ControllerList;
}  // namespace ControllerSettings

namespace NetMsg {

struct SpellComponent;
struct StaticComponent;
struct GameState;
struct CharacterComponent;
struct AIComponent;
struct Chatmessage;
struct Login;
struct ReturnStatus;
struct PlayerComponent;
struct Entity;
struct InputEvent;
struct Component;
struct MessageRoot;

enum MsgStatus {
  MsgStatus_S_Unknown = 0,
  MsgStatus_S_LoginSuccess = 1,
  MsgStatus_S_AlreadyLoggedIn = 2,
  MsgStatus_S_AccessDenied = 3
};

inline const char **EnumNamesMsgStatus() {
  static const char *names[] = { "S_Unknown", "S_LoginSuccess", "S_AlreadyLoggedIn", "S_AccessDenied", nullptr };
  return names;
}

inline const char *EnumNameMsgStatus(MsgStatus e) { return EnumNamesMsgStatus()[static_cast<int>(e)]; }

enum PlayerState {
  PlayerState_PlayerState_Idling = 0,
  PlayerState_PlayerState_Joining = 1,
  PlayerState_PlayerState_Dead = 2,
  PlayerState_PlayerState_Running = 3,
  PlayerState_PlayerState_Jumping = 4,
  PlayerState_PlayerState_OnMenu = 5,
  PlayerState_PlayerState_IsSpawned = 6,
  PlayerState_PlayerState_Spectating = 7,
  PlayerState_PlayerState_Attack_1 = 8,
  PlayerState_PlayerState_Attack_2 = 9,
  PlayerState_PlayerState_Attack_3 = 10,
  PlayerState_PlayerState_Attack_4 = 11,
  PlayerState_PlayerState_Attack_5 = 12,
  PlayerState_PlayerState_Attack_6 = 13,
  PlayerState_PlayerState_Hitted_1 = 14,
  PlayerState_PlayerState_Hitted_2 = 15,
  PlayerState_PlayerState_Hitted_3 = 16,
  PlayerState_PlayerState_Hitted_4 = 17,
  PlayerState_PlayerState_Hitted_5 = 18,
  PlayerState_PlayerState_Hitted_6 = 19,
  PlayerState_PlayerState_Count = 20
};

inline const char **EnumNamesPlayerState() {
  static const char *names[] = { "PlayerState_Idling", "PlayerState_Joining", "PlayerState_Dead", "PlayerState_Running", "PlayerState_Jumping", "PlayerState_OnMenu", "PlayerState_IsSpawned", "PlayerState_Spectating", "PlayerState_Attack_1", "PlayerState_Attack_2", "PlayerState_Attack_3", "PlayerState_Attack_4", "PlayerState_Attack_5", "PlayerState_Attack_6", "PlayerState_Hitted_1", "PlayerState_Hitted_2", "PlayerState_Hitted_3", "PlayerState_Hitted_4", "PlayerState_Hitted_5", "PlayerState_Hitted_6", "PlayerState_Count", nullptr };
  return names;
}

inline const char *EnumNamePlayerState(PlayerState e) { return EnumNamesPlayerState()[static_cast<int>(e)]; }

enum AnimationParameterId {
  AnimationParameterId_AnimationState = 0,
  AnimationParameterId_LookDirectionHorizontal = 1,
  AnimationParameterId_LookDirectionVertical = 2,
  AnimationParameterId_JumpPost = 3
};

inline const char **EnumNamesAnimationParameterId() {
  static const char *names[] = { "AnimationState", "LookDirectionHorizontal", "LookDirectionVertical", "JumpPost", nullptr };
  return names;
}

inline const char *EnumNameAnimationParameterId(AnimationParameterId e) { return EnumNamesAnimationParameterId()[static_cast<int>(e)]; }

enum AnimationTriggerId {
  AnimationTriggerId_attack_end = 1,
  AnimationTriggerId_attack_start = 2
};

inline const char **EnumNamesAnimationTriggerId() {
  static const char *names[] = { "attack_end", "attack_start", nullptr };
  return names;
}

inline const char *EnumNameAnimationTriggerId(AnimationTriggerId e) { return EnumNamesAnimationTriggerId()[static_cast<int>(e) - static_cast<int>(AnimationTriggerId_attack_end)]; }

enum AnimPortId {
  AnimPortId_Speed = 0,
  AnimPortId_Synch = 1,
  AnimPortId_In = 2,
  AnimPortId_select = 3,
  AnimPortId_timeIn = 4,
  AnimPortId_timeOut = 5,
  AnimPortId_in0 = 6,
  AnimPortId_in1 = 7,
  AnimPortId_weight = 8,
  AnimPortId_value = 9,
  AnimPortId_smoothTime = 10,
  AnimPortId_horizontalAmount = 11,
  AnimPortId_verticalAmount = 12,
  AnimPortId_left = 13,
  AnimPortId_right = 14,
  AnimPortId_up = 15,
  AnimPortId_down = 16,
  AnimPortId_min = 17,
  AnimPortId_max = 18,
  AnimPortId_minIn = 20,
  AnimPortId_maxIn = 21,
  AnimPortId_minOut = 22,
  AnimPortId_maxOut = 23
};

inline const char **EnumNamesAnimPortId() {
  static const char *names[] = { "Speed", "Synch", "In", "select", "timeIn", "timeOut", "in0", "in1", "weight", "value", "smoothTime", "horizontalAmount", "verticalAmount", "left", "right", "up", "down", "min", "max", "", "minIn", "maxIn", "minOut", "maxOut", nullptr };
  return names;
}

inline const char *EnumNameAnimPortId(AnimPortId e) { return EnumNamesAnimPortId()[static_cast<int>(e)]; }

enum AnimationId {
  AnimationId_SliceHorizontal = 0,
  AnimationId_SliceVertical = 1,
  AnimationId_JumpStart = 2,
  AnimationId_JumpLoop = 3,
  AnimationId_RunTop = 4,
  AnimationId_JumpEnd = 5,
  AnimationId_RunBase = 6,
  AnimationId_IdleTop = 7,
  AnimationId_IdleBase = 8,
  AnimationId_HandsRelaxed = 9,
  AnimationId_HandsClosed = 10,
  AnimationId_Dance = 11,
  AnimationId_DrawSwords = 12
};

inline const char **EnumNamesAnimationId() {
  static const char *names[] = { "SliceHorizontal", "SliceVertical", "JumpStart", "JumpLoop", "RunTop", "JumpEnd", "RunBase", "IdleTop", "IdleBase", "HandsRelaxed", "HandsClosed", "Dance", "DrawSwords", nullptr };
  return names;
}

inline const char *EnumNameAnimationId(AnimationId e) { return EnumNamesAnimationId()[static_cast<int>(e)]; }

enum ComponentType {
  ComponentType_CT_None = 0,
  ComponentType_CT_NetId = 1,
  ComponentType_CT_Body = 2,
  ComponentType_CT_Renderable = 3,
  ComponentType_CT_Controller = 4,
  ComponentType_CT_Player = 5,
  ComponentType_CT_Spell = 6,
  ComponentType_CT_Static = 7
};

inline const char **EnumNamesComponentType() {
  static const char *names[] = { "CT_None", "CT_NetId", "CT_Body", "CT_Renderable", "CT_Controller", "CT_Player", "CT_Spell", "CT_Static", nullptr };
  return names;
}

inline const char *EnumNameComponentType(ComponentType e) { return EnumNamesComponentType()[static_cast<int>(e)]; }

enum UComponent {
  UComponent_NONE = 0,
  UComponent_CharacterComponent = 1,
  UComponent_AIComponent = 2,
  UComponent_SpawnPointComponent = 3,
  UComponent_SpawnComponent = 4,
  UComponent_AnimationComponent = 5,
  UComponent_BodyComponent = 6,
  UComponent_PlayerComponent = 7,
  UComponent_SpellComponent = 8,
  UComponent_RenderableComponent = 9,
  UComponent_StaticComponent = 10,
  UComponent_Camera = 11,
  UComponent_Light = 12,
  UComponent_SoundListener = 13,
  UComponent_PhysicsComponent = 14,
  UComponent_SoundComponent = 15
};

inline const char **EnumNamesUComponent() {
  static const char *names[] = { "NONE", "CharacterComponent", "AIComponent", "SpawnPointComponent", "SpawnComponent", "AnimationComponent", "BodyComponent", "PlayerComponent", "SpellComponent", "RenderableComponent", "StaticComponent", "Camera", "Light", "SoundListener", "PhysicsComponent", "SoundComponent", nullptr };
  return names;
}

inline const char *EnumNameUComponent(UComponent e) { return EnumNamesUComponent()[static_cast<int>(e)]; }

inline bool VerifyUComponent(flatbuffers::Verifier &verifier, const void *union_obj, UComponent type);

enum Data {
  Data_NONE = 0,
  Data_Chatmessage = 1,
  Data_Scene = 2,
  Data_Login = 3,
  Data_ReturnStatus = 4,
  Data_InputEvent = 5,
  Data_Entity = 6,
  Data_GameState = 7
};

inline const char **EnumNamesData() {
  static const char *names[] = { "NONE", "Chatmessage", "Scene", "Login", "ReturnStatus", "InputEvent", "Entity", "GameState", nullptr };
  return names;
}

inline const char *EnumNameData(Data e) { return EnumNamesData()[static_cast<int>(e)]; }

inline bool VerifyData(flatbuffers::Verifier &verifier, const void *union_obj, Data type);

struct SpellComponent FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           verifier.EndTable();
  }
};

struct SpellComponentBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  SpellComponentBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  SpellComponentBuilder &operator=(const SpellComponentBuilder &);
  flatbuffers::Offset<SpellComponent> Finish() {
    auto o = flatbuffers::Offset<SpellComponent>(fbb_.EndTable(start_, 0));
    return o;
  }
};

inline flatbuffers::Offset<SpellComponent> CreateSpellComponent(flatbuffers::FlatBufferBuilder &_fbb) {
  SpellComponentBuilder builder_(_fbb);
  return builder_.Finish();
}

struct StaticComponent FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           verifier.EndTable();
  }
};

struct StaticComponentBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  StaticComponentBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  StaticComponentBuilder &operator=(const StaticComponentBuilder &);
  flatbuffers::Offset<StaticComponent> Finish() {
    auto o = flatbuffers::Offset<StaticComponent>(fbb_.EndTable(start_, 0));
    return o;
  }
};

inline flatbuffers::Offset<StaticComponent> CreateStaticComponent(flatbuffers::FlatBufferBuilder &_fbb) {
  StaticComponentBuilder builder_(_fbb);
  return builder_.Finish();
}

struct GameState FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const XFBType::Scene *scene() const { return GetPointer<const XFBType::Scene *>(4); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* scene */) &&
           verifier.VerifyTable(scene()) &&
           verifier.EndTable();
  }
};

struct GameStateBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_scene(flatbuffers::Offset<XFBType::Scene> scene) { fbb_.AddOffset(4, scene); }
  GameStateBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  GameStateBuilder &operator=(const GameStateBuilder &);
  flatbuffers::Offset<GameState> Finish() {
    auto o = flatbuffers::Offset<GameState>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<GameState> CreateGameState(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<XFBType::Scene> scene = 0) {
  GameStateBuilder builder_(_fbb);
  builder_.add_scene(scene);
  return builder_.Finish();
}

struct CharacterComponent FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           verifier.EndTable();
  }
};

struct CharacterComponentBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  CharacterComponentBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  CharacterComponentBuilder &operator=(const CharacterComponentBuilder &);
  flatbuffers::Offset<CharacterComponent> Finish() {
    auto o = flatbuffers::Offset<CharacterComponent>(fbb_.EndTable(start_, 0));
    return o;
  }
};

inline flatbuffers::Offset<CharacterComponent> CreateCharacterComponent(flatbuffers::FlatBufferBuilder &_fbb) {
  CharacterComponentBuilder builder_(_fbb);
  return builder_.Finish();
}

struct AIComponent FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const flatbuffers::String *script() const { return GetPointer<const flatbuffers::String *>(4); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* script */) &&
           verifier.Verify(script()) &&
           verifier.EndTable();
  }
};

struct AIComponentBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_script(flatbuffers::Offset<flatbuffers::String> script) { fbb_.AddOffset(4, script); }
  AIComponentBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  AIComponentBuilder &operator=(const AIComponentBuilder &);
  flatbuffers::Offset<AIComponent> Finish() {
    auto o = flatbuffers::Offset<AIComponent>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<AIComponent> CreateAIComponent(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> script = 0) {
  AIComponentBuilder builder_(_fbb);
  builder_.add_script(script);
  return builder_.Finish();
}

struct Chatmessage FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  uint16_t group() const { return GetField<uint16_t>(4, 0); }
  const flatbuffers::String *text() const { return GetPointer<const flatbuffers::String *>(6); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, 4 /* group */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* text */) &&
           verifier.Verify(text()) &&
           verifier.EndTable();
  }
};

struct ChatmessageBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_group(uint16_t group) { fbb_.AddElement<uint16_t>(4, group, 0); }
  void add_text(flatbuffers::Offset<flatbuffers::String> text) { fbb_.AddOffset(6, text); }
  ChatmessageBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ChatmessageBuilder &operator=(const ChatmessageBuilder &);
  flatbuffers::Offset<Chatmessage> Finish() {
    auto o = flatbuffers::Offset<Chatmessage>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<Chatmessage> CreateChatmessage(flatbuffers::FlatBufferBuilder &_fbb,
   uint16_t group = 0,
   flatbuffers::Offset<flatbuffers::String> text = 0) {
  ChatmessageBuilder builder_(_fbb);
  builder_.add_text(text);
  builder_.add_group(group);
  return builder_.Finish();
}

struct Login FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const flatbuffers::String *identity() const { return GetPointer<const flatbuffers::String *>(4); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* identity */) &&
           verifier.Verify(identity()) &&
           verifier.EndTable();
  }
};

struct LoginBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_identity(flatbuffers::Offset<flatbuffers::String> identity) { fbb_.AddOffset(4, identity); }
  LoginBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  LoginBuilder &operator=(const LoginBuilder &);
  flatbuffers::Offset<Login> Finish() {
    auto o = flatbuffers::Offset<Login>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<Login> CreateLogin(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> identity = 0) {
  LoginBuilder builder_(_fbb);
  builder_.add_identity(identity);
  return builder_.Finish();
}

struct ReturnStatus FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  MsgStatus status() const { return static_cast<MsgStatus>(GetField<uint16_t>(4, 0)); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, 4 /* status */) &&
           verifier.EndTable();
  }
};

struct ReturnStatusBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_status(MsgStatus status) { fbb_.AddElement<uint16_t>(4, static_cast<uint16_t>(status), 0); }
  ReturnStatusBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ReturnStatusBuilder &operator=(const ReturnStatusBuilder &);
  flatbuffers::Offset<ReturnStatus> Finish() {
    auto o = flatbuffers::Offset<ReturnStatus>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<ReturnStatus> CreateReturnStatus(flatbuffers::FlatBufferBuilder &_fbb,
   MsgStatus status = MsgStatus_S_Unknown) {
  ReturnStatusBuilder builder_(_fbb);
  builder_.add_status(status);
  return builder_.Finish();
}

struct PlayerComponent FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  PlayerState playerState() const { return static_cast<PlayerState>(GetField<uint16_t>(4, 0)); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, 4 /* playerState */) &&
           verifier.EndTable();
  }
};

struct PlayerComponentBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_playerState(PlayerState playerState) { fbb_.AddElement<uint16_t>(4, static_cast<uint16_t>(playerState), 0); }
  PlayerComponentBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  PlayerComponentBuilder &operator=(const PlayerComponentBuilder &);
  flatbuffers::Offset<PlayerComponent> Finish() {
    auto o = flatbuffers::Offset<PlayerComponent>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<PlayerComponent> CreatePlayerComponent(flatbuffers::FlatBufferBuilder &_fbb,
   PlayerState playerState = PlayerState_PlayerState_Idling) {
  PlayerComponentBuilder builder_(_fbb);
  builder_.add_playerState(playerState);
  return builder_.Finish();
}

struct Entity FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  uint32_t entityID() const { return GetField<uint32_t>(4, 0); }
  uint8_t deleteEntity() const { return GetField<uint8_t>(6, 0); }
  const flatbuffers::Vector<flatbuffers::Offset<Component>> *components() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Component>> *>(8); }
  const flatbuffers::Vector<flatbuffers::Offset<Component>> *deleteComponents() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Component>> *>(10); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, 4 /* entityID */) &&
           VerifyField<uint8_t>(verifier, 6 /* deleteEntity */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 8 /* components */) &&
           verifier.Verify(components()) &&
           verifier.VerifyVectorOfTables(components()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 10 /* deleteComponents */) &&
           verifier.Verify(deleteComponents()) &&
           verifier.VerifyVectorOfTables(deleteComponents()) &&
           verifier.EndTable();
  }
};

struct EntityBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_entityID(uint32_t entityID) { fbb_.AddElement<uint32_t>(4, entityID, 0); }
  void add_deleteEntity(uint8_t deleteEntity) { fbb_.AddElement<uint8_t>(6, deleteEntity, 0); }
  void add_components(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Component>>> components) { fbb_.AddOffset(8, components); }
  void add_deleteComponents(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Component>>> deleteComponents) { fbb_.AddOffset(10, deleteComponents); }
  EntityBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  EntityBuilder &operator=(const EntityBuilder &);
  flatbuffers::Offset<Entity> Finish() {
    auto o = flatbuffers::Offset<Entity>(fbb_.EndTable(start_, 4));
    return o;
  }
};

inline flatbuffers::Offset<Entity> CreateEntity(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t entityID = 0,
   uint8_t deleteEntity = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Component>>> components = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Component>>> deleteComponents = 0) {
  EntityBuilder builder_(_fbb);
  builder_.add_deleteComponents(deleteComponents);
  builder_.add_components(components);
  builder_.add_entityID(entityID);
  builder_.add_deleteEntity(deleteEntity);
  return builder_.Finish();
}

struct InputEvent FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  ControllerSettings::ActionType actionType() const { return static_cast<ControllerSettings::ActionType>(GetField<uint16_t>(4, 0)); }
  const XFBType::Vec3f *actionData() const { return GetStruct<const XFBType::Vec3f *>(6); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, 4 /* actionType */) &&
           VerifyField<XFBType::Vec3f>(verifier, 6 /* actionData */) &&
           verifier.EndTable();
  }
};

struct InputEventBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_actionType(ControllerSettings::ActionType actionType) { fbb_.AddElement<uint16_t>(4, static_cast<uint16_t>(actionType), 0); }
  void add_actionData(const XFBType::Vec3f *actionData) { fbb_.AddStruct(6, actionData); }
  InputEventBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  InputEventBuilder &operator=(const InputEventBuilder &);
  flatbuffers::Offset<InputEvent> Finish() {
    auto o = flatbuffers::Offset<InputEvent>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<InputEvent> CreateInputEvent(flatbuffers::FlatBufferBuilder &_fbb,
   ControllerSettings::ActionType actionType = ControllerSettings::ActionType_None,
   const XFBType::Vec3f *actionData = 0) {
  InputEventBuilder builder_(_fbb);
  builder_.add_actionData(actionData);
  builder_.add_actionType(actionType);
  return builder_.Finish();
}

struct Component FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  UComponent comp_type() const { return static_cast<UComponent>(GetField<uint8_t>(4, 0)); }
  const void *comp() const { return GetPointer<const void *>(6); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, 4 /* comp_type */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* comp */) &&
           VerifyUComponent(verifier, comp(), comp_type()) &&
           verifier.EndTable();
  }
};

struct ComponentBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_comp_type(UComponent comp_type) { fbb_.AddElement<uint8_t>(4, static_cast<uint8_t>(comp_type), 0); }
  void add_comp(flatbuffers::Offset<void> comp) { fbb_.AddOffset(6, comp); }
  ComponentBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  ComponentBuilder &operator=(const ComponentBuilder &);
  flatbuffers::Offset<Component> Finish() {
    auto o = flatbuffers::Offset<Component>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<Component> CreateComponent(flatbuffers::FlatBufferBuilder &_fbb,
   UComponent comp_type = UComponent_NONE,
   flatbuffers::Offset<void> comp = 0) {
  ComponentBuilder builder_(_fbb);
  builder_.add_comp(comp);
  builder_.add_comp_type(comp_type);
  return builder_.Finish();
}

struct MessageRoot FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  uint32_t netid() const { return GetField<uint32_t>(4, 0); }
  uint32_t scene() const { return GetField<uint32_t>(6, 0); }
  Data data_type() const { return static_cast<Data>(GetField<uint8_t>(8, 0)); }
  const void *data() const { return GetPointer<const void *>(10); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, 4 /* netid */) &&
           VerifyField<uint32_t>(verifier, 6 /* scene */) &&
           VerifyField<uint8_t>(verifier, 8 /* data_type */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 10 /* data */) &&
           VerifyData(verifier, data(), data_type()) &&
           verifier.EndTable();
  }
};

struct MessageRootBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_netid(uint32_t netid) { fbb_.AddElement<uint32_t>(4, netid, 0); }
  void add_scene(uint32_t scene) { fbb_.AddElement<uint32_t>(6, scene, 0); }
  void add_data_type(Data data_type) { fbb_.AddElement<uint8_t>(8, static_cast<uint8_t>(data_type), 0); }
  void add_data(flatbuffers::Offset<void> data) { fbb_.AddOffset(10, data); }
  MessageRootBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  MessageRootBuilder &operator=(const MessageRootBuilder &);
  flatbuffers::Offset<MessageRoot> Finish() {
    auto o = flatbuffers::Offset<MessageRoot>(fbb_.EndTable(start_, 4));
    return o;
  }
};

inline flatbuffers::Offset<MessageRoot> CreateMessageRoot(flatbuffers::FlatBufferBuilder &_fbb,
   uint32_t netid = 0,
   uint32_t scene = 0,
   Data data_type = Data_NONE,
   flatbuffers::Offset<void> data = 0) {
  MessageRootBuilder builder_(_fbb);
  builder_.add_data(data);
  builder_.add_scene(scene);
  builder_.add_netid(netid);
  builder_.add_data_type(data_type);
  return builder_.Finish();
}

inline bool VerifyUComponent(flatbuffers::Verifier &verifier, const void *union_obj, UComponent type) {
  switch (type) {
    case UComponent_NONE: return true;
    case UComponent_CharacterComponent: return verifier.VerifyTable(reinterpret_cast<const CharacterComponent *>(union_obj));
    case UComponent_AIComponent: return verifier.VerifyTable(reinterpret_cast<const AIComponent *>(union_obj));
    case UComponent_SpawnPointComponent: return verifier.VerifyTable(reinterpret_cast<const XFBType::SpawnPointComponent *>(union_obj));
    case UComponent_SpawnComponent: return verifier.VerifyTable(reinterpret_cast<const XFBType::SpawnComponent *>(union_obj));
    case UComponent_AnimationComponent: return verifier.VerifyTable(reinterpret_cast<const XFBType::AnimationComponent *>(union_obj));
    case UComponent_BodyComponent: return verifier.VerifyTable(reinterpret_cast<const XFBType::BodyComponent *>(union_obj));
    case UComponent_PlayerComponent: return verifier.VerifyTable(reinterpret_cast<const PlayerComponent *>(union_obj));
    case UComponent_SpellComponent: return verifier.VerifyTable(reinterpret_cast<const SpellComponent *>(union_obj));
    case UComponent_RenderableComponent: return verifier.VerifyTable(reinterpret_cast<const XFBType::RenderableComponent *>(union_obj));
    case UComponent_StaticComponent: return verifier.VerifyTable(reinterpret_cast<const StaticComponent *>(union_obj));
    case UComponent_Camera: return verifier.VerifyTable(reinterpret_cast<const XFBType::Camera *>(union_obj));
    case UComponent_Light: return verifier.VerifyTable(reinterpret_cast<const XFBType::Light *>(union_obj));
    case UComponent_SoundListener: return verifier.VerifyTable(reinterpret_cast<const XFBType::SoundListener *>(union_obj));
    case UComponent_PhysicsComponent: return verifier.VerifyTable(reinterpret_cast<const XFBType::PhysicsComponent *>(union_obj));
    case UComponent_SoundComponent: return verifier.VerifyTable(reinterpret_cast<const XFBType::SoundComponent *>(union_obj));
    default: return false;
  }
}

inline bool VerifyData(flatbuffers::Verifier &verifier, const void *union_obj, Data type) {
  switch (type) {
    case Data_NONE: return true;
    case Data_Chatmessage: return verifier.VerifyTable(reinterpret_cast<const Chatmessage *>(union_obj));
    case Data_Scene: return verifier.VerifyTable(reinterpret_cast<const XFBType::Scene *>(union_obj));
    case Data_Login: return verifier.VerifyTable(reinterpret_cast<const Login *>(union_obj));
    case Data_ReturnStatus: return verifier.VerifyTable(reinterpret_cast<const ReturnStatus *>(union_obj));
    case Data_InputEvent: return verifier.VerifyTable(reinterpret_cast<const InputEvent *>(union_obj));
    case Data_Entity: return verifier.VerifyTable(reinterpret_cast<const Entity *>(union_obj));
    case Data_GameState: return verifier.VerifyTable(reinterpret_cast<const GameState *>(union_obj));
    default: return false;
  }
}

inline const NetMsg::MessageRoot *GetMessageRoot(const void *buf) { return flatbuffers::GetRoot<NetMsg::MessageRoot>(buf); }

inline bool VerifyMessageRootBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<NetMsg::MessageRoot>(); }

inline void FinishMessageRootBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<NetMsg::MessageRoot> root) { fbb.Finish(root); }

}  // namespace NetMsg

#endif  // FLATBUFFERS_GENERATED_NETMSG_NETMSG_H_
