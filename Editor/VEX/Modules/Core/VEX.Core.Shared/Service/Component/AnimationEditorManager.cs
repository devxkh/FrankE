using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.Windows.Controls;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using VEF.Utils;
using VEX.Interface.UI;
using VEX.Model.UI;

namespace VEX.Core.Shared.Service.Component
{
    public delegate void AnimationEditorItemEventHandler(object sender, AnimationEditorItemEventArgs e);

    public class AnimationEditorItemEventArgs : EventArgs
    {
        public AnimationEditorItemEventArgs(AnimationEditorModel AnimationEditorItem)
        {
            AnimationEditorItem = AnimationEditorItem;
        }

        public AnimationEditorModel AnimationEditorItem { get; private set; }
    }

    /// <summary>
    /// The main project tree manager
    /// </summary>
    public class AnimationEditorManager : ViewModelBase, IAnimationEditorService
    {
        public System.Windows.Controls.ContextMenu ContextMenu { get; private set; }

        MenuItemViewModel menuItem;


        // An event that clients can use to be notified whenever the
        // elements of the list change:
        public event AnimationEditorItemEventHandler ItemAdded;

        // Invoke the Changed event; called whenever list changes:
        public virtual void OnItemAdded(AnimationEditorItemEventArgs e)
        {
            if (ItemAdded != null)
                ItemAdded(this, e);
        }

        //   public TreeList TreeList { get; set; }

        //   private IAnimationEditor mRootItem;


        //public void SetAsRoot(IAnimationEditor AnimationEditor)
        //{
        //    // var mProjectTreeService = _container.Resolve<IProjectTreeService>();
        //    //var commandManager = _container.Resolve<ICommandManager>();
        //    // var menuService = _container.Resolve<IMenuService>();
        //    // var dbService = _container.Resolve<IDatabaseService>();

        //    //---------------------------------------------
        //    //Projekt Tree
        //    //---------------------------------------------
        //    //todo nur ein Projekt!!
        //    //ptS.SetProject();
        //  //  AnimationEditorItems.Clear();
        //  //  RootItem = null;

        //  //  FileCategoryModel root = new FileCategoryModel(null, null) { Name = "RootNode" };
        //    //AuftragModel order = new AuftragModel(root, dbS) { Name = "Auftrag Neu", IsExpanded = true };
        //    //root.Items.Add(AnimationEditor);
        //    SelectedAnimationEditor = AnimationEditor;
        //   // RootItem = SelectedAnimationEditor;
        //}

        /// <summary>
        /// Root Item
        /// </summary>
        //public IAnimationEditor RootItem
        //{
        //    get { return mRootItem; }
        //    private set
        //    {
        //        if (RootItem != value)
        //        {
        //            //TreeList setted in AnimationEditor modul
        //            TreeList.RootItem = value;
        //            TreeList.Root.Children.Clear();
        //            TreeList.Rows.Clear();
        //            TreeList.CreateChildrenNodes(TreeList.Root);
        //            mRootItem = value;
        //        }
        //    }
        //}
        /// <summary>
        /// The injected logger
        /// </summary>
        private readonly ILoggerService _logger;

        /// <summary>
        /// The theme manager constructor
        /// </summary>
        /// <param name="eventAggregator">The injected event aggregator</param>
        /// <param name="logger">The injected logger</param>
        public AnimationEditorManager(ILoggerService logger)
        {
            AnimationEditors = new ObservableCollection<AnimationEditorModel>();

            _logger = logger;
            //Service für project contextmenu buttons .....
            ContextMenu = new ContextMenu();

            MenuItem mib1a = new MenuItem();
            mib1a.Header = "Text.xaml";
            ContextMenu.Items.Add(mib1a);
            mPredefObjects = new ObservableCollection<IItem>();
        }

        private ObservableCollection<IItem> mPredefObjects;

    //--todo ?    public AnimationEditorGraphToolModel SGTM { get; set; }


