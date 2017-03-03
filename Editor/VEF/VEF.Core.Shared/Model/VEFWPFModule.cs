using Prism.Events;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Interfaces.Settings;
using VEF.Model.Services;
using VEF.Model.Settings;
using Microsoft.Practices.Unity;
using System.Composition;
using System.Windows.Media;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Base;
using System.Windows;
using VEF.Interfaces.Themes;
using VEF.View.Shell;
using VEF.Core.Settings;
using VEF.XForms.Model.Services;
using VEF.Core.View;
using VEF.Core.Handler;
using VEF.Core.Shared.ViewModel;
using System.ComponentModel;
using Prism.Commands;
using VEF.Interfaces.Events;
using VEF.Core.Model.Services;
using System.Windows.Input;
using VEF.ViewModel;
using VEF.ViewModel.Logger;
using Module.PFExplorer.Service;

namespace VEF.Model
{
    [Export(typeof(IModule))]
    public class VEFWPFModule : VEFModule
    {
        public override void PreInitialize()
        {
            base.PreInitialize();
        }

        public override void Initialize()
        {
            base.Initialize();
            //  EventAggregator.PublishOnUIThread(new SplashMessageUpdateEvent { Message = "Loading Wide Core Module" });
            // EventAggregator.GetEvent<SplashMessageUpdateEvent>().Publish(new SplashMessageUpdateEvent { Message = "Loading Wide Core Module" });
            //not per default!
            //_container.RegisterType<TextViewModel>();
            //_container.RegisterType<TextModel>();
            //_container.RegisterType<TextView>();
            //      _container.RegisterType<AllFileHandler>();
            //UnityContainer.RegisterType<IThemeSettings, ThemeSettingsWPF>();
            UnityContainer.RegisterType<IThemeSettings, ThemeSettings>();
            UnityContainer.RegisterType<IRecentViewSettings, RecentViewSettings>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<IWindowPositionSettings, WindowPositionSettings>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<IToolbarPositionSettings, ToolbarPositionSettings>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<ICommandManager, VEF.Model.Services.CommandManager>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<IContentHandlerRegistry, ContentHandlerRegistry>(new ContainerControlledLifetimeManager());

            UnityContainer.RegisterType<IStatusbarService, VEFStatusbar>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<IThemeManager, ThemeManager>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<IToolbarService, ToolbarService>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<IMenuService, MenuItemViewModel>(new ContainerControlledLifetimeManager(),
                                                                     new InjectionConstructor(
                                                                         new InjectionParameter(typeof(string), "$MAIN$"),
                                                                         new InjectionParameter(typeof(int), 1),
                                                                         new InjectionParameter(typeof(IImageSource), null),
                                                                         new InjectionParameter(typeof(ICommand),
                                                                                                null),
                                                                         new InjectionParameter(
                                                                             typeof(IKeyGesture), null),
                                                                         new InjectionParameter(typeof(bool), false),
                                                                         new InjectionParameter(typeof(bool), false)));
            UnityContainer.RegisterType<ToolbarViewModel>(
                new InjectionConstructor(new InjectionParameter(typeof(string), "$MAIN$"),
                                         new InjectionParameter(typeof(int), 1),
                                         new InjectionParameter(typeof(IImageSource), null),
                                         new InjectionParameter(typeof(ICommand), null),
                                         new InjectionParameter(typeof(bool), false)));

            UnityContainer.RegisterType<ISettingsManager, SettingsManager>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<IOpenDocumentService, OpenDocumentService>(new ContainerControlledLifetimeManager());
            UnityContainer.RegisterType<ILoggerService, LoggerService>(new ContainerControlledLifetimeManager());
            //AppCommands();
            //LoadSettings();

            ////Try resolving a workspace
            //try
            //{
            //    _container.Resolve<AbstractWorkspace>();
            //}
            //catch
            //{
            //    _container.RegisterType<AbstractWorkspace, Workspace>(new ContainerControlledLifetimeManager());
            //}

            //// Try resolving a logger service - if not found, then register the NLog service
            //try
            //{
            //    _container.Resolve<ILoggerService>();
            //}
            //catch
            //{
            //    _container.RegisterType<ILoggerService, NLogService>(new ContainerControlledLifetimeManager());
            //}
            // if (IsMetro)
            // {
            //Use MahApps Metro window
            VEFModule.UnityContainer.RegisterType<IShell, ShellViewMetro>(new ContainerControlledLifetimeManager());
            // }

            var commandManager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;
            var registry = VEFModule.UnityContainer.Resolve(typeof(ContentHandlerRegistry), "") as ContentHandlerRegistry;

            //TODO: Check if you can hook up to the Workspace.ActiveDocument.CloseCommand
            var closeCommand = new DelegateCommand<object>(CloseDocument, CanExecuteCloseDocument);
            commandManager.RegisterCommand("CLOSE", closeCommand);


            commandManager.RegisterCommand("NEW", registry.NewCommand);


            VEFModule.UnityContainer.RegisterType<IPropertiesService, PropertiesManager>(new ContainerControlledLifetimeManager());
            VEFModule.UnityContainer.RegisterType<PropertiesToolViewModel>();
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as AbstractWorkspace;
            var tvm = VEFModule.UnityContainer.Resolve(typeof(PropertiesToolViewModel), "") as PropertiesToolViewModel;
            tvm.IsVisible = false;
            workspace.Tools.Add(tvm);
            ToolViewModel propertiesView = workspace.Tools.First(f => f.ContentId == "Properties");
            propertiesView.IsVisible = true; //todo as menu item!!

            var loggerToolViewModel = VEFModule.UnityContainer.Resolve(typeof(LoggerToolViewModel), "") as LoggerToolViewModel;
            workspace.Tools.Add(loggerToolViewModel);
            ToolViewModel loggerView = workspace.Tools.First(f => f.ContentId == "Logger");
            loggerView.IsVisible = true; //todo as menu item!!

            VEFModule.UnityContainer.RegisterType<IOutputService, OutputService>(new ContainerControlledLifetimeManager());//new ContainerControlledLifetimeManager());
            VEFModule.UnityContainer.RegisterType<OutputViewModel>();
             var outputViewModel = VEFModule.UnityContainer.Resolve(typeof(OutputViewModel),"") as OutputViewModel;
            workspace.Tools.Add(outputViewModel);
            ToolViewModel outputView = workspace.Tools.First(f => f.ContentId == "Output");
            outputView.IsVisible = true; //todo as menu item!!

            //------------------------------------------------------
            //Register File Type
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<XMLHandler>();
            VEFModule.UnityContainer.RegisterType<XMLViewModel>();
            VEFModule.UnityContainer.RegisterType<XMLView>();

            IContentHandler handler = VEFModule.UnityContainer.Resolve(typeof(XMLHandler), "") as XMLHandler;
            (VEFModule.UnityContainer.Resolve(typeof(ContentHandlerRegistry), "") as ContentHandlerRegistry).Register(handler);


            //------------------------------------------------------
            // REgister Project-FileExplorer
            //------------------------------------------------------
            VEFModule.UnityContainer.RegisterType<IProjectTreeService, ProjectTreeManager>(new ContainerControlledLifetimeManager());
            VEFModule.UnityContainer.RegisterType<ProjectToolViewModel>();
            workspace.Tools.Add(VEFModule.UnityContainer.Resolve(typeof(ProjectToolViewModel),"") as ProjectToolViewModel );
            ToolViewModel projectView = workspace.Tools.First(f => f.ContentId == "Project");
            projectView.IsVisible = true; //todo as menu item!!

            //load layout after all modules are loaded!
            //var shell = VEFModule.UnityContainer.Resolve(typeof(ShellViewMetro), "shell") as ShellViewMetro;
            //shell.LoadLayout(); //load avalondock layout

            var manager = VEFModule.UnityContainer.Resolve(typeof(ThemeManagerWPF), "ThemeManagerWPF") as ThemeManagerWPF;
            var themeSettings = VEFModule.UnityContainer.Resolve(typeof(ThemeSettings), "ThemeSettings") as ThemeSettings;
            //   var win = VEFModule.UnityContainer.Resolve<IShell>() as Window;
            manager.AddTheme(new LightTheme());
            //  manager.AddTheme(new DarkTheme());

            manager.SetCurrent("Light");

            //need to load core module first -> Show needs the style resources
          //  (shell as Window).Show();
        }

