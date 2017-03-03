using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows;
using System.Linq;

namespace VEX.Core.Shared.Model.UI.Helper
{
    public class FileLoader
    {
        private static int convertToInt(String intString)
        {
            Int32 tmp = 0;
            Int32.TryParse(intString, out tmp);
            return tmp;

        }

        private static UInt16 convertToUShort(String intString)
        {
            UInt16 tmp = 0;
            UInt16.TryParse(intString, out tmp);
            return tmp;

        }
        private static uint convertToUInt(String intString)
        {
            UInt32 tmp = 0;
            UInt32.TryParse(intString, out tmp);
            return tmp;

        }
        private static float convertToFloat(String intString)
        {
            float tmp = 0;
            float.TryParse(intString, out tmp);
            return tmp;

        }

        public static void LoadFont(GorillaModel gorilla, StreamReader sr, string line)
        {
            //// TODO load Angelcode's BmFont tool.

            FontModel font = new FontModel();

            //font.size = convertToInt(line.Replace("[Font.", "").Replace("]", ""));
            //font.Id = convertToUShort(line.Replace("[Font.", "").Replace("]", ""));
            //font.Name = line;
            while (!String.IsNullOrEmpty(line = sr.ReadLine()))
            {
                if (line.StartsWith("info"))
                {
                    string[] info = line.Split(' ');
                    font.size = convertToInt(info[2].Split('=')[1]);
                    font.Id = convertToUShort(info[2].Split('=')[1]);
                   // font.padding = convertToUShort(info[2].Split('=')[1]);
                   // font.spacing = convertToUShort(info[2].Split('=')[1]);
                }
                else if (line.StartsWith("common"))
                {
                    string[] info = line.Split(' ');
                    font.lineheight = convertToInt(info[1].Split('=')[1]);
                }


                //else if (line.StartsWith("glyph"))
                //{
                //    String[] glyphString = line.Split(' ');
                //    font.SetGlyph(convertToUInt(glyphString[0].Split('_')[1]), new Glyph() { X = convertToInt(glyphString[1]), Y = convertToInt(glyphString[2]), width = convertToInt(glyphString[3]), height = convertToInt(glyphString[4]), advance = convertToInt(glyphString[5]) }, "");
                //}
                //else if (line.Contains("verticaloffset_"))
                //{
                //    String[] verticaloffset_String = line.Split(' ');
                //    font.SetVerticalOffset(convertToUInt(verticaloffset_String[0].Split('_')[1]), convertToInt(verticaloffset_String[1]));
                //}
                //else if (line.Contains("kerning_"))
                //{
                //    String[] kerning_String = line.Split(' ');
                //    font.SetKerning(convertToUInt(kerning_String[0].Split('_')[1]), new Kerning() { RightGlyphID = convertToUInt(kerning_String[1]), KerningValue = convertToInt(kerning_String[2]) });
                //}
                //glyph_33 0 0 8 21
                //verticaloffset_33 -11
                //            glyph_121 101 270 25 37
                //verticaloffset_121 -18
                //kerning_121 65 1
                //kerning_121 76 1
                //kerning_121 84 2
                //kerning_121 86 1


            }

            gorilla.Fonts.Add(font);
            gorilla.Items.Add(font);
        }

        public static void LoadSprites(GorillaModel gorilla, StreamReader sr, string line)
        {
          
            while ((line = sr.ReadLine()) != null)
            {
                if (line.Contains("[Texture]") || line.Contains("[Font."))
                    return;

                if (string.IsNullOrEmpty(line))
                    continue;

                var spriteTextData = line.Split(' ');

                SpriteModel newSprite = new SpriteModel();

                newSprite.Name = spriteTextData[0];
                newSprite.posX = convertToInt(spriteTextData[1]);
                newSprite.posY = convertToInt(spriteTextData[2]);
                newSprite.width = convertToInt(spriteTextData[3]);
                newSprite.height = convertToInt(spriteTextData[4]);

                gorilla.Sprites.Add(newSprite);
            }

        }


