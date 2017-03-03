using PCL.XEditor;
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
using VEX.Core.Model;
using VEX.Core.Shared.Model.Project;
using VEX.Core.Shared.Service.FileWatcher;

namespace VEX.Core.View.Project
{
    /// <summary>
    /// Interaktionslogik für FileWatcher.xaml
    /// </summary>
    public partial class FileWatcherView : UserControl, IContentView, INotifyPropertyChanged
    {
        public FileWatcherView()
        {
            InitializeComponent();
        }


        private void _dataGrid_MouseUp(object sender, MouseButtonEventArgs e)
        {

            var mPropertiesService = VEFModule.UnityContainer.Resolve(typeof(IPropertiesService), "") as IPropertiesService;
            mPropertiesService.CurrentItem = _dataGrid.SelectedItem;
        }


        protected virtual void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void btn_ExecuteEvent_Click(object sender, RoutedEventArgs e)
        {
            var mPropertiesService = VEFModule.UnityContainer.Resolve(typeof(IPropertiesService), "") as IPropertiesService;

            SourceFileItem file = _dataGrid.SelectedItem as SourceFileItem;

            if (file.FileType == FileType.fbx)
            {
                FBXFileConverter test = new FBXFileConverter();
                test.Convert(file.SourceFilePath, file.DestinationFolder, file.DestinationFileName);

                string fbxfilename = @"F:\Projekte\coop\XGame\_devFolder\Work\Character\character@WalkBase.fbx";
                string skeletonfilename = @"F:\Projekte\coop\XGame\data\assets\TestModel.SKELETON";
                string meshfilename = @"F:\Projekte\coop\XGame\data\assets\TestModel.MESH";
                string logfilename = "log.txt";
                string animname = "WalkBase";
                int start = Int32.MinValue; int stop = Int32.MaxValue; float rate = 0;

                DLL_FBXToOgre tmp = new DLL_FBXToOgre();
                tmp.Test_AddFBXAnimationToExisting(fbxfilename, skeletonfilename, meshfilename, logfilename,
                                                             animname, start, stop, rate);
            }
        }

        private void btnAddRemove_Click(object sender, RoutedEventArgs e)
        {
            var mPropertiesService = VEFModule.UnityContainer.Resolve(typeof(IPropertiesService), "") as IPropertiesService;

            mPropertiesService.CurrentItem = this.DataContext;

        }

        private void btnForceTrigger_Click(object sender, RoutedEventArgs e)
        {
            SourceFileItem file = _dataGrid.SelectedItem as SourceFileItem;

            if (file != null)
                FileWatcherModel.Execute(file);

            return;

            var mPropertiesService = VEFModule.UnityContainer.Resolve(typeof(IPropertiesService), "") as IPropertiesService;

            SourceFileItem filex = _dataGrid.SelectedItem as SourceFileItem;

            if (filex.FileType == FileType.fbx)
            {
                FBXFileConverter test = new FBXFileConverter();
                test.Convert(filex.SourceFilePath, filex.DestinationFolder, filex.DestinationFileName);

                string fbxfilename = @"F:\Projekte\coop\XGame\_devFolder\Work\Character\character@WalkBase.fbx";
                string skeletonfilename = @"F:\Projekte\coop\XGame\data\assets\TestModel.SKELETON";
                string meshfilename = @"F:\Projekte\coop\XGame\data\assets\TestModel.MESH";
                string logfilename = "log.txt";
                string animname = "WalkBase";
                int start = Int32.MinValue; int stop = Int32.MaxValue; float rate = 0;

                DLL_FBXToOgre tmp = new DLL_FBXToOgre();
                tmp.Test_AddFBXAnimationToExisting(fbxfilename, skeletonfilename, meshfilename, logfilename,
                                                             animname, start, stop, rate);



            }
        }
    }
}
