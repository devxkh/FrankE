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
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Xml.Serialization;
using Microsoft.Practices.Unity;
using System.Collections.ObjectModel;
using VEF.Interfaces.Services;
using VEF.Core.Interface.Service;
using VEF.VEF_Helpers;
using VEX.IDAL;

namespace VEX.Core.Model
{
    public class VEXStateModel// : IItem
    {
        private ObservableCollection<IObjectEvent> m_ObjectEvents = new ObservableCollection<IObjectEvent>();

        public string Name { get; set; }
        public CollectionOfIItem Items { get; set; }

      //  public string ContentID { get; set; }

    ///    [Browsable(false)]
    //    [XmlIgnore]
     //   public List<MenuItem> MenuOptions { get; protected set; }

     //   private bool mIsExpanded;

    //    [XmlIgnore] //only manuell expand -> open!
    //    public bool IsExpanded { get { return mIsExpanded; } set { mIsExpanded = value; 
        //    if (!mOpened) Open(); 
    //    } }
        //public bool IsSelected { get; set; }
        //public bool Enabled { get; set; }
        //public bool Visible { get; set; }

        //[Browsable(false)]
        //[XmlIgnore]
        //public bool HasChildren { get { return Items != null && Items.Count > 0 ? true : false; } }

        //[Browsable(false)]
        //[XmlIgnore]
        //public IItem Parent { get; set; }

        /// <summary>
        /// gamestate Events
        /// </summary>
        [XmlIgnore]
        public ObservableCollection<IObjectEvent> ObjectEvents { get { return m_ObjectEvents; } set { m_ObjectEvents = value; } }

    //    protected IDatabaseService m_DBService;
        //private IDAL_DCTX m_DataContext;

        //[Browsable(false)]
        //[XmlIgnore]
        //public IDAL_DCTX DataContext
        //{
        //    get
        //    {
        //        if (m_DataContext == null)
        //            m_DataContext = ((IDAL.IDAL)m_DBService.CurrentDB).GetDataContextOpt(false) as IDAL_DCTX;

        //        return m_DataContext;
        //    }
        //    set
        //    {
        //        m_DataContext = value;
        //    }
        //}

     //   private bool mOpened;