        public static void LoadTexture(GorillaModel gorilla, StreamReader sr)
        {
            string line = null;
            while (!String.IsNullOrEmpty(line = sr.ReadLine()))
            {
                if (line.Contains("[Sprites]") || line.Contains("[Font."))
                    return;

                if (line.Contains("file"))
                {
                    gorilla.GorillaTexture.file = line;
                }
                else if (line.Contains("whitepixel"))
                {
                    String[] whitePixel = line.Split(' ');
                    gorilla.GorillaTexture.whitepixel = new Position() { x = convertToInt(whitePixel[1]), y = convertToInt(whitePixel[2]) };
                }


            }
            //[Texture]
            //file arial.png
            //whitepixel 34 22
        }

        public static void LoadGorillaFont(String filepath, GorillaModel gorilla)
        {
            // create reader & open file
            using (StreamReader sr = new StreamReader(filepath))
            {
                string line;

                while ((line = sr.ReadLine()) != null)
                {
                    Console.WriteLine(line);  // read a line of text

                    //load font data
                    if (line.Contains("[Font."))
                    {
                        LoadFont(gorilla, sr, line);
                    }

                    if (line.Contains("[Sprites]"))
                    {
                        LoadSprites(gorilla, sr, line);
                    }

                    if (line.Contains("[Texture]"))
                    {
                        LoadTexture(gorilla, sr);
                    }
                }

                // close the stream
                sr.Close();
            }
        }

        //public static string GenerateGorillaCode(GorillaModel gorillaModel)
        //{
        //    string code = "";
        //    try
        //    {
        //        // create a writer and open the file
        //        //using (StreamWriter writer = File.CreateText(filename))
        //        //{
        //        //    //Texture
        //        //    await writer.WriteLineAsync("[Texture]");
        //        //    await writer.WriteLineAsync("file " + gorillaModel.TextureName);
        //        //     await writer.WriteLineAsync("whitepixel 510 510");
        //        code += "[Texture]" + Environment.NewLine;
        //        code += "file " + gorillaModel.TextureName + Environment.NewLine;
        //        code += "whitepixel 510 510" + Environment.NewLine;

        //        //glyph_33 0 0 8 21
        //        //verticaloffset_33 -11
        //        //            glyph_121 101 270 25 37
        //        //verticaloffset_121 -18
        //        //kerning_121 65 1
        //        //kerning_121 76 1
        //        //kerning_121 84 2
        //        //kerning_121 86 1

        //        //fonts
        //        foreach (var font in gorillaModel.Fonts)
        //        {
        //            code += "[Font." + font.size + "]" + Environment.NewLine;

        //            foreach (var item in font.Items)
        //            {
        //                var fontItem = item as FontData;
        //                if (fontItem.Glyph.X > 0)
        //                    code += "glyph_" + fontItem.Index + " " + fontItem.Glyph.X + " " + fontItem.Glyph.Y + " " + fontItem.Glyph.width + " " + fontItem.Glyph.height + Environment.NewLine;

        //                if (fontItem.VerticalOffset > 0)
        //                    code += "verticaloffset_" + fontItem.Index + " " + fontItem.VerticalOffset + Environment.NewLine;

        //                if (fontItem.Kerning.Any())
        //                {
        //                    foreach (var kerning in fontItem.Kerning)
        //                    {
        //                        code += "kerning_" + fontItem.Index + " " + kerning.RightGlyphID + " " + kerning.KerningValue + Environment.NewLine;
        //                    }
        //                }
        //            }
        //        }
        //        //[Texture]
        //        //file dejavu.png
        //        //whitepixel 510 510
        //        //[Font.14]
        //        //lineheight 22
        //        //spacelength 6
        //        // [Sprites]
        //        //  mousepointer 54 464 15 22

        //        //sprites 
        //        //  await writer.WriteLineAsync("[Sprites]");
        //        code += "[Sprites]" + Environment.NewLine;
        //        foreach (var item in gorillaModel.Items)//.Where(x => x.GorillaType == GorillaType.Sprite))
        //        {
        //            var gorillaItem = item as IGorillaItem;
        //            if (gorillaItem != null && gorillaItem.GorillaType == GorillaType.Sprite)
        //                code += gorillaItem.Name + " " + gorillaItem.X + " " + gorillaItem.Y + " " + gorillaItem.Width + " " + gorillaItem.Height + Environment.NewLine;
        //            // await writer.WriteLineAsync(item.Name + " " + item.X + " " + item.Y + " " + item.Width + " " + item.Height);

        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show("Error:" + ex.Message);
        //    }
        //    return code;

        //}
    }
}
