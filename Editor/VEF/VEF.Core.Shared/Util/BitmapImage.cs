using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;
using VEF.Interfaces.Base;

namespace VEF.Core.WPF.Util
{
    public class ImageSource : IImageSource
    {
        public BitmapImage Source { get; set; }
    }
}
