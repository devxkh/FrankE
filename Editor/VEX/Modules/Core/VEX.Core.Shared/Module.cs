using Microsoft.Practices.Unity;
using Module.DB.Service;
using Prism.Commands;
using System;
using System.Collections.Generic;
using System.Composition;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using VEF;
using VEF.Core.Interface.Service;
using VEF.Core.Settings;
using VEF.Core.WPF.Util;
using VEF.Interfaces;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using VEF.Interfaces.Settings;
using VEF.Interfaces.Themes;
using VEF.Model.Services;
using VEF.Model.Settings;
using VEF.View.Shell;
using VEF.ViewModel;
using VEF.XForms.Model.Services;
using VEX.Core.Handler;
using VEX.Core.Interfaces.Services;
using VEX.Core.Model;
using VEX.Core.Model.Services;
using VEX.Core.Properties;
using VEX.Core.Shared.Handler.Atlas;
using VEX.Core.Shared.Handler.Components;
using VEX.Core.Shared.Handler.Scene;
using VEX.Core.Shared.Service.Component;
using VEX.Core.Shared.Service.UI;
using VEX.Core.Shared.ViewModel.Scene;
using VEX.Core.Shared.ViewModel.UI;
using VEX.Core.View;
using VEX.Core.View.Components;
using VEX.Core.View.Project;
using VEX.Core.View.UI;
using VEX.Core.ViewModel;
using VEX.Core.ViewModel.Project;
using VEX.Interface.Scene;
using VEX.Interface.UI;
using VEX.Service.Scene;

namespace VEX.Core
{

    public class TestCommand : IVEFCommand
    {
        /// <summary>
        /// Determine if this command supports undo
        /// </summary>
        /// <returns>true if this command can be undone, false otherwise</returns>
        public bool CanUndo()
        {
            return false;
        }


        /// <summary>
        /// Determine if this command supports redo
        /// </summary>
        /// <returns>true if this command be can redone, false otherwise</returns>
        public bool CanRedo()
        {
            return false;
        }


        /// <summary>
        /// Determine if this command can be executed. Executed commands are those that will
        /// be run automatically when added to the undo/redo stack. Batch style commands should
        /// not be executed since they will have already performed their operations.
        /// </summary>
        /// <returns>true if the command should be executed, false otherwise</returns>
        //bool CanExecute();


        /// <summary>
        /// Undoes the operations that this command performed.
        /// </summary>
        public void Undo()
        {

        }


        /// <summary>
        /// Redoes the operations that this command performed.
        /// </summary>
        public void Redo()
        {

        }


        /// <summary>
        /// Executes this command. Commands that are "pre-rolled" and have already performed
        /// their operations should never require this method. Batch style commands are an
        /// example of a command that should not require execution but can be undone/redone.
        /// </summary>
        //	void Execute();
        // Zusammenfassung:
        //     Tritt ein, wenn Änderungen auftreten, die sich auf die Ausführung des Befehls
        //     auswirken.
         public event EventHandler CanExecuteChanged;

        // Zusammenfassung:
        //     Definiert die Methode, die bestimmt, ob der Befehl im aktuellen Zustand ausgeführt
        //     werden kann.
        //
        // Parameter:
        //   parameter:
        //     Vom Befehl verwendete Daten. Wenn der Befehl keine Datenübergabe erfordert,
        //     kann das Objekt auf null festgelegt werden.
        //
        // Rückgabewerte:
        //     true, wenn der Befehl ausgeführt werden kann, andernfalls false.
        public bool CanExecute(object parameter)
        {
            return false;
        }
        //
        // Zusammenfassung:
        //     Definiert die Methode, die aufgerufen wird, wenn der Befehl aufgerufen wird.
        //
        // Parameter:
        //   parameter:
        //     Vom Befehl verwendete Daten. Wenn der Befehl keine Datenübergabe erfordert,
        //     kann das Objekt auf null festgelegt werden.
        public void Execute(object parameter)
        {

        }


        /// <summary>
        /// A short descriptive message about this command.
        /// </summary>
        /// <returns></returns>
        public string ShortMessage()
        {
            return "testcommand";
        }

