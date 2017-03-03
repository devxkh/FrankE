using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Windows.Shapes;
using VEF.Model.Services;
using System.Windows.Media;
using System.Xml.Serialization;
using System.Runtime.Serialization;

namespace VEX.Core.Shared.Model.UI
{
    [DataContract(IsReference = true)]
    public class SpriteModel : PItem
    {
        Rectangle rectselected = new Rectangle
        {
            Stroke = Brushes.Red,
            StrokeThickness = 2
        };

        private string mName;

        private string mPath;
        private Rectangle mRectangle;

        [DataMember]
        [Category("SpriteModel")]
        public string Path { get { return mPath; } set { mPath = value; RaisePropertyChanged("Path"); } }

        [Browsable(false)]
        public Rectangle Rectangle { get { return mRectangle; } set { mRectangle = value; RaisePropertyChanged("Rectangle"); } }

        [DataMember]
        [Category("SpriteModel")]
        public string Name { get { return mName; } set { mName = value; RaisePropertyChanged("Name"); } }

        [DataMember]
        [Category("SpriteModel")]
        public float width { get; set; }

        [DataMember]
        [Category("SpriteModel")]
        public float height { get; set; }

        [DataMember]
        [Category("SpriteModel")]
        public float posX { get; set; }

        [DataMember]
        [Category("SpriteModel")]
        public float posY { get; set; }
    }
}
