

using GongSolutions.Wpf.DragDrop;
using System.Windows;
using VEF.Interfaces;
using VEF.Interfaces.Services;

namespace VEF.Model.PFExplorer
{
    /// <summary>
    /// Class TextModel which contains the text of the document
    /// </summary>
    public class ProjectToolModel : ToolModel, IDropTarget
    {
    
    void IDropTarget.DragOver(IDropInfo dropInfo) {
        IItem sourceItem = dropInfo.Data as IItem;
        IItem targetItem = dropInfo.TargetItem as IItem;

        if (sourceItem != null && targetItem != null) {
            dropInfo.DropTargetAdorner = DropTargetAdorners.Highlight;
            dropInfo.Effects = DragDropEffects.Copy;
        }
    }

    void IDropTarget.Drop(IDropInfo dropInfo) {
        IItem sourceItem = dropInfo.Data as IItem;
        IItem targetItem = dropInfo.TargetItem as IItem;

        targetItem.Drop(sourceItem);
        //targetItem.Children.Add(sourceItem);
    }

        IProjectTreeService mProjectTreeService;

      //  ObservableCollection<ContentModel> mItems;

        public CollectionOfIItem Items { get {
                return mProjectTreeService.Items;
            } }

        //public IItem RootItem
        //{
        //    get { return mProjectTreeService.RootItem; }
        //}

        //public IItem SeRootItem
        //{
        //    get { return mProjectTreeService.RootItem; }
        //}

        /// <summary>
        /// Initializes a new instance of the <see cref="MDModel" /> class.
        /// </summary>
        /// <param name="commandManager">The injected command manager.</param>
        /// <param name="menuService">The menu service.</param>
        public ProjectToolModel()//ICommandManager commandManager, IMenuService menuService)
        {
            var commandManager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;
         //  var menuService = VEFModule.UnityContainer.Resolve<IMenuService>();
           mProjectTreeService = VEFModule.UnityContainer.Resolve(typeof(IProjectTreeService), "") as IProjectTreeService;

           mProjectTreeService.Items = new CollectionOfIItem();
     
            //tray.ContextMenu.ItemsSource = _children;

      //      mItems = new ObservableCollection<ContentModel>();


        //    CategoryModel cdata = new CategoryModel(commandManager, menuService) { Name = "Data" };
         //   mProjectTreeService.Items.Add(cdata);
            //------------- Scenes ----------------------
            //VMCategory cScenes = new VMCategory(,commandManager, menuService) { Name = "Scenes" };

            //p1.Items.Add(cScenes);

            //CVMScene sv = new CVMScene() { Name = "Scene 1" };
            //sv.Items.Add(new CVMCategory() { Name = "Cameras" });
            //sv.Items.Add(new CVMCategory() { Name = "Models" });
            //sv.Items.Add(new CVMCategory() { Name = "Sound" });
            //cScenes.Items.Add(sv);

        }

        //internal void SetLocation(object location)
        //{
        //    this.Location = location;
        //    RaisePropertyChanged("Location");
        //}

        //internal void SetDirty(bool value)
        //{
        //    this.IsDirty = value;
        //}

        public string HTMLResult { get; set; }

        public void SetHtml(string transform)
        {
            this.HTMLResult = transform;
            RaisePropertyChanged("HTMLResult");
        }
    }
}