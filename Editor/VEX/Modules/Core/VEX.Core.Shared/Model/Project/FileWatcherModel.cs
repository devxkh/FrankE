using Module.PFExplorer.Service;
using PCL.XEditor;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.IO;
using System.Runtime.Serialization;
using System.Text;
using System.Windows;
using VEF;
using VEF.Interfaces.Services;
using VEF.VEF_Helpers;
using VEF.View.Types;
using VEX.Core.Model;
using VEX.Core.Shared.Service.FileWatcher;

namespace VEX.Core.Shared.Model.Project
{
    [DataContract(IsReference = true)]
    public class FileWatcherModel : ProjectItemModel
    {
        private ObservableCollection<SourceFileItem> _FileItems;

        [DataMember]
        public ObservableCollection<SourceFileItem> FileItems
        {
            get {

                if (_FileItems == null)
                    _FileItems = new ObservableCollection<SourceFileItem>();

                return _FileItems;
            }
            set
            {

                if (_FileItems == null && value != null) //from deserialization
                {
                    value.CollectionChanged += this.OnCollectionChanged;
                    _FileItems = value;
                    foreach (var file in value)
                        AddItemToWatch(file);
                }
                else
                {
                    _FileItems = value;
                }

            }
        }

        void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var newItem in e.NewItems)
                {
                    var sourceFileItem = newItem as SourceFileItem;
                    if (sourceFileItem != null)
                    {
                        AddItemToWatch(sourceFileItem);
                    }
                }
            }
        }

        public FileWatcherModel()
        {
            _FileItems = new ObservableCollection<SourceFileItem>();
            _FileItems.CollectionChanged += this.OnCollectionChanged;

            //var commandManager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;
            //var menuService = VEFModule.UnityContainer.Resolve(typeof(IMenuService), "") as IMenuService;


            //// string sourceFile = @"F:\Projekte\Game\3d Models\Work\fighter\test\test.fbx";
            //string sourceFile = @"F:\Projekte\coop\XGame\_devFolder\Work\Character\character.fbx";
            ////  string sourceFile = @"F:\Projekte\Game\3d Models\Work\fighter\test\cvvcvc.txt";
            //string destinationFolder = @"F:\Projekte\coop\XGame\data\assets";
            
            //AddItemToWatch();

            //var test_sourceFileItem = new SourceFileItem()
            //{
            //    SourceFilePath = sourceFile,
            //    DestinationFolder = destinationFolder,
            //    DestinationFileName = "TestModel.MESH",
            //    FileType = FileType.fbx,
            //    Watch = true
            //};
            //_FileItems.Add(test_sourceFileItem);


            //FileItemWatcher watcher = new FileItemWatcher()
            //{
            //    SourceFileItem = test_sourceFileItem
            //};
            //watcher.Path = Path.GetDirectoryName(sourceFile);
            //watcher.Filter = Path.GetFileName(sourceFile);

            ///* Watch for changes in LastAccess and LastWrite times, and
            //   the renaming of files or directories. */
            //watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
            //   | NotifyFilters.FileName | NotifyFilters.DirectoryName;
            //// Only watch text files.
            ////  watcher.Filter = "*.txt";

            //// Add event handlers.
            //watcher.Changed += new FileSystemEventHandler(OnChanged);
            //watcher.Created += new FileSystemEventHandler(OnCreated);
            //watcher.Deleted += new FileSystemEventHandler(OnDeleted);
            //watcher.Renamed += new RenamedEventHandler(OnRenamed);

            //// Begin watching.
            //watcher.EnableRaisingEvents = true;
        }

        public override bool Open(object id)
        {
           
            int sceneID = VEF_Helper.StringToContentIDData(ContentID).IntValue;

            //  this.Location = ItemFolder + "\\" + sceneID + ".xml";

            //read sceneData from DAL -- Read data from XML not from database -> database data not human readable
            //9_01_2015      m_FBData = ObjectSerialize.Deserialize<FB_Scene>(this.Location.ToString()); // XML Serialize
      

            //only able to save data into database not load
            return true;
        }

        internal void SetLocation(object location)
        {
            this.Location = location;
            this.ContentID = location.ToString();

            RaisePropertyChanged("Location");
        }

        internal void SetDirty(bool value)
        {
            this.IsDirty = value;
        }


        private void AddItemToWatch(SourceFileItem sourceFileItem)
        {
           // string sourceFile = @"F:\Projekte\coop\XGame\_devFolder\Work\Shapes\Stairway.fbx";
           // string destinationFolder = @"F:\Projekte\coop\XGame\data\assets";

            //var test_sourceFileItem = new SourceFileItem()
            //{
            //    SourceFilePath = sourceFile,
            //    DestinationFolder = destinationFolder,
            //    DestinationFileName = sestinationFileName,// "Stairway.MESH",
            //    FileType = FileType.fbx,
            //    Watch = true
            //};

         //   _FileItems.Add(test_sourceFileItem);

            FileItemWatcher watcher = new FileItemWatcher()
            {
                SourceFileItem = sourceFileItem
            };

            if (string.IsNullOrEmpty(sourceFileItem.SourceFilePath))
            {
                MessageBox.Show("Cannot watch this file:" + sourceFileItem.SourceFilePath);
                return;
            }

            watcher.Path = Path.GetDirectoryName(sourceFileItem.SourceFilePath);
            watcher.Filter = Path.GetFileName(sourceFileItem.SourceFilePath);

            /* Watch for changes in LastAccess and LastWrite times, and
               the renaming of files or directories. */
            watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
               | NotifyFilters.FileName | NotifyFilters.DirectoryName;
            // Only watch text files.
            //  watcher.Filter = "*.txt";

            // Add event handlers.
            watcher.Changed += new FileSystemEventHandler(OnChanged);
            watcher.Created += new FileSystemEventHandler(OnCreated);
            watcher.Deleted += new FileSystemEventHandler(OnDeleted);
            watcher.Renamed += new RenamedEventHandler(OnRenamed);

            // Begin watching.
            watcher.EnableRaisingEvents = true;
        }

        private static void OnCreated(object source, FileSystemEventArgs e)
        {
            Console.WriteLine("File: {0} created", e.FullPath);
        }

        private static void OnDeleted(object source, FileSystemEventArgs e)
        {
            Console.WriteLine("File: {0} delete", e.FullPath);
        }

        public static void Execute(SourceFileItem sourceFileItem)
        {
            if (sourceFileItem.FileType == FileType.fbx)
            {
                FBXFileConverter test = new FBXFileConverter();
                test.Convert(sourceFileItem.SourceFilePath, sourceFileItem.DestinationFolder, sourceFileItem.DestinationFileName);
            }
            else if (sourceFileItem.FileType == FileType.fbx_Animation)
            {
                //     FBXFileConverter test = new FBXFileConverter();
                //     test.Convert(fileItemWatcher.SourceFilePath, fileItemWatcher.DestinationFolder, fileItemWatcher.DestinationFileName);
                //FBXFileConverter test = new FBXFileConverter();
                //test.Convert(sourceFileItem.SourceFilePath, sourceFileItem.DestinationFolder, sourceFileItem.DestinationFileName);
                //string fbxfilename = @"F:\Projekte\coop\XGame\_devFolder\Work\Character\character@WalkBase.fbx";
                //string skeletonfilename = @"F:\Projekte\coop\XGame\data\assets\TestModel.SKELETON";
                //string meshfilename = @"F:\Projekte\coop\XGame\data\assets\TestModel.MESH";

                string fileNameWithoutExtension = Path.GetFileNameWithoutExtension(sourceFileItem.DestinationFileName);

                if (!sourceFileItem.SourceFilePath.Contains("@"))
                {
                    (VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService).Log("Filename contains no @animationName", LogCategory.Error, LogPriority.Medium);
                    return;
                }

                string animName = Path.GetFileNameWithoutExtension(sourceFileItem.SourceFilePath).Split('@')[1];

                string logfilename = "log.txt";
                //     string animname = "WalkBase";
                int start = Int32.MinValue; int stop = Int32.MaxValue; float rate = 0;

                DLL_FBXToOgre tmp = new DLL_FBXToOgre();
                tmp.Test_AddFBXAnimationToExisting(sourceFileItem.SourceFilePath,
                                                    Path.Combine(sourceFileItem.DestinationFolder ,fileNameWithoutExtension + ".SKELETON"),
                                                    Path.Combine(sourceFileItem.DestinationFolder, fileNameWithoutExtension + ".MESH"),
                                                    logfilename,
                                                    animName, start, stop, rate);
            }else if(sourceFileItem.FileType == FileType.Script)
            {

            }
        }

        // Define the event handlers.
        private static void OnChanged(object source, FileSystemEventArgs e)
        {
            var fileItemWatcher = source as FileItemWatcher;
            if (fileItemWatcher == null)
                return;

            //HACK : fix for event triggered twice -> http://stackoverflow.com/questions/1764809/filesystemwatcher-changed-event-is-raised-twice
            try
            {
                fileItemWatcher.EnableRaisingEvents = false;

                Execute(fileItemWatcher.SourceFileItem);
            }

            finally
            {
                fileItemWatcher.EnableRaisingEvents = true;
            }
        }

        private static void OnRenamed(object source, RenamedEventArgs e)
        {
            // Specify what is done when a file is renamed.
            Console.WriteLine("File: {0} renamed to {1}", e.OldFullPath, e.FullPath);
        }
    }

    [DataContract]
    public class SourceFileItem //: ViewModelBase
    {
        private string _SourceFilePath;
        private string _DestinationFileName;
        private string _DestinationFolder;

        [DataMember]
        [Editor(typeof(FilePathEditor), typeof(FilePathEditor))]
        public string SourceFilePath { get { return _SourceFilePath; } set { _SourceFilePath = value; } }// RaisePropertyChanged("LocalFile"); } }

        [DataMember]
        [Editor(typeof(FolderEditor), typeof(FolderEditor))]
        public string DestinationFolder { get { return _DestinationFolder; } set { _DestinationFolder = value; } }// RaisePropertyChanged("LocalFile"); } }

        [DataMember]
        [Editor(typeof(FilePathEditor), typeof(FilePathEditor))]
        public string DestinationFileName { get { return _DestinationFileName; } set { _DestinationFileName = value; } }// RaisePropertyChanged("LocalFile"); } }

        [DataMember]
        public FileType FileType { get; set; }

        /// <summary>
        /// Filewachter for changes
        /// </summary>
        [DataMember]
        public bool Watch { get; set; }
    }
}
