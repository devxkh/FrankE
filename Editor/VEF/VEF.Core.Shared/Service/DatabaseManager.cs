using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using VEF.Interfaces.Controls;
using VEF.DAL.Interface;
using VEF.DAL.Interface.Events;
using VEF.Interfaces.Services;
using Prism.Events;
using VEF.Core.Interface.Service;
using System.Windows.Controls;
using VEF;

namespace Module.DB.Service
{ 
       
    /// <summary>
    /// The main project tree manager
    /// </summary> 
    [XmlInclude(typeof(IDALOptions))]
    [XmlInclude(typeof(IDB))]
    public class DatabaseManager : IDatabaseService
    {
        private User m_LoggedUser;
        private UInt16 m_CTXCounter = 0; 
       
        public System.Windows.Controls.ContextMenu ContextMenu { get; private set; }

        MenuItemViewModel menuItem;
        
        /// <summary>
        /// The injected logger
        /// </summary>
        private readonly ILoggerService _logger;

        public DatabaseManager() 
        {
            DBs = new ObservableCollection<IDB>();
            DBOptions = new ObservableCollection<IDALOptions>();
            ContextMenu = new ContextMenu();
        }

        /// <summary>
        /// The theme manager constructor
        /// </summary>
        /// <param name="eventAggregator">The injected event aggregator</param>
        /// <param name="logger">The injected logger</param>
        public DatabaseManager(ILoggerService logger)
        {
            DBs = new ObservableCollection<IDB>();
            DBOptions = new ObservableCollection<IDALOptions>();
            _logger = logger;
            //Service für project contextmenu buttons .....
            ContextMenu = new ContextMenu();

            MenuItem mib1a = new MenuItem();
            mib1a.Header = "Text.xaml";
            ContextMenu.Items.Add(mib1a);

        }

        /// <summary>
        /// logged user data
        /// </summary>
        public User LoggedUser { get { if (m_LoggedUser == null) m_LoggedUser = new User(); return m_LoggedUser; } }

        /// <summary>
        /// current database options
        /// </summary>
        public IDALOptions CurrentDBOptions { get; internal set; }
       
        /// <summary>
        /// The current database selected
        /// </summary>
        public IDB CurrentDB { get; internal set; }

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

        //public AbstractMenuItem RightClickMenu
        //{
        //    get
        //    {
        //        if (menuItem == null)
        //        {
        //            menuItem = new MenuItemViewModel("_ProjFile", 100);
        //            foreach (var value in ContextMenu.ItemsSource)
        //            {
        //                var menu = value as AbstractMenuItem;
        //                menuItem.Add(menu);
        //            }
        //        }
        //        return menuItem;
        //    }
        //}


        #region IDatabaseService Members

        /// <summary>
        /// collection of database items
        /// </summary>
        //[XmlIgnore]
        [XmlArray(ElementName = "DBs")]
        [XmlArrayItem(ElementName = "IDB")]
        public ObservableCollection<IDB> DBs { get; internal set; }
  
        /// <summary>
        /// collection of database options
        /// </summary>
        [XmlArray(ElementName = "DBOptions")]
        [XmlArrayItem(ElementName = "DBOptions")]
        public ObservableCollection<IDALOptions> DBOptions { get; internal set; }


        public UInt16 GetNextCtxID()
        {
            return m_CTXCounter = (UInt16)(m_CTXCounter + 1);
        }

        /// <summary>
        /// Set the current item
        /// </summary>
        /// <param name="guid">The guid of the item</param>
        /// <returns>true if the new item is set, false otherwise</returns>
        public bool SetCurrentDB(Guid guid)
        {
            var db = DBs.Where(x => x.Guid == guid);
            if (db.Any())
            {
                IDB newDB = db.First();
                CurrentDB = newDB;

                //ResourceDictionary theme = Application.Current.MainWindow.Resources.MergedDictionaries[0];
                //ResourceDictionary appTheme = Application.Current.Resources.MergedDictionaries.Count > 0
                //                                  ? Application.Current.Resources.MergedDictionaries[0]
                //                                  : null;
                //theme.BeginInit();
                //theme.MergedDictionaries.Clear();
                //if (appTheme != null)
                //{
                //    appTheme.BeginInit();
                //    appTheme.MergedDictionaries.Clear();
                //}
                //else
                //{
                //    appTheme = new ResourceDictionary();
                //    appTheme.BeginInit();
                //    Application.Current.Resources.MergedDictionaries.Add(appTheme);
                //}
                //foreach (Uri uri in newTheme.UriList)
                //{
                //    ResourceDictionary newDict = new ResourceDictionary {Source = uri};
                //    /*AvalonDock and menu style needs to move to the application
                //     * 1. AvalonDock needs global styles as floatable windows can be created
                //     * 2. Menu's need global style as context menu can be created
                //    */
                //    if (uri.ToString().Contains("AvalonDock") ||
                //        uri.ToString().Contains("Wide;component/Interfaces/Styles/VS2012/Menu.xaml"))
                //    {
                //        appTheme.MergedDictionaries.Add(newDict);
                //    }
                //    else
                //    {
                //        theme.MergedDictionaries.Add(newDict);
                //    }
                //}
                //appTheme.EndInit();
                //theme.EndInit();
                _logger.Log("Database item set to " + newDB.DBOptions.Name, LogCategory.Info, LogPriority.None);
                VEFModule.EventAggregator.GetEvent<DALChangeEvent>().Publish(newDB);
            }
            return false;
        }

        /// <summary>
        /// Adds a base item to the project-file manager
        /// </summary>
        /// <param name="theme">The item to add</param>
        /// <returns>true, if successful - false, otherwise</returns>
        public bool AddDB(IDB db)
        {
            if (!DBs.Contains(db))
            {
                DBs.Add(db);
                return true;
            }
            return false;
        }

        /// <summary>
        /// Adds a base item to the project-file manager
        /// </summary>
        /// <param name="theme">The item to add</param>
        /// <returns>true, if successful - false, otherwise</returns>
        public bool AddDBOption(IDALOptions db)
        {
            if (!DBOptions.Contains(db))
            {
                DBOptions.Add(db);
                return true;
            }
            return false;
        }

        #endregion
    }
}
