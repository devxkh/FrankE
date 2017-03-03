using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Runtime.Serialization;
using System.Text;
using System.Windows;
using VEF;
using VEF.Core.Model.Services;
using VEF.Interfaces.Services;
using VEF.Utils;
using VEX.Core.Model.Services;
using VEX.Core.View.UI.Helper;
using VEX.Interface.DAL;
using VEX.Model.Scene.Model;
using VEX.Model.Scene.Model.Objects;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using VEX.Service.Scene;

namespace VEX.Core.Shared.Interface.DAL
{
    [DataContract(IsReference = true)]
    public abstract class LocalFile : ViewModelIsRefBase, IFBObject
    {
        private bool _initialized;
        private string _Filepath;

        /// <summary>
        /// determine folder path from type
        /// </summary>
        [DataMember]
        public XFBType.FileLocation FileLocation { get; set; }

        public abstract void Read(Byte[] fbData);

        [DataMember]
        public object Parent { get; set; }

        /// <summary>
        /// path within location to the filename
        /// </summary>
        [DataMember]
        [Editor(typeof(AssetFilePathEditor), typeof(AssetFilePathEditor))]
        public string FilePath
        {
            get { return _Filepath; }
            set
            {
                _Filepath = value;

                if (!_initialized && _Filepath != null)
                    init();

                RaisePropertyChanged("FilePath");
            }
        }// RaisePropertyChanged("Filepath"); } }

        /// <summary>
        /// filename with extension
        /// </summary>
        [DataMember]
        public string FileName { get; set; }

        /// <summary>
        /// resource group
        /// </summary>
        [DataMember]
        public string ResourceGroup { get; set; }

        private bool _watch;

        /// <summary>
        /// enable filewatcher for this file
        /// </summary>
        [DataMember]
        public bool Watch
        {
            get { return _watch; }
            set
            {
                _watch = value;
                if (value == true)
                {
                    if (FileWatcher == null)
                        init();

                    FileWatcher.EnableRaisingEvents = value;// Begin watching.
                }
            }
        }

        protected FileSystemWatcher FileWatcher { get; set; }

        public void init()
        {
            try
            {
                string fullFilePath = "";

                if (FileLocation == XFBType.FileLocation.FILELOC_Asset)
                {
                    fullFilePath = System.IO.Path.Combine(@"F:\Projekte\coop\XGame\data", FilePath);
                }

                FileWatcher = new FileSystemWatcher();
                FileWatcher.Path = System.IO.Path.GetDirectoryName(fullFilePath);
                FileWatcher.Filter = System.IO.Path.GetFileName(fullFilePath);

                /* Watch for changes in LastAccess and LastWrite times, and
                   the renaming of files or directories. */
                if (!HasImageExtension(fullFilePath))
                {
                    FileWatcher.NotifyFilter = NotifyFilters.LastWrite;// | NotifyFilters.Size;
                                                                       //  NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite;
                                                                       // | NotifyFilters.FileName;// | NotifyFilters.DirectoryName;
                }
                //   NotifyFilter = NotifyFilters.FileName | NotifyFilters.Size;

                // Only watch text files.
                //   Filter = "*.txt";

                // Add event handlers.
                FileWatcher.Changed += new FileSystemEventHandler(OnChanged);
                FileWatcher.Created += new FileSystemEventHandler(OnCreated);
                FileWatcher.Deleted += new FileSystemEventHandler(OnDeleted);
                FileWatcher.Renamed += new RenamedEventHandler(OnRenamed);

                // Begin watching.
                // FileWatcher.EnableRaisingEvents = true;
                _initialized = true;

            }catch(Exception ex)
            {
                var _logger = VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as LoggerService;
                _logger.Log(ex.Message, LogCategory.Exception,LogPriority.High);
                throw new Exception(ex.Message);

                // MessageBox.Show(ex.Message);
            }
        }

        protected virtual void OnCreated(object source, FileSystemEventArgs e)
        {
            Console.WriteLine("File: {0} created", e.FullPath);
        }

        protected virtual void OnDeleted(object source, FileSystemEventArgs e)
        {
            Console.WriteLine("File: {0} delete", e.FullPath);
        }

        public abstract FBNetData CreateFBData(FlatBufferBuilder fbb, IFBObject child = null);
        //{
        //    FlatBufferBuilder fbb = new FlatBufferBuilder(4);
        //    var fbData = localFile.Entity.FBObject.CreateFBData(fbb);

        //    var mon = NetMsg.MessageRoot.CreateMessageRoot(fbb, 0, 1, NetMsg.Data.Entity, fbData._offset);
        //    NetMsg.MessageRoot.FinishMessageRootBuffer(fbb, mon);
        //    return fbData;
        //} 

        // Define the event handlers.
        protected virtual void OnChanged(object source, FileSystemEventArgs e)
        {
            //var localFile = source as LocalFile;
            //if (localFile == null)
            //    return;
          
            // Specify what is done when a file is changed, created, or deleted.
            Console.WriteLine("File: " + e.FullPath + " " + e.ChangeType);

            OnChange();
        }

        protected virtual void OnRenamed(object source, RenamedEventArgs e)
        {
            //var localFile = source as LocalFile;
            //if (localFile == null)
            //    return;

            OnChange();

            // Specify what is done when a file is renamed.
            Console.WriteLine("File: {0} renamed to {1}", e.OldFullPath, e.FullPath);
        }

        private void OnChange()
        {
             try
            {
                //HACK : fix for event triggered twice -> http://stackoverflow.com/questions/1764809/filesystemwatcher-changed-event-is-raised-twice
                FileWatcher.EnableRaisingEvents = false;

                EntityX parentEntity;
                if (Parent is MeshObject)
                    parentEntity = ((Parent as MeshObject).Parent as RenderableComponent).Parent;
                else
                    parentEntity = (Parent as RenderableComponent).Parent;

                List<Type> types = new List<Type>() { typeof(RenderableComponent) }; //send only the renderable component
                FlatBufferBuilder fbb = new FlatBufferBuilder(4);
                var fbEntity = parentEntity.FB_Entity.CreateFBData(types, fbb); //todo

                var mon = NetMsg.MessageRoot.CreateMessageRoot(fbb, parentEntity.NetID, 1, NetMsg.Data.Entity, fbEntity._offset);
                NetMsg.MessageRoot.FinishMessageRootBuffer(fbb, mon);

                //    var fbdata = FBObject.CreateFBData();

                //     FBObject.Read(fbdata._fbData);

                //   _SocketServerManager.SendMessageToServer(NetID, Parent.SceneID, msgType, fbData);

                //   var fbData = CreateFBData();

                var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;

                _SocketServerManager.Client.SendToServer(0, fbb.SizedByteArray(), ENet.PacketFlags.Reliable);


            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                FileWatcher.EnableRaisingEvents = true;
            }
        }

        public static bool HasImageExtension(string source)
        {
            return (source.EndsWith(".bmp")
                  || source.EndsWith(".gif")
                   || source.EndsWith(".ico")
                    || source.EndsWith(".jpg")
                     || source.EndsWith(".jpeg")
                      || source.EndsWith(".png")
                       || source.EndsWith(".tif")
                        || source.EndsWith(".tiff")
                         || source.EndsWith(".wmf"));
        }      
    }


    //interface IHasLocalFile
    //{
    //    ObservableCollection<LocalFile> LocalFiles { get; }
    //}
}