        public void Dispose()
        {

        }
    }

    [Export(typeof(IModule))]
    public class Module : IModule
    {
        //public static ModuleInformation Information
        //{
        //    get
        //    {
        //        ModuleInformation information = new ModuleInformation();
        //        information.Name = System.Reflection.Assembly.GetExecutingAssembly().GetName().Name; //"VEF.TestModule";
        //        information.Dependencies.Add(new ModuleInformation() { Name = "PCF.Core" });
        //        return information;
        //    }
        //}

        //     [ImportingConstructor]
        public Module()
        {

        }

        public void PreInitialize()
        {

        }

        public void Initialize()
        {
            LoadCommands();
            LoadMenus();
            LoadToolbar();

            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as AbstractWorkspace;
           


            VEFModule.UnityContainer.RegisterType<VEXProjectHandler>();
            VEFModule.UnityContainer.RegisterType<VEXProjectViewModel>();
            VEFModule.UnityContainer.RegisterType<VEXProjectView>();

            IContentHandler handler = VEFModule.UnityContainer.Resolve(typeof(VEXProjectHandler), "") as VEXProjectHandler;
            IContentHandlerRegistry chr = VEFModule.UnityContainer.Resolve(typeof(IContentHandlerRegistry), "") as IContentHandlerRegistry;

            chr.Register(handler);

            //SceneManager and scenegraph needs socketserver!
            VEFModule.UnityContainer.RegisterType<ISocketServerService, SocketServerManager>(new ContainerControlledLifetimeManager());
            VEFModule.UnityContainer.RegisterType<SocketServerToolViewModel>(new ContainerControlledLifetimeManager());
            var tvm = VEFModule.UnityContainer.Resolve(typeof(SocketServerToolViewModel), "") as SocketServerToolViewModel;
            tvm.IsVisible = false;
            workspace.Tools.Add(tvm);
            ToolViewModel propertiesView = workspace.Tools.First(f => f.ContentId == "SocketServer");
            propertiesView.IsVisible = true;
            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;
            _SocketServerManager.SocketServerToolModel = tvm.Model as SocketServerToolModel;


            VEFModule.UnityContainer.RegisterType<FileWatcherHandler>();
            VEFModule.UnityContainer.RegisterType<FileWatcherViewModel>();
            VEFModule.UnityContainer.RegisterType<FileWatcherView>();

            IContentHandler fileWatcherHandler = VEFModule.UnityContainer.Resolve(typeof(FileWatcherHandler), "") as FileWatcherHandler;
            chr.Register(fileWatcherHandler);


            //VEFModule.UnityContainer.RegisterType<IFileWatcherService, FileWatcherManager>(new ContainerControlledLifetimeManager());
            //VEFModule.UnityContainer.RegisterType<FileWatcherViewModel>(new ContainerControlledLifetimeManager());
            //var fw_tvm = VEFModule.UnityContainer.Resolve(typeof(FileWatcherViewModel), "") as FileWatcherViewModel;
            //fw_tvm.IsVisible = false;
            //workspace.Tools.Add(fw_tvm);
            //ToolViewModel fwView = workspace.Tools.First(f => f.ContentId == "FileWatcher");
            //fwView.IsVisible = true;
            //var _FileWatcherManager = VEFModule.UnityContainer.Resolve(typeof(FileWatcherManager), "") as FileWatcherManager;
            //_FileWatcherManager.FileWatcherToolModel = fw_tvm.Model as FileWatcherToolModel;


            //------------------------------------------------------
            // REgister SceneService
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<ISceneService, SceneManager>(new ContainerControlledLifetimeManager());

            //------------------------------------------------------
            //Register File Type
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<SceneViewerHandler>();
            VEFModule.UnityContainer.RegisterType<SceneViewModel>();
            VEFModule.UnityContainer.RegisterType<SceneView>();

            IContentHandler sceneViewerhandler = VEFModule.UnityContainer.Resolve(typeof(SceneViewerHandler), "") as SceneViewerHandler;
            chr.Register(sceneViewerhandler);

            VEFModule.UnityContainer.RegisterType<SceneGraphToolViewModel>();
            // _container.RegisterType<SceneToolView>();

            var sgtvm = VEFModule.UnityContainer.Resolve(typeof(SceneGraphToolViewModel), "") as SceneGraphToolViewModel;
            sgtvm.IsVisible = true;
            workspace.Tools.Add(sgtvm);
            ToolViewModel sceneGraphView = workspace.Tools.First(f => f.ContentId == "SceneGraph");
            sceneGraphView.IsVisible = true;


            //------------------------------------------------------
            // REgister AtlasService
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<IAtlasService, AtlasManager>(new ContainerControlledLifetimeManager());

            //------------------------------------------------------
            //Register File Type
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<AtlasHandler>();
            VEFModule.UnityContainer.RegisterType<AtlasViewModel>();
            VEFModule.UnityContainer.RegisterType<AtlasView>();

            IContentHandler AtlasViewerhandler = VEFModule.UnityContainer.Resolve(typeof(AtlasHandler), "") as AtlasHandler;
            chr.Register(AtlasViewerhandler);

            //VEFModule.UnityContainer.RegisterType<AtlasGraphToolViewModel>();
            //// _container.RegisterType<AtlasToolView>();

            //var sgtvm = VEFModule.UnityContainer.Resolve(typeof(AtlasGraphToolViewModel), "") as AtlasGraphToolViewModel;
            //sgtvm.IsVisible = true;
            //workspace.Tools.Add(sgtvm);

            //------------------------------------------------------
            // REgister AtlasService
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<IAnimationEditorService, AnimationEditorManager>(new ContainerControlledLifetimeManager());

            //------------------------------------------------------
            //Register File Type
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<AnimationEditorHandler>();
            VEFModule.UnityContainer.RegisterType<AnimationEditorViewModel>();
            VEFModule.UnityContainer.RegisterType<AnimationEditorView>();

            IContentHandler AnimationEditorViewerhandler = VEFModule.UnityContainer.Resolve(typeof(AnimationEditorHandler), "") as AnimationEditorHandler;
            chr.Register(AnimationEditorViewerhandler);



            //------------------------------------------------------
            // Register DatabaseManager
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<IDatabaseService, DatabaseManager>(new ContainerControlledLifetimeManager());

            LoadSettings();

            RegisterDatabase();
            SetDatabaseContext();



            var shell = VEFModule.UnityContainer.Resolve(typeof(ShellViewMetro), "shell") as ShellViewMetro;
            shell.LoadLayout(); //load avalondock layout
            (shell as Window).Show();
        }

