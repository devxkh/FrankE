using Microsoft.Practices.Unity;
using Prism.Events;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.Base;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using VEF.Utils;

namespace VEF.Interfaces
{
    /// <summary>
    /// Class AbstractWorkspace
    /// </summary>
    public abstract class AbstractWorkspace : ViewModelBase, IWorkspace
    {
        #region Fields

        /// <summary>
        /// The active document
        /// </summary>
        private ContentViewModel _activeDocument;

        /// <summary>
        /// The injected command manager
        /// </summary>
        protected ICommandManager _commandManager;

        /// <summary>
        /// The list of documents
        /// </summary>
        protected ObservableCollection<ContentViewModel> _docs = new ObservableCollection<ContentViewModel>();

        /// <summary>
        /// The menu service
        /// </summary>
        protected MenuItemViewModel _menus;

        /// <summary>
        /// The toolbar service
        /// </summary>
        protected AbstractToolbar _toolbarService;

        /// <summary>
        /// The status bar service
        /// </summary>
        protected IStatusbarService _statusbarService;

     //   public InteractionRequest<Confirmation> ConfirmationRequest { get; private set; }
    //    public InteractionRequest<Notification> NotificationRequest { get; private set; }

        //public Task<ProgressDialogController> ProgressDialog(String title, string content)
        //{
        //    (Application.Current.MainWindow as ShellViewMetro).MetroDialogOptions.ColorScheme = MetroDialogColorScheme.Accented;
        //    return (Application.Current.MainWindow as ShellViewMetro).ShowProgressAsync(title, content);
        //}

        //public Task<String> InputDialog(String title, string content)
        //{
        //    (Application.Current.MainWindow as ShellViewMetro).MetroDialogOptions.ColorScheme = MetroDialogColorScheme.Accented;
        //    return (Application.Current.MainWindow as ShellViewMetro).ShowInputAsync(title, content);
        //}

        //public Task<MessageDialogResult> MessageDialog(String title, string content, MessageDialogStyle msgDialogStyle, MetroDialogSettings dialogSettings)
        //{
        //    (Application.Current.MainWindow as ShellViewMetro).MetroDialogOptions.ColorScheme = MetroDialogColorScheme.Accented;
        //    return (Application.Current.MainWindow as ShellViewMetro).ShowMessageAsync(title, content, msgDialogStyle, dialogSettings);
        //}

        //public Task<LoginDialogData> LoginDialog(String title, string content)
        //{
        //    (Application.Current.MainWindow as ShellViewMetro).MetroDialogOptions.ColorScheme = MetroDialogColorScheme.Accented;
        //    return (Application.Current.MainWindow as ShellViewMetro).ShowLoginAsync(title, content, new LoginDialogSettings { NegativeButtonVisibility = Visibility.Visible });
        //}

        /// <summary>
        /// The list of tools
        /// </summary>
        protected ObservableCollection<ToolViewModel> _tools = new ObservableCollection<ToolViewModel>();

        #endregion

        #region CTOR

        /// <summary>
        /// Initializes a new instance of the <see cref="AbstractWorkspace" /> class.
        /// </summary>
        /// <param name="container">The injected container.</param>
        /// <param name="eventAggregator">The event aggregator.</param>
        protected AbstractWorkspace()
        {
            _docs = new ObservableCollection<ContentViewModel>();
            _docs.CollectionChanged += Docs_CollectionChanged;
            _tools = new ObservableCollection<ToolViewModel>();
            _menus = VEFModule.UnityContainer.Resolve(typeof(IMenuService),"") as MenuItemViewModel;
       //     _menus = VEFModule.UnityContainer.Resolve(typeof(MenuItemViewModel), "MenuItemViewModel") as MenuItemViewModel;
            _menus.PropertyChanged += _menus_PropertyChanged;
            _toolbarService = VEFModule.UnityContainer.Resolve(typeof(IToolbarService), "") as AbstractToolbar;
        //    _toolbarService = VEFModule.UnityContainer.Resolve(typeof(AbstractToolbar), "AbstractToolbar") as AbstractToolbar;
            _statusbarService = VEFModule.UnityContainer.Resolve(typeof(IStatusbarService), "") as IStatusbarService;
            _commandManager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;

        //    this.ConfirmationRequest = new InteractionRequest<Confirmation>();
       //     this.NotificationRequest = new InteractionRequest<Notification>();

            MinHeight = 200; //default
            MinHeight = 200; //default

        }

        #endregion

        #region Properties

