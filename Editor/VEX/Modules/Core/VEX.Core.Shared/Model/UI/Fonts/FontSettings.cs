using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;

namespace VEX.Core.Shared.Model.UI.Fonts
{
    public class FontSettings
    {
        public int OutlineWidth = 0;
        public int FontSize = 20;
        //public static int iTileHeight = 24;
        //public static int iTileWidth = 24;
        public int ImageHeight = 512;
        public int ImageWidth = 512;
        public int GRenderMode = 0;
        public int ImageCount = 1;
        public Color BgColor = Color.Transparent;
        public Color PenColor = Color.White;
        public Color ShadowColor = Color.Gray;
        public string TextStrings = "";
        public string FontName = @"F:\Projekte\coop\XTools\fontgen\Release\arial.ttf";
        public bool UseUnlimitHeight = false;
        public bool OptmizeAlpha = false;
        public ImageFormat globalSaveFmt = ImageFormat.Png;


        public int relativePositionX = 0;
        public int relativePositionY = 0;
    }
}
