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
using System.Xml.Serialization;
using Microsoft.Practices.Unity;
using System.Windows.Input;
using Module.PFExplorer.Service;
using VEF.Interfaces.Services;
using VEF.View.Types;
using VEX.IDAL;
using VEF.Interface.History;
using VEF.Interfaces.Controls;
using VEX.Core.Shared.Interface.Net;
using VEF.Model.Services;
using VEF;
using VEF.Core.Interface.Service;
using VEX.Core.Shared.MDB;
using VEF.DAL.Interface;
using VEF.Model.PFExplorer;
using VEX.Model.Scene;
using VEX.Model.Project;
using VEX.Model.Scene.Model;
using System.Runtime.Serialization;
using VEF.IDAL;
using System.Windows;

namespace VEX.Core.Model.Project
{
    [KnownType(typeof(DBTableModel))]
    [KnownType(typeof(DBEntitiesModel))]
    [KnownType(typeof(DBScenesModel))]
    [KnownType(typeof(DBUIModel))]
    [KnownType(typeof(PrefabCategoryModel))]
    [DataContract(IsReference = true)]
    public class VEXDBFileModel : ProjectItemModel, IDBFileModel
    {
        private IDAL.IDAL m_DBI;
        private ICommand CmdDeleteDBFile;
        private string m_DBPath;

        [Editor(typeof(FilePathEditor), typeof(FilePathEditor))]
        [Description("path to sqlite database")]
        [DataMember]
        public string DBFilePath
        {
            get { return m_DBPath; }
            set
            {
                if (m_DBPath != value)
                    this.IsDirty = true;

                m_DBPath = value;
                RaisePropertyChanged("DBFilePath");
            }
        }

        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>();

                VEFMenuItem miAddItem = new VEFMenuItem() { Header = "Add existing item" };

                foreach (var type in CanAddThisItems)
                {
                    miAddItem.Items.Add(new MenuItem() { Header = type.Name, Command = new CmdAddExistingItemToDBFile(this), CommandParameter = type });
                }

                list.Add(miAddItem);            
                
                list.Add(new VEFMenuItem() { Header = "Compile Database data", Command = new CmdCompileDBData(this) });
           //     list.Add(new VEFMenuItem() { Header = "Truncate Database", Command = new CmdTruncateDBData(this) });

                VEFMenuItem miAddNewItem = new VEFMenuItem() { Header = "Add new item" };

                foreach (var type in CanAddThisItems)
                {
                    miAddNewItem.Items.Add(new MenuItem() { Header = type.Name, Command = new CmdAddNewItemToDBFile(this), CommandParameter = type });
                }
                list.Add(miAddNewItem);