        public bool Open()
        {
            //ScenesListModel scenesProto = new ScenesListModel(this, UnityContainer) { Name = "Scenes" };
            //scenesProto.IsExpanded = true;
            //this.Items.Add(scenesProto);

            //DBCategoryModel dbRuntime = new DBCategoryModel(this, UnityContainer) { Name = "Runtime Data (not needed now)" };
            ////DBCategoryModel players = new DBCategoryModel(dbRuntime, unityContainer) { Name = "Players" };
            ////DBCategoryModel player1 = new DBCategoryModel(players, unityContainer) { Name = "Player1" };
            ////DBCategoryModel charsPlayer = new DBCategoryModel(player1, unityContainer) { Name = "Characters" };
            ////DBCategoryModel char1Player = new DBCategoryModel(charsPlayer, unityContainer) { Name = "Character 1" };
            ////charsPlayer.Items.Add(char1Player);
            ////player1.Items.Add(charsPlayer);
            ////players.Items.Add(player1);
            ////dbRuntime.Items.Add(players);
            ////this.Items.Add(dbRuntime);

            //DBCategoryModel scriptMats = new DBCategoryModel(this, UnityContainer) { Name = "Materials (Scripts)" };
            ////DBCategoryModel mat1 = new DBCategoryModel(scriptMats, UnityContainer) { Name = "MaterialsScript1" };
            ////scriptMats.Items.Add(mat1);
            //this.Items.Add(scriptMats);

            //DBCategoryModel objects = new DBCategoryModel(this, UnityContainer) { Name = "GameEntites" };
            //objects.IsExpanded = true;

            //PhysicCategoryModel allOgreObjects = new PhysicCategoryModel(objects, UnityContainer) { Name = "Ogre Objects" };
            //allOgreObjects.Items.Add(new StaticObjectModel(allOgreObjects, UnityContainer) { Name = "Plane" });
            //allOgreObjects.Items.Add(new StaticObjectModel(allOgreObjects, UnityContainer) { Name = "Cube" });

            //try
            //{
            //    IEnumerable<IDAL.IDAL.EntityContainer> result = IDAL.IDAL.selectAllEntities(DataContext);

            //    if (result != null)
            //    {
            //        //select all Nodes
            //        foreach (var gameEntity in result)
            //        {
            //            // ProtoType.Node nodeDeserialized = ProtoSerialize.Deserialize<ProtoType.Node>(node.Node.Data);

            //            if (gameEntity.Entity.EntType == null)
            //                continue;

            //            //switch ((EntityTypes)gameEntity.Entity.EntType)
            //            //{
            //            //    case EntityTypes.NT_SpawnPoint:

            //            //        SpawnPointModel tmpSpawnPoint = new SpawnPointModel(allSpawns, UnityContainer, m_DBI)
            //            //        {
            //            //            ContentID = "SpawnPointID:##:" + gameEntity.Entity.EntID,
            //            //            Name = gameEntity.Entity.Name ?? ("Noname SpawnPoint " + (int)gameEntity.Entity.EntID),
            //            //            DBData = gameEntity
            //            //        };// Data = gameEntityDataDeserialized });

            //            //        allSpawns.Items.Add(tmpSpawnPoint);
            //            //        break;

            //            //    case EntityTypes.NT_Static:

            //            //        StaticObjectModel tmp = new StaticObjectModel(staticObjects, UnityContainer, m_DBI)
            //            //        {
            //            //            ContentID = "StaticID:##:" + gameEntity.Entity.EntID,
            //            //            Name = gameEntity.Entity.Name ?? ("Noname Static " + (int)gameEntity.Entity.EntID),
            //            //            DB_Entity = gameEntity
            //            //        };// Data = gameEntityDataDeserialized });

            //            //        staticObjects.Items.Add(tmp);
            //            //        break;
            //            //    case EntityTypes.NT_Character:

            //            //        CharacterObjModel tmpChar = new CharacterObjModel(characterObjects, UnityContainer, m_DBI)
            //            //        {
            //            //            ContentID = "CharacterObjID:##:" + gameEntity.Entity.EntID,
            //            //            Name = gameEntity.Entity.Name ?? ("Noname CharObj " + (int)gameEntity.Entity.EntID),
            //            //            DBData = gameEntity
            //            //        };// Data = gameEntityDataDeserialized });

            //            //        characterObjects.Items.Add(tmpChar);
            //            //        break;
            //            //    //case NodeTypes.Physic:

            //            //    //    ProtoType.PhysicsObject dataPhysObj = new ProtoType.PhysicsObject();
            //            //    //    if (gameEntity.Data != null)
            //            //    //        dataPhysObj = ProtoSerialize.Deserialize<ProtoType.PhysicsObject>(gameEntity.Data);

            //            //    //    allPhysics.Items.Add(new PhysicsObjectModel(allPhysics, UnityContainer, dataPhysObj, m_DBI) { ContentID = "PhysicID:##:" + gameEntity.EntID, Name = gameEntity.Name ?? ("Noname" + (int)gameEntity.EntID) });// Data = gameEntityDataDeserialized });

            //            //    //    break;
            //            //    case EntityTypes.NT_Camera:
            //            //        //todo contentid for camera

            //            //        //   SceneNodes = new SceneNodes() { NodeID = sNode.NodeID, EntID = sNode.Node.EntityID, SceneID = ID, Data = ProtoSerialize.Serialize(sNode.Node) };


            //            //        //var itemCam = m_SceneService.SelectedScene.SceneItems.Where(x => x.ContentID == ""); // Search for Camera category
            //            //        //if (itemCam.Any())
            //            //        //    itemCam.First().SceneItems.Add(new CameraModel(itemCam.First(), UnityContainer) { Node = nodeDeserialized });

            //            //        break;
            //            //    case EntityTypes.NT_Light:

            //            //        //var itemLight = m_SceneService.SelectedScene.SceneItems.Where(x => x.ContentID == "");
            //            //        //if (itemLight.Any())
            //            //        //    itemLight.First().SceneItems.Add(new LightModel(itemLight.First(), UnityContainer) { Node = nodeDeserialized });
            //            //        break;
            //            //}

            //        }
            //    }

            ////    objects.Items.Add(staticObjects);
            ////    objects.Items.Add(characterObjects);
            //////    objects.Items.Add(creatureObjects);
            ////   // objects.Items.Add(allPhysics);

            ////    objects.Items.Add(allTrigger);
            ////    objects.Items.Add(allSpawns);
            ////    objects.Items.Add(allLights);
            ////    objects.Items.Add(allSkies);
            ////    objects.Items.Add(allTerrains);
            ////    objects.Items.Add(allSounds);
            ////    objects.Items.Add(DynamicObjects);
            //}
            //catch (Exception ex)
            //{
            //    MessageBox.Show("Error:" + ex.Message);
            //}

            //    scenes.Items.Add(scene);
     //       this.Items.Add(objects);
           
            return true;

        }

        public bool Save() { return true; }
        public bool Delete() { return true; }

        public string Location { get; set; }

        public VEXStateModel()
        {
          //  m_DBI = new IDAL(UnityContainer);

        }

        //[Browsable(false)]
        //[XmlIgnore]
        //public IUnityContainer UnityContainer { get; private set; }

        //public GameStateModel(IItem parent, IUnityContainer unityContainer)
        //{
        //    Name = "GameStates";
        //    UnityContainer = unityContainer;
        //    Parent = parent;
        //    Items = new CollectionOfIItem();
        //    MenuOptions = new List<MenuItem>();

        //    MenuItem mib1a = new MenuItem();
        //    mib1a.Header = "Text.xaml";
        //    MenuOptions.Add(mib1a);

        //    m_DBI = new IDAL();






        //}


        //public bool Create(IUnityContainer unityContainer) { return true; }
        //public bool Open(IUnityContainer unityContainer, object id) { return true; }
        //public bool Save(object param) { return true; }
        //public bool Closing() { return true; }
        //public void Refresh() { }
        //public void Finish() { }
        //public void Drop(IItem item) { }
    }
}
