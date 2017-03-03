using SharpFont;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using VEX.Core.Shared.Model.UI.Helper;

namespace VEX.Core.Shared.Model.UI.Fonts
{
    public class Table
    {
        public XYWH[] XYWHS;
        public struct XYWH
        {
            public uint charid;
            public uint x_pos;
            public uint y_pos;
            public uint c_width;
            public uint c_height;
            public uint page_num;

        }
    }
    class BMDrawer
    {
        //FontSettings gSettings = new FontSettings();
        //string fontName = FontSettings.fFontName;

        //private int fontHeight = FontSettings.iFontHeight;
        ////private int tile_height = FontSettings.iTileHeight;
        ////private int tile_width = FontSettings.iTileWidth;
        //private int image_width = FontSettings.iImageWidth;
        //private int image_height = FontSettings.iImageHeight;
        //private string fTextStrings = FontSettings.fTextStrings;


        private enum render_mode
        {
            freetype_normal = 0,
            freetype_nearestneighbor = 1,
            freetype_drawtwice = 2,
            freetype_HighQualityBicubic = 3,
            freeyype_nosmoothing = 4
        };


        //string grender_mode = Enum.GetName(typeof(render_mode), FontSettings.iGRenderMode);
        //private System.Drawing.Color penColor = FontSettings.cPenColor;

        //private System.Drawing.Color shadowColor = FontSettings.cShadowColor;

        uint uchar2code(string current_char)
        {
            uint ucode = (uint)Char.ConvertToUtf32(current_char, 0);
            return ucode;
        }
        //public Table.XYWH[] GetXYWHTable(string fTextStrings)
        //{
        //    Library library = new Library();
        //    Face face = library.NewFace(fontName, 0);
        //    face.SetCharSize(0, this.fontHeight, 0, 72);


        //    List<Table.XYWH> tmp = new List<Table.XYWH>();
        //    StringReader fReader = new StringReader(fTextStrings);
        //    int img_nums;
        //    int chars_per_page = (image_width / tile_width) * (image_height / tile_height);
        //    if (fTextStrings.Length < (chars_per_page))
        //    {
        //        img_nums = 1;
        //    }
        //    else
        //    {
        //        img_nums = (fTextStrings.Length / chars_per_page);
        //        if ((fTextStrings.Length % chars_per_page) > 0)
        //        {
        //            img_nums = (fTextStrings.Length / chars_per_page) + 1;
        //        }
        //    }
        //    for (int i = 0; i < img_nums; i++)
        //    {
        //        int pos = 0;
        //        string currentString;
        //        if (i != img_nums - 1)
        //        {
        //            char[] buffer = new char[chars_per_page];
        //            fReader.Read(buffer, pos, chars_per_page);
        //            currentString = new string(buffer);
        //            pos += currentString.Length;
        //        }
        //        else
        //        {
        //            currentString = fReader.ReadToEnd();
        //        }
        //        currentString = currentString.Replace("\n", "");
        //        currentString = currentString.Replace("\r", "");

        //        int x = 0, y = 0;
        //        for (int n = 0; n < currentString.ToCharArray().Length; n++)
        //        {
        //            Table.XYWH currentXYWH = new Table.XYWH();
        //            currentXYWH.x_pos = (uint)x;
        //            currentXYWH.y_pos = (uint)y;
        //            currentXYWH.page_num = (uint)i + 1;
        //            string currentChar0 = currentString.ToCharArray()[n].ToString();
        //            uint char_code = uchar2code(currentChar0);
        //            uint glyphIndex = face.GetCharIndex(uchar2code(currentChar0));
        //            currentXYWH.charid = char_code; //set charid
        //            face.LoadChar((uint)glyphIndex, LoadFlags.Render, LoadTarget.Lcd);
        //            face.LoadGlyph((uint)glyphIndex, LoadFlags.Render, LoadTarget.Lcd);
        //            face.Glyph.RenderGlyph(RenderMode.Lcd);

        //            FTBitmap ftbmp = face.Glyph.Bitmap;
        //            if (ftbmp.Width == 0)
        //            {

        //                currentXYWH.c_width = (uint)tile_width;


