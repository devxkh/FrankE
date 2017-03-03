using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using VEF;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEX.Core.Shared.Service.Scene;
using VEX.Interface.Scene;
using VEX.Model.Scene.Model;
using VEX.Service.Scene;

namespace VEX.Core.View.Scene
{
    /// <summary>
    /// Interaktionslogik für SceneGraphToolView.xaml
    /// </summary>
    public partial class SceneGraphToolView : UserControl, IContentView, INotifyPropertyChanged
    {
        IPropertiesService mPropertiesService;
        ISceneService mSceneService;
        public SceneGraphToolView()
        {
            InitializeComponent();
            

            mPropertiesService = VEFModule.UnityContainer.Resolve(typeof(IPropertiesService), "") as IPropertiesService;

            mSceneService = VEFModule.UnityContainer.Resolve(typeof(ISceneService), "") as ISceneService;
            //mSceneService.TreeList = _treeList;

        }

        /// <summary>
        /// Should be called when a property value has changed
        /// </summary>
        /// <param name="propertyName">The property name</param>
        protected virtual void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public event PropertyChangedEventHandler PropertyChanged;


        private void UserControl_Unloaded(object sender, System.Windows.RoutedEventArgs e)
        {
            //StreamWriter standardOutput = new StreamWriter(Console.OpenStandardOutput());
            //standardOutput.AutoFlush = true;
            //Console.SetOut(standardOutput);
        }

        //doesnt trigger?
        //private void ContextMenu_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        //{
        //  ContextMenu tmp =  (ContextMenu)sender;
        //  tmp.ItemsSource = mSceneService.CurrentItem.MenuOptions;
        //}

        private void ContextMenu_Opened(object sender, System.Windows.RoutedEventArgs e)
        {
            ContextMenu tmp = (ContextMenu)sender;

            if(mSceneService.SelectedScene.SelectedItem is EntityX)
                tmp.ItemsSource = (mSceneService.SelectedScene.SelectedItem as EntityX).MenuOptions;
             if(mSceneService.SelectedScene.SelectedItem is ComponentX)
                tmp.ItemsSource = (mSceneService.SelectedScene.SelectedItem as ComponentX).MenuOptions;
             else if(mSceneService.SelectedScene.SelectedItem is BodyComponent)
                tmp.ItemsSource = (mSceneService.SelectedScene.SelectedItem as BodyComponent).MenuOptions;

            //multiple items selected
            //if (_treeList.SelectedItems.Count > 1)
            //{
            //    List<MenuItem> lmi = new List<MenuItem>();
            //    lmi.Add(new MenuItem() { Header = "Multiselected!" });
            //    tmp.ItemsSource = lmi;
            //}
            ////one item selected
            //else if(_treeList.SelectedItem != null)
            //{
            //    tmp.ItemsSource = mSceneService.SelectedScene.SelectedItem.MenuOptions;
            //}
            ////just rootitem exists
            //else if (_treeList.RootItem != null)
            //{
            //    tmp.ItemsSource = mSceneService.RootItem.MenuOptions;
            //}

            //nothing selected          
        }

        private void _treeList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void _treeList_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
            //if (mSceneService.SelectedScene == null)
            //{
            //    e.Handled = true;
            //}
            //else if (
            //    (mSceneService.SelectedScene.SelectedItem == null
            //    || mSceneService.SelectedScene.SelectedItem.MenuOptions == null)
            //    && _treeList.RootItem == null )
            //{
            //    e.Handled = true;
            //}
        }

        private void TreeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            TreeView tmp = (TreeView)sender;
            if (tmp != null)
            {
                IItem tn = tmp.SelectedItem as IItem;
                if (tn != null)
                {
                    mSceneService.SelectedScene.SelectedItem = tn;
                    mPropertiesService.CurrentItem = tn;
                }
            }
        }

        //      private void Button_Click(object sender, RoutedEventArgs e)
        //      {
        //      }


        //      private void Button_Click_2(object sender, RoutedEventArgs e)
        //      {
        //ISceneService sv = mcontainer.Resolve<ISceneService>();
        //          sv.SelectedScene.SceneItems.Add(new SceneCategoryModel() {Name= "sdfsdf" });
        //          sv.SelectedScene.Items.Add(new SceneCategoryModel() { Name = "__sdfsdf" });
        //      }

    }
}
