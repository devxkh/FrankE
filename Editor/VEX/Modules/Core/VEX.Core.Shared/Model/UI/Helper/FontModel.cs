using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Linq;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEX.Core.Shared.Model.UI.Helper;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations;
using System.Runtime.Serialization;

namespace VEX.Core.Shared.Model.UI
{
    [DataContract]
    public struct FontOffset
    {
        [DataMember]
        public int x { get; set; }

        [DataMember]
        public int y { get; set; }
    }

    [KnownType(typeof(FontData))]
    [DataContract(IsReference = true)]
    public class FontModel : PItem
    {
        [DataMember]
        [Category("FontModel")]
        public ushort Id { get; set; }

        [DataMember]
        [Category("FontModel")]
        public int size { get; set; }

        [DataMember]
        [Category("FontModel")]
        public int lineheight { get; set; }

        [DataMember]
        [Category("FontModel")]
        public int spacelength { get; set; }

        [DataMember]
        [Category("FontModel")]
        public int baseline { get; set; }

        [DataMember]
        [Category("FontModel")]
        public float kerning { get; set; }

        [DataMember]
        [Category("FontModel")]
        public int letterspacing { get; set; }

        [DataMember]
        [Category("FontModel")]
        public float lineSpacing { get; set; }

        [DataMember]
        [Category("FontModel")]
        public int monowidth { get; set; }

        [DataMember]
        [Category("FontModel")]
        public int rangeFrom { get; set; }

        [DataMember]
        [Category("FontModel")]
        public int rangeTo { get; set; }

        [DataMember]
        [Category("FontModel")]
        public FontOffset offset { get; set; }

        [Display(AutoGenerateField = false)]
        [Category("FontModel")]
        [DisplayName("FontData")]
        [DataMember]
        public override CollectionOfIItem Items { get { return base.Items; } set { base.Items = value; } }


        public FontModel()
        {
            offset = new FontOffset();
        }


        private uint ConvertToGlyphInde(string character)
        {
            uint charAsUint = Convert.ToUInt32(character[0]);
            return charAsUint;
        }

        public void SetGlyph(string character, Glyph glyph)
        {
            uint characterAsUint = ConvertToGlyphInde(character);

            var font = Items.Where(x => (x as FontData).CharacterAsUint == characterAsUint);
            if (font.Any())
            {
                (font.First() as FontData).Glyph = glyph;
            }
            else
            {
                Items.Add(new FontData() { Name = character, Character = character, CharacterAsUint = characterAsUint, Glyph = glyph });
            }
        }

        public void SetVerticalOffset(string character, int offset)
        {
            uint characterAsUint = ConvertToGlyphInde(character);

            var font = Items.Where(x => (x as FontData).CharacterAsUint == characterAsUint);
            if (font.Any())
                (font.First() as FontData).VerticalOffset = offset;
            else
                Items.Add(new FontData() { Name = character, Character = character, CharacterAsUint = characterAsUint, VerticalOffset = offset });
        }

        public void SetKerning(string character, Kerning kerning)
        {
            uint characterAsUint = ConvertToGlyphInde(character);

            var font = Items.Where(x => (x as FontData).CharacterAsUint == characterAsUint);
            if (font.Any())
                (font.First() as FontData).Kerning.Add(kerning);
            else
                Items.Add(new FontData() { Name = character, Character = character, CharacterAsUint = characterAsUint, Kerning = new ObservableCollection<Kerning>() { kerning } });
        }
    }
}
