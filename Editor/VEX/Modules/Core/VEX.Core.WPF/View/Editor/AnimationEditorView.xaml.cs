using DLL.NodeEditor.Nodes;
using DLL.NodeEditor.ViewModel;
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
using VEX.Model.UI;

namespace VEX.Core.View.Components
{
    /// <summary>
    /// Interaktionslogik für AnimationComponentView.xaml
    /// </summary>
    public partial class AnimationEditorView : UserControl
    {
        public AnimationEditorView()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var GraphViewModel = (this.DataContext as AnimationEditorModel).GraphViewModel;
            

            var element1 = GraphViewModel.AddElement<ColorInput>(100, 50);
            //  element1.Bitmap = BitmapUtility.CreateFromBytes(DesignTimeImages.Desert);

            var element2 = GraphViewModel.AddElement<ColorInput>(100, 300);
            element2.Color = Colors.Green;

            var element3 = GraphViewModel.AddElement<Multiply>(400, 250);

            GraphViewModel.Connections.Add(new ConnectionViewModel()
            {
                From =  element1.OutputConnector,
                To = element3.InputConnectors[0]
            });

            GraphViewModel.Connections.Add(new ConnectionViewModel()
            {
                From = element2.OutputConnector,
                To =  element3.InputConnectors[1] });

        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
        //    var found =  this.FindResource("animationNodeTemplate");
        //    GraphControl.Resources.Add("animationNodeTemplate", found);
        }

        private void GraphControl_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete)
                ((GraphViewModel)DataContext).DeleteSelectedElements();
            base.OnKeyDown(e);
        }

        private void UserControl_PreviewKeyDown(object sender, KeyEventArgs e)
        {

        }

        private void _GraphControl_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {

        }

        private void ContextMenu_Opened(object sender, RoutedEventArgs e)
        {
            ContextMenu tmp = (ContextMenu)sender;
            var tvi = tmp.PlacementTarget as TreeViewItem;
            if (tvi != null)
            {
                //multiple items selected
                //if (treeView.SelectedItems.Count > 1)
                //{
                //    List<MenuItem> lmi = new List<MenuItem>();
                //    lmi.Add(new MenuItem() { Header = "Multiselected!" });
                //    tmp.ItemsSource = lmi;
                //}
                ItemsControl parent = ItemsControl.ItemsControlFromItemContainer(tvi);

                //one item selected
                //if (mProjectTreeService.SelectedItem != null)
                //{
                //    mProjectTreeService.SelectedItem.Parent = parent.DataContext as PItem;
                //    //      mProjectTreeService.SelectedItem.UnityContainer = m_Container;
                //    tmp.ItemsSource = mProjectTreeService.SelectedItem.MenuOptions;
                //}
            }
        }

        private void GraphControl_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            Focus();
            base.OnPreviewMouseDown(e);
        }
    }
}
