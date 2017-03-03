using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows.Controls;
using System.Windows.Input;
using System.Xml.Serialization;
using Microsoft.Practices.Unity;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using System.Windows;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using VEX.Service.Scene;
using VEX.Interface.Scene.Services;
using VEF.Interfaces.Services;
using VEX.Interface.Scene;
using VEF.Interfaces.Controls;
using VEF.Core.Interface.Service;
using VEX.IDAL;
using VEX.Core.Shared.Interface.Net;
using VEF;
using VEX.Core.Model.Services;
using VEX.Interface.DAL;
using VEF.DAL.Interface;
using VEX.Core.ViewModel;
using VEX.Core.Model;
using Module.PFExplorer.Service;
using System.Collections.Specialized;
using VEX.Core.Shared.Service.Scene;
using VEX.Core.Shared.Model.UI;
using VEF.Model.Services;
using VEX.Model.UI.FBufferObject;
using System.IO;
using VEX.Core.Shared.Model.UI.Helper;
using VEF.View.Types;
using System.Drawing;
using VEX.Core.Shared.Model.UI.Fonts;
using System.Runtime.Serialization;

namespace VEX.Model.UI
{
    [DataContract]
    public enum SquareSize : uint
    {
        [EnumMember]
        SS_0 = 0,
        [EnumMember]
        SS_8 = 8,
        [EnumMember]
        SS_16 = 16,
        [EnumMember]
        SS_32 = 32,
        [EnumMember]
        SS_64 = 64,
        [EnumMember]
        SS_128 = 128,
        [EnumMember]
        SS_256 = 256, //value need for canvas size!
        [EnumMember]
        SS_512 = 512,
        [EnumMember]
        SS_1024 = 1024,
        [EnumMember]
        SS_2048 = 2048,
        [EnumMember]
        SS_4096 = 4096,
    }

    [KnownType(typeof(FB_UI_Atlas))]
    [KnownType(typeof(SpriteModel))]
    [KnownType(typeof(FontModel))]
    [DataContract(IsReference = true)]
    public class AtlasModel : ProjectItemModel
    {
        private string _TargetFbbinFile;
        private FontSystem _FontSystem;
        private SourceItem _SourceItem;
        private SquareSize _TextureWidth;
        private SquareSize _TextureHeight;

        private ObservableCollection<System.Windows.UIElement> mRectangles;

        [DataMember]
        [Category("Atlas generation settings")]
        [Editor(typeof(FilePathEditor), typeof(FilePathEditor))]
        public string AngelcodeFontFile { get; set; }

        [DataMember]
        public FontSystem FontSystem { get { if (_FontSystem == null) _FontSystem = new FontSystem(); return _FontSystem; } set { _FontSystem = value; } }

        [Category("Atlas generation settings")]
        public string Characters { get { return _FontSystem.Characters; } set { _FontSystem.Characters = value; RaisePropertyChanged("Characters"); } }

        public ObservableCollection<System.Windows.UIElement> Rectangles
        {
            get
            {
                if (mRectangles == null)
                    mRectangles = new ObservableCollection<UIElement>(); return mRectangles;
            }
        }

        [DataMember]
        [Category("Atlas generation settings")]
        public string TargetFbbinFile { get { return _TargetFbbinFile; } set { _TargetFbbinFile = value; RaisePropertyChanged("TargetFbbinFile"); } }

        [Category("Atlas generation settings")]
        [DataMember]
        public SquareSize TextureWidth
        {
            get { return _TextureWidth; }
            set { _TextureWidth = value; RaisePropertyChanged("TextureWidth"); }
        }

        [DataMember]
        [Category("Atlas generation settings")]
        public SquareSize TextureHeight
        {
            get { return _TextureHeight; }
            set { _TextureHeight = value; RaisePropertyChanged("TextureHeight"); }
        }


        [DataMember]
        [Category("Generated Atlas")]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        public ObservableCollection<SpriteModel> Sprites { get { return FB_UI_Atlas.Sprites; } set { FB_UI_Atlas.Sprites = value; RaisePropertyChanged("Sprites"); } }

        [DataMember]
        [Category("Generated Atlas")]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        public ObservableCollection<FontModel> Fonts { get { return FB_UI_Atlas.Fonts; } set { FB_UI_Atlas.Fonts = value; RaisePropertyChanged("Fonts"); } }

        //[Category("Generated Atlas")]
        //[ExpandableObject]
        //public Vector2 Whitepixel { get; set; }

        [DataMember]
        [Category("Atlas generation settings")]
        [Editor(typeof(FilePathEditor), typeof(FilePathEditor))]
        public string ImageFolder { get; set; }

        [DataMember]
        [Category("Atlas generation settings")]
        public string ImageExtensions { get; set; }

        [DataMember]
        public uint AtlasID { get; set; }

        public bool Watch { get; set; }

        #region INETID
        
        [Browsable(false)]
        private IFBObject FBObject { get; set; } //{ return FB_SceneNode; } }

