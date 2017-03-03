using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using VEX.Core.Shared.Model.UI;
using VEX.Core.Shared.Model.UI.Fonts;
using VEX.Core.Shared.Model.UI.Helper;
using VEX.Model.UI;

namespace VEX.Core.View.UI
{
    /// <summary>
    /// Interaktionslogik für AtlasView.xaml
    /// </summary>
    public partial class AtlasView : UserControl
    {

        public AtlasView()
        {
            InitializeComponent();
        }

        private Point startPoint;
        private Rectangle rect;
        private SpriteModel mNewDropElement;

        private void Canvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (!Keyboard.IsKeyDown(Key.N))
                return;

            startPoint = e.GetPosition(canvas);

            rect = new Rectangle
            {
                Stroke = Brushes.LightBlue,
                StrokeThickness = 1
            };
            Canvas.SetLeft(rect, startPoint.X);
            Canvas.SetTop(rect, startPoint.X);
            // canvas.Children.Add(rect);

            //  var dc = (this.DataContext as AtlasModel);

            mNewDropElement = new SpriteModel();
            mNewDropElement.Name = "NewDroppedEle";
            mNewDropElement.Rectangle = rect;

            ((AtlasModel)this.DataContext).Rectangles.Add(rect);
            ((AtlasModel)this.DataContext).Items.Add(mNewDropElement);
        }


        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Released || rect == null)
                return;

            var pos = e.GetPosition(canvas);

            var x = Math.Min(pos.X, startPoint.X);
            var y = Math.Min(pos.Y, startPoint.Y);

            var w = Math.Max(pos.X, startPoint.X) - x;
            var h = Math.Max(pos.Y, startPoint.Y) - y;

            rect.Width = w;
            rect.Height = h;

            Canvas.SetLeft(rect, x);
            Canvas.SetTop(rect, y);

            //    canvas.Children.Add(rect);
            mNewDropElement.posX = (int)x;
            mNewDropElement.posY = (int)y;
            mNewDropElement.width = (int)w;
            mNewDropElement.height = (int)h;

        }


        private void Canvas_MouseUp(object sender, MouseButtonEventArgs e)
        {
            rect = null;
        }

        private void canvas_PreviewMouseMove(object sender, MouseEventArgs e)
        {

        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var mpm = ((AtlasModel)this.DataContext);

                mpm.Sprites.Clear();
                mpm.Rectangles.Clear();
            //    mpm.Fonts.Clear();

           //     FontSettings fontSettings = new FontSettings();

                MaxRectsBinPack binPack = new MaxRectsBinPack((int)mpm.TextureWidth, (int)mpm.TextureHeight, false);

                System.Drawing.Image image = System.Drawing.Image.FromFile(@"F:\Projekte\coop\XGame\_devFolder\Work\UI\Button_test-export.png");//mpm.AngelcodeFontFile);
                Rect newPos = binPack.Insert(image.Width, image.Height, MaxRectsBinPack.FreeRectChoiceHeuristic.RectBestLongSideFit);
                foreach(var fontModel in mpm.Fonts)
                {
                    foreach(FontData character  in fontModel.Items)
                    {
                        character.Glyph.X += (int)newPos.X;
                        character.Glyph.Y += (int)newPos.Y;
                    }

                }

                Rectangle testRect = new Rectangle
                {
                    Stroke = Brushes.LightBlue,
                    StrokeThickness = 0
                };
                ImageBrush ib = new ImageBrush();
                BitmapImage bmi = new BitmapImage(new Uri(@"F:\Projekte\coop\XGame\_devFolder\Work\UI\Button_test-export.png", UriKind.Absolute));
                ib.ImageSource = bmi;
                testRect.Fill = ib;


                testRect.Width = newPos.Width;
                testRect.Height = newPos.Height;

                Canvas.SetLeft(testRect, newPos.Left);
                Canvas.SetTop(testRect, newPos.Top);

                mpm.Rectangles.Add(testRect);
                //mpm.FontSystem.GenerateFont(mpm.Rectangles,
                //                           mpm.Fonts,
                //                            binPack,
                //                          fontSettings);

                //fontSettings = new FontSettings()
                //{
                //    FontSize = 40
                //};

                //mpm.FontSystem.GenerateFont(mpm.Rectangles,
                //                          mpm.FB_UI_Atlas.Fonts,
                //                          binPack,
                //                          fontSettings);


                AtlasHelper.GenAtlas(binPack, mpm.Rectangles, mpm.Sprites, mpm.ImageFolder, mpm.ImageExtensions, mpm.TextureWidth, mpm.TextureHeight);


                RenderTargetBitmap renderBitmap = new RenderTargetBitmap(
                   (int)canvas.Width, (int)canvas.Height,
                   96d, 96d, PixelFormats.Pbgra32);
                // needed otherwise the image output is black
                canvas.Measure(new Size((int)canvas.Width, (int)canvas.Height));
                canvas.Arrange(new Rect(new Size((int)canvas.Width, (int)canvas.Height)));

                renderBitmap.Render(canvas);

                //JpegBitmapEncoder encoder = new JpegBitmapEncoder();
                PngBitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(renderBitmap));

                using (FileStream file = File.Create(((AtlasModel)this.DataContext).FB_UI_Atlas.TextureName))
                {
                    encoder.Save(file);
                }
                
                var fbData = mpm.FB_UI_Atlas.CreateFBData();

                //@"F:\Projekte\coop\XGame\data\dbData\UI\TestAtlas.fbbin"
                using (FileStream fileStream = new FileStream(mpm.TargetFbbinFile, FileMode.Create))
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
            catch (Exception ex)
            {

            }
          
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            if(((AtlasModel)this.DataContext).FontSystem != null)
                ((AtlasModel)this.DataContext).FontSystem.Image = this._image;
        }
    }
}