        //            }
        //            else {
        //                float advance = (float)face.Glyph.Metrics.HorizontalAdvance;
        //                if (advance >= (float)tile_width)
        //                {
        //                    currentXYWH.c_width = (uint)tile_width;
        //                }
        //                else
        //                {
        //                    currentXYWH.c_width = (uint)face.Glyph.BitmapLeft + (uint)((float)face.Glyph.Metrics.HorizontalBearingX +
        //                                                                            (float)FontSettings.relativePositionX +
        //                                                                            (float)face.Glyph.Metrics.Width);
        //                }
        //            }
        //            //currentXYWH.c_width = (uint)((float)face.Glyph.Metrics.HorizontalBearingX + (float)face.Glyph.Metrics.Width);//set c_width
        //            if (char_code == (uint)32)
        //            {
        //                currentXYWH.c_width = (uint)tile_width / 2 - 1;
        //            }
        //            else if ((char_code <= (uint)0x3000) && (char_code >= (uint)0x7e))
        //            {
        //                currentXYWH.c_width = (uint)tile_width;

        //            }

        //            else if (char_code >= (uint)8000)
        //            {
        //                currentXYWH.c_width = (uint)tile_width;

        //            }
        //            currentXYWH.c_height = (uint)tile_height;
        //            tmp.Add(currentXYWH);
        //            x += this.tile_width;
        //            if (x + this.tile_width > this.image_width)
        //            {
        //                x = 0;
        //                y += this.tile_height;
        //            }

        //            ftbmp.Dispose();
        //        }
        //    }
        //    return tmp.ToArray();
        //}
        //public Bitmap[] DrawMultiImages(string fTextStrings)
        //{
        //    StringReader fReader = new StringReader(fTextStrings);
        //    int img_nums;
        //    int chars_per_page = (image_width / tile_width) * (image_height / tile_height);
        //    if (fTextStrings.Length < (chars_per_page))
        //    {
        //        img_nums = 1;
        //    }
        //    else
        //    {
        //        img_nums = (fTextStrings.Length / chars_per_page);
        //        if ((fTextStrings.Length % chars_per_page) > 0)
        //        {
        //            img_nums = (fTextStrings.Length / chars_per_page) + 1;
        //        }

        //    }

        //    Bitmap[] multi = new Bitmap[img_nums];
        //    for (int i = 0; i < img_nums; i++)
        //    {
        //        int pos = 0;
        //        string currentString;
        //        if (i != img_nums - 1)
        //        {
        //            char[] buffer = new char[chars_per_page];
        //            fReader.Read(buffer, pos, chars_per_page);
        //            currentString = new string(buffer);
        //            pos += currentString.Length;
        //        }
        //        else
        //        {
        //            currentString = fReader.ReadToEnd();
        //        }

        //        Bitmap currentbmp = test_draw(currentString);
        //        multi[i] = currentbmp;
        //    }
        //    return multi;
        //}
        public static Bitmap kPasteImage(Bitmap bmp, int newW, int newH, int kx, int ky)
        {
            //Interpolation Scaling Algorithm
            try
            {
                Bitmap b = new Bitmap(newW, newH);
                Graphics g = Graphics.FromImage(b);

                g.DrawImageUnscaled(bmp, kx, ky);
                g.Dispose();

                return b;
            }
            catch
            {
                return null;
            }
        }
        public static Bitmap kResizeImage(Bitmap bmp, int newW, int newH, System.Drawing.Drawing2D.InterpolationMode currnetMode)
        {
            //Interpolation Scaling Algorithm
            try
            {
                Bitmap b = new Bitmap(newW, newH);
                Graphics g = Graphics.FromImage(b);

                // Quality interpolation algorithm
                //g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.Bilinear;
                g.InterpolationMode = currnetMode;

                g.DrawImage(bmp, new Rectangle(0, 0, newW, newH), new Rectangle(0, 0, bmp.Width, bmp.Height), GraphicsUnit.Pixel);
                g.Dispose();

                return b;
            }
            catch
            {
                return null;
            }
        }

        public Bitmap gray2alpha(Bitmap cBmp)
        {
            Bitmap nBmp = new Bitmap((int)cBmp.Width, (int)cBmp.Height);
            System.Drawing.Color color;
            System.Drawing.Color colorResult;
            for (int i = 0; i < cBmp.Width; i++)
            {
                for (int j = 0; j < cBmp.Height; j++)
                {

                    color = cBmp.GetPixel(i, j);
                    int maxcolor = Math.Max(Math.Max(color.R, color.G), color.B);
                    if (!(color.A == 255))
                    {

                        maxcolor = color.A;
                    }

                    colorResult = System.Drawing.Color.FromArgb(maxcolor, 255, 255, 255);
                    nBmp.SetPixel(i, j, colorResult);

                }
            }

            return nBmp;
        }

