using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Text;
using System.Windows.Controls;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEX.Core.Shared.Model.UI.Helper;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Core.Shared.Model.UI
{
    public struct Kerning
    {
        public uint RightGlyphID { get; set; }
        public int KerningValue { get; set; }
    }

    public class Glyph
    {
        public int X { get; set; }
        public int Y { get; set; }
        public int width { get; set; }
        public int height { get; set; }
        public int advance { get; set; }
    }

    [DataContract(IsReference = true)]
    public class FontData : PItem
    {
        [Category("FontData")]
        public uint CharacterAsUint { get; set; }

        [Category("FontData")]
        public string Character { get; set; }


        [Category("FontData")]
        [ExpandableObject]
        public Glyph Glyph { get; set; }

        [Category("FontData")]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        public ObservableCollection<Kerning> Kerning { get; set; }

        [Category("FontData")]
        public int VerticalOffset { get; set; }

        public FontData()
        {
            Kerning = new ObservableCollection<Kerning>();
        }

        //private bool m_IsSelected;
        //[Browsable(false)]
        //public bool IsSelected
        //{
        //    get { return m_IsSelected; }
        //    set
        //    {
        //        m_IsSelected = value;
        //        //var propService = UnityContainer.Resolve<IPropertiesService>();
        //        //propService.CurrentItem = this;


        //        m_Gorilla.SelectedRectangle.Stroke = System.Windows.Media.Brushes.Red;
        //        m_Gorilla.SelectedRectangle.StrokeThickness = 2;
        //        m_Gorilla.SelectedRectangle.Width = Glyph.width;
        //        m_Gorilla.SelectedRectangle.Height = Glyph.height;

        //        Canvas.SetLeft(m_Gorilla.SelectedRectangle, Glyph.X);
        //        Canvas.SetTop(m_Gorilla.SelectedRectangle, Glyph.Y);
        //        //    var gorillaService = m_container.Resolve<IGorillaService>();
        //        //    gorillaService.SelectedGorilla = this;
        //    }
        //}
    }
}