        public override void PostInitialize()
        {
            base.PostInitialize();
        }


        /// <summary>
        /// Can the close command execute? Checks if there is an ActiveDocument - if present, returns true.
        /// </summary>
        /// <param name="obj">The obj.</param>
        /// <returns><c>true</c> if this instance can execute close document; otherwise, <c>false</c>.</returns>
        private bool CanExecuteCloseDocument(object obj)
        {
            ContentViewModel vm = obj as ContentViewModel;
            if (vm != null)
                return true;

            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as IWorkspace;
            return workspace.ActiveDocument != null;
        }

        /// <summary>
        /// CloseDocument method that gets called when the Close command gets executed.
        /// </summary>
        private void CloseDocument(object obj)
        {
            IWorkspace workspace = VEFModule.UnityContainer.Resolve(typeof(AbstractWorkspace), "") as IWorkspace;
            ILoggerService logger = VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService;
            IMenuService menuService = VEFModule.UnityContainer.Resolve(typeof(IMenuService), "") as IMenuService;

            CancelEventArgs e = obj as CancelEventArgs;
            ContentViewModel activeDocument = obj as ContentViewModel;

            if (activeDocument == null)
                activeDocument = workspace.ActiveDocument;

            if (activeDocument.Handler != null && activeDocument.Model != null && activeDocument.Model.IsDirty)
            {
                //means the document is dirty - show a message box and then handle based on the user's selection
                var res = MessageBox.Show(string.Format("Save changes for document '{0}'?", activeDocument.Title),
                                          "Are you sure?", MessageBoxButton.YesNoCancel);

                //Pressed Yes
                if (res == MessageBoxResult.Yes)
                {
                    if (!workspace.ActiveDocument.Handler.SaveContent(workspace.ActiveDocument))
                    {
                        //Failed to save - return cancel
                        res = MessageBoxResult.Cancel;

                        //Cancel was pressed - so, we cant close
                        if (e != null)
                        {
                            e.Cancel = true;
                        }
                        return;
                    }
                }

                //Pressed Cancel
                if (res == MessageBoxResult.Cancel)
                {
                    //Cancel was pressed - so, we cant close
                    if (e != null)
                    {
                        e.Cancel = true;
                    }
                    return;
                }
            }

            if (e == null)
            {
                if (activeDocument.Model != null)
                    logger.Log("Closing document " + activeDocument.Model.Location, LogCategory.Info, LogPriority.None);

                workspace.Documents.Remove(activeDocument);
                VEFModule.EventAggregator.GetEvent<ClosedContentEvent>().Publish(activeDocument);
                menuService.Refresh();
            }
            else
            {
                // If the location is not there - then we can remove it.
                // This can happen when on clicking "No" in the popup and we still want to quit
                if (activeDocument.Model == null || (activeDocument.Model != null && activeDocument.Model.Location == null))
                {
                    workspace.Documents.Remove(activeDocument);
                    VEFModule.EventAggregator.GetEvent<ClosedContentEvent>().Publish(activeDocument);
                }
            }
        }
    }
}
