using System;
using System.Collections.Generic;
using System.Text;
using VEX.Model.UI;

namespace VEX.Core.Shared.Model.UI.Helper
{
    class GorillaData
    {
        private string m_PathToGorillaFile;
        private string m_TexturePath;

        private string m_AlphabetFile;
        private SquareSize m_SquareTextureSize;
        private string m_PathToFontGorillaFile;
        private string m_ImageExtensions;
        private string m_FontImagePath;
        private string m_ImageFolder;

        public string AlphabetFile { get { return m_AlphabetFile; } set { m_AlphabetFile = value; } }
        public SquareSize SquareTextureSize { get { return m_SquareTextureSize; } set { m_SquareTextureSize = value; } }
        public string PathToFontGorillaFile { get { return m_PathToFontGorillaFile; } set { m_PathToFontGorillaFile = value; } }
        public string ImageExtensions { get { return m_ImageExtensions; } set { m_ImageExtensions = value; } }
        public string FontImagePath { get { return m_FontImagePath; } set { m_FontImagePath = value; } }
        public string ImageFolder { get { return m_ImageFolder; } set { m_ImageFolder = value; } }


        public string GorillaFile { get { return m_PathToGorillaFile; } set { m_PathToGorillaFile = value; } }
        public string Texture { get { return m_TexturePath; } set { m_TexturePath = value; } }
    }
}
