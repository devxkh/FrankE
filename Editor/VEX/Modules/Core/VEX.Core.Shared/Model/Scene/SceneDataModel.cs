#region License

//The MIT License (MIT)

//Copyright (c) 2014 Konrad Huber

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#endregion

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;
using System.Xml.Serialization;
using Microsoft.Practices.Unity;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using VEX.Model.Scene.Model.Objects;
using VEX.Service.Scene;
using VEX.IDAL;
using VEX.Interface.Scene;
using VEF.Interfaces.Services;
using VEF.Interfaces.Controls;
using VEF.Core.Interface.Service;
using VEF.Interfaces.PFExplorer;
using VEF.VEF_Helpers;
using VEF.Utils;
using VEF;
using VEX.Commands.Scene;
using VEX.Core.Shared.Interface.Net;
using VEX.Interface.DAL;
using VEF.DAL.Interface;
using VEX.Core.Model.Services;
using System.Collections.Specialized;
using Module.PFExplorer.Service;
using System.Runtime.Serialization;
using VEX.Core.Model.Project;
using VEF.IDAL;

namespace VEX.Model.Scene.Model
{
    public enum EntityTypes : ushort
    {
        NT_Unkown,
        NT_Physic,
        NT_Character,
        NT_Static,
        NT_Terrain,
        NT_Light,
        NT_Camera,
        NT_SpawnPoint,
    }

    /// <summary>
    /// Complete Scene description
    /// </summary>
    [DataContract]
    public class SceneDataModel : ProjectItemModel, IDBFileItem, INetID
    {
        private ISceneService m_SceneService;
        private object mSelectedItem;
        private ObservableCollection<EntityX> _Entities;

        [DataMember]
        public ObservableCollection<EntityX> Entities
        {
            get { return _Entities; }
            set
            {
                if (_Entities == null && value != null)
                    value.CollectionChanged += this.OnCollectionChanged;

                _Entities = value;


            } //needed for xml serialization
        }

        [DataMember]
        public ushort SceneID { get; set; }