        private void LoadSettings()
        {
            DBOptions dbOption = DBOptions.Default;
            ISettingsManager manager = VEFModule.UnityContainer.Resolve(typeof(ISettingsManager), "") as ISettingsManager;
            manager.Add(new DBSettingsItem("Datenbank", 1, dbOption));


            var managerDB = VEFModule.UnityContainer.Resolve(typeof(IDatabaseService), "") as IDatabaseService;
            managerDB.AddDBOption(dbOption);

            //    managerDB.SetCurrentDB(dbOption.Guid);
            //ObservableCollection<IDB> Databases
            //manager.Get("Text Editor").Add(new DBSettingsItem("General", 1, EditorOptions.Default));
        }

        private void RegisterDatabase()
        {
            var managerDB = VEFModule.UnityContainer.Resolve(typeof(IDatabaseService), "") as IDatabaseService;
            IDAL.IDAL newComID_DB = new IDAL.IDAL();
            newComID_DB.DBOptions = managerDB.DBOptions[0];

            newComID_DB.DBOptions.Name = "SQLITE DB";
            newComID_DB.DBOptions.DBType = VEF.DAL.Interface.DBType.SQLite;

            managerDB.AddDB(newComID_DB);
        }

        private void SetDatabaseContext()
        {
            var managerDB = VEFModule.UnityContainer.Resolve(typeof(IDatabaseService), "") as IDatabaseService; 

            var db = managerDB.DBs.Where(x => x.DBOptions.Name == "SQLITE DB");
            if (db.Any())
                managerDB.SetCurrentDB(db.First().Guid);
        }


        public void PostInitialize()
        {

        }

