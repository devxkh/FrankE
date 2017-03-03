// automatically generated, do not modify

namespace XFB_UI
{

using FlatBuffers;

public enum ElementState : sbyte
{
 ES_NORMAL = 0,
 ES_ACTIVE = 1,
 ES_PRELIGHT = 2,
 ES_SELECTED = 3,
 ES_INSENSITIVE = 4,
};

public enum StyleType : sbyte
{
 ST_DEFAULT = 0,
 ST_WINDOW = 1,
 ST_MENU = 2,
 ST_MENUITEM = 3,
 ST_NAVIGATION = 4,
 ST_NAVITEM = 5,
 ST_LISTBOX = 6,
 ST_COMBOBOX = 7,
 ST_LABEL = 8,
 ST_TOGGLEBUTTON = 9,
 ST_BUTTON = 10,
 ST_PANEL3D = 11,
 ST_CONSOLE = 12,
};

public enum GradientType : sbyte
{
 GT_NorthSouth = 0,
 GT_WestEast = 1,
 GT_Diagonal = 2,
};

public enum ListItemType : byte
{
 NONE = 0,
 Label = 1,
 Button = 2,
 Image = 3,
};

public enum MenuType : sbyte
{
 MT_LIST = 0,
 MT_SINGLE = 1,
 MT_MULTI = 2,
};

public enum Orientation : sbyte
{
 horizontal = 0,
 vertical = 1,
};

public enum UUIElement : byte
{
 NONE = 0,
 Label = 1,
 Menu = 2,
 Navigation = 3,
 Console = 4,
 Element = 5,
 Button = 6,
 ToggleButton = 7,
 Image = 8,
 ProgressBar = 9,
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

public sealed class Vec2f : Struct {
  public Vec2f __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float X { get { return bb.GetFloat(bb_pos + 0); } }
  public float Y { get { return bb.GetFloat(bb_pos + 4); } }

  public static Offset<Vec2f> CreateVec2f(FlatBufferBuilder builder, float X, float Y) {
    builder.Prep(4, 8);
    builder.PutFloat(Y);
    builder.PutFloat(X);
    return new Offset<Vec2f>(builder.Offset);
  }
};

public sealed class Align : Struct {
  public Align __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float Vertical { get { return bb.GetFloat(bb_pos + 0); } }
  public float Horizontal { get { return bb.GetFloat(bb_pos + 4); } }

  public static Offset<Align> CreateAlign(FlatBufferBuilder builder, float Vertical, float Horizontal) {
    builder.Prep(4, 8);
    builder.PutFloat(Horizontal);
    builder.PutFloat(Vertical);
    return new Offset<Align>(builder.Offset);
  }
};

public sealed class Scale : Struct {
  public Scale __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float Vertical { get { return bb.GetFloat(bb_pos + 0); } }
  public float Horizontal { get { return bb.GetFloat(bb_pos + 4); } }

