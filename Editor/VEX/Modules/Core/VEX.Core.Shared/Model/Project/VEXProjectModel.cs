#region License

// Copyright (c) 2014 Huber Konrad
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#endregion

using System.Collections.ObjectModel;
using System.Windows.Input;
using System.ComponentModel;
using System.Collections.Generic;
using System.Windows.Controls;
using System;
using System.Linq;
using Module.PFExplorer;
using System.Xml.Serialization;
using System.Xml;
using System.Xml.Schema;
using Microsoft.Practices.Unity;
using System.IO;
using Module.PFExplorer.Service;
using VEF.Interfaces.Services;
using VEF.View.Types;
using VEF.Interface.History;
using VEF.VEF_Helpers;
using VEF.Core.Util;
using VEX.Core.Shared.Interface.Services;
using VEF.IDAL;
using VEF;
using VEF.Interfaces.Controls;
using VEX.Model.Scene;
using VEF.Model.PFExplorer;
using VEX.Model.Scene.Model;
using VEX.Model.Project;
using System.Runtime.Serialization;
using VEX.Core.Shared.ViewModel.Editor.AnimationNodes;
using VEX.Service.Scene;
using VEX.Core.Shared.Model.InputSettings;
using VEX.Core.Shared.Model.Project;
using System.Windows;

namespace VEX.Core.Model.Project
{
    /// <summary>
    /// Class TextModel which contains the text of the document
    /// </summary>
    [KnownType(typeof(VEXDBFileModel))]
    [KnownType(typeof(EntityX))]
    [KnownType(typeof(VEXSettings))]
    [KnownType(typeof(FileWatcherModel))]
    [DataContract(IsReference = true)]
    public class VEXProjectModel : ProjectModel
    {
        private string result;

        public ObservableCollection<VEXStateModel> GameStates
        {
            get; set;
        }

        //todo list selection
        public VEXStateModel GameState { get; set; }

        public override List<System.Type> CanAddThisItems
        {
            get
            {
                return new List<Type>() { typeof(VEXDBFileModel), typeof(VEXSettings), typeof(FileWatcherModel) };
            }
        }

        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>();

                VEFMenuItem miAddItem = new VEFMenuItem() { Header = "Add Item" };

                foreach (var type in CanAddThisItems)
                {
                    miAddItem.Items.Add(new MenuItem() { Header = type.Name, Command = new CmdAddExistingItemToVEXProject(this), CommandParameter = type });
                }

                list.Add(miAddItem);