                return list;
            }
        }

        public bool SaveToDB(IDAL_DCTX ctx)
        {
            foreach (var item in Items)
            {
                var dbFileItem = item as IDBFileItem;
                if (dbFileItem != null)
                {
                    return dbFileItem.SaveToDB(ctx);
                }
            }

            return true;
        }

        public bool Open(IUnityContainer unityContainer, object id)
        {
            m_DBI = new IDAL.IDAL();
            return true;
        }

        public bool Delete()
        {
            return true;
        }
        
        public override List<System.Type> CanAddThisItems
        {
            get
            {
                return new List<Type>() { typeof(SceneDataModel), typeof(UICategoyModel), typeof(PrefabCategoryModel) };
            }
        }

        public VEXDBFileModel()
        {
            CmdDeleteDBFile = new CmdDeleteDBFile(this);
        }

        public new bool Create()
        {
            m_DBI = new IDAL.IDAL();


            return true;
        }

        public new bool Save(object param)
        {
            return true;
        }

        public bool Closing() { return true; }
        public void Refresh() { }
        public void Finish() { }
        public void Drop(IItem item) { }
    }
    //public class CmdTruncateDBData : ICommand
    //{
    //    private VEXDBFileModel mpm;
    //    public event EventHandler CanExecuteChanged;


    //    public bool CanExecute(object parameter)
    //    {
    //        return true;
    //    }

    //    public void Execute(object parameter)
    //    {
    //        var dbservice = VEFModule.UnityContainer.Resolve(typeof(IDatabaseService), "") as IDatabaseService;
    //        var ctx = ((IDAL.IDAL)dbservice.CurrentDB).GetDataContextOpt(false);
    //        IDAL.IDAL.TruncateDatabase(ctx);
    //    }

    //    public CmdTruncateDBData(VEXDBFileModel pm)
    //    {
    //        mpm = pm;
    //    }
    //}

    public class CmdCompileDBData : ICommand
    {
        private VEXDBFileModel mpm;
        public event EventHandler CanExecuteChanged;


        private void RekursivSaveToDB(IItem item, IDAL_DCTX ctx)
        {
            if (item.Items.Count > 0)
            {
                foreach (var subItem in item.Items)
                {
                    if (subItem is IDBFileItem)// && subItem is INetID)
                    {
                        var netObj = subItem as IDBFileItem;
                        netObj.SaveToDB(ctx);

                    }

                    if (subItem.Items.Count > 0)
                        RekursivSaveToDB(subItem, ctx); // rekursiv
                }
            }
            else
            {
                if (item is IDBFileItem)// && item is INetID)
                {
                    var netObj = item as IDBFileItem;
                    netObj.SaveToDB(ctx);
                }
            }
        }

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            try
            {
                var dbservice = VEFModule.UnityContainer.Resolve(typeof(IDatabaseService), "") as IDatabaseService;

                IDALOptions options = dbservice.CurrentDB.DBOptions;
                options.Host = mpm.DBFilePath; //TODO use settings!!

                var ctx = ((IDAL.IDAL)dbservice.CurrentDB).GetDataContextOpt(false);

                IDAL.IDAL.TruncateDatabase(ctx);

                RekursivSaveToDB(mpm, ctx);

                //   Type t = parameter as Type;

                //to create the objects i need the parameter data!!!!
                //         mpm.Save();
                //if (t.Name == "SceneDataModel")
                //{
                //    //KH 29.03             mpm.Items.Add(new SceneDataModel() { Parent = mpm, UnityContainer = mpm.UnityContainer, Name = "new scene", ContentID = "SceneID:##:" });
                //    // Type instance = (Type)Activator.CreateInstance(t);
                //    // object obj = t.GetConstructor(new Type[] { }).Invoke(new object[] { });
                //    //   mpm.Items.Add(obj as IItem);
                //}
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public CmdCompileDBData(VEXDBFileModel pm)
        {
            mpm = pm;
        }
    }

    public class CmdAddNewItemToDBFile : IHistoryCommand
    {
        private VEXDBFileModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            Type t = parameter as Type;

            //to create the objects i need the parameter data!!!!
            //         mpm.Save();
            if (t.Name == "SceneDataModel")
            {
                //KH 29.03             mpm.Items.Add(new SceneDataModel() { Parent = mpm, UnityContainer = mpm.UnityContainer, Name = "new scene", ContentID = "SceneID:##:" });
                // Type instance = (Type)Activator.CreateInstance(t);
                // object obj = t.GetConstructor(new Type[] { }).Invoke(new object[] { });
                //   mpm.Items.Add(obj as IItem);
            }else if(t.Name == "UICategoyModel")
            {
              //  var instance = (Type)Activator.CreateInstance(t);
                object obj = t.GetConstructor(new Type[] { }).Invoke(new object[] { });
                mpm.Items.Add(obj as IItem);
            }
            else if (t.Name == "PrefabCategoryModel")
            {
                //  var instance = (Type)Activator.CreateInstance(t);
                object obj = t.GetConstructor(new Type[] { }).Invoke(new object[] { });
                mpm.Items.Add(obj as IItem);
            }
        }

        public CmdAddNewItemToDBFile(VEXDBFileModel pm)
        {
            mpm = pm;
        }

        public bool CanRedo() { return true; }
        public bool CanUndo() { return true; }
        public void Redo() { }
        public string ShortMessage() { return "add item"; }
        public void Undo() { }

    }
    public class CmdAddExistingItemToDBFile : IHistoryCommand
    {
        private VEXDBFileModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            Type t = parameter as Type;

            //to create the objects i need the parameter data!!!!
            //         mpm.Save();
            if (t.Name == "SceneDataModel")
            {
                //KH 29.03             mpm.Items.Add(new SceneDataModel() { Parent = mpm, UnityContainer = mpm.UnityContainer, Name = "new scene", ContentID = "SceneID:##:" });
                // Type instance = (Type)Activator.CreateInstance(t);
                // object obj = t.GetConstructor(new Type[] { }).Invoke(new object[] { });
                //   mpm.Items.Add(obj as IItem);
            }
        }

        public CmdAddExistingItemToDBFile(VEXDBFileModel pm)
        {
            mpm = pm;
        }

        public bool CanRedo() { return true; }
        public bool CanUndo() { return true; }
        public void Redo() { }
        public string ShortMessage() { return "add item"; }
        public void Undo() { }

    }

    public class CmdDeleteDBFile : ICommand
    {
        private VEXDBFileModel m_model;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            m_model.Items.Clear();
            m_model.Parent.Items.Remove(m_model);
            //IDAL dbI = new IDAL();

            m_model.Delete();
            //// To serialize the hashtable and its key/value pairs,  
            //// you must first open a stream for writing. 
            //// In this case, use a file stream.
            //using (MemoryStream inputStream = new MemoryStream())
            //{
            //    // write to a file
            //    ProtoBuf.Serializer.Serialize(inputStream, mpm.Data);

            //    if (mpm.ID > -1)
            //        dbI.updatePhysics(mpm.ID, inputStream.ToArray());
            //    else
            //        dbI.insertPhysics(mpm.ID, inputStream.ToArray());
            //}

            //DLL_Singleton.Instance.updateObject(0, (int)ObjType.Physic);
        }

        public CmdDeleteDBFile(VEXDBFileModel model)
        {
            m_model = model;
        }
    }
}