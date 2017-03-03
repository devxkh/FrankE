using Microsoft.Practices.Unity;
using Prism.Events;
using Prism.Unity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Interfaces.Settings;
using System.Composition;
using VEF.Model.Settings;
using VEF.Model.Services;

namespace VEF
{
  //  [Export(typeof(IModule))]
    public class VEFModule : IModule
    {
      //  private IUnityContainer test;
        /// <summary>
        /// The container used in the application
        /// </summary>
        private static IUnityContainer _container;

        /// <summary>
        /// The event aggregator
        /// </summary>
        private static IEventAggregator _eventAggregator;

        /// <summary>
        /// The event aggregator pattern
        /// </summary>
        public static IEventAggregator EventAggregator
        {
            get { if (_eventAggregator == null) _eventAggregator = new EventAggregator(); return _eventAggregator; }
        }

        public static IUnityContainer UnityContainer
        {
            get { if (_container == null) _container = new UnityContainer(); return _container; }
        }
        
        /// <summary>
        /// The constructor of the CoreModule
        /// </summary>
        /// <param name="container">The injected container used in the application</param>
        /// <param name="eventAggregator">The injected event aggregator</param>
        public VEFModule()//IUnityContainer container, IEventAggregator eventAggregator)//, IEventAggregator eventAggregator)
        {
        }

        public virtual void PreInitialize()
        {

        }

        public virtual void Initialize()
        {
          //  EventAggregator.PublishOnUIThread(new SplashMessageUpdateEvent { Message = "Loading Wide Core Module" });
           // EventAggregator.GetEvent<SplashMessageUpdateEvent>().Publish(new SplashMessageUpdateEvent { Message = "Loading Wide Core Module" });
            //not per default!
            //_container.RegisterType<TextViewModel>();
            //_container.RegisterType<TextModel>();
            //_container.RegisterType<TextView>();
            //      _container.RegisterType<AllFileHandler>();

        //    UnityContainer.RegisterType<IThemeSettings, ThemeSettings>();
        //    UnityContainer.RegisterType<IRecentViewSettings, RecentViewSettings>(new ContainerControlledLifetimeManager());
            //_container.RegisterType<IWindowPositionSettings, WindowPositionSettings>(
            //    new ContainerControlledLifetimeManager());
            //_container.RegisterType<IToolbarPositionSettings, ToolbarPositionSettings>(
            //    new ContainerControlledLifetimeManager());
            //_container.RegisterType<ICommandManager, CommandManager>(new ContainerControlledLifetimeManager());
            //_container.RegisterType<IContentHandlerRegistry, ContentHandlerRegistry>(
            //    new ContainerControlledLifetimeManager());
      //platform specific      _container.Register<IWindowPositionSettings, WindowPositionSettings>();
            UnityContainer.RegisterType<ICommandManager, CommandManager>();
            //_container.RegisterType<IStatusbarService, WideStatusbar>(new ContainerControlledLifetimeManager());
            //_container.RegisterType<IThemeManager, ThemeManager>();
            //_container.RegisterType<IThemeManager, ThemeManager>(new ContainerControlledLifetimeManager());
            //_container.RegisterType<IToolbarService, ToolbarService>(new ContainerControlledLifetimeManager());
            //_container.RegisterType<IMenuService, MenuItemViewModel>(new ContainerControlledLifetimeManager(),
            //                                                         new InjectionConstructor(
            //                                                             new InjectionParameter(typeof(string),
            //                                                                                    "$MAIN$"),
            //                                                             new InjectionParameter(typeof(int), 1),
            //                                                             new InjectionParameter(
            //                                                                 typeof(ImageSource), null),
            //                                                             new InjectionParameter(typeof(ICommand),
            //                                                                                    null),
            //                                                             new InjectionParameter(
            //                                                                 typeof(KeyGesture), null),
            //                                                             new InjectionParameter(typeof(bool), false),
            //                                                             new InjectionParameter(typeof(bool), false),
            //                                                             new InjectionParameter(
            //                                                                 typeof(IUnityContainer), _container)));
            //_container.RegisterType<ToolbarViewModel>(
            //    new InjectionConstructor(new InjectionParameter(typeof(string), "$MAIN$"),
            //                             new InjectionParameter(typeof(int), 1),
            //                             new InjectionParameter(typeof(ImageSource), null),
            //                             new InjectionParameter(typeof(ICommand), null),
            //                             new InjectionParameter(typeof(bool), false),
            //                             new InjectionParameter(typeof(IUnityContainer), _container)));

            //_container.RegisterType<ISettingsManager, SettingsManager>(new ContainerControlledLifetimeManager());
            //_container.RegisterType<IOpenDocumentService, OpenDocumentService>(new ContainerControlledLifetimeManager());

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

        }

        public virtual void PostInitialize()
        {

        }
    }
}
