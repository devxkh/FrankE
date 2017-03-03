using System;
using System.Windows;
using FlatBuffers;
using System.Xml.Serialization;
using VEX.Interface.DAL;
using VEX.Interface.Scene.Services;
using System.Collections.ObjectModel;
using VEX.Core.Shared.Model.UI;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.ComponentModel;
using VEF.View.Types;

namespace VEX.Model.UI.FBufferObject
{

    [DataContract]
    public class FB_UI_Atlas : IFBObject//, INetMsg
    {
        #region private members

     //   private XFBType.Node m_FBData = new XFBType.Node();

        private ObservableCollection<SpriteModel> _sprites;
        private ObservableCollection<FontModel> _fonts;

        #endregion

        #region Properties

        [DataMember]
        [Category("Generated Atlas")]
        public string AtlasName { get; set; }

        [DataMember]
        [Category("Generated Atlas")]
        [Editor(typeof(FilePathEditor), typeof(FilePathEditor))]
        [Description("filepath to atlas texture")]
        [DisplayName("TextureFile")]
        public string TextureName { get; set; }

        [Browsable(false)]
        public ObservableCollection<SpriteModel> Sprites { get { if (_sprites == null) _sprites = new ObservableCollection<SpriteModel>(); return _sprites; } set { _sprites = value; } }

        [Browsable(false)]
        public ObservableCollection<FontModel> Fonts { get { if (_fonts == null) _fonts = new ObservableCollection<FontModel>(); return _fonts; } set { _fonts = value; } }

        //   public NetMsg.Data FBMsgType { get { return NetMsg.Data.Node; } }
        
        public object Parent { get; set; }

        #endregion

        public FB_UI_Atlas()
        {
            _sprites = new ObservableCollection<SpriteModel>();
            _fonts = new ObservableCollection<FontModel>();
        }

        #region Methods 

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
          //  m_FBData = XFBType.Node.GetRootAsNode(byteBuffer); // read 

            //m_Rotation = new Quaternion() { W = m_FBData.Transform.Rot.W, X = m_FBData.Transform.Rot.X, Y = m_FBData.Transform.Rot.Y, Z = m_FBData.Transform.Rot.Z };
            //m_Location = new Vector3() { X = m_FBData.Transform.Loc.X, Y = m_FBData.Transform.Loc.Y, Z = m_FBData.Transform.Loc.Z };
            //m_Scale = new Vector3() { X = m_FBData.Transform.Scl.X, Y = m_FBData.Transform.Scl.Y, Z = m_FBData.Transform.Scl.Z };
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            VectorOffset spritesOffset = new VectorOffset();
            if (_sprites.Count > 0)
            {
                List<int> spriteOffsets = new List<int>();
                foreach (var sprite in _sprites)
                    spriteOffsets.Add(XFBType.Sprite.CreateSprite(fbb, sprite.width, sprite.height, sprite.posX, sprite.posY, fbb.CreateString(sprite.Name ?? "")).Value);

                XFBType.Atlas.StartSpritesVector(fbb, _sprites.Count);
                foreach (var sprite in spriteOffsets)
                    fbb.AddOffset(sprite);
                spritesOffset = fbb.EndVector();
            }

            //------------------------ fonts ------------------------
            VectorOffset fontsOffset = new VectorOffset();
            if (_fonts.Count > 0)
            {
                List<int> fontsOffsets = new List<int>();
                foreach (FontModel font in _fonts)
                {
                    //------------------------  Font (e.g. [Font.24] ) = glyphData ------------------------
                    VectorOffset glyphsOffset = new VectorOffset();
                    if (font.Items.Count > 0) //font glyphs
                    {
                        //------------------------ FontData contains glyph,kerning data ------------------------
                        List<int> glyphsOffsets = new List<int>();
                        foreach (FontData fontData in font.Items)
                        {
                            //------------------------ kernings ------------------------
                            VectorOffset kerningsOffset = new VectorOffset();
                            if (fontData.Kerning.Count > 0)
                            {
                                List<int> kerningsOffsets = new List<int>();
                                foreach (Kerning kerningModel in fontData.Kerning)
                                {
                                    kerningsOffsets.Add(XFBType.KerningData.CreateKerningData(fbb, kerningModel.RightGlyphID, kerningModel.KerningValue).Value);
                                }

                                XFBType.Glyph.StartKerningListVector(fbb, fontData.Kerning.Count);
                                foreach (var kerning in kerningsOffsets)
                                    fbb.AddOffset(kerning);
                                kerningsOffset = fbb.EndVector();
                            }
                            
                            //glyph->uvLeft = offset.x + Ogre::StringConverter::parseReal(str_values[0]);
                            //glyph->uvTop = offset.y + Ogre::StringConverter::parseReal(str_values[1]);
                            //glyph->uvWidth = Ogre::StringConverter::parseReal(str_values[2]);
                            //glyph->uvHeight = Ogre::StringConverter::parseReal(str_values[3]);
                            //glyph->uvRight = glyph->uvLeft + glyph->uvWidth;
                            //glyph->uvBottom = glyph->uvTop + glyph->uvHeight;

                            //if (str_values.size() == 5)
                            //    glyph->glyphAdvance = Ogre::StringConverter::parseInt(str_values[4]);
                            //else
                            //    glyph->glyphAdvance = glyph->uvWidth;


                            glyphsOffsets.Add(XFBType.Glyph.CreateGlyph(fbb
                                , fontData.CharacterAsUint //glyph code
                                , font.offset.y + fontData.Glyph.Y//uvTop
                                , font.offset.y + fontData.Glyph.Y + fontData.Glyph.height  //uvBottom
                                , fontData.Glyph.width //uvWidth
                                , fontData.Glyph.height //uvHeight
                                , font.offset.x + fontData.Glyph.X //uvLeft
                                , font.offset.x + fontData.Glyph.X + fontData.Glyph.width //uvRight
                                , fontData.Glyph.width //glyphWidth
                                , fontData.Glyph.height //glyphHeight
                                , (fontData.Glyph.advance > 0 ? fontData.Glyph.advance : fontData.Glyph.width) //glyphAdvance
                                , fontData.VerticalOffset //verticalOffset
                                , kerningsOffset).Value);
                        }
                        
                        XFBType.Font.StartGlyphsVector(fbb, font.Items.Count);
                        foreach (var glyph in glyphsOffsets)
                            fbb.AddOffset(glyph);
                        glyphsOffset = fbb.EndVector();
                    }
                    
                    fontsOffsets.Add(XFBType.Font.CreateFont(fbb, font.Id, glyphsOffset, font.rangeFrom, font.rangeTo, font.spacelength, font.lineheight,
                                font.baseline, font.lineSpacing, font.letterspacing, font.monowidth).Value);
                }

                XFBType.Atlas.StartFontsVector(fbb, _fonts.Count);
                foreach (var fonts in fontsOffsets)
                    fbb.AddOffset(fonts);
                fontsOffset = fbb.EndVector();
            }

            var atlasName = fbb.CreateString(AtlasName);
            var texName = fbb.CreateString(Path.GetFileName(TextureName));

            XFBType.Atlas.StartAtlas(fbb);
            XFBType.Atlas.AddName(fbb, atlasName);
            XFBType.Atlas.AddSprites(fbb, spritesOffset);
            XFBType.Atlas.AddFonts(fbb, fontsOffset);
            XFBType.Atlas.AddTexture(fbb, texName);

            var finishOffset = XFBType.Atlas.EndAtlas(fbb);

            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }

        #endregion
    }
}