        private void LoadCommands()
        {
            //    VEFModule.EventAggregator.GetEvent<SplashMessageUpdateEvent>().Publish(new SplashMessageUpdateEvent { Message = "Commands.." });
            var manager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;

            var openCommand = new DelegateCommand(OpenModule);// new TestCommand(); // new DelegateCommand(OpenModule);
            var exitCommand = new DelegateCommand(CloseCommandExecute);
            var saveCommand = new DelegateCommand(SaveDocument, CanExecuteSaveDocument);
            var saveAsCommand = new DelegateCommand(SaveAsDocument, CanExecuteSaveAsDocument);
            var themeCommand = new DelegateCommand<string>(ThemeChangeCommand);
            var loggerCommand = new DelegateCommand(ToggleLogger);
            var OutputCommand = new DelegateCommand(ToggleOutput);




            manager.RegisterCommand("OPEN", openCommand);
            manager.RegisterCommand("SAVE", saveCommand);
            manager.RegisterCommand("SAVEAS", saveAsCommand);
            manager.RegisterCommand("EXIT", exitCommand);
            manager.RegisterCommand("LOGSHOW", loggerCommand);
            manager.RegisterCommand("OUTPUTSHOW", OutputCommand);
            manager.RegisterCommand("THEMECHANGE", themeCommand);
        }