        void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var newItem in e.NewItems)
                {
                    var entity = newItem as EntityX;
                    if (entity != null)
                    {
                       // entity.Parent = this;

                        var parent = this.Parent as VEXDBFileModel;
                        if (parent != null)
                        {
                            var ecm = parent.Items.Where(x => x is DBEntitiesModel);
                            if(ecm.Any())
                            {
                                var entityList = ecm.First();
                                entity.EntityID = (uint)entityList.Items.Count + 1;
                                entityList.Items.Add(entity);

                            }
                        }
                        var parentSceneCategoryModel = this.Parent as SceneCategoryModel;
                        if (parentSceneCategoryModel != null)
                        {
                            var sdm = parentSceneCategoryModel.Items.Where(x => x is SceneDataModel);
                            if (sdm.Any())
                            {
                                var scenesList = sdm.First();
                                scenesList.Items.Add(entity);

                            }
                        }

                    }
                }
            }
        }

        [Browsable(false)]
        public NetMsg.Data Type { get { return NetMsg.Data.Scene; } }

        public override void Drop(IItem item)
        {
            try
            {
                //if (item is IEntity)
                //{
                //    if(FBObject == null)
                //    {
                //      //  MessageBox.Show
                //    }

                //    var sceneItem = item as EntityX;
                //    createNewNode(sceneItem);

                //}
            }
            catch (Exception ex)
            {

            }
        }

        #region INETID

        private ushort _netID;

        [Browsable(false)]
        public IFBObject FBObject { get; set; }

        [ExpandableObject]
        [DataMember]
        public FB_Scene FB_Scene { get { return FBObject as FB_Scene; } set { FBObject = value; } }

        public virtual bool SendToSocket()
        {
            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;
            //if (NetID <= 0)
            //    NetID = _SocketServerManager.NewNetID();

            var fbdata = FBObject.CreateFBData();

            FBObject.Read(fbdata._fbData);

            return _SocketServerManager.SendMessageToServer(NetID, SceneID, NetMsg.Data.Scene, fbdata);
        }

        public ushort NetID { get { return _netID; } set { _netID = value; RaisePropertyChanged("NetID"); } }

        #endregion

        public bool AddEntity(EntityX node)
        {
            if (!Entities.Contains(node))
            {
                Entities.Add(node);
                return true;
            }
            return false;
        }
        
        [Browsable(false)]
        public object SelectedItem
        {
            get { return mSelectedItem; }
            set
            {
                mSelectedItem = value;

                m_SceneService.SGTM.SelectedObject = value;
            }
        }

        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>();

                list.Add(new VEFMenuItem() { Command = new CmdDeleteScene(this), Header = "Delete scene" });

                list.Add(new VEFMenuItem() { Command = new CmdSceneSendToServer(this), Header = "SendToServer" });

                return list;
            }
        }


        #region public command methods

        public override bool Create()
        {
            m_SceneService = VEFModule.UnityContainer.Resolve(typeof(ISceneService), "") as ISceneService;

            RaisePropertyChanged("FB_SceneData");

            return true;
        }

        public override bool Closing()
        {
            return true;
        }

        public override bool Open(object id)
        {
            m_SceneService = VEFModule.UnityContainer.Resolve(typeof(ISceneService), "") as ISceneService;

            int sceneID = VEF_Helper.StringToContentIDData(ContentID).IntValue;

            //  this.Location = ItemFolder + "\\" + sceneID + ".xml";

            //read sceneData from DAL -- Read data from XML not from database -> database data not human readable
            //9_01_2015      m_FBData = ObjectSerialize.Deserialize<FB_Scene>(this.Location.ToString()); // XML Serialize
            if (FBObject == null)
                Create();
            else
                RaisePropertyChanged("FB_SceneData");

            RaisePropertyChanged("SceneItems");

            m_SceneService.SelectedScene = this;

            //only able to save data into database not load
            return true;
        }

        public void Refresh() { }
        public void Finish() { }

        public bool SaveToDB(IDAL_DCTX ctx)
        {
            string DBPath = DBFileUtil.GetDBFilePath(this.Parent);
            if (!String.IsNullOrEmpty(DBPath))
            {
                IDAL.MDB.Scene dbSceneData = new IDAL.MDB.Scene();
                dbSceneData.Data = FBObject.CreateFBData()._fbData;
                dbSceneData.SceneID = SceneID;
                dbSceneData.Name = this.Name;
                
                IDAL.IDAL.insertScene(ctx, dbSceneData);

                uint nodeCount = 0;
                
                foreach (var sceneitem in Entities)
                {
                    var entity = sceneitem as EntityX;
                    if (entity != null)
                    {
                      //  entity.SaveToDB(ctx);

                        var m_SceneNodeDB = new IDAL.MDB.SceneNode();

                        var body = entity.GetComponentX<BodyComponent>() as BodyComponent;
                        if (body != null)
                        {
                            //if (body.SceneNodeID <= 0)
                            //    MessageBox.Show("SceneNodeID <= 0!");
                            //else {
                            m_SceneNodeDB.Data = body.FBObject.CreateFBData()._fbData;

                            m_SceneNodeDB.Name = Name;
                            m_SceneNodeDB.SceneID = SceneID;
                            m_SceneNodeDB.NodeID = nodeCount = nodeCount + 1;
                            m_SceneNodeDB.EntID = entity.EntityID;

                            //save sceneNode to db
                            if (m_SceneNodeDB.NodeID > 0)
                                IDAL.IDAL.insertSceneNode(ctx, m_SceneNodeDB);
                            //    }
                        }
                    }
                }

            }
            return true;

        }

        public override bool Save(object param)
        {
            //   this.Location = ItemFolder + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml";

            return true;
        }

        public override bool Delete()
        {
            //  this.Location = ItemFolder + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml";

            this.Parent.Items.Remove(this);

            return true;
        }

        #endregion

        public SceneDataModel()
        {
            _Entities = new ObservableCollection<EntityX>();

            _Entities.CollectionChanged += this.OnCollectionChanged;

            FBObject = new FB_Scene() { Parent = this };
         
        }

        #region contentmodel

        internal void SetLocation(object location)
        {
            this.Location = location;
            RaisePropertyChanged("Location");
        }

        internal void SetDirty(bool value)
        {
            this.IsDirty = value;
        }

        #endregion
    }



    public class CmdSceneSendToServer : ICommand
    {
        private SceneDataModel _SceneData;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            _SceneData.SendToSocket();

        }

        public CmdSceneSendToServer(SceneDataModel som)
        {
            _SceneData = som;
        }
    }

}
