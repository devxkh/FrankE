using Prism.Events;
using System;
using System.Collections.Generic;
using System.Text;
using VEF.Interfaces;
using VEF.Interfaces.Events;
using VEF.Interfaces.Services;
using VEX.Core.View.Scene;
using VEX.Model.Scene;

namespace VEX.Core.Shared.ViewModel.Scene
{
    internal class SceneGraphToolViewModel : ToolViewModel
    {
      //  private readonly IEventAggregator _aggregator;
        private readonly ILoggerService _logger;
        private IWorkspace _workspace;
        private readonly SceneGraphToolModel _model;
        private readonly SceneGraphToolView _view;

        public override PaneLocation PreferredLocation
        {
            get { return PaneLocation.Left; }
        }

        public SceneGraphToolViewModel(AbstractWorkspace workspace)
        {
            _workspace = workspace;
            Name = "SceneGraph";
            Title = "SceneGraph";
            ContentId = "SceneGraph";
             _model = new SceneGraphToolModel();
            Model = _model;
            IsVisible = true;

            _view = new SceneGraphToolView();
            _view.DataContext = _model;
            View = _view;

            //_aggregator = _container.Resolve<IEventAggregator>();
            //_aggregator.GetEvent<LogEvent>().Subscribe(AddLog);

            //_logger = _container.Resolve<ILoggerService>();


        }

        private void AddLog(ILoggerService logger)
        {
            //  _model.AddLog(logger);
        }


    }
}
