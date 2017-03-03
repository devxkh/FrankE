using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using VEF.Interfaces.Services;
using Xceed.Wpf.Toolkit.PropertyGrid;

namespace VEX.Core.View.Project
{
    /// <summary>
    /// Interaktionslogik für VFPathEditor.xaml
    /// </summary>
    public partial class VFPathEditor : UserControl
    {
        public VFPathEditor()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty PathValueProperty = DependencyProperty.Register("PathValue", typeof(object), typeof(VFPathEditor),
                                                                                           new FrameworkPropertyMetadata(null, FrameworkPropertyMetadataOptions.BindsTwoWayByDefault));

        //[NotNullValidator(MessageTemplate = "Customer must have valid no")]
        //[StringLengthValidator(5, RangeBoundaryType.Inclusive, 5, RangeBoundaryType.Inclusive, MessageTemplate = "Customer no must have {3} characters.")]
        //[RegexValidator("[A-Z]{2}[0-9]{3}", MessageTemplate = "Customer no must be 2 capital letters and 3 numbers.")]
        //[Required(ErrorMessage = "Customer no can not be empty")]
        //[StringLength(5, ErrorMessage = "Customer no must be 5 characters.")]
        //[RegularExpression("[A-Z]{2}[0-9]{3}", ErrorMessage = "Customer no must be 2 capital letters and 3 numbers.")]
        public object PathValue
        {
            get { return GetValue(PathValueProperty); }
            private set
            {
                SetValue(PathValueProperty, value);
            }
        }
        private void dragleave(object sender, DragEventArgs e)
        {

            e.Handled = true;

            this.BorderBrush = null;
            this.BorderThickness = new Thickness(0);
        }
        private void dragOver(object sender, DragEventArgs e)
        {
            //IItem sourceItem = dropInfo.Data as IItem;
            //    //IItem targetItem = dropInfo.TargetItem as IItem;

            //    DragInfo dragInfo = new DragInfo(sender,e);
            //    //  var item = dropInfo.VisualTargetItem as TreeViewItem;
            var view = sender as PropertyItem;
            IItem targetItem = view.Instance as IItem;

            var dataFormat = GongSolutions.Wpf.DragDrop.DragDrop.DataFormat.Name;
            var Data = (e.Data.GetDataPresent(dataFormat)) ? e.Data.GetData(dataFormat) : e.Data;

            //  IItem dataString = e.Data..GetData(DataFormats.StringFormat);

            //var dc = view.DataContext;
            //    //if (sourceItem != null && targetItem != null)
            //    //{
            //    //    dropInfo.DropTargetAdorner = DropTargetAdorners.Highlight;
            //    //    dropInfo.Effects = System.Windows.DragDropEffects.Copy;
            //    //}

            if (view != null)
            {
                //IDropTarget dropHandler = GongSolutions.Wpf.DragDrop.DragDrop.GetDropHandler(view);
                //if (dropHandler == this)
                //{
                e.Effects = System.Windows.DragDropEffects.Copy;

                e.Handled = true;
                //    }
            }


            this.BorderBrush = Brushes.Blue;
            this.BorderThickness = new Thickness(5);
        }

        private void drop(object sender, DragEventArgs e)
        {
            var view = sender as PropertyItem;


            IItem targetItem = view.Instance as IItem;
            var dataFormat = GongSolutions.Wpf.DragDrop.DragDrop.DataFormat.Name;
            var sourceData = (e.Data.GetDataPresent(dataFormat)) ? e.Data.GetData(dataFormat) : e.Data;
            IItem sourceDataIItem = sourceData as IItem;

            if (view != null)
            {
                if (sourceDataIItem != null)
                    this.tbFile.Text = sourceDataIItem.ContentID;

                //  e.Effects = System.Windows.DragDropEffects.Move;

                e.Handled = true;
            }

            //  view.BorderBrush = Color.FromArgb(1,1,1,1);
            this.BorderThickness = new Thickness(0);
            this.BorderBrush = null;


        }

        public FrameworkElement ResolveEditor(Xceed.Wpf.Toolkit.PropertyGrid.PropertyItem propertyItem)
        {
            // propertyItem.DragOver += new DragEventHandler(test);
            propertyItem.PreviewDragOver += new DragEventHandler(dragOver);
            propertyItem.PreviewDrop += new DragEventHandler(drop);
            propertyItem.PreviewDragLeave += new DragEventHandler(dragleave);


            Binding binding = new Binding("PathValue");
            binding.Source = propertyItem;
            binding.Mode = propertyItem.IsReadOnly ? BindingMode.OneWay : BindingMode.TwoWay;
            BindingOperations.SetBinding(this, VFPathEditor.PathValueProperty, binding);
            return this;
        }
    }
}