        private void LoadMenus()
        {
            // VEFModule.EventAggregator.GetEvent<SplashMessageUpdateEvent>().Publish(new SplashMessageUpdateEvent { Message = "Menus.." });
            var manager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;
            var menuService = VEFModule.UnityContainer.Resolve(typeof(IMenuService), "") as IMenuService;
            var settingsManager = VEFModule.UnityContainer.Resolve(typeof(ISettingsManager), "") as ISettingsManager;
            var themeSettings = VEFModule.UnityContainer.Resolve(typeof(IThemeSettings), "") as IThemeSettings;
            var recentFiles = VEFModule.UnityContainer.Resolve(typeof(IRecentViewSettings), "") as IRecentViewSettings;
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as IWorkspace;
            //###    ToolViewModel logger = workspace.Tools.First(f => f.ContentId == "Logger");
            //###     ToolViewModel Output = workspace.Tools.First(f => f.ContentId == "Output");
            //   ToolViewModel searchView = workspace.Tools.First(f => f.ContentId == "Search");
            //ToolViewModel propertiesView = workspace.Tools.First(f => f.ContentId == "Properties");
            //propertiesView.IsVisible = true;
            //in xaml {x:Static avalonDockProperties:Resources.Anchorable_AutoHide}
            menuService.Add(new MenuItemViewModel(Resources._File, 1));

            menuService.Get(Resources._File).Add(
                 (new MenuItemViewModel(Resources._New, 3, new ImageSource()
                 {
                     Source = null
                     //new BitmapImage(
                     //new Uri(
                     //@"pack://application:,,,/Module.Core;component/Icons/NewRequest_8796.png"))
                 },
                     manager.GetCommand("NEW")
                 , new KeyGestureWPF()
                         {
                             Gesture = new KeyGesture(Key.N, ModifierKeys.Control, "Ctrl + N")
                         })));
            menuService.Get(Resources._File).Add(
                                             (new MenuItemViewModel(Resources._Open, 4, new ImageSource()
                                             {
                                                 Source = null
                                             },
                                                 manager.GetCommand("OPEN")
                                             , new KeyGestureWPF()
                                             {
                                                 Gesture = new KeyGesture(Key.O, ModifierKeys.Control, "Ctrl + O")
                                             })));
            menuService.Get(Resources._File).Add(
                                              (new MenuItemViewModel(Resources._Save, 5, new ImageSource()
                                              {
                                                  Source = null
                                              },
                                                  manager.GetCommand("SAVE")
                                              , new KeyGestureWPF()
                                              {
                                                  Gesture = new KeyGesture(Key.S, ModifierKeys.Control, "Ctrl + S")
                                              })));
            //menuService.Get(Resources._File).Add(
            //    (new MenuItemViewModel(Resources._Open, 4,
            //                           new BitmapImage(
            //                               new Uri(
            //                                   @"pack://application:,,,/Module.Core;component/Icons/OpenFileDialog_692.png")),
            //                           manager.GetCommand("OPEN"),
            //                           new KeyGesture(Key.O, ModifierKeys.Control, "Ctrl + O"))));
            //menuService.Get(Resources._File).Add(new MenuItemViewModel(Resources._Save, 5,
            //                                                   new BitmapImage(
            //                                                       new Uri(
            //                                                           @"pack://application:,,,/Module.Core;component/Icons/Save_6530.png")),
            //                                                   manager.GetCommand("SAVE"),
            //                                                   new KeyGesture(Key.S, ModifierKeys.Control, "Ctrl + S")));
            menuService.Get(Resources._File).Add(new SaveAsMenuItemViewModel(Resources.SAVEAS, 6,
                                                   new ImageSource() {  Source = null },
                                                   manager.GetCommand("SAVEAS"), null, false, false));

            //menuService.Get(Resources._File).Add(new MenuItemViewModel(Resources.Close, 8, null, manager.GetCommand("CLOSE"),
            //                                                   new KeyGesture(Key.F4, ModifierKeys.Control, "Ctrl + F4")));

            ////##          menuService.Get(Resources._File).Add(recentFiles.RecentMenu);

            //menuService.Get(Resources._File).Add(new MenuItemViewModel(Resources.E_xit, 101, null, manager.GetCommand("EXIT"),
            //                                                   new KeyGesture(Key.F4, ModifierKeys.Alt, "Alt + F4")));


            menuService.Add(new MenuItemViewModel(Resources._Edit, 2));
            //menuService.Get(Resources._Edit).Add(new MenuItemViewModel(Resources._Undo, 1,
            //                                                   new BitmapImage(
            //                                                       new Uri(
            //                                                           @"pack://application:,,,/Module.Core;component/Icons/Undo_16x.png")),
            //                                                   ApplicationCommands.Undo));
            menuService.Get(Resources._Edit).Add((new MenuItemViewModel("_Undo", 3, new ImageSource()
                {
                    Source = null
                    //new BitmapImage(
                    //new Uri(
                    //@"pack://application:,,,/Module.Core;component/Icons/Undo_16x.png"))
                },
                    ApplicationCommands.Undo
                , new KeyGestureWPF()
                        {
                            Gesture = new KeyGesture(Key.N, ModifierKeys.Control, "Ctrl + Z")
                        })));
            //menuService.Get(Resources._Edit).Add(new MenuItemViewModel(Resources._Redo, 2,
            //                                                   new BitmapImage(
            //                                                       new Uri(
            //                                                           @"pack://application:,,,/Module.Core;component/Icons/Redo_16x.png")),
            //                                                   ApplicationCommands.Redo));
            //menuService.Get(Resources._Edit).Add(MenuItemViewModel.Separator(15));
            //menuService.Get(Resources._Edit).Add(new MenuItemViewModel(Resources.Cut, 20,
            //                                                   new BitmapImage(
            //                                                       new Uri(
            //                                                           @"pack://application:,,,/Module.Core;component/Icons/Cut_6523.png")),
            //                                                   ApplicationCommands.Cut));
            //menuService.Get(Resources._Edit).Add(new MenuItemViewModel(Resources.Copy, 21,
            //                                                   new BitmapImage(
            //                                                       new Uri(
            //                                                           @"pack://application:,,,/Module.Core;component/Icons/Copy_6524.png")),
            //                                                   ApplicationCommands.Copy));
            //menuService.Get(Resources._Edit).Add(new MenuItemViewModel(Resources._Paste, 22,
            //                                                   new BitmapImage(
            //                                                       new Uri(
            //                                                           @"pack://application:,,,/Module.Core;component/Icons/Paste_6520.png")),
            //                                                   ApplicationCommands.Paste));

            menuService.Add(new MenuItemViewModel(Resources._View, 3));

            //if (logger != null)
            //    menuService.Get(Resources._View).Add(new MenuItemViewModel(Resources._Logger, 2,
            //        //new BitmapImage(
            //        //    new Uri(
            //        //        @"pack://application:,,,/ComID.Core;component/Icons/Undo_16x.png"))
            //                                                             null,
            //                                                       manager.GetCommand("LOGSHOW")) { IsCheckable = true, IsChecked = logger.IsVisible });
            //if (Output != null)
            //    menuService.Get(Resources._View).Add(new MenuItemViewModel(Resources._Output, 2,
            //        //new BitmapImage(
            //        //    new Uri(
            //        //        @"pack://application:,,,/ComID.Core;component/Icons/Undo_16x.png"))
            //                                                             null,
            //                                                       manager.GetCommand("OUTPUTSHOW")) { IsCheckable = true, IsChecked = Output.IsVisible });


            //if (searchView != null)
            //    menuService.Get("_View").Add(new MenuItemViewModel("_Search", 2,
            //        //new BitmapImage(
            //        //    new Uri(
            //        //        @"pack://application:,,,/ComID.Core;component/Icons/Undo_16x.png"))
            //                                                             null,
            //                                                       manager.GetCommand("SEARCHSHOW")) { IsCheckable = true, IsChecked = searchView.IsVisible });
            //if (propertiesView != null)
            //    menuService.Get(Resources._View).Add(new MenuItemViewModel(Resources._Properties, 3,
            //        //new BitmapImage(
            //        //    new Uri(
            //        //        @"pack://application:,,,/ComID.Core;component/Icons/Undo_16x.png"))
            //                                                             null,
            //                                                       manager.GetCommand("PROPERTIESSHOW")) { IsCheckable = true, IsChecked = propertiesView.IsVisible });

            menuService.Get(Resources._View).Add(new MenuItemViewModel(Resources.Themes, 1));

            //Set the checkmark of the theme menu's based on which is currently selected
            //menuService.Get("_View").Get("Themes").Add(new MenuItemViewModel("Dark", 1, null,
            //                                                                 manager.GetCommand("THEMECHANGE"))
            //                                               {
            //                                                   IsCheckable = true,
            //                                                   IsChecked = (themeSettings.SelectedTheme == "Dark"),
            //                                                   CommandParameter = "Dark"
            //                                               });
            menuService.Get(Resources._View).Get(Resources.Themes).Add(new MenuItemViewModel("Light", 2, null,
                                                                             manager.GetCommand("THEMECHANGE"))
            {
                IsCheckable = true,
                IsChecked = (themeSettings.SelectedTheme == "Light"),
                CommandParameter = "Light"
            });

            menuService.Add(new MenuItemViewModel(Resources._Tools, 4));
            menuService.Get(Resources._Tools).Add(new MenuItemViewModel(Resources.Settings, 1, null, settingsManager.SettingsCommand));

            menuService.Add(new MenuItemViewModel(Resources._Help, 4));
        }

