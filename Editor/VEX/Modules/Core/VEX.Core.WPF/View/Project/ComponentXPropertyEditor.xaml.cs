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
using VEX.Core.Shared.Service.Scene;
using Xceed.Wpf.Toolkit.PropertyGrid;
using Xceed.Wpf.Toolkit.PropertyGrid.Editors;

namespace VEX.Core.View.Project
{
    /// <summary>
    /// Interaktionslogik für ComponentXPropertyEditor.xaml
    /// </summary>
    public partial class ComponentXPropertyEditor : UserControl, ITypeEditor
    {
      
        public ComponentXPropertyEditor()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty ComponentProperty = DependencyProperty.Register("Component", typeof(object), typeof(ComponentXPropertyEditor),
                                                                                             new FrameworkPropertyMetadata(null, FrameworkPropertyMetadataOptions.BindsTwoWayByDefault));
        
        public object Component
        {
            get
            {
                return GetValue(ComponentProperty);
            }
            private set
            {
                SetValue(ComponentProperty, value);
            }
        }
        
        public FrameworkElement ResolveEditor(Xceed.Wpf.Toolkit.PropertyGrid.PropertyItem propertyItem)
        {
            var component = propertyItem.Value as ComponentX;

            if (component == null)
                return this;

            ctxMenu.ItemsSource =  component.MenuOptions;

            Binding binding = new Binding("Component");
            binding.Source = propertyItem;
            binding.Mode = propertyItem.IsReadOnly ? BindingMode.OneWay : BindingMode.TwoWay;
            BindingOperations.SetBinding(this, ComponentXPropertyEditor.ComponentProperty, binding);
            return this;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //VistaOpenFileDialog dialog = new VistaOpenFileDialog();
            //dialog.Title = "Please select a file.";
            //dialog.FileName = tbFile.Text;

            //Window yourParentWindow = Window.GetWindow(this);
            //if ((bool)dialog.ShowDialog(yourParentWindow))
            //{
            //    var dataContext = tbFile.DataContext as Xceed.Wpf.Toolkit.PropertyGrid.PropertyItem;
            //    if (dataContext != null)
            //        dataContext.Value = dialog.FileName;
            //}
          
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
        }
        
        private void btnOptions_Click(object sender, RoutedEventArgs e)
        {
            (sender as Button).ContextMenu.IsEnabled = true;
            (sender as Button).ContextMenu.PlacementTarget = (sender as Button);
            (sender as Button).ContextMenu.Placement = System.Windows.Controls.Primitives.PlacementMode.Bottom;
            (sender as Button).ContextMenu.IsOpen = true;
        }
    }
}
