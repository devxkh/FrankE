using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Utils;
using VEF.XForms.Model.Services;
using VEX.Core.Shared.Interface.DAL;
using VEX.Core.Shared.Interface.Services;
using VEX.Core.Shared.Service.Scene;
using VEX.Enet.Interface;
using VEX.Interface.Scene;
using VEX.Model.Scene.Model;
using VEX.Model.Scene.Model.Objects;
using VEX.Service.Scene;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Core.Model
{
    public enum MaterialMap
    {
        specular,
        normal,
        occlusion,
        displacement,
        diffuse
    }

    public enum FileType
    {
        mesh,
        skeleton,
        texture,
        materialmap,
        sound,
        music,
        Script,

        fbx,
        fbx_Animation
    }

    public class SourceItem //: ViewModelBase
    {
        private ObservableCollection<LocalFile> _LocalFiles;

        [ExpandableObject]
        public SceneDataModel Scene { get; set; }

        [ExpandableObject]
        public EntityX Entity { get; set; }

        //public Action Action { get; set; }
        public  ObservableCollection<LocalFile> LocalFiles { get { return _LocalFiles; } set { _LocalFiles = value; } }// RaisePropertyChanged("LocalFile"); } }

        public ComponentX Component { get; set; }

        /// <summary>
        /// Filewachter for changes
        /// </summary>
        public bool Watch { get; set; }

        public SourceItem()
        {
            _LocalFiles = new ObservableCollection<LocalFile>();
        }
    }

    /// <summary>
    /// TODO : per flatbuffer file
    /// </summary>
    public enum GameState
    {
       WelcomeState,
       CustomizeState,
    }
    
    public class SocketServerToolModel : ToolModel
    {
        private HostInfo _HostInfo;

        private ObservableCollection<SourceItem> _sourceItems;

        public ObservableCollection<SourceItem> SceneItems
        {
            get
            {
                return _sourceItems;
            }
            set
            {
                _sourceItems = value;
            }
        }

        public GameState GameState { get; set; }

        [ExpandableObject]
        public HostInfo HostInfo { get { return _HostInfo; } }
        
        /// <summary>
        /// Initializes a new instance of the <see cref="MDModel" /> class.
        /// </summary>
        /// <param name="commandManager">The injected command manager.</param>
        /// <param name="menuService">The menu service.</param>
        public SocketServerToolModel()
        {
            var commandManager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;
            var menuService = VEFModule.UnityContainer.Resolve(typeof(IMenuService), "") as IMenuService;
            _HostInfo = new HostInfo();

            EntityX testEnt = new EntityX();
            testEnt.Components.Add(new RenderableComponent());
            testEnt.EntityID = 4;
            testEnt.Name = "Character";
            RenderableComponent renderableComp = testEnt.GetComponentX<RenderableComponent>() as RenderableComponent;

            //var newfiles = new ObservableCollection<LocalFile>();

            //var f1 = new MeshObject()
            //{
            //  //  Entity = testEnt,
            //    FileLocation = XFBType.FileLocation.FILELOC_Asset,
            //    FilePath = "assets/Sinbad.mesh"
            //};

            //var f2 = new MeshObject()
            //{
            //    FileLocation = XFBType.FileLocation.FILELOC_Asset,
            //    FilePath = "assets/Sinbad.skeleton"
            //};

            //var f3 = new MeshObject()
            //{
            //    FileLocation = XFBType.FileLocation.FILELOC_Asset,
            //    FilePath = "assets/sinbad_body.tga"
            //};

            //f1.init();
            //f2.init();
            //f3.init();
            //newfiles.Add(f1);
            //newfiles.Add(f2);
            //newfiles.Add(f3);
            //renderableComp.LocalFiles.Add(f1);
            //renderableComp.LocalFiles.Add(f2);
            //renderableComp.LocalFiles.Add(f3);

            _sourceItems = new ObservableCollection<SourceItem>();

        //    _sourceItems.Add(new SourceItem() { Entity = testEnt, Component = renderableComp, LocalFiles = newfiles });
        }
    }
}