        Rect getGlyphRect(Face face, string alphabet)
        {
            Rect rect = new Rect(0, 0, 0, 0);
            var slot = face.Glyph;
            var bitmap = slot.Bitmap;
            for (int i = 0; i < alphabet.Length; ++i)
            {
                // Load glyph
              //  char c = alphabet[i];
                string currentChar0 = alphabet.ToCharArray()[i].ToString();
                uint glyphIndex = face.GetCharIndex(uchar2code(currentChar0));

                face.LoadChar((uint)glyphIndex, LoadFlags.Render,LoadTarget.Lcd);
                // FT_Load_Char(face, c, FT_LOAD_RENDER);

                // Expand rectangle if necessary
                var Left = Math.Min(rect.Left, slot.BitmapLeft);
                var Top = Math.Max(rect.Top, slot.BitmapTop);
                var Right = Math.Max(rect.Right, (int)bitmap.Width - (int)slot.BitmapLeft);
                var Bottom = Math.Min(rect.Bottom, slot.BitmapTop - (int)bitmap.Rows);

                rect = new Rect(Left, Top, Right, Bottom);
            }
            return rect;
        }


        public Bitmap test_draw(ObservableCollection<System.Windows.UIElement> list,
                                                    ObservableCollection<FontModel> fontList,
                                                    MaxRectsBinPack binPack,
                                                      string alphabet,
                                                      FontSettings fontSettings)
        {



            alphabet = alphabet.Replace("\n", "");
            alphabet = alphabet.Replace("\r", "");
            Library library = new Library();
            Face face = library.NewFace(fontSettings.FontName, 0);

            // Find the largest glyph bounding rectangle
          //  Rect glyphRect = getGlyphRect(face, alphabet);
            //int glyphWidth = (int)Math.Ceiling(glyphRect.Width) + 4 * fontSettings.OutlineWidth;
            //int glyphHeight = (int)Math.Ceiling(glyphRect.Height) + 4 * fontSettings.OutlineWidth;
            int glyphWidth = 18 + 4 * fontSettings.OutlineWidth;
            int glyphHeight = 18 + 4 * fontSettings.OutlineWidth;

            //add new font

            FontModel newFont = new FontModel()
            {
                Id = (ushort)fontSettings.FontSize,
                size = fontSettings.FontSize,
                lineheight = glyphHeight, // 22,
                spacelength = (int)(glyphWidth * 0.6f), //todo ?
                baseline = 0,
                kerning = -0.5f,
                monowidth = fontSettings.FontSize + 1,
                letterspacing = 0,
                rangeFrom = alphabet[0],
                rangeTo = alphabet[alphabet.Length-1]
            };
            fontList.Add(newFont);


            Bitmap bmp = new Bitmap((int)Math.Ceiling((double)fontSettings.ImageWidth), (int)Math.Ceiling((double)fontSettings.ImageHeight));
            Graphics g = Graphics.FromImage(bmp);
            g.Clear(fontSettings.BgColor);
            //g.Clear(Color.Black);q
            int x = 0, y = 0;
            for (int i = 0; i < alphabet.ToCharArray().Length; i++)
            {
                string currentChar0 = alphabet.ToCharArray()[i].ToString();
                uint glyphIndex = face.GetCharIndex(uchar2code(currentChar0));
               

                if (fontSettings.FontSize <= 14)
                {
                    face.SetPixelSizes((uint)0, (uint)fontSettings.FontSize);
                    face.LoadGlyph(glyphIndex, LoadFlags.Default, LoadTarget.Normal);
                    face.Glyph.RenderGlyph(RenderMode.Normal);
                }
                else
                {
                    face.SetCharSize(0, fontSettings.FontSize, 0, 72);
                    face.LoadGlyph(glyphIndex, LoadFlags.ForceAutohint, LoadTarget.Lcd);
                    face.Glyph.RenderGlyph(RenderMode.Lcd);
                }

                //Get character alignment
                float left = (float)face.Glyph.Metrics.HorizontalBearingX;
                float right = (float)face.Glyph.Metrics.HorizontalBearingX + (float)face.Glyph.Metrics.Width;
                float top = (float)face.Glyph.Metrics.HorizontalBearingY;
                float bottom = (float)face.Glyph.Metrics.HorizontalBearingY + (float)face.Glyph.Metrics.Height;
                float FHT = fontSettings.FontSize;
                int FHD = (int)Math.Ceiling(FHT);
                int kx = x + face.Glyph.BitmapLeft;
                int ky = (int)Math.Round((float)y + (FHD - face.Glyph.BitmapTop));


                ////Select render mode (1 times or 2 times)
                //if (this.grender_mode == "freetype_nearestneighbor")
                //{
                //    face.SetCharSize(0, this.fontHeight * 2, 0, 72);
                //    face.LoadGlyph(glyphIndex, LoadFlags.ForceAutohint, LoadTarget.Lcd);
                //    face.Glyph.RenderGlyph(RenderMode.Lcd);
                //    FTBitmap ftbmp = face.Glyph.Bitmap;
                //    if (ftbmp.Width == 0)
                //    {
                //        x += this.tile_width;
                //        if (x + this.tile_width > this.image_width)
                //        {
                //            x = 0;
                //            y += this.tile_height;
                //        }
                //        continue;
                //    }

                //    Bitmap tmpBmp = ftbmp.ToGdipBitmap(this.penColor);

                //    tmpBmp = kPasteImage(tmpBmp, tile_width * 2, tile_height * 2, (int)face.Glyph.BitmapLeft,
                //                        (int)Math.Round(((float)this.fontHeight * 2 - face.Glyph.BitmapTop)));

                //    Bitmap cBmp = kResizeImage(tmpBmp, tmpBmp.Width / 2, tmpBmp.Height / 2, System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor);
                //    Bitmap nBmp = gray2alpha(cBmp);
                //    cBmp.Dispose();

                //    g.DrawImageUnscaled(nBmp, x + FontSettings.relativePositionX, y + FontSettings.relativePositionY);
                //    nBmp.Dispose();
                //}
                //else if (this.grender_mode == "freetype_HighQualityBicubic")
                //{
                //    face.SetCharSize(0, this.fontHeight * 2, 0, 72);
                //    face.LoadGlyph(glyphIndex, LoadFlags.ForceAutohint, LoadTarget.Lcd);
                //    face.Glyph.RenderGlyph(RenderMode.Lcd);
                //    FTBitmap ftbmp = face.Glyph.Bitmap;
                //    if (ftbmp.Width == 0)
                //    {
                //        x += this.tile_width;
                //        if (x + this.tile_width > this.image_width)
                //        {
                //            x = 0;
                //            y += this.tile_height;
                //        }
                //        continue;
                //    }

                //    Bitmap tmpBmp = ftbmp.ToGdipBitmap(this.penColor);

                //    tmpBmp = kPasteImage(tmpBmp, tile_width * 2, tile_height * 2, (int)face.Glyph.BitmapLeft,
                //        (int)Math.Round(((float)this.fontHeight * 2 - face.Glyph.BitmapTop)));

                //    Bitmap cBmp = kResizeImage(tmpBmp, tmpBmp.Width / 2, tmpBmp.Height / 2, System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic);
                //    Bitmap nBmp = gray2alpha(cBmp);
                //    cBmp.Dispose();

                //    g.DrawImageUnscaled(nBmp, x + FontSettings.relativePositionX, y + FontSettings.relativePositionY);
                //    nBmp.Dispose();

                //}
                //else if (this.grender_mode == "freetype_drawtwice")
                //{
                //    face.LoadGlyph(glyphIndex, LoadFlags.Default, LoadTarget.Normal);
                //    face.Glyph.RenderGlyph(RenderMode.Normal);
                //    FTBitmap ftbmp = face.Glyph.Bitmap;
                //    if (ftbmp.Width == 0)
                //    {
                //        x += this.tile_width;
                //        if (x + this.tile_width > this.image_width)
                //        {
                //            x = 0;
                //            y += this.tile_height;
                //        }
                //        continue;
                //    }
                //    Bitmap cBmp = ftbmp.ToGdipBitmap(this.penColor);
                //    Bitmap sBmp = ftbmp.ToGdipBitmap(this.shadowColor);

                //    Bitmap nBmp = gray2alpha(cBmp);
                //    cBmp.Dispose();

                //    g.DrawImageUnscaled(sBmp, kx + FontSettings.relativePositionX + 1, ky + FontSettings.relativePositionY + 1);//draw twice
                //    g.DrawImageUnscaled(nBmp, kx + FontSettings.relativePositionX, ky + FontSettings.relativePositionY);
                //    cBmp.Dispose();
                //    nBmp.Dispose();

                //}
                //else if (this.grender_mode == "freeyype_nosmoothing")
                //{
                //    face.SetPixelSizes((uint)0, (uint)this.fontHeight);
                //    face.LoadGlyph(glyphIndex, LoadFlags.Monochrome, LoadTarget.Mono);
                //    face.Glyph.RenderGlyph(RenderMode.Mono);
                //    FTBitmap ftbmp = face.Glyph.Bitmap;
                //    if (ftbmp.Width == 0)
                //    {
                //        x += this.tile_width;
                //        if (x + this.tile_width > this.image_width)
                //        {
                //            x = 0;
                //            y += this.tile_height;
                //        }
                //        continue;
                //    }
                //    Bitmap cBmp = ftbmp.ToGdipBitmap(this.penColor);
                //    g.DrawImageUnscaled(cBmp, kx + FontSettings.relativePositionX, ky + FontSettings.relativePositionY);
                //    cBmp.Dispose();
                //}

                //    int tile_width = 24;
                //int tile_height = FontSettings.iFontHeight;//24;
                ////else
                ////{
                FTBitmap ftbmp = face.Glyph.Bitmap;
                
                //    if (ftbmp.Width == 0)
                //    {
                //        x += tile_width;
                //        if (x + tile_width > this.image_width)
                //        {
                //            x = 0;
                //            y += tile_height;
                //        }
                //        continue;
                //    }


                Bitmap cBmp = ftbmp.ToGdipBitmap(fontSettings.PenColor);
                Bitmap nBmp = gray2alpha(cBmp);

                Rect newPos = binPack.Insert(cBmp.Width, cBmp.Height, MaxRectsBinPack.FreeRectChoiceHeuristic.RectBottomLeftRule);

                //DebugRectangle
                System.Windows.Shapes.Rectangle testRect = new System.Windows.Shapes.Rectangle
                {
                    Stroke = System.Windows.Media.Brushes.LightGreen,
                    StrokeThickness = 0
                };

                ImageBrush ib = new ImageBrush();
                //    cBmp.MakeTransparent();
                cBmp.Dispose();
                var source = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(nBmp.GetHbitmap(), IntPtr.Zero, Int32Rect.Empty,
                                                                                   System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions());
                nBmp.Dispose();
                ib.ImageSource = source;
                testRect.Fill = ib;
                testRect.Width = newPos.Width;
                testRect.Height = newPos.Height;
                Canvas.SetLeft(testRect, newPos.Left);
                Canvas.SetTop(testRect, newPos.Top);
                list.Add(testRect);
                
                Glyph newGlyph = new Glyph()
                {
                    X = (int)Math.Ceiling(newPos.Left),
                    Y = (int)Math.Ceiling(newPos.Top),
                    width = (int)Math.Ceiling(newPos.Width),
                    height = (int)Math.Ceiling(newPos.Height)      
                };
                newFont.SetGlyph(currentChar0, newGlyph);

                //if(glyphIndex == 33)
                //{

                //}
                // Construct KerningData
                for (int j = 0; j < alphabet.ToCharArray().Length; j++)
                {
                    string left_Char0 = alphabet.ToCharArray()[j].ToString();
                    uint left_glyphIndex = face.GetCharIndex(uchar2code(left_Char0));
                   
                    //if (left_glyphIndex == 45)
                    //{

                    //}
                    //char c1 = mAlphabet[i];
                    //FT_UInt c1Index = FT_Get_Char_Index(face, c1);
                    var delta = face.GetKerning(left_glyphIndex, glyphIndex, KerningMode.Default);
                
                    // KerningData kd = new KerningData(kern_currentChar0, currentChar0, delta.X.ToInt32() >> 6, 0, delta.Y.ToInt32() >> 6, 0);
                    if (left_glyphIndex == 0 || delta.X == 0) //no kerning
                        continue;
                    
                    Kerning newKerning = new Kerning();
                    newKerning.RightGlyphID = left_glyphIndex;
                    newKerning.KerningValue = delta.X.ToInt32() >> 6;
                    newFont.SetKerning(left_Char0, newKerning);

                 
                }

                newFont.SetVerticalOffset(currentChar0, ky);

                //cBmp.Dispose();
                //g.DrawImageUnscaled(nBmp, (int)Math.Ceiling(newPos.X) + fontSettings.relativePositionX, (int)Math.Ceiling(newPos.Y) + fontSettings.relativePositionY);
                //// g.DrawImageUnscaled(nBmp, kx + FontSettings.relativePositionX, ky + FontSettings.relativePositionY);
                //nBmp.Dispose();

            }
            g.Dispose();
            library.Dispose();
            return bmp;
        }
    }
}