  public static Offset<Scale> CreateScale(FlatBufferBuilder builder, float Vertical, float Horizontal) {
    builder.Prep(4, 8);
    builder.PutFloat(Horizontal);
    builder.PutFloat(Vertical);
    return new Offset<Scale>(builder.Offset);
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

public sealed class ResourceLocation : Table {
  public static ResourceLocation GetRootAsResourceLocation(ByteBuffer _bb) { return GetRootAsResourceLocation(_bb, new ResourceLocation()); }
  public static ResourceLocation GetRootAsResourceLocation(ByteBuffer _bb, ResourceLocation obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public ResourceLocation __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public string LocType { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }
  public string ResGroup { get { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; } }
  public bool Recursive { get { int o = __offset(10); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public bool ReadOnly { get { int o = __offset(12); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }

  public static Offset<ResourceLocation> CreateResourceLocation(FlatBufferBuilder builder,
      StringOffset nameOffset = default(StringOffset),
      StringOffset locTypeOffset = default(StringOffset),
      StringOffset resGroupOffset = default(StringOffset),
      bool recursive = false,
      bool readOnly = false) {
    builder.StartObject(5);
    ResourceLocation.AddResGroup(builder, resGroupOffset);
    ResourceLocation.AddLocType(builder, locTypeOffset);
    ResourceLocation.AddName(builder, nameOffset);
    ResourceLocation.AddReadOnly(builder, readOnly);
    ResourceLocation.AddRecursive(builder, recursive);
    return ResourceLocation.EndResourceLocation(builder);
  }

  public static void StartResourceLocation(FlatBufferBuilder builder) { builder.StartObject(5); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(0, nameOffset.Value, 0); }
  public static void AddLocType(FlatBufferBuilder builder, StringOffset locTypeOffset) { builder.AddOffset(1, locTypeOffset.Value, 0); }
  public static void AddResGroup(FlatBufferBuilder builder, StringOffset resGroupOffset) { builder.AddOffset(2, resGroupOffset.Value, 0); }
  public static void AddRecursive(FlatBufferBuilder builder, bool recursive) { builder.AddBool(3, recursive, false); }
  public static void AddReadOnly(FlatBufferBuilder builder, bool readOnly) { builder.AddBool(4, readOnly, false); }
  public static Offset<ResourceLocation> EndResourceLocation(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ResourceLocation>(o);
  }
};

public sealed class GradientParam : Table {
  public static GradientParam GetRootAsGradientParam(ByteBuffer _bb) { return GetRootAsGradientParam(_bb, new GradientParam()); }
  public static GradientParam GetRootAsGradientParam(ByteBuffer _bb, GradientParam obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public GradientParam __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Colour Color { get { return GetColor(new Colour()); } }
  public Colour GetColor(Colour obj) { int o = __offset(4); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public ushort Offset { get { int o = __offset(6); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static void StartGradientParam(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddColor(FlatBufferBuilder builder, Offset<Colour> colorOffset) { builder.AddStruct(0, colorOffset.Value, 0); }
  public static void AddOffset(FlatBufferBuilder builder, ushort offset) { builder.AddUshort(1, offset, 0); }
  public static Offset<GradientParam> EndGradientParam(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<GradientParam>(o);
  }
};

public sealed class Gradient : Table {
  public static Gradient GetRootAsGradient(ByteBuffer _bb) { return GetRootAsGradient(_bb, new Gradient()); }
  public static Gradient GetRootAsGradient(ByteBuffer _bb, Gradient obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Gradient __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public GradientType Type { get { int o = __offset(4); return o != 0 ? (GradientType)bb.GetSbyte(o + bb_pos) : GradientType.GT_NorthSouth; } }
  public GradientParam Sart { get { return GetSart(new GradientParam()); } }
  public GradientParam GetSart(GradientParam obj) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public GradientParam Stop { get { return GetStop(new GradientParam()); } }
  public GradientParam GetStop(GradientParam obj) { int o = __offset(8); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<Gradient> CreateGradient(FlatBufferBuilder builder,
      GradientType type = GradientType.GT_NorthSouth,
      Offset<GradientParam> sartOffset = default(Offset<GradientParam>),
      Offset<GradientParam> stopOffset = default(Offset<GradientParam>)) {
    builder.StartObject(3);
    Gradient.AddStop(builder, stopOffset);
    Gradient.AddSart(builder, sartOffset);
    Gradient.AddType(builder, type);
    return Gradient.EndGradient(builder);
  }

  public static void StartGradient(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddType(FlatBufferBuilder builder, GradientType type) { builder.AddSbyte(0, (sbyte)type, 0); }
  public static void AddSart(FlatBufferBuilder builder, Offset<GradientParam> sartOffset) { builder.AddOffset(1, sartOffset.Value, 0); }
  public static void AddStop(FlatBufferBuilder builder, Offset<GradientParam> stopOffset) { builder.AddOffset(2, stopOffset.Value, 0); }
  public static Offset<Gradient> EndGradient(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Gradient>(o);
  }
};

public sealed class Padding : Table {
  public static Padding GetRootAsPadding(ByteBuffer _bb) { return GetRootAsPadding(_bb, new Padding()); }
  public static Padding GetRootAsPadding(ByteBuffer _bb, Padding obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Padding __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort L { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort T { get { int o = __offset(6); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort R { get { int o = __offset(8); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort B { get { int o = __offset(10); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static Offset<Padding> CreatePadding(FlatBufferBuilder builder,
      ushort l = 0,
      ushort t = 0,
      ushort r = 0,
      ushort b = 0) {
    builder.StartObject(4);
    Padding.AddB(builder, b);
    Padding.AddR(builder, r);
    Padding.AddT(builder, t);
    Padding.AddL(builder, l);
    return Padding.EndPadding(builder);
  }

  public static void StartPadding(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddL(FlatBufferBuilder builder, ushort l) { builder.AddUshort(0, l, 0); }
  public static void AddT(FlatBufferBuilder builder, ushort t) { builder.AddUshort(1, t, 0); }
  public static void AddR(FlatBufferBuilder builder, ushort r) { builder.AddUshort(2, r, 0); }
  public static void AddB(FlatBufferBuilder builder, ushort b) { builder.AddUshort(3, b, 0); }
  public static Offset<Padding> EndPadding(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Padding>(o);
  }
};

public sealed class Margin : Table {
  public static Margin GetRootAsMargin(ByteBuffer _bb) { return GetRootAsMargin(_bb, new Margin()); }
  public static Margin GetRootAsMargin(ByteBuffer _bb, Margin obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Margin __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort L { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort T { get { int o = __offset(6); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort R { get { int o = __offset(8); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort B { get { int o = __offset(10); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static Offset<Margin> CreateMargin(FlatBufferBuilder builder,
      ushort l = 0,
      ushort t = 0,
      ushort r = 0,
      ushort b = 0) {
    builder.StartObject(4);
    Margin.AddB(builder, b);
    Margin.AddR(builder, r);
    Margin.AddT(builder, t);
    Margin.AddL(builder, l);
    return Margin.EndMargin(builder);
  }

  public static void StartMargin(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddL(FlatBufferBuilder builder, ushort l) { builder.AddUshort(0, l, 0); }
  public static void AddT(FlatBufferBuilder builder, ushort t) { builder.AddUshort(1, t, 0); }
  public static void AddR(FlatBufferBuilder builder, ushort r) { builder.AddUshort(2, r, 0); }
  public static void AddB(FlatBufferBuilder builder, ushort b) { builder.AddUshort(3, b, 0); }
  public static Offset<Margin> EndMargin(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Margin>(o);
  }
};

public sealed class Thickness : Table {
  public static Thickness GetRootAsThickness(ByteBuffer _bb) { return GetRootAsThickness(_bb, new Thickness()); }
  public static Thickness GetRootAsThickness(ByteBuffer _bb, Thickness obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Thickness __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort L { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort T { get { int o = __offset(6); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort R { get { int o = __offset(8); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public ushort B { get { int o = __offset(10); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static Offset<Thickness> CreateThickness(FlatBufferBuilder builder,
      ushort l = 0,
      ushort t = 0,
      ushort r = 0,
      ushort b = 0) {
    builder.StartObject(4);
    Thickness.AddB(builder, b);
    Thickness.AddR(builder, r);
    Thickness.AddT(builder, t);
    Thickness.AddL(builder, l);
    return Thickness.EndThickness(builder);
  }

  public static void StartThickness(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddL(FlatBufferBuilder builder, ushort l) { builder.AddUshort(0, l, 0); }
  public static void AddT(FlatBufferBuilder builder, ushort t) { builder.AddUshort(1, t, 0); }
  public static void AddR(FlatBufferBuilder builder, ushort r) { builder.AddUshort(2, r, 0); }
  public static void AddB(FlatBufferBuilder builder, ushort b) { builder.AddUshort(3, b, 0); }
  public static Offset<Thickness> EndThickness(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Thickness>(o);
  }
};

public sealed class Border : Table {
  public static Border GetRootAsBorder(ByteBuffer _bb) { return GetRootAsBorder(_bb, new Border()); }
  public static Border GetRootAsBorder(ByteBuffer _bb, Border obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Border __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Padding Padding { get { return GetPadding(new Padding()); } }
  public Padding GetPadding(Padding obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public Thickness Thickness { get { return GetThickness(new Thickness()); } }
  public Thickness GetThickness(Thickness obj) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public Colour Brush { get { return GetBrush(new Colour()); } }
  public Colour GetBrush(Colour obj) { int o = __offset(8); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }

  public static void StartBorder(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddPadding(FlatBufferBuilder builder, Offset<Padding> paddingOffset) { builder.AddOffset(0, paddingOffset.Value, 0); }
  public static void AddThickness(FlatBufferBuilder builder, Offset<Thickness> thicknessOffset) { builder.AddOffset(1, thicknessOffset.Value, 0); }
  public static void AddBrush(FlatBufferBuilder builder, Offset<Colour> brushOffset) { builder.AddStruct(2, brushOffset.Value, 0); }
  public static Offset<Border> EndBorder(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Border>(o);
  }
};

public sealed class WidgetState : Table {
  public static WidgetState GetRootAsWidgetState(ByteBuffer _bb) { return GetRootAsWidgetState(_bb, new WidgetState()); }
  public static WidgetState GetRootAsWidgetState(ByteBuffer _bb, WidgetState obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public WidgetState __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string BgImage { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public Gradient BgGradient { get { return GetBgGradient(new Gradient()); } }
  public Gradient GetBgGradient(Gradient obj) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public bool BgAnimated { get { int o = __offset(8); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public Colour BgColour { get { return GetBgColour(new Colour()); } }
  public Colour GetBgColour(Colour obj) { int o = __offset(10); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Colour Colour { get { return GetColour(new Colour()); } }
  public Colour GetColour(Colour obj) { int o = __offset(12); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Padding Border { get { return GetBorder(new Padding()); } }
  public Padding GetBorder(Padding obj) { int o = __offset(14); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public uint Fontsize { get { int o = __offset(16); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }

  public static void StartWidgetState(FlatBufferBuilder builder) { builder.StartObject(7); }
  public static void AddBgImage(FlatBufferBuilder builder, StringOffset bgImageOffset) { builder.AddOffset(0, bgImageOffset.Value, 0); }
  public static void AddBgGradient(FlatBufferBuilder builder, Offset<Gradient> bgGradientOffset) { builder.AddOffset(1, bgGradientOffset.Value, 0); }
  public static void AddBgAnimated(FlatBufferBuilder builder, bool bgAnimated) { builder.AddBool(2, bgAnimated, false); }
  public static void AddBgColour(FlatBufferBuilder builder, Offset<Colour> bgColourOffset) { builder.AddStruct(3, bgColourOffset.Value, 0); }
  public static void AddColour(FlatBufferBuilder builder, Offset<Colour> colourOffset) { builder.AddStruct(4, colourOffset.Value, 0); }
  public static void AddBorder(FlatBufferBuilder builder, Offset<Padding> borderOffset) { builder.AddOffset(5, borderOffset.Value, 0); }
  public static void AddFontsize(FlatBufferBuilder builder, uint fontsize) { builder.AddUint(6, fontsize, 0); }
  public static Offset<WidgetState> EndWidgetState(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<WidgetState>(o);
  }
};

public sealed class Style : Table {
  public static Style GetRootAsStyle(ByteBuffer _bb) { return GetRootAsStyle(_bb, new Style()); }
  public static Style GetRootAsStyle(ByteBuffer _bb, Style obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Style __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public StyleType Type { get { int o = __offset(6); return o != 0 ? (StyleType)bb.GetSbyte(o + bb_pos) : StyleType.ST_DEFAULT; } }
  public WidgetState NormalState { get { return GetNormalState(new WidgetState()); } }
  public WidgetState GetNormalState(WidgetState obj) { int o = __offset(8); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public WidgetState ActiveState { get { return GetActiveState(new WidgetState()); } }
  public WidgetState GetActiveState(WidgetState obj) { int o = __offset(10); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public WidgetState PrelightState { get { return GetPrelightState(new WidgetState()); } }
  public WidgetState GetPrelightState(WidgetState obj) { int o = __offset(12); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public WidgetState SelectedState { get { return GetSelectedState(new WidgetState()); } }
  public WidgetState GetSelectedState(WidgetState obj) { int o = __offset(14); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public WidgetState InsensitiveState { get { return GetInsensitiveState(new WidgetState()); } }
  public WidgetState GetInsensitiveState(WidgetState obj) { int o = __offset(16); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public Scale Scale { get { return GetScale(new Scale()); } }
  public Scale GetScale(Scale obj) { int o = __offset(18); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Margin Margin { get { return GetMargin(new Margin()); } }
  public Margin GetMargin(Margin obj) { int o = __offset(20); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static void StartStyle(FlatBufferBuilder builder) { builder.StartObject(9); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(0, nameOffset.Value, 0); }
  public static void AddType(FlatBufferBuilder builder, StyleType type) { builder.AddSbyte(1, (sbyte)type, 0); }
  public static void AddNormalState(FlatBufferBuilder builder, Offset<WidgetState> normalStateOffset) { builder.AddOffset(2, normalStateOffset.Value, 0); }
  public static void AddActiveState(FlatBufferBuilder builder, Offset<WidgetState> activeStateOffset) { builder.AddOffset(3, activeStateOffset.Value, 0); }
  public static void AddPrelightState(FlatBufferBuilder builder, Offset<WidgetState> prelightStateOffset) { builder.AddOffset(4, prelightStateOffset.Value, 0); }
  public static void AddSelectedState(FlatBufferBuilder builder, Offset<WidgetState> selectedStateOffset) { builder.AddOffset(5, selectedStateOffset.Value, 0); }
  public static void AddInsensitiveState(FlatBufferBuilder builder, Offset<WidgetState> insensitiveStateOffset) { builder.AddOffset(6, insensitiveStateOffset.Value, 0); }
  public static void AddScale(FlatBufferBuilder builder, Offset<Scale> scaleOffset) { builder.AddStruct(7, scaleOffset.Value, 0); }
  public static void AddMargin(FlatBufferBuilder builder, Offset<Margin> marginOffset) { builder.AddOffset(8, marginOffset.Value, 0); }
  public static Offset<Style> EndStyle(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Style>(o);
  }
};

public sealed class Element : Table {
  public static Element GetRootAsElement(ByteBuffer _bb) { return GetRootAsElement(_bb, new Element()); }
  public static Element GetRootAsElement(ByteBuffer _bb, Element obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Element __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public ushort Id { get { int o = __offset(6); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public Align Align { get { return GetAlign(new Align()); } }
  public Align GetAlign(Align obj) { int o = __offset(8); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Scale Scale { get { return GetScale(new Scale()); } }
  public Scale GetScale(Scale obj) { int o = __offset(10); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public Vec2f Positon { get { return GetPositon(new Vec2f()); } }
  public Vec2f GetPositon(Vec2f obj) { int o = __offset(12); return o != 0 ? obj.__init(o + bb_pos, bb) : null; }
  public uint Width { get { int o = __offset(14); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public uint Height { get { int o = __offset(16); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public ushort Rotation { get { int o = __offset(18); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public string Tooltip { get { int o = __offset(20); return o != 0 ? __string(o + bb_pos) : null; } }
  public string Atlas { get { int o = __offset(22); return o != 0 ? __string(o + bb_pos) : null; } }
  public ushort Group { get { int o = __offset(24); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public bool IsEnabled { get { int o = __offset(26); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public Style Style { get { return GetStyle(new Style()); } }
  public Style GetStyle(Style obj) { int o = __offset(28); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static void StartElement(FlatBufferBuilder builder) { builder.StartObject(13); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(0, nameOffset.Value, 0); }
  public static void AddId(FlatBufferBuilder builder, ushort id) { builder.AddUshort(1, id, 0); }
  public static void AddAlign(FlatBufferBuilder builder, Offset<Align> alignOffset) { builder.AddStruct(2, alignOffset.Value, 0); }
  public static void AddScale(FlatBufferBuilder builder, Offset<Scale> scaleOffset) { builder.AddStruct(3, scaleOffset.Value, 0); }
  public static void AddPositon(FlatBufferBuilder builder, Offset<Vec2f> positonOffset) { builder.AddStruct(4, positonOffset.Value, 0); }
  public static void AddWidth(FlatBufferBuilder builder, uint width) { builder.AddUint(5, width, 0); }
  public static void AddHeight(FlatBufferBuilder builder, uint height) { builder.AddUint(6, height, 0); }
  public static void AddRotation(FlatBufferBuilder builder, ushort rotation) { builder.AddUshort(7, rotation, 0); }
  public static void AddTooltip(FlatBufferBuilder builder, StringOffset tooltipOffset) { builder.AddOffset(8, tooltipOffset.Value, 0); }
  public static void AddAtlas(FlatBufferBuilder builder, StringOffset atlasOffset) { builder.AddOffset(9, atlasOffset.Value, 0); }
  public static void AddGroup(FlatBufferBuilder builder, ushort group) { builder.AddUshort(10, group, 0); }
  public static void AddIsEnabled(FlatBufferBuilder builder, bool isEnabled) { builder.AddBool(11, isEnabled, false); }
  public static void AddStyle(FlatBufferBuilder builder, Offset<Style> styleOffset) { builder.AddOffset(12, styleOffset.Value, 0); }
  public static Offset<Element> EndElement(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Element>(o);
  }
};

public sealed class Label : Table {
  public static Label GetRootAsLabel(ByteBuffer _bb) { return GetRootAsLabel(_bb, new Label()); }
  public static Label GetRootAsLabel(ByteBuffer _bb, Label obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Label __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public ushort FontSize { get { int o = __offset(6); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }

  public static Offset<Label> CreateLabel(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      ushort fontSize = 0) {
    builder.StartObject(2);
    Label.AddBase(builder, baseOffset);
    Label.AddFontSize(builder, fontSize);
    return Label.EndLabel(builder);
  }

  public static void StartLabel(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddFontSize(FlatBufferBuilder builder, ushort fontSize) { builder.AddUshort(1, fontSize, 0); }
  public static Offset<Label> EndLabel(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Label>(o);
  }
};

public sealed class Image : Table {
  public static Image GetRootAsImage(ByteBuffer _bb) { return GetRootAsImage(_bb, new Image()); }
  public static Image GetRootAsImage(ByteBuffer _bb, Image obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Image __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<Image> CreateImage(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>)) {
    builder.StartObject(1);
    Image.AddBase(builder, baseOffset);
    return Image.EndImage(builder);
  }

  public static void StartImage(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static Offset<Image> EndImage(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Image>(o);
  }
};

public sealed class Button : Table {
  public static Button GetRootAsButton(ByteBuffer _bb) { return GetRootAsButton(_bb, new Button()); }
  public static Button GetRootAsButton(ByteBuffer _bb, Button obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Button __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public string Image { get { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; } }
  public string Itemsource { get { int o = __offset(8); return o != 0 ? __string(o + bb_pos) : null; } }
  public string Onclicked { get { int o = __offset(10); return o != 0 ? __string(o + bb_pos) : null; } }
  public string Onhover { get { int o = __offset(12); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Button> CreateButton(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      StringOffset imageOffset = default(StringOffset),
      StringOffset itemsourceOffset = default(StringOffset),
      StringOffset onclickedOffset = default(StringOffset),
      StringOffset onhoverOffset = default(StringOffset)) {
    builder.StartObject(5);
    Button.AddOnhover(builder, onhoverOffset);
    Button.AddOnclicked(builder, onclickedOffset);
    Button.AddItemsource(builder, itemsourceOffset);
    Button.AddImage(builder, imageOffset);
    Button.AddBase(builder, baseOffset);
    return Button.EndButton(builder);
  }

  public static void StartButton(FlatBufferBuilder builder) { builder.StartObject(5); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddImage(FlatBufferBuilder builder, StringOffset imageOffset) { builder.AddOffset(1, imageOffset.Value, 0); }
  public static void AddItemsource(FlatBufferBuilder builder, StringOffset itemsourceOffset) { builder.AddOffset(2, itemsourceOffset.Value, 0); }
  public static void AddOnclicked(FlatBufferBuilder builder, StringOffset onclickedOffset) { builder.AddOffset(3, onclickedOffset.Value, 0); }
  public static void AddOnhover(FlatBufferBuilder builder, StringOffset onhoverOffset) { builder.AddOffset(4, onhoverOffset.Value, 0); }
  public static Offset<Button> EndButton(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Button>(o);
  }
};

public sealed class CheckBox : Table {
  public static CheckBox GetRootAsCheckBox(ByteBuffer _bb) { return GetRootAsCheckBox(_bb, new CheckBox()); }
  public static CheckBox GetRootAsCheckBox(ByteBuffer _bb, CheckBox obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public CheckBox __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<CheckBox> CreateCheckBox(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>)) {
    builder.StartObject(1);
    CheckBox.AddBase(builder, baseOffset);
    return CheckBox.EndCheckBox(builder);
  }

  public static void StartCheckBox(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static Offset<CheckBox> EndCheckBox(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<CheckBox>(o);
  }
};

public sealed class ComboBox : Table {
  public static ComboBox GetRootAsComboBox(ByteBuffer _bb) { return GetRootAsComboBox(_bb, new ComboBox()); }
  public static ComboBox GetRootAsComboBox(ByteBuffer _bb, ComboBox obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public ComboBox __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public ListItem GetItems(int j) { return GetItems(new ListItem(), j); }
  public ListItem GetItems(ListItem obj, int j) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int ItemsLength { get { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; } }

  public static Offset<ComboBox> CreateComboBox(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      VectorOffset itemsOffset = default(VectorOffset)) {
    builder.StartObject(2);
    ComboBox.AddItems(builder, itemsOffset);
    ComboBox.AddBase(builder, baseOffset);
    return ComboBox.EndComboBox(builder);
  }

  public static void StartComboBox(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddItems(FlatBufferBuilder builder, VectorOffset itemsOffset) { builder.AddOffset(1, itemsOffset.Value, 0); }
  public static VectorOffset CreateItemsVector(FlatBufferBuilder builder, Offset<ListItem>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartItemsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<ComboBox> EndComboBox(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ComboBox>(o);
  }
};

public sealed class ListItem : Table {
  public static ListItem GetRootAsListItem(ByteBuffer _bb) { return GetRootAsListItem(_bb, new ListItem()); }
  public static ListItem GetRootAsListItem(ByteBuffer _bb, ListItem obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public ListItem __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ListItemType ListItemTypeType { get { int o = __offset(4); return o != 0 ? (ListItemType)bb.Get(o + bb_pos) : ListItemType.NONE; } }
  public TTable GetListItemType<TTable>(TTable obj) where TTable : Table { int o = __offset(6); return o != 0 ? __union(obj, o) : null; }

  public static Offset<ListItem> CreateListItem(FlatBufferBuilder builder,
      ListItemType listItemType_type = ListItemType.NONE,
      int listItemTypeOffset = 0) {
    builder.StartObject(2);
    ListItem.AddListItemType(builder, listItemTypeOffset);
    ListItem.AddListItemTypeType(builder, listItemType_type);
    return ListItem.EndListItem(builder);
  }

  public static void StartListItem(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddListItemTypeType(FlatBufferBuilder builder, ListItemType listItemTypeType) { builder.AddByte(0, (byte)listItemTypeType, 0); }
  public static void AddListItemType(FlatBufferBuilder builder, int listItemTypeOffset) { builder.AddOffset(1, listItemTypeOffset, 0); }
  public static Offset<ListItem> EndListItem(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ListItem>(o);
  }
};

public sealed class Menu : Table {
  public static Menu GetRootAsMenu(ByteBuffer _bb) { return GetRootAsMenu(_bb, new Menu()); }
  public static Menu GetRootAsMenu(ByteBuffer _bb, Menu obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Menu __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public ushort DisplayedElements { get { int o = __offset(6); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public MenuType Type { get { int o = __offset(8); return o != 0 ? (MenuType)bb.GetSbyte(o + bb_pos) : MenuType.MT_LIST; } }
  public ListItem GetItems(int j) { return GetItems(new ListItem(), j); }
  public ListItem GetItems(ListItem obj, int j) { int o = __offset(10); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int ItemsLength { get { int o = __offset(10); return o != 0 ? __vector_len(o) : 0; } }
  public uint ItemWidth { get { int o = __offset(12); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public uint ItemHeight { get { int o = __offset(14); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public string OnSelectionChanged { get { int o = __offset(16); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Menu> CreateMenu(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      ushort displayedElements = 0,
      MenuType type = MenuType.MT_LIST,
      VectorOffset itemsOffset = default(VectorOffset),
      uint itemWidth = 0,
      uint itemHeight = 0,
      StringOffset onSelectionChangedOffset = default(StringOffset)) {
    builder.StartObject(7);
    Menu.AddOnSelectionChanged(builder, onSelectionChangedOffset);
    Menu.AddItemHeight(builder, itemHeight);
    Menu.AddItemWidth(builder, itemWidth);
    Menu.AddItems(builder, itemsOffset);
    Menu.AddBase(builder, baseOffset);
    Menu.AddDisplayedElements(builder, displayedElements);
    Menu.AddType(builder, type);
    return Menu.EndMenu(builder);
  }

  public static void StartMenu(FlatBufferBuilder builder) { builder.StartObject(7); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddDisplayedElements(FlatBufferBuilder builder, ushort displayedElements) { builder.AddUshort(1, displayedElements, 0); }
  public static void AddType(FlatBufferBuilder builder, MenuType type) { builder.AddSbyte(2, (sbyte)type, 0); }
  public static void AddItems(FlatBufferBuilder builder, VectorOffset itemsOffset) { builder.AddOffset(3, itemsOffset.Value, 0); }
  public static VectorOffset CreateItemsVector(FlatBufferBuilder builder, Offset<ListItem>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartItemsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddItemWidth(FlatBufferBuilder builder, uint itemWidth) { builder.AddUint(4, itemWidth, 0); }
  public static void AddItemHeight(FlatBufferBuilder builder, uint itemHeight) { builder.AddUint(5, itemHeight, 0); }
  public static void AddOnSelectionChanged(FlatBufferBuilder builder, StringOffset onSelectionChangedOffset) { builder.AddOffset(6, onSelectionChangedOffset.Value, 0); }
  public static Offset<Menu> EndMenu(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Menu>(o);
  }
};

public sealed class Navigation : Table {
  public static Navigation GetRootAsNavigation(ByteBuffer _bb) { return GetRootAsNavigation(_bb, new Navigation()); }
  public static Navigation GetRootAsNavigation(ByteBuffer _bb, Navigation obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Navigation __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public MenuType Type { get { int o = __offset(6); return o != 0 ? (MenuType)bb.GetSbyte(o + bb_pos) : MenuType.MT_LIST; } }
  public ListItem GetItems(int j) { return GetItems(new ListItem(), j); }
  public ListItem GetItems(ListItem obj, int j) { int o = __offset(8); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int ItemsLength { get { int o = __offset(8); return o != 0 ? __vector_len(o) : 0; } }
  public uint ItemWidth { get { int o = __offset(10); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public uint ItemHeight { get { int o = __offset(12); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public string OnSelectionChanged { get { int o = __offset(14); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Navigation> CreateNavigation(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      MenuType type = MenuType.MT_LIST,
      VectorOffset itemsOffset = default(VectorOffset),
      uint itemWidth = 0,
      uint itemHeight = 0,
      StringOffset onSelectionChangedOffset = default(StringOffset)) {
    builder.StartObject(6);
    Navigation.AddOnSelectionChanged(builder, onSelectionChangedOffset);
    Navigation.AddItemHeight(builder, itemHeight);
    Navigation.AddItemWidth(builder, itemWidth);
    Navigation.AddItems(builder, itemsOffset);
    Navigation.AddBase(builder, baseOffset);
    Navigation.AddType(builder, type);
    return Navigation.EndNavigation(builder);
  }

  public static void StartNavigation(FlatBufferBuilder builder) { builder.StartObject(6); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddType(FlatBufferBuilder builder, MenuType type) { builder.AddSbyte(1, (sbyte)type, 0); }
  public static void AddItems(FlatBufferBuilder builder, VectorOffset itemsOffset) { builder.AddOffset(2, itemsOffset.Value, 0); }
  public static VectorOffset CreateItemsVector(FlatBufferBuilder builder, Offset<ListItem>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartItemsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddItemWidth(FlatBufferBuilder builder, uint itemWidth) { builder.AddUint(3, itemWidth, 0); }
  public static void AddItemHeight(FlatBufferBuilder builder, uint itemHeight) { builder.AddUint(4, itemHeight, 0); }
  public static void AddOnSelectionChanged(FlatBufferBuilder builder, StringOffset onSelectionChangedOffset) { builder.AddOffset(5, onSelectionChangedOffset.Value, 0); }
  public static Offset<Navigation> EndNavigation(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Navigation>(o);
  }
};

public sealed class Console : Table {
  public static Console GetRootAsConsole(ByteBuffer _bb) { return GetRootAsConsole(_bb, new Console()); }
  public static Console GetRootAsConsole(ByteBuffer _bb, Console obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Console __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public uint Fontsize { get { int o = __offset(6); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }

  public static Offset<Console> CreateConsole(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      uint fontsize = 0) {
    builder.StartObject(2);
    Console.AddFontsize(builder, fontsize);
    Console.AddBase(builder, baseOffset);
    return Console.EndConsole(builder);
  }

  public static void StartConsole(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddFontsize(FlatBufferBuilder builder, uint fontsize) { builder.AddUint(1, fontsize, 0); }
  public static Offset<Console> EndConsole(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Console>(o);
  }
};

public sealed class ProgressBar : Table {
  public static ProgressBar GetRootAsProgressBar(ByteBuffer _bb) { return GetRootAsProgressBar(_bb, new ProgressBar()); }
  public static ProgressBar GetRootAsProgressBar(ByteBuffer _bb, ProgressBar obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public ProgressBar __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<ProgressBar> CreateProgressBar(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>)) {
    builder.StartObject(1);
    ProgressBar.AddBase(builder, baseOffset);
    return ProgressBar.EndProgressBar(builder);
  }

  public static void StartProgressBar(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static Offset<ProgressBar> EndProgressBar(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ProgressBar>(o);
  }
};

public sealed class ToggleButton : Table {
  public static ToggleButton GetRootAsToggleButton(ByteBuffer _bb) { return GetRootAsToggleButton(_bb, new ToggleButton()); }
  public static ToggleButton GetRootAsToggleButton(ByteBuffer _bb, ToggleButton obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public ToggleButton __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }

  public static Offset<ToggleButton> CreateToggleButton(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>)) {
    builder.StartObject(1);
    ToggleButton.AddBase(builder, baseOffset);
    return ToggleButton.EndToggleButton(builder);
  }

  public static void StartToggleButton(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static Offset<ToggleButton> EndToggleButton(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ToggleButton>(o);
  }
};

public sealed class UIWindow : Table {
  public static UIWindow GetRootAsUIWindow(ByteBuffer _bb) { return GetRootAsUIWindow(_bb, new UIWindow()); }
  public static UIWindow GetRootAsUIWindow(ByteBuffer _bb, UIWindow obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public UIWindow __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public bool ShowHead { get { int o = __offset(6); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }

  public static Offset<UIWindow> CreateUIWindow(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      bool showHead = false) {
    builder.StartObject(2);
    UIWindow.AddBase(builder, baseOffset);
    UIWindow.AddShowHead(builder, showHead);
    return UIWindow.EndUIWindow(builder);
  }

  public static void StartUIWindow(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddShowHead(FlatBufferBuilder builder, bool showHead) { builder.AddBool(1, showHead, false); }
  public static Offset<UIWindow> EndUIWindow(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<UIWindow>(o);
  }
};

public sealed class Box : Table {
  public static Box GetRootAsBox(ByteBuffer _bb) { return GetRootAsBox(_bb, new Box()); }
  public static Box GetRootAsBox(ByteBuffer _bb, Box obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Box __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public UIElement GetUiElements(int j) { return GetUiElements(new UIElement(), j); }
  public UIElement GetUiElements(UIElement obj, int j) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int UiElementsLength { get { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; } }
  public Orientation Orientation { get { int o = __offset(8); return o != 0 ? (Orientation)bb.GetSbyte(o + bb_pos) : Orientation.horizontal; } }

  public static Offset<Box> CreateBox(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      VectorOffset uiElementsOffset = default(VectorOffset),
      Orientation orientation = Orientation.horizontal) {
    builder.StartObject(3);
    Box.AddUiElements(builder, uiElementsOffset);
    Box.AddBase(builder, baseOffset);
    Box.AddOrientation(builder, orientation);
    return Box.EndBox(builder);
  }

  public static void StartBox(FlatBufferBuilder builder) { builder.StartObject(3); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddUiElements(FlatBufferBuilder builder, VectorOffset uiElementsOffset) { builder.AddOffset(1, uiElementsOffset.Value, 0); }
  public static VectorOffset CreateUiElementsVector(FlatBufferBuilder builder, Offset<UIElement>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartUiElementsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddOrientation(FlatBufferBuilder builder, Orientation orientation) { builder.AddSbyte(2, (sbyte)orientation, 0); }
  public static Offset<Box> EndBox(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Box>(o);
  }
};

public sealed class Alignment : Table {
  public static Alignment GetRootAsAlignment(ByteBuffer _bb) { return GetRootAsAlignment(_bb, new Alignment()); }
  public static Alignment GetRootAsAlignment(ByteBuffer _bb, Alignment obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Alignment __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Element Base { get { return GetBase(new Element()); } }
  public Element GetBase(Element obj) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(o + bb_pos), bb) : null; }
  public UIElement GetUiElements(int j) { return GetUiElements(new UIElement(), j); }
  public UIElement GetUiElements(UIElement obj, int j) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int UiElementsLength { get { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; } }

  public static Offset<Alignment> CreateAlignment(FlatBufferBuilder builder,
      Offset<Element> baseOffset = default(Offset<Element>),
      VectorOffset uiElementsOffset = default(VectorOffset)) {
    builder.StartObject(2);
    Alignment.AddUiElements(builder, uiElementsOffset);
    Alignment.AddBase(builder, baseOffset);
    return Alignment.EndAlignment(builder);
  }

  public static void StartAlignment(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddBase(FlatBufferBuilder builder, Offset<Element> baseOffset) { builder.AddOffset(0, baseOffset.Value, 0); }
  public static void AddUiElements(FlatBufferBuilder builder, VectorOffset uiElementsOffset) { builder.AddOffset(1, uiElementsOffset.Value, 0); }
  public static VectorOffset CreateUiElementsVector(FlatBufferBuilder builder, Offset<UIElement>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartUiElementsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<Alignment> EndAlignment(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Alignment>(o);
  }
};

public sealed class UIElement : Table {
  public static UIElement GetRootAsUIElement(ByteBuffer _bb) { return GetRootAsUIElement(_bb, new UIElement()); }
  public static UIElement GetRootAsUIElement(ByteBuffer _bb, UIElement obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public UIElement __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public UUIElement EleType { get { int o = __offset(4); return o != 0 ? (UUIElement)bb.Get(o + bb_pos) : UUIElement.NONE; } }
  public TTable GetEle<TTable>(TTable obj) where TTable : Table { int o = __offset(6); return o != 0 ? __union(obj, o) : null; }

  public static Offset<UIElement> CreateUIElement(FlatBufferBuilder builder,
      UUIElement ele_type = UUIElement.NONE,
      int eleOffset = 0) {
    builder.StartObject(2);
    UIElement.AddEle(builder, eleOffset);
    UIElement.AddEleType(builder, ele_type);
    return UIElement.EndUIElement(builder);
  }

  public static void StartUIElement(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddEleType(FlatBufferBuilder builder, UUIElement eleType) { builder.AddByte(0, (byte)eleType, 0); }
  public static void AddEle(FlatBufferBuilder builder, int eleOffset) { builder.AddOffset(1, eleOffset, 0); }
  public static Offset<UIElement> EndUIElement(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<UIElement>(o);
  }
};

public sealed class StyleData : Table {
  public static StyleData GetRootAsStyleData(ByteBuffer _bb) { return GetRootAsStyleData(_bb, new StyleData()); }
  public static StyleData GetRootAsStyleData(ByteBuffer _bb, StyleData obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public StyleData __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public Style GetStyles(int j) { return GetStyles(new Style(), j); }
  public Style GetStyles(Style obj, int j) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int StylesLength { get { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; } }

  public static Offset<StyleData> CreateStyleData(FlatBufferBuilder builder,
      VectorOffset stylesOffset = default(VectorOffset)) {
    builder.StartObject(1);
    StyleData.AddStyles(builder, stylesOffset);
    return StyleData.EndStyleData(builder);
  }

  public static void StartStyleData(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddStyles(FlatBufferBuilder builder, VectorOffset stylesOffset) { builder.AddOffset(0, stylesOffset.Value, 0); }
  public static VectorOffset CreateStylesVector(FlatBufferBuilder builder, Offset<Style>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartStylesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<StyleData> EndStyleData(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<StyleData>(o);
  }
};

public sealed class UIStateData : Table {
  public static UIStateData GetRootAsUIStateData(ByteBuffer _bb) { return GetRootAsUIStateData(_bb, new UIStateData()); }
  public static UIStateData GetRootAsUIStateData(ByteBuffer _bb, UIStateData obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public UIStateData __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Atlas { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public bool AutoDeleteAtlas { get { int o = __offset(6); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; } }
  public ResourceLocation GetLocations(int j) { return GetLocations(new ResourceLocation(), j); }
  public ResourceLocation GetLocations(ResourceLocation obj, int j) { int o = __offset(8); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int LocationsLength { get { int o = __offset(8); return o != 0 ? __vector_len(o) : 0; } }
  public UIElement GetElements(int j) { return GetElements(new UIElement(), j); }
  public UIElement GetElements(UIElement obj, int j) { int o = __offset(10); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int ElementsLength { get { int o = __offset(10); return o != 0 ? __vector_len(o) : 0; } }

  public static Offset<UIStateData> CreateUIStateData(FlatBufferBuilder builder,
      StringOffset atlasOffset = default(StringOffset),
      bool autoDeleteAtlas = false,
      VectorOffset locationsOffset = default(VectorOffset),
      VectorOffset elementsOffset = default(VectorOffset)) {
    builder.StartObject(4);
    UIStateData.AddElements(builder, elementsOffset);
    UIStateData.AddLocations(builder, locationsOffset);
    UIStateData.AddAtlas(builder, atlasOffset);
    UIStateData.AddAutoDeleteAtlas(builder, autoDeleteAtlas);
    return UIStateData.EndUIStateData(builder);
  }

  public static void StartUIStateData(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddAtlas(FlatBufferBuilder builder, StringOffset atlasOffset) { builder.AddOffset(0, atlasOffset.Value, 0); }
  public static void AddAutoDeleteAtlas(FlatBufferBuilder builder, bool autoDeleteAtlas) { builder.AddBool(1, autoDeleteAtlas, false); }
  public static void AddLocations(FlatBufferBuilder builder, VectorOffset locationsOffset) { builder.AddOffset(2, locationsOffset.Value, 0); }
  public static VectorOffset CreateLocationsVector(FlatBufferBuilder builder, Offset<ResourceLocation>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartLocationsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddElements(FlatBufferBuilder builder, VectorOffset elementsOffset) { builder.AddOffset(3, elementsOffset.Value, 0); }
  public static VectorOffset CreateElementsVector(FlatBufferBuilder builder, Offset<UIElement>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartElementsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<UIStateData> EndUIStateData(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<UIStateData>(o);
  }
};


}