        private void LoadToolbar()
        {
            // VEFModule.EventAggregator.GetEvent<SplashMessageUpdateEvent>().Publish(new SplashMessageUpdateEvent { Message = "Toolbar.." });
            var toolbarService = VEFModule.UnityContainer.Resolve(typeof(ToolbarService), "") as ToolbarService;
            var menuService = VEFModule.UnityContainer.Resolve(typeof(MenuItemViewModel), "") as MenuItemViewModel;

            toolbarService.Add(new ToolbarViewModel("Standard", 1) { Band = 0, BandIndex = 0, IsChecked = true });
            toolbarService.Get("Standard").Add(menuService.Get(Resources._File).Get(Resources._New));
            toolbarService.Get("Standard").Add(menuService.Get(Resources._File).Get(Resources._Open));
            toolbarService.Get("Standard").Add(menuService.Get(Resources._File).Get(Resources._Save));

            var tb = new ToolbarViewModel("_Edit", 1) { Band = 0, BandIndex = 1, };
            tb.IsChecked = false;
            toolbarService.Add(tb);
            toolbarService.Get("_Edit").Add(menuService.Get("_Edit").Get("_Undo"));
            //toolbarService.Get(Resources.Edit).Add(menuService.Get(Resources._Edit).Get(Resources._Redo));
            //toolbarService.Get(Resources.Edit).Add(MenuItemViewModel.Separator(3));
            //toolbarService.Get(Resources.Edit).Add(menuService.Get(Resources._Edit).Get(Resources.Cut));
            //toolbarService.Get(Resources.Edit).Add(menuService.Get(Resources._Edit).Get(Resources.Copy));
            //toolbarService.Get(Resources.Edit).Add(menuService.Get(Resources._Edit).Get(Resources._Paste));

            menuService.Get("_Tools").Add(toolbarService.RightClickMenu);

            toolbarService.ToolBarTrayVisible = false;

            //Initiate the position settings changes for toolbar
            VEFModule.UnityContainer.Resolve(typeof(ToolbarPositionSettings), "");
        }

