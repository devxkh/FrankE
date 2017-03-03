using FlatBuffers;
using Module.PFExplorer.Service;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using VEF;
using VEF.Core.Interface.Service;
using VEF.DAL.Interface;
using VEF.IDAL;
using VEF.Interface.History;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEF.Utils;
using VEX.Core.Model.Services;
using VEX.Core.Shared.Interface.Net;
using VEX.Core.Shared.Service.Scene;
using VEX.Core.Shared.ViewModel.Editor.Components;
using VEX.IDAL;
using VEX.Interface.DAL;
using VEX.Interface.Scene;
using VEX.Model.Scene;
using VEX.Model.Scene.Model;
using VEX.Model.Scene.Model.Objects;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Service.Scene
{
    //[KnownType(typeof(BodyComponent))]
    //[KnownType(typeof(RenderableComponent))]
    //[KnownType(typeof(SpawnPointComponent))]
    //[KnownType(typeof(SpawnComponent))]
    //[KnownType(typeof(LightComponent))]
    //[KnownType(typeof(CharacterComponent))]
    //[KnownType(typeof(AIComponent))]
    //[KnownType(typeof(AnimationComponent))]
    //[KnownType(typeof(PhysicsComponent))]
    //[KnownType(typeof(SoundComponent))]
    [KnownType("GetKnownTypes")]
    [DataContract(IsReference = true)]
    [ExpandableObject]
    public class EntityX : PItem, INetID
    {
        static IEnumerable<Type> GetKnownTypes()
        {
            return new Type[]
             {
                typeof(BodyComponent),
                typeof(RenderableComponent),
                typeof(SpawnPointComponent),
                typeof(SpawnComponent),
                typeof(LightComponent),
                typeof(CharacterComponent),
                typeof(AIComponent),
                typeof(AnimationComponent),
                typeof(PhysicsComponent),
                typeof(SoundComponent),
                typeof(AbilityComponent),
              };
        }

        //[DataMember]
        //public SceneDataModel ParentScene { get; set; }
        //[DataMember]
        //public ushort SceneID { get; set; }

        public bool Watch { get; set; }

        public uint EntityID
        {
            get { return FB_Entity.EntityID; }
            set
            {
                FB_Entity.EntityID = value; RaisePropertyChanged("EntityID");
            }
        }
        
        /// <summary>
        /// used for socket scene sync
        /// </summary>
        private uint _SceneID { get; set; }
        public uint SceneID
        {
            get { return _SceneID; }
            set {    _SceneID = value; RaisePropertyChanged("SceneID");    }
        }

        private uint _NetID { get; set; }
        public uint NetID
        {
            get { return _NetID; }
            set { _NetID = value; RaisePropertyChanged("NetID"); }
        }

        
       // [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        [NewItemTypes(new Type[] { typeof(BodyComponent),typeof(AIComponent), typeof(RenderableComponent), typeof(SpawnPointComponent), typeof(SpawnComponent), typeof(CharacterComponent),
            typeof(LightComponent),typeof(AbilityComponent), typeof(AnimationComponent) , typeof(PhysicsComponent) , typeof(SoundComponent)})]
        [ExpandableObject]
        public ComponentsList<ComponentX> Components
        {
            get {
               return FB_Entity.Components;
            }
            set {
                FB_Entity.Components = value;//for serializer
            } 
        }


        void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var newItem in e.NewItems)
                {
                    var componentX = newItem as ComponentX;
                    if (componentX != null)
                    {
                        componentX.Parent = this;

                        var body = componentX as BodyComponent;
                        if (body != null && componentX.Parent.Parent != null)
                        {
                        //    body.SceneNodeID = (uint)(this.Parent as DBEntitesModel).Items.Count; // currentlty nodeid = entityID -> one body per entity!
                        }

                    }
                }
            }
        }

        [Browsable(false)]
        public virtual IFBObject FBObject { get; protected set; }

        [DataMember]
        [ExpandableObject]
        public FB_Entity FB_Entity { get { return FBObject as FB_Entity; }
            set {

                if(FBObject == null)
                     value.Components.CollectionChanged += this.OnCollectionChanged;

                FBObject = value;
            } }


        public override List<System.Type> CanAddThisItems
        {
            get
            {
                return new List<Type>() { typeof(BodyComponent), typeof(AIComponent), typeof(AbilityComponent),typeof(RenderableComponent), typeof(AnimationComponent), typeof(SpawnPointComponent)
                , typeof(SpawnComponent), typeof(PhysicsComponent), typeof(LightComponent), typeof(SoundComponent), typeof(CharacterComponent)};
            }
        }

        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {              
                List<IMenuItem> list = new List<IMenuItem>() {
                    new VEFMenuItem() { Header = "IsVisible" },
                    new VEFMenuItem() { Command = new CmdDeleteObject(this), Header = "Remove" },
                    new VEFMenuItem() { Command = new CmdSendToServer(this), Header = "SendToServer" }
                };

                VEFMenuItem miAddItem = new VEFMenuItem() { Header = "Add Item" };

                foreach (var type in CanAddThisItems)
                {
                    miAddItem.Items.Add(new MenuItem() { Header = type.Name, Command = new CmdAddComponent(this), CommandParameter = type });
                }

                list.Add(miAddItem);
            
                return list;
            }
        }

        public ComponentX GetComponentX<T>()
        {
            var result = FB_Entity.Components.Where(x => x is T);
            if(result.Any())
            {
                return result.First();
            }
            return null;
        }

        public EntityX()
        {
            FBObject = new FB_Entity();
            FBObject.Parent = this;
            FB_Entity.Components.CollectionChanged += this.OnCollectionChanged;
        }

        public bool SaveToDB(IDAL_DCTX ctx)
        {
            string DBPath = DBFileUtil.GetDBFilePath(this.Parent);
            if (!string.IsNullOrEmpty(DBPath))
            {              
                FlatBuffers.FlatBufferBuilder fbbEntities = new FlatBuffers.FlatBufferBuilder(5);

                IDAL.MDB.Entity dbEnt = new IDAL.MDB.Entity();
                dbEnt.EntID = FB_Entity.EntityID;
                dbEnt.Name = Name;
                dbEnt.Data = this.FBObject.CreateFBData(fbbEntities)._fbData;
                dbEnt.replicate = true;

                this.FBObject.Read(dbEnt.Data);

                IDAL.IDAL.insertEntity(ctx, dbEnt);
            }

            return true;
        }

        public virtual void SendToSocket(IFBObject FBObject, NetMsg.Data msgType, List<Type> types = null)
        {
            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;

            if (FBObject != null)
            {
                FlatBufferBuilder fbb = new FlatBufferBuilder(4);
                FBNetData fbData;

                if(types == null)
                    fbData = FB_Entity.CreateFBData(fbb); 
                else
                    fbData = FB_Entity.CreateFBData(types,fbb); 
           
                _SocketServerManager.SendMessageToServer(NetID, 0, msgType, fbData);
            }
        }
    }

    public class CmdAddComponent : IHistoryCommand
    {
        private EntityX mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            Type type = parameter.GetType();
            string name = parameter.ToString();

            var newObj = System.Reflection.Assembly.GetExecutingAssembly().CreateInstance(name); // Activator.CreateInstance(name);
            var instance = newObj as ComponentX;
            if (instance != null)
            {
                mpm.Components.Add(instance);

                (VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService).Log("Component created:" + instance.Name, LogCategory.Info, LogPriority.Medium);
            }
        }

        public CmdAddComponent(EntityX pm)
        {
            mpm = pm;
        }

        public bool CanRedo() { return true; }
        public bool CanUndo() { return true; }
        public void Redo() { }
        public string ShortMessage() { return "add item"; }
        public void Undo() { }

    }

    public class CmdDeleteObject : ICommand
    {
        private EntityX m_EntityX;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            if(m_EntityX.Parent is SceneDataModel)
                (m_EntityX.Parent as SceneDataModel).Items.Remove(m_EntityX);

            if(m_EntityX.Parent is DBEntitiesModel)
                (m_EntityX.Parent as DBEntitiesModel).Items.Remove(m_EntityX);
            //TODO delete entites from scene collections!
        }

        public CmdDeleteObject(EntityX som)
        {
            m_EntityX = som;
        }
    }

    public class CmdSendToServer : ICommand
    {
        private EntityX _SceneNodeEntity;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            _SceneNodeEntity.SendToSocket(_SceneNodeEntity.FBObject, NetMsg.Data.Entity);

        }

        public CmdSendToServer(EntityX som)
        {
            _SceneNodeEntity = som;
        }
    }
}
