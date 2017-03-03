#region License

// Copyright (c) 2014

#endregion

using VEF.Core.View;
using VEF.Interfaces;
using VEF.Interfaces.Events;
using VEF.Interfaces.Services;
using VEF.Model;
namespace VEF.ViewModel
{
    internal class OutputViewModel : ToolViewModel
    {
        private readonly OutputModel _model;
        private readonly OutputToolView _view;
        private IWorkspace _workspace;

        public override  PaneLocation PreferredLocation { get { return PaneLocation.Bottom; } }

        public OutputViewModel( AbstractWorkspace workspace)
        {
            Name = "Output";
            Title = "Output";
            ContentId = "Output";

         //   var test = container.Resolve<IOutputService>("MOS");
            _model = new OutputModel(VEFModule.UnityContainer.Resolve(typeof(IOutputService), "") as IOutputService);
               // new OutputModel();
            Model = _model;
            IsVisible = false;

            _view = new OutputToolView();
            _view.DataContext = _model;
            View = _view;

            VEFModule.EventAggregator.GetEvent<OutputEvent>().Subscribe(AddLog);
        }

        private void AddLog(IOutputService Output)
        {
            _model.AddLog(Output);
        }
    }
}