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

using Microsoft.Practices.Unity;
using VEX.Model.Scene.Model;
using System.Windows.Controls;
using GongSolutions.Wpf.DragDrop;
using GongSolutions.Wpf.DragDrop.Utilities;
using VEF.Interfaces;
using VEX.Interface.Scene;
using VEF.Interfaces.Services;
using VEF;
using System;
using VEX.Service.Scene;
using VEX.Core.Shared.Interface.Services;
using System.Collections.Generic;
using VEX.Core.Model.Services;
using VEX.Core.Model;
using VEX.Interface.DAL;
using VEX.Core.Shared.Interface.Net;
using System.Collections.ObjectModel;
using System.Windows;

namespace VEX.Model.Scene
{

    /// <summary>
    /// Class TextModel which contains the text of the document
    /// </summary>
    public class SceneGraphToolModel : ToolModel, IDropTarget
    {
        private SceneManager m_SceneService;

        object mSelectedObject;
        public object SelectedObject { get { return mSelectedObject; } set { mSelectedObject = value; RaisePropertyChanged("SelectedObject"); } }

        ObservableCollection<EntityX> schjrott;
        public ObservableCollection<EntityX> Items
        { 
            get { return schjrott; }
            set { 
                schjrott = value; 
                RaisePropertyChanged("Items");
            }
        }

        void IDropTarget.DragOver(IDropInfo dropInfo)
        {
            IItem sourceItem = dropInfo.Data as IItem;
            IItem targetItem = dropInfo.TargetItem as IItem;

            if (sourceItem != null && targetItem != null)
            {
                //over graph scene item
                dropInfo.DropTargetAdorner = DropTargetAdorners.Highlight;
                dropInfo.Effects = System.Windows.DragDropEffects.Copy;
            }else
            {
                var item = dropInfo.VisualTargetItem as TreeViewItem;
                var view = dropInfo.VisualTarget as TreeView;
                bool directlyOverItem = false;
                var dc = view.DataContext as SceneGraphToolModel;

                if (dc != null)
                {
                    dropInfo.Effects = System.Windows.DragDropEffects.Copy;

                }
                if (item != null && view != null)
                {
                    var result = view.InputHitTest(dropInfo.DropPosition) as System.Windows.UIElement;
                    if (result != null)
                    {
                        var ancestor = result.GetVisualAncestor<TreeViewItem>();
                        directlyOverItem = (ancestor != null) && (ancestor == item);
                    }
                    //var ftc = item.DataContext as FolderTestCase;
                    //if (ftc != null && directlyOverItem)
                    //{
                    //    int insertIndex = dropInfo.InsertIndex;
                    //    IList destinationList = GetList(dropInfo.TargetCollection);
                    //    IEnumerable data = ExtractData(dropInfo.Data);

                    //    if (dropInfo.DragInfo.VisualSource == dropInfo.VisualTarget)
                    //    {
                    //        IList sourceList = GetList(dropInfo.DragInfo.SourceCollection);

                    //        foreach (object o in data)
                    //        {
                    //            int index = sourceList.IndexOf(o);

                    //            if (index != -1)
                    //            {
                    //                sourceList.RemoveAt(index);

                    //                if (sourceList == destinationList && index < insertIndex)
                    //                {
                    //                    --insertIndex;
                    //                }
                    //            }
                    //        }
                    //    }

                    //    foreach (object o in data)
                    //    {
                    //        ftc.Children.Add(o as TestCase);
                    //    }
                    //}
                }
                if (item == null && view != null)
                {
                    //Case when you drop anywhere on the tree and not on an item
                    //TestScenario scenaio = view.DataContext as TestScenario;
                    //TestCase tc = dropInfo.Data as TestCase;
                    //if (scenaio != null && tc != null)
                    //{
                    //    if (tc.Scenario == scenaio)
                    //    {
                    //        scenaio.Children.Remove(tc);
                    //    }
                    //    //Clone the dragged object - you never know if the object is dragged from one window to another
                    //    tc = tc.Clone() as TestCase;
                    //    tc.IsSelected = true;
                    //    scenaio.Children.Add(tc);
                    //}
                }
                else if (!directlyOverItem)
                {
                //    base.Drop(dropInfo);
                }

            }
        }

