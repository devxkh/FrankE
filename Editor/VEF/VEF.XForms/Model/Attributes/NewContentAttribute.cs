using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace VEF.Model.Attributes
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = true, Inherited = false)]
    public class NewContentAttribute : Attribute
    {
        public NewContentAttribute(string display, int priority, string description = "", string imageSource = "")
        {
            this.Display = display;
            if (!string.IsNullOrEmpty(imageSource))
            {
                _image = LoadFromResource(imageSource); //new BitmapImage(new Uri(imageSource));
            }
            this.Priority = priority;
            this.Description = description;
        }

        public string Display { get; private set; }

     //   public ImageSource ImageSource { get; private set; }

        private byte[] _image;

        public byte[] ImageSource
        {
            get { return _image; }
        }

        private static byte[] LoadFromResource(string name)
        {
            //todo
            //http://stackoverflow.com/questions/12512239/how-do-i-work-with-images-in-a-portable-class-library-targeting-windows-store-ap
            //using (Stream stream = typeof(NewContentAttribute).GetType().Assembly.GetManifestResourceStream("Portable." + name))
            //{
            //    MemoryStream buffer = new MemoryStream();
            //    stream.CopyTo(buffer);

            //    return buffer.ToArray();
            //}
            return null;
        }

        public int Priority { get; private set; }

        public string Description { get; private set; }
    }
}
