// automatically generated, do not modify

namespace XFBType
{

using FlatBuffers;

public sealed class Sprite : Table {
  public static Sprite GetRootAsSprite(ByteBuffer _bb) { return GetRootAsSprite(_bb, new Sprite()); }
  public static Sprite GetRootAsSprite(ByteBuffer _bb, Sprite obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Sprite __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public float Width { get { int o = __offset(4); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Height { get { int o = __offset(6); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float PosX { get { int o = __offset(8); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float PosY { get { int o = __offset(10); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public string Name { get { int o = __offset(12); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Sprite> CreateSprite(FlatBufferBuilder builder,
      float width = 0,
      float height = 0,
      float posX = 0,
      float posY = 0,
      StringOffset nameOffset = default(StringOffset)) {
    builder.StartObject(5);
    Sprite.AddName(builder, nameOffset);
    Sprite.AddPosY(builder, posY);
    Sprite.AddPosX(builder, posX);
    Sprite.AddHeight(builder, height);
    Sprite.AddWidth(builder, width);
    return Sprite.EndSprite(builder);
  }

  public static void StartSprite(FlatBufferBuilder builder) { builder.StartObject(5); }
  public static void AddWidth(FlatBufferBuilder builder, float width) { builder.AddFloat(0, width, 0); }
  public static void AddHeight(FlatBufferBuilder builder, float height) { builder.AddFloat(1, height, 0); }
  public static void AddPosX(FlatBufferBuilder builder, float posX) { builder.AddFloat(2, posX, 0); }
  public static void AddPosY(FlatBufferBuilder builder, float posY) { builder.AddFloat(3, posY, 0); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(4, nameOffset.Value, 0); }
  public static Offset<Sprite> EndSprite(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Sprite>(o);
  }
};

///Distances between two characters next to each other.
public sealed class KerningData : Table {
  public static KerningData GetRootAsKerningData(ByteBuffer _bb) { return GetRootAsKerningData(_bb, new KerningData()); }
  public static KerningData GetRootAsKerningData(ByteBuffer _bb, KerningData obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public KerningData __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint Character { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public float Kerning { get { int o = __offset(6); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }

  public static Offset<KerningData> CreateKerningData(FlatBufferBuilder builder,
      uint character = 0,
      float kerning = 0) {
    builder.StartObject(2);
    KerningData.AddKerning(builder, kerning);
    KerningData.AddCharacter(builder, character);
    return KerningData.EndKerningData(builder);
  }

  public static void StartKerningData(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddCharacter(FlatBufferBuilder builder, uint character) { builder.AddUint(0, character, 0); }
  public static void AddKerning(FlatBufferBuilder builder, float kerning) { builder.AddFloat(1, kerning, 0); }
  public static Offset<KerningData> EndKerningData(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<KerningData>(o);
  }
};

///Texture and size information about a single character loaded from a TextureAtlas.
public sealed class Glyph : Table {
  public static Glyph GetRootAsGlyph(ByteBuffer _bb) { return GetRootAsGlyph(_bb, new Glyph()); }
  public static Glyph GetRootAsGlyph(ByteBuffer _bb, Glyph obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Glyph __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint Code { get { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; } }
  public float UvTop { get { int o = __offset(6); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float UvBottom { get { int o = __offset(8); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float UvWidth { get { int o = __offset(10); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float UvHeight { get { int o = __offset(12); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float UvLeft { get { int o = __offset(14); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float UvRight { get { int o = __offset(16); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float GlyphWidth { get { int o = __offset(18); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float GlyphHeight { get { int o = __offset(20); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float GlyphAdvance { get { int o = __offset(22); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float VerticalOffset { get { int o = __offset(24); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public KerningData GetKerningList(int j) { return GetKerningList(new KerningData(), j); }
  public KerningData GetKerningList(KerningData obj, int j) { int o = __offset(26); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int KerningListLength { get { int o = __offset(26); return o != 0 ? __vector_len(o) : 0; } }

  public static Offset<Glyph> CreateGlyph(FlatBufferBuilder builder,
      uint code = 0,
      float uvTop = 0,
      float uvBottom = 0,
      float uvWidth = 0,
      float uvHeight = 0,
      float uvLeft = 0,
      float uvRight = 0,
      float glyphWidth = 0,
      float glyphHeight = 0,
      float glyphAdvance = 0,
      float verticalOffset = 0,
      VectorOffset kerningListOffset = default(VectorOffset)) {
    builder.StartObject(12);
    Glyph.AddKerningList(builder, kerningListOffset);
    Glyph.AddVerticalOffset(builder, verticalOffset);
    Glyph.AddGlyphAdvance(builder, glyphAdvance);
    Glyph.AddGlyphHeight(builder, glyphHeight);
    Glyph.AddGlyphWidth(builder, glyphWidth);
    Glyph.AddUvRight(builder, uvRight);
    Glyph.AddUvLeft(builder, uvLeft);
    Glyph.AddUvHeight(builder, uvHeight);
    Glyph.AddUvWidth(builder, uvWidth);
    Glyph.AddUvBottom(builder, uvBottom);
    Glyph.AddUvTop(builder, uvTop);
    Glyph.AddCode(builder, code);
    return Glyph.EndGlyph(builder);
  }

  public static void StartGlyph(FlatBufferBuilder builder) { builder.StartObject(12); }
  public static void AddCode(FlatBufferBuilder builder, uint code) { builder.AddUint(0, code, 0); }
  public static void AddUvTop(FlatBufferBuilder builder, float uvTop) { builder.AddFloat(1, uvTop, 0); }
  public static void AddUvBottom(FlatBufferBuilder builder, float uvBottom) { builder.AddFloat(2, uvBottom, 0); }
  public static void AddUvWidth(FlatBufferBuilder builder, float uvWidth) { builder.AddFloat(3, uvWidth, 0); }
  public static void AddUvHeight(FlatBufferBuilder builder, float uvHeight) { builder.AddFloat(4, uvHeight, 0); }
  public static void AddUvLeft(FlatBufferBuilder builder, float uvLeft) { builder.AddFloat(5, uvLeft, 0); }
  public static void AddUvRight(FlatBufferBuilder builder, float uvRight) { builder.AddFloat(6, uvRight, 0); }
  public static void AddGlyphWidth(FlatBufferBuilder builder, float glyphWidth) { builder.AddFloat(7, glyphWidth, 0); }
  public static void AddGlyphHeight(FlatBufferBuilder builder, float glyphHeight) { builder.AddFloat(8, glyphHeight, 0); }
  public static void AddGlyphAdvance(FlatBufferBuilder builder, float glyphAdvance) { builder.AddFloat(9, glyphAdvance, 0); }
  public static void AddVerticalOffset(FlatBufferBuilder builder, float verticalOffset) { builder.AddFloat(10, verticalOffset, 0); }
  public static void AddKerningList(FlatBufferBuilder builder, VectorOffset kerningListOffset) { builder.AddOffset(11, kerningListOffset.Value, 0); }
  public static VectorOffset CreateKerningListVector(FlatBufferBuilder builder, Offset<KerningData>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartKerningListVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<Glyph> EndGlyph(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Glyph>(o);
  }
};

public sealed class Font : Table {
  public static Font GetRootAsFont(ByteBuffer _bb) { return GetRootAsFont(_bb, new Font()); }
  public static Font GetRootAsFont(ByteBuffer _bb, Font obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Font __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public ushort Id { get { int o = __offset(4); return o != 0 ? bb.GetUshort(o + bb_pos) : (ushort)0; } }
  public Glyph GetGlyphs(int j) { return GetGlyphs(new Glyph(), j); }
  public Glyph GetGlyphs(Glyph obj, int j) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int GlyphsLength { get { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; } }
  public float RangeBegin { get { int o = __offset(8); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float RangeEnd { get { int o = __offset(10); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float SpaceLength { get { int o = __offset(12); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float LineHeight { get { int o = __offset(14); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float Baseline { get { int o = __offset(16); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float LineSpacing { get { int o = __offset(18); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float LetterSpacing { get { int o = __offset(20); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }
  public float MonoWidth { get { int o = __offset(22); return o != 0 ? bb.GetFloat(o + bb_pos) : (float)0; } }

  public static Offset<Font> CreateFont(FlatBufferBuilder builder,
      ushort id = 0,
      VectorOffset glyphsOffset = default(VectorOffset),
      float rangeBegin = 0,
      float rangeEnd = 0,
      float spaceLength = 0,
      float lineHeight = 0,
      float baseline = 0,
      float lineSpacing = 0,
      float letterSpacing = 0,
      float monoWidth = 0) {
    builder.StartObject(10);
    Font.AddMonoWidth(builder, monoWidth);
    Font.AddLetterSpacing(builder, letterSpacing);
    Font.AddLineSpacing(builder, lineSpacing);
    Font.AddBaseline(builder, baseline);
    Font.AddLineHeight(builder, lineHeight);
    Font.AddSpaceLength(builder, spaceLength);
    Font.AddRangeEnd(builder, rangeEnd);
    Font.AddRangeBegin(builder, rangeBegin);
    Font.AddGlyphs(builder, glyphsOffset);
    Font.AddId(builder, id);
    return Font.EndFont(builder);
  }

  public static void StartFont(FlatBufferBuilder builder) { builder.StartObject(10); }
  public static void AddId(FlatBufferBuilder builder, ushort id) { builder.AddUshort(0, id, 0); }
  public static void AddGlyphs(FlatBufferBuilder builder, VectorOffset glyphsOffset) { builder.AddOffset(1, glyphsOffset.Value, 0); }
  public static VectorOffset CreateGlyphsVector(FlatBufferBuilder builder, Offset<Glyph>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartGlyphsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddRangeBegin(FlatBufferBuilder builder, float rangeBegin) { builder.AddFloat(2, rangeBegin, 0); }
  public static void AddRangeEnd(FlatBufferBuilder builder, float rangeEnd) { builder.AddFloat(3, rangeEnd, 0); }
  public static void AddSpaceLength(FlatBufferBuilder builder, float spaceLength) { builder.AddFloat(4, spaceLength, 0); }
  public static void AddLineHeight(FlatBufferBuilder builder, float lineHeight) { builder.AddFloat(5, lineHeight, 0); }
  public static void AddBaseline(FlatBufferBuilder builder, float baseline) { builder.AddFloat(6, baseline, 0); }
  public static void AddLineSpacing(FlatBufferBuilder builder, float lineSpacing) { builder.AddFloat(7, lineSpacing, 0); }
  public static void AddLetterSpacing(FlatBufferBuilder builder, float letterSpacing) { builder.AddFloat(8, letterSpacing, 0); }
  public static void AddMonoWidth(FlatBufferBuilder builder, float monoWidth) { builder.AddFloat(9, monoWidth, 0); }
  public static Offset<Font> EndFont(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Font>(o);
  }
};

public sealed class Atlas : Table {
  public static Atlas GetRootAsAtlas(ByteBuffer _bb) { return GetRootAsAtlas(_bb, new Atlas()); }
  public static Atlas GetRootAsAtlas(ByteBuffer _bb, Atlas obj) { return (obj.__init(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public Atlas __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public string Name { get { int o = __offset(4); return o != 0 ? __string(o + bb_pos) : null; } }
  public Sprite GetSprites(int j) { return GetSprites(new Sprite(), j); }
  public Sprite GetSprites(Sprite obj, int j) { int o = __offset(6); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int SpritesLength { get { int o = __offset(6); return o != 0 ? __vector_len(o) : 0; } }
  public Font GetFonts(int j) { return GetFonts(new Font(), j); }
  public Font GetFonts(Font obj, int j) { int o = __offset(8); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int FontsLength { get { int o = __offset(8); return o != 0 ? __vector_len(o) : 0; } }
  public string Texture { get { int o = __offset(10); return o != 0 ? __string(o + bb_pos) : null; } }

  public static Offset<Atlas> CreateAtlas(FlatBufferBuilder builder,
      StringOffset nameOffset = default(StringOffset),
      VectorOffset spritesOffset = default(VectorOffset),
      VectorOffset fontsOffset = default(VectorOffset),
      StringOffset textureOffset = default(StringOffset)) {
    builder.StartObject(4);
    Atlas.AddTexture(builder, textureOffset);
    Atlas.AddFonts(builder, fontsOffset);
    Atlas.AddSprites(builder, spritesOffset);
    Atlas.AddName(builder, nameOffset);
    return Atlas.EndAtlas(builder);
  }

  public static void StartAtlas(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddName(FlatBufferBuilder builder, StringOffset nameOffset) { builder.AddOffset(0, nameOffset.Value, 0); }
  public static void AddSprites(FlatBufferBuilder builder, VectorOffset spritesOffset) { builder.AddOffset(1, spritesOffset.Value, 0); }
  public static VectorOffset CreateSpritesVector(FlatBufferBuilder builder, Offset<Sprite>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartSpritesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddFonts(FlatBufferBuilder builder, VectorOffset fontsOffset) { builder.AddOffset(2, fontsOffset.Value, 0); }
  public static VectorOffset CreateFontsVector(FlatBufferBuilder builder, Offset<Font>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartFontsVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddTexture(FlatBufferBuilder builder, StringOffset textureOffset) { builder.AddOffset(3, textureOffset.Value, 0); }
  public static Offset<Atlas> EndAtlas(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Atlas>(o);
  }
  public static void FinishAtlasBuffer(FlatBufferBuilder builder, Offset<Atlas> offset) { builder.Finish(offset.Value); }
};


}