        #region Commands


        private void CloseCommandExecute()
        {
            IShell shell = VEFModule.UnityContainer.Resolve(typeof(IShell), "") as IShell;
            shell.Close();
        }

        #region Open

        private void OpenModule()
        {
            var service = VEFModule.UnityContainer.Resolve(typeof(IOpenDocumentService), "") as IOpenDocumentService;
            service.Open();
        }

        #endregion

        #region Save

        private bool CanExecuteSaveDocument()
        {
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as AbstractWorkspace;
            if (workspace.ActiveDocument != null
                && workspace.ActiveDocument.Model != null)
            {
                return workspace.ActiveDocument.Model.IsDirty;
            }
            return false;
        }

        private bool CanExecuteSaveAsDocument()
        {
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as AbstractWorkspace;
            return (workspace.ActiveDocument != null);
        }

        private void SaveDocument()
        {
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as AbstractWorkspace;
            ICommandManager manager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;
            workspace.ActiveDocument.Handler.SaveContent(workspace.ActiveDocument);
            manager.Refresh();
        }

        private void SaveAsDocument()
        {
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as AbstractWorkspace;
            ICommandManager manager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;
            if (workspace.ActiveDocument != null)
            {
                workspace.ActiveDocument.Handler.SaveContent(workspace.ActiveDocument, true);
                manager.Refresh();
            }
        }
        #endregion

        #region Theme

        private void ThemeChangeCommand(string s)
        {
            var manager = VEFModule.UnityContainer.Resolve(typeof(ThemeManager), "") as AbstractWorkspace;
            var menuService = VEFModule.UnityContainer.Resolve(typeof(IMenuService), "") as AbstractWorkspace;
            var win = VEFModule.UnityContainer.Resolve(typeof(IShell), "") as IShell;
            //MenuItemViewModel mvm =  menuService.Get(Resources._View).Get(Resources.Themes).Get(manager.CurrentTheme.Name) as MenuItemViewModel;

            //if (manager.CurrentTheme.Name != s)
            //{
            //    if (mvm != null)
            //        mvm.IsChecked = false;
            //    win.Dispatcher.Invoke(new Action(() => manager.SetCurrent(s)));
            //}
            //else
            //{
            //    if (mvm != null)
            //        mvm.IsChecked = true;
            //}
        }

        #endregion

        #region Logger click

        private void ToggleLogger()
        {
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as AbstractWorkspace;
            var menuService = VEFModule.UnityContainer.Resolve(typeof(IMenuService), "") as AbstractWorkspace;
            ToolViewModel logger = workspace.Tools.First(f => f.ContentId == "Logger");
            //if (logger != null)
            //{
            //    logger.IsVisible = !logger.IsVisible;
            //    var mi = menuService.Get(Resources._View).Get(Resources._Logger) as MenuItemViewModel;
            //    mi.IsChecked = logger.IsVisible;
            //}
        }

        #endregion

        #region Output click

        private void ToggleOutput()
        {
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as AbstractWorkspace;
            var menuService = VEFModule.UnityContainer.Resolve(typeof(IMenuService), "") as AbstractWorkspace;
            ToolViewModel Output = workspace.Tools.First(f => f.ContentId == "Output");
            //if (Output != null)
            //{
            //    Output.IsVisible = !Output.IsVisible;
            //    var mi = menuService.Get(Resources._View).Get(Resources._Output) as MenuItemViewModel;
            //    mi.IsChecked = Output.IsVisible;
            //}
        }

        #endregion


      

        #endregion


    }

}
