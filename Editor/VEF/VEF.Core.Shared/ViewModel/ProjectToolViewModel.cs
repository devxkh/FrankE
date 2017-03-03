
using Microsoft.Practices.Unity;
using Prism.Events;
using System.Collections.ObjectModel;
using System.Windows.Controls;
using VEF.Core.View;
using VEF.Interfaces;
using VEF.Interfaces.Events;
using VEF.Interfaces.Services;
using VEF.Model.PFExplorer;

namespace VEF.ViewModel
{
    internal class ProjectToolViewModel : ToolViewModel
    {
        private readonly ILoggerService _logger;
        private IWorkspace _workspace;
        private readonly IUnityContainer _container;
        private readonly ProjectToolModel _model;
        private readonly ProjectToolView _view;

        public override PaneLocation PreferredLocation
        {
            get { return PaneLocation.Right; }
        }

        public ProjectToolViewModel(IUnityContainer container, AbstractWorkspace workspace)
        {
            _workspace = workspace;
            _container = container;
            Name = "Project";
            Title = "Project";
            ContentId = "Project";
            _model = new ProjectToolModel();//.Resolve<ICommandManager>(), container.Resolve<IMenuService>());
            Model = _model;
            IsVisible = true;

            _view = new ProjectToolView();
            _view.DataContext = _model;
            View = _view;

           // _aggregator = _container.Resolve<IEventAggregator>();
            VEFModule.EventAggregator.GetEvent<LogEvent>().Subscribe(AddLog);

            _logger = _container.Resolve(typeof(ILoggerService),"") as ILoggerService;



            //CVMProject p1 = ((CVMProject)Workspace.This.VMTV.List[0]);
            //// CVMCategory cdata = new CVMCategory() { Name = "Data" };
            //// p1.Items.Add(cdata);

            ////------------- Scenes ----------------------
            //CVMCategory cScenes = new CVMCategory() { Name = "Scenes" };

            //p1.Items.Add(cScenes);

            //CVMScene sv = new CVMScene() { Name = "Scene 1" };
            //sv.Items.Add(new CVMCategory() { Name = "Cameras" });
            //sv.Items.Add(new CVMCategory() { Name = "Models" });
            //sv.Items.Add(new CVMCategory() { Name = "Sound" });
            //cScenes.Items.Add(sv);
            //// Workspace.This.VMTV.List.Add(new CVMProject() { Name = "Proj2" });

            ////------------- Models ----------------------
            //CVMCategory cModels = new CVMCategory() { Name = "Models" };
            //CVMCategory cChars = new CVMCategory() { Name = "Characters" };
            //CVMModel cModel = new CVMModel() { Name = "OgreHead", File = "ogrehead.mesh" };
            //CVMModel cModel2 = new CVMModel() { Name = "Human", File = "human.mesh" };

            //cChars.Items.Add(cModel);
            //cChars.Items.Add(cModel2);
            //cModels.Items.Add(cChars);
            //CVMCategory cCreatures = new CVMCategory() { Name = "Creatures" };
            //cModels.Items.Add(cCreatures);
            //p1.Items.Add(cModels);

            ////------------------ Sounds -------------------------
            //CVMCategory cSounds = new CVMCategory() { Name = "Sounds" };
            //p1.Items.Add(cSounds);

            ////------------------ Particles -------------------------
            //CVMCategory cParticles = new CVMCategory() { Name = "Particles" };
            //p1.Items.Add(cParticles);

        }

        private void AddLog(ILoggerService logger)
        {
          //  _model.AddLog(logger);
        }


    }
}