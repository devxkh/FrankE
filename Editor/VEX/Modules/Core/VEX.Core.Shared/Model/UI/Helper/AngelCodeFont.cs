using Cyotek.Drawing.BitmapFont;
using System;
using System.Collections.Generic;
using System.Text;
using VEX.Model.UI;

namespace VEX.Core.Shared.Model.UI.Helper
{
    public class AngelCodeFont
    {
        public static void LoadFontFile(AtlasModel atlasmodel)
        {
            // example?
            //  https://github.com/cyotek/Cyotek.Drawing.BitmapFont

            BitmapFont _font = new BitmapFont();
            _font.Load(atlasmodel.AngelcodeFontFile);

            FontModel newfont = new FontModel();

            newfont.Id = (ushort)_font.FontSize;// (ushort)fontSettings.FontSize,
            newfont.size = _font.FontSize;// fontSettings.FontSize,
            newfont.lineheight = (int)(_font.LineHeight); // glyphHeight, // 22,
            newfont.spacelength = (int)(_font.FontSize * 0.6f); //FIXME ----------  (int)(glyphWidth * 0.6f), //todo ?
            newfont.baseline = _font.BaseHeight;// 0,
                                                   // newfont.kerning = _font.kern - 0.5f,
                                                   //  newfont.monowidth = _font.mono fontSettings.FontSize + 1,
            newfont.letterspacing = 0;
            
          //  newfont.rangeFrom = _font.Characters[0];
          //  newfont.rangeTo = _font.Characters[_font.Characters.Length - 1];

            foreach (var character in _font.Characters)
            {  
                newfont.SetGlyph(character.Key.ToString(),new Glyph() {
                     
                    advance = character.Value.XAdvance
                    , height = character.Value.Bounds.Height
                    , width = character.Value.Bounds.Width
                    , X = character.Value.Bounds.X
                   , Y = character.Value.Bounds.Y
                });
                newfont.SetVerticalOffset(character.Key.ToString(), character.Value.Offset.Y);
                newfont.offset = new FontOffset()
                {
                    x = character.Value.Offset.X,
                    y = character.Value.Offset.Y
                };
              //  newfont.spacelength = character.Value.
            }

            foreach (var kerning in _font.Kernings)
            {
                //if(kerning.Key.FirstCharacter != 'o' && kerning.Key.FirstCharacter != 'v')
                //{
                //    continue;
                //}
                newfont.SetKerning(kerning.Key.FirstCharacter.ToString(), new Kerning() { KerningValue = kerning.Value, RightGlyphID = kerning.Key.SecondCharacter });
            }


            atlasmodel.Fonts.Add(newfont);
        }
    }
}
