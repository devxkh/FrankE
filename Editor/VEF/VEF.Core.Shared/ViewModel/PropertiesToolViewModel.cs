using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Core.WPF.View;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model;
using VEF.XForms.Model;

namespace VEF.ViewModel
{
    public class PropertiesToolViewModel : ToolViewModel
    {
        private readonly PropertiesToolModel _model;
        private readonly PropertiesToolView _view;
        private IWorkspace _workspace;

        public PropertiesToolViewModel(AbstractWorkspace workspace)
        {
            Name = "Properties";
            Title = "Eigenschaften";
            ContentId = "Properties";
            _model = new PropertiesToolModel();//.Resolve<ICommandManager>(), container.Resolve<IMenuService>());
            Model = _model;
            IsVisible = true;

            _view = new PropertiesToolView();
            _view.DataContext = _model;
            View = _view;

         //    VEFModule.EventAggregator.GetEvent<LogEvent>().Subscribe(AddLog);

       //     _logger = _container.Resolve<ILoggerService>();
        }

        public override PaneLocation PreferredLocation
        {
            get { return PaneLocation.Right; }
        }
    }
}
