using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using VEF.Interfaces.Services;
using VEX.Model.UI;

namespace VEX.Core.Shared.Model.UI.Helper
{
    class AtlasHelper
    {
        public static void GenAtlas(MaxRectsBinPack binPack,
            ObservableCollection<System.Windows.UIElement> list,
            ObservableCollection<SpriteModel> oc,
            string pathToImageFolder,
            string searchFilext,
            SquareSize width,
            SquareSize height)
        {
           // MaxRectsBinPack test = new MaxRectsBinPack((int)width, (int)height, false);

            foreach (String imageFile in Directory.GetFiles(pathToImageFolder, searchFilext))
            {
                System.Drawing.Image image = System.Drawing.Image.FromFile(imageFile);
                Rect newPos = binPack.Insert(image.Width, image.Height, MaxRectsBinPack.FreeRectChoiceHeuristic.RectBestLongSideFit);

                Rectangle testRect = new Rectangle
                {
                    Stroke = Brushes.LightBlue,
                    StrokeThickness = 0
                };

                ImageBrush ib = new ImageBrush();
                BitmapImage bmi = new BitmapImage(new Uri(imageFile, UriKind.Absolute));
                ib.ImageSource = bmi;
                testRect.Fill = ib;

                testRect.Width = newPos.Width;
                testRect.Height = newPos.Height;

                Canvas.SetLeft(testRect, newPos.Left);
                Canvas.SetTop(testRect, newPos.Top);

                list.Add(testRect);

                // canvas.Children.Add(testRect);

                SpriteModel newSprite = new SpriteModel()
                {
                    Path = imageFile,
                    Rectangle = testRect,
                    Name = System.IO.Path.GetFileName(imageFile),
                    posX = (int)Math.Ceiling(newPos.Left),
                    posY = (int)Math.Ceiling(newPos.Top),
                    width = (int)Math.Ceiling(newPos.Width),
                    height = (int)Math.Ceiling(newPos.Height)
                };
               
                //newSprite.Path = imageFile;
                //newSprite.Rectangle = testRect;

                oc.Add(newSprite);

                //pictureBox.Width = image.Width;
                //pictureBox.Height = image.Height;
                //pictureBox.Image = image;
            }
        }
    }
}