   //     private AvalonDockThemesEnum m_ADTheme;
   //     public AvalonDockThemesEnum ADTheme { get { return m_ADTheme; } set { m_ADTheme = value; RaisePropertyChanged("ADTheme"); } }

        /// <summary>
        /// Gets the menu.
        /// </summary>
        /// <value>The menu.</value>
        public IList<AbstractCommandable> Menus
        {
            get { return _menus.Children; }
        }

        /// <summary>
        /// Gets the tool bar tray.
        /// </summary>
        /// <value>The tool bar tray.</value>
        public object ToolBarTray
        {
            get { return (_toolbarService as IToolbarService).ToolBarTray; }
        }

        public IStatusbarService StatusBar
        {
            get { return _statusbarService; }
        }

        #endregion

        #region IWorkspace Members

        /// <summary>
        /// The list of documents which are open in the workspace
        /// </summary>
        /// <value>The documents.</value>
        public virtual ObservableCollection<ContentViewModel> Documents
        {
            get { return _docs; }
            set { _docs = value; }
        }

        /// <summary>
        /// The list of tools that are available in the workspace
        /// </summary>
        /// <value>The tools.</value>
        public virtual ObservableCollection<ToolViewModel> Tools
        {
            get { return _tools; }
            set { _tools = value; }
        }

        /// <summary>
        /// The current document which is active in the workspace
        /// </summary>
        /// <value>The active document.</value>
        public virtual ContentViewModel ActiveDocument
        {
            get { return _activeDocument; }
            set
            {
                if (_activeDocument != value)
                {
                    _activeDocument = value;
                    RaisePropertyChanged("ActiveDocument");
                    _commandManager.Refresh();
                    _menus.Refresh();
                //##    _eventAggregator.GetEvent<ActiveContentChangedEvent>().Publish(_activeDocument);
                }
            }
        }

        /// <summary>
        /// Gets the title of the application.
        /// </summary>
        /// <value>The title.</value>
        public virtual string Title
        {
            get { return "Wide"; }
        }

        /// <summary>
        /// minimum width of the workspace
        /// </summary>
        public UInt32 MinWidth { get; set; }

        /// <summary>
        /// minimum height of the workspace
        /// </summary>
        public UInt32 MinHeight { get; set; }


        /// <summary>
        /// Gets the icon of the application.
        /// </summary>
        /// <value>The icon.</value>
     //   public virtual ImageSource Icon { get; protected set; }

        /// <summary>
        /// Closing this instance.
        /// </summary>
        /// <param name="e">The <see cref="CancelEventArgs" /> instance containing the event data.</param>
        /// <returns><c>true</c> if the application is closing, <c>false</c> otherwise</returns>
        public virtual bool Closing(CancelEventArgs e)
        {
            for (int i = 0; i < Documents.Count; i++)
            {
                ContentViewModel vm = Documents[i];
                if (vm.Model == null || (vm.Model != null && vm.Model.IsDirty))
                {
                    ActiveDocument = vm;

                    //Execute the close command
                    vm.CloseCommand.Execute(e);

                    //If canceled
                    if (e.Cancel == true)
                    {
                        return false;
                    }

                    //If it was a new view model with no location to save, we have removed the view model from documents - so reduce the count
                    if (vm.Model == null || (vm.Model != null && vm.Model.Location == null))
                    {
                        i--;
                    }
                }
            }
            return true;
        }

        #endregion

        /// <summary>
        /// Handles the PropertyChanged event of the menu control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="PropertyChangedEventArgs"/> instance containing the event data.</param>
        private void _menus_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            RaisePropertyChanged("Menus");
        }


        protected void Docs_CollectionChanged(object sender,
                                              System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            if (e.OldItems != null)
            {
                foreach (INotifyPropertyChanged item in e.OldItems)
                    item.PropertyChanged -= ModelChangedEventHandler;
            }

            if (e.NewItems != null)
            {
                foreach (INotifyPropertyChanged item in e.NewItems)
                    item.PropertyChanged += ModelChangedEventHandler;
            }

            if (e.Action == NotifyCollectionChangedAction.Remove)
            {
                if (_docs.Count == 0)
                {
                    this.ActiveDocument = null;
                }
            }
        }

        /// <summary>
        /// The changed event handler when a property on the model changes.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="PropertyChangedEventArgs"/> instance containing the event data.</param>
        protected virtual void ModelChangedEventHandler(object sender, PropertyChangedEventArgs e)
        {
            _commandManager.Refresh();
            _menus.Refresh();
            _toolbarService.Refresh();
        }
    }
}
