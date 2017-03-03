// automatically generated, do not modify

namespace FBSettings
{

using FlatBuffers;

public enum FSAA : ushort
{
 none = 0,
 x8 = 8,
 x16 = 16,
 x32 = 32,
};

public sealed class Graphics : Table {
  public static Graphics GetRootAsGraphics(ByteBuffer _bb) { return GetRootAsGraphics(_bb, new Graphics()); }
  public static Graphics GetRootAsGraphics(ByteBuffer _bb, Graphics obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Graphics __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public bool Fullscreen { get { int o = __offset(4); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public FSAA Fsaa { get { int o = __offset(6); return o != 0 ? (FSAA)bb.GetUshort(o + bb_pos) : FSAA.none; } }

  public static Offset<Graphics> CreateGraphics(FlatBufferBuilder builder,
      bool fullscreen = false,
      FSAA fsaa = FSAA.none) {
    builder.StartObject(2);
    Graphics.AddFsaa(builder, fsaa);
    Graphics.AddFullscreen(builder, fullscreen);
    return Graphics.EndGraphics(builder);
  }

  public static void StartGraphics(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddFullscreen(FlatBufferBuilder builder, bool fullscreen) { builder.AddBool(0, fullscreen, false); }
  public static void AddFsaa(FlatBufferBuilder builder, FSAA fsaa) { builder.AddUshort(1, (ushort)fsaa, 0); }
  public static Offset<Graphics> EndGraphics(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Graphics>(o);
  }
};

///resource folders
public sealed class Settings : Table {
  public static Settings GetRootAsSettings(ByteBuffer _bb) { return GetRootAsSettings(_bb, new Settings()); }
  public static Settings GetRootAsSettings(ByteBuffer _bb, Settings obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Settings __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Graphics Graphics { get { return GetGraphics(new Graphics()); } }
  public Graphics GetGraphics(Graphics obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public string WindowTitle { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Settings> CreateSettings(FlatBufferBuilder builder,
      Offset<Graphics> graphicsOffset = default(Offset<Graphics>),
      StringOffset windowTitleOffset = default(StringOffset)) {
    builder.StartObject(2);
    Settings.AddWindowTitle(builder, windowTitleOffset);
    Settings.AddGraphics(builder, graphicsOffset);
    return Settings.EndSettings(builder);
  }

  public static void StartSettings(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddGraphics(FlatBufferBuilder builder, Offset<Graphics> graphicsOffset) { builder.AddOffset(0, graphicsOffset.Value, 0); }
  public static void AddWindowTitle(FlatBufferBuilder builder, StringOffset windowTitleOffset) { builder.AddOffset(1, windowTitleOffset.Value, 0); }
  public static Offset<Settings> EndSettings(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Settings>(o);
  }
  public static void FinishSettingsBuffer(FlatBufferBuilder builder, Offset<Settings> offset) { builder.Finish(offset.Value); }
};


}
