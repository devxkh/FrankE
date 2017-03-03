//#region License

////The MIT License (MIT)

////Copyright (c) 2014 Konrad Huber

////Permission is hereby granted, free of charge, to any person obtaining a copy
////of this software and associated documentation files (the "Software"), to deal
////in the Software without restriction, including without limitation the rights
////to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
////copies of the Software, and to permit persons to whom the Software is
////furnished to do so, subject to the following conditions:

////The above copyright notice and this permission notice shall be included in all
////copies or substantial portions of the Software.

////THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
////IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
////FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
////AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
////LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
////OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
////SOFTWARE.

//#endregion

//using System;
//using System.Collections.Generic;
//using System.ComponentModel;
//using System.Windows.Controls;
//using Microsoft.Practices.Unity;
//using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
//using System.Windows.Input;
//using System.Xml.Serialization;
//using VEX.Model.Scene.Model.Objects;
//using System.Windows;
//using System.IO;
//using VEF.VEF_Helpers;
//using VEF.Core.Interface.Service;
//using VEX.Service.Scene;
//using VEX.IDAL;
//using VEF.Interfaces.Services;
//using VEF.Interfaces.Controls;
//using VEF;
//using VEX.IDAL.MDB;
//using VEX.Interface.DAL;
//using VEX.Core.Shared.Interface.Net;
//using VEF.DAL.Interface;
//using VEX.Core.Model.Services;
//using VEX.Interface.Scene;
//using Module.PFExplorer.Service;
//using VEX.Core.Shared.Service.Scene;

//namespace VEX.Model.Scene.Model
//{
//    [XmlInclude(typeof(BodyComponent))]

//    public class StaticObjectModel : ComponentX,  IEntityComponent
//    {

//      //  public NetMsg.Data Type { get { return NetMsg.Data.RenderableComponent; } }

//        public void Drop(IItem item)
//        {
//            //if(item is FileItem)
//            //{
//            //    if (m_FBData == null )
//            //        this.Open(item.UnityContainer, this.ContentID);

//            //    //todo
//            //    //ProtoType.Mesh mesh = new ProtoType.Mesh();
//            //    //mesh.Name = (item as FileItem).ContentID;
//            //    //mData.gameEntity.meshes.Add(mesh);
//            //}
//        }


//        #region INETID

//      //  public  uint SceneItemID { get; set; }

//     //   public bool Replicate { get; set; }

        
//        [XmlIgnore]
//        [Browsable(false)]
//        public IFBObject FBObject { get; set; }

//        [ExpandableObject]
//        public FB_StaticObjectModel FB_StaticObjectModel { get { return FBObject as FB_StaticObjectModel; } set { FBObject = value; } }
        
//        #endregion
        
//        [XmlIgnore]
//        [Browsable(false)]
//        public override List<IMenuItem> MenuOptions
//        {
//            get
//            {
//                List<IMenuItem> list = new List<IMenuItem>() {
//                    new VEFMenuItem() { Header = "IsVisible" },
//                    new VEFMenuItem() { Command = CmdDeleteStaticObj, Header = "Delete" },
//                   // new VEFMenuItem() { Command = new CmdSendToServer(this), Header = "SendToServer" }
//                };
//                return list;
//            }
//        }




//        public override bool Open(object id)
//        {
//            //read data from lokal json file
//            //  FBObject = ObjectSerialize.Deserialize<FB_StaticObjectModel>(ItemFolder + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml"); //ProtoSerialize.Deserialize<ProtoType.Node>(node.Data);
//            if (FBObject == null)
//                Create();
//            else
//                RaisePropertyChanged("FB_StaticObject");

//            // m_FBData.SetFBData(m_FBData.EntityBaseModel); //set base entity data

//            //test
//            //   m_FBData.Read(DB_Entity.Entity.Data);
//            return true;
//        }

//        public void Refresh() { }
//        public void Finish() { }

//        //public bool SaveToDB(IDAL_DCTX ctx)
//        //{
//        //    string DBPath = DBFileUtil.GetDBFilePath(this.Parent);
//        //    if (!string.IsNullOrEmpty(DBPath))
//        //    {
//        //        var DB_Entity = new IDAL.IDAL.EntityContainer();
//        //        DB_Entity.Entity = new Entity();
//        //        DB_Entity.Entity.Data = FBObject.CreateFBData()._fbData;
//        //        DB_Entity.Entity.Name = Name;
//        //        DB_Entity.Entity.replicate = true; // Replicate;

//        //        // if (VEF_Helper.StringToContentIDData(ContentID).IntValue > 0)
//        //        DB_Entity.Entity.EntID = VEF_Helper.StringToContentIDData(ContentID).IntValue;

//        //        //test
//        //        FBObject.Read(DB_Entity.Entity.Data);

//        //        //if (DB_Entity.Entity.EntID > 0)
//        //        //    m_dbI.updateEntity(DB_Entity.Entity);
//        //        //else
//        //        //{
//        //        DB_Entity.Entity.EntType = (decimal)EntityTypes.NT_Static;
//        //        IDAL.IDAL.insertEntity(ctx, DB_Entity.Entity);
//        //        //       ContentID = ContentID + ":" + DB_Entity.Entity.EntID;
//        //        //   }
//        //    }
//        //    return true;
//        //}

//        public override bool Save(object param)
//        {
//            try
//            {
//                //   SaveToDB();
//                // m_FBData.EntityBaseModel = m_FBData.EntityBaseModel;
//                //   ObjectSerialize.Serialize<IFBObject>(FBObject, ItemFolder + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml");  // XML Serialize

//            }
//            catch (Exception ex)
//            {
//                MessageBox.Show("error: " + ex.Message);
//            }
//            return true;
//        }

//        private ICommand CmdSaveStaticObj;
//        private ICommand CmdDeleteStaticObj;

//        public override bool Create()
//        {
//            RaisePropertyChanged("FB_StaticObject");

//            //base.m_DBService = VEFModule.UnityContainer.Resolve(typeof(IDatabaseService), "") as IDatabaseService;
//            // DataContext.Context = ((IDAL.IDAL)m_DBService.CurrentDB).GetDataContextOpt(false);

//            return true;
//        }
//        public override bool Delete()
//        {
//            try
//            {
//                Parent.Items.Remove(this);

//                //if (File.Exists(ItemFolder + "\\" + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml"))
//                //    File.Delete(ItemFolder + "\\" + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml");

//                MessageBox.Show("Static entity deleted");
//            }
//            catch (Exception ex)
//            {
//                MessageBox.Show("Error: static entity not deleted: " + ex.Message);
//            }
//            return true;
//        }
//        public bool Closing() { return true; }

//        /// <summary>
//        /// Default contructor for serialization
//        /// </summary>
//        public StaticObjectModel()
//        {
//            CmdDeleteStaticObj = new CmdDeleteStaticObject(this);

//            FBObject = new FB_StaticObjectModel() { Parent = this };

//            //    Name = "New Static Obj";
//        }

//        public class CmdDeleteStaticObject : ICommand
//        {
//            private StaticObjectModel m_StaticObjectModel;
//            public event EventHandler CanExecuteChanged;

//            public bool CanExecute(object parameter)
//            {
//                return true;
//            }

//            public void Execute(object parameter)
//            {
//                m_StaticObjectModel.Delete();
//            }

//            public CmdDeleteStaticObject(StaticObjectModel som)
//            {
//                m_StaticObjectModel = som;
//            }
//        }
//    }
//}
