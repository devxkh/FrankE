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
using System.Windows.Controls;
using Microsoft.Practices.Unity;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using System.Xml.Serialization;
using VEX.Model.Scene.Model.Objects;
using System.Windows.Input;
using VEX.Model.Scene.Model.Objects.ObjectData;
using System.Windows;
using System.IO;
using VEF.VEF_Helpers;
using VEX.Service.Scene;
using VEX.IDAL;
using VEF.Interfaces.Services;
using VEF.Core.Interface.Service;
using VEF;
using VEF.Interfaces.Controls;
using VEX.IDAL.MDB;
using VEX.Interface.DAL;
using VEX.Core.Shared.Interface.Net;
using VEF.DAL.Interface;

namespace VEX.Model.Scene.Model
{
    //public class RaceGenderItemsSource : IItemsSource
    //{
    //    public Xceed.Wpf.Toolkit.PropertyGrid.Attributes.ItemCollection GetValues()
    //    {
    //        Xceed.Wpf.Toolkit.PropertyGrid.Attributes.ItemCollection raceGenders = new Xceed.Wpf.Toolkit.PropertyGrid.Attributes.ItemCollection();
          
    //        raceGenders.Add(0, "Human NEU");
    //        raceGenders.Add(1, "Human WEU");
    //        return raceGenders;
    //    }
    //}

    //public class CharacterEntity : EntityX , IDBFileItem, INetID
    //{

    //    #region INETID

    //    public bool Replicate { get; set; }


    //    private ushort _netID;

    //    [ExpandableObject]
    //    public FB_CharacterObject FBObject { get; set; }

    //    public virtual bool SendToSocket() { return false; }

    //    public IFBObject getFBObject() { return FBObject; }

    //    [XmlIgnore]
    //    public ushort NetID { get { return _netID; } set { _netID = value; RaisePropertyChanged("NetID"); } }

    //    #endregion
        
    //    public void Drop(IItem item)
    //    {
    //        //if (item is CharacterCustomizeModel)
    //        //{

    //        //}

    //      //  if (item is FileItem)
    //      //  {
    //      //   //   if (mData.gameEntity == null)
    //      //   //       mData.gameEntity = new ProtoType.GameEntity();

    //      ////      ProtoType.Mesh mesh = new ProtoType.Mesh();
    //      //   //   mesh.Name = (item as FileItem).ContentID;
    //      //    //  mData.gameEntity.meshes.Add(mesh);
    //      //  }
    //    }
 
    //    [XmlIgnore]
    //    [Browsable(false)]
    //    public IDAL.IDAL.EntityContainer DB_Entity { get; set; }

    ////    #region GameEntityData


    //    //  private List<String> mMeshes;
    //    //private List<Mesh> mMeshes;
    //    //[Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
    //    //[NewItemTypes(new Type[] { typeof(Mesh), typeof(Plane), typeof(Cube) })]
    //    //[Category("GameEntity")]
    //    //public List<Mesh> Meshes { get { return mMeshes; } set { mMeshes = value; } }
    //    //public List<ProtoType.Mesh> Meshes { get { return mData.gameEntity.meshes; } }

    //    //private List<PhysicObject> m_Physics;
    //    //[Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
    //    //[Category("GameEntity")]
    //    //public List<PhysicObject> Physics { get { return m_Physics; } set { m_Physics = value; } }

    //    //private List<ProtoType.Sound> mSounds;
    //    //[Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
    //    //[NewItemTypes(new Type[] { typeof(ProtoType.Sound) })]
    //    //[Category("GameEntity")]
    //    //public List<ProtoType.Sound> Sounds { get { return mSounds; } set { mSounds = value; } }

    //    //[Category("GameEntity")]
    //    //public Int32 RenderQueue { get { return mData.gameEntity.mode; } set { mData.gameEntity.mode = value; } }

    //    //[Category("GameEntity")]
    //    //public Int32 Mode { get { return mData.gameEntity.mode; } set { mData.gameEntity.mode = value; } }
    //    //[Category("GameEntity")]
    //    //public bool CastShadows { get { return mData.gameEntity.castShadows; } set { mData.gameEntity.castShadows = value; } }
    //    //[Category("GameEntity")]
    //    //public string AnimationTree { get { return mData.gameEntity.animationTree; } set { mData.gameEntity.animationTree = value; } }
    //    //[Category("GameEntity")]
    //    //public string AnimationInfo { get { return mData.gameEntity.animationInfo; } set { mData.gameEntity.animationInfo = value; } }
      
    //    //[Category("Debug")]
    //    //public ProtoType.Debug Debug { get { return mData.gameEntity.debug; } set { mData.gameEntity.debug = value; } }

