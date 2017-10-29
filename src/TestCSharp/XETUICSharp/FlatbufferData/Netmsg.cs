// automatically generated, do not modify

namespace NetMsg
{
    using ControllerSettings;
    using XFBType;

    public enum MsgStatus : ushort
{
 S_Unknown = 0,
 S_LoginSuccess = 1,
 S_AlreadyLoggedIn = 2,
 S_AccessDenied = 3,
};

public enum ComponentType : ushort
{
 CT_None = 0,
 CT_NetId = 1,
 CT_Body = 2,
 CT_Controller = 3,
 CT_Player = 4,
 CT_Spell = 5,
 CT_Static = 6,
};

public enum EnityCmd : ushort
{
 EC_None = 0,
 EC_RemoveComponent = 1,
 EC_DeleteEntity = 2,
};

public enum Data : byte
{
 NONE = 0,
 RenderableComponent = 1,
 Chatmessage = 2,
 CharacterComponent = 3,
 SpellComponent = 4,
 Node = 5,
 Camera = 6,
 Light = 7,
 SoundListener = 8,
 Scene = 9,
 Login = 10,
 ReturnStatus = 11,
 InputEvent = 12,
 EntityCmdMsg = 13,
 StaticComponent = 14,
};


}
