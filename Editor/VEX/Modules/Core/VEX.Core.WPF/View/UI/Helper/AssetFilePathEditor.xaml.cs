using Ookii.Dialogs.Wpf;
using System;
using System.Collections.Generic;
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
using VEF.Interfaces.Services;
using Xceed.Wpf.Toolkit.PropertyGrid;
using Xceed.Wpf.Toolkit.PropertyGrid.Editors;

namespace VEX.Core.View.UI.Helper
{
    /// <summary>
    /// Interaktionslogik für AssetFilePathEditor.xaml
    /// </summary>
        public partial class AssetFilePathEditor : UserControl, ITypeEditor
        {
        
            public AssetFilePathEditor()
            {
                InitializeComponent();
            }

            public static readonly DependencyProperty PathValueProperty = DependencyProperty.Register("PathValue", typeof(object), typeof(AssetFilePathEditor),
                                                                                                 new FrameworkPropertyMetadata(null, FrameworkPropertyMetadataOptions.BindsTwoWayByDefault));

            //[NotNullValidator(MessageTemplate = "Customer must have valid no")]
            //[StringLengthValidator(5, RangeBoundaryType.Inclusive, 5, RangeBoundaryType.Inclusive, MessageTemplate = "Customer no must have {3} characters.")]
            //[RegexValidator("[A-Z]{2}[0-9]{3}", MessageTemplate = "Customer no must be 2 capital letters and 3 numbers.")]
            //[Required(ErrorMessage = "Customer no can not be empty")]
            //[StringLength(5, ErrorMessage = "Customer no must be 5 characters.")]
            //[RegularExpression("[A-Z]{2}[0-9]{3}", ErrorMessage = "Customer no must be 2 capital letters and 3 numbers.")]
            public object PathValue
            {
                get
                {
                    return GetValue(PathValueProperty);
                }
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

                var dataFormat = "";// GongSolutions.Wpf.DragDrop.DragDrop.DataFormat.Name;
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
                var dataFormat = "";// GongSolutions.Wpf.DragDrop.DragDrop.DataFormat.Name;
                var sourceData = (e.Data.GetDataPresent(dataFormat)) ? e.Data.GetData(dataFormat) : e.Data;
                IItem sourceDataIItem = sourceData as IItem;

                if (view != null)
                {
                    if (sourceDataIItem != null)
                    {
                        var dataContext = tbFile.DataContext as Xceed.Wpf.Toolkit.PropertyGrid.PropertyItem;
                        if (dataContext != null)
                            dataContext.Value = sourceDataIItem.ContentID;// dialog.SelectedPath;
                    }
                    //    this.tbFile.Text = sourceDataIItem.ContentID;

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
                BindingOperations.SetBinding(this, AssetFilePathEditor.PathValueProperty, binding);
                return this;
            }

            private void Button_Click(object sender, RoutedEventArgs e)
            {
                VistaOpenFileDialog dialog = new VistaOpenFileDialog();
                dialog.Title = "Please select a file.";
                //   dialog.use.UseDescriptionForTitle = true; // This applies to the Vista style dialog only, not the old dialog.
                //  if (!VistaFolderBrowserDialog.IsVistaFolderDialogSupported)
                //      MessageBox.Show(this, "Because you are not using Windows Vista or later, the regular folder browser dialog will be used. Please use Windows Vista to see the new dialog.", "Sample folder browser dialog");

                dialog.FileName = tbFile.Text;


                Window yourParentWindow = Window.GetWindow(this);
                if ((bool)dialog.ShowDialog(yourParentWindow))
                {
                    var dataContext = tbFile.DataContext as Xceed.Wpf.Toolkit.PropertyGrid.PropertyItem;
                    if (dataContext != null)
                        dataContext.Value = dialog.FileName;
                    //    tbFile.Text = dialog.FileName;
                }
                //  MessageBox.Show(this, "The selected folder was: " + dialog.SelectedPath, "Sample folder browser dialog");            


                //OpenFileDialog openFileDialog = new OpenFolderDialog();
                //openFileDialog.FileName = tbFile.Text.ToString();
                //if (openFileDialog.ShowDialog() == true)
                //{

                //    tbFile.Text = openFileDialog.FileName;
                //}
            }

            private void UserControl_Loaded(object sender, RoutedEventArgs e)
            {
                //PropertyItem test = this.DataContext as PropertyItem;

                //IDropTarget dd = test.Instance as IDropTarget;
            }

            //void IDropTarget.DragOver(IDropInfo dropInfo)
            //{
            //    //IItem sourceItem = dropInfo.Data as IItem;
            //    //IItem targetItem = dropInfo.TargetItem as IItem;

            //    //  var item = dropInfo.VisualTargetItem as TreeViewItem;
            //    var view = dropInfo.VisualTarget as PropertyGrid;

            //    //if (sourceItem != null && targetItem != null)
            //    //{
            //    //    dropInfo.DropTargetAdorner = DropTargetAdorners.Highlight;
            //    //    dropInfo.Effects = System.Windows.DragDropEffects.Copy;
            //    //}

            //    if (view != null)
            //    {
            //        IDropTarget dropHandler = GongSolutions.Wpf.DragDrop.DragDrop.GetDropHandler(view);
            //        if (dropHandler == this)
            //        {
            //            dropInfo.Effects = System.Windows.DragDropEffects.Move;
            //        }
            //    }
            //}

            //void IDropTarget.Drop(IDropInfo dropInfo)
            //{
            ////    IItem sourceItem = dropInfo.Data as IItem;
            ////    IItem targetItem = dropInfo.TargetItem as IItem;

            //    PropertyGrid view = dropInfo.VisualTarget as PropertyGrid;
            //    IDropTarget dt = view.SelectedObject as IDropTarget;



            //    dt.Drop(dropInfo);
            //    // sourceItem.Drop(sourceItem);
            //    //targetItem.Children.Add(sourceItem);
            //}

        }
    }