    //    //private long m_Race;
    //    //[Category("Character")]
    //    //public long RaceID { get { return m_Race; } set { m_Race = value; } }
      

    ////    #endregion
        
   
    //    [XmlIgnore]
    //    [Browsable(false)]
    //    public override List<IMenuItem> MenuOptions
    //    {
    //        get
    //        {
    //            List<IMenuItem> list = new List<IMenuItem>();
    //            VEFMenuItem miSave = new VEFMenuItem() { Command = CmdSaveCharacterObj, Header = "Save" };
    //            list.Add(miSave);
    //            return list;
    //        }
    //    }
        
    //    public override bool Open(object id)
    //    {
    //        //read data from lokal json file
    //      //  FBObject = ObjectSerialize.Deserialize<FB_CharacterObject>(ItemFolder + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml"); //ProtoSerialize.Deserialize<ProtoType.Node>(node.Data);
    //        if (FBObject == null)
    //            Create();
    //        else
    //            RaisePropertyChanged("FB_CharacterObject");

    //        //  m_FBData.SetFBData(m_FBData..EntityBaseModel); //set base entity data

    //        //test
    //        //   m_FBData.Read(DB_Entity.Entity.Data);
    //        return true;
    //    }

    //    private ICommand CmdSaveCharacterObj;

    //    public void Refresh() { }
    //    public void Finish() { }


    //    public bool SaveToDB(IDAL_DCTX ctx)
    //    {
    //        string DBPath = DBFileUtil.GetDBFilePath(this.Parent);
    //        if (!String.IsNullOrEmpty(DBPath))
    //        {
    //            DB_Entity.Entity.Data = FBObject.CreateFBData()._fbData;
    //            DB_Entity.Entity.Name = Name;
    //            DB_Entity.Entity.EntID = VEF_Helper.StringToContentIDData(ContentID).IntValue;
    //            DB_Entity.Entity.replicate = Replicate;
    //            //  if (VEF_Helper.StringToContentIDData(ContentID).IntValue > 0)
    //            //      DB_Entity.Entity.EntID = VEF_Helper.StringToContentIDData(ContentID).IntValue;

    //            //test
    //            //##   FBObject.Value = DB_Entity.Entity.Data;

    //            //if (DB_Entity.Entity.EntID > 0)
    //            //    m_dbI.updateEntity(DB_Entity.Entity);
    //            //else
    //            //{
    //            DB_Entity.Entity.EntType = (decimal)EntityTypes.NT_Character;
    //      IDAL.IDAL.insertEntity(ctx, DB_Entity.Entity);
    //                //    ContentID = ContentID + ":" + DB_Entity.Entity.EntID;
    //        //    }
    //        }

    //        return true;
    //    }

    //    public override bool Save(object param)
    //    {
    //        try
    //        {
    //        //    SaveToDB();

    //      //      ObjectSerialize.Serialize<IFBObject>(FBObject, ItemFolder + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml");  // XML Serialize

    //        }
    //        catch (Exception ex)
    //        {
    //            MessageBox.Show("error: " + ex.Message);
    //        }
    //        return true;
    //    }

    //    public override  bool Create()
    //    {
    //        FBObject = new FB_CharacterObject() { Parent = this };

    //        RaisePropertyChanged("FB_CharacterObject");
         
    //        return true;
    //    }

    //    public override  bool Delete()
    //    {
    //        try
    //        {
    //            Parent.Items.Remove(this);

    //            //if (File.Exists(ItemFolder + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml"))
    //            //    File.Delete(ItemFolder + VEF_Helper.StringToContentIDData(ContentID).IntValue + ".xml");

    //            MessageBox.Show("character entity deleted");
    //        }
    //        catch (Exception ex)
    //        {
    //            MessageBox.Show("Error: character entity not deleted: " + ex.Message);
    //        }
    //        return true;
    //    }

    //    public CharacterEntity()
    //    { 
    //        CmdSaveCharacterObj = new CmdSaveCharacterObject(this);
            
    //        DB_Entity = new IDAL.IDAL.EntityContainer();
    //        DB_Entity.Entity = new Entity();
          
    //    }
    //}


    //public class CmdSaveCharacterObject : ICommand
    //{
    //    private CharacterEntity m_CharacterObjModel;
    //    public event EventHandler CanExecuteChanged;

    //    public bool CanExecute(object parameter)
    //    {
    //        return true;
    //    }

    //    public void Execute(object parameter)
    //    {
    //        m_CharacterObjModel.Save(parameter);
    //    }

    //    public CmdSaveCharacterObject(CharacterEntity som)
    //    {
    //        m_CharacterObjModel = som;
    //    }
    //}
}