                list.Add(new VEFMenuItem() { Header = "Save to File", Command = new CmdSaveVEXProject(this) });
                //list.Add(new MenuItem() { Header = "Save" });
                //list.Add(new MenuItem() { Header = "Rename" });
                return list;
            }
        }

        private bool _IsExpanded;

        [Browsable(false)]
        [DataMember]
        public override bool IsExpanded
        {
            get {
                return _IsExpanded; }
            set
            {
                if (_IsExpanded != value)
                    IsDirty = true;

                _IsExpanded = value;
            }
        }


        //public ICommand RaiseConfirmation { get; private set; }
        ////  public ICommand RaiseSelectAEF { get; private set; }

        ////   public InteractionRequest<PSelectAEFViewModel> SelectAEFRequest { get; private set; }
        //public InteractionRequest<Confirmation> ConfirmationRequest { get; private set; }

        //private void OnRaiseConfirmation()
        //{
        //    this.ConfirmationRequest.Raise(new Confirmation { Content = "Confirmation Message", Title = "WPF Confirmation" },
        //        (cb) => { Result = cb.Confirmed ? "The user confirmed" : "The user cancelled"; });
        //}

        //private void OnRaiseSelectAEF()
        //{
        //    this.SelectAEFRequest.Raise(
        //        new PSelectAEFViewModel { Title = "Items" },
        //        (vm) =>
        //        {
        //            if (vm.SelectedItem != null)
        //            {
        //                Result = "The user selected: " + vm.SelectedItem;
        //            }
        //            else
        //            {
        //                Result = "The user didn't select an item.";
        //            }
        //        });
        //}

        public string Result
        {
            get { return this.result; }
            set { this.result = value; RaisePropertyChanged("Result"); }
        }

        public bool Create()
        {
            return true;
        }


        public bool Open(object id)
        {
            Folder = Path.GetDirectoryName(id.ToString());
            Name = Path.GetFileNameWithoutExtension(id.ToString());
            
            return true;
        }

        public new bool Save(object param = null)
        {
            try
            {
                List<Type> knownTypes = new List<Type>() { }; // typeof(AnimationNodeViewModel), typeof(OutputNodeViewModel) };

                string saveShadowCopy = this.Location + ".sbak";

                ObjectSerialize.Serialize(this, saveShadowCopy as string, knownTypes);

                Folder = Path.GetDirectoryName(saveShadowCopy as string);

                Name = Path.GetFileNameWithoutExtension(saveShadowCopy as string);

                File.Copy(saveShadowCopy, saveShadowCopy.Replace(".sbak", ""), true);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            return true;
        }
        public bool Delete() { return true; }
        public bool Closing() { return true; }
        public void Refresh() { }
        public void Finish() { }

        #region Settings

        private string _AssetFolder;

        [Editor(typeof(FolderEditor), typeof(FolderEditor))]
        public string AssetFolder
        {
            get { return _AssetFolder; }
            set
            {
                _AssetFolder = value;

                var assetBrowser = VEFModule.UnityContainer.Resolve(typeof(IAssetBrowserTreeService), "") as IAssetBrowserTreeService;


                if (Directory.Exists(_AssetFolder))
                {
                    var itemProvider = new ItemProvider();

                    assetBrowser.Items = itemProvider.GetItems(_AssetFolder);
                }
                else
                {
                    if (assetBrowser.Items != null)
                        assetBrowser.Items.Clear();
                }

                if (_AssetFolder != value)
                    IsDirty = true;
            }
        }

        #endregion

        /// <summary>
        /// Initializes a new instance of the <see cref="MDModel" /> class.
        /// </summary>
        /// <param name="commandManager">The injected command manager.</param>
        /// <param name="menuService">The menu service.</param>
        public VEXProjectModel(ICommandManager commandManager, IMenuService menuService)
        {
            //this.RaiseConfirmation = new DelegateCommand(this.OnRaiseConfirmation);
            //this.ConfirmationRequest = new InteractionRequest<Confirmation>();
     
            //   CanAddThisItems.Add(typeof(VEXDBFileModel));
            //  this.SelectAEFRequest = new InteractionRequest<PSelectAEFViewModel>();
            //  this.RaiseSelectAEF = new DelegateCommand(this.OnRaiseSelectAEF);

            //###    var assetBrowser = container.Resolve<IAssetBrowserTreeService>();
            //###     VEX_RFS fileAssets = new VEX_RFS(this, container) { Name = "Assets VFS", ContentID = "RootVFSID:##:" };
            //###      fileAssets.Open(AssetFolder);
            //###      m_Items.Add(fileAssets);
            //###       assetBrowser.SetAsRoot(fileAssets);
            //foreach (var item in fileAssets.Items)
            //    assetBrowser.AddItem(item);

            //-----------------------------------------
            //Customize Database category structure
            //-----------------------------------------
            //###     VEXDBFileModel dbData = new VEXDBFileModel(this, container);
            //###    dbData.IsExpanded = true;

            //            PredefObjectCategoyModel predefCategory = new PredefObjectCategoyModel(this, container) { Name = "Ogre System Objects" };

            //            predefCategory.Items.Add(new PredefObjectModel() { Name = "Cube" });
            ////sceneService.PredefObjects  ??????
            //            m_Items.Add(predefCategory);

            //###    m_Items.Add(dbData);
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
    }

    public class CmdAddNewItemToVEXProject : ICommand
    {
        private VEXProjectModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            mpm.Save();
        }

        public CmdAddNewItemToVEXProject(VEXProjectModel pm)
        {
            mpm = pm;
        }
    }

    public class CmdAddExistingItemToVEXProject : IHistoryCommand
    {
        private VEXProjectModel mpm;
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
            //if (t.Name == "VEXZipArchive")
            //{
            //    mpm.Items.Add(new VEXZipArchive() { Parent = mpm, UnityContainer = mpm.UnityContainer, Name = "Unknown.zip" });
            //   // Type instance = (Type)Activator.CreateInstance(t);
            //   // object obj = t.GetConstructor(new Type[] { }).Invoke(new object[] { });
            // //   mpm.Items.Add(obj as IItem);
            //}
            if (t.Name == "VEXDBFileModel")
            {
                VEXDBFileModel dbData = new VEXDBFileModel() { Parent = mpm, Name = "DBFile" };

                DBEntitiesModel objects = new DBEntitiesModel() { Parent = dbData, Name = "Entities" };
                objects.IsExpanded = true;


               // EntityCategoryModel staticObjects = new EntityCategoryModel() { Parent = dbData, Name = "EntityCategory" };
               // objects.Items.Add(staticObjects);
                //CharacterCategoryModel characterObjects = new CharacterCategoryModel() { Parent = dbData, Name = "Characters" };
                //objects.Items.Add(characterObjects);

                //SpawnPointCategoryModel allSpawns = new SpawnPointCategoryModel() { Parent = dbData, Name = "SpawnPoints" };
                //SpawnPointCategoryModel allTrigger = new SpawnPointCategoryModel() { Parent = dbData,  Name = "Triggers" };
                //SpawnPointCategoryModel allLights = new SpawnPointCategoryModel() { Parent = dbData,  Name = "Lights" };
                //SpawnPointCategoryModel allSkies = new SpawnPointCategoryModel() { Parent = dbData,  Name = "Skies" };
                //SpawnPointCategoryModel allSounds = new SpawnPointCategoryModel() { Parent = dbData,  Name = "Sounds" };
                //StaticObjectCategoryModel DynamicObjects = new StaticObjectCategoryModel() { Parent = dbData, Name = "Dynamics" };

                //objects.Items.Add(allTrigger);
                //objects.Items.Add(allSpawns);
                //objects.Items.Add(allLights);
                //objects.Items.Add(allSkies);
                //objects.Items.Add(allSounds);
                //objects.Items.Add(DynamicObjects);



                dbData.Items.Add(objects);

                SceneCategoryModel scenes = new SceneCategoryModel() { Parent = dbData, Name = "Scenes" };
                scenes.IsExpanded = true;
                dbData.Items.Add(scenes);


                mpm.Items.Add(dbData);
                dbData.IsExpanded = true;


            }
            else if(t.Name == "VEXSettings")
            {
                VEXSettings settings = new VEXSettings() { Parent = mpm, Name = "VEXSettings" };

                mpm.Items.Add(settings);
                settings.IsExpanded = true;

            }
            else if(t.Name == "FileWatcherModel")
            {
                FileWatcherModel fileWatcher = new FileWatcherModel() { Parent = mpm, Name = "FileWatcherModel", ContentID = "FileWatcherID:##:0" };

                mpm.Items.Add(fileWatcher);
                fileWatcher.IsExpanded = true;

            }
            //else if (t.Name == "VEX_RFS")
            //{
            //    mpm.AssetFolder = @"F:\Projekte\coop\VEX\data"; //todo set per propertygrid
            //    var assetBrowser = mpm.UnityContainer.Resolve<IAssetBrowserTreeService>();
            //    VEX_RFS fileAssets = new VEX_RFS() { Parent = mpm, UnityContainer = mpm.UnityContainer, Name = "Assets VFS", ContentID = "RootVFSID:##:" };
            //    fileAssets.Open(mpm.UnityContainer, mpm.AssetFolder);
            //    //        m_Items.Add(fileAssets);
            //    assetBrowser.SetAsRoot(fileAssets);

            //    mpm.Items.Add(new VEX_RFS() { Parent = mpm, UnityContainer = mpm.UnityContainer, Name = "RFS" });
            //}
        }

        public CmdAddExistingItemToVEXProject(VEXProjectModel pm)
        {
            mpm = pm;
        }

        public bool CanRedo() { return true; }
        public bool CanUndo() { return true; }
        public void Redo() { }
        public string ShortMessage() { return "add item"; }
        public void Undo() { }

    }

    public class CmdSaveVEXProject : ICommand
    {
        private VEXProjectModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            mpm.Save();
        }

        public CmdSaveVEXProject(VEXProjectModel pm)
        {
            mpm = pm;
        }
    }
}