        /// <summary>
        /// The current item selected
        /// </summary>
        private AnimationEditorModel mSelectedAnimationEditor;
        public AnimationEditorModel SelectedAnimationEditor
        {
            get
            {
                return mSelectedAnimationEditor;
            }
            set
            {
                AnimationEditorModel AnimationEditor = value as AnimationEditorModel;
                //if (AnimationEditor == null)
                //    SGTM.Items.Clear();
                //else
                //    SGTM.Items = AnimationEditor.Entities;

                mSelectedAnimationEditor = AnimationEditor;

                RaisePropertyChanged("SelectedAnimationEditor");
            }
        }


        /// <summary>
        /// Adds the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <returns><c>true</c> if successfully added, <c>false</c> otherwise</returns>
        //public override string Add(AbstractCommandable item)
        //{
        //    AbstractToolbar tb = item as AbstractToolbar;
        //    if (tb != null)
        //    {
        //        tb.IsCheckable = true;
        //        tb.IsChecked = true;
        //    }
        //    return base.Add(item);
        //}

        public AbstractMenuItem RightClickMenu
        {
            get
            {
                if (menuItem == null)
                {
                    menuItem = new MenuItemViewModel("_ProjFile", 100);
                    foreach (var value in ContextMenu.ItemsSource)
                    {
                        var menu = value as AbstractMenuItem;
                        menuItem.Add(menu);
                    }
                }
                return menuItem;
            }
        }


        #region IProjectTreeService Members

        /// <summary>
        /// collection of treeview items
        /// </summary>
        public ObservableCollection<AnimationEditorModel> AnimationEditors { get; internal set; }


        public ObservableCollection<IItem> PredefObjects { get { return mPredefObjects; } }

        /// <summary>
        /// Set the current item
        /// </summary>
        /// <param name="guid">The guid of the item</param>
        /// <returns>true if the new item is set, false otherwise</returns>
        //public bool SetCurrent(Guid guid)
        //{
        //    var item = Items.Where(x => x.Guid == guid);
        //    if (item.Any())
        //    {
        //        IItem newItem = item.First();
        //        CurrentItem = newItem;

        //        //ResourceDictionary theme = Application.Current.MainWindow.Resources.MergedDictionaries[0];
        //        //ResourceDictionary appTheme = Application.Current.Resources.MergedDictionaries.Count > 0
        //        //                                  ? Application.Current.Resources.MergedDictionaries[0]
        //        //                                  : null;
        //        //theme.BeginInit();
        //        //theme.MergedDictionaries.Clear();
        //        //if (appTheme != null)
        //        //{
        //        //    appTheme.BeginInit();
        //        //    appTheme.MergedDictionaries.Clear();
        //        //}
        //        //else
        //        //{
        //        //    appTheme = new ResourceDictionary();
        //        //    appTheme.BeginInit();
        //        //    Application.Current.Resources.MergedDictionaries.Add(appTheme);
        //        //}
        //        //foreach (Uri uri in newTheme.UriList)
        //        //{
        //        //    ResourceDictionary newDict = new ResourceDictionary {Source = uri};
        //        //    /*AvalonDock and menu style needs to move to the application
        //        //     * 1. AvalonDock needs global styles as floatable windows can be created
        //        //     * 2. Menu's need global style as context menu can be created
        //        //    */
        //        //    if (uri.ToString().Contains("AvalonDock") ||
        //        //        uri.ToString().Contains("Wide;component/Interfaces/Styles/VS2012/Menu.xaml"))
        //        //    {
        //        //        appTheme.MergedDictionaries.Add(newDict);
        //        //    }
        //        //    else
        //        //    {
        //        //        theme.MergedDictionaries.Add(newDict);
        //        //    }
        //        //}
        //        //appTheme.EndInit();
        //        //theme.EndInit();
        //        _logger.Log("projectfile item set to " + newItem.Name, LogCategory.Info, LogPriority.None);
        //        _eventAggregator.GetEvent<ItemChangeEvent>().Publish(newItem);
        //    }
        //    return false;
        //}

        /// <summary>
        /// Adds a base item to the project-file manager
        /// </summary>
        /// <param name="theme">The item to add</param>
        /// <returns>true, if successful - false, otherwise</returns>
        public bool AddAnimationEditor(AnimationEditorModel AnimationEditor)
        {
            if (!AnimationEditors.Contains(AnimationEditor))
            {
                AnimationEditors.Add(AnimationEditor);
                return true;
            }
            return false;
        }

        #endregion
    }
}
