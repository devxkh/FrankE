using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;
using System.Xml.Serialization;
using VEF.Utils;
using VEX.Core.Shared.Model.UI.Helper;

namespace VEX.Core.Shared.Model.UI.Fonts
{
    [DataContract]
    public class FontSystem : ViewModelBase
    {
        private ObservableCollection<System.Windows.UIElement> _uiElemetList;
        private ObservableCollection<FontModel> _fontList;
        private MaxRectsBinPack _MaxRectsBinPack;
        private FontSettings _FontSettings;

        private string _Characters;

        public System.Windows.Controls.Image Image { get; set; }

        [DataMember]
        public string Characters
        {
            get
            {
                if (_Characters == null)
                    _Characters = @"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()[]{}<>-=_+,.:;?'\/|\\`~öäüÄÖÜ";
                return _Characters;
            }
            set { _Characters = value; RaisePropertyChanged("Characters"); }
        }

        public void GenerateFont(ObservableCollection<System.Windows.UIElement> list,
                                ObservableCollection<FontModel> fontList,
                                MaxRectsBinPack maxRectsBinPack,
                                FontSettings fontSettings)
        {
            _FontSettings = fontSettings;
            _MaxRectsBinPack = maxRectsBinPack;
            _fontList = fontList;
            _uiElemetList = list;
            string message = "";
            bool result = checkBeforeRender(ref message);
            if (!result)
            {
                MessageBox.Show(message);
                return;
            }
            AsynDisplayImage();
        }


        private void AsynDisplayImage()
        {
            //ThreadPool.QueueUserWorkItem(o =>
            //{
            //    Application.Current.Dispatcher.BeginInvoke(
            //        DispatcherPriority.SystemIdle,
            //        new Action(() =>
            //        {
                        //Open a new thread pool execution draw
                        BMDrawer bmd = new BMDrawer();
                       // string teststrings = characterTextBox.Text;

                        Bitmap bmp = bmd.test_draw(_uiElemetList,_fontList, _MaxRectsBinPack, Characters, _FontSettings);
                        BitmapImage cbmp = BitmapToBitmapImage(bmp);
                        Image.Height = cbmp.Height;
                        Image.Width = cbmp.Width;
                        Image.Source = cbmp;
                        //if (checkboxShowLine.IsChecked == true)
                        //{
                        //    DrawingVisual drawingVisual = new DrawingVisual();
                        //    using (DrawingContext drawingContext = drawingVisual.RenderOpen())
                        //    {
                        //        //
                        //        // ... draw on the drawingContext
                        //        //
                        //        System.Windows.Media.Pen pen = new System.Windows.Media.Pen(System.Windows.Media.Brushes.Red, (double)0.3f);
                        //        drawingContext.DrawImage(Image.Source, new Rect(0, 0, Image.Source.Width, Image.Source.Height));
                        //        int x_lines = (int)Math.Round((float)(int)Image.Width / (float)FontSettings.iTileWidth);

                        //        int y_lines = (int)Math.Round((float)(int)Image.Height / (float)FontSettings.iTileHeight); ;
                        //        for (int i = 0; i < x_lines + 1; i++)
                        //        {
                        //            drawingContext.DrawLine(pen, new System.Windows.Point(i * FontSettings.iTileWidth, 0),
                        //                new System.Windows.Point(i * FontSettings.iTileWidth, (float)(int)Image.Height));
                        //        }
                        //        for (int i = 0; i < y_lines + 1; i++)
                        //        {
                        //            drawingContext.DrawLine(pen, new System.Windows.Point(0, i * FontSettings.iTileHeight),
                        //                new System.Windows.Point((float)(int)Image.Width, i * FontSettings.iTileHeight));
                        //        }
                        //        drawingContext.Close();
                        //        RenderTargetBitmap nbmp = new RenderTargetBitmap((int)Image.Width, (int)Image.Height, 96.0, 96.0, PixelFormats.Default);
                        //        nbmp.Render(drawingVisual);
                        //        Image.Source = nbmp;
                        //    }
                        //}

                 //   })
            //   );
            //});
        }

        private BitmapImage BitmapToBitmapImage(System.Drawing.Bitmap bmp)
        {
            BitmapImage bitmapImage = new BitmapImage();
            using (System.IO.MemoryStream ms = new System.IO.MemoryStream())
            {
                bmp.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = ms;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();
                bitmapImage.Freeze();
            }

            return bitmapImage;
        }

        private bool checkBeforeRender(ref string message)
        {
            bool result = true;
            //int currentTileWidth = FontSettings.iTileHeight;
            //int currentTileHeight = FontSettings.iTileHeight;
            //int currentImageHeight = FontSettings.iImageHeight;
            //int currentImageWidth = FontSettings.iImageWidth;
            //System.Drawing.Color currentBgColor = FontSettings.cBgColor;
            //System.Drawing.Color currentPenColor = FontSettings.cPenColor;
            //bool bUseUHeight = FontSettings.bUseUnlimitHeight;
            //if (bUseUHeight)
            //{
            //    int currentStringLength = Characters.Length;
            //    currentImageHeight = (currentStringLength / (currentImageWidth / currentTileWidth)) * currentTileHeight;
            //    if ((currentStringLength % (currentImageWidth / currentTileWidth)) != 0)
            //    {
            //        currentImageHeight += currentTileHeight;
            //    }
            //    FontSettings.iImageHeight = currentImageHeight;
            //}

            //if (FontSettings.iFontHeight < 8)
            //{
            //    result = false;
            //    message = "Error: Font Size too small.";
            //}
            //if ((currentImageHeight == 0) || (currentImageWidth == 0))
            //{
            //    result = false;
            //    message = "Error: Image can't set to zero";
            //}
            ////if ((currentImageHeight < currentTileHeight) || (currentImageWidth < currentTileWidth))
            ////{
            ////    result = false;
            ////    message = "Error: Image too small or Tile too large.";
            ////}
            //if (currentBgColor == currentPenColor)
            //{
            //    result = false;
            //    message = "Error: Pen Color can't be equal to background color";
            //}
            //if (!File.Exists(FontSettings.fFontName))
            //{
            //    result = false;
            //    message = "Error: true type font not found";
            //}
            return result;


        }

   
    }
}