        void IDropTarget.Drop(IDropInfo dropInfo)
        {
            IItem sourceItem = dropInfo.Data as IItem;
            IItem targetItem = dropInfo.TargetItem as IItem;

            if (targetItem != null)
                targetItem.Drop(sourceItem);
            //targetItem.Children.Add(sourceItem);


            var entity = sourceItem as EntityX;
            if (entity != null)
            {
                var scene = m_SceneService.SelectedScene as SceneDataModel;

                if(scene == null)
                {
                    MessageBox.Show("no scene is opened!");
                    return;
                }

                //  var newEntity = new EntityX();
                //  sceneItem.Type =
               // entity.Name = "test!!!";
                //if (sourceItem is StaticObjectModel)
                //{
                //    sceneItem.Type = (sourceItem as StaticObjectModel).Type;
                //  //  sceneItem.Components = sourceItem as IEntityComponent; // as StaticObjectModel).FBObject;
                //    sceneItem.Name = (sourceItem as StaticObjectModel).Name;
                //  //  sceneItem.ContentID = (sourceItem as StaticObjectModel).ContentID;
                //}

                scene.Entities.Add(entity);//.createNewEntity(entity);
             //   sceneNode.Type = NetMsg.Data.Node;
              //  sceneNode.SceneID = scene.SceneID;

                var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;
                // sceneNode.NetID = _SocketServerManager.NewNetID();

                entity.SendToSocket(entity.FBObject, NetMsg.Data.Entity);
                //_SocketServerManager.SendMessageToServer(sceneNode.NetID, scene.SceneID, NetMsg.Data.Node, sceneNode.FBObject.CreateFBData());
                return;
                //var items = new List<ISockerServerItem>();
                //foreach (var item in sceneNode.Items)
                //{
                //    var ComponentAttachedToNode = item as EntityX;
                //    if (ComponentAttachedToNode != null)
                //    {
                //        foreach (var fileItem in ComponentAttachedToNode.Items)
                //        {
                //            //todo get list of fileitems within scneitem e.g. staticobject??
                //            // items.Add(fileItem as ISockerServerItem);
                //        }

                //        var netMsgItem = (ComponentAttachedToNode as INetID).FBObject as INetMsg;
                //        if (netMsgItem != null)
                //        {
                //            _SocketServerManager.SendMessageToServer(sceneNode.NetID, scene.SceneID, netMsgItem.FBMsgType, (ComponentAttachedToNode as INetID).FBObject.CreateFBData());

                //           // _SocketServerManager.SocketServerToolModel.SourceItems.Add(new SourceItem() { Items = items, SceneItem = new StaticObjectModel(), Watch = true });
                //        }
                //    }

                //}
                //m_SceneService.OnItemAdded(new SceneItemEventArgs(sceneNode));
            }
        }
        
        /// <summary>
        /// Initializes a new instance of the <see cref="MDModel" /> class.
        /// </summary>
        /// <param name="commandManager">The injected command manager.</param>
        /// <param name="menuService">The menu service.</param>
        public SceneGraphToolModel() 
        {
      //      container.Resolve<ICommandManager>(), container.Resolve<IMenuService>()
     //       ISceneService sceneService, ICommandManager commandManager, IMenuService menuService
            //mProjectTreeService = VEFModule.UnityContainer.Resolve(typeof(IProjectTreeService), "") as IProjectTreeService;

            //mProjectTreeService.Items = new CollectionOfIItem();

            m_SceneService = VEFModule.UnityContainer.Resolve(typeof(SceneManager), "") as SceneManager;
            Items = new ObservableCollection<EntityX>();
         //   m_SceneService.SelectedScene = new SceneDataModel();
            m_SceneService.SGTM = this;
            //Service für project contextmenu buttons .....
            //tray.ContextMenu = new ContextMenu();
            //tray.ContextMenu.ItemsSource = _children;

         //   mItems = new ObservableCollection<ContentModel>();


            //CategoryModel cdata = new CategoryModel(commandManager, menuService) { Name = "Data" };
            //mItems.Add(cdata);
            //------------- Scenes ----------------------
            //VMCategory cScenes = new VMCategory(,commandManager, menuService) { Name = "Scenes" };

            //p1.Items.Add(cScenes);

            //CVMScene sv = new CVMScene() { Name = "Scene 1" };
            //sv.Items.Add(new CVMCategory() { Name = "Cameras" });
            //sv.Items.Add(new CVMCategory() { Name = "Models" });
            //sv.Items.Add(new CVMCategory() { Name = "Sound" });
            //cScenes.Items.Add(sv);

        }
    }  
}