        [ExpandableObject]
        [DataMember]
        public FB_UI_Atlas FB_UI_Atlas { get { return FBObject as FB_UI_Atlas; } set { FBObject = value; } }


        #endregion

        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>();

              //View needed!!  list.Add(new VEFMenuItem() { Header = "Generate Atlas", Command = new CmdGenerateAtlas(this) });
                list.Add(new VEFMenuItem() { Header = "Generate FB File", Command = new CmdGenFBAtlasFile(this) });
                list.Add(new VEFMenuItem() { Header = "Load AngelCode File", Command = new CmdLoadAngelCodeFontFile(this) });
                //     list.Add(new VEFMenuItem() { Header = "Load Gorilla File", Command = new CmdLoadGorillaFile(this) });

                return list;
            }
        }

        public AtlasModel()
        {
            _TextureHeight = new SquareSize();
            _TextureWidth = new SquareSize();

            Name = typeof(AtlasModel).Name;
            FBObject = new FB_UI_Atlas();
            
            Name = "Atlas NEW";
            ContentID = "AtlasID:##:";

            _SourceItem = new SourceItem()
            {
                //   SceneItem = Parent
            };
        }


        #region contentmodel

        internal void SetLocation(object location)
        {
            this.Location = location;
            RaisePropertyChanged("Location");
        }

        internal void SetDirty(bool value)
        {
            this.IsDirty = value;
        }

        #endregion
    }

    public class CmdGenFBAtlasFile : ICommand
    {
        private AtlasModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            var fbData = mpm.FB_UI_Atlas.CreateFBData();

            using (FileStream fileStream = new FileStream(@"F:\Projekte\coop\XGame\data\dbData\UI\TestAtlas.fbbin", FileMode.Create))
            {
                // Write the data to the file, byte by byte.
                for (int i = 0; i < fbData._fbData.Length; i++)
                {
                    fileStream.WriteByte(fbData._fbData[i]);
                }

                // Set the stream position to the beginning of the file.
                fileStream.Seek(0, SeekOrigin.Begin);

                // Read and verify the data.
                for (int i = 0; i < fileStream.Length; i++)
                {
                    if (fbData._fbData[i] != fileStream.ReadByte())
                    {
                        Console.WriteLine("Error writing data.");
                        return;
                    }
                }
                Console.WriteLine("The data was written to {0} " +
                    "and verified.", fileStream.Name);

            }
        }

        public CmdGenFBAtlasFile(AtlasModel pm)
        {
            mpm = pm;
        }
    }

    public class CmdGenerateAtlas : ICommand
    {
        private AtlasModel mpm;
        public event EventHandler CanExecuteChanged;

        Bitmap _packedImage;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            mpm.FB_UI_Atlas.Sprites.Clear();
            mpm.Rectangles.Clear();
            mpm.FB_UI_Atlas.Fonts.Clear();

            FontSettings fontSettings = new FontSettings();

            MaxRectsBinPack binPack = new MaxRectsBinPack((int)mpm.TextureWidth, (int)mpm.TextureHeight, false);

            //fontsize 20
            mpm.FontSystem.GenerateFont(mpm.Rectangles,
                                       mpm.FB_UI_Atlas.Fonts,
                                        binPack,
                                      fontSettings);

            //fontsize 40
            fontSettings = new FontSettings()
            {
                FontSize = 40
            };

            mpm.FontSystem.GenerateFont(mpm.Rectangles,
                                      mpm.FB_UI_Atlas.Fonts,
                                      binPack,
                                      fontSettings);


            AtlasHelper.GenAtlas(binPack, mpm.Rectangles, mpm.FB_UI_Atlas.Sprites, mpm.ImageFolder, mpm.ImageExtensions, mpm.TextureWidth, mpm.TextureHeight);

        }

        public CmdGenerateAtlas(AtlasModel pm)
        {
            mpm = pm;
        }
    }

    public class CmdLoadAngelCodeFontFile : ICommand
    {
        private AtlasModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            AngelCodeFont.LoadFontFile(mpm); //.LoadAngelCodeFont(@"F:\Projekte\coop\XGame\data\assets\test.fnt", test);

            //mpm.FB_UI_Atlas.Sprites = test.Sprites;
            //mpm.FB_UI_Atlas.Fonts = test.Fonts;
        }

        public CmdLoadAngelCodeFontFile(AtlasModel pm)
        {
            mpm = pm;
        }
    }

    public class CmdLoadGorillaFile : ICommand
    {
        private AtlasModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            GorillaModel test = new GorillaModel();
            FileLoader.LoadGorillaFont(@"F:\Projekte\coop\XGame\data\assets\XEngine.gorilla", test);

            mpm.Sprites = test.Sprites;
            mpm.Fonts = test.Fonts;
        }

        public CmdLoadGorillaFile(AtlasModel pm)
        {
            mpm = pm;
        }
    }
}
